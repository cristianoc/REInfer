open Styp;

type mode = {singletonTypes: bool};

let defaultMode = {singletonTypes: false};
let singletonMode = {singletonTypes: true};

let rec fromJson = (~mode=defaultMode, json: Js.Json.t): styp =>
  switch (Js.Json.classify(json)) {
  | JSONFalse => {
      typ: Boolean(mode.singletonTypes ? Some(false) : None),
      o: NotOpt,
      p: P.one,
    }
  | JSONTrue => {
      typ: Boolean(mode.singletonTypes ? Some(true) : None),
      o: NotOpt,
      p: P.one,
    }
  | JSONNull => {typ: Empty, o: Opt(P.one), p: P.one}
  | JSONString(x) => {
      typ: String(mode.singletonTypes ? Some(x) : None),
      o: NotOpt,
      p: P.one,
    }
  | JSONNumber(x) => {
      typ: Number(mode.singletonTypes ? Some(x) : None),
      o: NotOpt,
      p: P.one,
    }
  | JSONObject(dict) =>
    let do_entry = ((lbl, v)) => {
      let styp = fromJson(~mode, v);
      (lbl, styp);
    };
    {
      typ: Js.Dict.entries(dict)->(Belt.Array.map(do_entry))->makeObject,
      o: NotOpt,
      p: P.one,
    };
  | JSONArray(a) =>
    a
    ->(
        Belt.Array.reduce({typ: Empty, o: NotOpt, p: P.zero}, (styp, json) =>
          styp ++ fromJson(~mode, json)
        )
      )
    ->(styp => {typ: Array(styp), o: NotOpt, p: P.one})
  }
and plusStyp = (styp1, styp2) => {
  let typ =
    switch (plusTyp(styp1.typ, styp2.typ)) {
    | Some(typ) => typ
    | None => plusUnion(styp1->stypToUnion, styp2->stypToUnion)
    };
  let o = plusO(styp1.o, styp2.o);
  open! P;
  let p = styp1.p ++ styp2.p;
  {typ, o, p};
}
and plusO = (o1, o2) =>
  switch (o1, o2) {
  | (NotOpt, o)
  | (o, NotOpt) => o
  | (Opt(p1), Opt(p2)) =>
    open! P;
    Opt(p1 ++ p2);
  }
and plusTyp = (typ1, typ2): option(typ) =>
  switch (typ1, typ2) {
  | (Diff(typ, _, _), _) => plusTyp(typ, typ2)
  | (_, Diff(typ, _, _)) => plusTyp(typ1, typ)
  | (Empty, t)
  | (t, Empty) => t->Some
  | (Same(t1), t)
  | (t, Same(t1)) => plusTyp(t, t1)
  | (Number(x), Number(y)) => x == y ? Number(x)->Some : None
  | (String(x), String(y)) => x == y ? String(x)->Some : None
  | (Boolean(x), Boolean(y)) => x == y ? Boolean(x)->Some : None
  | (Object(d1), Object(d2)) =>
    let d = Js.Dict.empty();
    let doItem = ((lbl, styp)) =>
      switch (d->(Js.Dict.get(lbl))) {
      | None => d->(Js.Dict.set(lbl, styp))
      | Some(styp1) => d->(Js.Dict.set(lbl, styp ++ styp1))
      };
    d1->Js.Dict.entries->(Belt.Array.forEach(doItem));
    d2->Js.Dict.entries->(Belt.Array.forEach(doItem));
    d->Js.Dict.entries->makeObject->Some;
  | (Array(styp1), Array(styp2)) => (styp1 ++ styp2)->Array->Some
  | (Number(_), _)
  | (_, Number(_))
  | (String(_), _)
  | (_, String(_))
  | (Boolean(_), _)
  | (_, Boolean(_))
  | (Object(_), _)
  | (_, Object(_))
  | (Union(_), _)
  | (_, Union(_)) => None
  }
and plusUnion = (styps1, styps2) => {
  let rec findMatch = (t, ts, acc) =>
    switch (ts) {
    | [t1, ...ts1] =>
      if (plusTyp(t.typ, t1.typ) != None) {
        Some((t1, acc->Belt.List.reverse->(Belt.List.concat(ts1))));
      } else {
        findMatch(t, ts1, [t1, ...acc]);
      }
    | [] => None
    };
  let rec plus = (ls1, ls2) =>
    switch (ls1, ls2) {
    | ([t1, ...ts1], _) =>
      switch (findMatch(t1, ls2, [])) {
      | None => [t1, ...plus(ts1, ls2)]
      | Some((t2, ts2)) => [plusStyp(t1, t2), ...plus(ts1, ts2)]
      }
    | ([], ts) => ts
    };
  plus(styps1, styps2)->makeUnion;
}
and (++) = (styp1, styp2) => plusStyp(styp1, styp2);