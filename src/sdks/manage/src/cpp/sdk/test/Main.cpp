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
#include "ManageSDKTestGeneratedCode.h"

int __cnt = 0;
int __pass = 0;

int TotalTests = 0;
int TotalTestsPassed = 0;

int main()
{
    printf("Calling CreateFireboltInstance ---\n");
    ManageSDKTestGeneratedCode::CreateFireboltInstance();

    if (ManageSDKTestGeneratedCode::WaitOnConnectionReady() == true) {
        printf("Calling GetDeviceName ---> \n");
        ManageSDKTestGeneratedCode::GetDeviceName();
        ManageSDKTestGeneratedCode::SetDeviceName();
        ManageSDKTestGeneratedCode::GetDeviceName();
    }
    ManageSDKTestGeneratedCode::DestroyFireboltInstance();
    printf("TOTAL: %i tests; %i PASSED, %i FAILED\n", TotalTests, TotalTestsPassed, (TotalTests - TotalTestsPassed));
}

