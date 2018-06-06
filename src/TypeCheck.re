open Belt;
open Styp;

let typesNotMatched = (typ1, typ2) =>
  Annotation(
    "TypeErr",
    Empty,
    [|
      ("lhs", {typ: typ1, o: NotOpt, p: P.zero}),
      ("rhs", {typ: typ2, o: NotOpt, p: P.zero}),
    |],
  );

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
and (++) = (styp1, styp2) => {
  let typ = plusTyp(styp1.typ, styp2.typ);
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
and plusTyp = (typ1, typ2) =>
  switch (typ1, typ2) {
  | (Annotation(_, typ, _), _) => plusTyp(typ, typ2)
  | (_, Annotation(_, typ, _)) => plusTyp(typ1, typ)
  | (Empty, t)
  | (t, Empty) => t
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
  | (Number, _)
  | (_, Number)
  | (String, _)
  | (_, String)
  | (Boolean, _)
  | (_, Boolean)
  | (Object(_), _)
  | (_, Object(_)) => typesNotMatched(typ1, typ2)
  };