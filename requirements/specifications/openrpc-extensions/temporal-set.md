# Temporal Set RPC Method

Document status: Proposed Spec

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Mike Fine            | Comcast            |
| Jeremy LaCivita | Comcast |
| Kevin Pearson | Comcast |

## 1. Overview

A Temporal Set is an Array-like data structure that only contains unique
items, i.e., a \"set,\" and has its contents change over an indefinite
length of time, i.e., \"temporal.\"

This document describes an OpenRPC pattern and JavaScript code
generation for a Firebolt method template that returns this type of
object.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Temporal Set Requirements](#3-temporal-set-requirements)
  - [3.1. Live-list of matches](#31-live-list-of-matches)
  - [3.2. First match](#32-first-match)
  - [3.3. Background scan](#33-background-scan)
- [4. Temporal Set API](#4-temporal-set-api)
  - [4.1. JSON-RPC API](#41-json-rpc-api)
    - [4.1.1. onItemAvailable](#411-onitemavailable)
    - [4.1.2. onItemUnavailable](#412-onitemunavailable)
    - [4.1.3. stopMethodName](#413-stopmethodname)
  - [4.2. JavaScript API](#42-javascript-api)

## 3. Temporal Set Requirements

There are many common use cases that involve finding a specific service
or device, where the items be found could show up at any point in an
unknown future. This could be things like WiFi networks, Bluetooth
accessories, or DNS-SD-based developer tools.

Apps tend to fall into a handful of use cases which Firebolt APIs should
strive to enable.

In the following use cases, the terms \"matching\" and \"item\" are used
to describe the \"things\" being found, e.g. WiFi access points,
Bluetooth devices with the headset profile, etc. How this matching
occurs is outside the scope of this document.

### 3.1. Live-list of matches

Displaying a list of all matching items and keeping it up to date for an
indefinite time is probably the most common use case for this type of
API. A frequent example of this is a WiFi picker UX.

To make this UX as simple to implement as possible, the Temporal Set API
**MUST** ensure:

> Duplicate matched items **MUST NOT** be passed to the App
>
> AND
>
> The app **MUST** be informed when matched items become unavailable or
> are no longer part of the temporal set
>
> AND
>
> The app **MUST** be informed when matched items become available or
> are now part of the temporal set
>
> AND
>
> The app **MUST** be able to communicate that it no longer cares about
> this temporal set

### 3.2. First match

Finding a specific item, with no UX needed is another common use case. A
common example is pairing a known device with specific details that will
likely result in one match, e.g., a previously paired remote, or a
remote with a specific make/model.

To make this user journey as simple to implement as possible, the
Temporal Set API **MUST** ensure:

> There is a way to call the API that uses the same semantics, e.g.,
> method name, and a simpler method signature to denote the \"first
> match\" use case.

### 3.3. Background scan

Scanning for matches in the background is another use-case that could
come up. An example of this is to scan for a previously paired phone and
wake up the TV when the phone\'s Bluetooth signal is in proximity.

This use case can likely be fulfilled by an API that serves the previous
use cases but is listed here for completeness.

## 4. Temporal Set API

The section describes the RPC and JavaScript APIs.

### 4.1. JSON-RPC API

For a method to leverage the Temporal Set template, it MUST use thetemporal-set tag.


```json
{
  "name": "<methodName>",
  "tags": [
    {
      "name": "temporal-set"
    }
  ],
  "params": [
    {
      "name": "query",
      "schema": {
        "type": "string"
      }
    }
  ],
  "result": {
    "schema": {
      "type": "array",
      "items": {
        "title": "Item",
        "type": number
      }
    }
  }
}
```

When this tag is used on an OpenRPC method schema, the result schema
**MUST** be an `array`, and the `items` schema defines the schema for an
individual matched item.

The `query` param here is an example. The method may contain any
primitive (string, number, integer, boolean) parameters, or no
parameters. See [Context
Parameters](https://comcastcorp.sharepoint.com/:w:/r/sites/hqppa/Shared%20Documents/Global%20App%20Platform/Firebolt/Requirements/General/APIs/Context%20Parameters.docx?d=w84c3615b348241a4818d65985303e430&csf=1&web=1&e=DIFLdd)
for more info.

The `title` attribute on `result.schema items` **MUST** be present
and denotes the type of items being matched, e.g., \"BluetoothDevice.\"
The title **MAY** be inside of a schema linked via a `$ref`. if it is
not directly on `result.items`.

When this method is called, all matching items that the platform
currently knows about **MUST** be returned without waiting for
additional matches.

Methods with this tag will have three OpenRPC methods generated by the
Firebolt tooling.

#### 4.1.1. onItemAvailable

This is an OpenRPC event with the name including the title of the
original `result.items`. This event fires whenever an *additional,*
matching item is found that was not returned in the original method
array result. It is up to the Firebolt implementation to filter results,
not the SDK.

The `correlationId` parameter maps this listener back to the original
temporal-set API call that started the temporal set scan. The `listen`
parameter is the standard event listener parameter.

```json
{
  "name": "on<Item>Available",
  "tags": [
    {
      "name": "event",
      "x-temporal-set": "<methodName>"
    }
  ],
  "params": {
     {
       "name": "correlationId",
       "schema": {
         "type": ["number", "string"]
       }
     },
     {
       "name": "listen",
       "schema": {
         "type": "boolean"
       }
     }
   },
  "result": {
    "anyOf": [
      {
        "schema": <methodName.result.items>
      },
      {
        "$ref": "http://meta.comcast.com/firebolt/types/#/defintions/ListenReponse"
    ]
  }
}
```

#### 4.1.2. onItemUnavailable

This is an OpenRPC event with the name matching the title of the
original `result.items`. This event fires whenever an item is no longer
\"found.\" Items dispatched from this event should be items that the app
has received either via the initial method call or an `onItemAvailable`
event.

```json
{
  "name": "on<Item>Unavailable",
  ...
}
```

Aside from the `name`, all other aspects of this schema match theonItemAvailable schema.

#### 4.1.3. stopMethodName

This is an OpenRPC method that cancels the current temporal set session.

```json
{
  "name": "stop<MethodName>",
  "params": [
    {
      " correlationId ": {
        "type": ["string", "number"]
      }
    }
  ],
  "result": {
    "type": "void"
  }
}
```

Calling this method ends the session, and no further events with the
current `correlationId` should be dispatched. The `correlationId` is the
id value from the original method call.

Methods may have different additional requirements of what this means.
Discussion of those is out of scope for this document.

### 4.2. JavaScript API

The JavaScript API will leverage the RPC API in two different ways,
depending on whether the app wants the first match, or a live temporal
set.

For the first match, the app would do something like:

```javascript
Module.find("Firebolt Tool", 10000).then(result => {
    console.log("Here's the result")
    console.dir(result)
})
```

The last parameter is an optional timeout value. All context parameters
**MUST** be passed before the timeout.

This code would result in the following RPC calls:

```json
[
  {
    "id": 1,
    "jsonrpc": "2.0",
    "method": "module.find",
    "params": {
      "query": "Firebolt Tool"
    }
  },
  {
    "id": 2,
    "jsonrpc": "2.0",
    "method": "module.onItemAvailable",
    "params": {
      "listen": true,
	"correlationId": 1
    }
  }
]
```

Note that these two calls are batched into a single request to avoid
latency race conditions.

If a match is found, then the responses might look like:

```json
[
  {
    "id": 1,
    "jsonrpc": "2.0",
    "result": [
      "Here's a match!"
    ]
  },
  {
    "id": 2,
    "jsonrpc": "2.0",
    "result": {
      "listening": true
    }
  }
]
```

At this point, the SDK would resolve the promise with the *first*
result, and turn off the listener:

```json
  {
    "id": 2,
    "jsonrpc": "2.0",
    "method": "module.onItemAvailable",
    "params": {
      "listen": false,
      "correlationId": 1
    }
  }
```

If no item was available immediately, then the SDK would wait for anonItemAvailble event, and then turn off the listener.

For first-match use cases, once the listener is turned off, the SDK MUST
call the `stop<Method>` API immediately.

Alternately, if the app calls the stop method before any result is
returned, then the listener would be turned off and thestop<Method> RPC API would be called:

```json
  {
    "id": 3,
    "jsonrpc": "2.0",
    "method": "module.stopFind",
    "params": {
      "correlationId": 1
    }
  }
```

The JavaScript code for doing a live temporal set would look like this:

```javascript
Module.find("Firebolt Tool",
    result => {
        console.log(\'this item shows up\')
        console.dir(result)
    },
    result => {
        console.log(\'this item goes away\')
        console.dir(result)
    }
).then( process => {
    setTimeout( () => { process.stop() }, 10000)
})
```

The RPC calls for this flow are similar, with the following additions:

-   the `onItemUnavailble` event is turned on

-   the first callback is called once for *each* item found

-   the second callback is called once for each item removed
