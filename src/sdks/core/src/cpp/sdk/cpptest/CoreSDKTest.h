/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <iostream>
#include "firebolt.h"

class CoreSDKTest {
    class OnPolicyChangedNotification : public Firebolt::Advertising::IAdvertising::IOnPolicyChangedNotification {
    public:
        void onPolicyChanged( const Firebolt::Advertising::AdPolicy& ) override;
    };
    class OnDeviceNameChangedNotification : public Firebolt::Device::IDevice::IOnDeviceNameChangedNotification {
    public:
        void onDeviceNameChanged( const std::string& ) override;
    };
    class OnAudioChangedNotification : public Firebolt::Device::IDevice::IOnAudioChangedNotification {
    public:
        void onAudioChanged( const Firebolt::Device::AudioProfiles& ) override;
    };
    class OnScreenResolutionChangedNotification : public Firebolt::Device::IDevice::IOnScreenResolutionChangedNotification {
    public:
        void onScreenResolutionChanged( const Firebolt::Device::Resolution& ) override;
    };
    class OnPreferredAudioLanguagesChangedNotification : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification {
    public:
        void onPreferredAudioLanguagesChanged( const std::vector<std::string>& ) override;
    };
    struct OnClosedCaptionsSettingsChangedNotification : public Firebolt::Accessibility::IAccessibility::IOnClosedCaptionsSettingsChangedNotification {
        void onClosedCaptionsSettingsChanged( const Firebolt::Accessibility::ClosedCaptionsSettings& ) override;
    };

    struct OnBackgroundNotification : public Firebolt::Lifecycle::ILifecycle::IOnBackgroundNotification {
        void onBackground( const Firebolt::Lifecycle::LifecycleEvent& ) override;
    };
    struct OnForegroundNotification : public Firebolt::Lifecycle::ILifecycle::IOnForegroundNotification {
        void onForeground( const Firebolt::Lifecycle::LifecycleEvent& ) override;
    };

    struct OnFriendlyNameChangedNotification : public Firebolt::SecondScreen::ISecondScreen::IOnFriendlyNameChangedNotification {
        void onFriendlyNameChanged( const std::string& ) override;
    };

    struct OnAvailableNotification : public Firebolt::Capabilities::ICapabilities::IOnAvailableNotification {
        void onAvailable( const Firebolt::Capabilities::CapabilityInfo& ) override;
    };

    struct OnNavigateToHomeIntentNotification : public Firebolt::Discovery::IDiscovery::IOnNavigateToHomeIntentNotification {
        void onNavigateTo( const Firebolt::Intents::HomeIntent& ) override;
    };
    struct OnNavigateToEntityIntentNotification : public Firebolt::Discovery::IDiscovery::IOnNavigateToEntityIntentNotification {
        void onNavigateTo( const Firebolt::Intents::EntityIntent& ) override;
    };
    struct OnNavigateToTuneIntentNotification : public Firebolt::Discovery::IDiscovery::IOnNavigateToTuneIntentNotification {
        void onNavigateTo( const Firebolt::Intents::TuneIntent& ) override;
    };
    struct KeyboardEmailAsyncResponse : public Firebolt::Keyboard::IKeyboardAsyncResponse {
        void response(const std::string&, Firebolt::Error*) override;
    };
    struct KeyboardPasswordAsyncResponse : public Firebolt::Keyboard::IKeyboardAsyncResponse {
        void response(const std::string&, Firebolt::Error*) override;
    };
    struct KeyboardStandardAsyncResponse : public Firebolt::Keyboard::IKeyboardAsyncResponse {
        void response(const std::string&, Firebolt::Error*) override;
    };

public:
    CoreSDKTest() = default;
    virtual ~CoreSDKTest() = default;

    static void CreateFireboltInstance(const std::string& url);
    static void DestroyFireboltInstance();
    static void TestCoreStaticSDK();

    static void GetAccountId();
    static void GetAccountUid();

    static void GetDeviceName();
    static void SubscribeDeviceNameChanged();
    static void UnsubscribeDeviceNameChanged();
    static void GetDeviceModel();
    static void GetDeviceSku();
    static void GetDeviceAudio();
    static void SubscribeDeviceAudioChanged();
    static void UnsubscribeDeviceAudioChanged();
    static void GetDeviceScreenResolution();
    static void SubscribeDeviceScreenResolutionChanged();
    static void UnsubscribeDeviceScreenResolutionChanged();

    static void GetLocalizationAdditionalInfo();
    static void GetLocalizationLatlon();
    static void GetLocalizationPreferredAudioLanguages();
    static void SubscribeLocalizationPreferredAudioLanguagesChanged();
    static void UnsubscribeLocalizationPreferredAudioLanguagesChanged();

    static void GetAccessibilityClosedCaptionsSettings();
    static void SubscribeAccessibilityClosedCaptionsSettingsChanged();
    static void UnsubscribeAccessibilityClosedCaptionsSettingsChanged();

    static void GetAdvertisingPolicy();
    static void SubscribeAdvertisingPolicyChanged();
    static void UnsubscribeAdvertisingPolicyChanged();
    static void BuildAdvertisingConfiguration();
    static void GetAdvertisingDeviceAttributes();

    static void InvokeKeyboardStandard();
    static void AbortKeyboardStandard();
    static void InvokeKeyboardPassword();
    static void AbortKeyboardPassword();
    static void InvokeKeyboardEmail();
    static void AbortKeyboardEmail();

    static void VerifyProfileApproveContentRating();
    static void VerifyProfileApprovePurchase();
    static void GetProfileFlags();

    static void LifecycleClose();
    static void SubscribeLifecycleBackgroundNotification();
    static void UnsubscribeLifecycleBackgroundNotification();
    static void SubscribeLifecycleForegroundNotification();
    static void UnsubscribeLifecycleForegroundNotification();

    static void GetAuthenticationDevice();
    static void GetAuthenticationSession();
    static void GetAuthenticationToken();
    static void GetAuthenticationRoot();

    static void GetCapabilitiesSupported();
    static void GetCapabilitiesAvailable();
    static void GetCapabilitiesGranted();
    static void GetCapabilitiesPermitted();
    static void GetCapabilitiesInfo();
    static void SubscribeCapabilitiesAvailableChanged();
    static void UnsubscribeCapabilitiesAvailableChanged();

    static void MetricsStartContent();
    static void MetricsStopContent();

    static void GetSecondScreenDevice();
    static void GetSecondScreenProtocols();
    static void GetSecondScreenFriendlyName();
    static void SubscribeSecondScreenFriendlyNameChanged();
    static void UnsubscribeSecondScreenFriendlyNameChanged();

    static void DiscoverySignIn();
    static void DiscoverySignOut();
    static void DiscoveryContentAccess();
    static void DiscoveryClearContentAccess();
    static void DiscoveryEntitlements();
    static void DiscoveryEntityInfo();
    static void DiscoveryPolicy();
    static void DiscoveryPurchasedContent();
    static void DiscoveryLaunch();
#ifdef POLYMORPHICS_REDUCER_METHODS
    static void DiscoveryWatched();
    static void DiscoveryWatchedReduced();
#endif
    static void SubscribeDiscoveryOnNavigateToLaunchNotification();
    static void UnsubscribeDiscoveryOnNavigateToLaunchNotification();
    static void DiscoveryWatchNext();

    static void ParametersInitialization();

    static bool WaitOnConnectionReady();

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;
    static OnPolicyChangedNotification _policyChangedNotification;
    static OnDeviceNameChangedNotification _deviceNameChangedNotification;
    static OnAudioChangedNotification _audioChangedNotification;
    static OnScreenResolutionChangedNotification _screenResolutionChangedNotification;
    static OnPreferredAudioLanguagesChangedNotification _preferredAudioLanguagesChangedNotification;
    static OnClosedCaptionsSettingsChangedNotification _closedCaptionsSettingsChangedNotification;
    static OnBackgroundNotification _backgroundNotification;
    static OnForegroundNotification _foregroundNotification;
    static OnFriendlyNameChangedNotification _friendlyNameChangedNotification;
    static OnAvailableNotification _availableNotification;
    static OnNavigateToHomeIntentNotification _navigateToHomeIntentNotification;
    static OnNavigateToEntityIntentNotification _navigateToEntityIntentNotification;
    static OnNavigateToTuneIntentNotification _navigateToTuneIntentNotification;
    static KeyboardEmailAsyncResponse _keyboardEmailAsyncResponse;
    static KeyboardPasswordAsyncResponse _keyboardPasswordAsyncResponse;
    static KeyboardStandardAsyncResponse _keyboardStandardAsyncResponse;
};

