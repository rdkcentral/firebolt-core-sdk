# Program Entities

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor     | Organization |
| --------------- | ------------ |
| Seth Kelly      | Comcast      |
| Jeremy LaCivita | Comcast      |

## 1. Overview
TBD... 

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL 
NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT 
RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be 
interpreted as described in [BCP 
14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and 
only when, they appear in all capitals, as shown here. 

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Program Entities](#3-program-entities)
  - [3.1. Optional TV Entity Properties](#31-optional-tv-entity-properties)


## 3. Program Entities
Every Program Entity **MUST** be an [Entity](./index.md#3-entities). 

Every Program Entity **MUST** have a `const` property named `entityType`, which 
**MUST** have the value `"program"`. 

Every Program Entity **MUST** have a `string` property named `programType`, 
whose value **MUST** be one of: 

 - `"movie"`
 - `"episode"`
 - `"season"`
 - `"series"`
 - `"other"`
 - `"preview"`
 - `"extra"`
 - `"concert"`
 - `"sportingEvent"`
 - `"advertisement"`
 - `"musicVideo"`
 - `"minisode"`

An example Program Entity: 

```json
{
    "entityType": "program",
    "programType": "movie",
    "entityId": "entity/abc"
}
``` 

Another example Entity: 

```json
{
    "entityType": "program",
    "programType": "episode",
    "entityId": "entity/xyz"
}
``` 

### 3.1. Optional TV Entity Properties
A Program Entity **MAY** have a `string` property named `seasonId` if its 
programType is `episode`, otherwise the entity **MUST NOT** have this property. 

A Program Entity **MAY** have a `string` property named `seriesId` if its 
programType is either `episode` or `season`, otherwise the entity **MUST NOT** 
have this property. 

An example TV Program Entity: 

```json
{
    "entityType": "program",
    "programType": "episode",
    "entityId": "entity/def",
    "seriesId": "entity/hij",
    "seasonId": "entity/klm"
}
``` 

Another example TV Program Entity: 

```json
{
    "entityType": "program",
    "programType": "season",
    "entityId": "entity/klm",
    "seriesId": "entity/hij"
}
``` 
