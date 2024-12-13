# Device Information

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Andrew Bennett  | Sky            |
| Piotr Kobzda    | Liberty        |
| Jeremy LaCivita | Comcast        |
| Farhan Mahmood  | Liberty        |
| Jan Pedersen    | Sky            |

## 1. Overview
This document outlines the requirements for ontological, intrinsic, and product-related device indentification APIs.

**TODO**: add capabilities to all APIs

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Device Identifiers](#3-device-identifiers)
  - [3.1. Device Identifier](#31-device-identifier)
  - [3.2. Anonymized Device Identifier](#32-anonymized-device-identifier)
  - [3.3. Device Name](#33-device-name)
- [4. Versions](#4-versions)
  - [4.1. Platform Version](#41-platform-version)
  - [4.2. Firmware Version](#42-firmware-version)
  - [4.3. Debugging Info](#43-debugging-info)
- [5. Device Classification](#5-device-classification)
  - [5.1. Type](#51-type)
  - [5.2. Class](#52-class)
  - [5.3. Make](#53-make)
  - [5.4. Model](#54-model)
  - [5.5. Serial Number](#55-serial-number)
- [6. Device Proposition](#6-device-proposition)
  - [6.1. Distributor](#61-distributor)
  - [6.2. Partner](#62-partner)
  - [6.3. Propositions](#63-propositions)
- [7. Cuts](#7-cuts)
- [8. Refactored into to other modules](#8-refactored-into-to-other-modules)
  - [8.1. MediaInfo](#81-mediainfo)
  - [8.2. HDMI](#82-hdmi)
  - [8.3. Network](#83-network)
  - [8.4. Analog Output](#84-analog-output)
  - [8.5. Manage SDK (TBD)](#85-manage-sdk-tbd)

## 3. Device Identifiers

### 3.1. Device Identifier
The Device module **MUST** expose a read-only, clear-text unique identifier of the device via the `Device.id` method.

This API will likely only be permitted to fisrt-party apps and **MUST** only be surfaced in the Manage SDK.

The value of this **MUST** be unique within a distributor.

This API requires `use` access to the `xrn:firebolt:capability:device:identification` capability.

**NOTE**: we probably need a registry of Firebolt distributors to avoid collisions.

### 3.2. Anonymized Device Identifier
The Device module **MUST** expose a read-only, anonymized device identifier that is consistent across launches of the same app via the `Device.uid` method.

The value of this **MUST** be unique within a distributor and per app.

The anonymized device identifier **MUST NOT** be trackable across apps.

The anonymized device identifiers **MUST** be resettable for all apps at once via the `Device.resetIdentifiers()` method.

The anonymized device identifier **MUST** be an MD5 hash of:

- `Device.distributor()`
- `Device.id()`
- curent app id
- the timestamp of when `Device.resetIdentifiers()` was last called, or the Epoch

**TODO**: What is the use case? if it's just Advertising, then we should cut this.
**NOTE**: Potentially connected to user opts out of personalized recommendations

### 3.3. Device Name
The Device module **MUST** expose a read/write/notification property of the user preferred name of the device via the `Device.name` method.

## 4. Versions

### 4.1. Platform Version
The Device module **MUST** expose the highest supported Firebolt API version as a `SemanticVersion` object via the `Device.version()` method.

A `SemanticVersion` is structured as follows:

```typescript
type SemanticVersion = {
    major: number;
    minor: number;
    patch: number;
    readable: string;
}
```

**NOTE**: The SDK version is moved to a statically generated `SDK.version` method and does not involve an RPC call:

```typescript
import { SDK } from '@firebolt-js/sdk'

console.log(SDK.version())
```

### 4.2. Firmware Version
The Device module **MUST** expose the current firmware version as a `string` via the `Device.firmware()` method.

### 4.3. Debugging Info
The Device module **MUST** expose a free-form debugging `string` via the `Device.debugInfo()` method.

## 5. Device Classification

### 5.1. Type
The Device module **MUST** expose the read-only type of device, e.g. IPSTB, via the `Device.type` method.

The `type` method **MUST** return one of:

- `STB`
- `TV`

### 5.2. Class
Some sort of `string` hardware vendor profiling of the device, e.g. QUALM vs IP... need more examples

- `QUALM``
- `IP`

### 5.3. Make
The Device module **MUST** expose the read-only manufacturer of the device, e.g. "Raspberry Pi, ltd", via the `Device.make` method.

**NOTE**: Definitely NOT an enum, but, do we want this value to be consistent across distributors? Do we need a registry?

### 5.4. Model
The Device module **MUST** expose the model number of the device, e.g. "Raspberry Pi 400", via the `Device.model` method.

The Device model **SHOULD NOT** include the make.

### 5.5. Serial Number
The Device module **MUST** expose the read-only serial number of the device via the `Device.serialNumber` method.

This API will likely only be permitted to fisrt-party apps and **MUST** only be surfaced in the Manage SDK.

The value of this **MUST** be unique within a make and model, even across distributors.

## 6. Device Proposition

### 6.1. Distributor
The Device module **MUST** expose the read-only distributor of the device, e.g. "RDK Management" via the `Device.distributor` method.

**NOTE**: we probably need a registry of Firebolt distributors to avoid collisions.
**TODO**: Confirm RDK-M distributor name.

### 6.2. Partner
The Device module **MUST** expose the read-only distribution partner of the device, e.g. "RDK Demos".

The distribution partner is a way to have one or more sub-divisions within a distributor.

### 6.3. Propositions
The Device module **MUST** expose a list of product propositions that are currently enabled or that the device is currently entitled to surface.

**TODO**: need examples.

## 7. Cuts

- Device.sku
- Device.platform

## 8. Refactored into to other modules
**NOTE**: this section will go away once reviewed.

### 8.1. MediaInfo

- Device.audio
- Device.hdr
- Device.screenResolution
- Device.videoResolution
  
### 8.2. HDMI

- Device.hdcp

### 8.3. Network

- Device.network

### 8.4. Analog Output

- TBD...

### 8.5. Manage SDK (TBD)

- Device.provision
  