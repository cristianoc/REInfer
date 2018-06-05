open Belt;
open Styp;

let typesNotMatched = (t1, t2) =>
  Annotation(
    "TypeErr",
    Empty,
    [|
      ("lhs", {t: t1, o: NotOpt, p: 0}),
      ("rhs", {t: t2, o: NotOpt, p: 0}),
    |],
  );

let rec fromJson = (json: Js.Json.t) : styp =>
  switch (Js.Json.classify(json)) {
  | JSONFalse
  | JSONTrue => {t: Boolean, o: NotOpt, p: 1}
  | JSONNull => {t: Empty, o: Opt, p: 0}
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
    |. Array.reduce({t: Empty, o: NotOpt, p: 0}, (styp, json) =>
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

