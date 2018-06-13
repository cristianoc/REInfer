open Belt;

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

let constToString = typ =>
  switch (typ) {
  | Number(x) =>
    "number"
    ++ (x |. Option.mapWithDefault("", f => ":" ++ string_of_float(f)))
  | String(x) => "string" ++ (x |. Option.mapWithDefault("", s => ":" ++ s))
  | Boolean(x) =>
    "boolean"
    ++ (x |. Option.mapWithDefault("", b => ":" ++ string_of_bool(b)))
  | _ => assert(false)
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
  | Opt(p) => styp.typ |. typIsEmpty && styp.p == p
  };

let stypEmpty = {typ: Empty, o: NotOpt, p: P.zero};

let stypIsEmpty = styp =>
  switch (styp) {
  | {typ, o: NotOpt, p} when typ |. typIsEmpty && p == P.zero => true
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
  |. List.fromArray
  |. List.sort(compareEntries)
  |. Js.Dict.fromList
  |. Object;

let compareStyp = (x: styp, y: styp) : int => compare(x, y);
let makeUnion = styps => styps |. List.sort(compareStyp) |. Union;