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

import { test, expect, beforeAll } from "@jest/globals";
import { Keyboard, Settings } from "../../build/javascript/src/firebolt-manage";

const state = {
  cb: null,
  eventId: null,
  pending: []
}

class MockProviderBroker {

  constructor() {
  }

  send(parsed) {
    if (parsed.method === 'Keyboard.provide') {
      state.eventId = parsed.id
    }
    if ((parsed.method === 'keyboard.standardResponse') || (parsed.method === 'keyboard.standardError')) {
      let pending = state.pending.find(p => p.correlationId === parsed.params.correlationId)
      state.pending = state.pending.filter(p => p.correlationId === parsed.params.correlationId)
      if (pending) {
        pending.callback(parsed)
      }
    }
  }

  receive(callback) {
    state.cb = callback
  }

  async triggerProvider(msg, providerCallback) {
    let fullMsg = {
      jsonrpc: '2.0',
      id: state.eventId,
      result: {
        correlationId: '' + Math.round((Math.random() * 1000000)),
        parameters: msg
      }
    }
    state.pending.push({
      correlationId: fullMsg.result.correlationId,
      callback: providerCallback
    })
    state.cb(fullMsg)
  }
}
const broker = new MockProviderBroker()
let provider = null

beforeAll(async () => {
  Settings.setLogLevel('DEBUG')
  window['__firebolt'].transport = new MockProviderBroker()
  provider = new DelegatingKBProvider(new KBProvider())
  Keyboard.provide(provider);
})

class DelegatingKBProvider implements Keyboard.Keyboard {
  delegate: Keyboard.Keyboard;
  constructor(delegate: Keyboard.Keyboard) {
    this.delegate = delegate;
  }
  standard(message: string): Promise<string> {
    return this.delegate.standard(message)
  }

  password(message?: string): Promise<string> {
    return this.delegate.password(message)
  }

  email(type: Keyboard.EmailUsage, message?: string): Promise<string> {
    return this.delegate.email(type, message)
  }
}

class KBProvider implements Keyboard.Keyboard {
  standard(message: string): Promise<string> {
    return Promise.resolve(null)
  }

  email(type: Keyboard.EmailUsage, message?: string): Promise<string> {
    return Promise.resolve(null)
  }

  password(message?: string): Promise<string> {
    return Promise.resolve(null)
  }
}

test("Keyboard.provide() declarations", () => {
  Keyboard.provide(new KBProvider());
  expect(1).toBe(1);
});

// Events Test cases

// test("Keyboard.listen() for requestEmail event", () => {
//   return Keyboard.listen("requestEmail", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.once() for requestEmail event", () => {
//   return Keyboard.once("requestEmail", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.listen() for requestPassword event", () => {
//   return Keyboard.listen("requestPassword", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.once() for requestPassword event", () => {
//   return Keyboard.once("requestPassword", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.listen() for requestStandard event", () => {
//   return Keyboard.listen("requestStandard", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.once() for requestStandard event", () => {
//   return Keyboard.once("requestStandard", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.clear()", () => {
//   const result = Keyboard.clear(2);
//   expect(result).toBeFalsy();
// });
