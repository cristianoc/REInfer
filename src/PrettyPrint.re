open Belt;
open Styp;

let pToJson = p => p |. P.toString |. Js.Json.string;

let rec stypToJson = (styp: styp) : Js.Json.t => {
  let dict = Js.Dict.empty();
  dict |. Js.Dict.set("typ", styp.typ |. typToJson);
  switch (styp.o) {
  | NotOpt => ()
  | Opt(p1) => dict |. Js.Dict.set("opt", p1 |. pToJson)
  };
  dict |. Js.Dict.set("p", styp.p |. pToJson);
  dict |. Js.Json.object_;
}
and typToJson = (typ: typ) : Js.Json.t => {
  open Js.Json;
  let arr = a => a |. Js.Dict.fromArray |. object_;
  switch (typ) {
  | Empty => [|("kind", "Empty" |. string)|] |. Js.Dict.fromArray |. object_
  | Same(typ) =>
    [|("kind", "Same" |. string), ("typ", typ |. typToJson)|] |. arr
  | Number(_)
  | String(_)
  | Boolean(_) =>
    let kind =
      (
        switch (typ) {
        | Number(_) => "Number"
        | String(_) => "String"
        | Boolean(_) => "Boolean"
        | _ => assert(false)
        }
      )
      |. string;
    [|("kind", kind), ("value", typ |. constToString |. string)|] |. arr;
  | Object(d) =>
    let entries =
      Js.Dict.entries(d)
      |. Array.map(((lbl, styp)) => (lbl, styp |. stypToJson))
      |. arr;
    [|("kind", "Object" |. string), ("entries", entries)|] |. arr;
  | Array(styp) =>
    let typ = styp |. stypToJson;
    [|("kind", "Array" |. string), ("typ", typ)|] |. arr;
  | Union(styps) =>
    let entries =
      styps
      |. List.toArray
      |. Array.mapWithIndex((i, styp) =>
           ("u" ++ string_of_int(i), styp |. stypToJson)
         )
      |. arr;
    [|("kind", "Union" |. string), ("entries", entries)|] |. arr;
  | Diff(t, lhs, rhs) =>
    let common = t |. typToJson;
    let lhs = lhs |. stypToJson;
    let rhs = rhs |. stypToJson;
    [|
      ("kind", "Diff" |. string),
      ("common", common),
      ("lhs", lhs),
      ("rhs", rhs),
    |]
    |. arr;
  };
};

let diffToJson = (diff: Diff.t) => {
  let styp1 = diff.styp1 |. stypToJson;
  let styp2 = diff.styp2 |. stypToJson;
  let stypB = diff.stypB |. stypToJson;
  let stypA1 = diff.stypA1 |. stypToJson;
  let stypA2 = diff.stypA2 |. stypToJson;
  [|
    ("styp1", styp1),
    ("styp2", styp2),
    ("stypB", stypB),
    ("stypA1", stypA1),
    ("stypA2", stypA2),
  |]
  |. Js.Dict.fromArray
  |. Js.Json.object_;
};
let styp = styp => styp |. stypToJson |. Js.Json.stringify;

let diff = diff => diff |. diffToJson |. Js.Json.stringify;