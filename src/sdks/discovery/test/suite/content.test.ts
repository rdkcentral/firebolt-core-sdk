/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
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

import { test, expect } from "@jest/globals";
import { Content, Discovery } from "../../build/javascript/src/firebolt-discovery";

test("Content.requestUserInterest()", () => {
  return Content.requestUserInterest(Discovery.InterestType.INTEREST, Discovery.InterestReason.PLAYLIST).then((interest: Content.InterestResult) => {
    const entity = interest.entity
    const appId = interest.appId
    expect(appId).toBeDefined()
    expect(entity).toBeDefined()
    expect(entity.info.title).toBe("Cool Runnings")
  })
});

test("Content.onUserInterest()", () => {
  return Content.listen('userInterest', (interest: Content.InterestEvent) => {
    const entity = interest.entity
    const appId = interest.appId
    const reason = interest.reason
    expect(interest['type']).toBeDefined()
    expect(reason).toBeDefined()
    expect(appId).toBeDefined()
    expect(entity).toBeDefined()
    expect(entity.info.title).toBe("Cool Runnings")
  })
});
