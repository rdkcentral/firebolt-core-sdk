# Syndication SDK

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Jeremy LaCivita | Comcast        |
| Peter Yu        | Comcast        |

## 1. Overview
This document outlines the requirements for ontological, intrinsic, and product-related device indentification APIs.

**TODO**: add capabilities to all APIs

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Ontology](#3-ontology)
  - [3.1. OS Class](#31-os-class)
  - [3.2. Leased](#32-leased)
  - [3.3. Experience](#33-experience)
  - [3.4. Account Type](#34-account-type)
  - [3.5. Account Sub Type](#35-account-sub-type)
  - [3.6. Programmer](#36-programmer)
  - [3.7. Retailer](#37-retailer)

## 3. Ontology
The Syndication Extension SDK **MUST** expose an `Ontology` module to contain the APIs outlined below.

### 3.1. OS Class
The `Ontology` module of the Syndication Extension SDK **MUST** have a string `osClass` property that returns what software and bootstrap configuration needs to be loaded on the device for a given operator.

This property **MUST** be readable by any app with `use` access to the `xrn:firebolt:capability:syndication:ontology` capability.

This property **MUST** be read/write and have a setter available to any app with `manage` access to the `xrn:firebolt:capability:syndication:ontology` capability.

The value **SHOULD** be set during device activation by a 1st party setup experience.

Examples values:

- `entos-rdk-residential`
- `entos-rdk-commercial`
- `skyq-rdk`
- `xre-rdk`
- `flex-rdk`

### 3.2. Leased
The `Ontology` module of the Syndication Extension SDK **MUST** have a boolean `leased` property that returns whether or not the device is leased by the customer (true) or owned (false).

This property **MUST** be readable by any app with `use` access to the `xrn:firebolt:capability:syndication:ontology` capability.

This property **MUST** be read/write and have a setter available to any app with `manage` access to the `xrn:firebolt:capability:syndication:ontology` capability.

The value **SHOULD** be set during device activation by a 1st party setup experience.

### 3.3. Experience
The `Ontology` module of the Syndication Extension SDK **MUST** have a string `experienceAppId` property that returns the appId of the primary aggregated experience app, aka "launcher", aka EPG, installed on this device.

This property **MUST** be readable by any app with `use` access to the `xrn:firebolt:capability:syndication:ontology` capability.

This property **MUST** be read/write and have a setter available to any app with `manage` access to the `xrn:firebolt:capability:syndication:ontology` capability.

The value **SHOULD** be set during device activation by a 1st party setup experience.

**TODO**: is app id okay here? what if a Firebolt app is using this API and is running on a different distribution platform w/ different app ids?

### 3.4. Account Type
The `Ontology` module of the Syndication Extension SDK **MUST** have a string `accountType` property that returns the type of account that is active on this device, e.g. `"residential"` or `"business"`.

This property **MUST** be read only by any app with `use` access to the `xrn:firebolt:capability:syndication:ontology` capability.

The value of this property **MUST** be configurable as a pass-through provider and may be provided by an App, a middleware component, or a cloud REST API.

See [Cloud Pass-through Providers](#) for more info.

### 3.5. Account Sub Type
The `Ontology` module of the Syndication Extension SDK **MUST** have a string `accountSubType` property that returns the type of account that is active on this device, e.g. `"hospitality"` or `"university"`.

This property **MUST** be read only by any app with `use` access to the `xrn:firebolt:capability:syndication:ontology` capability.

The value of this property **MUST** be configurable as a pass-through provider and may be provided by an App, a middleware component, or a cloud REST API.

See [Cloud Pass-through Providers](#) for more info.

### 3.6. Programmer
The `Ontology` module of the Syndication Extension SDK **MUST** have a string `programmerId` property that returns the ID of the partner that is providing programming to the primary aggregated experience.

This property **MUST** be readable by any app with `use` access to the `xrn:firebolt:capability:syndication:ontology` capability.

This property **MUST** be read/write and have a setter available to any app with `manage` access to the `xrn:firebolt:capability:syndication:ontology` capability.

The value **SHOULD** be set during device activation by a 1st party setup experience.

**TODO**: What is the scope of these ids?

### 3.7. Retailer
The `Ontology` module of the Syndication Extension SDK **MUST** have a string `retailerId` property that returns the ID of the partner that initially retailed the device.

This property **MUST** be readable by any app with `use` access to the `xrn:firebolt:capability:syndication:ontology` capability.

This property **MUST** be read/write and have a setter available to any app with `manage` access to the `xrn:firebolt:capability:syndication:ontology` capability.

The value **SHOULD** be set during device activation by a 1st party setup experience.

**TODO**: What is the scope of these ids?
