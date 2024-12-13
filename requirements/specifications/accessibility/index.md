# Accessibility Settings

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Andrew Bennet            | Sky            |
| Tim Dibben            | Sky            |
| Jeremy LaCivita            | Comcast            |
| Thijs van der Wal            |             |
| Rimpu Varshney            |             |

## 1. Overview

This document describes the requirements that Firebolt platforms must
fulfill when surfacing the device and/or user accessibility settings to
Apps.

Exposing these settings, e.g. whether closed captions are enabled,
allows Apps to respect the device's current setting so that the user has
a seamless experience when switching from app to app.

This document covers how Firebolt platforms manage accessibility
settings and expose to Apps. It does not cover the use cases Apps might
apply these APIs to.

The term 'Closed Captions' refers to text tracks accompanying video
content that can be turned on and off by the viewer. These are generally
to assist in case the viewer is hard of hearing, in a noisy environment,
or for other accessibility purposes. These tracks typically include
descriptions of important sounds, in addition to the words spoken in the
audio. Many countries and standards body require or encourage the use
Closed Captions, as defined here. The goal of Closed Captions is to make
content more accessible, and therefore, device-wide closed captions
settings should be respected across multiple apps.

This document does not cover requirements for rendering Closed Captions
or other text tracks.

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

- [1. Overview](#1-overview)
  - [1.1. Settings Scope](#11-settings-scope)
  - [1.2. Closed Captions Settings](#12-closed-captions-settings)
    - [1.2.1. Font Family](#121-font-family)
    - [1.2.2. Font Size](#122-font-size)
    - [1.2.3. Font Color](#123-font-color)
    - [1.2.4. Font Edge](#124-font-edge)
    - [1.2.5. Font Edge Color](#125-font-edge-color)
    - [1.2.6. Background Color](#126-background-color)
    - [1.2.7. Font Opacity](#127-font-opacity)
    - [1.2.8. Background Color](#128-background-color)
    - [1.2.9. Background Opacity](#129-background-opacity)
    - [1.2.10. Text Align](#1210-text-align)
    - [1.2.11. Text Align Vertical](#1211-text-align-vertical)
    - [1.2.12. Toggling closed captions](#1212-toggling-closed-captions)
    - [1.2.13. Changing closed captions styles](#1213-changing-closed-captions-styles)
  - [1.3. Voice Guidance Settings](#13-voice-guidance-settings)
    - [1.3.1. Toggling voice guidance](#131-toggling-voice-guidance)
    - [1.3.2. Changing voice guidance speed](#132-changing-voice-guidance-speed)
  - [1.4. Audio Description Settings](#14-audio-description-settings)
    - [1.4.1. Toggling audio descriptions](#141-toggling-audio-descriptions)
  - [1.5. Core SDK APIs](#15-core-sdk-apis)
    - [1.5.1. Closed Captions Settings](#151-closed-captions-settings)
    - [1.5.2. Voice Guidance Settings](#152-voice-guidance-settings)
    - [1.5.3. Audio Description Settings](#153-audio-description-settings)
  - [1.6. Manage SDK APIs](#16-manage-sdk-apis)

### 1.1. Settings Scope

Accessibility settings **MUST** be scoped to the current device. If a
user, household, or account has multiple devices, then changing an
accessibility setting on one device **MUST NOT** change the settings on
another device.

If a device supports profiles accessibility settings **MAY** be managed
separately for each profile, but only on a per-device basis.

### 1.2. Closed Captions Settings

Closed captions settings describe whether closed captions are enabled,
as well as the user's preferred style settings for rendering captions.

The settings are represented by the ClosedCaptionsSettings object, which
has two fields:

| Field   | Description                                         |
|---------|-----------------------------------------------------|
| enabled | Whether closed captions should be presented.        |
| styles  | The preferred styles for rendering closed captions. |

The styles field is an instance of ClosedCaptionsStyles:

| Field             | Description                                                           |
|----------------------|--------------------------------------------------|
| fontFamily        | The name of the font family.                                          |
| fontSize          | The font size as a percent of the video height, i.e. in CSS vh units. |
| fontColor         | The font color.                                                       |
| fontEdge          | The edge type - none, raised, depressed, uniform, dropShadow.         |
| fontEdgeColor     | The edge color.                                                       |
| fontOpacity       | The opacity of the font characters.                                   |
| backgroundColor   | The background color.                                                 |
| backgroundOpacity | The background opacity.                                               |
| textAlign         | The horizontal alignment for captions - left, center, right.          |
| textAlignVertical | The vertical alignment for captions - top, middle, bottom.            |

#### 1.2.1. Font Family

The fontFamily denotes which typeface to be used for rendering closed
captions fonts. This **MUST** be one of:


- `"monospaced_serif"`
- `"proportional_serif"`
- `"monospaced_sanserif"`
- `"proportional_sanserif"`
- `"smallcaps"`
- `"cursive"`
- `"casual"`
- `null`

Firebolt devices **MUST** support all of these values.

#### 1.2.2. Font Size

The fontSize denotes the size that closed captions will be rendered.
This is a numeric value that specifies a relative multiplier for the
default size, e.g. a value of one represents the default closed caption
font size.

To support large fonts for easy reading while still retaining at least
seven rows of captions, the maximum value for this property **MUST** be
2.

To support smaller fonts for minimizing how much of content is
obstructed, the minimum value for this property **MUST** be 0.5.

These values are determined based on closed captions requiring fourteen
rows of text and a one-sixth margin above and below the text. Therefore,
Apps **SHOULD** use two-thirds of the physically rendered video height,
divided by fourteen as the default font-size. While not all Apps will
conform to this standard, it clarifies the range of values supported.

#### 1.2.3. Font Color

The fontColor denotes the color that closed captions fonts will be
rendered in. This is a hexadecimal RGB color, without opacity, per the
[CSS Color Module Level 3](https://www.w3.org/TR/css-color-3/#rgb-color)
spec. For example \"#FF0000\" for red.

The value of this **MUST** be a six-digit, case-insensitive hexadecimal
string preceded by the \'#\' character.

#### 1.2.4. Font Edge

The fontEdge denotes the type of font outline that closed captions fonts
will be rendered with, e.g. a drop-shadow. This is an enumeration that
**MUST** be one of the following values:

- `"none"`
- `"raised"`
- `"depressed"`
- `"uniform"`
- `"drop_shadow_left"`
- `"drop_shadow_right"`
- `null`

#### 1.2.5. Font Edge Color

The fontEdgeColor denotes the color that any closed captions font
outline will be rendered in. This is a hexadecimal RGB color, without
opacity, per the [CSS Color Module Level
3](https://www.w3.org/TR/css-color-3/#rgb-color) spec. For example
\"#FF0000\" for red.

The value of this **MUST** be a six-digit, case-insensitive hexadecimal
string preceded by the \'#\' character.

#### 1.2.6. Background Color

The backgroundColor denotes the color of any background the closed
captions fonts will be rendered with. This is a hexadecimal RGB color,
without opacity, per the [CSS Color Module Level
3](https://www.w3.org/TR/css-color-3/#rgb-color) spec. For example
\"#FF0000\" for red.

#### 1.2.7. Font Opacity

The fontOpacity denotes transparency that closed captions fonts will be
rendered with. This **MUST** be a numeric value from 0 to 100.

#### 1.2.8. Background Color

The backgroundColor denotes the color of any background the closed
captions fonts will be rendered with. This is a hexadecimal RGB color,
without opacity, per the [CSS Color Module Level
3](https://www.w3.org/TR/css-color-3/#rgb-color) spec. For example
\"#FF0000\" for red.

The value of this **MUST** be a six-digit, case-insensitive hexadecimal
string preceded by the \'#\' character.

#### 1.2.9. Background Opacity

The backgroundOpacity denotes transparency that any closed captions
background will be rendered with. This **MUST** be a numeric value from
0 to 100.

#### 1.2.10. Text Align

The textAlign denotes horizontal alignment for any closed captions. This
**MUST** be one of the following values:

-   left

-   center

-   right

This is a default value that should only be used for rendering closed
captions that don't have any position or alignment data.

#### 1.2.11. Text Align Vertical

The textAlignVertical denotes vertical alignment for any closed
captions. This **MUST** be one of the following values:

-   top

-   middle

-   bottom

This is a default value that should only be used for rendering closed
captions that don't have any position or alignment data.

#### 1.2.12. Toggling closed captions

Enabling closed captions puts the device in a state where Apps
**SHOULD** be displaying closed captions. The language to be used is up
to the App itself, but it may use the Localization APIs for to determine
user preference, if desired.

Firebolt platforms **MUST** have a way to toggle this setting without
exiting the current App. This **MAY** be done via a physical remote
control unit button, or via an on-screen overlaid UI.

When a device switches from closed captions being disabled to enabled,
all running Apps that have registered for the
onClosedCaptionsSettingsChanged notification **MUST** be notified with
the entire updated ClosedCaptionsSettings object.

When enabling closed captions, there may be more than one text track
that is appropriate.

Apps **MAY** use the following guidelines for selecting which track to
render.

It is suggested but not required, that Apps render the first available
text track from this list:

-   Closed Captions with language matching the most recent selection in
    this session

-   Closed Captions with language matching Localization.language()

-   Closed Captions with language matching the video content

-   Other text track with language Localization.language()

-   Other text track with language matching the video content

#### 1.2.13. Changing closed captions styles

Changing closed captions styles updates the various style preferences
that Apps **MUST** respect when rendering captions. These styles are the
baseline styles and may be overridden for individual captions. Style
information that is packaged with the actual captions **MUST** override
the default styles here.

Firebolt platforms **MUST** have a way to modify these settings without
exiting the current App, via an on-screen overlaid UI. This UI **MAY**
be designed as a simple predefined set of styles for ease of use.

When the device closed captions style settings change, all running Apps
that have registered for the onClosedCaptionsSettingsChanged
notification **MUST** be notified with the entire updated
ClosedCaptionsSettings object.

### 1.3. Voice Guidance Settings

Voice guidance settings describe whether voice guidance is enabled, as
well as the user's preferred speed for the guidance voice.

The settings are represented by the VoiceGuidanceSettings object, which
has two fields:

| Field   | Description                               |
|---------|-------------------------------------------|
| enabled | Whether voice guidance should be enabled. |
| speed   | The preferred speed for guidance voice.   |

#### 1.3.1. Toggling voice guidance

Enabling voice guidance puts the device in a state where Apps **SHOULD**
be playing voice-overs for interactive UI elements as they are
highlighted with the directional buttons on the remote control unit.

Firebolt platforms **MUST** have a way to toggle this setting without
exiting the current App. This **MAY** be done via a physical remote
control unit button, or via an on-screen overlaid UI.

Firebolt platforms **MAY** use Localization.locale() to determine which
voice to use for voice guidance, for example to adopt a local accent.

When a device switches to voice guidance being disabled or enabled, all
running Apps that have registered for the onVoiceGuidanceSettingsChanged
notification **MUST** be notified with the entire updated
VoiceGuidanceSettings object.

#### 1.3.2. Changing voice guidance speed

Changing the voice guidance speed updates how fast any accessibility
voice-over speech should be played Apps **SHOULD** respect this when
playing accessibility related voice-overs.

This **MUST** be a floating point value from 0.1 to 10 inclusive. The
value 1 is the normal speed for the current voice, 0.5 is half speed, 2
is twice as fast, etc.

Firebolt platforms **MUST** have a way to modify this setting without
exiting the current App, via an on-screen overlaid UI.

When the device voice guidance speed settings change, all running Apps
that have registered for the onVoiceGuidanceSettingsChanged notification
**MUST** be notified with the entire updated VoiceGuidanceSettings
object.

### 1.4. Audio Description Settings

Audio description settings determine whether descriptive audio tracks,
which generally describe the video content, are enabled.

The settings are represented by the AudioDescriptionSettings object,
which has one field:

| Field   | Description                                   |
|---------|-----------------------------------------------|
| enabled | Whether audio descriptions should be enabled. |

If the enabled value has never been set, then it **MUST** default to
false.

#### 1.4.1. Toggling audio descriptions

Enabling audio descriptions puts the device in a state where Apps
**SHOULD** be playing descriptive audio tracks for any content that has
them available.

Firebolt platforms **SHOULD** have a way to toggle this setting without
exiting the current App. This **MAY** be done via a physical remote
control unit button, or via an on-screen overlaid UI.

Firebolt platforms **MAY** use Localization.language() to determine
which language to use for audio descriptions, if more than one language
is available.

Firebolt platforms **MUST** persist changes to this setting across
sessions and power cycles.

When a device switches to audio descriptions being disabled or enabled,
all running Apps that have registered for the
onAudioDescriptionSettingsChanged notification **MUST** be notified with
the entire updated AudioDescriptionSettings object.

### 1.5. Core SDK APIs

The following APIs are exposed by the Firebolt Core SDK as part of the
core:accessibility domain/module.

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, errors, and permissions.

#### 1.5.1. Closed Captions Settings

This is a property API that exposes a getter and subscriber for a
mutable system property.

The Accessibility.closedCaptionsSettings() method allows both getter and
notification-based access to the current closed captions settings.

When called without any parameters, the current ClosedCaptionsSettings
value **MUST** be returned.

When called with a single callback as a parameter, the SDK **MUST**
register to receive Accessibility.onClosedCaptionsSettingsChanged
notifications, and proxy them to the callback as they occur.

#### 1.5.2. Voice Guidance Settings

This is a property API that exposes a getter and subscriber for a
mutable system property.

The Accessibility.voiceGuidanceSettings() method allows both getter and
notification-based access to the current voice guidance settings.

When called without any parameters, the current VoiceGuidanceSettings
value **MUST** be returned.

When called with a single callback as a parameter, the SDK **MUST**
register to receive Accessibility.onVoiceGuidanceSettingsChanged
notifications, and proxy them to the callback as they occur.

#### 1.5.3. Audio Description Settings

This is a property API that exposes a getter and subscriber for a
mutable system property.

The Accessibility.audioDescriptionSettings() method allows both getter
and notification-based access to the current audio description settings.

When called without any parameters, the current AudioDescriptionSettings
value **MUST** be returned.

When called with a single callback as a parameter, the SDK **MUST**
register to receive Accessibility.onAudioDescriptionSettingsChanged
notifications, and proxy them to the callback as they occur.

### 1.6. Manage SDK APIs

The following APIs are exposed by the Firebolt Manage SDK as part of the
manage domain.

See the [Firebolt API
Documentation](https://developer.comcast.com/firebolt/core/sdk/latest/api/)
for details around syntax, errors, and permissions.

The following methods exist (let's agree before I type all the words for
each one) as get/set/subscribe

-   ClosedCaptions.enabled

-   ClosedCaptions.fontFamily

-   ClosedCaptions.fontSize

-   ClosedCaptions.fontColor

-   ClosedCaptions.fontEdge

-   ClosedCaptions.fontEdgeColor

-   ClosedCaptions.fontOpacity

-   ClosedCaptions.backgroundColor

-   ClosedCaptions.backgroundOpacity

-   ClosedCaptions.textAlign

-   ClosedCaptions.textAlignVertical

-   VoiceGuidance.enabled

-   VoiceGuidance.speed

-   AudioDescriptions.enabled

Sample Firebolt Request method and Response RPC messages, as supported
on X1/Reflex:

Request to fetch **VoiceGuidance** settings:

{\"jsonrpc\":\"2.0\",\"id\":9,\"method\":\"**accessibility.voiceGuidance**\",\"params\":{}}

Response:

{\"jsonrpc\":\"2.0\",\"id\":9,\"result\":{\"enabled\":false,\"speed\":50}}

Request to fetch **ClosedCaptions** settings:

{\"jsonrpc\":\"2.0\",\"id\":8,\"method\":\"**accessibility.closedCaptions**\",\"params\":{}}

Response:

{\"jsonrpc\":\"2.0\",\"id\":8,

\"result\":{\"**enabled**\":true,

\"**styles**\":

> {\"backgroundColor\":\"0xFF000000\",\"fontFamily\":\"default\",\"fontEdge\":\"none\",\"fontEdgeColor\":\"0xFFFFFFFF\",\"backgroundOpacity\":100,\"fontSize\":20,\"fontOpacity\":100,\"fontColor\":\"0xFFFFFFFF\"}

}

}

Note1: same data will be returned when these new methods are invoked:\
accessibility.**voiceGuidanceSettings** and
accessibility.**closedCaptionSettings**

Note2: When subscribed to receive any changes using the following
methods, above data will be returned:\
accessibility.**onVoiceGuidanceSettingsChanged** and
accessibility.**onClosedCaptionSettingsChanged**
