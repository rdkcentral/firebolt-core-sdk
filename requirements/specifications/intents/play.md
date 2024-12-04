# Play Intent

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor     | Organization |
| --------------- | ------------ |
| Jeremy LaCivita | Comcast      |
| Liz Sheffield   | Comcast      |
| Seth Kelly      | Comcast      |
| Simon Grist     | Sky          |

## 1. Overview
There are many use cases where a Firebolt device will need to inform an app of 
a user's intention to play something. This could originate from a voice remote, 
an editorial tile, a developer tool, or any number of places. Having a standard 
message to play something allows an app to integrate with this message once, 
while allowing the platform to change when and where the intent comes from 
w/out further work from the app. 

Apps will need to be able to play specific entities from a back-office 
meta-data integration, entities from a federated meta-data integration, or 
non-specific entities based on a query. 

The existing Firebolt `playback` intent does not meet these requirements. This 
document outlines a more flexible `play-entity` and `play-query` intent to 
replace it. 

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Play Entity Intent](#3-play-entity-intent)
  - [3.1. Play Entity Options](#31-play-entity-options)
    - [3.1.1. Play First Option](#311-play-first-option)
- [4. Play Query Intent](#4-play-query-intent)
  - [4.1. Play Options for Query](#41-play-options-for-query)
- [5. Core APIs](#5-core-apis)

## 3. Play Entity Intent
The Firebolt `navigateTo` notification **MUST** support a `play-entity` intent, 
which tells an app to initiate playback of specific entity. 

The `play-entity` intent **MUST** have an `action` property, whose value is 
`"play-entity"`. 

The `play-entity` intent **MUST** have a `data` object property, which is an 
object conforming to the following: 

> The `data` object **MUST** have an `entity` object property. 
> 
> The `entity` object, **MUST** be an [Entity](../entities/). 
> 
> The `data` object **MAY** have an `options` object property that conforms to 
> [Play Entity Options](#31-play-entity-options). 

The `play-entity` intent **MUST** have a `context` object property that 
conforms to the [Intent Context](./index.md#4-intent-context). 

An example play-entity intent: 

```json 
{
    "action": "play-entity",
    "data": {
        "entity": {
            "entityType": "program",
            "programType": "movie",
            "entityId": "movie/xyz"
        }
    },
    "context": {
        "source": "voice"
    }
 }
``` 

Which would instruct an app to play the movie entity with id `movie/xyz`. 

### 3.1. Play Entity Options

#### 3.1.1. Play First Option
For `play-entity` intents with an `entity` whose `entityType` is `"playlist"`, 
e.g.: 

 ```json
 {
    "action": "play-entity",
    "data": {
        "entity": {
            "entityType": "playlist",
            "entityId": "playlist/xyz"
        }
    },
    "context": {
        "source": "voice"
    }
 }
``` 

The `options` property of the intent **MAY** contain a `playFirstId` string 
property, to identify an entity to play *before* starting the playlist, e.g.: 

 ```json
 {
    "action": "play-entity",
    "data": {
        "entity": {
            "entityType": "playlist",
            "entityId": "playlist/xyz"
        },
        "options": {
            "playFirstId": "song/xyz"
        }
    },
    "context": {
        "source": "voice"
    }
 }
``` 

If `playFirstId` is provided, the the targeted app **MUST** attempt to play the 
entity denoted by `playFirstId` first, regardless of whether it is part of the 
identified playlist or not. 
 
If the `playFirstId` was successfully played, then the app **SHOULD** remove 
the `playFirstId` entity from any later position in the playlist, if 
appropriate. 

The `options` property of the intent **MAY** contain a `playFirstTrack` integer 
property, to identify an entity from the playlist to play *before* the rest of 
the playlist, e.g.: 

 ```json
 {
    "action": "play-entity",
    "data": {
        "entity": {
            "entityType": "playlist",
            "entityId": "playlist/xyz"
        },
        "options": {
            "playFirstTrack": 3
        }
    },
    "context": {
        "source": "voice"
    }
 }
``` 

If `playFirstTrack` is provided and the playlist has at least that many items, 
then the item denoted by `playFirstTrack` **MUST** be moved from it's original 
position to the front of the playlist for playback. 

The options object **MUST NOT** have both a `playFirstId` and a 
`playFirstTrack` property. 

## 4. Play Query Intent
The Firebolt `navigateTo` notification **MUST** support a `play-query` intent, 
which tells an app to find content that matches a query and play that content. 

The `play-query` intent **MUST** have an `action` property, whose value is 
`"play-query"`. 

The `play-query` intent **MUST** have `data` property, which is an object 
conforming to the following: 

> The `data` object **MUST** have a `query` string property. 
> 
> The `data` object **MAY** have an `options` object property that conforms to 
> [Play Options](#41-play-options-for-query). 

The `play-query` intent **MUST** have a `context` object property that conforms 
to the [Intent Context](./index.md#4-intent-context). 

An example play intent: 

```json 
{
    "action": "play-query",
    "data": {
        "query": "Ed Sheeran"
    },
    "context": {
        "source": "voice"
    }
}
``` 

Which would instruct an app to search for content matching the query "Ed 
Sheeran" and then play the results. 

### 4.1. Play Options for Query
For `play-query` intents with a `query`, e.g.: 

 ```json
 {
    "action": "play-query",
    "data": {
        "query": "Ed Sheeran"
    },
    "context": {
        "source": "voice"
    }
 }
``` 

The `options` property of the intent **MAY** contain a `programTypes` 
array-of-strings property, to filter which program entity typess, e.g. `[ 
"movie", "episode" ]` should be included, e.g.: 

 ```json
 {
    "action": "play-query",
    "data": {
        "query": "Ed Sheeran",
        "options": {
            "programTypes": [
                "movie"
            ]
        }
    },
    "context": {
        "source": "voice"
    }
 }
``` 

The `options` property of the intent **MAY** contain a `musicTypes` 
array-of-strings property, to filter which music entity typess, e.g. `[ "song", 
"album" ]` should be included, e.g.: 

 ```json
 {
    "action": "play-query",
    "data": {
        "query": "Ed Sheeran",
        "options": {
            "programTypes": [
                "movie"
            ],
            "musicTypes": [
                "song"
            ]
        }
    },
    "context": {
        "source": "voice"
    }
 }
``` 
 
## 5. Core APIs
The Firebolt Core SDK will support listening to `play-query` and `play-entity` 
intents via the `Discovery.navigateTo` notification. 

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.listen('navigateTo', (intent) => {
    if (intent.action === 'play-query') 
        // do stuff with play intent!
    }
})
``` 