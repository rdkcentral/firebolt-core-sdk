# Requirements Style Guide

Document Status: Working Draft

See [Firebolt Requirements Governance](./governance.md) for more info.

**NOTE**: Update this link based on your directory depth ^^

| Contributor | Organization |
| ----------- | ------------ |
| TBD         | TBD          |

## 1. Overview
This document is both a style guide *and* a template for Firebolt Requirements Specifications.

The Overview section is a non-normative or informative introduction to the contents and subject matter of the document. This is included to introduce the reader to the overall problem, solution, and scope. No formal requirements will be included here, as it will often be skipped by readers that are already familiar with the document.

Overviews can be as long or short as appropriate for the subject matter, and should have a target audience ranging from technical product managers to engineering teams that may be testing, implementing, or integrating with the functionality described in the document.

The overview must contain the following towards the end:

Requirements documents are written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt) and should include the following summary in the Overview section:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Specification Style Requirements](#3-specification-style-requirements)
  - [3.1. General Style Requirements](#31-general-style-requirements)
  - [3.2. Firebolt Style Requirements](#32-firebolt-style-requirements)
  - [3.3. Firebolt Method Templates](#33-firebolt-method-templates)
- [4. Example Section](#4-example-section)
  - [4.1. Example Feature](#41-example-feature)

**NOTE**: This is a simple table of contents. It should include links to all headers in the document, except for the top-level header (i.e. `# Title`). It is recommended to use a Markdown plugin to generate this based on headers ranging from level two to level six. Delete this note from your actual spec :)

## 3. Specification Style Requirements
Firebolt uses method templates in order to code-generate consistent APIs. For example, methods with the `"property"` tag only need to have the `getter` editorially defined. The Firebolt OpenRPC tools will auto-generate the `setter` and `subscriber` as OpenRPC methods with matching types. Additionally, the Firebolt OpenRPC tools will then code-generate the getter, setter, and subscriber as APIs in various languages using templates.

This enables both consistent APIs (all properties have a recongnizable pattern) and consistent SDK implementation, which reduces the code that needs to be tested.

### 3.1. General Style Requirements
All headers **MUST** be numbered, and have the parent header as the prefix, separated with '.'

Module and method names, as well as constants **MUST** be in monospace font, e.g. the `Foo` module **MUST** have a `bar` method that returns `true`. Specs should use JavaScript notation for any code examples if the spec is not targeting another specific language binding, e.g. a spec about Event listeners in C++ would use C++ syntax.

String constants and values **MUST** be wrapped in quotes for clarity, e.g. `"Hello World"`.

### 3.2. Firebolt Style Requirements
All Firebolt APIs exposed for building Firebolt Apps **MUST** be exposed as JSON-RPC methods on a WebSocket accessible to the device, typically running locally.

Parameters and return values for all APIs **MUST** be described using JSON-Schema schemas.

Methods **MUST** be grouped into “modules” or “packages” of functionality.

The JSON-RPC method name of any method **MUST** follow the template:

```
<module>.<method>
```

e.g.

```
lifecycle.ready
```

JSON-RPC method names are case sensitive.

Methods **MUST** have at least one capability used, managed, or provided by the method.

Methods **MAY** require the use of more than one capability, but this means that the app must have permission to all of them. In order to enable App permissions to be evaluated in an isolated layer, separate from the method implementation itself, a Firebolt method **MUST NOT** be specified to add or remove fields based on the caller's permissions.

The words used in method and parameter names **SHOULD** be used as consistently as possible across the Firebolt API surface. See the [Firebolt API Glossary](./glossary.md) for words that Firebolt uses and how they are used.

### 3.3. Firebolt Method Templates
Methods **SHOULD** consider using the existing Firebolt method tags, in order to have a level of consistency across APIs.

If a Firebolt method is specified such that it requires a non-existant template, then a new Requirements Specification **MUST** be written and referenced by the specification that inspired it. Method templates **MUST** be designed with re-use in mind.

## 4. Example Section
A section describes group of closely related features. Many specifications have only one section, however, more complicated specifications may have many. The first paragraph of a section is typically a non-normative introduction to that section, and therefor does not contain any formal requirements.

### 4.1. Example Feature
Each feature under a section will have it's own heading. Non-normative introductions to features are not typically needed, as the reader is ready to get into requirements at this point. It is recommended that all Feature headings under each Section contain only sentences or short paragraphs with formal requirements, e.g. MUST, SHOULD, MAY, MUST NOT, SHOULD NOT, etc. These sentences should be separated by blank lines for readability, e.g.:

This requirement **MUST** be satisifed.

This requirement **SHOULD** be satisfied.

This requirement **MUST** be satisfied. The requirement **MUST** be satisifed in this particular way.
