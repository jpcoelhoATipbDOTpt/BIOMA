# Organization

Describes the organization entity
-  `id`: Organization Identifier
   -  Attribute type: **Property**. 
   -  Required
-  `legalName`: Organization's legal name
   -  Attribute type: **Property**. [legalName](https://schema.org/legalName)
   -  Required
-  `taxID`: The organization's tax number
   -  Attribute type: **Property**. [taxID](https://schema.org/taxID)
   -  Required
-  `ssnID`: The organization's social security number
   -  Attribute type: **Property**. 
   -  Required
-  `caeID`: The organization's economic activity code
   -  Attribute type: **Property**. 
   -  Optional
-  `address`: The company's headquarters address
   -  Attribute type: **Property**. [address](https://schema.org/address)
   -  Optional
-  `email`: Contact email address
   -  Attribute type: **Property**. [email](https://schema.org/email)
   -  Required
-  `telephone`: Mobile or telephone contact
   -  Attribute type: **Property**. [telephone](https://schema.org/telephone)
   -  Optional
-  `location`: Company's geographic location (latitude and longitude)
   -  Attribute type: **Property**. [GeoCoordinates](https://schema.org/GeoCoordinates)
   -  Optional



# Process

Describes a given process within a company
-  `id`: Process identifier
   -  Attribute type: **Property**. 
   -  Required
-  `name`: Process designation
   -  Attribute type: **Property**. [name](https://schema.org/name)
   -  Optional
-  `location`: Process's geographic location (latitude and longitude)
   -  Attribute type: **Property**. [GeoCoordinates](https://schema.org/GeoCoordinates)
   -  Optional



# Asset

Describes an asset within a process
-  `id`: Asset Identifier
   -  Attribute type: **Property**. 
   -  Required
-  `name`: Asset designation
   -  Attribute type: **Property**. [name](https://schema.org/name)
   -  Required
-  `location`: Asset's geographic location (latitude and longitude)
   -  Attribute type: **Property**. [GeoCoordinates](https://schema.org/GeoCoordinates)
   -  Optional



# Node

Describes a given node within an asset
-  `id`: Measurement node identifier
   -  Attribute type: **Property**. 
   -  Optional
-  `category`: Define node category * `Automatic` - Measures delivered automatically by an IoT device * `Manual` - Measures introduced by a human operator * `Both` - This node have measures that are introduced by an IoT device and a human. One of : `Automatic`, `Manual`, `Both`.
   -  Attribute type: **Property**. [category](https://schema.org/category)
   -  Optional
-  `manual`: Human Operator Description
   -  Attribute type: **Property**. [Person](https://schema.org/Person)
   -  Optional
-  `automatic`: IoT device description
   -  Attribute type: **Property**. 
   -  Optional
-  `location`: Node's geographic location (latitude and longitude)
   -  Attribute type: **Property**. [GeoCoordinates](https://schema.org/GeoCoordinates)
   -  Optional



## Examples

### OK


