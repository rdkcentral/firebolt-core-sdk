/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import { test, expect } from "@jest/globals";
import { Discovery, Entertainment, Entity } from "../../build/javascript/src/firebolt";

test("watched(entityId)", () => {
  return Discovery.watched("abc").then((success: boolean) => {
    expect(success).toBe(true);
  });
});

test("policy()", () => {
  return Discovery.policy().then((res: Discovery.DiscoveryPolicy) => {
    expect(res.enableRecommendations).toBeTruthy();
    expect(res.rememberWatchedPrograms).toBeTruthy();
    expect(res.shareWatchHistory).toBeTruthy();
  });
});

test("policy(subscriber)", () => {
  return Discovery.policy((policy: Discovery.DiscoveryPolicy) => { }).then(
    (res: number) => {
      expect(res).toBe(1);
    }
  );
});

test("entityInfo(EntityInfoResult)", () => {
  const dummyData: Discovery.EntityInfoResult = {
    expires: new Date().toISOString(),
    entity: {
      identifiers: {
        assetId: "test123",
      },
      title: "Test",
      entityType: "program",
      programType: Entertainment.ProgramType.MOVIE,
    },
  };
  return Discovery.entityInfo(dummyData).then((res: boolean) => {
    expect(res).toBeTruthy();
  });
});

test("watchNext(title?: LocalizedString, identifiers: ContentIdentifiers, expires?: string, images?: object)", () => {
  return Discovery.watchNext("abc", { entityId: "partner.com/entity/123" }).then((success: boolean) => {
    expect(success).toBe(true);
  });
});

test("entitlements(entitlements: Entitlement[])", () => {
  const dummyData: Array<Entertainment.Entitlement> = [
    {
      entitlementId: "test123",
      startTime: `${new Date().getTime()}`,
      endTime: `${new Date().getTime() + 1}`,
    },
  ];
  return Discovery.entitlements(dummyData).then((res: boolean) => {
    expect(res).toBeTruthy();
  });
});

test("launch(appId)", () => {
  return Discovery.launch("test123").then((res: boolean) => {
    expect(res).toBeTruthy();
  });
});

test("signIn(appId)", () => {
  const dummyData: Array<Entertainment.Entitlement> = [
    {
      entitlementId: "test123",
      startTime: `${new Date().getTime()}`,
      endTime: `${new Date().getTime() + 1}`,
    },
  ];
  return Discovery.signIn(dummyData).then((res: boolean) => {
    expect(res).toBeTruthy();
  });
});

test("signOut()", () => {
  return Discovery.signOut().then((res: boolean) => {
    expect(res).toBeTruthy();
  });
});

test("purchasedContent()", () => {
  const dummyData: Discovery.PurchasedContentResult = {
    expires: `${new Date().toISOString}`,
    totalCount: 2,
    entries: [
      {
        identifiers: {
          assetId: "test123",
        },
        title: "TEST",
        entityType: "program",
        programType: Entertainment.ProgramType.MOVIE,
      },
    ],
  };
  return Discovery.purchasedContent(dummyData).then((res: boolean) => {
    expect(res).toBeTruthy();
  });
});

test("listen() navigateTo event.", () => {
  return Discovery.listen("navigateTo", () => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() navigateTo event.", () => {
  return Discovery.once("navigateTo", () => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("listen() policyChanged event.", () => {
  return Discovery.listen("policyChanged", () => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("once() policyChanged event.", () => {
  return Discovery.once("policyChanged", () => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("clear()", () => {
  const result: boolean = Discovery.clear(-1000);
  expect(result).toBeFalsy();
});

test("details() provider", () => {

  class myUserInterestProvider implements Discovery.Interest {
    userInterest(type: Discovery.InterestType, reason: Discovery.InterestReason): Promise<Entity.EntityDetails> {
      return Promise.resolve(null)
    }
  }
})
