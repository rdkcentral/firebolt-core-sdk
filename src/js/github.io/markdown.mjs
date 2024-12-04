import nopt from 'nopt'
import path from 'path'
import { readJson, readDir, readFiles, readText, writeFiles, writeText, writeJson } from '../../../node_modules/@firebolt-js/openrpc/src/shared/filesystem.mjs'

const knownOpts = {
    'file': [String]
}

const defaultOpts = {
}

const shortHands = {
    'f': '--file'
}
  
// Last 2 arguments are the defaults.
const parsedArgs = Object.assign(defaultOpts, nopt(knownOpts, shortHands, process.argv, 2))

const signOff = () => console.log('\nThis has been a presentation of \x1b[38;5;202mFirebolt\x1b[0m \u{1F525} \u{1F529}\n')

//const packageJson = await readJson(process.env.npm_package_json)
//const version = channel(packageJson.version)
const requirements = await readFiles(await readDir(path.join('.', 'requirements'), { recursive: true }), path.join('.'))

const processFiles = (docs) => {
    Object.keys(docs).forEach(ref => {
        if (ref.endsWith('.md')) {
            let data = docs[ref]

            data = fixBrokenLinks(data, ref, docs)
            data = wrapText(data)
            data = prettyTables(data)
            data = bcp14(data)

            docs[ref] = data
        }
    })

    // do external links after all local links are fixed
    Object.keys(docs).forEach(ref => {
        if (ref.endsWith('.md')) {
            docs[ref] = fixBrokenExternalLinks(docs[ref], ref, docs)
        }
    })
}

function fixBrokenExternalLinks(data, ref, files) {
    return fixBrokenLinks(data, ref, files, true)
}
function fixBrokenLinks(data, ref, files, external=false) {

    const getSlugs = (data) => {
        // find all headers
        const headers = data.match(/#+[ \t]+(([0-9]+\.)+)[ /t]+(.*?)\n/g)

        // turn to slugs
        return headers.map(h => h.replace(/#/g, ''))
                        .map(h => h.replace(/\t/g, ''))
                        .map(h => h.replace(/\./g, ''))
                        .map(h => h.replace(/^ /g, ''))
                        .map(h => h.replace(/\n$/g, ''))
                        .map(h => h.replace(/ /g, '-'))
                        .map(h => h.toLowerCase())
                        .map(h => '#' + h)
    }

    const slugs = getSlugs(data)
    const links = data.match(/\]\([^\)]*?\#[^\)]*?\)/gms)

    links && links.map(l => l.slice(2, -1)).forEach(link => {
        if (!slugs.find(s => s === link)) {
            // fix local links
            if (!external) {
                const best = slugs.find(s => s.match(new RegExp(link.replace(/^\#[0-9]+/, '#[0-9]+')))) || slugs.find(s => s.startsWith(link.split('-')[0] + '-'))
                if (best) {
                    console.log('Fixing broken link: (' + link + ') -> (' + best + ')')
                    data = data.replace('](' + link + ')', '](' + best + ')')    
                }    
            }
            // fix bad slugs in links to other files
            else if (external && link.match(/[^\)]+?\#[^\)]*?/gms)) {
                // external
                const [file, slug] = link.split('#')
                const fileRef = path.join(path.dirname(ref), file)
                const fileSlugs = getSlugs(files[fileRef])
                if (!fileSlugs.find(s => s === '#' + slug)) {
                    const best = fileSlugs.find(s => s.match(new RegExp(('#'+slug).replace(/^\#[0-9]+/, '#[0-9]+')))) || slugs.find(s => s.startsWith(link.split('-')[0] + '-'))
                    if (best) {
                        console.log('Fixing broken external link: (' + link + ') -> (' + file + best + ')')
                        data = data.replace('](' + link + ')', '](' + file + best + ')')    
                    }
                }
            }
        }
    })    

    return data
}

/* TODO: 
    - Newline at top bug
    - Multiple spaces bug
*/
function wrapText(data) {
    const lines = data.split('\n')
    const maximum = 80
    let buffer = ''
    let wrapped = []
    let width = 0
    const block_regex = /^\s*?\>/
    const code_regex = /^\s*?```/
    let code = false

    lines.forEach( (line, index) => {

        if (line.match(code_regex)) {
            code = !code
        }

        // skip lists, tables, headers, and blanks
        if (code || line.match(/^\s*?\-/) || line.match(/^\s*?\|/) || line.match(/^\#+/) || line.match(/^\s*?$/)) {
            buffer && (wrapped.push(buffer))
            buffer = ''
            wrapped.push(line)
            width = 0
        }
        else {
            const quote = line.match(block_regex) ? true : false
            
            if (quote) {
                line = line.replace(block_regex, '').trim()
                
                if (!buffer) {
                    buffer = '> '
                    width = 2
                }
                else if (!line.trim()) {
                    buffer += '\n> \n> '
                    width = 2
                }
            }

            let first = true
            line.split(/\s+/).filter(word => word).forEach((word, i, words) => {
                if (word.match(block_regex)) {
                    throw "Found > in line: " + line
                }
                
                if (word && !word.match(/^\s+$/)) {
                    let len = word.length + 1 // .replace(/\(.*?\)/g, '')
                    if (len > maximum && width === (quote ? 2 : 0)) {
                        buffer += (quote ? '> ' : '') + word + ' '
                        width = len + (quote ? 2 : 0)
                    }
                    else if (width + len > maximum) {
                        buffer += '\n' + (quote ? '> ' : '') + word + ' '
                        width = len + (quote ? 2 : 0)
//                        !first && (first = true)
                    }
                    else {
                        buffer += word + ' '
                        width += len
                    }
                }
                first = false
            })
        }
    })

    buffer && (wrapped.push(buffer))

    return wrapped.join('\n')
}

function prettyTables(data) {
    const lines = data.split('\n')
    const table_regex = /^\s*?\|/
    const column_regex = /(?<!\\)\|/
    const columns = line => line.trim().split(column_regex).slice(1, -1).map(c => (' ' + c.trim() + ' ').length)

    for (var i=0; i<lines.length; i++) {
        if (lines[i].match(table_regex)) {
            let widths = columns(lines[i])
            lines[i+1] = lines[i+1].replace(/\-+/g, '-')
            // find the max width of each column
            for (var j=i; lines[j].match(table_regex); j++) {
                widths = columns(lines[[j]]).map( (w, index) => Math.max(w, widths[index]))
            }
            // pad each cell to match the max width
            for (j=i; lines[j].match(table_regex); j++) {
                lines[j] = lines[j].split(column_regex).map((cell, index) => {
                    // stuff before or after the table row
                    if (index === 0 || index === widths.length + 1) {
                        return cell
                    }
                    else {
                        if (cell.match(/^ \-+ $/)) {
                            return ' ' + '-'.repeat(widths[index-1]-2) + ' '
                        }
                        else if (cell.match(/^\-+$/)) {
                            return '-'.repeat(widths[index-1])
                        }
                        else {
                            return (' ' + cell.trim() + ' ').padEnd(widths[index-1])
                        }
                    }
                }).join('|')
                i++
            }
        }
    }

    return lines.join('\n')
}

function bcp14(data) {
    return data
    .replace(/([^\*])MUST(\s+)NOT([^\*])/gms, '$1**MUST$2NOT**$3')
    .replace(/([^\*])SHOULD(\s+)NOT([^\*])/gms, '$1**SHOULD$2NOT**$3')
    .replace(/([^\*])SHALL(\s+)NOT([^\*])/gms, '$1**SHALL$2NOT**$3')
    .replace(/([^\*])NOT(\s+)RECOMMENDED([^\*])/gms, '$1**NOT$2RECOMMENDED**$3')
    .replace(/([^\*])MUST([^\*])/gms, '$1**MUST**$2')
    .replace(/([^\*])SHOULD([^\*])/gms, '$1**SHOULD**$2')
    .replace(/([^\*])SHALL([^\*])/gms, '$1**SHALL**$2')
    .replace(/([^\*])RECOMMENDED([^\*])/gms, '$1**RECOMMENDED**$2')
    .replace(/([^\*])MAY([^\*])/gms, '$1**MAY**$2')
    .replace(/([^\*])REQUIRED([^\*])/gms, '$1**REQUIRED**$2')
    .replace(/([^\*])OPTIONAL([^\*])/gms, '$1**OPTIONAL**$2')
}

processFiles(requirements)
writeFiles(requirements)

signOff()
