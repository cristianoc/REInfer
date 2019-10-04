module P: {
  type t;
  let zero: t;
  let one: t;
  let (++): (t, t) => t;
  let (--): (t, t) => t;
  let toString: t => string;
  let toFloat: t => float;
} = {
  type t = int;
  let zero = 0;
  let one = 1;

  let (++) = (+);

  let (--) = (-);
  let toString = string_of_int;
  let toFloat = float_of_int;
};

type p = P.t;

type o =
  | NotOpt
  | Opt(p);

type typ =
  | Empty
  | Same(typ)
  | Number(option(float))
  | String(option(string))
  | Boolean(option(bool))
  | Object(Js.Dict.t(styp))
  | Array(styp)
  | Union(list(styp))
  | Diff(typ, styp, styp)
and styp = {
  typ,
  o,
  p,
};

let string_of_bool = b => b ? "true" : "false";

let constToString = typ =>
  switch (typ) {
  | Number(x) =>
    "number"
    ++ x->(Belt.Option.mapWithDefault("", f => ":" ++ Js.Float.toString(f)))
  | String(x) => "string" ++ x->(Belt.Option.mapWithDefault("", s => ":" ++ s))
  | Boolean(x) =>
    "boolean"
    ++ x->(Belt.Option.mapWithDefault("", b => ":" ++ string_of_bool(b)))
  | _ => assert(false)
  };

let rec stripDiffStyp = styp => {...styp, typ: styp.typ->stripDiffTyp}
and stripDiffTyp = typ =>
  switch (typ) {
  | Empty
  | Number(_)
  | String(_)
  | Boolean(_) => typ
  | Same(typ) => Same(typ->stripDiffTyp)
  | Object(d) => Js.Dict.map((. styp) => stripDiffStyp(styp), d)->Object
  | Array(styp) => Array(styp->stripDiffStyp)
  | Union(styps) => styps->(Belt.List.map(stripDiffStyp))->Union
  | Diff(t, _, _) => t->stripDiffTyp
  };

let typIsEmpty = typ =>
  switch (typ) {
  | Empty
  | Same(_) => true
  | _ => false
  };

let stypIsNull = (styp: styp) =>
  switch (styp.o) {
  | NotOpt => false
  | Opt(p) => styp.typ->typIsEmpty && styp.p == p
  };

let stypEmpty = {typ: Empty, o: NotOpt, p: P.zero};

let stypIsEmpty = styp =>
  switch (styp) {
  | {typ, o: NotOpt, p} when typ->typIsEmpty && p == P.zero => true
  | _ => false
  };

let stypToUnion = styp =>
  switch (styp.typ) {
  | Union(styps) => styps
  | _ => [styp]
  };

let compareEntries = ((lbl1: string, _), (lbl2: string, _)) =>
  compare(lbl1, lbl2);

let makeObject = arr =>
  arr
  ->Belt.List.fromArray
  ->(Belt.List.sort(compareEntries))
  ->Js.Dict.fromList
  ->Object;

let compareStyp = (x: styp, y: styp): int => compare(x, y);
let makeUnion = styps => styps->(Belt.List.sort(compareStyp))->Union;

let pToJson = p => p->P.toString->Js.Json.string;

let rec stypToJson = (styp: styp): Js.Json.t => {
  let dict = Js.Dict.empty();
  dict->(Js.Dict.set("typ", styp.typ->typToJson));
  switch (styp.o) {
  | NotOpt => ()
  | Opt(p1) => dict->(Js.Dict.set("opt", p1->pToJson))
  };
  dict->(Js.Dict.set("p", styp.p->pToJson));
  dict->Js.Json.object_;
}
and typToJson = (typ: typ): Js.Json.t => {
  open Js.Json;
  let arr = a => a->Js.Dict.fromArray->object_;
  switch (typ) {
  | Empty => [|("kind", "Empty"->string)|]->Js.Dict.fromArray->object_
  | Same(typ) => [|("kind", "Same"->string), ("typ", typ->typToJson)|]->arr
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
      ->string;
    [|("kind", kind), ("value", typ->constToString->string)|]->arr;
  | Object(d) =>
    let entries =
      Js.Dict.entries(d)
      ->(Belt.Array.map(((lbl, styp)) => (lbl, styp->stypToJson)))
      ->arr;
    [|("kind", "Object"->string), ("entries", entries)|]->arr;
  | Array(styp) =>
    let typ = styp->stypToJson;
    [|("kind", "Array"->string), ("typ", typ)|]->arr;
  | Union(styps) =>
    let entries =
      styps
      ->Belt.List.toArray
      ->(
          Belt.Array.mapWithIndex((i, styp) =>
            ("u" ++ string_of_int(i), styp->stypToJson)
          )
        )
      ->arr;
    [|("kind", "Union"->string), ("entries", entries)|]->arr;
  | Diff(t, lhs, rhs) =>
    let common = t->typToJson;
    let lhs = lhs->stypToJson;
    let rhs = rhs->stypToJson;
    [|
      ("kind", "Diff"->string),
      ("common", common),
      ("lhs", lhs),
      ("rhs", rhs),
    |]
    ->arr;
  };
};