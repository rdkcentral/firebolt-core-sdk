# Firebolt Requirements

Document Status: Working Draft

See [Firebolt Requirements Governance](../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Jeremy LaCivita            | Comcast            |

## 1. Overview
All of the documents in this `/requirements/` directory comprise the collected set of requirements for this Firebolt version.

This document covers the Firebolt Specification JSON, [./firebolt-specification.json](./firebolt-specification.json), which is a JSON document outlining all Firebolt Capabilities and whether they MUST, SHOULD, or COULD be supported.

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt) and should include the following summary in the Overview section:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Capabilities](#3-capabilities)
  - [3.1. Capability Level](#31-capability-level)
    - [3.1.1. Should vs Could](#311-should-vs-could)
    - [3.1.2. Supported Capability](#312-supported-capability)

## 3. Capabilities
All Firebolt APIs are assigned a capability by either using it, managing it, or providing it.

See [Capabilities](./general/capabilities/capabilities.md) for more info.

### 3.1. Capability Level
In the Firebolt Specification JSON, every capability is given a `level` of either:

- `"must"`
- `"should"`
- `"could"`

A capability with the level set to `"must"` **MUST** be supported or the implementation in question is not a certified Firebolt implementation.

A capability with the level set to `"should"` **SHOULD** be supported, especially if the implementation supports similar requirements in a non-Firebolt interface.

A capability with the level set to `"could"` **COULD** be supported at the implementations discretion.

#### 3.1.1. Should vs Could
This section is non-normative and does not denote any requiements.

"Should" means that not supporting a capability has a detremental impact on a Firebolt platform, and care should be taken when deciding not to support a `"should"` capability.

For example, a capability supporting HDMI outputs would likely be assigned a level of `"should"`, since most STB devices have HDMI outputs, while most TV devices do not.

If a capability has a level of `"should"` and the device exposes the functionality in question through hardware or software, then it should either be treated as a `"must"` or a really good reason should exist for why it was not implemented.

If a device has HDMI output ports, then it probably should implement this capability. While a device w/out HDMI output ports does not need to.

"Could" means that this API is truly optional, for example a capability to expose the postal code of the device might be assigned a `level` of `"could"` since Firebolt platforms can justifiably opt not to support this.

#### 3.1.2. Supported Capability
A supported capability **MUST** have all of its `x-uses` APIs surfaced, supported, and passing Firebolt Compliance tests.

A supported capability **MUST** have all of its `x-provides` APIs surfaced, supported, and passing Firebolt Compliance tests.

A supported capability **MUST** either:

> have all of its `x-manages` APIs surfaced, supported, and passing Firebolt Compliance tests.
>
> **OR**
>
> have a Firebolt Certification translation layer that translates all of its `x-manages` APIs into local, non-firebolt APIs so that certification can run.
