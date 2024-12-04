# App Presentation

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor               | Organization |
| ------------------------- | ------------ |
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
applications must fulfill when managing App Presention. *App Presentation* 
refers to the display, focus, and navigational aspects of an App. 

The *display* of an app refers to its visibility and size. 

Whether an app has an *overlay* refers to any other apps or UX being presented 
on top of the app. 

Apps that are presented to users by the platform may receive *navigation* 
intents, which are like deep links from the platform. 


## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Focus](#3-focus)
- [4. Visible](#4-visible)
- [5. Display](#5-display)
  - [5.1. Display vs Lifecycle](#51-display-vs-lifecycle)
- [6. Loading Screen](#6-loading-screen)
  - [6.1. Platform-provided Loading Screen](#61-platform-provided-loading-screen)
  - [6.2. App-provided Loading Screen](#62-app-provided-loading-screen)
- [7. Overlay](#7-overlay)
  - [7.1. Overlay vs Focus](#71-overlay-vs-focus)
- [8. Navigation](#8-navigation)
- [9. Picture-in-Picture Video](#9-picture-in-picture-video)


## 3. Focus

The `Presentation` module **MUST** have a `focus` boolean property that returns 
whether or not the app has input, e.g. RCU, focus. 

An app with focus **MUST** receive key presses from the RCU.

Firebolt platforms **MAY** decide which RCU keys are privilleged, and do not go to apps.

Firebolt platforms **MAY** forward RCU keys to an app that does not have focus, e.g. a pause key while there's a settings overlay.

An app **MAY** receive intents from the platform regardless of whether it has focus or not.

As a property, this API also has an `onFocusChanged` notification. 

## 4. Visible
The `Presentation` module **MUST** have a `visibile` boolean property that returns `true` if the `display` is one of `fullscreen`, `scaled`, `thumbnail`.

## 5. Display

The `Presentation` module **MUST** have a `display` string property that 
returns one of the following values: 

| Value        | Description                                                                                                             |
|--------------|-------------------------------------------------------------------------------------------------------------------------|
| `fullscreen` | The app is displayed such that the dimensions fill the entire screen                                                    |
| `offscreen`  | The app has it's graphics surface attached, but not displayed on the screen at the moment, e.g. scrolled out of view |
| `scaled`     | The app is displayed at a size smaller than the entire screen but at least 25% of the width or height                   |
| `thumbnail`  | The app is displayed at a size smaller than 25% of the width or height of the entire screen                             |
| `loading`    | The platform is displaying a loading screen while the app prepares to be activated                                      | 
| `none`       | The app does not have its graphics surface attached to the screen                                                      |

Note that if a scaled or thumbnailed app goes offscreen, it's now offscreen.

### 5.1. Display vs Lifecycle

Each Lifecycle state only supports certain display states: 

| Lifecycle      | Supported Displays                               |
|----------------|--------------------------------------------------|
| `initializing` | `none`, `loading`                                |
| `active`       | `fullscreen`, `scaled`, `thumbnail`, `offscreen` |
| `running`      | `none`, `loading`                                |
| `suspended`    | `none`, `loading`                                |
| `sleeping`     | `none`, `loading`                                |

See [Picture-in-picture](#9-picture-in-picture-video) for exceptions to this. 

## 6. Loading Screen
In order to manage user expectations, Firebolt platforms **MAY** display 
loading screens to end users when an app is going to be activated. Loading 
Screens may be rendered either by the platform, the app, or both, depending on 
Capability configuration. 

Firebolt platforms **MAY** decide when an app activation warrents a loading 
screen, for example when an app will be initialized or woken from sleep before 
activation. 

If an app has the `xrn:firebolt:capability:presentation:loading-screen` 
capability and the platform chooses to utilize the app's loading screen, the 
app **MAY** be made visible any time from the beginning of activate() 
transition and **MUST** be made visible no later than the end. 

When the app is made visbile, the platform **MUST** update the display state to one of:

- `fullscreen`
- `scaled`
- `thumbnail`
- `offscreen` 

If an app does not have the 
`xrn:firebolt:capability:presentation:loading-screen` capability or the 
platform decides not to use the app's loading screen, the app **MUST** be made 
visible at the end of the activate() transition. 

It is up to each platform to determine when a loading screen is useful. 

### 6.1. Platform-provided Loading Screen

If an app provides the `xrn:firebolt:capability:presentation:loading-screen` 
capability, then the platform **MAY** use the app-provided loading screen, in 
which case, the rest of the section does not apply. 

If the platform determines that a platform loading screen will be displayed, 
then: 

> The loading screen **SHOULD** include a loading image referenced in the app's 
> manifest and cached on the device. 
> 
> The loading screen **MUST** be displayed when the user attempts to launch the 
> app. 
> 
> The loading screen **MUST** stay displayed until the app becomes active.
> 
> The presentation state of the app **MUST** be `LOADING` for the entire time 
> the loading screen is displayed. 
> 
> Each Firebolt platform **MAY** define what "load screen" means in these 
> requirements. 

See [Lifecycle](./index.md) for more info on launching. 

### 6.2. App-provided Loading Screen

If an app provides the `xrn:firebolt:capability:presentation:loading-screen` 
capability, then the platform **MAY** invoke this capability in some 
situations. 

If the platform determines that an app loading screen will be displayed, then: 

> The platform provided loading screen **MAY** be displayed first. 
> 
> If the platform provided loading screen is displayed then the app's 
> presentation state should be `loading`. 
> 
> The app **MAY** be made visible at the beginning of the activate transition. 
> 
> The app **MAY** be made visible at a later point during the activate 
> transition based on platform-specific requirements, e.g. detecting that the 
> app's graphics surface has been utilized. 
> 
> The app **MUST** be made visible no later than the end of the activate 
> transition. 

The presentation state of the app **SHOULD NOT** be `none` at any time during 
the `activate()` transition. 

See [Lifecycle](./index.md) for more info on loading and activating apps. 

## 7. Overlay
The `Presentation` module **MUST** have an `overlay` string property that 
informs the app when a focus-consuming overlay is present. 

| Value      | Description                                                                                   |
|------------|-----------------------------------------------------------------------------------------------|
| `partial`  | There is a overlay partially covering the app such that the content is still mostly viewable. |
| `blocking` | There is a blocking overlay covering a majority of the app.                                   |
| `none`     | There is nothing covering the app.                                                            |

### 7.1. Overlay vs Focus

| Focus | Overlay                 |
| ----- | ----------------------- |
| true  | none                    |
| false | partial, blocking, none |

## 8. Navigation
Typically navigation is handled either when the app is activated, via the 
`intent` parameter of the [`activate()` 
method](./index.md#52-activating-an-app), or by internal input within the app. 

There are other times when the platform needs to inform an app of a user's 
intent to navigate when the app is already `ACTIVE`, e.g. when a voice command 
is executed or an RCU sends a reserved key to the platform that would result in 
the app taking some action, e.g. going to its home screen. 

If the app provides the `xrn:firebolt:capability:presentation:navigation` 
capability then the platform **MUST** call the `Presentation.navigateTo` method 
of the app's provider and pass an `intent` to an app that is in the `ACTIVE` 
state. 

To invoke an app's `navigateTo` provider API the platform **MUST**: 

> The platform **MUST** call the `Presentation.navigateTo` method of the App,
> and wait for `appNavigateToTimeout` milliseconds for either a result or error
> response.
> 
> Once the platform receives a result, then the platform may proceed with the
> expectation that the app in fact will handle the `intent`.
> 
> If the app times out or returns an error, then the app **MAY** have focus
> removed or be deactivated, so that the platform can handle the 
> `intent` in some other way. 

An app **SHOULD** successfully handle the `navigateTo` call if the app is capabable
of handling the intent. Otherwise the app **SHOULD** throw an error.

Platforms **MAY** decide to remove focus from or deactivate apps that do not 
acknowledge the `navigateTo` call successfully. 

If an app receives multiple navigate calls in parallel, it **MAY** ignore all but the final call.

An app can decide how to handle multiple navigate calls, but  
**SHOULD** execute the final call.

To fullfil a prioritized `navigateTo()` call, the app **MUST** inspect the 
`intent` parameter and prepare to fulfill a specific [Navigation 
Intent](../intents/navigation.md) which may include: 

 - Loading any metadata needed to display the user's intended content.
 - Performing any entitlement checks to decide whether to display a player or a purchase flow
 - Any other steps necesary to present content to the user quickly

The app **MAY** display a loading indicator. 

## 9. Picture-in-Picture Video
If an app has the `xrn:firebolt:capability:media:picture-in-picture`, then it 
can keep playing audio/video when the app is in the `none` display state and 
the audio & video will be presented to the user in bounding box determined by 
the platform. Note that this does not include the entire UX of the app, just 
the active media pipeline. 

When an app has this capability, it **MAY** be put into the `none` display 
state while in the `active` Lifecycle state. 
