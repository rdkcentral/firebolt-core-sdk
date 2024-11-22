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
#include "DiscoverySDKTest.h"

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
    if (DiscoverySDKTest::WaitOnConnectionReady()) {
        
        runTest(DiscoverySDKTest::SubscribeUserInterest, "SubscribeUserInterest");
        runTest(DiscoverySDKTest::UnsubscribeUserInterest, "UnsubscribeUserInterest");
        runTest(DiscoverySDKTest::RequestUserInterest, "RequestUserInterest");

        if (allTestsPassed) {
            cout << "============================" << endl;
            cout << "ALL DISCOVERY SDK TESTS SUCCEEDED!" << endl;
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
        cout << "Discovery Test not able to connect with server..." << endl;
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
                printf("./TestFireboltDiscovery -u ws://ip:port\n");
                exit(1);
        }
    }

    printf("Firebolt Discovery SDK Test\n");

    DiscoverySDKTest::CreateFireboltInstance(url);
    RunAllTests();
    DiscoverySDKTest::DestroyFireboltInstance();

    return 0;
}