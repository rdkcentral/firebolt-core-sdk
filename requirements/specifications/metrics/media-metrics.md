# Context Parameters
Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor                | Organization       |
| -------------------------- | ------------------ |
| Jeremy LaCivita            | Comcast            |
| Bertwin Wolf               | Sky                |
| Peter Yu                   | Comcast            |

## 1. Overview
This document outlines a set of audio / video quality of service metrics APIs.

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Content Metrics](#3-content-metrics)
  - [3.1. Content Start](#31-content-start)
  - [3.2. Content Stop](#32-content-stop)
- [4. Media Metrics](#4-media-metrics)
  - [4.1. Load Start](#41-load-start)
  - [4.2. Play](#42-play)
  - [4.3. Playing](#43-playing)
  - [4.4. Pause](#44-pause)
  - [4.5. Waiting](#45-waiting)
  - [4.6. Progress](#46-progress)
  - [4.7. Seeking](#47-seeking)
  - [4.8. Seeked](#48-seeked)
  - [4.9. Rate Change](#49-rate-change)
  - [4.10. Rendition Change](#410-rendition-change)
  - [4.11. Ended](#411-ended)
  - [4.12. Error](#412-error)
- [Discovery Metrics](#discovery-metrics)
  - [Watched](#watched)

## 3. Content Metrics
The term "content" is used to denote *any* type of primary content that a user could be engaged in, e.g. a video game, a live broadcast, or a pre-recorded video presentation.

### 3.1. Content Start
The `Metrics` module **MUST** include a `startContent` API so that an app may report when the user is engaged in "primary content."

The `startContent` API **MUST** have an optional `entityId` parameter for the app to specify which content is being started.

The remainder of this section outlines guidelines that apps should consider when calling `startContent`.

In order for content to be considered started, the user **SHOULD** have requested it through some explicit interaction with the app.

If an app automatically starts some default content, then the act of launching the app to the foreground **MAY** be considered an explicit interaction to start the content.

An app **SHOULD** differentiate, as appropriate, between previewing content currently in focus in a browse experience versus content the user is truly engaged with.

Once content has been identified to be started, apps **SHOULD** wait until any loading is complete before calling `startContent`.

If the content is streaming media content, and will leverage the Media Metrics APIs, then `startContent` **SHOULD** be called immediately before the first `mediaPlaying` call.

If content requires user interaction before starting, e.g. a prompt to select language, region, game difficulty, etc, apps **SHOULD** wait until all of such prompts are completed before calling `startContent`.

### 3.2. Content Stop
The `Metrics` module **MUST** include an `stopContent` API so that an app may report when the user finished being engaged in "primary content."

The `stopContent` API **MUST** have an optional `entityId` parameter for the app to specify which content is being stopped.

The remainder of this section outlines guidelines that apps should consider when calling `stopContent`.

In order for content to be considered stopped, it **MUST** have previously been started within the app's current lifecycle.

Content **MAY** be stopped explicitly by the user, or automatically by the app.

The `stopContent` API **SHOULD** be called after *all* `media*` APIs.


## 4. Media Metrics

The term "media" is used to denote primary content that is either a live, linear, or pre-recorded audio video content that can be played using the provided media pipeline of the device.

Switching assets during playback, e.g. freezing the primary content in order to load and play an advertisement 

### 4.1. Load Start
The `Metrics` module **MUST** include a `mediaLoadStart` API for denoting when the "initial request" (see below) for the media asset is made, so that the media load time may be calculated.

The `mediaLoadStart` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog is being loaded.

The remainder of this section outlines guidelines that apps should consider when calling `mediaLoadStart`.

The "initial request" for the media **SHOULD** be the earliest possible request made for a *standard* media format, e.g. an HLS or DASH manifest,  MPEG4 or MP3 file.

Bespoke calls to a content management, digital rights management, or other business / discovery logic **MAY** happen before the media starts to play, but **SHOULD NOT** be considered the "initial request."

The "initial request" **MAY** be TCP/IP, file-system, or bytes embedded into the application, e.g. [Data URI](https://datatracker.ietf.org/doc/html/rfc2397).

The `mediaLoadStart` API **SHOULD** only be called once for the first asset loaded as part of the playback experience, which could be the main asset, an advertisement, or a short branding clip.

The `mediaLoadStart` API **SHOULD NOT** be called again when switching assets during playback, e.g. switching from the primary content to load and play an advertisement.

### 4.2. Play
The `Metrics` module **MUST** include a `mediaPlay` API for denoting when the "intent to play" the media happens (see below), so that the platform knows when the user is expecting media to be playing.

The `mediaPlay` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog is expected to play.

The remainder of this section outlines guidelines that apps should consider when calling `mediaPlay`.

The `mediaPlay` API **SHOULD** be called when the initial or subsequent "intent to play" occurs.

Given the player is configured to autoplay, then the initial "intent to play" **SHOULD** be immediately before `mediaLoadStart`.

Given the player is not configured to autoplay, then the initial "intent to play" **SHOULD** be immediately before instructing the player to start.

The `mediaPlay` API **SHOULD** also be called when a subsequent "intent to play" occurs, e.g. unpausing content that was previously paused.

The `mediaPlay` API **SHOULD NOT** be used when playback resumes after an interuption, e.g. buffering.

The `mediaPlay` API **SHOULD NOT** be called when switching assets during playback, e.g. switching back to the primary content after an advertisement.

The `mediaPlay` API **SHOULD NOT** be called when switching renditions during playback, e.g. switching from one HLS bitrate to another.

### 4.3. Playing
The `Metrics` module **MUST** include a `mediaPlaying` API for denoting when the media is actually playing, i.e. frames are being rasterized by the media pipeline.

The `mediaPlaying` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog is playing.

The remainder of this section outlines guidelines that apps should consider when calling `mediaPlaying`.

The `mediaPlaying` API **SHOULD** be called when the media pipeline confirms that frames of the media are actually being rasterized to denote a change in the playing state, i.e. the media was previously not playing (due to being paused, waiting, or not yet started) and has now started or resumed playing.

The `mediaPlaying` API **SHOULD NOT** be called when switching assets during playback, e.g. switching back to the primary content after an advertisement.

The `mediaPlaying` API **SHOULD NOT** be called when switching renditions during playback, e.g. switching from one HLS bitrate to another, unless the switch resulted in a `mediaWaiting` due to interupted playback.

The `mediaPlaying` API **SHOULD NOT** be called when switching from trick play back to normal play, unless the switch resulted in a `mediaWaiting` due to interupted playback.

Once called, the `mediaPlaying` API **SHOULD NOT** be called again unless a `mediaPlay`, `mediaPause`, `mediaWaiting`, or `mediaSeeking` call has been made since.

### 4.4. Pause
The `Metrics` module **MUST** include a `mediaPause` API for denoting when the media stops playing, i.e. frames are no longer being rasterized by the media pipeline, due to an "intent to pause" (see below).

The `mediaPause` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog is paused.

The remainder of this section outlines guidelines that apps should consider when calling `mediaPause`.

The `mediaPause` API **SHOULD** be called when an "intent to pause" occurs. An "intent to pause" is either an explicit user intent, e.g. clicking a pause control, an indirect user action, e.g. opening a settings UX, or app business logic, e.g. an overlay display advertisement is displayed over the content.

The `mediaPause` API **SHOULD NOT** be called to denote an unexpected interuption, e.g. buffering or other non-user, non-business logic reasons that frames might stop rasterizing.

The `mediaPause` API **SHOULD NOT** be called when switching assets during playback, e.g. switching from the primary content to play an advertisement, unless the advertisment is loaded into a paused state and requires user interaction to play.

The `mediaPause` API **SHOULD NOT** be called when switching renditions during playback, e.g. switching from one HLS bitrate to another, unless the switch resulted in a `mediaWaiting` due to interupted playback.

The `mediaPause` API **SHOULD NOT** be called when switching to trick play from normal play.

Once called, the `mediaPause` API **SHOULD NOT** be called again unless a `mediaPlay` call has been made since.

### 4.5. Waiting
The `Metrics` module **MUST** include a `mediaWaiting` API for denoting when the media stops playing, i.e. frames are no longer being rasterized by the media pipeline, due to an unexpected interuption (see below), e.g. buffering.

The `mediaWaiting` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog has been interrupted.

The remainder of this section outlines guidelines that apps should consider when calling `mediaWaiting`.

The `mediaWaiting` API **SHOULD** be called when an "unexpected interruption" occurs. An "unexpected interruption" is due to underlying physical resources such as network, CPU, or even software bugs, e.g. buffering or other non-user, non-business logic reasons that frames might stop rasterizing.

The `mediaWaiting` API **SHOULD NOT** be called when an "intent to pause" occurs. An "intent to pause" is either an explicit user intent, e.g. clicking a pause control, an indirect user action, e.g. opening a settings UX, or app business logic, e.g. an advertisement is displayed over the content.

The `mediaWaiting` API **SHOULD NOT** be called due to the initial "[intent to play](#42-play)."

Once called, the `mediaWaiting` API **SHOULD NOT** be called again unless a `mediaPlay` call has been made since.

### 4.6. Progress
The `Metrics` module **MUST** include a `mediaProgress` API for denoting playback progress of the media.

The `mediaProgress` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog the progress is from.

The `mediaProgress` API **MUST** have a required `progress` parameter denoting how much progress has been made.

The remainder of this section outlines guidelines that apps should consider when calling `mediaProgress`.

The `mediaProgress` API **SHOULD** be called when playback progress occurs at a rate of roughly once per 60 seconds.

The `mediaProgress` API **SHOULD NOT** be called after playback stops, e.g. while paused or waiting.

The `mediaProgress` API **SHOULD** be called with an up-to-date `progress` value right before any `mediaPause` call.

The `progress` value **SHOULD** be a number greater than 0 and less than 1 denoting the percent of the content that progress has reached, if the duration of the content is static and known, e.g. VOD content.

The `progress` value **SHOULD** be an integer number of secionds from 1 to 86400 denoting the number of seconds from the "beginning" of the content that progress has reached, if the duration of the content is dynamic or not known, e.g. live content.

The "beginning" of the content **SHOULD** be considered as the start of the broadcast/event/etc., if known, otherwise it **MAY** be the start of the available media, e.g available on a CDN.

The `progress` value **SHOULD** jump up or down based on seeking, etc.

### 4.7. Seeking
The `Metrics` module **MUST** include a `mediaSeeking` API for denoting an "intent to seek" into the media.

The `mediaSeeking` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog the seek is occuring in.

The `mediaSeeking` API **MUST** have a required `target` parameter denoting the seek destination.

The remainder of this section outlines guidelines that apps should consider when calling `mediaSeeking`.

The `mediaSeeking` API **SHOULD** be called when an "intent to seek" occurs, e.g. the user or the app's business logic initiats a seek.

The `mediaSeeking` API **SHOULD** be called for each user intention to seek, even those that may be ignored or cancelled due to rapid successive user interactions.

The `target` value **SHOULD** be a number greater than 0 and less than 1 denoting the percent of the content intended to seek to, if the duration of the content is static and known, e.g. VOD content.

The `target` value **SHOULD** be an integer number of secionds from 1 to 86400 denoting the number of seconds from the "beginning" of the content intended to seek to, if the duration of the content is dynamic or not known, e.g. live content.

The "beginning" of the content **SHOULD** be considered as the start of the broadcast/event/etc., if known, otherwise it **MAY** be the start of the available media, e.g available on a CDN.

### 4.8. Seeked
The `Metrics` module **MUST** include a `mediaSeeked` API for denoting a successfully completed seek into the media.

The `mediaSeeked` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog the seek is occuring in.

The `mediaSeeked` API **MUST** have a required `position` parameter denoting the position resulting from the seek operation, which may be different than the target from `mediaSeeking` due to keyframes, etc.

The remainder of this section outlines guidelines that apps should consider when calling `mediaSeeked`.

The `mediaSeeked` API **SHOULD** be called when an "intent to seek" is successfully fulfilled and right before `mediaPlaying` is called due to the seek operation resulting in playback.

The `mediaSeeked` API **SHOULD NOT** be called for any cancelled or ignored intents to seek, to ensure that every `mediaSeeked` correlates to the preceding `mediaSeeking` call.

The `position` value **SHOULD** be a number greater than 0 and less than 1 denoting the percent of the content intended to seek to, if the duration of the content is static and known, e.g. VOD content.

The `position` value **SHOULD** be an integer number of secionds from 1 to 86400 denoting the number of seconds from the "beginning" of the content intended to seek to, if the duration of the content is dynamic or not known, e.g. live content.

The "beginning" of the content **SHOULD** be considered as the start of the broadcast/event/etc., if known, otherwise it **MAY** be the start of the available media, e.g available on a CDN.

### 4.9. Rate Change
The `Metrics` module **MUST** include a `mediaRateChanged` API for denoting a change to the playback rate, e.g. going from 1x to 2x playback speed.

The `mediaRateChanged` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog the seek is occuring in.

The `mediaRateChanged` API **MUST** have a required `rate` parameter denoting the new playback rate.

The remainder of this section outlines guidelines that apps should consider when calling `mediaRateChanged`.

The `mediaRateChanged` API **SHOULD** be called when the playback rate of the content is explicitly changed for any reason, user-initiated or otherwise.

The `mediaRateChanged` API **SHOULD** be called regardless of whether the rate change is due to the media pipeline rasterizing frames at a different rate, or due to a simulated rasterization, e.g. "trick play" with I-frames.

### 4.10. Rendition Change
The `Metrics` module **MUST** include a `mediaRenditionChanged` API for denoting a change to rendition, e.g. bitrate or dimension changes for quality.

The `mediaRenditionChanged` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog the seek is occuring in.

The `mediaRenditionChanged` API **MUST** have a required `bitrate` number parameter denoting the new bitrate.

The `mediaRenditionChanged` API **MUST** have a required `width` number parameter denoting the new width.

The `mediaRenditionChanged` API **MUST** have a required `height` number parameter denoting the new height.

The `mediaRenditionChanged` API **MUST** have an optional `profile` string parameter with a description of the new profile, e.g. 'HDR', etc.

The remainder of this section outlines guidelines that apps should consider when calling `mediaRenditionChanged`.

The `mediaRenditionChanged` API **SHOULD** be called when the stream of bytes being sent to the media pipeline changes, e.g. an HLS ABR change.

The `mediaRenditionChanged` API **SHOULD** be called regardless of whether the rate change is due to the user selecting a higher quality or an automatic change for QoS reasons.

### 4.11. Ended
The `Metrics` module **MUST** include a `mediaEnded` API for denoting when the media reaches the natural end, from the user's perspective.

The `mediaEnded` API **MUST** have a required `entityId` parameter to specify what entity from the app has ended.

The remainder of this section outlines guidelines that apps should consider when calling `mediaEnded`.

The `mediaEnded` API **SHOULD** be called when the media reaches the end of a "predetermined playback experience."

A "predetermined playback experience" **COULD** be the end of all VOD assets in the experience playlists, including advertisements, etc.

A "predetermined playback experience" **COULD** be reaching a program boundary in a linear or live stream.

A "predetermined playback experience" **COULD** be reaching then end of a live stream.

Running out of frames unexpectedly **SHOULD NOT** be considered a "predetermined playback experience."

The `mediaEnded` API **SHOULD NOT** be called again unless a `mediaPlay` call has been made since.

The `mediaEnded` API **SHOULD NOT** be used when the user stops or cancels media that is not at the end.

### 4.12. Error
The `Metrics` module **MUST** include a `error` API for denoting when an unrecoverable error with the media occurs and playback will be cancelled, e.g. after the initial `mediaPlaying` or fail to begin, e.g. before.

The `error` API **MUST** have a required `entityId` parameter to specify what entity from the app has had an error.

The `error` API **MUST** have a required `type` string parameter.

The `type` parameter **SHOULD** always be set to `media` for media-related errors.

The remainder of this section outlines guidelines that apps should consider when calling `error`.

The `error` API **SHOULD** be called whenever the app decides to cancel media playback due to an unrecoverable error.

## Discovery Metrics

### Watched
The `Discovery` module **MUST** include a `watched` API for denoting that .

The `watched` API **MUST** have a required `entityId` parameter to specify what entity from the app catalog the progress is from.

The `watched` API **MUST** have an optional `completed` parameter to specify whether or the entity has played back with enough progress that it would not be offered in a "resume" list inside of the app.

The `watched` API **MUST** have a required `progress` parameter denoting how much progress has been made.

The remainder of this section outlines guidelines that apps should consider when calling `watched`.

The `watched` API **SHOULD** be called when playback progress occurs at a rate of roughly once per 60 seconds.

The `watched` API **SHOULD NOT** be called after playback stops, e.g. while paused or waiting.

The `watched` API **SHOULD** be called with an up-to-date `progress` value right before any `mediaPause` call.

The `progress` value **SHOULD** be a number greater than 0 and less than 1 denoting the percent of the content that progress has reached, if the duration of the content is static and known, e.g. VOD content.

The `progress` value **SHOULD** be an integer number of secionds from 1 to 86400 denoting the number of seconds from the "beginning" of the content that progress has reached, if the duration of the content is dynamic or not known, e.g. live content.

The "beginning" of the content **SHOULD** be considered as the start of the broadcast/event/etc., if known, otherwise it **MAY** be the start of the available media, e.g available on a CDN.

The `progress` value **SHOULD** jump up or down based on seeking, etc.
