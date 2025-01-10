# Networking Requirements

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Bart Catrysse   | Liberty Global |
| Brian Chow      | Sky            |
| Jeremy LaCivita | Comcast        |
| Joe Martin      | Comcast        |

## 1. Overview

To provide the best experience to users, content partners want to understand details about a device's network connection, such as the device's connection state, connection type, and that connection's performance capabilities.  Content partners also want to be notified of key changes to the device's connection, such as connect/disconnect events or IP changes.  This data can be used to gauge how those changes may impact the user's experience and react appropriately.

App partners also have different requirements of what network details are made available to them.  For instance, most app partners simply want to know the device's current connection state, type, and be notified of changes to that connection.  Other app partners may have more sophisticated needs, requiring access to details on the the configurations of all available network interfaces, including interface MAC addresses, IPs, and interface capabilities.

This information can be used to gracefully handle cases when the device has poor or no network connectivity, provide valuable data into how the user's network performance is impacting their experience, and to unlock more advanced networking features on the device (such as Wake-on-LAN functionality).

These APIs will be surfaced in the Firebolt `Network` module.

### 1.1. User Stories

As an app, I want to...

- Get the device's network connection state and connection type
- Get details on each of the device's interfaces, such as name, MAC address, and IP configuration
- Get details on the wireless connection, such as SSID and signal strength
- Be notified of key changes to the device's network connection, such as connection state, TCP/IP configuration, or wireless signal

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Constants, Types, and Schemas](#3-constants-types-and-schemas)
  - [3.1. Connection States](#31-connection-states)
  - [3.2. Interface Types](#32-interface-types)
  - [3.3 Ethernet Standards](#33-ethernet-standards)
  - [3.4. Wireless Standards](#34-wireless-standards)
- [4. Network APIs](#4-network-apis)
  - [4.1. Connection Status](#41-connection-status)
  - [4.2. Interfaces](#42-interfaces)
  - [4.3. IP Properties](#43-ip-properties)
  - [4.4. Wifi Status](#44-wifi-status)

## 3. Constants, Types, and Schemas

### 3.1. Connection States

The Firebolt `Network` module **MUST** have a `ConnectionState` enumeration:

- `connected`
- `disconnected`
- `unknown`

### 3.2. Interface Types

The Firebolt `Network` module **MUST** have an `InterfaceType` enumeration:

- `ethernet`
- `wifi`
- `other`
- `unknown`

### 3.3 Ethernet Standards

The Firebolt `Network` module **MUST** have an `EthernetStandard` enumeration:

| Name                   |
| ---------------------- |
| `Fast Ethernet`        |
| `Gigbabit Ethernet`    |
| `10 Gigbabit Ethernet` |

### 3.4. Wireless Standards

The Firebolt `Network` module **MUST** have an `WirelessStandard` enumeration:

| Name       | Description |
| ---------- | ----------- |
| `802.11ac` | WIFI 5      |
| `802.11ax` | WIFI 6/6E   |
| `802.11be` | WIFI 7      |
| `802.11bn` | WIFI 8      |
| `802.11n`  | WIFI 4      |
| `legacy`   | 802.11a/b/g |
| `other`    |             |

## 4. Network APIs

Apps need to get various details about the device's network configuration and capabilities, such as whether the device is connected to a network, what type of connection is used, and details on the network interfaces available on the device.

Apps also need to be aware of changes to the device's network connection that may occur, either through user-initiated changes or via external factors.

To facilitate this, the `Network` module will surface methods that provide various details of the device's connection to the local network while also allowing apps to subscribe to various events triggered by key changes to the network connection.

### 4.1. Connection Status

The `Network` module **MUST** have a `connectionStatus` method that returns an object describing the device's current network connection status.

This method's response **MUST** support the following properties:

| Property    | Type                    | Required in Response |
| ----------- | ----------------------- | -------------------- |
| `connected` | `boolean`               | Yes                  |
| `type`      | `Network.InterfaceType` | No                   |

The result **MUST** be based on the device's preferred/default network interface.

If the device's preferred interface has both link-layer connectivity and valid IP configuration, the `connected` value **MUST** be `true`, otherwise `false` is returned.

If `connected` is `true`, `type` **MUST** be one of: `ethernet`, `wifi`, or `other`.

If `connected` is `false`, `type` **MUST NOT** be returned.

This method **MUST** have a corresponding `onStatusChanged` event returning the properties listed above to notify listeners when any of the properties have changed and taken effect.

The platform **MUST** trigger the event when the device's preferred network interface changes.

The platform **MUST** trigger the event on connection changes to device's preferred network interface (e.g. connect, disconnect, auth failure, wifi out of range, etc).

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:network:connectionstatus` capability.

```javascript
Network.connectionStatus()
//> {
//>   "connected": true,
//>   "type": "wifi"
//> }
```

### 4.2. Interfaces

The `Network` module **MUST** have an `interfaces` method that describes each network interface on the device.

This method's response **MUST** return an array of objects with the following properties for each enabled interface:

| Property          | Type                                                 | Description                                                                                        |
| ----------------- | ---------------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| `connectionState` | `Network.ConnectionState`                            |                                                                                                    |
| `interfaceName`   | `string`                                             |                                                                                                    |
| `macAddress`      | `string`                                             |                                                                                                    |
| `preferred`       | `boolean`                                            | Whether the interface is the preferred/default interface for routing                               |
| `standard`        | `Network.EthernetStandard`</br>or `WirelessStandard` | The physical connection standard supported by the interface (e.g. `Gigbabit Ethernet`, `802.11ac`) |
| `type`            | `Network.InterfaceType`                              | The generalized type of interface (e.g. `ethernet` or `wifi`)                                      |

If `connectionState` is `disconnected`, `preferred` **MUST** be `false`.

This method **MUST** have a corresponding `onInterfaceChanged` event returning an object with the properties listed above to notify listeners when an interface's properties have changed and taken effect.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:network:interfaces` capability.

```javascript
Network.interfaces()
//> [
//>   {
//>     connectionState: "disconnected",
//>     interfaceName: "wifi0",
//>     macAddress: "00:00:00:00:00:00",
//>     preferred: false,
//>     standard: "802.11ac",
//>     type: "wifi"
//>   },
//>   {
//>     connectionState: "connected",
//>     interfaceName: "eth0",
//>     macAddress: "00:00:00:00:00:00",
//>     preferred: true,
//>     standard: "Gigabit Ethernet",
//>     type: "ethernet"
//>   },
//> ]
```

### 4.3. IP Properties

The `Network` module **MUST** have an `ipProperties` method that returns an object describing the TCP/IP properties of an interface.

The method **MUST** require a `string` parameter denoting the interface name on which the result shall be based.

This method's response **MUST** return the following properties:

| Property           | Type       |
| ------------------ | ---------- |
| `interfaceName`    | `string`   |
| `ipv4Addresses`    | `[]string` |
| `ipv4DNSAddresses` | `[]string` |
| `ipv6Addresses`    | `[]string` |
| `ipv6DNSAddresses` | `[]string` |

The values returned in `ipv4Addresses` and `ipv6Addresses` **MUST** be presented in CIDR notation.

If an invalid interface name is provided, a `-40404 / Interface not found` JSON-RPC error **MUST** be returned.

This method **MUST** have a corresponding `onIpPropertiesChanged` event returning the properties listed above to notify listeners that an interface's IP properties have changed and taken effect.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:network:ipproperties` capability.

```javascript
Network.ipProperties("eth0")
//> {
//>   interfaceName: "eth0",
//>   ipv4Addresses: ["192.168.1.100/24"],
//>   ipv4DNSAddresses: ["75.75.75.75"],
//>   ipv6Addresses: ["2001:db8:abcd:0012::0/64"],
//>   ipv6DNSAddresses: ["2001:558:feed::1"]
//> }
```

### 4.4. Wifi Status

The `Network` module **MUST** have a `wifiStatus` method that returns an object describing an interface's connection status to a wireless network.

The method **MUST** support a required `string` parameter denoting the interface name of which the result is based.

This method's response **MUST** support the following properties:

| Property          | Type                       | Description                                 | Required in Response |
| ----------------- | -------------------------- | ------------------------------------------- | -------------------- |
| `connectionState` | `Network.ConnectionState`  |                                             | Yes                  |
| `interfaceName`   | `string`                   |                                             | Yes                  |
| `protocol`        | `Network.WirelessStandard` | Current wireless protocol (e.g. `802.11ac`) | No                   |
| `signalStrength`  | `integer`                  | Signal strength / RSSI value (in dBm)       | No                   |
| `ssid`            | `string`                   | Wireless network name                       | No                   |

If no wireless interface matches the provided name, a `-40404 / Wireless interface not found` JSON-RPC error **MUST** be returned.

If the wireless interface is not connected to a network, `connectionState` **MUST** be `disconnected`. Additionally, `mode`, `signalStrength` and `ssid` **MUST NOT** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:network:wifistatus` capability.

```javascript
Network.wifiStatus("wifi0")
//> {
//>  connectionState: "connected",
//>  interfaceName: "wifi0",
//>  protocol: "802.11ac",
//>  signalStrength: -50,
//>  ssid: "MyNetwork"
//> }
```
