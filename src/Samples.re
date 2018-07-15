open Belt;

type t = {
  samples: list(Styp.styp), /* stored in reverse order */
  sum: Styp.styp,
  prevSum: Styp.styp,
  common: Styp.styp,
  prevCommon: Styp.styp,
};

let empty = {
  samples: [],
  sum: Styp.stypEmpty,
  prevSum: Styp.stypEmpty,
  common: Styp.stypEmpty,
  prevCommon: Styp.stypEmpty,
};

let toList = ({samples}) => samples |. List.reverse;

let getSum = ({sum}) => sum;

let getCommon = ({common}) => common;

let getLast = ({samples}) =>
  switch (samples) {
  | [last, ..._] => last
  | [] => Styp.stypEmpty
  };

let getPrev = ({samples}) =>
  switch (samples) {
  | [_, prev, ..._] => prev
  | [_]
  | [] => Styp.stypEmpty
  };

let getPrevSum = ({prevSum}) => prevSum;

let getPrevCommon = ({prevCommon}) => prevCommon;

let add = (t, styp) => {
  let samples = [styp, ...t.samples];
  let prevSum = t.sum;
  let sum = TypeCheck.(++)(t.sum, styp);
  let prevCommon = t.common;
  let common =
    t.samples == [] ?
      styp : Diff.diff(t.common, styp).stypB |. Styp.stripDiffStyp;
  {samples, sum, prevSum, common, prevCommon};
};

let addMany = (t, styps) => {
  let styp = styps |. List.reduce(Styp.stypEmpty, TypeCheck.(++));
  t |. add(styp);
};

let fromList = styps => styps |. List.reduce(empty, add);

let getAllDiffs = t => {
  let common = t |. getCommon;
  t |. toList |. List.map(styp => Diff.diff(common, styp));
};