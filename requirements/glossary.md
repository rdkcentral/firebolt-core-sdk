# Glossary

Document Status: Working Draft 
| Contributor     | Organization |
| --------------- | ------------ |
| Jeremy LaCivita | Comcast      |

## 1. Overview

This document describes various terms used as part of Firebolt APIs, e.g. 
method names or parameters, and how they are used by Firebolt, for consistency. 

The terms are this document are commonly used across multiple modules. However, 
new APIs should be deferential to all existing APIs, not just words listed 
here. 

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL 
NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT 
RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be 
interpreted as described in [BCP 
14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and 
only when, they appear in all capitals, as shown here. 
## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Firebolt Terms](#3-firebolt-terms)
  - [3.1. app](#31-app)
  - [3.2. available](#32-available)
  - [3.3. availability](#33-availability)
  - [3.4. capability](#34-capability)
  - [3.5. closed captions](#35-closed-captions)
  - [3.6. content](#36-content)
  - [3.7. entitlement](#37-entitlement)
  - [3.8. granted](#38-granted)
  - [3.9. lifecycle](#39-lifecycle)
  - [3.10. media](#310-media)
  - [3.11. permitted](#311-permitted)
  - [3.12. policy](#312-policy)
  - [3.13. user grant](#313-user-grant)
  - [3.14. supported](#314-supported)

## 3. Firebolt Terms

### 3.1. app

noun. - A Firebolt app. Any component that calls [Firebolt 
APIs](https://github.com/rdkcentral/firebolt-apis), either directly, or by 
running inside of a container that calls Firebolt APIs, is a Firebolt app. 
### 3.2. available

adj. - Used in the context of a [capability](#34-capability) to denote that the 
capability *could* be leveraged now if it is [permitted](#311-permitted) and 
either [granted](#38-granted) or is not gated by a [user 
grant](#313-user-grant). Available capabilities are, by definition, 
[supported](#314-supported). 
### 3.3. availability

noun. - Used in the context of [content](#36-content) to denote that the 
content *could* be consumed if either the device has an 
[entitlement](#37-entitlement) to the content, or the content does not require 
any entitlement. 
### 3.4. capability

noun. - A discrete unit of functionality that a Firebolt device might be able 
to perform. It is granular enough to enable appropriate access controls across 
all Firebolt Apps, but useful enough to be a meaningful functional unit that an 
App might care about. 
### 3.5. closed captions

noun. - Closed Captions are text tracks rendered over or near 
[content](#36-content) with the intention of making the audio track of the 
content more accessible, for example to deaf or hard-of-hearing individuals. 
### 3.6. content

noun. - Content consumed on Firebolt platforms, e.g. video, games, music, etc. 
### 3.7. entitlement

noun. - Used in the context of [content](#36-content) to denote that the device 
or user has acquired the *right* to consume the content. Content may also have 
[availability](#33-availability) requirements for consumption, e.g. a user may 
have pre-orded a piece of content, and therefor have an entitlement to it, that 
becomes available in the future. 
### 3.8. granted

adj. - Used in the context of a [capability](#34-capability) to denote that the 
capability has been granted to an app by the user. Capabilities that are gated 
by [user grant](#313-user-grant) cannot be leveraged by any app w/out being 
granted. 
### 3.9. lifecycle

noun. - Used to describe the life, from being loaded to unloaded, of a Firebolt 
[app](#31-app). The app lifecycle has many states that inform the app how it is 
being percieved and how it should behave. 
### 3.10. media

noun. - [Content](#36-content) that that plays back over time without requiring 
interaction from the user, e.g. video or music. Media must have a start-time, 
or a duration, or both. 
### 3.11. permitted

adj. - Used in the context of a [capability](#34-capability) to denote that the 
capability has been permitted to an app by the distributor of the device. 
### 3.12. policy

noun. - A group of user, device, and/or distributor settings that affect a 
particular domain, e.g. Advertising. 
### 3.13. user grant

noun. - A secure process in which a user of a device grants an app on the 
device access to a capability. 
### 3.14. supported

adj. - Used in the context of a [capability](#34-capability) to denote that the 
capability *could* be leveraged at some point on this device, because the 
distributor offers it as part of this device's feature set. Leveraging a 
capability also requires that it is [available](#32-available), 
[permitted](#311-permitted), and either [granted](#38-granted) or is not gated 
by a [user grant](#313-user-grant). 
