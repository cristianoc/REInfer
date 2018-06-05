open Belt;
open Styp;

let typesNotMatched = (t1, t2) =>
  Annotation(
    "TypeErr",
    Empty,
    [|
      ("lhs", {t: t1, o: NotOpt, p: P.zero}),
      ("rhs", {t: t2, o: NotOpt, p: P.zero}),
    |],
  );

let rec fromJson = (json: Js.Json.t) : styp =>
  switch (Js.Json.classify(json)) {
  | JSONFalse
  | JSONTrue => {t: Boolean, o: NotOpt, p: P.one}
  | JSONNull => {t: Empty, o: Opt(P.one), p: P.one}
  | JSONString(_) => {t: String, o: NotOpt, p: P.one}
  | JSONNumber(_) => {t: Number, o: NotOpt, p: P.one}
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
      p: P.one,
    };
  | JSONArray(a) =>
    a
    |. Array.reduce({t: Empty, o: NotOpt, p: P.zero}, (styp, json) =>
         styp ++ fromJson(json)
       )
    |. (styp => {t: Array(styp), o: NotOpt, p: P.one})
  }
and (++) = (styp1, styp2) => {
  let t = plusT(styp1.t, styp2.t);
  let o = plusO(styp1.o, styp2.o);
  open! P;
  let p = styp1.p ++ styp2.p;
  {t, o, p};
}
and plusO = (o1, o2) =>
  switch (o1, o2) {
  | (NotOpt, o)
  | (o, NotOpt) => o
  | (Opt(p1), Opt(p2)) =>
    open! P;
    Opt(p1 ++ p2);
  }
and plusT = (t1, t2) =>
  switch (t1, t2) {
  | (Annotation(_, t, _), _) => plusT(t, t2)
  | (_, Annotation(_, t, _)) => plusT(t1, t)
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
  | (_, Object(_)) => typesNotMatched(t1, t2)
  };