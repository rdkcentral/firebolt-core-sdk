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
#include <string>
#include "DiscoverySDKTest.h"

using namespace std;
bool DiscoverySDKTest::_connected;
DiscoverySDKTest::OnUserInterestNotification DiscoverySDKTest::_userInterestNotification;

void DiscoverySDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    _connected = connected;
}

void DiscoverySDKTest::CreateFireboltInstance(const std::string& url)
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

void DiscoverySDKTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
    Firebolt::IFireboltAccessor::Instance().Deinitialize();
    Firebolt::IFireboltAccessor::Instance().Dispose();
}

bool DiscoverySDKTest::WaitOnConnectionReady()
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

void DiscoverySDKTest::OnUserInterestNotification::onUserInterest( const Firebolt::Content::InterestEvent& interest)
{
    cout << "User Interest changed notification"  << endl;
}

void DiscoverySDKTest::SubscribeUserInterest()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ContentInterface().subscribe(_userInterestNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Content.UserInterest is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("Subscribe Content.UserInterest failed. " + errorMessage);
    }
}

void DiscoverySDKTest::UnsubscribeUserInterest()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ContentInterface().unsubscribe(_userInterestNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Content.UserInterest is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("Unsubscribe Content.UserInterest failed." + errorMessage);
    }
}

void DiscoverySDKTest::RequestUserInterest()
{
    Firebolt::Discovery::InterestType type = Firebolt::Discovery::InterestType::INTEREST;
    Firebolt::Discovery::InterestReason reason = Firebolt::Discovery::InterestReason::REACTION;
    Firebolt::Error error = Firebolt::Error::None;

    Firebolt::IFireboltAccessor::Instance().ContentInterface().requestUserInterest(type, reason, &error);
    
    if (error == Firebolt::Error::None) {
        cout << "Content.requestuserInterest call is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("Content.requestUserInterest failed." + errorMessage);
    }
}
