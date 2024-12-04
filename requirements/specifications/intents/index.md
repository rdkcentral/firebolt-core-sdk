# Intents

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor     | Organization |
| --------------- | ------------ |
| Jeremy LaCivita | Comcast      |
| Simon Grist     | Sky          |


## 1. Overview
Offen times an end-user has a specific intention that needs to be communicated 
to an app by the platform. A common reason for this is that a platform may have 
a voice interface, and an end-user has given an instruction that needs to be 
carried out by a specific app, e.g. a deep link to content w/in that app. 

Other use cases include editorially placed calls to action in the main user 
experience, developer tools, and app-to-app communication brokered by Firebolt 
intents. 

All intents have an `action`, and `context` property, and many intents have an 
additional `data` property. 

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Intent Action](#3-intent-action)
- [4. Intent Context](#4-intent-context)
- [5. Intent Data](#5-intent-data)
- [6. Intent Message](#6-intent-message)
  - [6.1. App Intent Message](#61-app-intent-message)
  - [6.2. Platform Intent Message](#62-platform-intent-message)
  - [6.3. Intent Message Type](#63-intent-message-type)
  - [6.4. Intent Message Metadata](#64-intent-message-metadata)
- [7. Intent Types](#7-intent-types)

## 3. Intent Action
The intent `action` denotes what type of intent it is. 

All intents **MUST** have an `action` `string` property denoting the type of intent. 

See the various [Intent Types](#intent-types) below for values. 

## 4. Intent Context

The intent `context` provides information on where the intent orginated from. 
All intents **MUST** have a `context` property, which is an object. 

The `context` object **MUST** have a `source` string property with one of the 
following values: 

 | Value       | Description                                                                         |
 |-------------|-------------------------------------------------------------------------------------|
 | `voice`     | This intent originated from a voice service                                         |
 | `editorial` | This intent originated from an editorial CMS                                        |
 | `api`       | This intent originated from some other API on the platform, e.g. `Discovery.launch` |

The `context` object **MAY** have a `campaign` string property, which can have 
any string value. This property denotes an editorial campaign. 

## 5. Intent Data
If an intent has any additional data, it **MUST** be in the `data` property. 

## 6. Intent Message
When an intent is sent to a Firebolt device from some other system, e.g. a cloud voice service, it **MUST** be wrapped in an `IntentMessage` object so that it can be properly routed after transport.

An intent message **MUST** have an `intent` object property that is the intent being passed.

An example intent message:

```json
{
    "type": "xrn:firebolt:intent:app:launch",
    "appId": "Netflix",
    "intent": {
        "action": "launch",
        "context": {
            "source": "voice"
        }
    },
    "metadata": {
        "foo": "bar"
    }
}
```

### 6.1. App Intent Message
If an intent is targeting a specific app, then the intent message **MUST** have an `appId` string property with the appId of the targeted app.

### 6.2. Platform Intent Message
If an intent messagage does not have an `appId` property, then it **MUST** be targeting the device itself, e.g. a `power` intent to turn off the device.

### 6.3. Intent Message Type
An intent message **MUST** have a `type` string property for categorizing the intent.

The type property **MUST** match the regular expression:

```regex
^xrn:firebolt:intent:(app|platform):[a-zA-Z]+$
```

App Intent Messages **MUST** have the fourth section set to `app`.

Platform Intent Messages **MUST** have the fourth section set to `platform`

All Intent Messages **MUST** have the fifth section set to the same value as `intent.action`.

Platforms may use this to route different types of intents to different subsystems without having to understand the internal structure of Firebolt intent objects.

### 6.4. Intent Message Metadata
An intent message **MAY** have a `metadata` object property for adding distributor-specific metadata for logging or analytics. The values in `metadata` **MUST NOT** impact how the device interprets the intent.

## 7. Intent Types

- [Play](./play.md)
- [Tune](./tune.md)
- [Basic Navigation](./navigation.md)
  