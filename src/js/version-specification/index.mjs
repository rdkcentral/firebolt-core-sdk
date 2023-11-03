import apis from './apis.mjs'
import capabilities from './capabilities.mjs'

import nopt from 'nopt'
import path from 'path'
import { readFile, writeFile } from 'fs/promises'

const loadJson = file => readFile(file).then(data => JSON.parse(data.toString()))

const knownOpts = {
    'capabilities': [Boolean],
    'legacy-versions': [Number],
    'source': [String],
    'report': [Boolean]
}

const defaultOpts = {
    'capabilities': true,
    'legacy-versions': 2,
    'source': './src/json/firebolt-specification.json',
    'report': false
}

const shortHands = {
    'l': '--legacy-versions',
    'c': '--capabilities',
    't': '--target',
    's': '--source',
    'r': '--report'
}
  
// Last 2 arguments are the defaults.
const parsedArgs = Object.assign(defaultOpts, nopt(knownOpts, shortHands, process.argv, 2))

const signOff = () => console.log('\nThis has been a presentation of \x1b[38;5;202mFirebolt\x1b[0m \u{1F525} \u{1F529}\n')

let version = await loadJson(parsedArgs.source)

version = await apis(version, parsedArgs)
version = await capabilities(version, parsedArgs)

if (!parsedArgs.report) {
    writeFile(path.join('.', 'dist', 'firebolt-specification.json'), JSON.stringify(version, null, '\t'))
}

signOff()
