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
type t =
  | Empty
  | Number
  | String
  | Boolean
  | Object(Js.Dict.t(styp))
  | Array(styp)
  | Annotation(string, t, array((string, styp)))
and styp = {
  t,
  o,
  p,
};

let stypIsNull = (styp: styp) =>
  styp.t == Empty && styp.o == Opt(P.one) && styp.p == P.zero;

let stypEmpty = {t: Empty, o: NotOpt, p: P.zero};
let stypIsEmpty = styp =>
  switch (styp) {
  | {t: Empty, o: NotOpt, p} when p == P.zero => true
  | _ => false
  };