open Belt;

type t = {
  samples: list(Styp.styp),
  sum: Styp.styp,
  lastDiff: Diff.t,
};

let empty = {
  samples: [],
  sum: Styp.stypEmpty,
  lastDiff: Diff.diff(Styp.stypEmpty, Styp.stypEmpty),
};

let toList = ({samples}) => samples |. List.reverse;

let getLastDiff = ({lastDiff}) => lastDiff;
let getSum = ({sum}) => sum;

let getCommon = ({lastDiff}) => lastDiff.stypB |. Styp.stripDiffStyp;

let add = (t, styp) => {
  let samples = [styp, ...t.samples];
  let sum = TypeCheck.(++)(t.sum, styp);
  let lastDiff = Diff.diff(t.samples == [] ? styp : t |. getCommon, styp);
  {samples, sum, lastDiff};
};

let addMany = (t, styps) => styps |. List.reduce(t, add);

let getAllDiffs = t => {
  let common = t |. getCommon;
  t |. toList |. List.map(styp => Diff.diff(common, styp));
};