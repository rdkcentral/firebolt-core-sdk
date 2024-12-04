/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
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

import { test, expect } from "@jest/globals";
import { ClosedCaptions } from "../../build/javascript/src/firebolt-manage";

test("ClosedCaptions.enabled()", () => {
  return ClosedCaptions.enabled().then((res: boolean) => {
    expect(res).toBe(true);
  });
});

test("ClosedCaptions.fontFamily()", () => {
  return ClosedCaptions.fontFamily().then((res: string) => {
    expect(res).toEqual("monospace_serif");
  });
});

test("ClosedCaptions.fontSize()", () => {
  return ClosedCaptions.fontSize().then((res: number) => {
    expect(res).toBe(1);
  });
});

test("ClosedCaptions.fontColor()", () => {
  return ClosedCaptions.fontColor().then((res: string) => {
    expect(res).toEqual("#ffffff");
  });
});

test("ClosedCaptions.fontEdge()", () => {
  return ClosedCaptions.fontEdge().then((res: string) => {
    expect(res).toEqual("none");
  });
});

test("ClosedCaptions.fontEdgeColor()", () => {
  return ClosedCaptions.fontEdgeColor().then((res: string) => {
    expect(res).toEqual("#000000");
  });
});

test("ClosedCaptions.fontOpacity()", () => {
  return ClosedCaptions.fontOpacity().then((res: number) => {
    expect(res).toBe(99);
  });
});

test("ClosedCaptions.backgroundColor()", () => {
  return ClosedCaptions.backgroundColor().then((res: string) => {
    expect(res).toEqual("#000000");
  });
});

test("ClosedCaptions.backgroundOpacity()", () => {
  return ClosedCaptions.backgroundOpacity().then((res: number) => {
    expect(res).toBe(99);
  });
});

test("ClosedCaptions.textAlign()", () => {
  return ClosedCaptions.textAlign().then((res: string) => {
    expect(res).toEqual("center");
  });
});

test("ClosedCaptions.textAlignVertical()", () => {
  return ClosedCaptions.textAlignVertical().then((res: string) => {
    expect(res).toEqual("middle");
  });
});

test("ClosedCaptions.listen()", () => {
  return ClosedCaptions.listen("fontColorChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("ClosedCaptions.once()", () => {
  return ClosedCaptions.once("fontColorChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("clear", () => {
  const result = ClosedCaptions.clear(-1000);
  expect(result).toBeFalsy();
});

test("ClosedCaptions.setFontColor() with null", async () => {
  const oldValue = await ClosedCaptions.fontColor()
  return ClosedCaptions.fontColor(null).then(async (res: null) => {
    expect(res).toBe(null);
    const newValue = await ClosedCaptions.fontColor()
    expect(newValue).toBe(null)
  });
});

test("ClosedCaptions.setFontColor() with ffffff", () => {
  return ClosedCaptions.fontColor("#ffffff").then((res: null) => {
    expect(res).toBe(null);
  });
});
