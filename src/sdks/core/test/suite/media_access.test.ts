import Setup from "../../../../../test/Setup"

import { test, expect  } from "@jest/globals"
import { MediaAccess } from "../../build/javascript/src/firebolt";

test('Live-list', () => {
    return new Promise( (resolve, reject) => {
        const process = MediaAccess.volumes({}, (volume: MediaAccess.Volume) => {
                // add
                expect(typeof volume.type).toBe('string')
            },
            (volume: MediaAccess.Volume) => {
                // remove
            }
        )

        expect(typeof process.stop).toBe('function')
        setTimeout(_ => {
            process.stop()
            resolve({})
        }, 10)
    })
})

test('First-match', () => {
    return MediaAccess.volumes({}, 10).then( (volume:MediaAccess.Volume) => {
        expect(volume.type).toBe('usb')
    })
})

test('Known values', () => {
    return MediaAccess.volumes({}).then( (volumes:MediaAccess.Volume[]) => {
        expect(volumes.length).toBe(2)
    })
})

test('Only one sesssion at a time', () => {
    return new Promise( (resolve, reject) => {
        let errorThrown = false
        try {
            MediaAccess.volumes({}, (v: MediaAccess.Volume)=>{}, (v: MediaAccess.Volume)=>{})
            MediaAccess.volumes({}, (v: MediaAccess.Volume)=>{}, (v: MediaAccess.Volume)=>{})
        }
        catch (error) {
            console.dir(error)
            errorThrown = true
        }
        expect(errorThrown).toBeTruthy()
        resolve({})
    })
})
