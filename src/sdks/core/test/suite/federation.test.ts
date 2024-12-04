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

// NOTE: this test SHOULD NOT include Setup, since it does it's own
// setup for Firebolt SDK/TL handshake

import { test, expect, beforeAll } from "@jest/globals";
import { Lifecycle, Discovery, Entertainment, Types } from '../../build/javascript/src/firebolt'

// holds test transport layer state, e.g. callback

const state = {
  callback:(a:string) => {}
}

let pullEntityInfoListenCount = 0
let entityInfoPulled = false
let entityInfoReceived = false
let entityInfoPushed = false
let callbackWiredUp = false
let sendCalled = false
let correlationId:string
let secondRegistrationFailed = false

beforeAll(() => {
    return new Promise( (resolve, reject) => {
        const transport = {
            send: function(message: string) {
                const json = JSON.parse(message)
                sendCalled = true
                if (json.method.toLowerCase() === 'discovery.onpullentityinfo') {
                    // we'll assert on this later...
                    pullEntityInfoListenCount++
                    if (state.callback) {
                        // we'll assert on this later...
                        callbackWiredUp = true
                        let response:object = {
                            jsonrpc: '2.0',
                            id: json.id,
                            result: {
                                listening: true,
                                event: 'Discovery.onPullEntityInfo'
                            }
                        }
                        // catching errors, so all tests don't fail if this breaks
                        try {
                            state.callback(JSON.stringify(response))
                        }
                        catch (err) {
                            throw err
                            // fail silenetly (the boolean-based tests below will figure it out...)
                        }
        
                        setTimeout( _ => {
                            correlationId = '' + (Math.random() * 1000)
                            try {
                                response = {
                                    jsonrpc: '2.0',
                                    method: 'Discovery.pullEntityInfo',
                                    params: {
                                        value: {
                                            correlationId: correlationId,
                                            parameters: {
                                                entityId: "345"
                                            }    
                                        }
                                    }
                                }
        
                                state.callback(JSON.stringify(response))
        
                                state.callback(JSON.stringify({
                                    jsonrpc: '2.0',
                                    method: 'Discovery.pullEntityInfo',
                                    params: {
                                        value: {
                                            correlationId: 'this-will-fail',
                                            parameters: {
                                                entityId: "this-will-fail"
                                            }
                                        }
                                    }
                                }))
                            }
                            catch (err) {
                                throw err
                            }

                            // resolve the beforeAll promise
                            setTimeout(_ => { resolve(null) }, 500)
                        })
                    }
                }
                else if (json.method.toLowerCase() === 'discovery.entityinfo') {
                    if (correlationId && (json.params.correlationId === correlationId)) {
                        entityInfoReceived = true
                    }
                    else if (correlationId && (json.params.correlationId === 'this-will-fail')) {
                    }
                    else if (!json.params.correlationId && json.params.result.entity.identifiers.entityId === "PUSH:345") {
                        entityInfoPushed = true
                    }
                    
                    setTimeout(() => {
                        state.callback(JSON.stringify({
                            jsonrpc: '2.0',
                            id: json.id,
                            result: true
                        }))
                    }, 100)
                }
            },
            receive: function(callback: (a:string) => void) {
                // store the callback
                state.callback = callback
            }
        }
        
        const win:any = window;
        win.__firebolt.transport = transport

        const result:Discovery.EntityInfoResult = {
            "expires": "2025-01-01T00:00:00.000Z",
            "entity": {
                "identifiers": {
                "entityId": "PUSH:345"
                },
                "entityType": "program",
                "programType": Entertainment.ProgramType.MOVIE,
                "title": "Cool Runnings",
                "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                "releaseDate": "1993-01-01T00:00:00.000Z",
                "contentRatings": [
                {
                    "scheme": "US-Movie",
                    "rating": "PG"
                },
                {
                    "scheme": "CA-Movie",
                    "rating": "G"
                }
                ],
                "waysToWatch": [
                    {
                        "identifiers": {
                        "assetId": "123"
                        },
                        "expires": "2025-01-01T00:00:00.000Z",
                        "entitled": true,
                        "entitledExpires": "2025-01-01T00:00:00.000Z",
                        "offeringType": Entertainment.OfferingType.BUY,
                        "price": 2.99,
                        "audioProfile": [Types.AudioProfile.DOLBY_ATMOS],
                        "videoQuality": ["UHD"],
                        "audioLanguages": [
                        "en"
                        ],
                        "closedCaptions": [
                        "en"
                        ],
                        "subtitles": [
                        "es"
                        ],
                        "audioDescriptions": [
                        "en"
                        ]
                    }
                ]
            }
        }

        // Setup a callback that returns the correct payload
        Discovery.entityInfo((parameters:Discovery.EntityInfoParameters) => {

            console.dir(parameters)

            if (parameters.entityId === 'this-will-fail') {
                throw "Intentional Test failure"
            }

            entityInfoPulled = true
            return Promise.resolve(result)
        })

        Discovery.entityInfo(result)

        // you can't test bad signatures in TS, the compiler won't let you
        // consider moving this test to JS
        // Discovery.entityInfo(() => {}).catch(error => {
        //     secondRegistrationFailed = true
        // })

        //Lifecycle.ready()
        })
})

test('Transport was sent listeners', () => {
    expect(pullEntityInfoListenCount).toBeGreaterThan(0)
});

test('Transport was sent each listener only once', () => {
    expect(pullEntityInfoListenCount).toBe(1)
});

test('Entity Info was pulled from the app', ()=> {
    expect(callbackWiredUp).toBe(true)
    expect(entityInfoPulled).toBe(true)
    expect(entityInfoReceived).toBe(true)
});

test('Entity Info was pushed from the app', ()=> {
    expect(entityInfoPushed).toBe(true)
});

// test('Entity Info pull handler cannot be registered more than once', ()=> {
//     expect(secondRegistrationFailed).toBe(true)
// });