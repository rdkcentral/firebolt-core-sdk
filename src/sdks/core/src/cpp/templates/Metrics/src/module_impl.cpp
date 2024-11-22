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

#include "${info.title.lowercase}_impl.h"


${if.implementations}
namespace Firebolt {
namespace ${info.Title} {
${if.providers}
/* ${PROVIDERS} */${end.if.providers}

/* ready - Inform the platform that your app is minimally usable. This method is called automatically by `Lifecycle.ready()` */
    bool ${info.Title}Impl::ready( Firebolt::Error *err )  
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;
        FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
        if (transport != nullptr) {
        
            JsonObject jsonParameters;
    
            WPEFramework::Core::JSON::Boolean jsonResult;
            status = transport->Invoke("${info.title.lowercase}.ready", jsonParameters, jsonResult);
            if (status == Firebolt::Error::None) {
                FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Metrics.ready is successfully invoked");
                success = jsonResult.Value();
            }

        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        }
        if (err != nullptr) {
            *err = status;
        }

        return success;
    }


  /* signIn - Log a sign In event, called by Discovery.signIn(). */
    bool ${info.Title}Impl::signIn( Firebolt::Error *err )  
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;
        FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
        if (transport != nullptr) {
        
            JsonObject jsonParameters;
    
            WPEFramework::Core::JSON::Boolean jsonResult;
            status = transport->Invoke("${info.title.lowercase}.signIn", jsonParameters, jsonResult);
            if (status == Firebolt::Error::None) {
                FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Metrics.signOut is successfully invoked");
                success = jsonResult.Value();
            }

        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        }
        if (err != nullptr) {
            *err = status;
        }
        return success;

    }  
    /* signOut - Log a sign out event, called by Discovery.signOut(). */
    bool ${info.Title}Impl::signOut( Firebolt::Error *err )  
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;
        FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
        if (transport != nullptr) {
        
            JsonObject jsonParameters;
    
            WPEFramework::Core::JSON::Boolean jsonResult;
            status = transport->Invoke("${info.title.lowercase}.signOut", jsonParameters, jsonResult);
            if (status == Firebolt::Error::None) {
                FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Metrics.signOut is successfully invoked");
                success = jsonResult.Value();
            }

        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        }
        if (err != nullptr) {
            *err = status;
        }

        return success;
    }


    // Methods
    /* ${METHODS} */

    // Events
    /* ${EVENTS} */

}//namespace ${info.Title}
}${end.if.implementations}
${if.enums}

namespace WPEFramework {

/* ${ENUMS} */
}${end.if.enums}