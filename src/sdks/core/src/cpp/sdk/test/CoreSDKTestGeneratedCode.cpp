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

#include <iostream>

#include "Module.h"
#include "firebolt.h"
#include "CoreSDKTestStaticCode.h"
#include "CoreSDKTestGeneratedCode.h"

using namespace std;
bool CoreSDKTestGeneratedCode::_connected;

void CoreSDKTestGeneratedCode::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
   cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
   _connected = connected;
}

void CoreSDKTestGeneratedCode::CreateFireboltInstance()
{
    const std::string config = _T("{\
            \"waitTime\": 1000,\
            \"logLevel\": \"Info\",\
            \"workerPool\":{\
            \"queueSize\": 8,\
            \"threadCount\": 3\
            },\
            \"wsUrl\": \"ws://127.0.0.1:9998\"\
            }");

    _connected = false;
    Firebolt::IFireboltAccessor::Instance().Initialize(config);
    Firebolt::IFireboltAccessor::Instance().Connect(ConnectionChanged);
}

void CoreSDKTestGeneratedCode::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
    Firebolt::IFireboltAccessor::Instance().Deinitialize();
    Firebolt::IFireboltAccessor::Instance().Dispose();
}

bool CoreSDKTestGeneratedCode::WaitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (_connected == false)) {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        SleepMs(sleepSlot);
        waiting -= sleepSlot;
    }
    return _connected;
}

void CoreSDKTestGeneratedCode::TestCoreStaticSDK()
{
    FireboltSDK::Tests::Main<FireboltSDK::CoreTestStaticCode>();
}

void CoreSDKTestGeneratedCode::GetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().Name(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get DeviceName = " << name.c_str() << endl;
    } else {
        cout << "Get DeviceName status = " << static_cast<int>(error) << endl;
    }
}

