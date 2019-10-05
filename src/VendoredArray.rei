/***********************************************************************/
/*                                                                     */
/*                                OCaml                                */
/*                                                                     */
/*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         */
/*                                                                     */
/*  Copyright 1996 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License, with    */
/*  the special exception on linking described in file ../LICENSE.     */
/*                                                                     */
/***********************************************************************/
/* Adapted significantly by Authors of BuckleScript */

/** {!Belt.Array}
    Utililites for Array functions
*/;

<<<<<<< HEAD
[@dead "length"] /** [length xs] return the size of the array */
external length: array('a) => int = "%array_length";

[@dead "size"] /** {b See} {!length} */ external size: array('a) => int = "%array_length";
=======
/** [length xs] return the size of the array */
external length: array('a) => int = "%array_length";

/** {b See} {!length} */ external size: array('a) => int = "%array_length";
>>>>>>> DCE

/**
  [get arr i]

  If [i <= 0 <= length arr];returns [Some value] where [value] is the item at index [i]
  If [i] is out of range;returns [None]

  @example {[
    Belt.Array.get [|"a";"b";"c"|] 0 = Some "a";;
    Belt.Array.get [|"a";"b";"c"|] 3 = None;;
    Belt.Array.get [|"a";"b";"c"|] (-1) = None;;
  ]}
*/

let get: (array('a), int) => option('a);

<<<<<<< HEAD
[@dead "getExn"] /** [getExn arr i]
=======
/** [getExn arr i]
>>>>>>> DCE

    {b raise} an exception if [i] is out of range;otherwise return the value at index [i] in [arr]
*/

let getExn: (array('a), int) => 'a;

<<<<<<< HEAD
[@dead "getUnsafe"] /** [getUnsafe arr i]
=======
/** [getUnsafe arr i]
>>>>>>> DCE

    {b Unsafe}

    no  bounds checking;this would cause type error
    if [i] does not stay within range
*/
external getUnsafe: (array('a), int) => 'a = "%array_unsafe_get";

<<<<<<< HEAD
[@dead "getUndefined"] /** [getUndefined arr i]
=======
/** [getUndefined arr i]
>>>>>>> DCE

    It does the samething in the runtime as {!getUnsafe};
    it is {i type safe} since the return type still track whether it is
    in range or not
*/
external getUndefined: (array('a), int) => Js.undefined('a) =
  "%array_unsafe_get";

<<<<<<< HEAD
[@dead "set"] /** [set arr n x] modifies [arr] in place;
=======
/** [set arr n x] modifies [arr] in place;
>>>>>>> DCE
    it replaces the nth element of [arr] with [x]
    @return false means not updated due to out of range
*/

let set: (array('a), int, 'a) => bool;

<<<<<<< HEAD
[@dead "setExn"] /** [setExn arr i x]
=======
/** [setExn arr i x]
>>>>>>> DCE
    {b raise} an exception if [i] is out of range
*/

let setExn: (array('a), int, 'a) => unit;

<<<<<<< HEAD
[@dead "setUnsafe"] external setUnsafe: (array('a), int, 'a) => unit = "%array_unsafe_set";

[@dead "shuffleInPlace"] /** [shuffleInPlace arr] randomly re-orders the items in [arr] */

let shuffleInPlace: array('a) => unit;

[@dead "shuffle"] /** [shuffle xs]
=======
external setUnsafe: (array('a), int, 'a) => unit = "%array_unsafe_set";

/** [shuffleInPlace arr] randomly re-orders the items in [arr] */

let shuffleInPlace: array('a) => unit;

/** [shuffle xs]
>>>>>>> DCE
    @return a fresh array with items in original array randomly shuffled */

let shuffle: array('a) => array('a);

<<<<<<< HEAD
[@dead "reverseInPlace"] /** [reverseInPlace arr] reverses items in [arr] in place
=======
/** [reverseInPlace arr] reverses items in [arr] in place
>>>>>>> DCE

  @example {[
    let arr = [|10;11;12;13;14|];;
    let () = reverseInPlace arr;;
    arr = [|14;13;12;11;10|];;
  ]}
*/

let reverseInPlace: array('a) => unit;

<<<<<<< HEAD
[@dead "reverse"] /** [reverse arr]
=======
/** [reverse arr]
>>>>>>> DCE
    @return a fresh array with items in [arr] in reverse order

    @example {[
      reverse [|10;11;12;13;14|] = [|14;13;12;11;10|];;
    ]}
*/

let reverse: array('a) => array('a);

<<<<<<< HEAD
[@dead "makeUninitialized"] /**
=======
/**
>>>>>>> DCE
  [makeUninitialized n] creates an array of length [n] filled with the undefined value.
  You must specify the type of data that will eventually fill the array.

  @example {[
    let arr: string Js.undefined array = makeUninitialized 5;;
    getExn arr 0 = Js.undefined;;
  ]}
*/
[@bs.new]
external makeUninitialized: int => array(Js.undefined('a)) = "Array";

<<<<<<< HEAD
[@dead "makeUninitializedUnsafe"] /** [makeUninitializedUnsafe n]
=======
/** [makeUninitializedUnsafe n]
>>>>>>> DCE

    {b Unsafe}

    @example {[
    let arr = Belt.Array.makeUninitializedUnsafe 5;;
    let () = Js.log(Belt.Array.getExn arr 0);; (* undefined *)
    Belt.Array.setExn arr 0 "example";;
    let () = Js.log(Belt.Array.getExn arr 0 = "example");;
    ]}
*/
[@bs.new]
external makeUninitializedUnsafe: int => array('a) = "Array";

<<<<<<< HEAD
[@dead "make"] /** [make n e]
=======
/** [make n e]
>>>>>>> DCE
    return an array of size [n] filled  with value [e]
    @return an empty array when [n] is negative.
*/

let make: (int, 'a) => array('a);

<<<<<<< HEAD
[@dead "range"] /** [range start finish] create an inclusive array
=======
/** [range start finish] create an inclusive array
>>>>>>> DCE
    @example {[
      range 0 3 =  [|0;1;2;3|];;
      range 3 0 =  [||] ;;
      range 3 3 = [|3|];;
    ]}
*/

let range: (int, int) => array(int);

<<<<<<< HEAD
[@dead "rangeBy"] /** [range start finish] create an inclusive array
=======
/** [range start finish] create an inclusive array
>>>>>>> DCE
    @example {[
      range 0 3 =  [|0;1;2;3|];;
      range 3 0 =  [||] ;;
      range 3 3 = [|3|];;
    ]}
*/
/** [rangeBy start finish ~step]

    @return empty array when step is 0 or negative
    it also return empty array when [start > finish]

    @example {[
     rangeBy 0 10 ~step:3 = [|0;3;6;9|];;
     rangeBy 0 12 ~step:3 = [|0;3;6;9;12|];;
     rangeBy 33 0 ~step:1 =  [||];;
     rangeBy 33 0 ~step:(-1) = [||];;
     rangeBy 3 12 ~step:(-1) = [||];;
     rangeBy 3 3 ~step:0 = [||] ;;
     rangeBy 3 3 ~step:(1) = [|3|] ;;
   ]}
*/

let rangeBy: (int, int, ~step: int) => array(int);

<<<<<<< HEAD
[@dead "makeByU"] let makeByU: (int, (. int) => 'a) => array('a);
[@dead "makeBy"] /** [makeBy n f]
=======
let makeByU: (int, (. int) => 'a) => array('a);
/** [makeBy n f]
>>>>>>> DCE

    return an empty array when [n] is negative
    return an array of size [n] populated by [f i] start from [0] to [n - 1]

    @example {[
      makeBy 5 (fun i -> i) = [|0;1;2;3;4|];;
      makeBy 5 (fun i -> i * i) = [|0;1;4;9;16|]
    ]}
*/

let makeBy: (int, int => 'a) => array('a);

<<<<<<< HEAD
[@dead "makeByAndShuffleU"] let makeByAndShuffleU: (int, (. int) => 'a) => array('a);
[@dead "makeByAndShuffle"] /** [makeByAndShuffle n f]
=======
let makeByAndShuffleU: (int, (. int) => 'a) => array('a);
/** [makeByAndShuffle n f]
>>>>>>> DCE

    Equivalent to [shuffle (makeBy n f)]
*/

let makeByAndShuffle: (int, int => 'a) => array('a);

<<<<<<< HEAD
[@dead "zip"] /** [zip a b]
=======
/** [zip a b]
>>>>>>> DCE

    Create an array of pairs from corresponding elements of [a] and [b].
    Stop with the shorter array

    @example {[
      zip [|1;2|] [|3;4;5|] = [|(1, 3);(2, 4)|]
    ]}
 */

let zip: (array('a), array('b)) => array(('a, 'b));

<<<<<<< HEAD
[@dead "zipByU"] let zipByU: (array('a), array('b), (. 'a, 'b) => 'c) => array('c);
[@dead "zipBy"] /**
=======
let zipByU: (array('a), array('b), (. 'a, 'b) => 'c) => array('c);
/**
>>>>>>> DCE
    [zipBy xs ys f]

    Create an array by applying [f] to corresponding elements of [xs] and [ys]
    Stops with shorter array

    Equivalent to [map (zip xs ys) (fun (a,b) -> f a b) ]

    @example {[
      zipBy [|1;2;3|] [|4;5|] (fun a b -> 2 * a + b) = [|6;9|];;
    ]}
 */

let zipBy: (array('a), array('b), ('a, 'b) => 'c) => array('c);

<<<<<<< HEAD
[@dead "unzip"] /** [unzip a] takes an array of pairs and creates a pair of arrays. The first array contains all the first items of the pairs; the second array contains all the second items.
=======
/** [unzip a] takes an array of pairs and creates a pair of arrays. The first array contains all the first items of the pairs; the second array contains all the second items.
>>>>>>> DCE

    @example {[
      unzip [|(1,2) ; (3,4)|] = ([|1;3|], [|2;4|]);;
      unzip [|(1,2) ; (3,4) ; (5,6) ; (7,8)|] = ([|1;3;5;7|], [|2;4;6;8|]);;
    ]}
*/

let unzip: array(('a, 'b)) => (array('a), array('b));

<<<<<<< HEAD
[@dead "concat"] /** [concat xs ys]
=======
/** [concat xs ys]
>>>>>>> DCE

    @return a fresh array containing the
    concatenation of the arrays [v1] and [v2];so even if [v1] or [v2]
    is empty;it can not be shared

    @example {[
      concat [|1;2;3|] [|4;5|] = [|1;2;3;4;5|];;
      concat [| |] [|"a";"b";"c"|] = [|"a";"b";"c"|];;
    ]}
*/

let concat: (array('a), array('a)) => array('a);

<<<<<<< HEAD
[@dead "concatMany"] /**
=======
/**
>>>>>>> DCE
    [concatMany xss]

    @return a fresh array as the concatenation of [xss] (an array of arrays)

    @example {[
      concatMany [| [|1;2;3|]; [|4;5;6|]; [|7;8|] |] = [|1;2;3;4;5;6;7;8|];;
    ]}
*/

let concatMany: array(array('a)) => array('a);

<<<<<<< HEAD
[@dead "slice"] /** [slice xs offset len] creates a new array with the [len] elements of [xs] starting at [offset] for
=======
/** [slice xs offset len] creates a new array with the [len] elements of [xs] starting at [offset] for
>>>>>>> DCE

    [offset] can be negative;and is evaluated as [length xs - offset]
    [slice xs -1 1] means get the last element as a singleton array

    [slice xs (-len) len] will return a copy of the array

    if the array does not have enough data;[slice] extracts through
    the end of sequence.

    if [len] is negative;returns the empty array.

    @example {[
      slice [|10;11;12;13;14;15;16|] ~offset: 2 ~len: 3 = [|12;13;14|];;
      slice [|10;11;12;13;14;15;16|] ~offset: (-4) ~len: 3 = [|13;14;15|];;
      slice [|10;11;12;13;14;15;16|] ~offset:4  ~len:9 = [|14;15;16|];;
    ]}
*/

let slice: (array('a), ~offset: int, ~len: int) => array('a);

<<<<<<< HEAD
[@dead "sliceToEnd"] /** [sliceToEnd xs offset] creates a new array with the elements of [xs] starting at [offset]
=======
/** [sliceToEnd xs offset] creates a new array with the elements of [xs] starting at [offset]
>>>>>>> DCE

    [offset] can be negative;and is evaluated as [length xs - offset]
    [sliceToEnd xs -1] means get the last element as a singleton array

    [sliceToEnd xs 0] will return a copy of the array

    @example {[
      sliceToEnd [|10;11;12;13;14;15;16|] 2 = [|12;13;14;15;16|];;
      sliceToEnd [|10;11;12;13;14;15;16|] (-4) = [|13;14;15;16|];;
    ]}
*/

let sliceToEnd: (array('a), int) => array('a);

<<<<<<< HEAD
[@dead "copy"] /** [copy a]
=======
/** [copy a]
>>>>>>> DCE

    @return a copy of [a];that is;a fresh array
   containing the same elements as [a].
*/
[@bs.send]
external copy: (array('a), [@bs.as 0] _) => array('a) = "slice";

<<<<<<< HEAD
[@dead "fill"] /** [fill arr ~offset ~len x]
=======
/** [fill arr ~offset ~len x]
>>>>>>> DCE

    Modifies [arr] in place,
    storing [x] in elements number [offset] to [offset + len - 1].

    [offset] can be negative;and is evaluated as [length arr - offset]

    [fill arr ~offset:(-1) ~len:1] means fill the last element,
    if the array does not have enough data;[fill] will ignore it

    @example {[

      let arr = makeBy 5 (fun i -> i) ;;
      fill arr ~offset:2 ~len:2 9 ;;
      arr = [|0;1;9;9;4|];;
      fill arr ~offset:7 ~len:2 8;;
      arr = [|0;1;9;9;4|];;
    ]}
 */

let fill: (array('a), ~offset: int, ~len: int, 'a) => unit;

<<<<<<< HEAD
[@dead "blit"] /** [blit ~src:v1 ~srcOffset:o1 ~dst:v2 ~dstOffset:o2 ~len]
=======
/** [blit ~src:v1 ~srcOffset:o1 ~dst:v2 ~dstOffset:o2 ~len]
>>>>>>> DCE

    copies [len] elements
   from array [v1];starting at element number [o1];to array [v2],
   starting at element number [o2].

    It works correctly even if
    [v1] and [v2] are the same array;and the source and
    destination chunks overlap.

    [offset] can be negative;[-1] means [len - 1];if [len + offset]  is still
    negative;it will be set as 0

    For each of the examples;presume that [v1 = \[|10;11;12;13;14;15;16;17|\]] and
    [v2 = \[|20;21;22;23;24;25;26;27|\]]. The result shown is the content of the destination array.

    @example {[
      Belt.Array.blit ~src: v1 ~srcOffset: 4 ~dst: v2 ~dstOffset: 2 ~len: 3 |.
        [|20;21;14;15;16;25;26;27|]
      Belt.Array.blit ~src: v1 ~srcOffset: 4 ~dst: v1 ~dstOffset: 2 ~len: 3 |.
        [|10;11;14;15;16;15;16;17|]
      ]}

*/

let blit:
  (
    ~src: array('a),
    ~srcOffset: int,
    ~dst: array('a),
    ~dstOffset: int,
    ~len: int
  ) =>
  unit;

<<<<<<< HEAD
[@dead "blitUnsafe"] /**
=======
/**
>>>>>>> DCE
   {b Unsafe} blit without bounds checking
*/

let blitUnsafe:
  (
    ~src: array('a),
    ~srcOffset: int,
    ~dst: array('a),
    ~dstOffset: int,
    ~len: int
  ) =>
  unit;

<<<<<<< HEAD
[@dead "forEachU"] let forEachU: (array('a), (. 'a) => unit) => unit;
[@dead "forEach"] /** [forEach xs f]
=======
let forEachU: (array('a), (. 'a) => unit) => unit;
/** [forEach xs f]
>>>>>>> DCE

    Call [f] on each element of [xs] from the beginning to end. [f] returns [unit];so no
    new array is created. Use [forEach] when you are primarily concerned with repetitively
    creating side effects.

    @example {[
      forEach [|"a";"b";"c"|] (fun x -> Js.log("Item: " ^ x));;
      (*  prints:
        Item: a
        Item: b
        Item: c
      *)

      let total = ref 0;;
      forEach [|1;2;3;4|] (fun x -> total := !total + x);;
      !total  = 1 + 2 + 3 + 4;;

    ]}
*/

let forEach: (array('a), 'a => unit) => unit;

<<<<<<< HEAD
[@dead "mapU"] let mapU: (array('a), (. 'a) => 'b) => array('b);
[@dead "map"] /** [map xs f ]
=======
let mapU: (array('a), (. 'a) => 'b) => array('b);
/** [map xs f ]
>>>>>>> DCE

    @return a new array by calling [f] for each element of [xs] from
    the beginning to end

    @example {[
     map [|1;2|] (fun x-> x + 1) = [|3;4|]
   ]}

*/

let map: (array('a), 'a => 'b) => array('b);

<<<<<<< HEAD
[@dead "getByU"] let getByU: (array('a), (. 'a) => bool) => option('a);
[@dead "getBy"] /** [getBy xs p] returns [Some value] for the first value in [xs] that satisifies the predicate function [p]; returns [None] if no element satisifies the function.
=======
let getByU: (array('a), (. 'a) => bool) => option('a);
/** [getBy xs p] returns [Some value] for the first value in [xs] that satisifies the predicate function [p]; returns [None] if no element satisifies the function.
>>>>>>> DCE

  @example {[
      getBy [|1;4;3;2|] (fun x -> x mod 2 = 0) = Some 4
      getBy [|15;13;11|] (fun x -> x mod 2 = 0) = None
    ]}
*/

let getBy: (array('a), 'a => bool) => option('a);

<<<<<<< HEAD
[@dead "getIndexByU"] let getIndexByU: (array('a), (. 'a) => bool) => option(int);
[@dead "getIndexBy"] /** [getIndexBy xs p] returns [Some index] for the first value in [xs] that satisifies the predicate function [p]; returns [None] if no element satisifies the function.
=======
let getIndexByU: (array('a), (. 'a) => bool) => option(int);
/** [getIndexBy xs p] returns [Some index] for the first value in [xs] that satisifies the predicate function [p]; returns [None] if no element satisifies the function.
>>>>>>> DCE

  @example {[
      getIndexBy [|1;4;3;2|] (fun x -> x mod 2 = 0) = Some 1
      getIndexBy [|15;13;11|] (fun x -> x mod 2 = 0) = None
    ]}
*/

let getIndexBy: (array('a), 'a => bool) => option(int);

<<<<<<< HEAD
[@dead "keepU"] let keepU: (array('a), (. 'a) => bool) => array('a);
[@dead "keep"] /** [keep xs p ]
=======
let keepU: (array('a), (. 'a) => bool) => array('a);
/** [keep xs p ]
>>>>>>> DCE
    @return a new array that keep all elements satisfy [p]

    @example {[
      keep [|1;2;3|] (fun x -> x mod  2 = 0) = [|2|]
    ]}
*/

let keep: (array('a), 'a => bool) => array('a);

<<<<<<< HEAD
[@dead "keepWithIndexU"] let keepWithIndexU: (array('a), (. 'a, int) => bool) => array('a);
[@dead "keepWithIndex"] /** [keepWithIndex xs p ]
=======
let keepWithIndexU: (array('a), (. 'a, int) => bool) => array('a);
/** [keepWithIndex xs p ]
>>>>>>> DCE
    @return a new array that keep all elements satisfy [p]

    @example {[
      keepWithIndex [|1;2;3|] (fun _x i -> i = 1) = [|2|]
    ]}
*/

let keepWithIndex: (array('a), ('a, int) => bool) => array('a);

<<<<<<< HEAD
[@dead "keepMapU"] let keepMapU: (array('a), (. 'a) => option('b)) => array('b);
[@dead "keepMap"] /** [keepMap xs p]
=======
let keepMapU: (array('a), (. 'a) => option('b)) => array('b);
/** [keepMap xs p]
>>>>>>> DCE
    @return a new array that keep all elements that return a non-None applied [p]

    @example {[
      keepMap [|1;2;3|] (fun x -> if x mod 2 then Some x else None)
      = [| 2 |]
    ]}
*/

let keepMap: (array('a), 'a => option('b)) => array('b);

<<<<<<< HEAD
[@dead "forEachWithIndexU"] let forEachWithIndexU: (array('a), (. int, 'a) => unit) => unit;
[@dead "forEachWithIndex"] /** [forEachWithIndex xs f]
=======
let forEachWithIndexU: (array('a), (. int, 'a) => unit) => unit;
/** [forEachWithIndex xs f]
>>>>>>> DCE

    The same as {!forEach};except that [f] is supplied two arguments:
    the index starting from 0 and the element from [xs]

    @example {[

      forEach [|"a";"b";"c"|] (fun i x -> Js.log("Item " ^ (string_of_int i) ^ " is " ^ x));;
      (*  prints:
        Item 0 is a
        Item 1 is b
        Item 2 is cc
      *)

      let total = ref 0 ;;
      forEachWithIndex [|10;11;12;13|] (fun i x -> total := !total + x + i);;
      !total  = 0 + 10 + 1 +  11 + 2 + 12 + 3 + 13;;
    ]}

*/

let forEachWithIndex: (array('a), (int, 'a) => unit) => unit;

<<<<<<< HEAD
[@dead "mapWithIndexU"] let mapWithIndexU: (array('a), (. int, 'a) => 'b) => array('b);
[@dead "mapWithIndex"] /** [mapWithIndex xs f ]
=======
let mapWithIndexU: (array('a), (. int, 'a) => 'b) => array('b);
/** [mapWithIndex xs f ]
>>>>>>> DCE

    [mapWithIndex xs f] applies [f] to each element of [xs]. Function [f] takes two arguments:
  the index starting from 0 and the element from [xs].

    @example {[
      mapWithIndex [|1;2;3|] (fun i x -> i + x) =
      [|0 + 1; 1 + 2; 2 + 3|]
    ]}
*/

let mapWithIndex: (array('a), (int, 'a) => 'b) => array('b);

let partitionU: (array('a), (. 'a) => bool) => (array('a), array('a));
/** [partition f a] split array into tuple of two arrays based on predicate f; first of tuple where predicate cause true, second where predicate cause false

    @example {[
      partition [|1;2;3;4;5|] (fun x -> x mod 2 = 0  ) = ([|2;4|], [|1;2;3|]);;
      partition [|1;2;3;4;5|] (fun x -> x mod 2 <> 0 ) = ([|1;2;3|], [|2;4|]);;
    ]}
*/

let partition: (array('a), 'a => bool) => (array('a), array('a));

<<<<<<< HEAD
[@dead "reduceU"] let reduceU: (array('b), 'a, (. 'a, 'b) => 'a) => 'a;
[@dead "reduce"] /** [reduce xs init f]
=======
let reduceU: (array('b), 'a, (. 'a, 'b) => 'a) => 'a;
/** [reduce xs init f]
>>>>>>> DCE

    Applies [f] to each element of [xs] from beginning to end.  Function [f] has two parameters: the item
    from the list and an “accumulator”;which starts with a value of [init]. [reduce]
    returns the final value of the accumulator.

    @example {[
      reduce [|2;3;4|] 1 (+) = 10;;
      reduce [|"a";"b";"c";"d"|] "" (^) = "abcd";;
    ]}

*/

let reduce: (array('b), 'a, ('a, 'b) => 'a) => 'a;

<<<<<<< HEAD
[@dead "reduceReverseU"] let reduceReverseU: (array('b), 'a, (. 'a, 'b) => 'a) => 'a;
[@dead "reduceReverse"] /** [reduceReverse xs init f]
=======
let reduceReverseU: (array('b), 'a, (. 'a, 'b) => 'a) => 'a;
/** [reduceReverse xs init f]
>>>>>>> DCE

    Works like {!reduce};except that function [f] is applied to each item of [xs] from the last
    back to the first.

    @example {[
      reduceReverse [|"a";"b";"c";"d"|] "" (^) = "dcba";;
    ]}
*/

let reduceReverse: (array('b), 'a, ('a, 'b) => 'a) => 'a;

<<<<<<< HEAD
[@dead "reduceReverse2U"] let reduceReverse2U: (array('a), array('b), 'c, (. 'c, 'a, 'b) => 'c) => 'c;
[@dead "reduceReverse2"] /**
=======
let reduceReverse2U: (array('a), array('b), 'c, (. 'c, 'a, 'b) => 'c) => 'c;
/**
>>>>>>> DCE
   [reduceReverse2 xs ys init f]
   Reduces two arrays [xs] and [ys];taking items starting at [min (length xs) (length ys)]
   down to and including zero.

   @example {[
     reduceReverse2 [|1;2;3|] [|1;2|] 0 (fun acc x y -> acc + x + y) = 6
   ]}
*/

let reduceReverse2: (array('a), array('b), 'c, ('c, 'a, 'b) => 'c) => 'c;

<<<<<<< HEAD
[@dead "reduceWithIndexU"] let reduceWithIndexU: (array('a), 'b, (. 'b, 'a, int) => 'b) => 'b;
[@dead "reduceWithIndex"] /** [reduceWithIndex xs f]
=======
let reduceWithIndexU: (array('a), 'b, (. 'b, 'a, int) => 'b) => 'b;
/** [reduceWithIndex xs f]
>>>>>>> DCE

    Applies [f] to each element of [xs] from beginning to end. Function [f] has three parameters: the item
    from the array and an “accumulator”, which starts with a value of [init] and the index of each element. [reduceWithIndex]
    returns the final value of the accumulator.

    @example {[
      reduceWithIndex [|1;2;3;4|] 0 (fun acc x i -> acc + x + i) = 16;
    ]}
*/

let reduceWithIndex: (array('a), 'b, ('b, 'a, int) => 'b) => 'b;

<<<<<<< HEAD
[@dead "someU"] let someU: (array('a), (. 'a) => bool) => bool;
[@dead "some"] /** [some xs p]
=======
let someU: (array('a), (. 'a) => bool) => bool;
/** [some xs p]
>>>>>>> DCE

    @return true if at least one of the elements in [xs] satifies [p];where [p] is a {i predicate}: a function taking
    an element and returning a [bool].

    @example {[
      some [|2; 3; 4|] (fun x -> x mod 2 = 1) = true;;
      some [|-1; -3; -5|] (fun x -> x > 0) = false;;
    ]}
*/

let some: (array('a), 'a => bool) => bool;

<<<<<<< HEAD
[@dead "everyU"] let everyU: (array('a), (. 'a) => bool) => bool;
[@dead "every"] /** [every xs p]
=======
let everyU: (array('a), (. 'a) => bool) => bool;
/** [every xs p]
>>>>>>> DCE

    @return true if all elements satisfy [p];where [p] is a {i predicate}: a function taking
    an element and returning a [bool].

    @example {[
      every [|1; 3; 5|] (fun x -> x mod 2 = 1) = true;;
      every [|1; -3; 5|] (fun x -> x > 0) = false;;
    ]}
*/

let every: (array('a), 'a => bool) => bool;

<<<<<<< HEAD
[@dead "every2U"] let every2U: (array('a), array('b), (. 'a, 'b) => bool) => bool;
[@dead "every2"] /** [every2 xs ys p] returns true if [p xi yi] is true for all pairs of elements
=======
let every2U: (array('a), array('b), (. 'a, 'b) => bool) => bool;
/** [every2 xs ys p] returns true if [p xi yi] is true for all pairs of elements
>>>>>>> DCE
  up to the shorter length (i.e. [min (length xs) (length ys)])
    @example {[
      every2 [|1;2;3|] [|0;1|] (>) = true;;
      every2 [||] [|1|] (fun  x y -> x > y) = true;;
      every2 [|2;3|] [|1|] (fun  x y -> x > y) = true;;
      every2 [|0;1|] [|5;0|] (fun x y -> x > y) = false;
    ]}
*/

let every2: (array('a), array('b), ('a, 'b) => bool) => bool;

<<<<<<< HEAD
[@dead "some2U"] let some2U: (array('a), array('b), (. 'a, 'b) => bool) => bool;
[@dead "some2"] /** [some2 xs ys p] returns true if [p xi yi] is true for any pair of elements
=======
let some2U: (array('a), array('b), (. 'a, 'b) => bool) => bool;
/** [some2 xs ys p] returns true if [p xi yi] is true for any pair of elements
>>>>>>> DCE
  up to the shorter length (i.e. [min (length xs) (length ys)])

    @example {[
      some2 [|0;2|] [|1;0;3|] (>) = true ;;
      (some2 [||] [|1|] (fun   x y -> x > y)) =  false;;
      (some2 [|2;3|] [|1;4|] (fun   x y -> x > y)) = true;;
    ]}
*/

let some2: (array('a), array('b), ('a, 'b) => bool) => bool;

<<<<<<< HEAD
[@dead "cmpU"] let cmpU: (array('a), array('a), (. 'a, 'a) => int) => int;
[@dead "cmp"] /** [cmp xs ys f]
=======
let cmpU: (array('a), array('a), (. 'a, 'a) => int) => int;
/** [cmp xs ys f]
>>>>>>> DCE

    - Compared by length if [length xs <> length ys];returning -1 if[length xs < length ys] or 1 if [length xs > length ys]
    - Otherwise compare one by one [f x y]. [f] returns
      - a negative number if [x] is “less than” [y]
      - zero if [x] is “equal to” [y]
      - a positive number if [x] is “greater than” [y]
    - The comparison returns the first non-zero result of [f];or zero if [f] returns zero for all [x] and [y].

    @example {[
      cmp [|1; 3; 5|] [|1; 4; 2|] (fun a b -> compare a b) = -1;;
      cmp [|1; 3; 5|] [|1; 2; 3|] (fun a b -> compare a b) = 1;;
      cmp [|1; 3; 5|] [|1; 3; 5|] (fun a b -> compare a b) = 0;;
    ]}
*/

let cmp: (array('a), array('a), ('a, 'a) => int) => int;

<<<<<<< HEAD
[@dead "eqU"] let eqU: (array('a), array('a), (. 'a, 'a) => bool) => bool;
[@dead "eq"] /** [eq xs ys]
=======
let eqU: (array('a), array('a), (. 'a, 'a) => bool) => bool;
/** [eq xs ys]
>>>>>>> DCE

    - return false if length is not the same
    - otherwise compare items one by one using [f xi yi];and return true if all results are true;false otherwise

    @example {[
      eq [|1; 2; 3|] [|-1; -2; -3|] (fun a b -> abs a = abs b) = true
    ]}
*/

let eq: (array('a), array('a), ('a, 'a) => bool) => bool;

<<<<<<< HEAD
[@dead "truncateToLengthUnsafe"] /** {b Unsafe}
=======
/** {b Unsafe}
>>>>>>> DCE
  [truncateToLengthUnsafe xs n] sets length of array [xs] to [n].

  If [n] is greater than the length of [xs];the extra elements are set to [Js.Null_undefined.null]

  If [n] is less than zero;raises a [RangeError].

  @example {[
    let arr = [|"ant";"bee";"cat";"dog";"elk"|];;
    let () = truncateToLengthUnsafe arr 3;;
    arr = [|"ant";"bee";"cat"|];;
  ]}

*/
[@bs.set]
<<<<<<< HEAD
external truncateToLengthUnsafe: (array('a), int) => unit = "length";
=======
external truncateToLengthUnsafe: (array('a), int) => unit = "length";
>>>>>>> DCE
