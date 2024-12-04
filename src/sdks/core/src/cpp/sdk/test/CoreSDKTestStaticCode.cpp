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

#include "Module.h"
#include "CoreSDKTestStaticCode.h"

namespace FireboltSDK {
    CoreTestStaticCode::CoreTestStaticCode()
        : Tests()
    {
        _functionMap.emplace(std::piecewise_construct, std::forward_as_tuple("Get Country Code"),
                             std::forward_as_tuple(&GetCountryCode));
    }

    /* static */ Firebolt::Error CoreTestStaticCode::GetCountryCode()
    {
        const string method = _T("localization.countryCode");
        WPEFramework::Core::ProxyType<WPEFramework::Core::JSON::String> response;
        Firebolt::Error status = FireboltSDK::Properties::Get(method, response);

        EXPECT_EQ(status, Firebolt::Error::None);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(Logger::Category::Core, Logger::Module<Tests>(), "CountryCode : %s", response->Value().c_str());
        } else {
            FIREBOLT_LOG_ERROR(Logger::Category::Core, Logger::Module<Tests>(), "Get %s status = %d\n", method.c_str(), status);
        }

        return status;
    }
}

