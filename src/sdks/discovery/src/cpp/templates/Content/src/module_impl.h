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

#include "FireboltSDK.h"
#include "IModule.h"
/* ${IMPORTS} */
#include "${info.title.lowercase}.h"

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {


    // Types
    class JsonData_InterestResult: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_InterestResult() override = default;
  
    public:
        JsonData_InterestResult()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("appId"), &AppId);
            Add(_T("entity"), &Entity);
        }

        JsonData_InterestResult(const JsonData_InterestResult& other)
        {
            Add(_T("appId"), &AppId);
            AppId = other.AppId;
            Add(_T("entity"), &Entity);
            Entity = other.Entity;
        }

        JsonData_InterestResult& operator=(const JsonData_InterestResult& other)
        {
            Add(_T("appId"), &AppId);
            AppId = other.AppId;
            Add(_T("entity"), &Entity);
            Entity = other.Entity;
            return (*this);
        }

    public:
        FireboltSDK::JSON::String AppId;
        Firebolt::Entity::JsonData_EntityDetails Entity;
    };

    class JsonData_InterestEvent: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_InterestEvent() override = default;
  
    public:
        JsonData_InterestEvent()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("appId"), &AppId);
            Add(_T("type"), &Type);
            Add(_T("reason"), &Reason);
            Add(_T("entity"), &Entity);
        }

        JsonData_InterestEvent(const JsonData_InterestEvent& other)
        {
            Add(_T("appId"), &AppId);
            AppId = other.AppId;
            Add(_T("type"), &Type);
            Type = other.Type;
            Add(_T("reason"), &Reason);
            Reason = other.Reason;
            Add(_T("entity"), &Entity);
            Entity = other.Entity;
        }

        JsonData_InterestEvent& operator=(const JsonData_InterestEvent& other)
        {
            Add(_T("appId"), &AppId);
            AppId = other.AppId;
            Add(_T("type"), &Type);
            Type = other.Type;
            Add(_T("reason"), &Reason);
            Reason = other.Reason;
            Add(_T("entity"), &Entity);
            Entity = other.Entity;
            return (*this);
        }

    public:
        FireboltSDK::JSON::String AppId;
        Firebolt::Discovery::JsonData_InterestType Type;
        Firebolt::Discovery::JsonData_InterestReason Reason;
        Firebolt::Entity::JsonData_EntityDetails Entity;
    };

    class ContentImpl : public IContent, public IModule {

    public:
        ContentImpl() = default;
        ContentImpl(const ContentImpl&) = delete;
        ContentImpl& operator=(const ContentImpl&) = delete;

        ~ContentImpl() override = default;

        // Methods & Events
        // signature callback params: 
        // method result properties : 
        void subscribe( IContent::IOnUserInterestNotification& notification, Firebolt::Error *err = nullptr ) override;
        void unsubscribe( IContent::IOnUserInterestNotification& notification, Firebolt::Error *err = nullptr ) override;

        /*
         requestUserInterest
         Provide information about the entity currently displayed or selected on the screen.
         */
        InterestResult requestUserInterest( const Discovery::InterestType& type, const Discovery::InterestReason& reason, Firebolt::Error *err = nullptr ) override;

    };

}//namespace ${info.Title}
}${end.if.implementations}
