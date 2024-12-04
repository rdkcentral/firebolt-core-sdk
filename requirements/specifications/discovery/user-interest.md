# User Interest

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Eugene Chung            | Comcast            |
| Tim Dibben            | Sky            |
| Mike Horwitz            | Comcast            |
| Jeremy LaCivita            | Comcast            |

## 1. Overview

In additional to traditional discovery APIs such as Watch History and
Watch Next, Firebolt provides a more abstract API that facilitates
impromptu content discovery connections between first-party Aggregated
Experiences and third-party Apps.

The User Interest Capability enables Apps to provide meta-data on
content that the user has expressed an interest in to Aggregated
Experience Apps that have been given access to use this Capability.

This allows for open ended design of Aggregated Experience App features
that present App-specific content to re-engage the user with the content
inside the originating App.

While the functionality and UX is left to the Aggregated Experience App,
typically designed by each Firebolt Distributor, the Firebolt API
enables events to register user interest and pass entity meta-data:

![Diagram Description automatically
generated](../../../requirements/images/specifications/intents/user-interest/media/image1.png)

Which generally enables Aggregated Experiences to present that entity
meta-data in some way that leads to re-launching the original App at a
later point, using a `navigateTo` notification:

![Diagram Description automatically
generated](../../../requirements/images/specifications/intents/user-interest/media/image2.png)

This is just one example of what an Aggregated Experience App might do
with the User Interest API.

Note that this API **SHOULD NOT** be used to implement Watch History or
Watch Next features. These concepts are much more fundamental to
Firebolt and have explicit APIs so that Firebolt Distributors can keep
track of which apps are using them separately.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. User Interest Flows](#3-user-interest-flows)
  - [3.1. User Interest from an in-app UX](#31-user-interest-from-an-in-app-ux)
  - [3.2. User Interest from a platform UX](#32-user-interest-from-a-platform-ux)
    - [User Interest Errors](#user-interest-errors)
  - [3.3. Upstream User Interest Intent](#33-upstream-user-interest-intent)
  - [3.4. User Interest Bulk Updates](#34-user-interest-bulk-updates)
- [4. Core SDK APIs](#4-core-sdk-apis)
  - [4.1. InterestType](#41-interesttype)
  - [4.2. InterestReason](#42-interestreason)
  - [4.3. Discovery.userInterest](#43-discoveryuserinterest)
  - [4.4. Discovery Interest Provider](#44-discovery-interest-provider)
  - [4.5. InterestIntent](#45-interestintent)
- [5. Discovery SDK APIs](#5-discovery-sdk-apis)
  - [5.1. Interest Types](#51-interest-types)
  - [5.2. Content.requestUserInterest](#52-contentrequestuserinterest)
  - [5.3. Content.onUserInterest](#53-contentonuserinterest)


## 3. User Interest Flows
### 3.1. User Interest from an in-app UX

Some Apps will have a built-in user interface for users to express
interest in content from the App. This could be a "Favorite" button,
an in-app "My List" button, etc.

If the App wants to leverage any additional exposure from the device's
Aggregated Experience, it can wire up its own UI to the Firebolt User
Interest API, in addition to any in-app features that it's already
invoking.

By calling the `Discovery.userInterest` method with the relevant entity
meta-data, the device's Aggregated Experience will be notified of the
user's interest in that entity:

```typescript
Discovery.userInterest(type: InterestType, reason: InterestReason, entity: EntityDetails)
```

The `type` parameter denotes the directionality of the interest:

-   `interest`
-   `disinterest`   

The `reason` parameter denotes why or how the user has expressed interest:

| Reason | Description |
| ------ | ----------- |
| `playlist` | Interested in adding to a list |
| `reaction` | Interested in submitting a reaction, e.g. like or dislike |
| `recording` | Interest in scheduling a recording |
| `share` | Interest in sharing the content on social media |

**NOTE**: We can remove some of these (not `playlist`) these are here for now to illustrate the purpose for the reason paramater.

An app **MUST** `provide` the `xrn:firebolt:capability:discovery:interest`
capability in order to call `Discovery.userInterest`.

When this method is called with a valid `EntityDetails`, the platform
**MUST** dispatch a `Content.onUserInterest` notification to all Apps
that have registered for it (typically Aggregated Experience Apps) with
information about the app, interest type, and the entity.

The `Content.onUserInterest` event has a result type of `Interest`:

| property | type | description |
|---------|------|-------------|
| appId   | string | The id of the app that pushed the user interest. |
| type    | `InterestType` | the type of interest. |
| reason  | `InterestReason` | the reason for the interest |
| entity  | `EntityDetails` | The entity the user expressed interest in. |

An Aggregated Experience can register for the `Content.onUserInterest`
notification, and it will receive notifications when an `EntityDetails` is
returned from the active App after a `Discovery.userInterest` call is
fulfilled.

An app **MUST** have permissions to `use` the
`xrn:firebolt:capability:discovery:interest` capability in order to 
listen to the `Content.onUserInterest` notification.

If the result is not a valid entity, i.e. does not match
the [EntityDetails](../entities/) schema, then no `Content.onUserInterest`
notification will be dispatched.

The `Discovery.userInterest` method **SHOULD NOT** be used in place of more
specific Discovery methods, e.g. `Discovery.watchNext` or
`Discovery.watched`. These methods facilitate specific UX flows that may
have separate legal opt-outs for each user.

The `Discovery.userInterest` method **SHOULD NOT** be called unless the user
is activating a UI element in the app, or in a second screen experience
that is communicating with the app, that implies interest of some kind.

### 3.2. User Interest from a platform UX

Firebolt platforms may provide a platform UX, e.g. voice or and RCU, to
express user interest in content from an active App. To facilitate this
Apps will need to be told about the user's expressed interest in their
content.

First, the Aggregated Experience (or some app with this
capability) detects that the user is interested in something. In this
picture the interest is triggered by an RCU button, but how this occurs
is outside the scope of this document. When this happens, the Aggregated
Experience app calls `Content.requestUserInterest()`, which will trigger the
platform to identify the best [Provider Candidate](../openrpc-extensions/app-passthrough-apis.md#5-provider-candidates)
and call that app's `userInterest` method via the Provider RPC method:
`Discovery.onRequestUserInterest`.

![](../../../requirements/images/specifications/intents/user-interest/media/image3.png)

Next, the provider app receives and responds to the request with an 
EntityDetails, which is returned as the result to the pending
`Content.requestUserInterest` method:

![](../../../requirements/images/specifications/intents/user-interest/media/image4.png)

**TODO**: clean this up and add to spec

1. When an Aggregated Experience app calls `Content.requestUserInterst` the platform MUST dispatch a `Discovery.onRequestUserInterest` notification to the best candidated provider app.
2. The Firebolt SDK embedded in the provider app parses out the parameters from onRequestUserInterest API and calls the apps `Provider.userInterest` method, which was passed in via Discovery.provide()
3. The SDK waits for the response from `Provider.userInterest` and then it calls `Discovery.userInterestResponse`
4. If the app threw an error, the SDK calls `Discovery.userInterestError`

Once an App's callback is invoked, that app will have `interestTimeout`
milliseconds to return a value or throw an error. Values returned after
that time **MUST** be ignored. The timeout value is stored in the
device's configuration manifest.

To be notified when a user expresses interest in the currently displayed
content, an App **MUST** provide the
`xrn:firebolt:capability:discovery:interest` capability by enabling the
`Discovery.onRequestUserInterest` notification.

If there is a valid entity to return, then the method registered by the
App **MUST** return the currently displayed entity meta-data.

If there is no valid entity to return, then the method **MUST** throw an
exception.

If the provider app returns a valid `EntityDetails` before the timeout,
then, the returned value **MUST** be used.

If there is no app registered the an error **MUST** be returned.

#### User Interest Errors
An app is expected return either a valid result or an appriate error.

If neither happens before `interestTimeout` expires then the platform **MUST** return a Provider timed-out error:

```json
{
  "id": 1,
  "error": {
    "code": -50400,
    "message": "Provider timed-out",
    "data": {
      "capability": "xrn:firebolt:capability:discovery:interest",
    }
  }
}
```

If an app recieves a request for user interest when there is nothing appropriate to return, e.g. nothing selected or presented that maps to an Entity, then the app **SHOULD** return an error with a valid JSON-RPC error response, e.g.:

```json
{
  "id": 1,
  "error": {
    "code": -40400,
    "message": "No entities currently presented."
  }
}
```

The platform API Gateway **MUST** append, or overwrite, the `data.capability` value to any errors returned by the app, e.g.:

```json
{
  "id": 1,
  "error": {
    "code": -40400,
    "message": "No entities currently presented.",
    "data": {
      "capability": "xrn:firebolt:capability:discovery:interest",
    }
  }
}
```

### 3.3. Upstream User Interest Intent
In some cases, e.g. a voice assistant, some upstream component will inform
the platform that the user is interested in whatever is currently being presented.

To do this, the upstream system **MUST** send a `Interest` intent, which describes the type of and reason for the interest.

```json
{
  "action": "interest",
  "data": {
    "type": "interest",
    "reason": "playlist"
  }
}
```

When a Firebolt platform receives this intent, it **SHOULD** initiate the platform's [user interest flow](#4-user-interest-from-a-platform-ux).

### 3.4. User Interest Bulk Updates

Sending bulk interest updates, e.g. Entities the user expressed interest
in on a different platform, is not supported.

## 4. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK as part of the
`Discovery` module.

### 4.1. InterestType
This is an enum with the following values:

- `"interest"`
- `"disinterest"`

### 4.2. InterestReason
This is an enum with the following values:

| Reason | Description |
| ------ | ----------- |
| `playlist` | Interested in adding to a list |
| `reaction` | Interested in submitting a reaction, e.g. like or dislike |
| `recording` | Interest in scheduling a recording |
| `share` | Interest in sharing the content on social media |

### 4.3. Discovery.userInterest

This is a push API that allows Apps to push entities that the user has
expressed interest in to the platform.

To push an entity that the user is interested in pass an `EntityDetails`
object to the method:

```typescript
Discovery.userInterest(type: InterestType, reason: InterestReason, entity: EntityDetails): Promise<void>
```

### 4.4. Discovery Interest Provider
To respond to requests for the current entity, because the user has
expressed interest in some way that the platform manages, register a
provider:

```typescript
interface IDiscoveryInterestProvider {
  function userInterest(type: InterestType, reason: InterestReason): Promise<EntityDetails>
}

Discovery.provide("xrn:firbolt:capability:discovery:interest", IDiscoveryInterestProvider)
```

### 4.5. InterestIntent

An `InterestIntent` denotes that the user has expressed interest in the
currently displayed and/or selected content:

```typescript
type InterestIntent {
  action: "interest"
  data: {
    type: "interest" | "disinterest",
    reason: "playlist" | "reaction" | "recording"
  },
  context: {
    source: "rcu" | "voice"
  }
}
```

## 5. Discovery SDK APIs

The following APIs are exposed by the Firebolt Discovery SDK as part of the
`Content` module.

### 5.1. Interest Types
This type stores the various attributes of an Interest response or event:

```typescript
type InterestType = "interest" | "disinterest"
type InterestReason = "playlist" | "reaction" | "recording" | "share"

type Interest {
  appId: string
  entity: EntityDetails
  type?: InterestType
  reason?: InterestReason
}
```

### 5.2. Content.requestUserInterest
This method triggers the corresponding Discovery provider API for the
provider app.

```typescript
Content.requestUserInterest(type: InterestType, reason: InterestReason): Promise<Interest>
```

### 5.3. Content.onUserInterest

This notification allows Aggregated Experience Apps to be informed when
a user expresses interest in some Content, and the content resolves to a
valid Entity from some App.

`Content.listen('userInterest', Interest => void): Promise<void>`

The callback will be passed an `Interest` object with
the appId, type, reason, and information about the entity that the user expressed interest in.
