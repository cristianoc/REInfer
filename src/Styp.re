type p = int;
type o =
  | NotOpt
  | Opt;
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
  styp.t == Empty && styp.o == Opt && styp.p == 0;

let stypEmpty = {t: Empty, o: NotOpt, p: 0};
let stypIsEmpty = styp =>
  switch (styp) {
  | {t: Empty, o: NotOpt, p: 0} => true
  | _ => false
  };