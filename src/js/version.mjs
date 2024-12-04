#!/usr/bin/env node

import { readFile, writeFile } from 'fs/promises'
import path from 'path'
import { exec, execSync } from 'child_process'

process.argv.shift()
process.argv.shift()

const task = process.argv.shift()

let inWorkspace = false
let packageJson = await readFile(path.join('.', 'package.json'))
    .then(bytes => bytes.toString())
    .then(JSON.parse)

if (!packageJson.workspaces) {
    inWorkspace = true
    packageJson = await readFile(path.join('..', '..', '..', 'package.json'))
        .then(bytes => bytes.toString())
        .then(JSON.parse)
}

const packageMain = packageJson

if (task === 'sync') {

    console.log()

    await Promise.all(packageMain.workspaces.map(async workspace => {
        console.log(`Updating ${workspace}/package.json to version ${packageMain.version}.`)
        const packageWorkspace = await readFile(path.join('.', workspace, 'package.json'))
            .then(bytes => bytes.toString())
            .then(JSON.parse)
        packageWorkspace.version = packageMain.version
        return writeFile(path.join('.', workspace, 'package.json'), JSON.stringify(packageWorkspace, null, '\t'))
    }))

    console.log()
}
else if (task === 'channel') {
    const branch = process.argv.shift()
    const releaserc = await readFile(path.join('.', '.releaserc'))
        .then(bytes => bytes.toString())
        .then(JSON.parse)

    // default to 'test' channel if branch is unknown
    const config = releaserc.branches.find(b => b.name === branch) || { channel: branch.replace('/', '-') }
    const channel = config.channel || (!config.prerelease ? 'latest' : config.name)

    // return the configured channel name for the branch, otherwise return the branch name, unless it's the main branch, then return 'latest'
    console.log(channel)
}
else if (task === 'validate') {
    // Check all workspaces for:
    //  - package.json.version is the same
    //  - pacakge.json.main exists
    //  - package.json.types exists
    await Promise.all(packageMain.workspaces.map(async workspace => {
        console.log(`Validating ${workspace} distribution matches version.`)
        const packagePath = inWorkspace ? path.join('.') : path.join('.', workspace)
        const packageWorkspace = await readFile(path.join(packagePath, 'package.json'))
            .then(bytes => bytes.toString())
            .then(JSON.parse)
        if (packageWorkspace.version !== packageMain.version) {
            console.error(`${packageWorkspace.name} version does not match root.`)
            process.exit(-1)
        }

        const main = await readFile(path.join(packagePath, packageWorkspace.main))
        const types = await readFile(path.join(packagePath, packageWorkspace.types))

        if (!(main.byteLength > 0 && types.byteLength > 0)) {
            console.error(`${packageWorkspace.name} has empty artifacts.`)
            process.exit(-1)
        }
    }))


} else if (task === 'latest-prerelease') {
    console.log('Finding the latest prerelease')
    const prerelease = process.argv.shift()
    console.log('prerelease : ' + prerelease)
    exec("npm show @firebolt-js/sdk versions --json", (error, result, errlog) => {
        if (error) {
            console.error(`error: ${error.message}`);
            return;
        }
        let versions = JSON.parse(result).sort().reverse()
        let matches = versions.filter(v => {
            if (v.indexOf('-') !== -1) {
                let prerel = v.substring(v.indexOf('-') + 1)
                return prerel.startsWith(prerelease + '.')
            }
            return false
        })
        if (matches.length > 0) {
            console.log('Setting package version to ' + matches[0])
            console.log(execSync("npm version " + matches[0] + " --git-tag-version false --allow-same-version true"))
            console.log(execSync("npm version " + matches[0] + " --workspaces --git-tag-version false --allow-same-version true"))
            return matches[0]
        }
        return null
    });
} else if (task === 'branch-to-prerelease') {
    const branch = process.argv.shift()
    console.log(branch.replace('/', '-'))
}
