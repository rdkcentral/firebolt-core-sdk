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

/* ${IMPORTS} */

/* ${INITIALIZATION} */

function version() {
  return new Promise( (resolve, reject) => {
    Gateway.request('Device.version').then( v => {
          v = v || {}
          v.sdk = v.sdk || {}
          v.sdk.major = parseInt('${major}')
          v.sdk.minor = parseInt('${minor}')
          v.sdk.patch = parseInt('${patch}')
          v.sdk.readable = '${readable}'
          resolve(v)    
      }).catch(error => {
          reject(error)
      })
  })
}

/* ${METHODS} */

export default {

  /* ${EVENTS_ENUM} */
  /* ${ENUM_IMPLEMENTATIONS} */

  version,
  /* ${METHOD_LIST} */

}
