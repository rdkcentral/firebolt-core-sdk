# App Lifecycle Management

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor               | Organization |
|---------------------------|--------------|
| Andrew Bennett            | Sky          |
| Cody Bonney               | Charter      |
| Bart Catrysse             | Liberty      |
| Tim Dibben                | Sky          |
| Piotr Kobzda              | Liberty      |
| Jeremy LaCivita           | Comcast      |
| Ramprasad Lakshminarayana | Sky          |
| Kevin Pearson             | Comcast      |
| Jan Pedersen              | Sky          |
| Peter Yu                  | Comcast      |

## 1. Overview

This document describes the requirements that Firebolt platforms and Firebolt 
applications must fulfill when managing App Lifecycles. *App Lifecycle* refers 
to the lifecycle of an individual app from the time it is launched/loaded to 
the time it is destroyed and all runtime resources are discarded. 

*Initializing* an app refers to fetching the initial resources, e.g. the 
app-manifest and index.html, and loading them into a container capable of 
running the app, e.g. a web browser. 

*Activating* an app refers to the process of getting an app into a state where 
it is given full resources, e.g. media pipeline. This may include *initializing* the app 
first, if needed.

*Closing* an app refers to the process of getting an app out of a state where 
it is the primary user experience (e.g. not visible, not audible, and not 
responding to input). This **does not** involve *destroying* the app. 

*Suspending* an app refers to reducing the app's memory and CPU usage, and 
deallocating its graphics surface so that other apps will have more resources 
available. 

*Resuming* an app refers to reallocating its graphics surface and resuming 
normal CPU and memory allocations. 

*Destroying* an app refers to the process of notifying an app to do any needed 
clean up, and then *terminating* it. 

*Terminating* an app refers to shutting down the app's container and reclaiming 
any memory, CPU, etc. that it was consuming. 

*Hibernating* an app refers to putting the app into a state where it does not use 
CPU cycles, which allows the platform to optimise memory consumption. 

*Restoring* an app refers to copying a Hibernated app back into the memory space of 
a compatible process so that it resumes where it left off. 

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Lifecycle States](#3-lifecycle-states)
  - [3.1. Initializing](#31-initializing)
  - [3.2. Running](#32-running)
  - [3.3. Active](#33-active)
  - [3.4. Suspended](#34-suspended)
  - [3.5. Hibernated](#35-hibernated)
- [4. Getting the current state](#4-getting-the-current-state)
- [5. Lifecycle State Transitions](#5-lifecycle-state-transitions)
  - [5.1. Initializing an app](#51-initializing-an-app)
  - [5.2. Activating an app](#52-activating-an-app)
  - [5.3. Deactivating an app](#53-deactivating-an-app)
  - [5.4. Suspending an app](#54-suspending-an-app)
  - [5.5. Resuming an app](#55-resuming-an-app)
  - [5.6. Putting an app into hibernation](#56-putting-an-app-into-hibernation)
  - [5.7. Restoring an app from hibernation](#57-restoring-an-app-from-hibernation)
  - [5.8. Destroying an app](#58-destroying-an-app)
  - [5.9. Terminating an app](#59-terminating-an-app)
- [6. Create Parameters](#6-create-parameters)
- [7. Core SDK APIs](#7-core-sdk-apis)
  - [7.1. Application Interface](#71-application-interface)
  - [7.2. Activatable Interface](#72-activatable-interface)
  - [7.3. Hibernation Interface](#73-hibernation-interface)
  - [7.4. Example App](#74-example-app)
  - [7.5. Close](#75-close)
  - [7.6. State](#76-state)
- [8. Lifecycle Configuration](#8-lifecycle-configuration)


## 3. Lifecycle States

Firebolt platforms **MUST** support running one or more apps concurrently. The 
platform **MUST** manage transition of apps from state to state. 

A Firebolt app, once running, **MUST** be in one of several states and **MUST 
NOT** be in more than one state at a time. 

As an app changes states the platform will invoke specific app-provided 
transition methods, see [Transitions](#5-lifecycle-state-transitions), for more 
on this. 

![Lifecycle States](../../images/specifications/lifecycle/lifecycle-states.png) 

|              | CPU | RAM | F/S | Net | GFX | SFC | A/V | Description                                                                |
|--------------|-----|-----|-----|-----|-----|-----|-----|----------------------------------------------------------------------------|
| Initializing | ✔   | ✔   | ✔   | ✔   |     |     |     | Started executing, but is not yet instantiated as a Firebolt app.          |
| Running      | ✔   | ✔   | ✔   | ✔   | ✔   | ✔   |     | Full access to resources, except A/V, and registered as a Firebolt app.    |
| Active       | ✔   | ✔   | ✔   | ✔   | ✔   | ✔   | ✔   | Full access to resources and is a perceptible part of the user experience. |
| Suspended    | ↓   | ↓   | ✔   | ✔   |     |     |     | Reduced memory footprint and no access to graphics or A/V.                 |
| Hibernated   |     |     |     |     |     |     |     | No CPU cycles are given to the app. App may stay in RAM or be stored.      |

|     | Legend                  |
|-----|-------------------------| 
| CPU | Central Processing Unit |
| RAM | Ramdon Access Memory    |
| F/S | File System             |
| Net | Network                 |
| GFX | Graphics rendering      |
| SFC | Graphics surface        |
| A/V | Audio Video Decoder     |
| ↓   | Limited                 |
| ✔   | Normal access           |
| ?   | Unknown                 | 

### 3.1. Initializing

This is the initial state an app exists from the moment it starts receiving CPU 
cycles. 

When an app starts running it **MUST** initialize the Firebolt SDK as quickly 
as possible and then wait for the `Application.create()` interface to be called 
before doing further setup. 

Apps in this state **MUST NOT** have a graphics surface allocated yet. 

Apps in this state **MUST NOT** be visible. 

Apps in this state **MUST NOT** receive RCU key presses. 

Apps in this state **MUST NOT** have access to the audio-video decoder. 

Apps in this state **MUST NOT** use the media pipeline. 

See [Initializing an app](#51-initializing-an-app) for more information. 

### 3.2. Running

This state allows an app to be running and ready to go, but not actively part 
of the user-perceptible experience. 

Running apps can execute code, but are not presented to the user, do not
receive any input from RCUs, and cannot use the video decoder. 

Apps in this state **MUST** have access to the graphics surface. 

Apps in this state **MAY** have created, allocated a graphics surface, but it 
will not be made visible by platform compositor. 

Apps in this state **MUST NOT** be visible. 

Apps in this state **MUST NOT** receive RCU key presses. 

Apps in this state **MUST NOT** have access to the audio-video decoder. 

Apps in this state **MUST NOT** use the media pipeline and the platform 
**MUST** tear down any Media Pipeline sessions associated with this app. 

Apps **MUST** only enter this state from:

  - the `INITIALIZING` state, via the `create()` method
  - the `ACTIVE` state, via the `deactivate()` method
  - the `SUSPENDED` state, via the `resume()` method

When an app transitions to this state, the platform **MUST** dispatch the 
`Lifecycle.onStateChanged` notification with the current state. 

### 3.3. Active

This state allows an app to be presented as part of the user-perceptible 
experience. 

To determine if an app is the *primary* experience, e.g. fullscreen, etc., see 
[Presentation](./presentation.md#5-display). 

It is a platform decision as to how many apps may be in this state at once. 

Apps in this state **MAY** be visible. 

Apps in this state **MAY** receive RCU key presses that they have permissions 
for. 

Apps in this state **MUST** have access to the audio decoder if they have 
permission to the `xrn:firebolt:capability:decoder:audio` capability and the 
platform has an available software or hardware decoder. 

Apps in this state **MUST** have access to the video decoder if they have 
permission to the `xrn:firebolt:capability:decoder:video` capability and the 
platform has an available software or hardware decoder. 

Apps in this state **MUST** have access to the graphics surface. 

Apps in this state **SHOULD** reduce memory usage, if possible. 

Apps **MUST** only enter this state from the `RUNNING` state, via the `activate()` method.

When an app transitions to this state, the platform **MUST** dispatch the 
`Lifecycle.onStateChanged` notification with the current state. 

### 3.4. Suspended

This state allows an app to remain in memory and consume fewer resources. 

Suspended apps can execute code, but are not presented to the user, do not
receive any input from RCUs, and cannot use the video decoder. 

Apps in this state **MUST NOT** have a graphics surface allocated any longer. 
It **MUST** have been deallocated in the `suspend()` transition. 

Apps in this state **MUST NOT** be visible. 

Apps in this state **MUST NOT** receive RCU key presses. 

Apps in this state **MUST NOT** have access to the audio-video decoder. 

Apps in this state **SHOULD** further reduce memory usage (more so than in the 
`active` state), if possible. 

Apps **MUST** only enter this state from:

  - the `HIBERNATED` state, via the `restore()` method
  - the `RUNNING` state, via the `suspend()` method

When an app transitions to this state, the platform **MUST** dispatch the 
`Lifecycle.onStateChanged` notification with the current state. 

### 3.5. Hibernated

This state allows an app to be copied from memory to local storage and then 
terminated to save resources. Subsequently, the app may be copied back into 
memory, and resume in the same state. 

*If* a platform does not support the 
`xrn:firebolt:capability:lifecycle:hibernation` capability, then the following 
requirements **MUST NOT** be fulfilled, even partially. A platform **MUST NOT** 
use the APIs documented here to implement an alternate, non-compliant version 
of the app hibernation feature. 

*If* a platform supports the `xrn:firebolt:capability:lifecycle:hibernation` 
capability, then the following requirements **MUST** be fulfilled. 

Apps **MUST** only enter this state from the `SUSPENDED` state, via the 
`hibernate()` method. 

If a platform supports copying hibernated apps memory out of RAM then: 

> The platform **MAY** save the app's memory space at this point, so that it 
> may be restored later. 
> 
> Finally, the app and its container **MAY** be removed from memory and have 
> other resources released as well. 

## 4. Getting the current state

The Lifecycle module **MUST** provide a `state` property API that returns the 
current lifecycle state of the app. 

If an app is in a transition from one state to another, then it **MUST** be 
considered in the state *before* the transition until such time as the app's 
implementation of the [transition](#5-lifecycle-state-transitions) has returned 
and the platform has finished the transition. 

The `state` API **MUST** have a corresponding `onStateChanged` notification. 

The `state` API must have one of the following values: 
- `Initializing`
- `Running`
- `Suspended`
- `Active`
- `Hibernated`

Note that the `onStateChanged` notification **MUST** never be dispatched for 
the `Hibernated` state since it would not be received anyway. 

## 5. Lifecycle State Transitions

There are several state transitions where the app and the platform need to 
interact to ensure the transition goes smoothly. 

![Lifecycle 
States](../../images/specifications/lifecycle/lifecycle-transitions.png) 

As an app changes states the platform will invoke specific app-provided 
transition methods from the `Application` interface: 

|   | Legend        |
|---|---------------|
| ↓ | Limited       |
| ✔ | Normal access |

|             | CPU | RAM | Net | GFX | A/V | Description                                                                                          |
|-------------|-----|-----|-----|-----|-----|------------------------------------------------------------------------------------------------------|
| `create()`  | ✔   | ✔   | ✔   | ✔   |     | Creation of the app, from a Firebolt Lifecycle perspective.                                          |
| `suspend()` | ✔   | ✔   | ✔   | ✔   |     | Reduce memory and CPU usage, deallocate graphics surface.                                            |
| `resume()`  | ✔   | ✔   | ✔   | ✔   |     | graphics surface reallocated, full memory usage and normal CPU cycles.                               |
| `destroy()` | ✔/↓ | ✔/↓ | ✔   |     |     | Prepare for the app to be deallocated and removed from execution. CPU & RAM based on previous state. |


If an app implements the `Activatable` interface, then the following 
transitions may be invoked: 

|                | CPU | RAM | Net | GFX | A/V | Description                                                               |
|----------------|-----|-----|-----|-----|-----|---------------------------------------------------------------------------|
| `activate()`   | ✔   | ✔   | ✔   | ✔   | ✔   | App is expected to become a user-perceptible part of the user experience. |
| `deactivate()` | ✔   | ✔   | ✔   | ✔   | ✔   | Must remove any user-perceptible activities and deallocate A/V decoders.  |



Finally, if an app implements the `Hibernation` interface, then the following 
transitions may be invoked. 

|           | CPU | RAM | Net | GFX | A/V | Description                                                                            |
|-----------|-----|-----|-----|-----|-----|----------------------------------------------------------------------------------------|
| `hibernate()` | ↓   | ↓   | ✔   |     |     | Prepare for an extended period with no CPU cycles given to app.                        |
| `restore()`  | ↓   | ↓   | ✔   |     |     | Cleanup after an extended period with no CPU, e.g. reset timers / network connections. |


All of these transition APIs are blocking, and each one has a 
platform-configurable timeout that specifies how long the app has to fulfill 
the method. 

The platform **MUST** never invoke any transitions on an app when that app is 
already running a transition. 

All Firebolt apps **MUST** implement the `Application` interface, 
`xrn:firebolt:capability:lifecycle:application`. 

This includes: 
- `Application.create()`
- `Application.suspend()`
- `Application.resume()`
- `Application.destroy()`


By providing an implementation of the 
`xrn:firebolt:capability:lifecycle:application` interface, an app can influence 
how resources are managed during these state transitions. See [Application 
Interface](#71-application-interface) for more info. 

User-facing apps **MUST** implement the `Activatable` interface, 
`xrn:firebolt:capability:lifecycle:activatable`. 

This includes: 
- `Application.activate()`
- `Application.deactivate()`


By providing an implementation of the 
`xrn:firebolt:capability:lifecycle:activatable` interface, an app can influence 
how resources are managed during these state transitions. See [Activatable 
Interface](#72-activatable-interface) for more info. 
### 5.1. Initializing an app

Once an app is loaded it **MUST** be initialized immediately. 

Initializing consists of three parts: 
- Registration of the Firebolt Application provider
- Any other code that automatically runs within the app executable
- Invoking the app's Application.create() method


If an app does not provide the `xrn:firebolt:capability:lifecycle:application` 
capability within `initializeTimeout` milliseconds, then the platform **MUST** 
terminate the app. 

Otherwise, the platform **MUST** call the app's implementation of 
`Application.create()`: 

> The platform **MUST** call the `Application.create` method of the app, 
> and wait for `appCreateTimeout` milliseconds for either a successful
> result or error response. 
> 
> Once the platform receives a success, then the app is considered to have any
> important Firebolt notifications set up and is ready 
> to be activated and presented to the user. 
> 
> If the app times out or throws an error, then the app **MUST** be 
> immediately terminated by the platform. 

Apps **SHOULD** set up any Firebolt event listeners either before calling 
`Lifecycle.provide` or during `create()`, since the platform will wait until 
the app is ready before dispatching many critical events such as Lifecycle and 
Presentation events. 

Apps **SHOULD** acquire any important authentication needed for the app to 
function during initialization. 

Apps **MAY** load a limited set of global display resources, e.g. a global 
style sheet or a logo used throughout the experience, during initialization. 

During the `create()` transition, apps **MUST** inspect the `params` parameter 
for [Parameters](#6-create-parameters) and prepare to fulfill the provided 
launch configuration. 

Example Launch Parameters: 
```json
{
  "preload": true,
  "preloadReason": "boot"
}

``` 

Once the `create` method returns the app **MUST** be immediately transitioned 
to the `RUNNING` state. 
### 5.2. Activating an app


Activating an app transitions it to the `ACTIVE` state so that it becomes part 
of the user's experience. 

Firebolt apps that have permission to use the 
`xrn:firebolt:capability:lifecycle:activate` capability **MUST** implement 
`Activatable.activate()`. 

The platform may activate apps for any number of reasons that are out of scope 
for this document. 

To activate an app, platforms **MUST** use the following process. 

If the app is already in the `ACTIVE` state, then it is already activated and 
there is no need to do anything else. The platform **MUST NOT** dispatch any 
*additional* lifecycle notifications when attempting to activate an app that is 
already in the active state and the remainder of this section does not apply. 

If the app is not loaded, then the platform **MUST** load it first. 

If the app is not initialized, the platform **MUST** 
[initialize](#51-initializing-an-app) it first. 

If the app is suspended, then it **MUST** be [resumed](#55-resuming-an-app) 
first. 

At this point, the app **MUST** be in the `RUNNING` state. 

If an app provides the `xrn:firebolt:capability:lifecycle:activatable` 
capability, then the platform **MUST** call the app's implementation of 
`Activatable.activate()`: 

> The platform **MUST** call the `Activatable.activate` method of the app, 
> and wait for `appActivateTimeout` milliseconds for either a success or an
> error response. 
> 
> The `activate` call **MUST** include a `NavigationIntent`. 
> 
> Once the platform receives a success response, then the app may be 
> moved to the `ACTIVE` state. 
> 
> If the app times out or throws an error, then the app **MUST** 
> be terminated. 

If the app provides the `xrn:firebolt:capability:presentation:navigation` 
capability then the `intent` **MAY** be any [Navigation 
Intent](../intents/navigation.md) the app is configured to support. 

If the app does not provide the capability, then the `intent` **MUST** be the 
[Launch Intent](../intents/navigation.md). 

During the `activate()` transition, the app **MUST** inspect the `intent` 
parameter and prepare to fulfill a specific Navigation Intent for this 
activation which may include: 

- Loading any metadata needed to display the user's intended content.
- Performing any entitlement checks to decide whether to display a player or a purchase flow
- Any other steps necessary to present content to the user quickly

The platform **MAY** display a loading screen for the entire duration of the 
`activate()` callback, and apps **SHOULD** do whatever is necessary to present 
the user with content that fulfills the `intent` without additional loading 
screens in the app's UX. 

### 5.3. Deactivating an app

Deactivating an app transitions it to the `RUNNING` state, so that it consumes
fewer resources. This **MAY** be paired with a transition of the [Presentation](./presentation.md)
state, so that it is no longer part of the user's experience. 

Firebolt apps that have permission to use the 
`xrn:firebolt:capability:lifecycle:activate` capability **MUST** implement 
`Activatable.deactivate()`. 

The platform may deactivate apps for any number of reasons that are out of scope for 
this document. 

Apps **MAY** request to be deactivated, via the `Lifecycle.close()` API method. 

To deactivate an app, platforms **MUST** use the following process. 

If an app is already in the `RUNNING`, `SUSPENDED`, or `HIBERNATED` state, then 
it is already deactivated and there is no need to do anything else. The platform 
**MUST NOT** dispatch any *additional* lifecycle notifications when attempting 
to deactivate such an app and the remainder of this section does not apply. 

If an app is already performing a `deactivate()` transition, the platform 
**MUST** ignore the new attempt to deactivate the app, allow the pending closure to 
complete, and the remainder of this section does not apply. 

If an app is already performing an `activate()` transition, the platform 
**MUST** wait for the activate call to succeed or fail and then skip the 
remaining [activation steps](#52-activating-an-app) and fulfill the remainder
of this section instead. 

If an app is currently [initializing](#51-initializing-an-app), the platform 
**MUST** wait for initialization to succeed or fail and then skip any 
activation that may have been pending, and the remainder of this section does
not apply. 

If an app is currently in a [destroy](#58-destroying-an-app) transition then 
the app cannot be deactivated and the platform **MUST NOT** attempt to, and the 
remainder of this section does not apply. 

At this point, the app **MUST** be in the `ACTIVE` state. 

If an app provides the `xrn:firebolt:capability:lifecycle:activatable` 
capability, then the platform **MUST** call the app's implementation of 
`Activatable.deactivate()`: 

> The platform **MUST** call the `Activatable.deactivate` method on the app,
> and wait for `appDeactivateTimeout` milliseconds for a success or error response.
> 
> Once the platform receives a success, then the app may be moved to the `RUNNING` state. 
> 
> If the app times out or makes an error, then the app **MUST** 
> be terminated. 

During the `deactivate()` transition, the app **MUST** deallocate any A/V 
decoders. 

The platform **MAY** begin to transition the app out of view as soon as 
`deactivate()` is called. 
### 5.4. Suspending an app


Suspending an app transitions it to the `SUSPENDED` state, where it is no 
longer allowed to use graphics composition, and is expected to consume less CPU 
and RAM. 

The platform may suspend apps in order to free up memory, or for any number of 
reasons that are out of scope for this document. However, it is the platform's 
decision to suspend an app, not the app itself. 

To suspend an app, platforms **MUST** use the following process. 

If an app is in the `ACTIVE` state then it cannot yet be suspended, and 
**MUST** be deactivated first. 

If an app is in the `HIBERNATED` state then it cannot be suspended and there is 
no need to do anything else. The platform **MUST NOT** dispatch any 
*additional* lifecycle notifications when attempting to suspend an app that is 
already in the `HIBERNATED` state and the remainder of this section does not 
apply. 

If an app is already in the `SUSPENDED` state, then it is already suspended and 
there is no need to do anything else. The platform **MUST NOT** dispatch any 
*additional* lifecycle notifications when attempting to suspend an app that is 
already in the suspended state and the remainder of this section does not 
apply. 

If the app is not loaded, or is not in the `RUNNING` state, then it cannot be 
suspended, and the remainder of this section does not need to happen. 

At this point, the app **MUST** be in the `RUNNING` state. 

Since every app **MUST** provide the 
`xrn:firebolt:capability:lifecycle:application` capability, the platform 
**MUST** call the app's implementation of `Application.suspend()`: 

> The platform **MUST** call the `Application.suspend` method of the app,
> and wait for `appSuspendTimeout` milliseconds for either a success or error
> in response.
> 
> Once the platform receives a success, then the app may be moved to the
> `SUSPENDED` state. 
> 
> If the app times out or throws an error, then the app **MUST** be 
> [destroyed](#58-destroying-an-app). 

During the `suspend()` transition, the app: 

> **MUST** deallocate any graphics surface. 
> 
> **SHOULD** reduce memory usage, if possible. 
### 5.5. Resuming an app

Resuming an app allows it to reallocate graphics composition and reload any 
resources it might have deallocated during `suspend()`. 

The platform may resume apps so they can access more resources or in 
preparation to activate them. 

To resume an app, platforms **MUST** use the following process. 

If an app is not in the `SUSPENDED` state, then it cannot be resumed and there 
is no need to do anything else. The platform **MUST NOT** dispatch any 
*additional* lifecycle notifications when attempting to resume an app that is 
not in the `SUSPENDED` state and the remainder of this section does not apply. 

At this point, the app **MUST** be in the `SUSPENDED` state. 

Next, the platform **MUST** remove any restrictions on access the graphics 
compositor. 

Suspended apps **MUST** provide the 
`xrn:firebolt:capability:lifecycle:application` capability, so the platform 
**MUST** call the app's implementation of `Application.resume()`: 

The platform **MUST** call the `Application.resume` method of the app,
and wait for `appResumeTimeout` milliseconds for either a success or error
response.

Once the platform receives a success, then the app may be moved 
to the `RUNNING` state. 

If the app times out or throws an error, then the app **MUST** be 
terminated. 

During the `resume()` transition, apps **SHOULD** reallocate graphics 
composition and other necessary resources. 

### 5.6. Putting an app into hibernation
Putting an app into hibernation allows the platform to copy the apps memory stack to
storage and terminate the app in order to save memory.

An app that has been put into hibernation **MUST** be able to be brought back into
memory / CPU in the same state it had been in.

Firebolt apps that have permission to use the 
`xrn:firebolt:capability:lifecycle:hibernation` capability **MUST** implement 
`Hibernation.hibernate()`. 

To put an app into hibernation, platforms **MUST** use the following process. 

If an app is not in the `SUSPENDED` state, then it cannot be put into hibernation and there 
is no need to do anything else. The platform **MUST NOT** dispatch any 
*additional* lifecycle notifications when attempting to resume an app that is 
not in the `SUSPENDED` state and the remainder of this section does not apply. 

At this point, the app **MUST** be in the `SUSPENDED` state. 

Next, the platform **MUST** copy the apps CPU and memory state to some persistant
storage. How platforms implement this is out of scope for this document.

Hibernation apps **MUST** provide the 
`xrn:firebolt:capability:lifecycle:hibernation` capability, so the platform 
**MUST** call the app's implementation of `Hibernation.hibernate()`: 

Once the platform receives a success, then the app may be moved 
to the `HIBERNATED` state. 

If the app times out or throws an error, then the app **MUST** be 
terminated. 

During the `hibernate()` transition, apps **SHOULD** note the clock time in order
to determine the duration of hibernation when the app is restored.
composition and other necessary resources. 

### 5.7. Restoring an app from hibernation
Restoring an app from hibernation allows the platform to copy the apps memory stack back
from storage and relaunch the app in the original state.

Firebolt apps that have permission to use the 
`xrn:firebolt:capability:lifecycle:hibernation` capability **MUST** implement 
`Hibernation.restore()`. 

To restore an app from hibernation, platforms **MUST** use the following process. 

If an app is not in the `HIBERNATED` state, then it cannot be restored from hibernation and there 
is no need to do anything else. The platform **MUST NOT** dispatch any 
*additional* lifecycle notifications when attempting to restore an app that is 
not in the `HIBERNATED` state and the remainder of this section does not apply. 

At this point, the app **MUST** be in the `HIBERNATED` state. 

Next, the platform **MUST** copy the apps CPU and memory state back from persistant
storage. How platforms implement this is out of scope for this document.

Hibernated apps **MUST** provide the 
`xrn:firebolt:capability:lifecycle:hibernation` capability, so the platform 
**MUST** call the app's implementation of `Hibernation.restore()`.

Once the platform receives a success, then the app may be moved 
to the `SUSPENDED` state.

If the app times out or throws an error, then the app **MUST** be 
terminated. 

During the `restore()` transition, apps **SHOULD** check how long it had been in
the `HIBERNATED` state to determine if any processes need to be reset, reauthenticated, etc.

### 5.8. Destroying an app

Destroying an app transitions it out of memory, so that it is no longer using 
resources on the device. 

The platform may destroy apps for any number of reasons that are out of scope 
for this document. 

To destroy an app, platforms **MUST** use the following process. 

If an app is not in the `RUNNING` state, then it cannot be destroyed and there 
is no need to do anything else. The platform **MUST NOT** dispatch any 
*additional* lifecycle notifications when attempting to destroy an app that is 
not in the `RUNNING` state and the remainder of this section does not need to 
happen. 

At this point, the app **MUST** be in the `RUNNING` state. 

Since every app **MUST** provide the 
`xrn:firebolt:capability:lifecycle:application` capability, the platform 
**MUST** call the app's implementation of `Application.destroy()`: 

> The platform **MUST** call the `Application.destroy` method of the app,
> and wait for `appDestroyTimeout` milliseconds for either a success or error
> response.
> 
> Once the platform receives a success, then the platform may proceed with app
> destroying. 
> 
> If the app times out or throws an error, then the app **MUST** 
> be terminated. 

### 5.9. Terminating an app

Terminating an app removes it from memory without dispatching any state 
changes. 

The platform **SHOULD** terminate apps when one of the transitions outlined 
here fails for some reason, or if an app becomes non-responsive. 

Terminating an app results in removing it from memory and all resources held by 
the app and it's container being freed up. 

Platforms **MAY** terminate an app when needed but **SHOULD NOT** do this in 
place of graceful [destroying](#58-destroying-an-app). 

## 6. Create Parameters

The `CreateParameters` type is an object with the following properties: 

```typescript
type CreateParameters = {
  preload: boolean,
  preloadReason?: "boot" | "restart" | "user"
}
``` 

## 7. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK. 

### 7.1. Application Interface

The `Application` interface is implemented by Apps to provide resource 
management around memory as an Application moves through the core lifecycle 
states: 
- `INITIALIZING`
- `RUNNING`
- `SUSPENDED`


All apps **MUST** implement the Application interface. 
```typescript
interface Application {
  function create(params: CreateParameters): Promise<void>;
  function suspend(): Promise<void>;
  function resume(): Promise<void>;
  function destroy(): Promsie<void>;
}

``` 
| Method      | Description                                                                                                                                                                       |
|-------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `create()`  | Called when the platform is ready to create the lifecycle session for the app. Only called only once, during the `INITIALIZING` state.                                            |
| `suspend()` | Called when the platform requires the app to deallocate its graphics surface and reduce memory as much as possible. This may be called anytime the app is in the `RUNNING` state. |
| `resume()`  | Called when the platform wants the app to reallocate its graphics surface and prepare to be potentially used.                                                                     |
| `destroy()` | Called when the platform is ready to end the lifecycle session for the app. Only called once.                                                                                     |

### 7.2. Activatable Interface

The `Activatable` interface is implemented by Apps that provide user 
perceptible experiences, e.g. visible, audible, or user input. 

These types of apps require additional resource management 
```typescript
interface Activatable {
  function activate(intent: NavigationIntent): Promise<void>;
  function deactivate(): Promise<void>;
}

``` 
| Method         | Description                                                                                                                    |
|----------------|--------------------------------------------------------------------------------------------------------------------------------|
| `activate()`   | Called when the platform is ready to move the app into the `ACTIVE` state. A/V resources may be allocated.                     |
| `deactivate()` | Called when the platform is ready to move the app out of the `ACTIVE` state and into `RUNNING` to deallocate any A/V decoders. |

### 7.3. Hibernation Interface

The `Hibernation` interface is implemented by Apps that are able to handle being 
put into hibernation and then restored at a later point in time. 

These types of apps require additional resource management to reestablish 
network connections and may also require additional thread safety checks. 
```typescript
interface Hibernation {
  function hibernate(): Promise<void>;
  function restore(): Promise<void>;
}

``` 
| Method    | Description                                                                                                                                           |
|-----------|-------------------------------------------------------------------------------------------------------------------------------------------------------|
| `hibernate()` | Called when the platform is ready to move the app into the `HIBERNATED` state where it will no longer have access to the CPU.                           |
| `restore()`  | Called when the platform is ready to move the app out of the `HIBERNATED` state and into `RUNNING`. Network connections should be reestablished here. |

### 7.4. Example App

Example: 
```typescript
import { Lifecycle } from '@firebolt-js/sdk'

class ExampleApplication implements Lifecycle.Application, Lifecycle.Activatable {

  async function create(params: CreateParameters): void {
  }

  async function activate(intent: NavigationIntent, session: ProviderSession): void {
    // reallocate A/V
  }

  async function deactivate(): void {
    // free up MSE
    video.src = ""
    video.load()
  }

  async function suspend(): void {
    // The quicket way to save memory & CPU is to clear the DOM
    document.body.innerHTML = ''
  }

  async function resume(): void {
    // recreate UI
    const ux = await createMyUX();
    document.body.appendChild(ux)
  }

  async function destroy(): void {
    // final analytics call
    await fetch("https://example.com/app/metrics/destroy");
  }
}

Lifecycle.provide([
    "xrn:firebolt:capability:lifecycle:application",
    "xrn:firebolt:capability:lifecycle:activatable"
  ], new ExampleApplication())

``` 

**NOTE**: we need to support passing an array of capabilities for a single 
class. 

See the [Firebolt API 
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/) for 
details around syntax, etc. 

### 7.5. Close

The Lifecycle.close() API allows an app to request that it be closed by the 
platform. 

This method requires a reason parameter, which tells the platform why the app 
is requesting to be closed: 

| Reason                    | Description                                                                                                                                                              |
|---------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| CloseReason.REMOTE_BUTTON | The user pressed the back or last button on the RCU and the App has determined it is at the top of it's navigation stack and should go back to the platform home screen. |
| CloseReason.USER_EXIT     | The user selected an exit control exposed by the app's UI.                                                                                                               |
| CloseReason.ERROR         | The app is experiencing unrecoverable issues and needs to be closed and destroyed.                                                                                       |

Platforms generally **SHOULD** respect this call and move the app to the 
running state, but there may be edge cases where this is not possible, e.g. the 
app is considered to be the default experience for the device, and closing it 
would leave no other UX present. 

When the request to close is not respected, the `Lifecycle.close()` method 
**MUST** return an error. 

Platforms **MAY** prioritize apps to be destroyed based on the reason provided. 
For example, apps closed due to the RCU are less likely to be destroyed since 
it may be an accidental RCU press, whereas an explicit user exit is more likely 
to be intentional. 

### 7.6. State

The Lifecycle.state() method provides convenient access to the current state, 
and is implemented by the Core SDK listening to all state notifications. This 
method **MUST NOT** be asynchronous. 

## 8. Lifecycle Configuration

In order to enable Firebolt Certification of a device's Lifecycle Management 
features, the device **MUST** support the following configuration options, so 
that the Firebolt Certification Test Suite knows which optional conditions to 
test for, and for how long to wait for state transitions. 

The LifecyclePolicy fields are: 

| Field                | Type   | Required | Description                                                                                                              |
|----------------------|--------|----------|--------------------------------------------------------------------------------------------------------------------------|
| appInitializeTimeout | bigint | Yes      | Number of milliseconds the platform should wait before terminating a loaded app that did not call `Lifecycle.provide()`. |
| appCreateTimeout     | bigint | Yes      | Number of milliseconds the platform should wait before terminating a loaded app that did not finish `create()`.          |
| appDestroyTimeout    | bigint | Yes      | Number of milliseconds the platform should wait before terminating an app that did not finish `destroy()`.               |
| appActivateTimeout   | bigint | Yes      | Number of milliseconds the platform should wait before terminating an app that did finish `activate()`.                  |
| appDeactivateTimeout | bigint | Yes      | Number of milliseconds the platform should wait before terminating an app that did finish `deactivate()`.                |
| appSuspendTimeout    | bigint | Yes      | Number of milliseconds the platform should wait before terminating an app that did finish `suspend()`.                   |
| appResumeTimeout     | bigint | Yes      | Number of milliseconds the platform should wait before terminating an app that did finish `resume()`.                    |
| appHibernateTimeout  | bigint | Yes      | Number of milliseconds the platform should wait before terminating an app that did finish `hibernate()`.                     |
| appRestoreTimeout       | bigint | Yes      | Number of milliseconds the platform should wait before terminating an app that did finish `restore()`.                      |
