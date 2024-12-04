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

import { jest, test, expect, beforeAll } from "@jest/globals";
import { testHarness } from "../../../../../test/Setup";
import { Lifecycle, Intents, Settings } from "../../build/javascript/src/firebolt";

let readyResolved: boolean = false;
let readyCalled: boolean = false;
let readyMetricCalled: boolean = false;
let readyMetricCalledAfterResolve: boolean = false;

testHarness.onSend = function (module: string, method: string) {
  if (module === "Lifecycle" && method === "ready") {
    readyCalled = true;
  } else if (module === "Metrics" && method === "ready") {
    readyMetricCalled = true;

    if (readyResolved) {
      readyMetricCalledAfterResolve = true;
    }
  }
};

const callback = jest.fn();

let created, activated

beforeAll(() => {
  Settings.setLogLevel('DEBUG')

  class App implements Lifecycle.Application, Lifecycle.Activatable {
    create(params: Lifecycle.CreateParameters): Promise<void> {
      created = true
      return Promise.resolve(null)
    }

    suspend(): Promise<void> {
      return Promise.resolve(null)
    }

    resume(): Promise<void> {
      return Promise.resolve(null)
    }

    destroy(): Promise<void> {
      return Promise.resolve(null)
    }

    activate(intent: Intents.NavigationIntent): Promise<void> {
      activated = true
      return Promise.resolve(null)
    }

    deactivate(): Promise<void> {
      return Promise.resolve(null)
    }

  }

  const app = new App()
  Lifecycle.provideApplication(app)
  Lifecycle.provideActivatable(app)
})

test('App moves to the "running" state next', () => {
  expect(created).toBe(true)
});

test('App moves to the "active" state next', () => {
  expect(activated).toBe(true)
});

