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

class ManageSDKTest {
    class OnAudioDescriptionsEnabledChangedNotification : public Firebolt::AudioDescriptions::IAudioDescriptions::IOnEnabledChangedNotification {
    public:
        void onEnabledChanged( const bool ) override;
    };

    class OnDeviceNameChangedNotification : public Firebolt::Device::IDevice::IOnDeviceNameChangedNotification {
    public:
        void onDeviceNameChanged( const std::string& ) override;
    };

    class OnFontFamilyChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontFamilyChangedNotification {
        void onFontFamilyChanged( const Firebolt::Accessibility::FontFamily& ) override;
    };

    class OnBackgroundOpacityChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundOpacityChangedNotification {
        void onBackgroundOpacityChanged( const float ) override;
    };

    class OnPreferredAudioLanguagesChangedNotification : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification {
    public:
        void onPreferredAudioLanguagesChanged( const std::vector<std::string>& ) override;
    };

    class OnAllowACRCollectionChangedNotification : public Firebolt::Privacy::IPrivacy::IOnAllowACRCollectionChangedNotification {
    public:
        void onAllowACRCollectionChanged( const bool ) override;
    };

    class OnSignInNotification : public Firebolt::Discovery::IDiscovery::IOnSignInNotification {
    public:
        void onSignIn( const Firebolt::Discovery::Event& ) override;
    };

    class OnSignOutNotification : public Firebolt::Discovery::IDiscovery::IOnSignOutNotification {
    public:
        void onSignOut( const Firebolt::Discovery::Event& ) override;
    };

    class KeyboardProvider : public Firebolt::Keyboard::IKeyboardProvider {
    public:
        KeyboardProvider();
        ~KeyboardProvider() override = default;
        void standard( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session ) override;
        void password( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session ) override;
        void email( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session ) override;
        void SendMessage(bool response);

    private:
        void startKeyboardSession(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session);

    private:
        std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> _session;
        Firebolt::Keyboard::KeyboardParameters _parameters;
        bool _keyInput;
    };
    class AcknowledgeChallengeProvider : public Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeProvider {
    public:
        AcknowledgeChallengeProvider();
        ~AcknowledgeChallengeProvider() override = default;
        void challenge( const Firebolt::AcknowledgeChallenge::Challenge& parameters, std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> session ) override;
        void SendMessage(bool response);

    private:
        void startAcknowledgeChallengeSession(const Firebolt::AcknowledgeChallenge::Challenge& parameters, std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> session);

    private:
        std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> _session;
        Firebolt::AcknowledgeChallenge::Challenge _parameters;
        bool _challengeInput;
    };
    class PinChallengeProvider : public Firebolt::PinChallenge::IPinChallengeProvider {
    public:
        PinChallengeProvider();
        ~PinChallengeProvider() override = default;
        void challenge( const Firebolt::PinChallenge::PinChallenge& parameters, std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> session ) override;
        void SendMessage(bool response);

    private:
        void startPinChallengeSession(const Firebolt::PinChallenge::PinChallenge& parameters, std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> session);

    private:
        std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> _session;
        Firebolt::PinChallenge::PinChallenge _parameters;
        bool _challengeInput;
    };

public:
    ManageSDKTest() = default;
    virtual ~ManageSDKTest() = default;

    static void CreateFireboltInstance(const std::string& url);
    static void DestroyFireboltInstance();
    static void TestManageStaticSDK();

    static void GetAdvertisingSkipRestriction();
    static void SetAdvertisingSkipRestriction();
    static void ResetAdvertisingIdentifier();

    static void SetAccountSession();

    static void GetAudioDescriptionsEnabled();
    static void SetAudioDescriptionsEnabled();
    static void SubscribeAudioDescriptionsEnabledChanged();
    static void UnsubscribeAudioDescriptionsEnabledChanged();

    static void GetDeviceName();
    static void SetDeviceName();
    static void SubscribeDeviceNameChanged();
    static void UnsubscribeDeviceNameChanged();

    static void GetClosedCaptionsBackgroundOpacity();
    static void SetClosedCaptionsBackgroundOpacity();
    static void SubscribeClosedCaptionsBackgroundOpacityChanged();
    static void UnsubscribeClosedCaptionsBackgroundOpacityChanged();

    static void GetClosedCaptionsFontFamily();
    static void SetClosedCaptionsFontFamily();
    static void SubscribeClosedCaptionsFontFamilyChanged();
    static void UnsubscribeClosedCaptionsFontFamilyChanged();

    static void GetLocalizationPreferredAudioLanguages();
    static void SetLocalizationPreferredAudioLanguages();
    static void SubscribeLocalizationPreferredAudioLanguagesChanged();
    static void UnsubscribeLocalizationPreferredAudioLanguagesChanged();

    static void GetPrivacyAllowACRCollection();
    static void SetPrivacyAllowACRCollection();
    static void SubscribePrivacyAllowACRCollectionChanged();
    static void UnsubscribePrivacyAllowACRCollectionChanged();
    static void GetPrivacySettings();

    static void SubscribeDiscoverySignInNotification();
    static void UnsubscribeDiscoverySignInNotification();
    static void SubscribeDiscoverySignOutNotification();
    static void UnsubscribeDiscoverySignOutNotification();

    static void RegisterKeyboardProvider();
    static void SendResponseMessageToKeyboardProvider();
    static void SendErrorMessageToKeyboardProvider();

    static void RegisterAcknowledgeChallengeProvider();
    static void SendResponseMessageToAcknowledgeChallengeProvider();
    static void SendErrorMessageToAcknowledgeChallengeProvider();

    static void RegisterPinChallengeProvider();
    static void SendResponseMessageToPinChallengeProvider();
    static void SendErrorMessageToPinChallengeProvider();

    static void GetLocalizationAdditionalInfo();
    static void AddLocalizationAdditionalInfo();
    static void RemoveLocalizationAdditionalInfo();

    static void GetUserGrantsPermission();
    static void GrantUserGrantsPermission();
    static void DenyUserGrantsPermission();
    static void ClearUserGrantsPermission();

    static void WifiScan();
    static void WifiConnect();
    static void WifiDisconnect();

    static bool WaitOnConnectionReady();

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;
    static OnAudioDescriptionsEnabledChangedNotification _audioDescriptionEnabledChangedNotification;
    static OnDeviceNameChangedNotification _deviceNameChangedNotification;
    static OnFontFamilyChangedNotification _fontFamilyChangedNotification;
    static OnBackgroundOpacityChangedNotification _backgroundOpacityChangedNotification;
    static OnPreferredAudioLanguagesChangedNotification _preferredAudioLanguagesChangedNotification;
    static OnAllowACRCollectionChangedNotification _allowACRCollectionChangedNotification;
    static KeyboardProvider _keyboardProvider;
    static AcknowledgeChallengeProvider _acknowledgeChallengeProvider;
    static PinChallengeProvider _pinChallengeProvider;
    static OnSignInNotification _signInNotification;
    static OnSignOutNotification _signOutNotification;

    static Firebolt::Wifi::AccessPointList _apList;
};

