/**
 * Serializer for arbitrary values.
 * Note: might not work across versions of the compiler (as the runtime representation might change).
 * Note: uses json stringify under the hood: does not support functions or cyclic values.
 */

let toString: 'a => string;

let fromString: string => 'a;