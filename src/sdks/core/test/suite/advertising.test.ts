/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import { test, expect } from "@jest/globals";
import { Advertising } from "../../build/javascript/src/firebolt";

test("policy()", () => {
  return Advertising.policy().then((policy: Advertising.AdPolicy) => {
    expect(policy.skipRestriction).toBe("adsUnwatched");
    expect(policy.limitAdTracking).toBe(false);
  });
});

test("config()", () => {
  return Advertising.config({
    coppa: true,
    environment: "test",
    authenticationEntity: "Test",
  }).then((res: object) => {
    expect(typeof res).toBe("object");
  });
});

test("advertisingId()", () => {
  return Advertising.advertisingId().then((res: object) => {
    expect(typeof res).toBe("object");
  });
});

test("deviceAttributes()", () => {
  return Advertising.deviceAttributes().then((res: object) => {
    expect(typeof res).toBe("object");
  });
});

test("appBundleId()", () => {
  return Advertising.appBundleId().then((res: string) => {
    expect(res).toBe("app.operator");
    expect(typeof res).toBe("string");
  });
});

test("listen()", () => {
  return Advertising.listen((event: string, data: object) => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("once()", () => {
  return Advertising.once((event: string, data: object) => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("listen() specific Advertising event.", () => {
  return Advertising.listen("policyChanged", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() specific Advertising event.", () => {
  return Advertising.once("policyChanged", () => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("clear()", () => {
  const result: boolean = Advertising.clear(-1000);
  expect(result).toBeFalsy();
});
