open Belt;
open Styp;
let rec abduce = (styp1: styp, styp2: styp) : styp =>
  switch (styp1, styp2) {
  | ({t: t1, o: o1, p: p1}, {t: t2, o: o2, p: p2}) =>
    let t = abduceT(t1, t2);
    let o = abduceO(o1, o2);
    let p = p2 - p1;
    {t, o, p};
  }
and abduceT = (t1: t, t2: t) : t =>
  switch (t1, t2) {
  | (Empty, _) => t2
  | (Number, Number) => Empty
  | (String, String) => Empty
  | (Boolean, Boolean) => Empty
  | (Object(d1), Object(d2)) =>
    let d = Js.Dict.empty();
    let doItem2 = ((lbl, styp2)) =>
      switch (d1 |. Js.Dict.get(lbl)) {
      | None =>
        if (! stypIsEmpty(styp2)) {
          d |. Js.Dict.set(lbl, styp2);
        }
      | Some(styp1) =>
        let stypA = abduce(styp1, styp2);
        if (! stypIsEmpty(stypA)) {
          d |. Js.Dict.set(lbl, stypA);
        };
      };
    let doItem1 = ((lbl, styp1)) =>
      switch (d2 |. Js.Dict.get(lbl)) {
      | None =>
        let tA = abduceT(styp1.t, styp1.t);
        let oA = abduceO(styp1.o, NotOpt);
        let pA = - styp1.p;
        let stypA = {t: tA, o: oA, p: pA};
        if (! stypIsEmpty(stypA)) {
          d |. Js.Dict.set(lbl, stypA);
        };
      | Some(_) => ()
      };
    d2 |. Js.Dict.entries |. Array.forEach(doItem2);
    d1 |. Js.Dict.entries |. Array.forEach(doItem1);
    let arr =
      d |. Js.Dict.entries |. Array.keep(((_, styp)) => ! stypIsEmpty(styp));
    arr |. Array.length == 0 ? Empty : Object(arr |. Js.Dict.fromArray);
  | (Array(styp1), Array(styp2)) =>
    let stypA = abduce(styp1, styp2);
    stypIsEmpty(stypA) ? Empty : Array(stypA);
  | _ => assert(false)
  }
and abduceO = (o1: o, o2: o) : o =>
  switch (o1, o2) {
  | (NotOpt, NotOpt) => NotOpt
  | (NotOpt, Opt) => Opt
  | (Opt, Opt) => NotOpt
  | (Opt, NotOpt) => assert(false)
  };

let abduceCheck = (styp1, styp2) => {
  let stypA = abduce(styp1, styp2);
  open !TypeCheck;
  if (styp1 ++ stypA != styp2) {
    Js.log("checkAbduce failed");
    Js.log2("styp1", styp1 |. PrettyPrint.styp);
    Js.log2("styp2", styp2 |. PrettyPrint.styp);
    Js.log2("stypA", stypA |. PrettyPrint.styp);
    Js.log2("styp1 ++ stypA", styp1 ++ stypA |. PrettyPrint.styp);
    assert(false);
  };
  stypA;
};
let (--) = (styp2, styp1) => abduceCheck(styp1, styp2);