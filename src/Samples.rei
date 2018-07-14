/**
 * Type for samples.
 *
 * Samples are obtained by adding types in a given order.
 * For each addition, the common type and sum type are updated.
 * The common type is the type in common to all samples.
 * The sum type is the aggregate sum of all samples.
 * One can get the last diff (w.r.t. the common type before the last addition),
 * or all the diffs (w.r.t. the current common type).
 */
type t;

/** Add one sample. */
let add: (t, Styp.styp) => t;

/** Add a list of samples. */
let addMany: (t, list(Styp.styp)) => t;

/** Empty samples. */
let empty: t;

/** Get the diff of all the samples w.r.t. the common type. */
let getAllDiffs: t => list(Diff.t);

/** Get the type in common to all the samples. */
let getCommon: t => Styp.styp;

/**
 * Get the diff obtained when adding the last sample:
 * The diff between the previous common type and the newly added element.
 */
let getLastDiff: t => Diff.t;

/** Get the type of the aggregate sum of all the samples. */
let getSum: t => Styp.styp;

/** Get the list of samples in the order they were added. */
let toList: t => list(Styp.styp);