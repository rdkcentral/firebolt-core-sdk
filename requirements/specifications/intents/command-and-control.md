# Command and Control Intents

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor      | Organization |
| ---------------- | ------------ |
| Saras Arveti     | Comcast      |
| Eileen Bengston  | Comcast      |
| Michael Driscoll | Comcast      |
| Simon Grist      | Sky          |
| Jeremy LaCivita  | Comcast      |

## 1. Overview

This document outlines several basic Intents for controlling a Firebolt
compliant device.

### 1.1. Message.type

Message.type should be a useful grouping to bucket related intents
together for easier forwarding to appropriate components.

## 2. Table of Contents
- [1. Overview](#1-overview)
  - [1.1. Message.type](#11-messagetype)
- [2. Table of Contents](#2-table-of-contents)
- [3. Control Intents](#3-control-intents)
  - [3.1. Power Intent](#31-power-intent)
  - [3.2. Volume Intents](#32-volume-intents)
    - [3.2.1. Volume Intent](#321-volume-intent)
    - [3.2.2. Mute Intent](#322-mute-intent)
  - [3.3. Channel Intent](#33-channel-intent)
  - [3.4. Media Control Intents](#34-media-control-intents)
    - [3.4.1. Pause, Play, Replay, and Stop Intents](#341-pause-play-replay-and-stop-intents)
    - [3.4.2. Seek Intent](#342-seek-intent)
    - [3.4.3. Fast-forward and Rewind Intents](#343-fast-forward-and-rewind-intents)
  - [3.5. Accessibility Intents](#35-accessibility-intents)
    - [3.5.1. Closed Captions Intent](#351-closed-captions-intent)
    - [3.5.2. Voice Guidance Intent](#352-voice-guidance-intent)
    - [3.5.3. Audio Descritions Intent](#353-audio-descritions-intent)
    - [3.5.4. High Contrast Intent](#354-high-contrast-intent)
    - [3.5.5. Screen Magnification Intent](#355-screen-magnification-intent)
  - [3.6. Interaction Intents](#36-interaction-intents)
    - [3.6.1. Focus Intent](#361-focus-intent)
    - [3.6.2. Select Intent](#362-select-intent)
    - [3.6.3. Scroll Intent](#363-scroll-intent)
    - [3.6.4. Back Intent](#364-back-intent)
    - [3.6.5. Exit Intent](#365-exit-intent)
- [4. Launch Intents](#4-launch-intents)
  - [4.1. Content Discovery Launch Intents](#41-content-discovery-launch-intents)
  - [4.2. Device Settings Launch Intent](#42-device-settings-launch-intent)

## 3. Control Intents

Control intents are for user intentions that will be needed regardless
of whether there are any apps installed.

For example, these intents are all useful even if only using your TV
with a single HDMI input, and not for apps.

### 3.1. Power Intent

This intent allows a user to turn the device on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:power",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "power",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:power",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "power",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Additionally, this intent allows a user to set a timer for turning off
the power, aka a "sleep timer."

This is handled by the optional field delay, which is measured in whole
seconds:

```json
{
    "type": "xrn:firebolt:intent:platform:power",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "power",
        "data": {
            "value": true | false,
            "delay": 3600
        },
        "context": {
            "source": "voice"
        }
    }
}
```

To cancel a sleep timer, send a new intent without a delay.

While it may not be implemented by all platforms, this could also be
used to turn on the TV with a timer.

### 3.2. Volume Intents

Volume Intents control the audio level of the device.

#### 3.2.1. Volume Intent

This intent allows setting the volume to an absolute or relative value.

```json
{
    "type": "xrn:firebolt:intent:platform:volume",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "volume",
        "data": {
            "value": 70
        },
        "context": {
            "source": "VOICE"
        }
    }
}

```

The value is an integer value from 0 to 100.

This intent also supports relative volume changes, by providing the
optional relative field:

```json
{
    "type": "xrn:firebolt:intent:platform:volume",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "volume",
        "data": {
            "value": -10,
            "relative": true
        },
        "context": {
            "source": "VOICE"
        }
    }
}

```

The value is a positive or negative integer that is relative to a scale
of 0-100.

Firebolt will not support complicated relative changes, e.g. "Set the
volume to 50% *of what it currently is\...*"

Firebolt uses a size of 0-100 for this intent. It\'s up to each voice
integration if it wants to convert "5" to "50%" before generating
the intent, but convenience transformations like this are recommended.

Whether or not a TV uses logarithmic or linear scale is irrelevant to
the VolumeIntent schema.

#### 3.2.2. Mute Intent

This intent allows the user to mute or unmute the device.

```json
{
    "type": "xrn:firebolt:intent:platform:volume",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "mute",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "VOICE"
        }
    }
}
```

### 3.3. Channel Intent

For tuning to a specific channel, either OTA or in-app, see [Tune
Intents](./tune.md).

The intents in this section are for relative next/previous channel user
intentions and are a separate type of Intent. This allows each app to
decide what "channel" means. For example, an App might simply take you
to the next section/genre if it doesn\'t have linear streams in it\'s
catalog.

The goal of the action property to is tell the client how to parse the
Intent, so overloading the tune intent with a different structure is not
desirable.

Also,
"tune" inherently means to zero in on a specific part of a
scale, e.g. tuning a harp.

For relative "channel surfing" we\'ll use the more content-centric
action "channel" which will also align with non-linear apps that want
to leverage the channel up/down intent.

The Channel Intent allows a user to scan "channels" in an app (or
actual OTA channels if not in an app).

Users can scan to the next or previous channel. For scanning to the most
recent, i.e. "Last" channel, see [Interaction
Intent
](#interaction-intents).

```json
{
    "type": "xrn:firebolt:intent:platform:channel",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "channel",
        "data": {
            "value": "next" | "previous"
        },
        "context": {
            "source": "voice"
        }
    }
}

```

The value property MUST always be "next" or "previous". These are
chosen over up/down since not all use cases will be numeric.

Since this intent is always relative to the current app, there is no
need for an appId.

If this Intent needs to be passed to the current app, it can be passed
as-is, via the Discovery. onNavigateTo API, or a simulated RCU press of
one of the channel up/down buttons.

### 3.4. Media Control Intents

#### 3.4.1. Pause, Play, Replay, and Stop Intents

These intents allow the user to pause and resume playback of the current
Media: 

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "pause" | "play" | "replay" | "stop",
        "context": {
            "source": "voice"
        }
    }
}
```

If the action is pause, then the currently playing media should be
paused, with the frames on-screen and the video decoder ready to resume.

If the action is play, and the current media is paused, then the
currently paused media should resume.

If the action is play, and there is something playbable selected, then
playback of the selected asset should be initiated.

If the action is replay, then the currently paused or playing media should restart
from the beginning. This should work even if the decoder has finished,
and its resources have been released.

If the action is stop, then the currently playing media should be
stopped, frames removed from the screen, and any decoder resources
should be released.

#### 3.4.2. Seek Intent

The seek intent allows users to jump to a relative or absolute position
in the currently playing media.

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "seek",
        "data": {
            "seconds": 3600
        },
        "context": {
            "source": "voice"
        }
    }
}
```

The seconds value is a positive integer representing where to seek.

This intent also supports relative seeking, by providing the optional
relative field:

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "seek",
        "data": {
            "seconds": -30,
            "relative": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

For relative seeking, the seconds value may be a positive or negative value.

If a relative seek intent with a seconds value of `0` is received, the platform **SHOULD** ignore it, rather than rebuffering at the current position.

#### 3.4.3. Fast-forward and Rewind Intents

These intents allow users to fast-forward or rewind:

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "fast-forward" | "rewind",
        "data": {
            "speed": 2.5
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Speed is a float in the range of 0 (non-includsive) to 10 (inclusive),
with values between 0 and 1 denoting slow motion.

It is a device-level decision how to implement different speeds, however
actual fast playback (with audio) should be used where possible and
reasonable, e.g. a speed of 1.5 should actually be playing the video w/
sync\'d audio, while a speed of 10 will likely be using iframes and not
have audio. For rewind it is not important, and likely undesirable, to
provide audio.

If speed is not provided then the device should cycle through a range
of speeds defined by the device. This range of speeds **COULD** include
the value `1` so that users can get back to normal speed if desired.

### 3.5. Accessibility Intents

These intents manipulate accessibility features on the device.

#### 3.5.1. Closed Captions Intent

This intent allows a user to turn closed captions on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "closed-captions",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "closed-captions",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.5.2. Voice Guidance Intent

This intent allows a user to turn voice guidance on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "voice-guidance",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "voice-guidance",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

The intent **MAY** specify `speed` `number` property that specifies a speed from 0 to 10:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "voice-guidance",
        "data": {
            "speed": 2
        },
        "context": {
            "source": "voice"
        }
    }
}
```

When providing a `speed` this intent **MAY** also set the `relative` property to `true` denoting an increase or decrease in speed. The speed value may be between -5 and 5 inclusive:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "voice-guidance",
        "data": {
            "speed": -1,
            "relative": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Finally, the intent **MAY** specify a `verbosity` property, which **MUST** use one of the following values is provided:

| Value  | Description |
|--------|-------------|
| `low`  | to select shorter response, less context, and less detail; can use abbreviations and can selectively skip words  |
| `high` | to select longer response, more context, and more detail; full comprehensive readout and explicit reflection of what is seen on screen |

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "voice-guidance",
        "data": {
            "value": true,
            "verbosity": "low"
        },
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.5.3. Audio Descritions Intent

This intent allows a user to turn audio descriptions of content on or off.


```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "audio-descriptions",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

This intent may specify a language:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "audio-descriptions",
        "data": {
            "value": true,
            "language": "eng"
        },
        "context": {
            "source": "voice"
        }
    }
}
```

The `language` must be a three character ISO 639 1/2 code, e.g. `eng`.

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "audio-descriptions",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.5.4. High Contrast Intent

This intent allows a user to turn high contrast mode on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "high-contrast",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "high-contrast",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.5.5. Screen Magnification Intent

This intent allows a user to turn screen magnification on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "screen-magnification",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "screen-magnification",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Finally, this intent may specify a magnification scale as a number:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "screen-magnification",
        "data": {
            "scale": 2.5
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Setting the scale to `1` turns off magnification. Setting the scale to a value greater than 1 turns on magnification.

Even if a Firebolt platform does not support specifying the numeric scale, it **MUST** turn magnifacation on and off based on them.

If the intent has the `toggle` property, then it **MUST NOT** have the `scale` or `value` property.

If the intent has the `value` property, then it **MUST NOT** have the `toggle`.

### 3.6. Interaction Intents

Interaction Intents allow for voice (or other upstream intent service)
to control an on-screen UI without need for a keyboard or remote.

#### 3.6.1. Focus Intent

The Focus Intent allows users to move the focus / cursor
up/down/left/right:

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "focus",
        "data": {
            "direction": "up" | "down" | "left" | "right"
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Note that this does not give focus to a particular app, which is handled
by the "launch" action.

These Intents will generate appropriate HTML browser keyCode events to
facilitate up/down/left/right key presses.

#### 3.6.2. Select Intent

The select intent allows users to tell an app select, e.g.,
"click" on
whatever is focused. This is a platform-level intent that effectively
sends the "Ok" or "Select" key to the current app.

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "select",
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.6.3. Scroll Intent

The Scroll Intent allows users to move the current view port
up/down/left/right:

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "scroll",
        "data": {
            "direction": "up" | "down" | "left" | "right",
            "unit": "page" | "line" | "percent"
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Both `direction` and `unit` are required.

These Intents will generate appropriate browser / DOM scrolling
operations that don\'t require custom APIs.

#### 3.6.4. Back Intent

The back intent allows users to tell an app go to "back" like a
browser. This is a platform-level intent and will initiate a browser
back flow for web apps. For native apps, this will be converted to an
app Navigation Intent by the client and surfaced through the navigateTo
API.

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "back",
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.6.5. Exit Intent

The exit intent allows users to tell an app close. This is a
platform-level intent and will simply move the current app into the
inactive state.

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "exit",
        "context": {
            "source": "voice"
        }
    }
}
```

## 4. Launch Intents

If a Firebolt app wants to launch the main or settings experience of the device, it can use one of the following abstract appIds with the `launch` intent.

### 4.1. Content Discovery Launch Intents

The following section IDs will be used, with the Firebolt application
type as the target App ID:

`xrn:firebolt:application-type:main`

### 4.2. Device Settings Launch Intent

To launch the settings UI, a Launch Intent will be used, with the
Firebolt application type:

`xrn:firebolt:application-type:settings`
