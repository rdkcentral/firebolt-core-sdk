import nopt from 'nopt'
import path from 'path'
import { readJson, readDir, readFiles, readText, writeFiles, writeText, writeJson } from '../../../node_modules/@firebolt-js/openrpc/src/shared/filesystem.mjs'

const knownOpts = {
    'output': [String]
}

const defaultOpts = {
}

const shortHands = {
    'o': '--output'
}
  
// Last 2 arguments are the defaults.
const parsedArgs = Object.assign(defaultOpts, nopt(knownOpts, shortHands, process.argv, 2))

const signOff = () => console.log('\nThis has been a presentation of \x1b[38;5;202mFirebolt\x1b[0m \u{1F525} \u{1F529}\n')

const packageJson = await readJson(process.env.npm_package_json)
const version = parsedArgs.argv.remain && parsedArgs.argv.remain[0] || channel(packageJson.version)
const requirements = await readFiles(await readDir(path.join('.', 'requirements'), { recursive: true }), path.join('.', 'requirements'))

const processFiles = (docs, base, dir, subdir, category, setType) => {
    Object.keys(docs).forEach(ref => {
        let data = docs[ref]
        const source = ref
        delete docs[ref]
        let type = ''

        if (setType && category === 'requirements') {
            const parts = ref.split(path.sep)
            if (parts.length >= 3) {
                type = ref.split(path.sep)[1].replace(/.$/,'');
            }
        }

        if (ref.endsWith('.md')) {
            const filename = ref.split(path.sep).pop()
            // if this is a generated file, leave it alone
            if ( !base.startsWith('src')) { //filename !== 'index.md') {
                console.log(`UPDATING LINKS: ${ref}`)
                const dirname = filename.split('.').shift()
                const parts = filename === 'index' ? ['..'] : ['index.md']
                // if the dirname is the same as parent dir, don't insert it
                if (dirname !== ref.split(path.sep).slice(-2, -1)[0] && dirname !== 'index') {
                    parts.unshift(dirname)
                    data = data.replace(/\]\(\.\.\//g, '](../../')
                    data = data.replace(/\]\(\.\//g, '](../')
                }
                data = data.replace(/\]\((.*?)\.md([\)#])/g, ']($1$2')
                data = data.replace(/\]\((.*?)\/(.*?)\/\2([\)#])/g, ']($1/$2$3')
                ref = ref.split(path.sep).slice(0, -1).concat(parts).join(path.sep)
            }
            else {
                console.log(`NOT UPDATING LINKS: ${ref}`)
            }

            docs[path.join(parsedArgs.output, dir, version, subdir, ref)] = frontmatter(data, version, subdir, category, type)
        }
        else {
            docs[path.join(parsedArgs.output, dir, version, subdir, ref)] = data
        }
    
//        console.log(`Will copy ${path.join(base, source)} to ${path.join(parsedArgs.output, dir, version, subdir, ref)}`)
    
        if (version === 'latest') {
            if (ref.endsWith('.md')) {
                docs[path.join(parsedArgs.output, dir, packageJson.version, subdir, ref)] = frontmatter(data, packageJson.version, subdir, category, type)
            }
            else {
                docs[path.join(parsedArgs.output, dir, packageJson.version, subdir, ref)] = data
            }
            console.log(`Will copy ${path.join(base, source)} to ${path.join(parsedArgs.output, dir, packageJson.version, subdir, ref)}`)
        }    
    })
}

processFiles(requirements, path.join('.', 'requirements'), 'requirements', '', 'requirements', true)
writeFiles(requirements)

packageJson.workspaces.forEach(async workspace => {
    const docs = await readFiles(await readDir(path.join(workspace, 'build', 'docs', 'markdown'), { recursive: true }), path.join(workspace, 'build', 'docs', 'markdown'))

    docs['index.md'] = (await readText(path.join(workspace, 'README.md')))
    docs['changelog.md'] = '---\ntitle: Change Log\n---\n' + (await readText(path.join(workspace, 'CHANGELOG.md')))

    // point to new output location
    processFiles(docs, path.join(workspace, 'build', 'docs', 'markdown'), 'apis', workspace.split(path.sep).pop())

    writeFiles(docs)
})

const specification = await readJson(path.join('dist', 'firebolt-specification.json'))
const openrpc = await readJson(path.join('dist', 'firebolt-open-rpc.json'))
const corerpc = await readJson(path.join('dist', 'firebolt-core-open-rpc.json'))

const capabilities = () => {
    const getOrCreateCapMethodList = (capabilities, c) => capabilities[c] = capabilities[c] || { uses: [], manages: [], provides: [] }
    const capabilities = {}
    openrpc.methods.forEach(method => {
        const caps = method.tags.find(t => t.name === "capabilities");
        (caps['x-uses'] || []).forEach(c => {
          getOrCreateCapMethodList(capabilities, c)
          capabilities[c].uses.push(method.name)
        });
        (caps['x-manages'] || []).forEach(c => {
          getOrCreateCapMethodList(capabilities, c)
          capabilities[c].manages.push(method.name)
        });
        if (caps['x-provides']) {
          const c = caps['x-provides']
          getOrCreateCapMethodList(capabilities, c)
          capabilities[caps['x-provides']].provides.push(method.name)
        }
    })

    Object.entries(specification.capabilities).forEach( ([c, v]) => {
        capabilities[c].level = v.level
    })

    let manifest = '\n## Capailities\n| Capability | Level | Uses | Provides | Manages |\n|-|-|-|-|-|\n'
    
    const linkify = (method) => `[${method}](./${corerpc.methods.find(m => m.name === method) ? 'core' : 'manage'}/${method.split('.').shift()}/#${method.match(/\.on[A-Z]/) ? method.split('.').pop().charAt(2).toLowerCase() + method.split('.').pop().substring(3).toLowerCase() : method.split('.').pop().toLowerCase()})`
    Object.keys(capabilities).sort().forEach(c => {
        const use = capabilities[c].uses.length ? `<details><summary>${capabilities[c].uses.length}</summary>${capabilities[c].uses.map(linkify).join('<br/>')}</details>` : ''
        const man = capabilities[c].manages.length ? `<details><summary>${capabilities[c].manages.length}</summary>${capabilities[c].manages.map(linkify).join('<br/>')}</details>` : ''
        const pro = capabilities[c].provides.length ? `<details><summary>${capabilities[c].provides.length}</summary>${capabilities[c].provides.map(linkify).join('<br/>')}</details>` : ''

        manifest += `| \`${c}\` | **${capabilities[c].level.toUpperCase()}** | ${use} | ${pro} | ${man} |\n`
    })


    manifest += '\n## Methods\nCapability prefix `xrn:firebolt:capability` let off for readability.\n| Method | Level | Uses | Provides | Manages |\n|-|-|-|-|-|\n'

    openrpc.methods.forEach(method => {
        let uses = Object.entries(capabilities).filter( ([c, v]) => v.uses.includes(method.name)).map(([c, v]) => c)
        let mans = Object.entries(capabilities).filter( ([c, v]) => v.manages.includes(method.name)).map(([c, v]) => c)
        let pros = Object.entries(capabilities).filter( ([c, v]) => v.provides.includes(method.name)).map(([c, v]) => c)
        let level = Array.from(new Set(uses.concat(mans).concat(pros).map(c => capabilities[c].level))).join(', ')

        uses = uses.map(c => c.split(':').slice(3, 5).join(':')).map(c => `\`${c}\``).join(', ')
        pros = pros.map(c => c.split(':').slice(3, 5).join(':')).map(c => `\`${c}\``).join(', ')
        mans = mans.map(c => c.split(':').slice(3, 5).join(':')).map(c => `\`${c}\``).join(', ')
        level = level.includes('must') ? 'must' : level.includes('should') ? 'should' : 'could'

        manifest += `| ${linkify(method.name)} | **${level.toUpperCase()}** | ${uses} | ${pros} | ${mans} |\n`

    })

    return manifest
}

// This is the main README, and goes in a few places...
console.log(`Will copy ${path.join('.', 'README.md')} to ${path.join(parsedArgs.output, 'apis', 'index.md')}`)
const index = frontmatter(await readText(path.join('README.md')), null, null) + capabilities()
writeText(path.join(parsedArgs.output, 'apis', version, 'index.md'), index)
if (version === 'latest') {
    console.log(`Will copy ${path.join('.', 'README.md')} to ${path.join(parsedArgs.output, packageJson.version, 'index.md')}`)
    writeText(path.join(parsedArgs.output, 'apis', 'index.md'), index)
    writeText(path.join(parsedArgs.output, 'apis', packageJson.version, 'index.md'), index)
}

// this is the firebolt spec JSON
writeJson(path.join(parsedArgs.output, 'requirements', version, 'specifications', 'firebolt-specification.json'), specification)
if (version === 'latest') {
    writeJson(path.join(parsedArgs.output, 'requirements', packageJson.version, 'specifications', 'firebolt-specification.json'), specification)
}

// this is the firebolt OpenRPC spec JSON
writeJson(path.join(parsedArgs.output, 'requirements', version, 'specifications', 'firebolt-open-rpc.json'), openrpc)
if (version === 'latest') {
    writeJson(path.join(parsedArgs.output, 'requirements', packageJson.version, 'specifications', 'firebolt-open-rpc.json'), openrpc)
}

function channel(version) {
    const parts = version.split("-")

    if (parts.length > 1) {
        parts.shift()
        const chnl = parts.join("-").split(".").shift()
        return chnl
    }
    else {
        return 'latest'
    }
}

function frontmatter(data, version, sdk, category, type) {
    let matter = ''
    if (data.startsWith('---')) {
        matter = data = data.substring(4)
        matter = data.substring(0, data.indexOf('---'))
        data = data.substring(data.indexOf('---')+4)
    }

    matter = '---\n' + matter + '\n'

    if (version && matter.indexOf('Version:') === -1) {
        matter += `version: ${version}\n`
    }

    if (matter.indexOf('layout:') === -1) {
        matter += `layout: default\n`
    }

    if (matter.toLowerCase().indexOf('title:') === -1) {
        matter += `title: ${data.match(/\# (.*?)\n/)[1]}\n`
    }

    if (sdk && matter.indexOf('sdk:') === -1) {
        matter += `sdk: ${sdk}\n`
    }

    if (category && matter.indexOf('category:') === -1) {
        matter += `category: ${category}\n`
    }

    if (type && matter.indexOf('type:') === -1) {
        matter += `type: ${type}\n`
    }

    matter += '---\n'

    return matter + data.replace(/\<details(.*?)\>/g, '<details markdown="1" $1>')
}

signOff()
