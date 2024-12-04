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

/**
 * This module sets up the mock transport layer immediately, instead of letting the SDK wait 500ms
 */

if (!window.__firebolt) {
    window.__firebolt = {}
}

// wires up the mock transport w/out waiting
window.__firebolt.mockTransportLayer = true

// sets a flag that mock defaults impls can use to speed things up, e.g. Lifecycle/defaults.js
window.__firebolt.automation = true

export const sent = []

export const testHarness = {
    initialize: function(config) {
        this.emit = config.emit
    },
    onSend: function(module, method, params, id) {
        const msg = {
            module,
            method,
            params,
            id
        }
        sent.push(msg)
    }
}

window.__firebolt.testHarness = testHarness

export class DefaultApplication {
    create(params) {
        return Promise.resolve(null)
    }
    resume() {
        return Promise.resolve(null)
    }
    suspend() {
        return Promise.resolve(null)
    }
    destroy() {
        return Promise.resolve(null)
    }
}

export default testHarness