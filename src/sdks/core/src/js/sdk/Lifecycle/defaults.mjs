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

import MockTransport from '../Transport/MockTransport.mjs'

const emit = (value) => {
  MockTransport.event('Lifecycle', value.state, value)
}

const win = typeof window !== 'undefined' ? window : {}
const automation = win.__firebolt ? !!win.__firebolt.automation : false

export default {
  provideApplication: async function() {
    await MockTransport.request('Application.create', { params: { preload: false }})
    await MockTransport.request('Activatable.activate', { intent: { action: "launch" }})
  },

  close: function(params) {
    let reason = params.reason
    if (reason === 'remoteButton') {
//      inactive.previous = 'foreground'
//      setTimeout(() => emit(inactive), automation ? 1 : 500)
    }
    else if (['userExit', 'error'].includes(reason)) {
      // inactive.previous = 'foreground'
      // unloading.previous = 'inactive'
      // setTimeout(() => emit(inactive), automation ? 1 : 500)
      // setTimeout(() => emit(unloading), automation ? 2 : 1000)
    }
    else {
      throw "Invalid close reason"
    }
  },

  finished: function() {
    if (win.location)
      win.location.href = "about:blank"
  },
}

