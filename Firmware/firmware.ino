/********************************************************************** 
* PROJETO BIOMA 
* 2021 
***********************************************************************/ 
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <LoRaTiny85.h>

const int   device_id = 7189;  // ID of this End node 
const float lambda    = 0.981; // Fator de ponderação (esquecimento)
const float deltaT    = 0.002; // Período de amostragem
const float Vrms      = 230;   // Valor nominal da tensão eficaz (estimativa)

float      w  =  1;      // Fator de ponderação inicial
float    I[3] = {0,0,0}; // Corrente instantânea antes de filtrada
float   If[3] = {0,0,0}; // Corrente instantânea depois de filtrada
float Irms[2] = {0,0};   // Corrente eficaz
double     Et = 0;       // Energia elétrica (calculada desde o momento em que o sistema é ligado)

volatile bool flag=false;

int contador = 0;

ISR(TIMER1_COMPA_vect) 
{
  flag=true;
}

void rotinaprincipal()
{
    // Desativa interrupções
    cli();
    // Atualiza fator de ponderação
    w=lambda*w+1;
    // Lê entrada da ADC3 (Pino 2 do integrado)
    I[0]=0.00322265625* ((float) analogRead(A3));        // Converte para tensão (3V3)
    // Filtro Digital
    If[0]=1.075*If[1]-0.3293*If[2] + 0.3354*(I[0]-I[2]); // Largura de Banda = 40 Hz
    // Estima valor eficaz
    Irms[0] = sqrt((1.0-1.0/w)*sq(Irms[1])+(1.0/w)*sq(If[0]));
    // Provavelmente é necessário colocar aqui algumas proteções como limite superior, inferior e banda morta
    // (garantir que valores de corrente inferiores Imin se traduzem em Irms=0)
    // Calcula energia elétrica
    Et+=Irms[0]*Vrms*deltaT;
    // Atualização dos estados
    If[2]=If[1];
    If[1]=If[0];
    I[2]=I[1];
    I[1]=I[0];
    Irms[1]=Irms[0];
    
    if (contador==1000){
      LoRaTiny85.beginPacket();
      LoRaTiny85.print("<");
      LoRaTiny85.print(device_id);
      LoRaTiny85.print(">Et=");
      LoRaTiny85.print(Et);
      LoRaTiny85.endPacket();
      contador =0;
    }
    else{
        contador++;
      }      
    // Ativa interrupções
    sei();
}

void entrarSleep(void)
{
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
  power_adc_disable();
  power_timer0_disable();
  sleep_mode();
  sleep_disable();
  power_all_enable();
}


void setup()
{
  OSCCAL = 0x5A;          // Calibração do clock interno
  // Configura Timer 1 para gerar uma interrupção a cada 2ms (500 Hz)
  cli();                  //Desabilita interrupções globais
  TCCR1 = 0;              //Limpa registo TCCR1
  TCCR1 |= (1 << CTC1);   //Força modo CTC
  TCCR1 |=  (1 << CS13);  //Define prescalers: bits CS13-CS10
  TCNT1 = 0;              //Limpa registo TCNT1
  OCR1C = 124;            //Estabelece o valor de comparação
  TIMSK |= (1 << OCIE1A); //Ativa interrupções por comparação
  // Configura transceiver LoRa
  if (!LoRaTiny85.begin(868100000)) {
    while (1);
  }
  LoRaTiny85.setSyncWord(0x34);
  sei();                  //Habilita interrupções globais
}

void loop()
{
  if (flag) {
    rotinaprincipal();
    flag=false;
  }
  entrarSleep();
}
