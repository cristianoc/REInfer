/**
 * Type for samples.
 *
 * Samples are obtained by adding types in a given order.
 * For each addition, the common type and sum type are updated.
 * The common type is the type in common to all samples.
 * The sum type is the aggregate sum of all samples.
 * There is access to the previous version of all values.
 */
type t;

/** Add one sample. */
let add: (t, Styp.styp) => t;

/**
 * Add a list as a single sample.
 * Equivalent to adding a single sample with the sum type of the elements.
 */
let addMany: (t, list(Styp.styp)) => t;

/** Empty samples. */
let empty: t;

/** Add the samples in the order they appear in the list. */
let fromList: list(Styp.styp) => t;

/** Get the list of diffs between the common type and each sample. */
let getAllDiffs: t => list(Diff.t);

/** Get the type in common to all the samples. */
let getCommon: t => Styp.styp;

/** Get the last sample added. */
let getLast: t => Styp.styp;

/** Get the second-last sample added. */
let getPrev: t => Styp.styp;

/** Get the common type as it was before adding the last sample. */
let getPrevCommon: t => Styp.styp;

/** Get the sum type as it was before adding the last sample. */
let getPrevSum: t => Styp.styp;

/** Get the type of the aggregate sum of all the samples. */
let getSum: t => Styp.styp;

/** Get the list of samples in the order they were added. */
let toList: t => list(Styp.styp);