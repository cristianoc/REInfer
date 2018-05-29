open Belt;

type p = int;
type o =
  | NotOpt
  | Opt;
type t =
  | Same
  | Number
  | String
  | Boolean
  | Object(Js.Dict.t(styp))
  | Array(styp)
and styp = {
  t,
  o,
  p,
};

let stypIsNull = (styp: styp) =>
  styp.t == Same && styp.o == Opt && styp.p == 0;

let stypSame = {t: Same, o: NotOpt, p: 0};
let stypIsSame = styp =>
  switch (styp) {
  | {t: Same, o: NotOpt, p: 0} => true
  | _ => false
  };

module PrettyPrint = {
  let simpleNull = true;
  let simpleEmptyArray = true;
  let skip100Percent = false;
  let skip0OutOf0 = true;
  let percent = false;

  let pToString = (p, ~ctx) => {
    let p0 =
      switch (ctx) {
      | None => p
      | Some(p0) => p0
      };
    if (percent && p0 != 0) {
      let perc = float_of_int(p) /. float_of_int(p0);
      string_of_float(perc);
    } else {
      string_of_int(p) ++ "/" ++ string_of_int(p0);
    };
  };

  let pToJson = (p, ~ctx) => p |. pToString(~ctx) |. Js.Json.string;

  let is100Percent = (p, ~ctx) => ctx == None || ctx == Some(p);

  let is0OutOf0 = (p, ~ctx) => p == 0 && (ctx == None || ctx == Some(0));

  let addStats = (jsonT, ~o, ~p, ~skipP, ~ctx) => {
    let jsonStats = {
      let pString = p |. pToString(~ctx);
      let oString = o == Opt ? "?" : "";
      oString ++ pString |. Js.Json.string;
    };
    switch (Js.Json.classify(jsonT)) {
    | JSONObject(dict) =>
      dict |. Js.Dict.set("_stats", jsonStats);
      dict |. Js.Json.object_;
    | JSONArray(arr) =>
      let jsonNew =
        [|("_stats", jsonStats)|] |. Js.Dict.fromArray |. Js.Json.object_;
      arr |. Js.Array.concat([|jsonNew|]) |. Js.Json.array;
    | _ =>
      if (skipP && o == NotOpt) {
        jsonT;
      } else {
        let dict = Js.Dict.empty();
        dict |. Js.Dict.set("typ", jsonT);
        dict |. Js.Dict.set("_stats", jsonStats);
        dict |. Js.Json.object_;
      }
    };
  };
  let rec toJson = (styp: styp, ~ctx: option(p)) : Js.Json.t =>
    if (simpleNull && styp |. stypIsNull) {
      Js.Json.null;
    } else {
      let skipP =
        skip100Percent
        && styp.p
        |. is100Percent(~ctx)
        || skip0OutOf0
        && styp.p
        |. is0OutOf0(~ctx);
      let jsonT = styp.t |. toJsonT(~ctx=Some(styp.p));
      switch (skipP, styp.o) {
      | (true, NotOpt) => jsonT
      | _ => jsonT |. addStats(~o=styp.o, ~p=styp.p, ~skipP, ~ctx)
      };
    }
  and toJsonT = (t: t, ~ctx: option(p)) : Js.Json.t =>
    switch (t) {
    | Same => Js.Json.string("same")
    | Number => Js.Json.string("number")
    | String => Js.Json.string("string")
    | Boolean => Js.Json.string("boolean")
    | Object(d) =>
      let doEntry = ((lbl, styp)) => (lbl, styp |. toJson(~ctx));
      Js.Dict.entries(d)
      |. Array.map(doEntry)
      |. Js.Dict.fromArray
      |. Js.Json.object_;
    | Array(styp) when simpleEmptyArray && stypIsSame(styp) =>
      [||] |. Js.Json.array
    | Array(styp) => [|styp |. toJson(~ctx)|] |. Js.Json.array
    };
  let styp = styp => styp |. toJson(~ctx=None) |. Js.Json.stringify;
};

let rec fromJson = (json: Js.Json.t) : styp =>
  switch (Js.Json.classify(json)) {
  | JSONFalse
  | JSONTrue => {t: Boolean, o: NotOpt, p: 1}
  | JSONNull => {t: Same, o: Opt, p: 0}
  | JSONString(_) => {t: String, o: NotOpt, p: 1}
  | JSONNumber(_) => {t: Number, o: NotOpt, p: 1}
  | JSONObject(dict) =>
    let do_entry = ((lbl, v)) => {
      let styp = fromJson(v);
      (lbl, styp);
    };
    {
      t:
        Object(
          Js.Dict.entries(dict) |. Array.map(do_entry) |. Js.Dict.fromArray,
        ),
      o: NotOpt,
      p: 1,
    };
  | JSONArray(a) =>
    a
    |. Array.reduce({t: Same, o: NotOpt, p: 0}, (styp, json) =>
         styp ++ fromJson(json)
       )
    |. (styp => {t: Array(styp), o: NotOpt, p: 1})
  }
and (++) = (styp1, styp2) => {
  let t = plusT(styp1.t, styp2.t);
  let o = styp1.o == Opt ? styp1.o : styp2.o;
  let p = styp1.p + styp2.p;
  {t, o, p};
}
and plusT = (t1, t2) =>
  switch (t1, t2) {
  | (Same, t)
  | (t, Same) => t
  | (Number, Number) => Number
  | (String, String) => String
  | (Boolean, Boolean) => Boolean
  | (Object(d1), Object(d2)) =>
    let d = Js.Dict.empty();
    let doItem = ((lbl, styp)) =>
      switch (d |. Js.Dict.get(lbl)) {
      | None => d |. Js.Dict.set(lbl, styp)
      | Some(styp1) => d |. Js.Dict.set(lbl, styp ++ styp1)
      };
    d1 |. Js.Dict.entries |. Array.forEach(doItem);
    d2 |. Js.Dict.entries |. Array.forEach(doItem);
    Object(d |. Js.Dict.entries |. Js.Dict.fromArray);
  | (Array(styp1), Array(styp2)) =>
    let styp = styp1 ++ styp2;
    styp |. Array;
  | (Number, _) =>
    Js.log("++ TODO: Number Left");
    assert(false);
  | (_, Number) =>
    Js.log("++ TODO: Number Right");
    assert(false);
  | (String, _) =>
    Js.log("++ TODO: String Left");
    assert(false);
  | (_, String) =>
    Js.log("++ TODO: String Right");
    assert(false);
  | (Boolean, _) =>
    Js.log("++ TODO: Boolean Left");
    assert(false);
  | (_, Boolean) =>
    Js.log("++ TODO: Boolean Right");
    assert(false);
  | (Object(_), _) =>
    Js.log("++ TODO: Object Left");
    assert(false);
  | (_, Object(_)) =>
    Js.log("++ TODO: Object Right");
    assert(false);
  };

let rec abduce = (styp1: styp, styp2: styp) : styp =>
  switch (styp1, styp2) {
  | ({t: t1, o: o1, p: p1}, {t: t2, o: o2, p: p2}) =>
    let t = abduceT(t1, t2);
    let o = abduceO(o1, o2);
    let p = p2 - p1;
    {t, o, p};
  }
and abduceT = (t1: t, t2: t) : t =>
  switch (t1, t2) {
  | (Same, _) => t2
  | (Number, Number) => Same
  | (String, String) => Same
  | (Boolean, Boolean) => Same
  | (Object(d1), Object(d2)) =>
    let d = Js.Dict.empty();
    let doItem2 = ((lbl, styp2)) =>
      switch (d1 |. Js.Dict.get(lbl)) {
      | None =>
        if (! stypIsSame(styp2)) {
          d |. Js.Dict.set(lbl, styp2);
        }
      | Some(styp1) =>
        let stypA = abduce(styp1, styp2);
        if (! stypIsSame(stypA)) {
          d |. Js.Dict.set(lbl, stypA);
        };
      };
    let doItem1 = ((lbl, styp1)) =>
      switch (d2 |. Js.Dict.get(lbl)) {
      | None =>
        let tA = abduceT(styp1.t, styp1.t);
        let oA = abduceO(styp1.o, NotOpt);
        let pA = - styp1.p;
        let stypA = {t: tA, o: oA, p: pA};
        if (! stypIsSame(stypA)) {
          d |. Js.Dict.set(lbl, stypA);
        };
      | Some(_) => ()
      };
    d2 |. Js.Dict.entries |. Array.forEach(doItem2);
    d1 |. Js.Dict.entries |. Array.forEach(doItem1);
    let arr =
      d |. Js.Dict.entries |. Array.keep(((_, styp)) => ! stypIsSame(styp));
    arr |. Array.length == 0 ? Same : Object(arr |. Js.Dict.fromArray);
  | (Array(styp1), Array(styp2)) =>
    let stypA = abduce(styp1, styp2);
    stypIsSame(stypA) ? Same : Array(stypA);
  | _ => assert(false)
  }
and abduceO = (o1: o, o2: o) : o =>
  switch (o1, o2) {
  | (NotOpt, NotOpt) => NotOpt
  | (NotOpt, Opt) => Opt
  | (Opt, Opt) => NotOpt
  | (Opt, NotOpt) => assert(false)
  };

let abduceCheck = (styp1, styp2) => {
  let stypA = abduce(styp1, styp2);
  if (styp1 ++ stypA != styp2) {
    Js.log("checkAbduce failed");
    Js.log2("styp1", styp1 |. PrettyPrint.styp);
    Js.log2("styp2", styp2 |. PrettyPrint.styp);
    Js.log2("stypA", stypA |. PrettyPrint.styp);
    Js.log2("styp1 ++ stypA", styp1 ++ stypA |. PrettyPrint.styp);
    assert(false);
  };
  stypA;
};
let (--) = (styp2, styp1) => abduceCheck(styp1, styp2);

let rec diff = (styp1: styp, styp2: styp) : (styp, styp, styp) => {
  let (tA1, tA2, tB) = diffT(styp1.t, styp2.t);
  let (oA1, oA2, oB) = diffO(styp1.o, styp2.o);
  let pB = min(styp1.p, styp2.p);
  let (pA1, pA2) = (styp1.p - pB, styp2.p - pB);
  let stypA1 = {t: tA1, o: oA1, p: pA1};
  let stypA2 = {t: tA2, o: oA2, p: pA2};
  let stypB = {t: tB, o: oB, p: pB};
  (stypA1, stypA2, stypB);
}
and diffT = (t1: t, t2: t) : (t, t, t) =>
  switch (t1, t2) {
  | (Same, _) => (Same, t2, Same)
  | (_, Same) => (t1, Same, Same)

  | (Number, Number) => (Same, Same, Number)
  | (String, String) => (Same, Same, String)
  | (Boolean, Boolean) => (Same, Same, Boolean)

  | (Object(d1), Object(d2)) =>
    let dA1 = Js.Dict.empty();
    let dA2 = Js.Dict.empty();
    let dB = Js.Dict.empty();
    let doItem2 = ((lbl, styp2)) =>
      switch (d1 |. Js.Dict.get(lbl)) {
      | None =>
        if (! stypIsSame(styp2)) {
          dA2 |. Js.Dict.set(lbl, styp2);
        }
      | Some(styp1) =>
        let (stypA1, stypA2, stypB) = diff(styp1, styp2);
        if (! stypIsSame(stypA1)) {
          dA1 |. Js.Dict.set(lbl, stypA1);
        };
        if (! stypIsSame(stypA2)) {
          dA2 |. Js.Dict.set(lbl, stypA2);
        };
        dB |. Js.Dict.set(lbl, stypB);
      };
    let doItem1 = ((lbl, styp1)) =>
      switch (d2 |. Js.Dict.get(lbl)) {
      | None =>
        if (! stypIsSame(styp1)) {
          dA1 |. Js.Dict.set(lbl, styp1);
        }
      | Some(_) => ()
      };
    d2 |. Js.Dict.entries |. Array.forEach(doItem2);
    d1 |. Js.Dict.entries |. Array.forEach(doItem1);
    let tA1 =
      dA1 |. Js.Dict.entries |. Array.length == 0 ? Same : dA1 |. Object;
    let tA2 =
      dA2 |. Js.Dict.entries |. Array.length == 0 ? Same : dA2 |. Object;
    let tB = dB |. Object;
    (tA1, tA2, tB);

  | (Array(styp1), Array(styp2)) =>
    let (stypA1, stypA2, stypB) = diff(styp1, styp2);
    let tA1 = stypIsSame(stypA1) ? Same : Array(stypA1);
    let tA2 = stypIsSame(stypA2) ? Same : Array(stypA2);
    let tB = Array(stypB);
    (tA1, tA2, tB);
  | _ => assert(false)
  }
and diffO = (o1: o, o2: o) : (o, o, o) =>
  switch (o1, o2) {
  | (NotOpt, _) => (NotOpt, o2, NotOpt)
  | (_, NotOpt) => (o1, NotOpt, NotOpt)
  | (Opt, Opt) => (NotOpt, NotOpt, Opt)
  };

let diffCheck = (styp1, styp2) => {
  let (stypA1, stypA2, stypB) = diff(styp1, styp2);
  assert(stypB ++ stypA1 == styp1);
  assert(stypB ++ stypA2 == styp2);
  (stypA1, stypA2, stypB);
};
