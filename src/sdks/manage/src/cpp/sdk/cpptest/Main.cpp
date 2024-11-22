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

#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "ManageSDKTest.h"

using namespace std;

const char* options = ":hu:";

void RunAllTests() {
    bool allTestsPassed = true;
    vector<string> errorMessages;

    auto runTest = [&allTestsPassed, &errorMessages](auto testFunction, const string& testName) {
        try {
            testFunction();
        } catch (const exception& e) {
            errorMessages.push_back("Test " + testName + " failed: " + e.what());
            allTestsPassed = false;
        }
    };

    // Ensure the connection is ready before running tests
    if (ManageSDKTest::WaitOnConnectionReady()) {
        // Advertising methods
        runTest(ManageSDKTest::GetAdvertisingSkipRestriction, "GetAdvertisingSkipRestriction");
        runTest(ManageSDKTest::SetAdvertisingSkipRestriction, "SetAdvertisingSkipRestriction");
        runTest(ManageSDKTest::ResetAdvertisingIdentifier, "ResetAdvertisingIdentifier");

        // Account methods
        runTest(ManageSDKTest::SetAccountSession, "SetAccountSession");

        // AudioDescriptions methods
        runTest(ManageSDKTest::GetAudioDescriptionsEnabled, "GetAudioDescriptionsEnabled");
        runTest(ManageSDKTest::SetAudioDescriptionsEnabled, "SetAudioDescriptionsEnabled");
        runTest(ManageSDKTest::SubscribeAudioDescriptionsEnabledChanged, "SubscribeAudioDescriptionsEnabledChanged");
        runTest(ManageSDKTest::UnsubscribeAudioDescriptionsEnabledChanged, "UnsubscribeAudioDescriptionsEnabledChanged");

        // Device methods
        runTest(ManageSDKTest::GetDeviceName, "GetDeviceName");
        runTest(ManageSDKTest::SetDeviceName, "SetDeviceName");
        runTest(ManageSDKTest::SubscribeDeviceNameChanged, "SubscribeDeviceNameChanged");
        runTest(ManageSDKTest::UnsubscribeDeviceNameChanged, "UnsubscribeDeviceNameChanged");

        // ClosedCaptions methods
        runTest(ManageSDKTest::GetClosedCaptionsBackgroundOpacity, "GetClosedCaptionsBackgroundOpacity");
        runTest(ManageSDKTest::SetClosedCaptionsBackgroundOpacity, "SetClosedCaptionsBackgroundOpacity");
        runTest(ManageSDKTest::SubscribeClosedCaptionsBackgroundOpacityChanged, "SubscribeClosedCaptionsBackgroundOpacityChanged");
        runTest(ManageSDKTest::UnsubscribeClosedCaptionsBackgroundOpacityChanged, "UnsubscribeClosedCaptionsBackgroundOpacityChanged");

        runTest(ManageSDKTest::GetClosedCaptionsFontFamily, "GetClosedCaptionsFontFamily");
        runTest(ManageSDKTest::SetClosedCaptionsFontFamily, "SetClosedCaptionsFontFamily");
        runTest(ManageSDKTest::SubscribeClosedCaptionsFontFamilyChanged, "SubscribeClosedCaptionsFontFamilyChanged");
        runTest(ManageSDKTest::UnsubscribeClosedCaptionsFontFamilyChanged, "UnsubscribeClosedCaptionsFontFamilyChanged");

        // Localization methods
        runTest(ManageSDKTest::GetLocalizationPreferredAudioLanguages, "GetLocalizationPreferredAudioLanguages");
        runTest(ManageSDKTest::SetLocalizationPreferredAudioLanguages, "SetLocalizationPreferredAudioLanguages");
        runTest(ManageSDKTest::SubscribeLocalizationPreferredAudioLanguagesChanged, "SubscribeLocalizationPreferredAudioLanguagesChanged");
        runTest(ManageSDKTest::UnsubscribeLocalizationPreferredAudioLanguagesChanged, "UnsubscribeLocalizationPreferredAudioLanguagesChanged");

        runTest(ManageSDKTest::GetLocalizationAdditionalInfo, "GetLocalizationAdditionalInfo");
        runTest(ManageSDKTest::AddLocalizationAdditionalInfo, "AddLocalizationAdditionalInfo");
        runTest(ManageSDKTest::RemoveLocalizationAdditionalInfo, "RemoveLocalizationAdditionalInfo");

        // Privacy methods
        runTest(ManageSDKTest::GetPrivacyAllowACRCollection, "GetPrivacyAllowACRCollection");
        runTest(ManageSDKTest::SetPrivacyAllowACRCollection, "SetPrivacyAllowACRCollection");
        runTest(ManageSDKTest::SubscribePrivacyAllowACRCollectionChanged, "SubscribePrivacyAllowACRCollectionChanged");
        runTest(ManageSDKTest::UnsubscribePrivacyAllowACRCollectionChanged, "UnsubscribePrivacyAllowACRCollectionChanged");

        runTest(ManageSDKTest::GetPrivacySettings, "GetPrivacySettings");

        // Discovery methods
        runTest(ManageSDKTest::SubscribeDiscoverySignInNotification, "SubscribeDiscoverySignInNotification");
        runTest(ManageSDKTest::UnsubscribeDiscoverySignInNotification, "UnsubscribeDiscoverySignInNotification");
        runTest(ManageSDKTest::SubscribeDiscoverySignOutNotification, "SubscribeDiscoverySignOutNotification");
        runTest(ManageSDKTest::UnsubscribeDiscoverySignOutNotification, "UnsubscribeDiscoverySignOutNotification");

        // UserGrants methods
        runTest(ManageSDKTest::GetUserGrantsPermission, "GetUserGrantsPermission");
        runTest(ManageSDKTest::GrantUserGrantsPermission, "GrantUserGrantsPermission");
        runTest(ManageSDKTest::DenyUserGrantsPermission, "DenyUserGrantsPermission");
        runTest(ManageSDKTest::ClearUserGrantsPermission, "ClearUserGrantsPermission");

        // Wifi methods
        // runTest(ManageSDKTest::WifiScan, "WifiScan");
        // runTest(ManageSDKTest::WifiConnect, "WifiConnect");
        // runTest(ManageSDKTest::WifiDisconnect, "WifiDisconnect");

        // Provider registration
        runTest(ManageSDKTest::RegisterKeyboardProvider, "RegisterKeyboardProvider");
        runTest(ManageSDKTest::SendResponseMessageToKeyboardProvider, "SendResponseMessageToKeyboardProvider");
        runTest(ManageSDKTest::SendErrorMessageToKeyboardProvider, "SendErrorMessageToKeyboardProvider");

        runTest(ManageSDKTest::RegisterAcknowledgeChallengeProvider, "RegisterAcknowledgeChallengeProvider");
        runTest(ManageSDKTest::SendResponseMessageToAcknowledgeChallengeProvider, "SendResponseMessageToAcknowledgeChallengeProvider");
        runTest(ManageSDKTest::SendErrorMessageToAcknowledgeChallengeProvider, "SendErrorMessageToAcknowledgeChallengeProvider");

        runTest(ManageSDKTest::RegisterPinChallengeProvider, "RegisterPinChallengeProvider");
        runTest(ManageSDKTest::SendResponseMessageToPinChallengeProvider, "SendResponseMessageToPinChallengeProvider");
        runTest(ManageSDKTest::SendErrorMessageToPinChallengeProvider, "SendErrorMessageToPinChallengeProvider");

        runTest(ManageSDKTest::GlobalSubscribeHdmiAutoLowLatencyModeCapableChanged, "GlobalSubscribeHdmiAutoLowLatencyModeCapableChanged");
        runTest(ManageSDKTest::GlobalUnsubscribeHdmiAutoLowLatencyModeCapableChanged, "GlobalUnsubscribeHdmiAutoLowLatencyModeCapableChanged");

        runTest(ManageSDKTest::GetAutoLowLatencyModeCapable, "GetAutoLowLatencyModeCapable");
        runTest(ManageSDKTest::SetAutoLowLatencyModeCapable, "SetAutoLowLatencyModeCapable");
        runTest(ManageSDKTest::GetEdidVersion, "GetEdidVersion");
        runTest(ManageSDKTest::SetEdidVersion, "SetEdidVersion");
        runTest(ManageSDKTest::GetHdmiPortInfo, "GetHdmiPortInfo");
        
        if (allTestsPassed) {
            cout << "============================" << endl;
            cout << "ALL MANAGE SDK TESTS SUCCEEDED!" << endl;
            cout << "============================" << endl;
        } else {
            cout << "============================" << endl;
            cout << "SOME TESTS FAILED:" << endl;
            for (const auto& errorMessage : errorMessages) {
                cout << errorMessage << endl;
            }
            cout << "============================" << endl;
            exit(1);
        }
    } else {
        cout << "Manage Test not able to connect with server..." << endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    int c;
    string url = "ws://127.0.0.1:9998";
    while ((c = getopt(argc, argv, options)) != -1) {
        switch (c) {
            case 'u':
                url = optarg;
                break;
            case 'h':
                printf("./TestFireboltManage -u ws://ip:port\n");
                exit(1);
        }
    }

    printf("Firebolt Manage SDK Test\n");

    ManageSDKTest::CreateFireboltInstance(url);
    RunAllTests();
    ManageSDKTest::DestroyFireboltInstance();

    return 0;
}
