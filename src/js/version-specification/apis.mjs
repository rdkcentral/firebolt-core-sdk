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
import path from 'path'
import { promises } from "fs"
import { exec as exec_callback } from "child_process"
import { logHeader, logSuccess, logInfo, logError } from '../../../node_modules/@firebolt-js/openrpc/src/shared/io.mjs'

const exec = async (command) => {
    return new Promise( (resolve, reject) => {
        exec_callback(command, (error, stdout, stderr) => {
            if (error) {
                reject(error)
            }
            else {
                resolve(stdout)
            }
        })
    })
}

const { readFile, writeFile } = promises

const run = async (version, parsedArgs) => {

    logHeader('Adding OpenRPC API versions')

    const loadJson = file => readFile(file).then(data => JSON.parse(data.toString()))
    const loadJsonTree = async file => {
        const json = await loadJson(file)
        const dir = path.join('.', path.dirname(file))
        const find = (tree, prop, value) => {
            const results = []
            Object.keys(tree).map(key => {
                if (key.match(prop) && tree[key].match(value)) {
                    results.push({
                        parent: tree,
                        property: key,
                        value: tree[key]
                    })
                }
                else if (typeof tree[key] === 'object' && Object.keys(tree[key]).length){
                    results.push(...find(tree[key], prop, value))
                }
            })
            return results
        }
    
        const promises = []
        find(json, /^\$ref$/, new RegExp("^" + json.$id)).map(result => {
            const file = path.join('.' + result.value.substr(json.$id.length), result.value.split("/").pop() + ".json")
            const root = json
            promises.push(loadJsonTree(path.join(dir, file)).then(json => {
                delete result.parent[result.property]
                Object.assign(result.parent, json)
                if (json.definitions) {
                    root.definitions = root.definitions || {}
                    Object.assign(root.definitions, json.definitions)
                    delete result.parent.definitions
                }
                delete result.parent.$id
            }))
        })
    
        return Promise.all(promises).then(_ => json)
    }
        
    const equals = (a, b, ignore=[]) => {
        return !diff(a, b, ignore)
    }
    
    const diff = (a, b, ignore=[]) => {
        if (typeof a !== typeof b) {
            return true
        }
    
        if (['string', 'boolean', 'number'].includes(typeof a)) {
            return !(a === b)
        }
        else if (typeof a === 'object') {
            if (Array.isArray(a) !== Array.isArray(b)) {
                return true
            }
    
            if (Array.isArray(a)) {
                if (a.length !== b.length) {
                    return true
                }
    
                for (var i=0; i<a.length; i++) {
                    if (!equals(a[i], b[i], ignore)) {
                        return true
                    }
                }
            }
            else {
                const diffs = {
                    removed: [],
                    added: [],
                    changed: []
                }
    
                const keysA = Object.keys(a).sort().filter(k => !ignore.includes(k))
                const keysB = Object.keys(b).sort().filter(k => !ignore.includes(k))
    
                if (diff(keysA, keysB, ignore)) {
                    diffs.removed = keysA.filter(x => !keysB.includes(x))
                    diffs.added = keysB.filter(x => !keysA.includes(x))
                }
    
                const keys = keysA.filter(k => keysB.includes(k))
                for (var i=0; i<keys.length; i++) {
                    const subdiffs = diff(a[keys[i]], b[keys[i]], ignore)
                    if (subdiffs) {
                        subdiffs.added && subdiffs.added.forEach(p => diffs.added.push(keys[i] + '.' + p))
                        subdiffs.removed && subdiffs.removed.forEach(p => diffs.removed.push(keys[i] + '.' + p))
                        if (subdiffs.changed && subdiffs.changed.length) {
                            subdiffs.changed && subdiffs.changed.forEach(p => diffs.changed.push(keys[i] + '.' + p))
                        }
                        else {
                            diffs.changed.push(keys[i])
                        }
                    }
                }
                if (diffs.removed.length > 0 || diffs.added.length > 0 || diffs.changed.length > 0) {
                    return diffs
                }
            }
        }
        return false
    }

    const rpc = await loadJson('./dist/firebolt-open-rpc.json')
    const packageJson = await loadJson(process.env.npm_package_json)
                
    const major = parseInt(packageJson.version.split("-").shift().split(".").shift())
    version.apis = version.apis || {}
    version.apis[`${major}`] = rpc

    logSuccess(`Added version ${packageJson.version}`)

    return new Promise( async (resolve, reject) => {
        let legacy = major-1
        while (legacy>major-parsedArgs['legacy-versions']-1 && legacy>0) {
            const v = `${legacy}.x`

            // create a temporary npm package and install the version of Firebolt we want to grab
            await exec(`cd build; mkdir temp${legacy}; cd temp${legacy}; npm init -y ; npm install --saveDev @firebolt-js/sdk@${v}`)

            version.apis[`${legacy}`] = await loadJson(`./build/temp${legacy}/node_modules/@firebolt-js/sdk/dist/firebolt-open-rpc.json`)
            await exec(`cd build; rm -r temp${legacy}`)

            logSuccess(`Added version ${v}`)

            legacy--
        }
        resolve(version)
    })
}

export default run