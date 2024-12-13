# Media Access

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Anthony Borzotta           | Comcast           |
| Jeremy LaCivita | Comcast |

## 1. Overview

Some apps will need to make use of files stored on the device, e.g. on
internal storage or a USB Mass Storage device.

Giving such apps full access to the filesystem to facilitate access to
the user's personally cultivated media is providing far too much
information for such a simple use case. On the other hand, providing a
platform file picker UI might not enable the richness of experience that
app developers need.

The apps that would use this feature are primarily interested in user
cultivated media files, and where they came from, e.g., USB or a cloud
photo storage provider, etc., is of secondary or no importance. This API
is intended to expose user cultivated media in a convenient, file-system
agnostic, storage-agnostic way.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Media Access](#3-media-access)
  - [3.1. Listing Media Files](#31-listing-media-files)
  - [3.2. Volume Availability](#32-volume-availability)
  - [3.3. Accessing Files](#33-accessing-files)
  - [3.4. Core APIs](#34-core-apis)
    - [3.4.1. Volumes](#341-volumes)
    - [3.4.2. Files](#342-files)
  - [3.5. Schemas](#35-schemas)
    - [3.5.1. MediaFile](#351-mediafile)
    - [3.5.2. Volume](#352-volume)
    - [3.5.3. VolumeType](#353-volumetype)

## 3. Media Access

The Firebolt `MediaAccess` module consists of APIs to list and read
various types of `MediaFile`. It also contains APIs for detecting when
new media file `Volumes` are available.

### 3.1. Listing Media Files

The `MediaAccess` module **MUST** have a `files` API used to return a
list of `MediaFile` objects from a specific directory.

The `files` APIs **MUST** support a required `path` parameter of type
`string`.

The `path` parameter may denote a Volume mount-point or a directory at
any level below one of the available volumes.

The `files` API **MUST** return all files and directories inside the 
provided `path`.

The `files` API **MUST NOT** be recursive.

If the `path` is not a valid directory, the `files` API **MUST** return
an `Invalid path` error.

If the `path` is a directory that cannot be accessed due to OS
permissions, then the `files` API **MUST** also return the same `Invalid path`
error. 

Each `MediaFile` includes the full URI, relative to the Volume, so
that Apps may present them in a manner that matches the directory
structure on the `Volume`, e.g.:

TODO: is this a true root path, or simulated path.

```json
{
    "name": "mysong.mp3",
    "url": "https://127.0.0.1:1001/MediaAccess/USBMassStorage/mnt/USB-Drive/mp3s/mysong.mp3",
    "isDir": false,
    "type": "application/mp3"
}
```

Example director:

```json
{
    "name": "mp3s",
    "url": "https://127.0.0.1:1001/MediaAccess/USBMassStorage/mnt/USB-Drive/mp3s/mysong.mp3",
    "isDir": true
}

```


Apps **MUST** use the `path` property for display purposes and the `url`
property for fetching purposes. This allows the underlying HTTP
implementation to change w/out apps breaking.

In order to call the `MediaAccess.files()` API an app **MUST** have
permission to use the `xrn:firebolt:capability:media-access:files`
capability.

### 3.2. Volume Availability

Apps that consume user cultivated media will likely want to know when
volumes become available or unavailable.

This is accomplished with a temporal-set API called `volumes()`.

The volumes API **MUST** support a context parameter of type for the
Volume Type, e.g. `usb`.

See [Temporal Sets](../openrpc-extensions/temporal-set.md) for more info.

### 3.3. Accessing Files

**TODO**: this is still in review
**TODO**: Add some details on the HTTP Server thunder plugin

In order to do something with the file, apps will need access to the
file contents.

Firebolt platforms **MUST** provide a local `https` server for apps to
request MediaFiles.

The server **MUST** be reachable via the IP address 127.0.0.1

The server **MUST** only be accessible via `https` and have a valid,
self-signed certificate trusted by the browser.

**NOTE: does using an IP address mean we can't use SSL? Do we need a
fake domain name? Do we even need SSL if the host is 127.0.0.1?**

Each App that uses the MediaAccess APIs **MUST** be assigned a unique
port number for accessing the http URLs for those files. This allows any
security measures to be opaque to the calling app.

App containers **MUST** be limited to only access one of the available
Media Access ports.

The port numbers `1000` to `1999` on the local device **MUST** be reserved
for HTTP Media Access URLs.

**TODO**: ^^ get rid of port logic for now


HTTP URLs for file access **MUST** follow the template:

```
https://127.0.0.1:<app port>/MediaAccess/<storage type>/<path>
```

The `<storage type>` for `usb` is `USBMassStorage`.

For example:

```
https://127.0.0.1:1001/MediaAccess/USBMassStorage/mnt/USB-Drive/mp3s/mysong.mp3
```

![Diagram Description automatically
generated](../../images/specifications/media/access/media/media-access-hla.png)

### 3.4. Core APIs

The following APIs are added to the Core SDK.

#### 3.4.1. Volumes

The `volumes` method can be called in one of four ways.

```typescript
function volumes(): Promise<Volume[]>
```

The get the currently cached list of Volumes w/out scanning call the
method with just a `query` parameter:

```typescript
function volumes(query: Volume): Promise<Volume[]>
```

This returns the Volumes that the device is aware or, that match the
query, without checking if there are any new volumes.

To find the first volume that matches a query, pass in a `query` and a
`timeout`, in milliseconds, representing how long the app is willing to
wait.

```typescript
function volumes(query: Volume, timeout: number): Promise\<Volume\>
```

This returns a `Volume` object if a match is found before the `timeout`.

To initiate a live temporal set that updates continuously, call the
method with a `query`, an `add` callback and a `remove` callback:

```typescript
function volumes(query: Volume, add: (item: Volume) => void, remove:
(item: Volume) => void): VolumeProcess
```

This will initiate an open-ended scan for volumes matching the query and
call the callbacks when a device becomes available or unavailable.

This method returns a `VolumeProcess` object, synchronously, that
contains a single `stop()` method for cancelling the temporal-set
session.

#### 3.4.2. Files

These APIs return all the files that match the associated capability,
and the Volume query parameter:

```typescript
function files(path: string):Promise<MediaFile[]>
```

### 3.5. Schemas

The following Schemas are used by this API.

#### 3.5.1. MediaFile

This is the primary object return by the various APIs.

| Property | Type    | Description                                  |
|----------|---------|----------------------------------------------|
| name     | string  | The Unix filename of the file w/out any path or directories |
| uri      | string  | The http URL to request the file contents, e.g. `https://127.0.0.1:1001/MediaAccess/USBMassStorage/mnt/USB-Drive/mp3s/mysong.mp3` |
| isDir    | boolean | Whether the MediaFile is a directory         |

If a file is a directory then `isDir` **MUST** be true.

#### 3.5.2. Volume

This provides information about a Volume, e.g. a Device, that stores
MediaFiles.

| Property | Type       | Description                                                                  |
|----------|------------|------------------------------------------------------------------------------|
| type     | VolumeType | The type of volume, e.g. USB                                                 |
| path     | string     | The Unix path to the root of the volume's storage, e.g. `/mnt/USB-Drive` |
| label    | string     | The display name of the volume, e.g. `My Cool USB Drive`                     |

#### 3.5.3. VolumeType

An enumeration of strings representing possible Volume types:

-   `'usb'`
