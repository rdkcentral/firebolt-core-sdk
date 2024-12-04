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

const win: any = window;

let sendCalled = false
let inactiveCalled = false
let _callback: Function;
let firstId: Number

win.__firebolt = {
  transport: {
    send: function(message: string) {
      const json = JSON.parse(message)
      if (firstId === undefined) {
        firstId = json.id
      }
      sendCalled = true
      if (json.method === 'Lifecycle.onInactive') {
        inactiveCalled = true
      }
      else if (json.method === 'Device.name') {
        console.dir(json)
        _callback && setTimeout(() => {
            _callback(JSON.stringify({
              jsonrpc: '2.0',
              id: json.id,
              result: 'Test Name'
            }))
        }, 100)
      }
    },
    receive: function(callback: Function) {
      _callback = callback
    }
  }
}

import { test, expect, beforeAll } from "@jest/globals";
import { Lifecycle, Device } from "../../build/javascript/src/firebolt";
import { DefaultApplication } from '../../../../../test/Setup'

Lifecycle.provideApplication(new DefaultApplication())

// Wire up our synchronous transport layer before the SDK loads
beforeAll(() => {
  return new Promise((resolve, reject) => {
    setTimeout(resolve, 1000);
  });
});

test("Transport injected before SDK", () => {
  // NOTE: this assumes an implementation detail that we start at 1 (we do at time of this test writing)
  //       this isn't the best test, since there's no requirement that we start at 1 or even use numbers
  //       at all (could be strings or even null).
  //       if this test ever fails, we should find a better way to test that we didn't miss any requests
  expect(firstId).toBe(1)
});

test("Transport send method working", () => {
  expect(sendCalled).toBe(true);
});

test("Transport `receive` callback wired up", () => {
  return Device.name().then((name) => {
    expect(name).toBe("Test Name");
  });
});
