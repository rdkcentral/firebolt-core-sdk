/*
 * Copyright 2022 Comcast Cable Communications Management, LLC
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
import nopt from 'nopt'
import path from 'path'

import readline from 'readline'

import { promises } from "fs"
import { logHeader, logSuccess, logInfo, logError } from '../../../node_modules/@firebolt-js/openrpc/src/shared/io.mjs'
const { readFile, writeFile } = promises


const loadJson = file => readFile(file).then(data => JSON.parse(data.toString()))

const doImport = (source, target, clear=false, report=false) => {
    const result = JSON.parse(JSON.stringify(target))

    if (clear && report) throw "Error, cannot clear and generate a report!"

    if (clear) {
        logSuccess(` - Clearing all capabilities.`)
        result.capabilities = {}
    }

    const capabilities = methods => methods.filter(m => m.tags && m.tags.find(t => t.name === "capabilities")).map(m => m.tags.find(t => t.name === "capabilities"))

    const uses = Array.from(new Set(capabilities(source.methods).filter(c => c['x-uses']).map(c => c['x-uses']).flat()))
    const manages = Array.from(new Set(capabilities(source.methods).filter(c => c['x-manages']).map(c => c['x-manages']).flat()))
    const provides = Array.from(new Set(capabilities(source.methods).filter(c => c['x-provides']).map(c => c['x-provides']).flat()))
    const all = Array.from(new Set(uses.concat(manages).concat(provides))).sort()

    all.forEach(capability => {
      if (!result.capabilities[capability]) {
          logSuccess(`${report ? 'Missing' : 'Adding'} capability ${capability}.`)
      }
        result.capabilities[capability] = Object.assign({
          level: 'must',
          use: {
              public: uses.includes(capability),
              negotiable: true && uses.includes(capability)
          },
          manage: {
              public: manages.includes(capability),
              negotiable: true && manages.includes(capability)
          },
          provide: {
              public: provides.includes(capability),
              negotiable: true && provides.includes(capability)
          }
        }, result.capabilities[capability] || {})
        if (uses.includes(capability) != result.capabilities[capability].use.public) {
            logSuccess(` - ${report ? 'Incorrect' : 'Setting'} use.public: ${uses.includes(capability)} for ${capability}.`)
            result.capabilities[capability].use.public = uses.includes(capability)
        }
        if (manages.includes(capability) != result.capabilities[capability].manage.public) {
            logSuccess(` - ${report ? 'Incorrect' : 'Setting'} manage.public: ${manages.includes(capability)} for ${capability}.`)
            result.capabilities[capability].manage.public = manages.includes(capability)
        }
        if (provides.includes(capability) != result.capabilities[capability].provide.public) {
            logSuccess(` - ${report ? 'Incorrect' : 'Setting'} provides.public: ${provides.includes(capability)} for ${capability}.`)
            result.capabilities[capability].provide.public = provides.includes(capability)
        }
    })

    Object.keys(result.capabilities).forEach(cap => {
        if (!all.includes(cap)) {
            logInfo(`Source JSON has unused capability '${cap}'`)
        }
    })

    if (report) {
        const unused = []
        Object.entries(result.capabilities).forEach(([capability, policy]) => {
            const uses = source.methods.filter(m => m.tags && m.tags.find(t => t.name === "capabilities") && m.tags.find(t => t.name === "capabilities")['x-uses'] && m.tags.find(t => t.name === "capabilities")['x-uses'].includes(capability))
            const provides = source.methods.filter(m => m.tags && m.tags.find(t => t.name === "capabilities") && m.tags.find(t => t.name === "capabilities")['x-provides'] && m.tags.find(t => t.name === "capabilities")['x-provides'] === capability)
            const manages = source.methods.filter(m => m.tags && m.tags.find(t => t.name === "capabilities") && m.tags.find(t => t.name === "capabilities")['x-manages'] && m.tags.find(t => t.name === "capabilities")['x-manages'].includes(capability))

            if ((uses.length + provides.length + manages.length) > 0) {
                logHeader(capability)
                uses.forEach(m => logSuccess(' - use    : ' + m.name))
                if (uses.length === 0) {
                    logInfo(' - use    : none')
                }

                manages.forEach(m => logSuccess(' - manage : ' + m.name))
                if (manages.length === 0) {
                    logInfo(' - manage : none')
                }

                provides.forEach(m => logSuccess(' - provide: ' + m.name))
                if (provides.length === 0) {
                    logInfo(' - provide: none')
                }

                console.log()
            }
            else {
                unused.push(capability)
            }
        })
        logHeader('Unused capabilities:')
        unused.forEach(c => logSuccess(' - ' + c))
    }

    const caps = result.capabilities
    result.capabilities = {}
    //.filter(([_, c]) => c.level != "could")
    Object.entries(caps).sort((a, b) => a[0] < b[0] ? -1 : a[0] > b[0] ? 1 : 0).forEach(([key, value]) => {
        result.capabilities[key] = value
    })

    return result
}

const run = async(version, parsedArgs) => {
    const rpc = await loadJson('./dist/firebolt-open-rpc.json')
    let report = false
    
    if (parsedArgs.report) {
        report = true
    }

    console.log()
    logHeader(`Adding OpenRPC Capabilities`)
    
    return doImport(rpc, version, false, report)
}

export default run