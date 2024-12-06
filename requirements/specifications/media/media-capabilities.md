# Media Capabilities Requirements

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Anthony Borzota | Comcast        |
| Jeremy LaCivita | Comcast        |
| Stuart Harris   | Sky            |
| Luc Kennedy-Lamb| Sky            |
| Farhan Mahmood  | Liberty Global |
| Joe Martin      | Comcast        |

## 1. Overview

Prior to playing media content, content partners want to understand the media-playing capabilities of a Firebolt device and its attached peripherals, such as displays, sound bars, and AV receivers.

This information can be used to determine the limits of the user's AV system, which would allow content partners to provide the user with the best-possible entertainment experience their AV system can support, while allowing them to avoid playing content the user cannot fully enjoy due to technological constraints.

This information may also provide content partners with valuable data about their user-base, which can assist them in making decisions about the types of content they make available to users in the future.

### 1.1. User Stories

As an app, I want to...

- Get the current audio output mode to determine the audio output capabilities of the device in its current configuration
- Get the actual audio output properties of the source device (regardless of any user-settings)
- Get the audio codecs supported on the platform in its current configuration
- Check whether Atmos content is supported in the device's current configuration before attempting to play such content
- Get the actual video output properties of the source device (regardless of any user-settings)
- Get the best possible video output mode supported on the platform in its current configuration
- Get the colorimetry values supported by the display
- Get the HDR formats supported on the platform in its current configuration
- Get the maximum color depth supported on the platform in its current configuration
- Get the native/maximum resolution of the display, in pixels
- Get the physical width and height of the display, in centimeters
- Get the video codecs supported on the platform in its current configuration
- Get the video modes (resolutions + frame rates) supported by the display
- Get notified that the video mode will be changed prior to that change taking effect

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Constants, Types, and Schemas](#3-constants-types-and-schemas)
  - [3.1. Audio Codecs](#31-audio-codecs)
  - [3.2. Video Codecs](#32-video-codecs)
  - [3.3. Dimensions](#33-dimensions)
  - [3.4. Video Modes](#34-video-modes)
  - [3.5. HDR Formats](#35-hdr-formats)
  - [3.6. Colorimetry](#36-colorimetry)
  - [3.7. Color Space \& Chroma Subsampling](#37-color-space--chroma-subsampling)
  - [3.8. Audio Output Mode](#38-audio-output-mode)
  - [3.8. Audio Output Protocol](#38-audio-output-protocol)
  - [3.9. Quantization Range](#39-quantization-range)
- [4. Media Capabilities](#4-media-capabilities)
  - [4.1. Supported Audio Codecs](#41-supported-audio-codecs)
  - [4.2. Supported Video Codecs](#42-supported-video-codecs)
  - [4.3. Atmos Support](#43-atmos-support)
  - [4.4. Color Depth](#44-color-depth)
  - [4.5. HDR Formats](#45-hdr-formats)
  - [4.6. Preferred Video Mode](#46-preferred-video-mode)
- [5. Display Support](#5-display-support)
  - [5.1. Display Size](#51-display-size)
  - [5.2. Colorimetry](#52-colorimetry)
  - [5.3. Native Resolution](#53-native-resolution)
  - [5.4. Supported Video Modes](#54-supported-video-modes)
- [6. Audio Output](#6-audio-output)
  - [6.1. Mode](#61-mode)
  - [6.2. Status](#62-status)
- [7. Video Output](#7-video-output)
  - [7.1. Status](#71-status)
  - [7.2. On Mode Will Change Event](#72-on-mode-will-change-event)

## 3. Constants, Types, and Schemas

### 3.1. Audio Codecs

The Firebolt `Media` module **MUST** have an `AudioCodec` enumeration:

| Name     | Description                                    |
| -------- | ---------------------------------------------- |
| `aac`    | Advanced Audio Coding                          |
| `ac3`    | Dolby Digital / Dolby Audio Codec 3            |
| `ac4`    | Dolby Audio Codec 4                            |
| `eac3`   | Dolby Digital Plus / Dolby Enhanced AC-3 / DD+ |
| `mpeg3`  | MPEG-1 Part 3 & MPEG-2 Part 3                  |
| `opus`   | IETF Opus                                      |
| `pcm`    | Pulse Code Modulation/WAVE                     |
| `truehd` | Dolby TrueHD / MLP                             |
| `vorbis` | Xiph.org Vorbis                                |

### 3.2. Video Codecs

The Firebolt `Media` module **MUST** have a `VideoCodec` enumeration:

| Name    | Description                                    |
| ------- | ---------------------------------------------- |
| `av1`   | AOMedia Video 1                                |
| `avc`   | Advanced Video Coding / MPEG-4 Part 10 (H.264) |
| `hevc`  | High Efficiency Video Coding (H.265)           |
| `mpeg1` | MPEG-1 Part 2 Visual                           |
| `mpeg2` | MPEG-2 Part 2 Visual                           |
| `vp8`   | Video Processor 8                              |
| `vp9`   | Video Processor 9                              |

### 3.3. Dimensions

The Firebolt `Types` module must have a `Dimensions` object of the following schema:

| Field    | Type     |
| -------- | -------- |
| `height` | `number` |
| `width`  | `number` |

### 3.4. Video Modes

For the purposes of the Firebolt API, a `VideoMode` shall be defined as the shorthand vertical resolution and frame rate of video content.

The Firebolt `Media` module **MUST** have a `VideoMode` enumeration:

- `480i`
- `480p`
- `576i25`
- `576p50`
- `576p60`
- `720p50`
- `720p60`
- `1080i50`
- `1080i60`
- `1080p24`
- `1080p25`
- `1080p30`
- `1080p50`
- `1080p60`
- `2160p24`
- `2160p25`
- `2160p30`
- `2160p50`
- `2160p60`
- `4320p50`
- `4320p60`
- `other`
- `unknown`

Any methods relating to the video mode (such as a device's video output mode) **MUST** return `Media.VideoMode` values.

### 3.5. HDR Formats

The Firebolt `Media` module **MUST** have an `HDRFormat` enumeration:

- `advancedHdr`
- `dolbyVision`
- `hdr10`
- `hdr10plus`
- `hlg`
- `none`
- `unknown`

### 3.6. Colorimetry

The Firebolt `Media` module **MUST** have a `Colorimetry` enumeration:

| Value        | Description                                           |
| ------------ | ----------------------------------------------------- |
| `BT2020cYCC` | Rec. ITU-R BT.2020 Y’cC’BCC’RC                        |
| `BT2020RGB`  | Rec. ITU-R BT.2020 R’G’B’                             |
| `BT2020YCC`  | Rec. ITU-R BT.2020 Y’C’BC’R                           |
| `defaultRGB` | Default chromaticity information of the display       |
| `ICtCp`      | Rec. ITU-R BT.2100                                    |
| `opRGB`      | IEC 61966-2-5; previously named `AdobeRGB`            |
| `opYCC601`   | IEC 61966-2-5 Annex A; previously named `AdobeYCC601` |
| `sRGB`       | IEC 61966-2-1                                         |
| `ST2113RGB`  | SMPTE ST 2113 R’G’B’; previously named `DCI-P3`       |
| `sYCC601`    | IEC 61966-2-1/Amendment 1                             |
| `xvYCC601`   | Standard Definition; based on IEC 61966-2-4           |
| `xvYCC709`   | High Definition; based on IEC 61966-2-4               |
| `unknown`    | Reserved for edge cases (no display, etc.)            |

> NOTE: The above values are based on the latest CTA-861 standard, and are subject to change to match this standard.

### 3.7. Color Space & Chroma Subsampling

The Firebolt `Media` module **MUST** have a `ColorSpace` enumeration:

| Name       | Chroma |
| ---------- | ------ |
| `RGB444`   | 4:4:4  |
| `YCbCr420` | 4:2:0  |
| `YCbCr422` | 4:2:2  |
| `YCbCr444` | 4:4:4  |
| `other`    |        |
| `unknown`  |        |

### 3.8. Audio Output Mode

The Firebolt `Media` module **MUST** have an `AudioMode` enumeration:

- `auto`
- `mono`
- `passthrough`
- `stereo`
- `surround`
- `unknown`

### 3.8. Audio Output Protocol

The Firebolt `Media` module **MUST** have an `AudioProtocol` enumeration:

> TODO: Fill this in/validate this enum

- `analog`
- `bluetooth`
- `hdmi`
- `spdif`

### 3.9. Quantization Range

The Firebolt `VideoOutput` module **MUST** have a `QuantizationRange` enumeration:

- `full`
- `limited`
- `unknown`

## 4. Media Capabilities

Apps need to know what type of media the device and its connected peripherals in their current configuration are together capable of playing.

To facilitate this, the `MediaCapabilities` module will provide convenience methods that encapsulate the media-playing capabilities of the device and its connected peripherals, including (but not limited to) displays, sound bars, and receivers.

### 4.1. Supported Audio Codecs

The `MediaCapabilities` module **MUST** have an `audioCodecs` method that returns an array of `Media.AudioCodec` values describing the audio codecs supported by the audio decoding device in its current configuration.

If the device is currently in `passthrough` audio mode, audio codecs supported by the audio sink **MUST** be returned, otherwise the audio codecs supported by the device **MUST** be returned.

This method **MUST** have a corresponding `onAudioCodecsChanged` event to notify listeners when the available audio codecs have changed.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:media-capabilities:info` capability.

```javascript
MediaCapabilities.audioCodecs()
//> [
//>   "aac",
//>   "ac3",
//>   "ac4",
//>   "eac3",
//>   "mpeg3",
//>   "pcm"
//> ]
```

### 4.2. Supported Video Codecs

The `MediaCapabilities` module **MUST** have an `videoCodecs` method that returns an array of `Media.VideoCodec` values describing the video codecs supported by the device.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:media-capabilities:info` capability.

```javascript
MediaCapabilities.videoCodecs()
//> [
//>   "av1",
//>   "avc",
//>   "hevc",
//>   "mpeg1",
//>   "mpeg2",
//>   "vp8",
//>   "vp9",
//>   "vp10"
//> ]
```

### 4.3. Atmos Support

The `MediaCapabilities` module **MUST** have an `atmosSupported` method that returns a boolean value denoting whether or not Dolby Atmos is supported by the audio decoding device in its current configuration.

This method **MUST** have a corresponding `onAtmosSupportedChanged` event to notify listeners if the support for Dolby Atmos has changed (such as when the audio sink configuration has been updated).

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:media-capabilities:info` capability.

```javascript
MediaCapabilities.atmosSupported()
//> true
```

### 4.4. Color Depth

The `MediaCapabilities` module **MUST** have a `colorDepth` method that returns an integer describing the maximum color depth commonly supported across the user's AV chain in its current configuration.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

This method **MUST** have a corresponding `onColorDepthChanged` event to notify listeners when the supported color depth has changed (such as when a new display has been connected).

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:media-capabilities:info` capability.

```javascript
MediaCapabilities.colorDepth()
//> 10
```

### 4.5. HDR Formats

The `MediaCapabilities` module **MUST** have an `hdrFormats` method that returns an array of `Media.HDRFormat` values describing the HDR capabilities commonly supported across the user's AV chain in its current configuration.

An empty array **MUST** be returned if no HDR formats are supported by the platform (such as when an SDR/non-HDR display is connected).

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

This method **MUST** have a corresponding `onHdrFormatsChanged` event to notify listeners when the supported HDR formats have changed (such as when a new display has been connected).

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:media-capabilities:info` capability.

```javascript
MediaCapabilities.hdrFormats()
//> ["dolbyVision", "hdr10", "hdr10plus", "hlg"]
```

### 4.6. Preferred Video Mode

The `MediaCapabilities` module **SHOULD** have a `preferredVideoMode` method that returns a `Media.VideoMode` value describing the best-possible video mode commonly supported across the user's AV chain in its current configuration.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

This method **MUST** have a corresponding `onPreferredVideoModeChanged` event to notify listeners when the preferred video mode has changed (such as when a new display has been connected).

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:media-capabilities:info` capability.

```javascript
MediaCapabilities.preferredVideoMode()
//> "2160p60"
```

## 5. Display Support

Apps need to know various capabilties of the currently connected or built-in display.

These will be surfaced in the `Display` module.

### 5.1. Display Size

The `Display` module **MUST** have a `size` method that returns a `Types.Dimensions` object describing the physical width and height of the display, in centimeters.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.size()
//> { "width": 157, "height": 91 }
```

### 5.2. Colorimetry

The `Display` module **MUST** have a `colorimetry` method that returns an array of `Media.Colorimetry` values describing the display's supported colorimetry values.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.colorimetry()
//> ["BT2020RGB", "BT2020YCC", "xvYCC601", "xvYCC709"]
```

### 5.3. Native Resolution

The `Display` module **MUST** have an `nativeResolution` method that returns a `Types.Dimensions` object describing the `width` and `height` of the display's native resolution as numbers, in pixels.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.nativeResolution()
//> { "width": 1920, "height": 1080 }
```

### 5.4. Supported Video Modes

The `Display` module **MUST** have a `videoModes` method that returns an array of `Media.VideoMode` values describing the video modes supported by the display.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.videoModes()
//> ["720p50", "720p60", "1080p50", "1080p60"]
```

## 6. Audio Output

Apps need to know various aspects of the audio system, such as which audio output mode is currently set.

These APIs will be surfaced in the `AudioOutput` module.

### 6.1. Mode

The `AudioOutput` module **MUST** include a `mode` method that returns a `Media.AudioMode` value describing the device's current audio output mode setting.

This method **MUST** have a corresponding `onModeChanged` event to notify listeners after a change to this property has been made and that change has taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:audio-output:mode` capability.

```javascript
AudioOutput.mode()
//> "stereo"
```

### 6.2. Status

The `AudioOutput` module **MUST** include a `status` method that returns an object describing properties of the device's current audio output.  In other words, properties returned by this method may not describe audio output settings, but may instead represent the actual, effective results of those settings.

This method **MUST** have a corresponding `onStatusChanged` event to notify listeners after a change to any properties have been made and that change has taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:audio-output:status` capability.

This method **MUST** return the following properties:

| Property   | Type                  |
| ---------- | --------------------- |
| `mode`     | `Media.AudioMode`     |
| `protocol` | `Media.AudioProtocol` |

```javascript
AudioOutput.status()
//> {
//>   "mode": "surround",
//>   "protocol": "value TBD"
//> }
```

## 7. Video Output

Apps need to know various aspects of the video output system, such as the current video mode/resolution.

These APIs will be surfaced in the `VideoOutput` module.

### 7.1. Status

The `VideoOutput` module **MUST** include a `status` method that returns an object describing properties of the device's current video output.  In other words, properties returned by this method may not describe video output settings, but may instead represent the actual, effective results of those settings.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

This method **MUST** have a corresponding `onStatusChanged` event to notify listeners after a change to any properties have been made and that change has taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:video-output:status` capability.

This method **MUST** return the following properties:

| Property            | Type                            |
| ------------------- | ------------------------------- |
| `colorDepth`        | `integer`                       |
| `colorimetry`       | `Media.Colorimetry`             |
| `colorSpace`        | `Media.ColorSpace`              |
| `frameRate`         | `number`                        |
| `hdrFormat`         | `Media.HDRFormat`               |
| `mode`              | `Media.VideoMode`               |
| `quantizationRange` | `VideoOutput.QuantizationRange` |
| `resolution`        | `Types.Dimensions`              |

```javascript
VideoOutput.status()
//> {
//>   "colorDepth": 10,
//>   "colorimetry": "BT2020YCC",
//>   "colorSpace": "YCbCr422",
//>   "frameRate": 60,
//>   "hdrFormat": "hdr10plus",
//>   "mode": "2160p60",
//>   "quantizationRange": "limited",
//>   "resolution": { "width": 3840, "height": 2160 }
//> }
```

### 7.2. On Mode Will Change Event

The `VideoOutput` module **MUST** have a `onModeWillChange` event returning a `Media.VideoModes` value that notifies listeners when a change to the device's video output mode setting has been made but before that change has taken effect.

Access to this event **MUST** require the `use` role of the `xrn:firebolt:capability:video-output:mode` capability.

```javascript
VideoOutput.listen('onModeWillChange', (mode) => {
  console.log(mode)
})
//> "2160p60"
```
