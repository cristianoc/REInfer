open Belt;
open Styp;

type diffStyp = {
  styp1: styp,
  styp2: styp,
  stypA1: styp,
  stypA2: styp,
  stypB: styp,
};

type diffTyp = {
  typA1: typ,
  typA2: typ,
  typB: typ,
};

type t = diffStyp;

/* Inline the differences in the B part */
let inlineDifferences = true;

let rec diffStyp = (styp1: styp, styp2: styp) : t => {
  let {typA1, typA2, typB} = diffTyp(styp1.typ, styp2.typ);
  let (oA1, oA2, oB) = diffO(styp1.o, styp2.o);
  let pB = min(styp1.p, styp2.p);
  let (pA1, pA2) = (P.(styp1.p -- pB), P.(styp2.p -- pB));
  let stypA1 = {typ: typA1, o: oA1, p: pA1};
  let stypA2 = {typ: typA2, o: oA2, p: pA2};
  let stypB = {typ: typB, o: oB, p: pB};
  open! TypeCheck;
  {styp1, styp2, stypA1, stypA2, stypB};
}
and diffO = (o1: o, o2: o) : (o, o, o) =>
  switch (o1, o2) {
  | (NotOpt, _) => (NotOpt, o2, NotOpt)
  | (_, NotOpt) => (o1, NotOpt, NotOpt)
  | (Opt(p1), Opt(p2)) => (
      p1 > p2 ? Opt(P.(p1 -- p2)) : NotOpt,
      p2 > p1 ? Opt(P.(p2 -- p1)) : NotOpt,
      Opt(min(p1, p2)),
    )
  }
and diffTyp = (typ1: typ, typ2: typ) : diffTyp =>
  switch (typ1, typ2) {
  | (Empty | Diff(_), _) => {typA1: Empty, typA2: typ2, typB: Empty}
  | (_, Empty | Diff(_)) => {typA1: typ1, typA2: Empty, typB: Empty}

  | (Number, Number) => {typA1: Empty, typA2: Empty, typB: Number}
  | (String, String) => {typA1: Empty, typA2: Empty, typB: String}
  | (Boolean, Boolean) => {typA1: Empty, typA2: Empty, typB: Boolean}

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
    let typA1 =
      dA1 |. Js.Dict.entries |. Array.length == 0 ? Empty : dA1 |. Object;
    let typA2 =
      dA2 |. Js.Dict.entries |. Array.length == 0 ? Empty : dA2 |. Object;
    let typB = dB |. Object;
    {typA1, typA2, typB};

  | (Array(styp1), Array(styp2)) =>
    let {stypA1, stypA2, stypB} = diffStyp(styp1, styp2);
    let typA1 = stypIsEmpty(stypA1) ? Empty : Array(stypA1);
    let typA2 = stypIsEmpty(stypA2) ? Empty : Array(stypA2);
    let typB = Array(stypB);
    {typA1, typA2, typB};
  | (Number, _)
  | (_, Number)
  | (String, _)
  | (_, String)
  | (Boolean, _)
  | (_, Boolean)
  | (Object(_), _)
  | (_, Object(_))
  | (Union(_), _)
  | (_, Union(_)) => assert(false)
  };

let rec combine = (stypA1: styp, stypA2: styp, stypB: styp) : styp =>
  if (stypA1.p != P.zero
      || stypA1.o != NotOpt
      || stypA2.p != P.zero
      || stypA2.o != NotOpt) {
    {...stypB, typ: Diff(stypB.typ, stypA1, stypA2)};
  } else {
    {...stypB, typ: combineT(stypA1.typ, stypA2.typ, stypB.typ)};
  }
and combineT = (typA1: typ, typA2: typ, typB: typ) : typ =>
  switch (typA1, typA2, typB) {
  | (Array(_) | Empty, Array(_) | Empty, Array(stypB)) =>
    let getStyp = typ =>
      switch (typ) {
      | Array(styp) => styp
      | _ => stypEmpty
      };
    let stypA1 = typA1 |. getStyp;
    let stypA2 = typA2 |. getStyp;
    combine(stypA1, stypA2, stypB) |. Array;
  | (Object(_) | Empty, Object(_) | Empty, Object(dictB)) =>
    let d = Js.Dict.empty();
    let getDict = typ =>
      switch (typ) {
      | Object(dict) => dict
      | _ => Js.Dict.empty()
      };
    let dictA1 = typA1 |. getDict;
    let dictA2 = typA2 |. getDict;
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
  | _ => typB
  };

let diff = (styp1, styp2) => {
  let d = diffStyp(styp1, styp2);
  inlineDifferences ?
    {...d, stypB: combine(d.stypA1, d.stypA2, d.stypB)} : d;
};
let diffCheck = (styp1, styp2) => {
  let d = diffStyp(styp1, styp2);
  open! TypeCheck;
  assert(d.stypB ++ d.stypA1 == styp1);
  assert(d.stypB ++ d.stypA2 == styp2);
  inlineDifferences ?
    {...d, stypB: combine(d.stypA1, d.stypA2, d.stypB)} : d;
};