# Media Pipeline Requirements

Document Status: Working Draft

See [Firebolt Requirements Governance](./governance.md) for more info.

**NOTE**: Update this link based on your directory depth ^^

| Contributor         | Organization |
| ------------------- | ------------ |
| Lucien Kennedy-Lamb | Sky          |
| Bijal Shah          | Sky          |
| Yuri Pasquali       | Sky          |
| Stuart Pett         | Sky          |
| Wouter Meek         | Comcast      |
| Jeremy LaCivita     | Comcast      |
| Kevin Pearson       | Comcast      |
| Phillip Stroffolino | Comcast      |

## 1. Overview

Playback of audio/video media is a first-class concern for Firebolt. As
such, Firebolt must provide a consistent, secure Media Pipeline API for
sending audio and video streams from an app container out to a decoder
and CDM for content decryption, decoding, and rasterization.

Additionally, Firebolt browsers must leverage the same Media Pipeline
implementation as native apps, so that content plays back the same in
both environments and can have resources managed in the same way.

This is achieved with the open source [Rialto Media
Pipeline](https://github.com/rdkcentral/rialto) API and implementation:

TODO: we need a few additions to support Netflix:

**TODO**: the rest of these need to move to Rialto:


- Preferred resolution/framerate
- atmos lock
- loudness eq
The audioSettings **MUST** include an `atmosOutputLock` boolean property.

The audioSettings **MUST** include an `audioLoudnessEquivalence` boolean property.

The audioSettings API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioSettingsChanged` notification.

Use of the `audioSettings` and `onAudioSettingsChanged` APIs require access
to the `use` role of the `xrn:firebolt:capability:device:audio-settings` capability.

**TODO**: Netflix needs to be able to *set* atmosOutputLock...


![Diagram Description automatically
generated](../../../../requirements/images/specifications/media/media-pipeline/media/image1.png)

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Media Pipeline](#3-media-pipeline)
  - [3.1. Media Pipeline Commands](#31-media-pipeline-commands)
  - [3.2. MediaPipeline Notifications](#32-mediapipeline-notifications)
  - [3.3. Media Pipeline Management](#33-media-pipeline-management)
- [4. W3C Media APIs](#4-w3c-media-apis)
  - [4.1. MediaSource](#41-mediasource)
  - [4.2. MediaElement](#42-mediaelement)
- [5. Supported Media](#5-supported-media)
  - [5.1. Container formats](#51-container-formats)
  - [5.2. Video codecs](#52-video-codecs)
  - [5.3. Audio codecs](#53-audio-codecs)
- [6. Supported Decryption](#6-supported-decryption)
  - [6.1. DRM Key Systems](#61-drm-key-systems)
  - [6.2. Decryption Schemes](#62-decryption-schemes)

## 3. Media Pipeline

The Firebolt Media Pipeline consists of an API for passing audio & video
streams *out* of individual app containers *into* managed media sessions
that support decryption, decoding, and rasterization. Additionally there
is an API for sending notifications out of the decoder and into the app
container.

The goal of this abstraction is to decouple individual Firebolt Apps and
containers from the underlying implementations of these features.
Additionally, this abstraction allows for the same component to manage
media sessions in a consistent manner regardless of implementation.

To ensure consistency, all native containers, including browsers, that
run on Firebolt platforms **MUST** use Rialto as the only pipeline to
Media decoders and CDMs.

The Media Pipeline API uses a client-server model to allow Firebolt
devices to manage media pipeline resources and visibility. This enables
multiple media pipeline sessions to be running at once, even though they
will not all have access to the underlying decoder. Command messages are
passed using an efficient binary RPC protocol. Media data is passed
using memory shared by only the app container and its respective Rialto
session server.

![Timeline Description automatically
generated](../../../requirements/images/specifications/media/media-pipeline/media/image2.png)

### 3.1. Media Pipeline Commands

Media Pipeline commands go from the app to the Rialto Media Pipeline
server.

This section describes the use cases that the Rialto API solves. For
actual API semantics, please refer to the Rialto Github repository.

The MediaPipeline API **MUST** support pushing data into the Pipeline,
in response to a notification that more data is needed.

The MediaPipeline API **MUST** support informing the Pipeline that it
has reached the end of a stream and no more data is available.

The MediaPipeline API **MUST** support initializing (aka loading) a new
Media session, typically done before starting a new stream.

The MediaPipeline API **MUST** support attaching one video and one audio
source buffer.

The MediaPipeline API **MUST** support removing source buffers.

The MediaPipeline API **MUST** support pausing and playing.

The MediaPipeline API **MUST** support stopping playback, such that it
cannot be resumed without reinitializing.

The MediaPipeline API **MUST** support setting the playback rate.

The MediaPipeline API **MUST** support setting the current playback
position.

The MediaPipeline API **MUST** support setting the video location and
dimensions.

The MediaPipeline API **MUST** support dynamic audio decode switching to
support Netflix use cases.

### 3.2. MediaPipeline Notifications

Media Pipeline notifications come from the Rialto Media Pipeline server
to the app.

This section describes the use cases that the Rialto API solves. For
actual API semantics, please refer to the Rialto Github repository.

The MediaPipeline API **MUST** support notifying the app when more audio
or video data is needed in order for playback to continue without error.

The MediaPipeline API **MUST** support notifying the app when a need for
more audio or video data is no longer relevant, e.g. due to switching
buffers or stopping.

The MediaPipeline API **MUST** support notifying the app of the current
Media duration.

The MediaPipeline API **MUST** support notifying the app of the current
Media position.

The MediaPipeline API **MUST** support notifying the app of the current
native dimensions of the current Media.

The MediaPipeline API **MUST** support notifying the app of the current
buffer state, e.g. buffered, idle, error.

The MediaPipeline API **MUST** support notifying the app of the current
playback state, e.g. playing, paused, seeking, stopped.

The MediaPipeline API **MUST** support notifying the app whether the
current media contains video and/or audio data.

The MediaPipeline API **MUST** support notifying the app when frames of
video or samples of audio are dropped due to performance.

The MediaPipeline API **MUST** support notifying the app when EIA/CEA
608/708 closed caption data is extracted and ready for presentation.

### 3.3. Media Pipeline Management

Rialto also exposes a management API for deciding which Rialto session
is active and visible. The Firebolt Execution Environment, typically
Ripple interacts with this API as apps move in and out of focus.

![Diagram Description automatically
generated](../../../requirements/images/specifications/media/media-pipeline/media/image3.png)

**TODO**: add decode pool requirements, e.g. minimum decoders for a
Firebolt platform, etc. \-- This needs to be written out.

**TODO**: add colloquial description of API surface in Rialto Server
Manager. We need this written out for the management api.

## 4. W3C Media APIs

The Media Source API enables the entire functional scope of the W3C
MediaSource and MediaElement APIs, (e.g. MediaSource.addSourceBuffer,
video.src, video.play(), etc.)

Firebolt browsers will use Rialto to implement `MediaElement` and
`MediaSource` APIs.

### 4.1. MediaSource

Browser MediaSource APIs **MUST** be powered by Rialto. Higher level
concerns such as source buffer management, etc., are outside the scope
of this document.

When using MediaSource APIs, demuxing is the concern of the app, not the
browser.

![Graphical user interface, application, Teams Description automatically
generated](../../../requirements/images/specifications/media/media-pipeline/media/image4.png)

### 4.2. MediaElement

Browser Media Element implementations **MUST** support progressive
download and demuxing of the following media container formats:

-   Progressive MPEG4 video

-   Progressive MP3 audio

Demuxed segments **MUST** be sent to Rialto for decoding.

MediaElement implementations **MUST** not support additional formats,
e.g. HLS or DASH. These formats should be parsed and fetched by a player
implemented on top of MSE.

Legacy support for direct playback of HLS is outside the scope of this
document.

![Graphical user interface, application Description automatically
generated](../../../requirements/images/specifications/media/media-pipeline/media/image5.png)

## 5. Supported Media

The Rialto Media Pipeline supports the following media types.

### 5.1. Container formats

The Media Pipeline **MUST** support the following container formats:

-   Demuxed MP4 audio and video streams, via MSE

-   MPEG 1 for audio-only playback (progressively fetched upstream)

### 5.2. Video codecs

The Media Pipeline **MUST** support the following video codecs:

-   AVC

-   HEVC

-   VP9

-   H.264

### 5.3. Audio codecs

The Media Pipeline **MUST** support the following audio codecs:

-   HE-AAC

-   AAC-LC

-   HE-AACv2

-   MPEG-1 Audio Layer III (for audio-only media)

## 6. Supported Decryption

The Rialto Media Pipeline supports the following media decryption types.

### 6.1. DRM Key Systems

-   Widevine

-   PlayReady

-   *I know there\'s **legacy use cases**\... do we call them out?*

### 6.2. Decryption Schemes

-   CMAF CBCS decryption
