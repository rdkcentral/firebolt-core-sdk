# Channel Entities

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor     | Organization |
| --------------- | ------------ |
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
- [3. Channel Entities](#3-channel-entities)


## 3. Channel Entities
Every Channel Entity **MUST** be an [Entity](./index.md#3-entities). 

Every Channel Entity **MUST** have a `const` property named `entityType`, which 
**MUST** have the value `"channel"`. 

Every Channel Entity **MUST** have a `string` property named `channelType`, 
whose value **MUST** be one of: 

 - `"streaming"`
 - `"broadcast"`

An example Channel Entity: 

```json
{
    "entityType": "channel",
    "channelType": "streaming",
    "entityId": "streaming/xyz"
}
``` 

Another example Channel Entity: 

```json
{
    "entityType": "channel",
    "channelType": "broadcast",
    "entityId": "broadcast/xyz"
}
``` 
