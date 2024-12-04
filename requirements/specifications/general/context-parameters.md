# Context Parameters
Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Jeremy LaCivita            | Comcast            |
| Yuri Pasquali             | Sky |

## 1. Overview

**TODO**: This doc is old and need to be refreshed

Context Parameters are parameters on an RPC method that provide context
for the call via a set of primitive types (string, number, integer,
boolean). This allows for sharing the context parameters across property
getters, setters, and subscribers, as well as filtering which events to
listen for by context.

An example of a property method with context could be:

```javascript
// get a context-driven property (context: appId=hulu)
const huluShare = await Privacy.shareWatchHistory('hulu')
```

```javascript
// set a context-driven property (context: appId=hulu)
Privacy.shareWatchHistory('hulu', false)
```

In the example above, 'hulu' is the context parameter for both the
shareWatchHistory getter and setter.

Context parameters can also be applied to property subscribers, as well
as other, non-property events:

```javascript
// subscribe to a context-driven property
Privacy.shareWatchHistory('hulu', (value) => {
    console.log('hulu value changed to: ' + value)
})

Privacy.listen('shareWatchHistoryChanged', 'hulu', (value) => {
    console.log('hulu value changed to: ' + value)
})
```

For subscribers and events, the context parameters may be omitted, in
which case, all events will be dispatched to the listener:

```javascript
// subscribe to a context-driven property w/out any context (get all of them)

Privacy.shareWatchHistory((appId, value) => {
    console.log(`App '${appId}' value changed to ${value}`)
})

Privacy.listen('shareWatchHistoryChanged', (appId, value) => {
    console.log(`App '${appId}' value changed to: ${value}`)
})
```

Context Parameters **MUST** be of a primitive type, to avoid complex
object-tree filtering.

This document describes an OpenRPC pattern and JavaScript code
generation for a Firebolt method template that uses Context Parameters.

## 2. Table of Contesnts
- [1. Overview](#1-overview)
- [2. Table of Contesnts](#2-table-of-contesnts)
- [3. Context Parameters Use Cases](#3-context-parameters-use-cases)
- [4. Context Parameters API](#4-context-parameters-api)
  - [4.1. JSON-RPC API](#41-json-rpc-api)
    - [4.1.1. Setter RPC generation](#411-setter-rpc-generation)
    - [4.1.2. onChanged RPC generation](#412-onchanged-rpc-generation)
    - [4.1.3. Temporal Set onAvailable / Unavailable RPC generation](#413-temporal-set-onavailable--unavailable-rpc-generation)
    - [4.1.4. Event RPC Decoration](#414-event-rpc-decoration)
  - [4.2. JavaScript API](#42-javascript-api)
    - [4.2.1. Event Listener Signatures](#421-event-listener-signatures)

## 3. Context Parameters Use Cases

How each parameter affects it's corresponding API is out of scope for
this document. See each API spec for details on what each context
parameter does.

Setting a context parameter to null is still setting it to a value. If a
context parameter is passed to the SDK with either a value of null or
undefined, then it **MUST** be explicitly set in the RPC request to the
value null. This is to avoid additional method signature permutations
being required for the SDK.

An effort should be made to sort the context parameters in order of most
usefulness, since not all languages support undefined.

## 4. Context Parameters API

The section describes the RPC and JavaScript APIs.

### 4.1. JSON-RPC API

Simple getters and event listeners don't need any parameters.

If a method is tagged as either a property (any kind) or an event, then
**all** the parameters in the RPC definition **MUST** be context
parameters.

To facilitate this, the listen parameter that all events currently have
will be removed from the source module and inserted into the generated
RPC by the firebolt-openrpc tooling.

If any Context Parameters have a type other than:

-   `string`
-   `boolean`
-   `number`
-   `integer`

Then the RPC method **MUST NOT** pass validation. This is to ensure that
implementing context parameters is not overly complicated.

#### 4.1.1. Setter RPC generation

When generating the setter for a property method, all the Context
Parameters **MUST** be copied to the setter. The context parameters
**MUST** be before the value parameter, which itself **MUST** be last.

#### 4.1.2. on<Property>Changed RPC generation

When generating the on<Property>Changed notification for a property
method, all the Context Parameters **MUST** be copied to the event
parameters. The context parameters **MUST** be before the listen
parameter, which itself **MUST** be last.

#### 4.1.3. Temporal Set on<Item>Available / Unavailable RPC generation

Generated Temporal Set events will treat the entire parameter list from
the original temporal-set method as Context Parameters and copy them to
the event parameters. The context parameters **MUST** be before the
listen parameter, which itself **MUST** be last.

#### 4.1.4. Event RPC Decoration

All RPC methods tagged as event **MUST** have the listen parameter, of
type boolean, automatically added when generating the final RPC. This
parameter will be added at the end of the parameters list.

All RPC methods tagged as event that have context parameters **MUST**
have the result schema wrapped in an object. The original result schema
**MUST** be moved to a property called data. Each of the context
parameters **MUST** be copied to a property called context.

So the following RPC event:

```json
{
    "name": "onContextualEvent",
    "tags": [
        {
            "name": "event"
        }
    ],
    "params": [
        {
            "name": "a",
            "required": true,
            "schema": {
                "type": "boolean"
            }
        },
        {
            "name": "b",
            "required": true,
            "schema": {
                "type": "string"
            }
        },
        {
            "name": "c",
            "required": true,
            "schema": {
                "type": "number"
            }
        }
    ],
    "result": {
        "name": "result",
        "schema": {
            "type": "object",
            "properties": {
                "foo": {
                    "type": "boolean"
                }
            }
        }
    }
}
```

Would have its result transformed to:

```json
{
    "name": "result",
    "schema": {
        "type": "object",
        "properties": {
            "data": {
                "type": "object",
                "properties": {
                    "foo": {
                        "type": "boolean"
                    }
                }
            },
            "context": {
                "type": "object",
                "properties": {
                    "a": {
                        "type": "boolean"
                    },
                    "b": {
                        "type": "string"
                    },
                    "c": {
                        "type": "number"
                    }
                },
                "required": [
                    "a", "b", "c"
                ]
            }
        }
    }
}
```

### 4.2. JavaScript API

TBD

#### 4.2.1. Event Listener Signatures

If any of the context parameters are optional, then a callback signature
must be generated for each left-to-right combination of the parameters.

For example, the method:

```json
{
    "name": "onFoo",
    "tags": [
        {
            "name": "event"
        }
    ],
    "params": [
        {
            "name": "a",
            "required": true,
            "schema": {
                "type": "boolean"
            }
        },
        {
            "name": "b",
            "required": false,
            "schema": {
                "type": "string"
            }
        },
        {
            "name": "c",
            "required": false,
            "schema": {
                "type": "number"
            }
        }
    ]
}
```

Would result in the following method signatures:

```typescript
listen(event: 'foo', a: boolean, callback: (b: string, c: number, data: any) => {})

listen(event: 'foo', a: boolean, b: string, callback: (c: number, data: any) => {})

listen(event: 'foo', a: boolean, b: string, c: number, callback: (data: any) => {})
```

Which allows parameters to be omitted, from right-to-left, and included
as part of the result, instead.

When invoking the callback, the SDK **MUST** pass the data portion of
the result to the data parameter of the callback, and each context
property to the corresponding callback parameter.

This pattern also applies to property subscribers.
