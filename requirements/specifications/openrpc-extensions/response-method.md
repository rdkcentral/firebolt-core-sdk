# Response Method Binding

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Sathish Kirupakaran         | Comcast            |
| Jeremy LaCivita | Comcast | 
| Kevin Pearson | Comcast |

## 1. Overview

A Response Method is an RPC method that is attached to an RPC result by
the SDK for convenience. This allows for results that represent their
own focused APIs. For example:

```javascript
const pet = House.getPet()

pet.walk()
```

In the example above, pet.walk() is an RPC method that takes a pet
object as a parameter. Calling pet.walk() via the Response Method syntax
allows contextual APIs to be called with simpler method signatures.
These methods may or may not be hidden via the rpc-only tag to avoid
Apps calling them without valid parameters, if desired.

This document describes an OpenRPC pattern and JavaScript code
generation for a Firebolt method template that returns results that
contain these type of methods.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Response Methods Use Cases](#3-response-methods-use-cases)
  - [3.1. Array Example](#31-array-example)
- [4. Response Methods API](#4-response-methods-api)
  - [4.1. JSON-RPC API](#41-json-rpc-api)
  - [4.2. JavaScript API](#42-javascript-api)

## 3. Response Methods Use Cases

Response methods may be added to any top-level object result or to all
top-level objects in an array result. The example above covers top-level
objects and an array example is in the following section.

Response Methods **MUST** be at the top level of the response object or
at the top level of all of the objects in the response array. Response
Methods are not supported in nested objects. Response Methods are not
supported as the result of an RPC method itself, i.e., an RPC method
cannot just return a Response Method without an object wrapper.

Response Methods **MUST** point to an RPC method with a compatible
signature (see below).

### 3.1. Array Example

```javascript
const pets = House.getPets()

pets.forEach( pet => pet.walk() )
```

In this example, each pet in the getPets() array has the walk method.

## 4. Response Methods API

The section describes the RPC and JavaScript APIs.

### 4.1. JSON-RPC API

For a method response to contain Response Methods, it **MUST** use the
x-method extension attribute on a property.

```json
{
    "name": "getPet",
    "params": [
    ],
    "result": {
        "schema": {
            "type": "object",
            "properties": {
                "name": {
                    "type": "string"
                },
                "walk": {
                    "type": "null",
                    "x-method": "House.walkPet",
                    "x-this-param": "pet"
                }
            }
        }
    }
}
```

When the x-method attribute is used within an OpenRPC method result
schema, the result schema **MUST** be an object or an array. For objects
the attribute **MUST** be on one of the top-level properties. For arrays
the attribute **MUST** be on one of the top level properties of the
items schema.

Properties flagged with the x-method attribute MUST be of type: "null"
and have no other attributes except for title, description, and
\$comment. This is to avoid duplication / contradiction of the
referenced RPC method.

The x-method value **MUST** be an OpenRPC method within the current
module, and be fully qualified, in case this requirement is ever
relaxed, e.g. House.walkPet, not just walkPet.

When the x-method attribute is used, the following optional extension
attributes may be used as well:

| Extension attribute | Type            | Description                                                                                       |
|------------------|-------------|-----------------------------------------|
| x-this-param        | string          | Parameter name to assign the value of the object to when calling the x-method RPC method          |
| x-additional-params | array<string> | Ordered mapping of parameter names for additional parameters. *Can we just grab from the method?* |

Method results that have properties containing the x-method attribute
will have JavaScript bindings created to insert the methods when using
the SDK. No RPC methods are generated automatically. the RPC method
targeted by x-method **MUST** exist in the module source.

### 4.2. JavaScript API

Using the simple example from above:

```javascript
const pet = House.getPet()

pet.walk()
```

The first line would result in the following RPC call:

```json
{
    "id": 1,
    "jsonrpc": "2.0",
    "method": "house.getPet",
    "params": []
}
```

And the response might look like:

```json
{
    "id": 1,
    "jsonrpc": "2.0",
    "result": {
        "name": "Fido",
        "type": "dog"
    ]
}
```

At this point, the SDK would decorate the response to include the walk()
method, something like:

```javascript
json.result['walk'] = (pet) => {
    return Transport.send('house', 'walkPet', { pet })
}
```

Note that the Response Method, walk(), also returns a Promise, since it
calls another Firebolt RPC method.

Response Methods MUST support additional parameters as well. For
example, if the walkPet() method had a required parameter called
distance, in addition to pet, then the generated method would look
something like:

```javascript
json.result['walk'] = (pet, distance) => {
    return Transport.send('house', 'walkPet', { pet, distance })
}
```

The order of the parameters in the House.walkPet method **MUST** be
respected when generating Response Methods. If walkPet had pet as the
second parameter, then pet.walk() would be generated like this:


```javascript
json.result['walk'] = (distance, pet) => {
    return Transport.send('house', 'walkPet', { pet, distance })
}
```

When a Response Method is called, it simply calls the RPC method w/ the
main object as the parameter denoted by x-this-param.
