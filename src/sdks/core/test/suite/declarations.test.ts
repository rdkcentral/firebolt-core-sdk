import Setup from "../../../../../test/Setup"
import { sent } from "../../../../../test/Setup"

import { test, expect  } from "@jest/globals"
import { Lifecycle, Device, Discovery, Entertainment } from "../../build/javascript/src/firebolt";

let listenerId:number

// test('Able to get TypeScript listenerId', () => {
//     return Lifecycle.listen('inactive', () => {}).then((id:number) => {
//         listenerId = id
//         expect(listenerId > 0).toBe(true)
//     })
// })

test('Able to get resolution', () => {
    return Device.screenResolution().then( (res:[number, number]) => {
        expect(res[0]>0).toBe(true)
        expect(res[1]>0).toBe(true)
    })
})

test('purchaseContent', () => {
    return Discovery.purchasedContent({
        expires: '',
        totalCount: 5,
        entries: [
        ]
    }).then(() => {
        let result:Discovery.PurchasedContentResult = sent.find(message => message.method === 'purchasedContent').params.result
        expect(result.totalCount).toBe(5)
        expect(typeof result.totalCount).toBe('number')
    })
})

const result: Discovery.EntityInfoResult = {
    entity: {
        "entityType": "program",
        "identifiers": {
            "entityId": "123"
        },
        "programType": Entertainment.ProgramType.MOVIE,
        "title": "A title"
    },
    "expires": ""
}

test('entityInfo', () => {

    return Discovery.entityInfo(result).then(() => {
        let result:Discovery.EntityInfoResult = sent.find(message => message.method === 'entityInfo').params.result
        expect(result.entity.identifiers.entityId).toBe("123")
    })
})

test('entityInfo pull', () => {
    let resolver
    const p = new Promise((resolve, reject) =>  {
        resolver = resolve
    })

    Discovery.entityInfo( (request: Discovery.EntityInfoParameters) => {
        setTimeout( _ => {
            resolver()
        }, 1000)

        return Promise.resolve(result)
    })

    Setup.emit('Discovery', 'pullEntityInfo', {
        correlationId: '123',
        parameters: {
            entityId: '123'
        }
    })

    let result2:Discovery.EntityInfoResult = sent.find(message => message.method === 'entityInfo').params.result
    expect(result2.entity.identifiers.entityId).toBe("123")

    return p
})