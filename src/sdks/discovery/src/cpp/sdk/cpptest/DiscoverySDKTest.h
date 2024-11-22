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

class DiscoverySDKTest {
    class OnUserInterestNotification : public Firebolt::Content::IContent::IOnUserInterestNotification {
    public:
        void onUserInterest( const Firebolt::Content::InterestEvent& ) override;
    };

public:
    DiscoverySDKTest() = default;
    virtual ~DiscoverySDKTest() = default;

    static void CreateFireboltInstance(const std::string& url);
    static void DestroyFireboltInstance();
    static void TestDiscoveryStaticSDK();

    static void SubscribeUserInterest();
    static void UnsubscribeUserInterest();
    static void RequestUserInterest();

    static bool WaitOnConnectionReady();

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;
    static OnUserInterestNotification _userInterestNotification;

};