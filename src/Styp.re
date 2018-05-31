type p = int;
type o =
  | NotOpt
  | Opt;
type t =
  | Same
  | Number
  | String
  | Boolean
  | Object(Js.Dict.t(styp))
  | Array(styp)
and styp = {
  t,
  o,
  p,
};

let stypIsNull = (styp: styp) =>
  styp.t == Same && styp.o == Opt && styp.p == 0;

let stypSame = {t: Same, o: NotOpt, p: 0};
let stypIsSame = styp =>
  switch (styp) {
  | {t: Same, o: NotOpt, p: 0} => true
  | _ => false
  };