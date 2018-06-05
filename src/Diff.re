open Belt;
open Styp;

type difft = {
  styp1: styp,
  styp2: styp,
  stypA1: styp,
  stypA2: styp,
  stypB: styp,
};

/* Inline the differences in the B part */
let inlineDifferences = true;

let rec diffStyp = (styp1: styp, styp2: styp) : difft => {
  let (tA1, tA2, tB) = diffT(styp1.t, styp2.t);
  let (oA1, oA2, oB) = diffO(styp1.o, styp2.o);
  let pB = min(styp1.p, styp2.p);
  let (pA1, pA2) = (styp1.p - pB, styp2.p - pB);
  let stypA1 = {t: tA1, o: oA1, p: pA1};
  let stypA2 = {t: tA2, o: oA2, p: pA2};
  let stypB = {t: tB, o: oB, p: pB};
  {styp1, styp2, stypA1, stypA2, stypB};
}
and diffT = (t1: t, t2: t) : (t, t, t) =>
  switch (t1, t2) {
  | (Empty | Annotation(_), _) => (Empty, t2, Empty)
  | (_, Empty | Annotation(_)) => (t1, Empty, Empty)

  | (Number, Number) => (Empty, Empty, Number)
  | (String, String) => (Empty, Empty, String)
  | (Boolean, Boolean) => (Empty, Empty, Boolean)

  | (Object(d1), Object(d2)) =>
    let dA1 = Js.Dict.empty();
    let dA2 = Js.Dict.empty();
    let dB = Js.Dict.empty();
    let doItem2 = ((lbl, styp2)) =>
      switch (d1 |. Js.Dict.get(lbl)) {
      | None =>
        if (! stypIsEmpty(styp2)) {
          dA2 |. Js.Dict.set(lbl, styp2);
        }
      | Some(styp1) =>
        let {stypA1, stypA2, stypB} = diffStyp(styp1, styp2);
        if (! stypIsEmpty(stypA1)) {
          dA1 |. Js.Dict.set(lbl, stypA1);
        };
        if (! stypIsEmpty(stypA2)) {
          dA2 |. Js.Dict.set(lbl, stypA2);
        };
        dB |. Js.Dict.set(lbl, stypB);
      };
    let doItem1 = ((lbl, styp1)) =>
      switch (d2 |. Js.Dict.get(lbl)) {
      | None =>
        if (! stypIsEmpty(styp1)) {
          dA1 |. Js.Dict.set(lbl, styp1);
        }
      | Some(_) => ()
      };
    d2 |. Js.Dict.entries |. Array.forEach(doItem2);
    d1 |. Js.Dict.entries |. Array.forEach(doItem1);
    let tA1 =
      dA1 |. Js.Dict.entries |. Array.length == 0 ? Empty : dA1 |. Object;
    let tA2 =
      dA2 |. Js.Dict.entries |. Array.length == 0 ? Empty : dA2 |. Object;
    let tB = dB |. Object;
    (tA1, tA2, tB);

  | (Array(styp1), Array(styp2)) =>
    let {stypA1, stypA2, stypB} = diffStyp(styp1, styp2);
    let tA1 = stypIsEmpty(stypA1) ? Empty : Array(stypA1);
    let tA2 = stypIsEmpty(stypA2) ? Empty : Array(stypA2);
    let tB = Array(stypB);
    (tA1, tA2, tB);
  | (Number, _)
  | (_, Number)
  | (String, _)
  | (_, String)
  | (Boolean, _)
  | (_, Boolean)
  | (Object(_), _)
  | (_, Object(_)) => (t1, t2, TypeCheck.typesNotMatched(t1, t2))
  }
and diffO = (o1: o, o2: o) : (o, o, o) =>
  switch (o1, o2) {
  | (NotOpt, _) => (NotOpt, o2, NotOpt)
  | (_, NotOpt) => (o1, NotOpt, NotOpt)
  | (Opt, Opt) => (NotOpt, NotOpt, Opt)
  };

let rec combine = (stypA1: styp, stypA2: styp, stypB: styp) : styp =>
  if (stypA1.p != 0
      || stypA1.o != NotOpt
      || stypA2.p != 0
      || stypA2.o != NotOpt) {
    {
      ...stypB,
      t:
        Annotation(
          "common",
          stypB.t,
          [|("lhs", stypA1), ("rhs", stypA2)|],
        ),
    };
  } else {
    {...stypB, t: combineT(stypA1.t, stypA2.t, stypB.t)};
  }
and combineT = (tA1: t, tA2: t, tB: t) : t =>
  switch (tA1, tA2, tB) {
  | (Array(_) | Empty, Array(_) | Empty, Array(stypB)) =>
    let getStyp = t =>
      switch (t) {
      | Array(styp) => styp
      | _ => stypEmpty
      };
    let stypA1 = tA1 |. getStyp;
    let stypA2 = tA2 |. getStyp;
    combine(stypA1, stypA2, stypB) |. Array;
  | (Object(_) | Empty, Object(_) | Empty, Object(dictB)) =>
    let d = Js.Dict.empty();
    let getDict = t =>
      switch (t) {
      | Object(dict) => dict
      | _ => Js.Dict.empty()
      };
    let dictA1 = tA1 |. getDict;
    let dictA2 = tA2 |. getDict;
    let doItem = lbl => {
      let getStyp = dict =>
        switch (dict |. Js.Dict.get(lbl)) {
        | None => stypEmpty
        | Some(styp) => styp
        };
      d
      |. Js.Dict.set(
           lbl,
           combine(dictA1 |. getStyp, dictA2 |. getStyp, dictB |. getStyp),
         );
    };
    Set.String.(
      dictA1
      |. Js.Dict.keys
      |. fromArray
      |. union(dictA2 |. Js.Dict.keys |. fromArray)
      |. union(dictB |. Js.Dict.keys |. fromArray)
      |. forEach(doItem)
    );
    Object(d);
  | _ => tB
  };

let diff = (styp1, styp2) => {
  let d = diffStyp(styp1, styp2);
  inlineDifferences ?
    {...d, stypB: combine(d.stypA1, d.stypA2, d.stypB)} : d;
};
let diffCheck = (styp1, styp2) => {
  let d = diff(styp1, styp2);
  open! TypeCheck;
  assert(d.stypB ++ d.stypA1 == styp1);
  assert(d.stypB ++ d.stypA2 == styp2);
  d;
};

type t = difft;