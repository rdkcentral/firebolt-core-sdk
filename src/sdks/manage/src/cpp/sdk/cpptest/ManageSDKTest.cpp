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

#include <unistd.h>
#include <cstring>
#include "ManageSDKTest.h"

using namespace std;
bool ManageSDKTest::_connected;
ManageSDKTest::OnAudioDescriptionsEnabledChangedNotification ManageSDKTest::_audioDescriptionEnabledChangedNotification;
ManageSDKTest::OnDeviceNameChangedNotification ManageSDKTest::_deviceNameChangedNotification;
ManageSDKTest::OnFontFamilyChangedNotification ManageSDKTest::_fontFamilyChangedNotification;
ManageSDKTest::OnBackgroundOpacityChangedNotification ManageSDKTest::_backgroundOpacityChangedNotification;
ManageSDKTest::OnPreferredAudioLanguagesChangedNotification ManageSDKTest::_preferredAudioLanguagesChangedNotification;
ManageSDKTest::OnAllowACRCollectionChangedNotification ManageSDKTest::_allowACRCollectionChangedNotification;
ManageSDKTest::OnSignInNotification ManageSDKTest::_signInNotification;
ManageSDKTest::OnSignOutNotification ManageSDKTest::_signOutNotification;
ManageSDKTest::KeyboardProvider ManageSDKTest::_keyboardProvider;
ManageSDKTest::AcknowledgeChallengeProvider ManageSDKTest::_acknowledgeChallengeProvider;
ManageSDKTest::PinChallengeProvider ManageSDKTest::_pinChallengeProvider;
Firebolt::Wifi::AccessPointList ManageSDKTest::_apList;

void ManageSDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    _connected = connected;
}

void ManageSDKTest::CreateFireboltInstance(const std::string& url)
{
    const std::string config = "{\
            \"waitTime\": 100000,\
            \"logLevel\": \"Info\",\
            \"workerPool\":{\
            \"queueSize\": 8,\
            \"threadCount\": 3\
            },\
            \"wsUrl\": " + url + "}";

    _connected = false;
    Firebolt::IFireboltAccessor::Instance().Initialize(config);
    Firebolt::IFireboltAccessor::Instance().Connect(ConnectionChanged);
}

void ManageSDKTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
    Firebolt::IFireboltAccessor::Instance().Deinitialize();
    Firebolt::IFireboltAccessor::Instance().Dispose();
}

bool ManageSDKTest::WaitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (_connected == false)) {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    return _connected;
}

template<typename T>
using EnumMap = std::unordered_map<T, string>;
template <typename T>
inline const string& ConvertFromEnum(EnumMap<T> enumMap, T type)
{
    return enumMap[type];
}
template <typename T>
inline const T ConvertToEnum(EnumMap<T> enumMap, const string& str)
{
     T value;
     for (auto element: enumMap) {
          if (element.second == str) {
              value = element.first;
              break;
          }
     }
     return value;
}

EnumMap<Firebolt::Advertising::SkipRestriction> skipRestrictionMap = {
    { Firebolt::Advertising::SkipRestriction::NONE, "none" },
    { Firebolt::Advertising::SkipRestriction::ADS_UNWATCHED, "adsUnwatched" },
    { Firebolt::Advertising::SkipRestriction::ADS_ALL, "adsAll" },
    { Firebolt::Advertising::SkipRestriction::ALL, "all" }};
void ManageSDKTest::GetAdvertisingSkipRestriction()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Advertising::SkipRestriction skipRestriction = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().skipRestriction(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Advertising SkipRestriction is success : " << ConvertFromEnum<Firebolt::Advertising::SkipRestriction>(skipRestrictionMap, skipRestriction) << endl;
    } else {
        cout << "Get Advertising SkipRestriction status: " <<  static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::SetAdvertisingSkipRestriction()
{
    Firebolt::Error error = Firebolt::Error::None;
    cout << "Support SkipRestriction -> " << endl;
    for (auto skipRestriction : skipRestrictionMap) {
         cout << skipRestriction.second << endl;
    }
    std::string skipRestriction;
    cout << "Enter new skipRestriction : ";
    cin >> skipRestriction;

    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().setSkipRestriction(ConvertToEnum<Firebolt::Advertising::SkipRestriction>(skipRestrictionMap, skipRestriction), &error);
    if (error == Firebolt::Error::None) {
        cout << "Set Advertising SkipRestriction is success " << endl;
    } else {
        cout << "Set Advertising SkipRestriction status: " <<  static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::ResetAdvertisingIdentifier()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().resetIdentifier(&error);
    if (error == Firebolt::Error::None) {
        cout << "Set Advertising Reset Identifier is success " << endl;
    } else {
        cout << "Set Advertising Reset Identifier status: " <<  static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetAccountSession()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string token = "Test";
    int32_t expiresIn = 60;
    Firebolt::IFireboltAccessor::Instance().AccountInterface().session(token, expiresIn, &error);
    if (error == Firebolt::Error::None) {
        cout << "Set Account Session is success" << endl;
    } else {
        cout << "Set Account Session status : " <<  static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetAudioDescriptionsEnabled()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool enabled = Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().enabled(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get AudioDescriptions Enabled: " << (enabled ? "true" : "false") << endl;
    } else {
        cout << "Get AudioDescriptions Enabled status: " <<  static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::SetAudioDescriptionsEnabled()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string strEnabled;
    cout << "Enter enabled or not (true/false): ";
    cin >> strEnabled;
    bool enabled = strEnabled == "true" ? true : false;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().setEnabled(enabled, &error);
    if (error == Firebolt::Error::None) {
        cout << "Set AudioDescriptions Enabled: " << endl;
    } else {
        cout << "Set AudioDescriptions Enabled status: " <<  static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::OnAudioDescriptionsEnabledChangedNotification::onEnabledChanged( const bool enabled )
{
    cout << "AudioDescriptions Enabled changed, new value --> " << (enabled ? "true" : "false") << endl;
}
void ManageSDKTest::SubscribeAudioDescriptionsEnabledChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().subscribe(_audioDescriptionEnabledChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe AudioDescriptions EnabledChange is success" << endl;
    } else {
        cout << "Subscribe AudioDescriptions EnabledChange status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribeAudioDescriptionsEnabledChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().unsubscribe(_audioDescriptionEnabledChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe AudioDescriptions EnabledChange is success" << endl;
    } else {
        cout << "Unsubscribe AudioDescriptions EnabledChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Name = " << name.c_str() << endl;
    } else {
        cout << "Get Device Name status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::SetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string name;
    cout << "Enter new device name :";
    getchar();
    getline(cin, name);
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().setName(name, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Device Name is success" << endl;
    } else {
        cout << "Set Device Name status = " << static_cast<int>(error) << endl;
    }
    cin.putback('\n');
}
void ManageSDKTest::OnDeviceNameChangedNotification::onDeviceNameChanged( const std::string& name )
{
    cout << "Name changed, new name --> " << name << endl;
}
void ManageSDKTest::SubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device NameChange is success" << endl;
    } else {
        cout << "Subscribe Device NameChange status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device NameChange is success" << endl;
    } else {
        cout << "Unsubscribe Device NameChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetClosedCaptionsBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    const float value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().backgroundOpacity(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption BackgroundOpacity = " << value << endl;
    } else {
        cout << "Get ClosedCaption BackgroundOpacity status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::SetClosedCaptionsBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    uint32_t bgOpacity;
    cout << "Enter new background opacity: ";
    scanf("%d", &bgOpacity);

    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setBackgroundOpacity(bgOpacity, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption BackgroundOpacity is success" << endl;
    } else {
        cout << "Set ClosedCaption BackgroundOpacity status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::OnBackgroundOpacityChangedNotification::onBackgroundOpacityChanged( const float opacity )
{
    cout << "BackgroundOpacity changed, new value --> " << opacity << endl;
}
void ManageSDKTest::SubscribeClosedCaptionsBackgroundOpacityChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(_backgroundOpacityChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe ClosedCaptions BackgroundOpacityChange is success" << endl;
    } else {
        cout << "Subscribe ClosedCaptions BackgroundOpacityChange status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribeClosedCaptionsBackgroundOpacityChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(_backgroundOpacityChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe ClosedCaptions BackgroundOpacityChange is success" << endl;
    } else {
        cout << "Unsubscribe ClosedCaptions BackgroundOpacityChange status = " << static_cast<int>(error) << endl;
    }
}

EnumMap<Firebolt::Accessibility::FontFamily> fontFamilyMap = {
    { Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF, "MonospacedSerif" },
    { Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF, "ProportionalSerif" },
    { Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF, "MonospacedSanserif" },
    { Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF, "ProportionalSanserif" },
    { Firebolt::Accessibility::FontFamily::SMALLCAPS, "SmallCaps" },
    { Firebolt::Accessibility::FontFamily::CURSIVE, "Cursive" },
    { Firebolt::Accessibility::FontFamily::CASUAL, "Casual" }
};
void ManageSDKTest::GetClosedCaptionsFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Accessibility::FontFamily value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontFamily(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption FontFamily value = " << ConvertFromEnum<Firebolt::Accessibility::FontFamily>(fontFamilyMap, value) << endl;
    } else {
        cout << "Get ClosedCaption FontFamily status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::SetClosedCaptionsFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string fontFamily;
    cout << "Supported font family -> " << endl;
    for (auto family : fontFamilyMap) {
         cout << family.second << endl;
    }
    cout << "Enter new font family : ";
    cin >> fontFamily;

    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontFamily(ConvertToEnum<Firebolt::Accessibility::FontFamily>(fontFamilyMap, fontFamily), &error);
    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption FontFamily is success" << endl;
    } else {
        cout << "Set ClosedCaption FontFamily status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::OnFontFamilyChangedNotification::onFontFamilyChanged( const Firebolt::Accessibility::FontFamily& family )
{
    cout << "FontFamily changed, new code --> " << ConvertFromEnum<Firebolt::Accessibility::FontFamily>(fontFamilyMap, family) << endl;
}
void ManageSDKTest::SubscribeClosedCaptionsFontFamilyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(_fontFamilyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe ClosedCaptions FontFamilyChange is success" << endl;
    } else {
        cout << "Subscribe ClosedCaptions FontFamilyChange status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribeClosedCaptionsFontFamilyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(_fontFamilyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe ClosedCaptions FontFamilyChange is success" << endl;
    } else {
        cout << "Unsubscribe ClosedCaptions FontFamilyChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::vector<std::string> languages = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Localization PreferredAudioLanguages : " << endl;
        for (auto language: languages) {
            cout << "----- > " <<language << endl;
        }
    } else {
        cout << "Get Localization PreferredAudioLanguages status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::SetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::vector<std::string> languages = { "ara", "jpn", "hin", "eng", "per", "dut" };
    cout << "Sample language code --> " << endl;
    for (auto language : languages) {
         cout << language << " ";
    }
    std::string language;
    cout << " enter new audio language code to set : ";
    getchar();
    getline(cin, language);

    std::vector<std::string> newLanguages;
    string delimeter = " ";
    char* token = strtok(const_cast<char*>(language.c_str()), delimeter.c_str());
    while (token != nullptr)
    {
        newLanguages.push_back(string(token));
        token = strtok(nullptr, delimeter.c_str());
    }
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setPreferredAudioLanguages(newLanguages, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Localization PreferredAudioLanguages is success" << endl;
    } else {
        cout << "Get Localization PreferredAudioLanguages status = " << static_cast<int>(error) << endl;
    }
    cin.putback('\n');
}
void ManageSDKTest::OnPreferredAudioLanguagesChangedNotification::onPreferredAudioLanguagesChanged( const std::vector<std::string>& languages)
{
    cout << "PreferredAudioLanguages Changed, new languages --> " << endl;
    for (auto language : languages) {
        cout << " -> " << language << endl;
    }
}
void ManageSDKTest::SubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        cout << "Subscribe Localization PreferredAudioLanguagesChange status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        cout << "Unsubscribe Localization PreferredAudioLanguagesChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetPrivacyAllowACRCollection()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool allowACRCollection = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowACRCollection(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Privacy AllowACRCollection : " << (allowACRCollection ? "true" : "false") << endl;
    } else {
        cout << "Get Privacy AllowACRCollection status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::SetPrivacyAllowACRCollection()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string strAllowACRCollection;
    cout << "Enter new allowACRCollection (true/false): ";
    cin >> strAllowACRCollection;
    bool allowACRCollection = strAllowACRCollection == "true" ? true : false;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowACRCollection(allowACRCollection , &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Privacy AllowACRCollection is success" << endl;
    } else {
        cout << "Get Privacy AllowACRCollection status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::OnAllowACRCollectionChangedNotification::onAllowACRCollectionChanged( const bool allowACRCollection )
{
    cout << "AllowACRCollection Changed, new value of allowACRCollection : " << (allowACRCollection ? "true" : "false") << endl;
}
void ManageSDKTest::SubscribePrivacyAllowACRCollectionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(_allowACRCollectionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Privacy AllowACRCollectionChanged is success" << endl;
    } else {
        cout << "Subscribe Privacy AllowACRCollectionChanged status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribePrivacyAllowACRCollectionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(_allowACRCollectionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Privacy AllowACRCollectionChanged is success" << endl;
    } else {
        cout << "Unsubscribe Privacy AllowACRCollectionChanged status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::GetPrivacySettings()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Privacy::PrivacySettings privacySettings = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().settings(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Privacy Settings -> " << endl;
        cout << "\tallowACRCollection : " << privacySettings.allowACRCollection << endl;
        cout << "\tallowResumePoints : " << privacySettings.allowResumePoints << endl;
        cout << "\tallowAppContentAdTargeting : " << privacySettings.allowAppContentAdTargeting << endl;
        cout << "\tallowCameraAnalytics : " << privacySettings.allowCameraAnalytics << endl;
        cout << "\tallowPersonalization : " << privacySettings.allowPersonalization << endl;
        cout << "\tallowPrimaryBrowseAdTargeting : " << privacySettings.allowPrimaryBrowseAdTargeting << endl;
        cout << "\tallowPrimaryContentAdTargeting : " << privacySettings.allowPrimaryContentAdTargeting << endl;
        cout << "\tallowProductAnalytics : " << privacySettings.allowProductAnalytics << endl;
        cout << "\tallowRemoteDiagnostics : " << privacySettings.allowRemoteDiagnostics << endl;
        cout << "\tallowUnentitledPersonalization : " << privacySettings.allowUnentitledPersonalization << endl;
        cout << "\tallowUnentitledResumePoints : " << privacySettings.allowUnentitledResumePoints << endl;
        cout << "\tallowWatchHistory : " << privacySettings.allowWatchHistory << endl;
    } else {
        cout << "Get Privacy Settings status = " << static_cast<int>(error) << endl;
    }

}

void ManageSDKTest::OnSignInNotification::onSignIn( const Firebolt::Discovery::Event& event )
{
    cout << "Discovery SignIn Event for appId --> " << event.appId << endl;
}
void ManageSDKTest::SubscribeDiscoverySignInNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(_signInNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Discovery SignIn Notification is success" << endl;
    } else {
        cout << "Subscribe Discovery SignIn Notification status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribeDiscoverySignInNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(_signInNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Discovery SignIn Notification is success" << endl;
    } else {
        cout << "Unsubscribe Discovery SignIn Notification status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::OnSignOutNotification::onSignOut( const Firebolt::Discovery::Event& event )
{
    cout << "Discovery SignOut Event for appId --> " << event.appId << endl;
}
void ManageSDKTest::SubscribeDiscoverySignOutNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(_signOutNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Discovery SignOut Notification is success" << endl;
    } else {
        cout << "Subscribe Discovery SignOut Notification status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::UnsubscribeDiscoverySignOutNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(_signOutNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Discovery SignOut Notification is success" << endl;
    } else {
        cout << "Unsubscribe Discovery SignOut Notification status = " << static_cast<int>(error) << endl;
    }
}

ManageSDKTest::KeyboardProvider::KeyboardProvider()
    : _session(nullptr)
    , _parameters()
    , _keyInput(false)
{
}
void ManageSDKTest::KeyboardProvider::SendMessage(bool response)
{
    if (_keyInput) {
        cout << " Invoking _session->focus " << endl;
        _session->focus();
        getchar();

        string key;
        cout << _parameters.message << " : ";
        getline(cin, key);
        if (response) {
            Firebolt::Keyboard::KeyboardResult keyboardResult;
            keyboardResult.text = key;
            keyboardResult.canceled = false;
            cout << " Invoking _session->result " << endl;
            _session->result(keyboardResult);
        } else {
            Firebolt::Keyboard::KeyboardError keyboardError;
            keyboardError.code = 123;
            keyboardError.message = key;
            keyboardError.data = "nothing to send";
            cout << " Invoking _session->error " << endl;
            _session->error(keyboardError);
        }
        _keyInput = false;
        cin.putback('\n');
    } else {
        cout << " there is no active keyboard input session " << endl;
    }
}
void ManageSDKTest::KeyboardProvider::standard(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    cout << "KeyboardProvider Standard is invoked" << endl;
    startKeyboardSession(parameters, std::move(session));
}
void ManageSDKTest::KeyboardProvider::password(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    cout << "KeyboardProvider Password is invoked" << endl;
    startKeyboardSession(parameters, std::move(session));
}
void ManageSDKTest::KeyboardProvider::email(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    cout << "KeyboardProvider Email is invoked" << endl;
    startKeyboardSession(parameters, std::move(session));
}
void ManageSDKTest::KeyboardProvider::startKeyboardSession( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session )
{
    _session = std::move(session);
    _parameters = parameters;
    _keyInput = true;
}
void ManageSDKTest::RegisterKeyboardProvider()
{
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().provide(_keyboardProvider);
}
void ManageSDKTest::SendResponseMessageToKeyboardProvider()
{
    _keyboardProvider.SendMessage(true);
}
void ManageSDKTest::SendErrorMessageToKeyboardProvider()
{
    _keyboardProvider.SendMessage(false);
}

ManageSDKTest::AcknowledgeChallengeProvider::AcknowledgeChallengeProvider()
    : _session(nullptr)
    , _parameters()
    , _challengeInput(false)
{
}
void ManageSDKTest::AcknowledgeChallengeProvider::SendMessage(bool response)
{
    if (_challengeInput) {
        cout << " Invoking _session->focus " << endl;
        _session->focus();
        cout << " capability : " << _parameters.capability << endl;
        cout << " id : " << _parameters.requestor.id << endl;
        cout << " name : " << _parameters.requestor.name << endl;
        if (response) {
            Firebolt::AcknowledgeChallenge::GrantResult challengeResult;
            challengeResult.granted = true;
            cout << " Invoking _session->result " << endl;
            _session->result(challengeResult);
        } else {
            string key;
            getline(cin, key);

            Firebolt::AcknowledgeChallenge::AcknowledgeChallengeError challengeError;
            challengeError.code = 234;
            challengeError.message = key;
            cout << " Invoking _session->error " << endl;
            _session->error(challengeError);
            cin.putback('\n');
        }
        _challengeInput = false;
    } else {
        cout << " there is no active acknowledge challenge input session " << endl;
    }
}
void ManageSDKTest::AcknowledgeChallengeProvider::challenge(const Firebolt::AcknowledgeChallenge::Challenge& parameters, std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> session)
{
    cout << "AcknowledgeChallengeProvider challenge is invoked" << endl;
    startAcknowledgeChallengeSession(parameters, std::move(session));
}
void ManageSDKTest::AcknowledgeChallengeProvider::startAcknowledgeChallengeSession( const Firebolt::AcknowledgeChallenge::Challenge& parameters, std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> session )
{
    _session = std::move(session);
    _parameters = parameters;
    _challengeInput = true;
}
void ManageSDKTest::RegisterAcknowledgeChallengeProvider()
{
    Firebolt::IFireboltAccessor::Instance().AcknowledgeChallengeInterface().provide(_acknowledgeChallengeProvider);
}
void ManageSDKTest::SendResponseMessageToAcknowledgeChallengeProvider()
{
    _acknowledgeChallengeProvider.SendMessage(true);
}
void ManageSDKTest::SendErrorMessageToAcknowledgeChallengeProvider()
{
    _acknowledgeChallengeProvider.SendMessage(false);
}

ManageSDKTest::PinChallengeProvider::PinChallengeProvider()
    : _session(nullptr)
    , _parameters()
    , _challengeInput(false)
{
}
void ManageSDKTest::PinChallengeProvider::SendMessage(bool response)
{
    if (_challengeInput) {
        cout << " Invoking _session->focus " << endl;
        _session->focus();
        cout << " pinSpace : " << static_cast<int>(_parameters.pinSpace) << endl;
        if (_parameters.capability.has_value()) {
            cout << " capability : " << _parameters.capability.value() << endl;
        }
        cout << " id : " << _parameters.requestor.id << endl;
        cout << " name : " << _parameters.requestor.name << endl;

        if (response) {
            Firebolt::PinChallenge::PinChallengeResult challengeResult;
            challengeResult.granted = true;
            challengeResult.reason = Firebolt::PinChallenge::ResultReason::CORRECT_PIN;
            cout << " Invoking _session->result " << endl;
            _session->result(challengeResult);
        } else {
            string key;
            getline(cin, key);

            Firebolt::PinChallenge::PinChallengeError challengeError;
            challengeError.code = 234;
            challengeError.message = key;
            cout << " Invoking _session->error " << endl;
            _session->error(challengeError);
            cin.putback('\n');
        }
        _challengeInput = false;
    } else {
        cout << " there is no active pin challenge input session " << endl;
    }
}
void ManageSDKTest::PinChallengeProvider::challenge(const Firebolt::PinChallenge::PinChallenge& parameters, std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> session)
{
    cout << "PinChallengeProvider challenge is invoked" << endl;
    startPinChallengeSession(parameters, std::move(session));
}
void ManageSDKTest::PinChallengeProvider::startPinChallengeSession( const Firebolt::PinChallenge::PinChallenge& parameters, std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> session )
{
    _session = std::move(session);
    _parameters = parameters;
    _challengeInput = true;
}
void ManageSDKTest::RegisterPinChallengeProvider()
{
    Firebolt::IFireboltAccessor::Instance().PinChallengeInterface().provide(_pinChallengeProvider);
}
void ManageSDKTest::SendResponseMessageToPinChallengeProvider()
{
    _pinChallengeProvider.SendMessage(true);
}
void ManageSDKTest::SendErrorMessageToPinChallengeProvider()
{
    _pinChallengeProvider.SendMessage(false);
}

void ManageSDKTest::GetLocalizationAdditionalInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Localization::Info info = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&error);
    if (error == Firebolt::Error::None) {
        cout << "AdditionalInfo is success, Info : " << endl;
        for (auto element : info) {
           cout << " " << element.first << " : " <<  element.second << endl;
        }
    } else {
        cout << "AdditionalInfo call status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::AddLocalizationAdditionalInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string key;
    cout << "Enter new key :";
    getchar();
    getline(cin, key);
    std::string value;
    cout << "Enter new value :";
    getline(cin, value);

    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().addAdditionalInfo(key, value, &error);
    if (error == Firebolt::Error::None) {
        cout << "Add AdditionalInfo is success" << endl;
    } else {
        cout << "Add AdditionalInfo status = " << static_cast<int>(error) << endl;
    }

    cin.putback('\n');
}
void ManageSDKTest::RemoveLocalizationAdditionalInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string key;
    cout << "Enter key to be removed :";
    getchar();
    getline(cin, key);

    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().removeAdditionalInfo(key, &error);
    if (error == Firebolt::Error::None) {
        cout << "Remove AdditionalInfo is success" << endl;
    } else {
        cout << "Remove AdditionalInfo status = " << static_cast<int>(error) << endl;
    }

    cin.putback('\n');
}

void ManageSDKTest::GetUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    cout << "Enter appId :";
    getchar();
    std::string appId;
    getline(cin, appId);

    std::vector<Firebolt::UserGrants::GrantInfo> grantInfo = Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().app(appId, &error);
    if (error == Firebolt::Error::None) {
        cout << "Get UserGrants Permission is success" << endl;
	if (grantInfo.size() > 0) {
            cout << "Grant Permission list : " << endl;
            for (auto info : grantInfo) {
                cout << "GrantState : " << static_cast<int>(info.state) << endl;
                cout << "Capability : " << info.capability << endl;
                cout << "Role : " << static_cast<int>(info.role) << endl;
                cout << "Lifespan : " << static_cast<int>(info.lifespan) << endl;
            }
	}
    } else {
        cout << "Get UserGrants Permission status = " << static_cast<int>(error) << endl;
    }

    cin.putback('\n');
}
void ManageSDKTest::GrantUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::UserGrants::GrantModificationOptions grantModificationOptions;
    cout << "Enter appId :";
    getchar();
    std::string appId;
    getline(cin, appId);
    grantModificationOptions.appId = std::make_optional<std::string>(appId);

    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().grant(Firebolt::Capabilities::Role::USE, "xrn:firebolt:capability:device:model", grantModificationOptions, &error);
    if (error == Firebolt::Error::None) {
        cout << "Grant UserGrants Permission is success" << endl;
    } else {
        cout << "Grant UserGrants Permission status = " << static_cast<int>(error) << endl;
    }

    cin.putback('\n');
}
void ManageSDKTest::DenyUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::UserGrants::GrantModificationOptions grantModificationOptions;
    cout << "Enter appId :";
    getchar();
    std::string appId;
    getline(cin, appId);
    grantModificationOptions.appId = std::make_optional<std::string>(appId);

    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().deny(Firebolt::Capabilities::Role::USE, "xrn:firebolt:capability:device:model", grantModificationOptions, &error);
    if (error == Firebolt::Error::None) {
        cout << "Deny UserGrants Permission is success" << endl;
    } else {
        cout << "Deny UserGrants Permission status = " << static_cast<int>(error) << endl;
    }

    cin.putback('\n');
}
void ManageSDKTest::ClearUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::UserGrants::GrantModificationOptions grantModificationOptions;
    cout << "Enter appId :";
    getchar();
    std::string appId;
    getline(cin, appId);
    grantModificationOptions.appId = std::make_optional<std::string>(appId);

    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().clear(Firebolt::Capabilities::Role::USE, "xrn:firebolt:capability:device:model", grantModificationOptions, &error);
    if (error == Firebolt::Error::None) {
        cout << "Clear UserGrants Permission is success" << endl;
    } else {
        cout << "Clear UserGrants Permission status = " << static_cast<int>(error) << endl;
    }

    cin.putback('\n');
}

void PrintAP(const Firebolt::Wifi::AccessPoint ap)
{
    if (ap.ssid.has_value()) {
        cout << " SSID : " << ap.ssid.value() << endl;
    }
    if (ap.securityMode.has_value()) {
        cout << " SecurityMode : " << static_cast<int>(ap.securityMode.value()) << endl;
    }
    if (ap.signalStrength.has_value()) {
        cout << " SignalStrength : " << ap.signalStrength.value() << endl;
    }
    if (ap.frequency.has_value()) {
        cout << " Frequency : " << ap.frequency.value() << endl;
    }
}
void PrintAPList(const Firebolt::Wifi::AccessPointList& apList)
{
    if (apList.list.has_value()) {
        cout<< "list ---->" << endl;
        uint32_t index = 0;
        for (const auto ap : apList.list.value()) {
            cout << index << ". " << endl;
            PrintAP(ap);
            cout << endl;
            index++;
        }
    } else {
        cout << "empty list " << endl;
    }
}
void ManageSDKTest::WifiScan()
{
    Firebolt::Error error = Firebolt::Error::None;
    int32_t timeout = -1;
    _apList = Firebolt::IFireboltAccessor::Instance().WifiInterface().scan(timeout, &error);
    if (error == Firebolt::Error::None) {
        cout << "Wifi Scan is success, ";
	PrintAPList(_apList);
    } else {
        cout << "Wifi Scan status = " << static_cast<int>(error) << endl;
    }
}
void ManageSDKTest::WifiConnect()
{
    Firebolt::Error error = Firebolt::Error::None;
    if (_apList.list.has_value()) {
        cout << "Scanned access pointlist : " << endl;
        PrintAPList(_apList);
        cout << "Select access point from the list: enter index : ";
        int32_t index;
        cin >> index;
        Firebolt::Wifi::AccessPoint ap = _apList.list.value()[index];
        std::string passphrase;
        cout << "Enter passphrase to connect ";
        cin >> passphrase;

        string ssid = ap.ssid.has_value() ? ap.ssid.value() : "";
        printf("%s:%s:%d _apList.list.value()[index] = %s\n", __FILE__, __func__, __LINE__, ssid.c_str());
        Firebolt::Wifi::WifiSecurityMode securityMode = ap.securityMode.has_value() ? ap.securityMode.value() : Firebolt::Wifi::WifiSecurityMode::NONE;
        Firebolt::Wifi::AccessPoint connectedAP = Firebolt::IFireboltAccessor::Instance().WifiInterface().connect(ssid, passphrase, securityMode , &error);
        if (error == Firebolt::Error::None) {
            cout << "Wifi Connect is success, ";
            PrintAP(connectedAP);
        } else {
            cout << "Wifi Connect status = " << static_cast<int>(error) << endl;
        }
    } else {
        cout << "Empty AP list, please initiate scan before trying connect " << endl;
    }
}
void ManageSDKTest::WifiDisconnect()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().WifiInterface().disconnect(&error);
    if (error == Firebolt::Error::None) {
        cout << "Wifi Disconnect is success, ";
    } else {
        cout << "Wifi Disconnect status = " << static_cast<int>(error) << endl;
    }
}
