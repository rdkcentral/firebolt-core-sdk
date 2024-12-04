# Music Entities

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor     | Organization |
| --------------- | ------------ |
| Jeremy LaCivita | Comcast      |
| Liz Sheffield   | Comcast      |

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
- [3. Music Entities](#3-music-entities)
  - [3.1. Optional Music Entity Properties](#31-optional-music-entity-properties)


## 3. Music Entities
Every Music Entity **MUST** be an [Entity](./index.md#3-entities). 

Every Music Entity **MUST** have a `const` property named `entityType`, which 
**MUST** have the value `"music"`. 

Every Music Entity **MUST** have a `string` property named `musicType`, whose 
value **MUST** be one of: 

 - `"song"`
 - `"album"`

An example Music Entity: 

```json
{
    "entityType": "music",
    "musicType": "song",
    "entityId": "song/xyz"
}
``` 

Another example Music Entity: 

```json
{
    "entityType": "music",
    "musicType": "album",
    "entityId": "album/xyz"
}
``` 

### 3.1. Optional Music Entity Properties
A Music Entity **MAY** have a `string` property named `albumId` if its 
musicType is `song`, otherwise the entity **MUST NOT** have this property. 

An example Music Entity: 

```json
{
    "entityType": "music",
    "musicType": "song",
    "entityId": "song/xyz",
    "albumId": "album/xyz"
}
``` 
