# [1.1.0](https://github.com/rdkcentral/firebolt-apis/compare/v1.0.0...v1.1.0) (2024-02-09)

### Bug Fixes

    * Add Music to Playable entities (#225 (https://github.com/rdkcentral/firebolt-apis/issues/225)) (22c9b71 (https://github.com/rdkcentral/firebolt-apis/commit/22c9b71d3c0ee98d32585d1b365afabf8e64d6ed))
    * Modified account:uid to SHOULD (#224 (https://github.com/rdkcentral/firebolt-apis/issues/224)) (70c8b24 (https://github.com/rdkcentral/firebolt-apis/commit/70c8b24decfcbff2c32fb1b0d21290afc00a8432))

# [1.0.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.17.1...v1.0.0) (2023-11-03)

Upgraded to 1.0 at part of RDK6 release. This API is still compatibile with 0.x versions.

### Bug Fixes

    * Updated Discovery.launch example with xrn:firebolt: application-type (#187 (https://github.com/rdkcentral/firebolt-apis/issues/187)) (4dbbab3 (https://github.com/rdkcentral/firebolt-apis/commit/4dbbab3d9fa68c0e5185ca72fd0170bae8a30139))

### Features
  
    * Added scope parameter for advertisingId (#188 (https://github.com/rdkcentral/firebolt-apis/issues/188))
    * Play Intent (#151 (https://github.com/rdkcentral/firebolt-apis/issues/151)) (d1ddf3f (https://github.com/rdkcentral/firebolt-apis/commit/d1ddf3fb3b1f758315686ad2f6dc57c2b270f33a))

# [0.17.1](https://github.com/rdkcentral/firebolt-apis/compare/v0.17.0...v0.17.1) (2023-09-15)

### Bug Fixes

fix: Add enumerated values for fontFamily/fontEdge (#181)

# [0.17.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.16.0...v0.17.0) (2023-09-07)

### Bug Fixes

* fix: Using 3 letter ISO639 language codes ([#173](https://github.com/rdkcentral/firebolt-apis/issues/173))

# [0.15.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.14.0...v0.15.0) (2023-07-31)

### Bug Fixes

* Rename Advisory "Committee" to "Board" ([#135](https://github.com/rdkcentral/firebolt-apis/issues/135)) ([ef410c4](https://github.com/rdkcentral/firebolt-apis/commit/ef410c43bbb32414c3aa1d11b43093565cc90edf))
* window fix from firebolt-openrpc 2.0.3 ([8c06dd1](https://github.com/rdkcentral/firebolt-apis/commit/8c06dd1432822719f5634e2877b36efdf02a4809))

### Features

* **Nullable CC Styles** Added support to set and get null in ClosedCaptions style fields ([#150](https://github.com/rdkcentral/firebolt-apis/issues/150)) ([9c511e4](https://github.com/rdkcentral/firebolt-apis/commit/9c511e4fddebcdf5dfc04e9e8e31f98ab7eef680))
* **Window CC Styles** Added windowColor and windowOpacity to closedCaptions style ([#145](https://github.com/rdkcentral/firebolt-apis/issues/145)) ([f65b901](https://github.com/rdkcentral/firebolt-apis/commit/f65b9019bda22400df9b9634c332e720db38118d))
* **Audio Descriptions** Audio Description and Preferred Audio Languages Settings ([#45](https://github.com/rdkcentral/firebolt-apis/issues/45)) ([58f6ea1](https://github.com/rdkcentral/firebolt-apis/commit/58f6ea1dde7a819883eb3da24f879b6a9ecc9a41))

# [0.14.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.13.0...v0.14.0) (2023-06-22)

### Bug Fixes

* **VoiceGuidance** Change voice guidance limits to 0.5 and 2 ([#137](https://github.com/rdkcentral/firebolt-apis/issues/137)) ([b8f1944](https://github.com/rdkcentral/firebolt-apis/commit/b8f19449efd808639599b162aba61c08ec089c41))

### Features

* **Capabilities** Allow granted in capability.info and capability.granted to be null ([#134](https://github.com/rdkcentral/firebolt-apis/issues/134)) ([c5c31ee](https://github.com/rdkcentral/firebolt-apis/commit/c5c31ee3c744ec018a57232d2e7b1caf41158ed6))

# [0.13.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.12.0...v0.13.0) (2023-06-09)

### Bug Fixes

* Point to `firebolt-openrpc` 2.0.1 ([c57cb21](https://github.com/rdkcentral/firebolt-apis/commit/c57cb218343fd058e2e6e676d52d9d0c904ad9a8))

### Features

* Add SecureStorage.clear method. ([#127](https://github.com/rdkcentral/firebolt-apis/issues/127)) ([4422c79](https://github.com/rdkcentral/firebolt-apis/commit/4422c79122fc35e7b35180254be52bf33c64ab5b))


# [0.12.0](https://github.com/rdkcentral/firebolt-apis/compare/v0.11.0...v0.12.0) (2023-05-18)

### Bug Fixes

* The `title` and `identifiers` parameters are now required for `Discovery.watchNext()` ([#124](https://github.com/rdkcentral/firebolt-core-sdk/issues/124)) ([96d7b2b](https://github.com/rdkcentral/firebolt-core-sdk/commit/96d7b2bb7464d6044346440d37feecba9dbc7899))
* Fixed handling of context parameters for `Capabilities.listen()`.

# [0.11.0](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.10.0...v0.11.0) (2023-05-01)


### Bug Fixes

* Change doc examples to https ([#79](https://github.com/rdkcentral/firebolt-core-sdk/issues/79)) ([0da43e6](https://github.com/rdkcentral/firebolt-core-sdk/commit/0da43e666842bb75d20f9585c0d1f3f0236388ee))
* Updated secure storage spec to allow null as result value ([#84](https://github.com/rdkcentral/firebolt-core-sdk/issues/84)) ([7ed1fed](https://github.com/rdkcentral/firebolt-core-sdk/commit/7ed1fed9ab9f5d84927c4e31c2816e15da0d6f44))


# [0.10.0](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.9.0...v0.10.0) (2023-02-06)


### Bug Fixes

* Capability module needs capability tags ([#71](https://github.com/rdkcentral/firebolt-core-sdk/issues/71)) ([6f0af1b](https://github.com/rdkcentral/firebolt-core-sdk/commit/6f0af1b9712faab137b1652ea337d5f284196ad4))
* Change doc examples to https ([#79](https://github.com/rdkcentral/firebolt-core-sdk/issues/79)) ([c7047af](https://github.com/rdkcentral/firebolt-core-sdk/commit/c7047af9f3fa47e8cd7d252c3bbd321fa8f3d125))
* FIRESDK-31 returned response from Lifecycle.ready method ([#81](https://github.com/rdkcentral/firebolt-core-sdk/issues/81)) ([efc740f](https://github.com/rdkcentral/firebolt-core-sdk/commit/efc740f7899897981cc840f12efe30f3e9543be4))
* Updated openrpc version to 1.8.0-next.2 ([#85](https://github.com/rdkcentral/firebolt-core-sdk/issues/85)) ([b988c41](https://github.com/rdkcentral/firebolt-core-sdk/commit/b988c4159b154f8c041b766f794618250448bce0))
* Updated secure storage spec to allow null as result value ([#84](https://github.com/rdkcentral/firebolt-core-sdk/issues/84)) ([4117ad7](https://github.com/rdkcentral/firebolt-core-sdk/commit/4117ad79322c8a3decd59f5ad52d5dfe6cf2f2a4))
* Use new openrpc template code with bug fixes ([#69](https://github.com/rdkcentral/firebolt-core-sdk/issues/69)) ([9fed6fc](https://github.com/rdkcentral/firebolt-core-sdk/commit/9fed6fcb71b9914e91674f5e80f7d61673cc66fe))
* Word publish scripts ([#78](https://github.com/rdkcentral/firebolt-core-sdk/issues/78)) ([a3846e0](https://github.com/rdkcentral/firebolt-core-sdk/commit/a3846e0db22e1221547ad97a019aba3850c51f6a))


### Features

* Add content-access api, deprecate entitlements, remove availabi… ([#83](https://github.com/rdkcentral/firebolt-core-sdk/issues/83)) ([f3c8017](https://github.com/rdkcentral/firebolt-core-sdk/commit/f3c8017eb391119e47d810426fdae4b11d8e0c38))
* Add Secure Storage module ([#77](https://github.com/rdkcentral/firebolt-core-sdk/issues/77)) ([f62e4ae](https://github.com/rdkcentral/firebolt-core-sdk/commit/f62e4aeb9325df00c6a2484cf3aaa0b756bd8113))
* New Capabilities API ([#63](https://github.com/rdkcentral/firebolt-core-sdk/issues/63)) ([0ba5ef5](https://github.com/rdkcentral/firebolt-core-sdk/commit/0ba5ef5e030ce740e40fd5ad30ca5cfd100cf32e))
* Trigger ([607825b](https://github.com/rdkcentral/firebolt-core-sdk/commit/607825bd5547c74a8a7707f751446ab0e069d9f9))
* Turn on dryRun ([dcddc60](https://github.com/rdkcentral/firebolt-core-sdk/commit/dcddc6068f91505d97457ed04eb8e2996dab9278))


# 0.9.0

### Features

* Adding Availabilities API ([#65](https://github.com/rdkcentral/firebolt-core-sdk/issues/65)) ([ec940dd](https://github.com/rdkcentral/firebolt-core-sdk/commit/ec940dd1a7a6865f18d64ada69793c87556a172e))
* Tagging Capabilities ([e3b6ee2](https://github.com/rdkcentral/firebolt-core-sdk/commit/e3b6ee2475fbd9157a40bc92490c06df135ebc34))

### Bug Fixes

* Don't ignore source files when publishing to npm [skip ci] ([cb26ff2](https://github.com/rdkcentral/firebolt-core-sdk/commit/cb26ff2e09416613c5557e76966eccbe0ec66d54))
* Build SDK before npm publish ([#64](https://github.com/rdkcentral/firebolt-core-sdk/issues/64)) ([f221fa3](https://github.com/rdkcentral/firebolt-core-sdk/commit/f221fa34e24e29e86487b1ec98468b64f495d134))
* **Lifecycle:** lifecycle state api returns correct state in all circumstances ([31e405c](https://github.com/rdkcentral/firebolt-core-sdk/commit/31e405c124d29a3e87294dc4b356ff8df9972af8))

# 0.8.1

- Added Device.version().firmware to surface the underlying hardware firmware version
- Added Device.version().api to surface the latest Firebolt API supported by this device
- Deprecated Device.version().os which does not have a formal specification. Use `firmware` instead.

# 0.8.0

- Tune Intents are now supported in `navigateTo` events
- Added TypeScript declarations for Settings and Events
- Fixed/Removed test-enabling code from SDK
- Fixed bug where the SDK would initialize itself even when not being used

# 0.7.0

- Removed all `bigint` types from TypeScript declarations, in favor of `number`, since bigint is not widely supported across browsers. This changes impacts:
    - Device.screenResolution
    - Device.videoResolution
    - Discovery.purchasedContent
    - Metrics.mediaProgress
    - Metrics.mediaSeeking
    - Metrics.mediaSeeked
    - Parameters.initialization

To upgrade to 0.7.0 simply change the type of any Firebolt Promise resolutions from `bigint` to `number`, e.g.:

```typescript
const res:[bigint, bigint] = await Device.screenResolution()
```

Should become:

```typescript
const res:[number, number] = await Device.screenResolution()
```

# 0.6.2

- Fixed incompatibility with Jest 26 due to [jest/issues/10565](https://github.com/facebook/jest/issues/10565)


# 0.6.1

- Changed Firebolt build to use `.mjs` extension
- Firebolt builds are now pure ES6 modules, not bundled with Webpack
- Added `types` path to package.json
- Fixed TypeScript declarations for `FlatMap` and `BooleanMap`
- Added TypeScript return type declarations for `listen` and `once` (all modules)
- Added TypeScript declaration for `clear` method (all modules)
- Changed `{}` return type to `void` for listener callbacks

# 0.6.0

- Added support for [rdkcentral/mock-firebolt](https://github.com/rdkcentral/mock-firebolt/) via a WebSocket transport layer
- Deprecated Accessibility.closedCaptions and voiceGuidance, created properties for Accessibility.closedCaptionsSettings and voiceGuidanceSettings, which support subscribers
- Deprecated Device.listen('deviceNameChanged'), added support for subscribing to Device.name()
- Added support for subscribing to property changes: Device.audio, hdcp, hdr, name, network, screenResolution, videoResolution, Advertising.policy, Discovery.policy, Localization.language
- Added proper TypeScript declarations for Discovery.entityInfo and Discovery.purchasedContent
- Fixed race condition w/ Transport Layer initialization

# 0.5.2

- Added Parameters modules
- Fixed typo in Advertising.config example result for docs/Mock
- Updated Metrics.error signature to include `type` as first parameter
- Created window.__firebolt.testHarness handshake (for Mock TL only)
- Added `LocalizedString` type for localized string dictionaries
- Updated `Discovery.watchNext` to use `LocalizedString` for `title` and each property of `images`
- Added `OfferingType` and `ProgramType` parameters to `Discovery.purchasedContent`

# 0.5.1

- Cleaned up errors in various Mock responses
- Methods that call private Metrics APIs, e.g. Lifecycle.ready, now do so **after** promise resolution

# 0.5.0

- Updated TS declarations (.d.ts) to detect which event is being passed to `.listen()` methods
- Updated all `listen()` and `once()` methods to return a `Promise`
- Renamed `verifyContentRating` and `verifyPurchase` to `approveContentRating` and `approvePurchase` respectively
- Added `Profile.flags()` for distributor-specific profile flags
- Added optional `source` field to all `LifecycleEvents`
- Complete rewrite of `Metrics` APIs (see docs)
- Added `policyChanged` events to `Discovery` and `Advertising`
- Fixed duplicate RPC `listen` calls when listening to an event in slightly different ways, e.g. `once()` vs `listen()`
- Added Account, Authentication, Keyboard, Profile, SecondScreen modules
- Added Federated Search APIs to Discovery
- Added TypeScript/Intellisense declarations file
- Fixed spelling error on Accessibility module name
- Moved the `coppa` parameter for `Advertising.confg()` into the `options` object, and made it optional
- Final version of `Advertising.policy().skipRestriction` semantics
