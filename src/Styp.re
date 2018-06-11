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
  | Number
  | String
  | Boolean
  | Object(Js.Dict.t(styp))
  | Array(styp)
  | Union(list(styp))
  | Diff(typ, styp, styp)
and styp = {
  typ,
  o,
  p,
};

let stypIsNull = (styp: styp) =>
  styp.typ == Empty && styp.o == Opt(P.one) && styp.p == P.zero;

let stypEmpty = {typ: Empty, o: NotOpt, p: P.zero};
let stypIsEmpty = styp =>
  switch (styp) {
  | {typ: Empty, o: NotOpt, p} when p == P.zero => true
  | _ => false
  };