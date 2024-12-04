# HDMIInput

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor         | Organization   |
| ------------------- | -------------- |
| Jeremy LaCivita     | Comcast        |
| Lucien Kennedy-Lamb | Sky            |

## 1. Overview
This document describes the requirements for managing HDMI inputs on a Firebolt device. hese APIs are for managing the HMDI inputs of a device. All TVs have HDMI inputs, whereas only certain STBs have HDMI inputs.

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt), specifically:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. All Ports](#3-all-ports)
- [4. Single Port](#4-single-port)
- [5. Port Connection Notification](#5-port-connection-notification)
- [6. Port Signal Notification](#6-port-signal-notification)
- [7. EDID Version](#7-edid-version)
- [8. Low Latency](#8-low-latency)
  - [8.1. Low Latency Mode](#81-low-latency-mode)
    - [8.1.1. Low Latency Mode Notification](#811-low-latency-mode-notification)
  - [8.2. Auto Low Latency Mode Signalled](#82-auto-low-latency-mode-signalled)
  - [8.3. Port Auto Low Latency Mode Capable](#83-port-auto-low-latency-mode-capable)
    - [8.3.1. Port Auto Low Latency Mode Capable Changed Notification](#831-port-auto-low-latency-mode-capable-changed-notification)
- [9. HDMI Port managing active source](#9-hdmi-port-managing-active-source)
## 3. All Ports
The `HDMIInput` module **MUST** have a `ports` method that lists all physical HDMI input ports on the device.

The `ports` API **MUST** return an array of `HDMIInputPort` objects.

An example response:

```json
[
    {
        "port": "HDMI1",
        "connected": true,
        "signal": "unknown",
        "arcCapable": true,
        "arcConnected": true,
        "autoLowLatencyModeCapable": true,
        "autoLowLatencyModeSignalled": true,
        "edidVersion": "2.0"
    }
]
```

The `HDMIInputPort` object **MUST** have a `port` string property, which is the unique ID of that port. This is usually formatted and printed on the device near the port.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The `HDMIInputPort` object **MUST** have a `connected` boolean property, which is true if that port has a device connected, false otherwise.

The `HDMIInputPort` object **MUST** have a `signal` string property, which denotes the signal validity.

The `signal` property **MUST** be one of the following values:

- `"unknown"` - the HDMI input port is not switched, so the signal state is unknown.
- `"none"` - no signal from the HDMI input device.
- `"stable"` - the signal is stable and should provide good audio and viddeo.
- `"unstable"` - the signal is unstable and could exhibit broken audio and video.
- `"unsupported"` - the signal is not at a supported speed/resolution.

The `HDMIInputPort` object **MUST** have an `arcCapable` boolean property, which is true if this HDMI port supports ARC and/or eARC device connections.

The `HDMIInputPort` object **MUST** have an `arcConnected` boolean property, which is true if the attached device supports ARC and/or eARC, regardless of whether the input port supports ARC.

The `HDMIInputPort` object **MUST** have an `edidVersion` string property which is the selected E-EDID version "1.4" or "2.0" for the port.

The `edidVersion` property **MUST** be one of the following values:

- `"1.4"`
- `"2.0"`
- `"unknown"`

If the `edidVersion` is `"2.0"` then the `HDMIInputPort` object:

> **MUST** have an `autoLowLatencyModeCapable` boolean property, which is true if the device has ALLM support in the EDID on this HDMI input, false otherwise.
>
> **MUST** have an `autoLowLatencyModelSignalled` boolean property, which is true if the port is receiving an ALLM signal from a downstream source device, and false otherwise.

If the `edidVersion` is `"1.4"` or `"unknown"` then the `HDMIInputPort` object:

 > **MUST** have the `autoLowLatencyModeCapable` boolean property set to `false`.
 >
 > **MUST** have the `autoLowLatencyModelSignaled` boolean property set to `false`

The `"unknown"` value of the `edidVersion` property **SHOULD** be reserved for edge cases, such as a test device with a newer version of HDMI ports than the device software supports.

The `ports` API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

## 4. Single Port
The `HDMIInput` module **MUST** have a `port` method that returns info on a single HDMI port.

The `port` API **MUST** return an `HDMIInputPort` object that corresponds to the provided `portId` parameter.

```javascript
HDMIInput.port('HDMI1')
```

The `port` API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

## 5. Port Connection Notification
The `HDMIInput` module **MUST** have an `onConnectionChanged` notification that fires when any HDMI port has a connection physically engaged or disengaged.

This notification **MUST** have an object payload.

The object payload **MUST** have a `port` string property that denotes which input port has detected a connection change.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The object payload **MUST** have a `connected` boolean property that denotes the updated value of the connection state.

Example payload:

```json
  {
      "port": "HDMI1",
      "contected": true
  }
```

The `onConnectionChanged` API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.


## 6. Port Signal Notification
The `HDMIInput` module **MUST** have an `onSignalChanged` notification that fires when any HDMI port signal changes status.

This notification **MUST** have an object payload.

The object payload **MUST** have a `port` string property that denotes which input port has detected a change to the signal validity.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The object payload **MUST** have a `signal` string property that denotes the updated value of the input device signal.

The `signal` property **MUST** be one of the following values:

- `"unknown"` - the HDMI input port is not switched, so the signal state is unknown.
- `"none"` - no signal from the HDMI input device.
- `"stable"` - the signal is stable and should provide good audio and viddeo.
- `"unstable"` - the signal is unstable and could exhibit broken audio and video.
- `"unsupported"` - the signal is not at a supported speed/resolution.

Example payload:

```json
  {
      "port": "HDMI1",
      "signal": "stable"
  }
```

The `onSignalChanged` API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

## 7. EDID Version
Extended Display Identification Data enables HDMI devices to communicate which set of features are supported.

The `HDMIInput` module **MUST** have a boolean property named `edidVersion`, with a getter, setter, and notification subscriber.

The `edidVersion` property **MUST** have a `port` parameter to specify which port.

The `edidVersion` property requires access to the `use` role of the `xrn:firebolt:capability:inputs:hdmi` capability.

The `edidVersion` property **MUST** have a notification for when a port's edid value changes.

The `edidVersion` property **MUST** have a setter that requires access to the `manage` role.

Setting this property changes the specified port's EDID version, that is broadcast to other devices.

Low latency mode switches the device to shorten the overall processing time of HDMI A/V signals.
Depending on the platform some video processing features may be disabled such as MPEG noise reduction.

## 8. Low Latency
Low Latency refers to a set of functionally that combines to provide manual or automatic activation of HDMI Low Latency Mode.

Low latency mode switches the device to shorten the overall processing time of HDMI A/V signals.

Depending on the platform some video processing features may be disabled such as MPEG noise reduction.

### 8.1. Low Latency Mode
The `HDMIInput` module **MUST** have a boolean property named `lowLatencyMode`, with a getter, setter, and notification subscriber.

Enabling this property turns on the underlying low latency mode feature for the Firebolt device, which affects all HDMI ports,
but not other media sources.

Low latency mode switches the device to shorten the overall processing time of HDMI A/V signals.
Depending on the platform some video processing features may be disabled such as MPEG noise reduction.

The `lowLatencyMode` API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

The `lowLatencyMode` API **MUST** have a corresponding setter that requires `manage` access to the `xrn:firebolt:capability:inputs:hdmi` capability.


#### 8.1.1. Low Latency Mode Notification
Whenever the underlying HDMI implementation executes an LLM change (either on or off), this notification **MUST** fire:

`HDMIInput.onLowLatencyModeChanged`

The `onLowLatencyModeChanged` API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

### 8.2. Auto Low Latency Mode Signalled
The `HDMIInput` module **MUST** have an `onAutoLowLatencyModeSignalChanged` notification that fires when the ALLM signal from the source connected to a port changes.

This notification **MUST** have an object payload.

The object payload **MUST** have a `port` string property that denotes which input port has detected a change to the ALLM signal.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The object payload **MUST** have an `autoLowLatencyMode` boolean property that denotes the updated value, true or false, of the ALLM setting.

Example payload:

```json
  {
      "port": "HDMI1",
      "autoLowLatencyModeSignalled": true
  }
```

The `onAutoLowLatencyModeSignalChanged` API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

### 8.3. Port Auto Low Latency Mode Capable
The `HDMIInput` module **MUST** have a boolean property `autoLowLatencyModeCapable` which reflects the HDMI port setting for advertising ALLM support in its E-EDID.

The `autoLowLatencyModeCapable` property takes a string context parameter, `port` to identify the HDMI port.

The `port` parameter must match the pattern:

```regexp
 /^HDMI[0-9]+$/
 ```

The `autoLowLatencyModeCapable`  API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

Changing this property turns on/off the underlying auto low latency mode advertisement in any HDMI port E-EDID of version >= v2.0.

To change the property:

```javascript
function autoLowLatencyModeCapable(port: string, autoLowLatencyMode: boolean)
```

The `autoLowLatencyModeCapable` setter API requires `manage` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

#### 8.3.1. Port Auto Low Latency Mode Capable Changed Notification
Whenever the underlying HDMI implementation executes an ALLM support change (either on or off), this notification must fire:

`HDMIInput.onAutoLowLatencyModeCapableChanged`

To listen for port ALLM notifications:

```javascript
HDMIInput.autoLowLatencyModeCapableChanged((data) => {
  console.log('Port ' + data.port + ' ALLM changed to ' + data.autoLowLatencyModeCapable)
})
```

`autoLowLatencyModeCapable` - whether or not ALLM is advertised as supported in the E-EDID for the port.

`port` - the HDMI port that had an E-EDID ALLM advertisement change.

The `onAutoLowLatencyModeCapableChanged`  API requires `use` access to the `xrn:firebolt:capability:inputs:hdmi` capability.


## 9. HDMI Port managing active source

The `HDMIInput` module **MUST** have `open` and `close` method(s) that manages the active source of on a single HDMI port.

The `HDMIInput.open` **MUST** include a `portId` field complying to the schema of `HDMIPortId`

The `HdmiInput.open` and `HDMIInput.close` API(s) **MUST** return an `empty` object for a successful operation, if there was an error the response **Must** contain the details of the error.

The `HdmiInput.open` and `HDMIInput.close` API requires `manage` access to the `xrn:firebolt:capability:inputs:hdmi` capability.

Below is an example for opening a given HDMIPort.
```javascript
HDMIInput.open('HDMI1').then(() => {
  console.log("Successfully opened HDMI1 port");
})
```

Below is an example for closing last active source.
```javascript
HDMIInput.close().then(() => {
  console.log("Successfully closed HDMI1 port");
})
```