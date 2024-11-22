/* Copyright 2023 Comcast Cable Communications Management, LLC
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


#include "${info.title.lowercase}_impl.h"

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {
${if.providers}
/* ${PROVIDERS} */${end.if.providers}

EnumMap<Firebolt::Lifecycle::LifecycleState> lifecycleStateMap = {
    { Firebolt::Lifecycle::LifecycleState::INITIALIZING, "initializing" },
    { Firebolt::Lifecycle::LifecycleState::INACTIVE, "inactive" },
    { Firebolt::Lifecycle::LifecycleState::FOREGROUND, "foreground" },
    { Firebolt::Lifecycle::LifecycleState::BACKGROUND, "background" },
    { Firebolt::Lifecycle::LifecycleState::UNLOADING, "unloading" },
    { Firebolt::Lifecycle::LifecycleState::SUSPENDED, "suspended" }
};


/* ready - Notify the platform that the app is ready */
static void readyDispatcher(const void* result) {
    Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready();
}

// localCallback to update the state
static void onReadyInnerCallback(void* notification, const void* userData, void* jsonResponse )
{
    const LifecycleImpl* selfConst = static_cast<const LifecycleImpl*>(userData);
    LifecycleImpl* self = const_cast<LifecycleImpl*>(selfConst);

    WPEFramework::Core::ProxyType<JsonData_LifecycleEvent>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonData_LifecycleEvent>*>(jsonResponse));
    ASSERT(proxyResponse.IsValid() == true);

    if (proxyResponse.IsValid() == true) {
        LifecycleEvent value;

        value.state = proxyResponse->State;
        std::string stateStr = ConvertEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, value.state);
        // Assign stateStr to currentState in ${info.Title}Impl instance
        self->currentState = stateStr;
        std::cout << "Updated the Current State to: " << self->currentState << std::endl;

        proxyResponse.Release();

    }
}
 


/* ready - Notify the platform that the app is ready */
void ${info.Title}Impl::ready(Firebolt::Error *err) {  
    Firebolt::Error status = Firebolt::Error::NotConnected;

    JsonObject jsonParameters;

    // Call Prioritize to subscribe to corresponding event, add to internalMap, and prioritize its callback
    status = FireboltSDK::Event::Instance().Prioritize<JsonData_LifecycleEvent>("lifecycle.onForeground", jsonParameters, onReadyInnerCallback, (void*)nullptr, this);
    status = FireboltSDK::Event::Instance().Prioritize<JsonData_LifecycleEvent>("lifecycle.onBackground", jsonParameters, onReadyInnerCallback, (void*)nullptr, this);
    status = FireboltSDK::Event::Instance().Prioritize<JsonData_LifecycleEvent>("lifecycle.onInactive", jsonParameters, onReadyInnerCallback, (void*)nullptr, this);
    status = FireboltSDK::Event::Instance().Prioritize<JsonData_LifecycleEvent>("lifecycle.onSuspended", jsonParameters, onReadyInnerCallback, (void*)nullptr, this);
    status = FireboltSDK::Event::Instance().Prioritize<JsonData_LifecycleEvent>("lifecycle.onUnloading", jsonParameters, onReadyInnerCallback, (void*)nullptr, this);
   
    FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
    if (transport != nullptr) {
        WPEFramework::Core::JSON::VariantContainer jsonResult;
        status = transport->Invoke("lifecycle.ready", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Lifecycle.ready is successfully invoked");

            WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job = WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>(WPEFramework::Core::ProxyType<FireboltSDK::Worker>::Create(readyDispatcher, nullptr));
            WPEFramework::Core::IWorkerPool::Instance().Submit(job);
        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in invoking lifecycle.ready: %d", status);
            if (err != nullptr) {
                *err = status;
            }
        }

    } else {
        FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        if (err != nullptr) {
            *err = status;
        }
    }
}  


/* state - return the state of the app */
std::string ${info.Title}Impl::state(Firebolt::Error *err)  {
    std::cout << "**CURRENT STATE OF THE APP::::**" << currentState << std::endl;
    return currentState;
}



/* finished - Notify the platform that the app is done unloading */
void ${info.Title}Impl::finished(Firebolt::Error *err) 
{
    Firebolt::Error status = Firebolt::Error::NotConnected;
        if(currentState == "unloading")
        {
            FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
            if (transport != nullptr) {
            
                JsonObject jsonParameters;
        
                WPEFramework::Core::JSON::VariantContainer jsonResult;
                status = transport->Invoke("lifecycle.finished", jsonParameters, jsonResult);
                if (status == Firebolt::Error::None) {
                    FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Lifecycle.finished is successfully invoked");
        
                }

            } else {
                FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
            }
        }

    return;
}

// Methods
/* ${METHODS} */

// Events
/* ${EVENTS} */

}//namespace Lifecycle
}${end.if.implementations}
${if.enums}

namespace WPEFramework {

/* ${ENUMS} */
}${end.if.enums}