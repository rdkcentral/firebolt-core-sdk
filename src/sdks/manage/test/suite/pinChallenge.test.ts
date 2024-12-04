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
import { PinChallenge } from "../../build/javascript/src/firebolt-manage";

class PCProvider implements PinChallenge.PinChallenge {
  challenge(requestor: PinChallenge.ChallengeRequestor, pinSpace: "purchase" | "content", capability?: string): Promise<PinChallenge.PinChallengeResult> {
    return Promise.resolve(null)
  }
}

test("PinChallenge.provide() declarations", () => {
  PinChallenge.provide(
    new PCProvider()
  );
  expect(1).toBe(1);
});

// Events Test cases

// test("PinChallenge.listen() for requestChallenge event", () => {
//   return PinChallenge.listen("requestChallenge", () => {}).then(
//     (res: number) => {
//       expect(res > 0).toBe(true);
//     }
//   );
// });

// test("PinChallenge.once() for requestChallenge event", () => {
//   return PinChallenge.once("requestChallenge", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("PinChallenge.clear()", () => {
//   const result = PinChallenge.clear(2);
//   expect(result).toBeFalsy();
// });
