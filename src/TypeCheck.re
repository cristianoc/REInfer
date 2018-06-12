open Belt;
open Styp;

let rec fromJson = (json: Js.Json.t) : styp =>
  switch (Js.Json.classify(json)) {
  | JSONFalse
  | JSONTrue => {typ: Boolean, o: NotOpt, p: P.one}
  | JSONNull => {typ: Empty, o: Opt(P.one), p: P.one}
  | JSONString(_) => {typ: String, o: NotOpt, p: P.one}
  | JSONNumber(_) => {typ: Number, o: NotOpt, p: P.one}
  | JSONObject(dict) =>
    let do_entry = ((lbl, v)) => {
      let styp = fromJson(v);
      (lbl, styp);
    };
    {
      typ:
        Object(
          Js.Dict.entries(dict) |. Array.map(do_entry) |. Js.Dict.fromArray,
        ),
      o: NotOpt,
      p: P.one,
    };
  | JSONArray(a) =>
    a
    |. Array.reduce({typ: Empty, o: NotOpt, p: P.zero}, (styp, json) =>
         styp ++ fromJson(json)
       )
    |. (styp => {typ: Array(styp), o: NotOpt, p: P.one})
  }
and plusStyp = (styp1, styp2) => {
  let typ =
    switch (plusTyp(styp1.typ, styp2.typ)) {
    | Some(typ) => typ
    | None => plusUnion(styp1 |. stypToUnion, styp2 |. stypToUnion)
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
and plusTyp = (typ1, typ2) : option(typ) =>
  switch (typ1, typ2) {
  | (Diff(typ, _, _), _) => plusTyp(typ, typ2)
  | (_, Diff(typ, _, _)) => plusTyp(typ1, typ)
  | (Empty, t)
  | (t, Empty) => t |. Some
  | (Number, Number) => Number |. Some
  | (String, String) => String |. Some
  | (Boolean, Boolean) => Boolean |. Some
  | (Object(d1), Object(d2)) =>
    let d = Js.Dict.empty();
    let doItem = ((lbl, styp)) =>
      switch (d |. Js.Dict.get(lbl)) {
      | None => d |. Js.Dict.set(lbl, styp)
      | Some(styp1) => d |. Js.Dict.set(lbl, styp ++ styp1)
      };
    d1 |. Js.Dict.entries |. Array.forEach(doItem);
    d2 |. Js.Dict.entries |. Array.forEach(doItem);
    Object(d |. Js.Dict.entries |. Js.Dict.fromArray) |. Some;
  | (Array(styp1), Array(styp2)) =>
    let styp = styp1 ++ styp2;
    styp |. Array |. Some;
  | (Number, _)
  | (_, Number)
  | (String, _)
  | (_, String)
  | (Boolean, _)
  | (_, Boolean)
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
        Some((t1, acc |. List.reverse |. List.concat(ts1)));
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
  plus(styps1, styps2) |. Union;
}
and (++) = (styp1, styp2) => plusStyp(styp1, styp2);