/* Copyright (C) 2017 Authors of BuckleScript
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * In addition to the permissions granted to you by the LGPL, you may combine
 * or link a "work that uses the Library" with a publicly distributed version
 * of this file to produce a combined library or application, then distribute
 * that combined work under the terms of your choosing, with no requirement
 * to comply with the obligations normally placed on you by section 4 of the
 * LGPL version 3 (or the corresponding section of a later version of the LGPL
 * should you choose to use a later version).
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

/** {!Belt.List}

    Utilities for List data type.

    This module is compatible with original ocaml stdlib.
    In general, all functions comes with the original stdlib also
    applies to this collection, however, this module provides  faster
    and stack safer utilities

*/;

/** ['a t] is compatible with built-in [list] type */

type t('a) = list('a);

/** [length xs]

    @return the length of the list [xs]
*/

let length: t('a) => int;

/** {b See} {!length} */

let size: t('a) => int;

/**
  [head xs] returns [None] if [xs] is the empty list, otherwise it returns [Some value] where [value] is the first
  element in the list.
   @example {[
     head [] = None ;;
     head [1;2;3] = Some 1 ;;
   ]}
*/

let head: t('a) => option('a);

/**
  [head xs] returns [None] if [xs] is the empty list, otherwise it returns [Some value] where [value] is the first
  element in the list.
   @example {[
     head [] = None ;;
     head [1;2;3] = Some 1 ;;
   ]}
*/
/** [headExn xs]

    {b See} {!head}

    {b raise} an exception if [xs] is empty

*/

let headExn: t('a) => 'a;

/**  [tail xs] returns [None] if [xs] is empty;
  otherwise it returns [Some xs2] where [xs2] is everything except the first element of [xs];

  @example{[

      tail [] = None;;
      tail [1;2;3;4] = Some [2;3;4];;
    ]}
*/

let tail: t('a) => option(t('a));

/** [tailExn xs]

    {b See} {!tail}

    {b raise} an exception if [xs] is empty
*/

let tailExn: t('a) => t('a);

/**
  [add xs y] adds [y] to the beginning of list [xs]

   @example{[
     add [1] 3 = [3;1];;
   ]}
*/

let add: (t('a), 'a) => t('a);

/**
  [add xs y] adds [y] to the beginning of list [xs]

   @example{[
     add [1] 3 = [3;1];;
   ]}
*/
/** [get xs n]

    return the nth element in [xs],
    or [None] if [n] is larger than the length

    @example {[
      get [0;3;32] 2 = Some 32 ;;
      get [0;3;32] 3 = None;;
    ]}
 */

let get: (t('a), int) => option('a);

/** [getExn xs n]

    {b See} {!get}

    {b raise} an exception if [n] is larger than the length
*/

let getExn: (t('a), int) => 'a;

/**  [make n v]

    - return a list of length [n] with each element filled with value [v]
    - return the empty list if [n] is negative

     @example {[
       make 3 1 =  [1;1;1]
     ]}
*/

let make: (int, 'a) => t('a);

let makeByU: (int, (. int) => 'a) => t('a);
/** [makeBy n f]

    - return a list of length [n] with element [i] initialized with [f i]
    - return the empty list if [n] is negative

    @example {[
      makeBy 5 (fun i -> i) = [0;1;2;3;4];;
      makeBy 5 (fun i -> i * i) = [0;1;4;9;16];;
    ]}
*/

let makeBy: (int, int => 'a) => t('a);

/** [shuffle xs]
   @return a new list in random order
*/

let shuffle: t('a) => t('a);

/** [drop xs n]

    return the list obtained by dropping the first [n] elements,
    or [None] if [xs] has fewer than [n] elements

    @example {[
      drop [1;2;3] 2 = Some [3];;
      drop [1;2;3] 3 = Some [];;
      drop [1;2;3] 4 = None;;
    ]}
*/

let drop: (t('a), int) => option(t('a));

/** [take xs n]

    return a list with the first [n] elements from [xs],
    or [None] if [xs] has fewer than [n] elements

    @example {[
      take [1;2;3] 1 = Some [1];;
      take [1;2;3] 2 = Some [1;2];;
      take [1;2;3] 4 = None;;
    ]}
*/

let take: (t('a), int) => option(t('a));

/**
    [splitAt xs n]
    split the list [xs] at position [n]
    return None when the length of [xs] is less than [n]

   @example{[
     splitAt [0;1;2;3;4] 2 = Some ([0;1], [2;3;4])
   ]}
*/

let splitAt: (t('a), int) => option((list('a), list('a)));

/**
    [concat xs ys]

    @return the list obtained by adding [ys] after [xs]

   @example {[
     concat [1;2;3] [4;5] = [1;2;3;4;5]
   ]}
*/

let concat: (t('a), t('a)) => t('a);

/**
    [concatMany a]
    return the list obtained by concatenating in order all the lists in array [a]

   @example {[
     concatMany [| [1;2;3] ; []; [3]; [4] |] = [1;2;3;3;4]
   ]}
*/

let concatMany: array(t('a)) => t('a);

/**
   [reverseConcat xs ys] is  equivalent to [concat (reverse xs) ys]
   @example {[
     reverseConcat [1;2] [3;4] = [2;1;3;4]
   ]}
*/

let reverseConcat: (t('a), t('a)) => t('a);

/**
    [flatten ls]
    return the list obtained by concatenating in order all the lists in list [ls]

   @example {[
     flatten [ [1;2;3] ; []; [3]; [4] ] = [1;2;3;3;4]
   ]}
*/

let flatten: t(t('a)) => t('a);

let mapU: (t('a), (. 'a) => 'b) => t('b);
/**
    [map xs f]

    return the list obtained by applying [f] to each element of [xs]

   @example {[
     map [1;2] (fun x-> x + 1) = [3;4]
   ]}
*/

let map: (t('a), 'a => 'b) => t('b);

/** [zip xs ys]

    @return a list of pairs from the two lists
    with the length of the shorter list

    @example {[
      zip [1;2] [3;4;5] = [(1,3); (2,4)]
    ]}
*/

let zip: (t('a), t('b)) => t(('a, 'b));

let zipByU: (t('a), t('b), (. 'a, 'b) => 'c) => t('c);
/** [zipBy xs ys f]

    {b See} {!zip}

    Equivalent to [zip xs ys |> List.map (fun (x,y) -> f x y)]

    @example {[
      zipBy [1;2;3] [4;5] (fun a b -> 2 * a + b) = [6;9];;
    ]}

*/

let zipBy: (t('a), t('b), ('a, 'b) => 'c) => t('c);

let mapWithIndexU: (t('a), (. int, 'a) => 'b) => t('b);
/** [mapWithIndex xs f] applies [f] to each element of [xs]. Function [f] takes two arguments:
  the index starting from 0 and the element from [xs].

    @example {[
      mapWithIndex [1;2;3] (fun i x -> i + x) =
      [0 + 1; 1 + 2; 2 + 3 ]
    ]}
*/

let mapWithIndex: (t('a), (int, 'a) => 'b) => t('b);

/** [fromArray arr] converts the given array to a list

  @example {[
      fromArray [|1;2;3|]  = [1;2;3]
    ]}
*/

let fromArray: array('a) => t('a);

/** [toArray xs] converts the given list to an array
  @example {[
      toArray [1;2;3] = [|1;2;3|]
    ]}
*/

let toArray: t('a) => array('a);

/* type json = Js_json.t  */

/* val toJson : 'a t -> ('a -> json  [@bs]) -> json */
/* val fromJson : json -> (json -> 'a [@bs]) -> 'a t  */

/** [reverse xs] returns a new list whose elements are those of [xs] in reverse order.
  @example {[
      reverse [1;2;3] = [3;2;1]
    ]}
*/

let reverse: t('a) => t('a);

let mapReverseU: (t('a), (. 'a) => 'b) => t('b);
/** [mapReverse xs f]

    Equivalent to [reverse (map xs f)]

    @example {[
      mapReverse [3;4;5] (fun x -> x * x) = [25;16;9];;
    ]}
*/

let mapReverse: (t('a), 'a => 'b) => t('b);

let forEachU: (t('a), (. 'a) => 'b) => unit;
/** [forEach xs f ]
    Call [f] on each element of [xs] from the beginning to end. [f] returns [unit], so no
    new array is created. Use [foreach] when you are primarily concerned with repetitively
    creating side effects.

    @example {[
      forEach ["a";"b";"c"] (fun x -> Js.log("Item: " ^ x));;
      (*  prints:
        Item: a
        Item: b
        Item: c
      *)

      let us = ref 0;;
      forEach [1;2;3;4] (fun x -> us := !us + x);;
      !us  = 1 + 2 + 3 + 4;;
    ]}
*/

let forEach: (t('a), 'a => 'b) => unit;

let forEachWithIndexU: (t('a), (. int, 'a) => 'b) => unit;
/** [forEachWithIndex xs f]

    @example {[

      forEach ["a";"b";"c"] (fun i x -> Js.log("Item " ^ (string_of_int i) ^ " is " ^ x));;
      (*  prints:
        Item 0 is a
        Item 1 is b
        Item 2 is cc
      *)

      let total = ref 0 ;;
      forEachWithIndex [10;11;12;13] (fun i x -> total := !total + x + i);;
      !total  = 0 + 10 + 1 +  11 + 2 + 12 + 3 + 13;;
    ]}
*/

let forEachWithIndex: (t('a), (int, 'a) => 'b) => unit;

let reduceU: (t('a), 'b, (. 'b, 'a) => 'b) => 'b;
/** [reduce xs f]

    Applies [f] to each element of [xs] from beginning to end.  Function [f] has two parameters: the item
    from the list and an “accumulator”, which starts with a value of [init]. [reduce]
    returns the final value of the accumulator.

    @example {[
      reduce [1;2;3;4] 0 (+) = 10;;
      reduce [1;2;3;4] 10 (-) = 0;;
      reduce [1;2;3;4] [] add = [4;3;2;1];
    ]}
*/

let reduce: (t('a), 'b, ('b, 'a) => 'b) => 'b;

let reduceWithIndexU: (t('a), 'b, (. 'b, 'a, int) => 'b) => 'b;
/** [reduceWithIndex xs f]

    Applies [f] to each element of [xs] from beginning to end. Function [f] has three parameters: the item
    from the list and an “accumulator”, which starts with a value of [init] and the index of each element. [reduceWithIndex]
    returns the final value of the accumulator.

    @example {[
      reduceWithIndex [1;2;3;4] 0 (fun acc x i -> acc + x + i) = 16;;
    ]}
*/

let reduceWithIndex: (t('a), 'b, ('b, 'a, int) => 'b) => 'b;

let reduceReverseU: (t('a), 'b, (. 'b, 'a) => 'b) => 'b;
/** [reduceReverse xs f]

    Works like {!reduce}, except that function [f] is applied to each item of [xs] from the last
    back to the first.

    @example {[
      reduceReverse [1;2;3;4] 0 (+) = 10;;
      reduceReverse [1;2;3;4] 10 (-) = 0;;
      reduceReverse [1;2;3;4] [] add = [1;2;3;4];;
    ]}
*/

let reduceReverse: (t('a), 'b, ('b, 'a) => 'b) => 'b;

let mapReverse2U: (t('a), t('b), (. 'a, 'b) => 'c) => t('c);
/** [mapReverse2 xs ys f]

    equivalent to [reverse (zipBy xs ys f)]

    @example {[
      mapReverse2 [1;2;3] [1;2] (+) = [4;2]
    ]}
*/

let mapReverse2: (t('a), t('b), ('a, 'b) => 'c) => t('c);

let forEach2U: (t('a), t('b), (. 'a, 'b) => 'c) => unit;
/** [forEach2 xs ys f] stop with the shorter list
*/

let forEach2: (t('a), t('b), ('a, 'b) => 'c) => unit;

let reduce2U: (t('b), t('c), 'a, (. 'a, 'b, 'c) => 'a) => 'a;
/** [reduce2 xs ys init f ]

    Applies [f] to each element of [xs] and [ys] from beginning to end. Stops with the shorter list.
    Function [f] has three parameters: an “accumulator” which starts with a value of [init],
    an item from [xs], and an item from [ys]. [reduce2] returns the final value of the accumulator.

    @example {[
      reduce2 [1;2;3] [4;5] 0 (fun acc x y -> acc + x * x + y) =  0 + (1 * 1 + 4) + (2 * 2 + 5);;
      reduce2 [1;2;3] [4;5] [] (fun acc x y -> add acc (x + y) = [2 +5;1 + 4 ];; (*add appends at end *)
    ]}
*/

let reduce2: (t('b), t('c), 'a, ('a, 'b, 'c) => 'a) => 'a;

let reduceReverse2U: (t('a), t('b), 'c, (. 'c, 'a, 'b) => 'c) => 'c;
/**
   [reduceReverse2 xs ys init f ]

    Applies [f] to each element of [xs] and [ys] from end to beginning. Stops with the shorter list.
    Function [f] has three parameters: an “accumulator” which starts with a value of [init],
    an item from [xs], and an item from [ys]. [reduce2] returns the final value of the accumulator.

    @example {[
      reduceReverse2 [1;2;3] [4;5] 0 (fun acc x y -> acc + x * x + y) =  0 + (1 * 1 + 4) + (2 * 2 + 5);;
      reduceReverse2 [1;2;3] [4;5] [] (fun acc x y -> add acc (x + y) = [1 + 4;2 + 5];; (*add appends at end *)
    ]}*/

let reduceReverse2: (t('a), t('b), 'c, ('c, 'a, 'b) => 'c) => 'c;

let everyU: (t('a), (. 'a) => bool) => bool;
/** [every xs p]

    @return true if all elements satisfy [p], where [p] is a {i predicate}: a function taking
    an element and returning a [bool].

    @example {[
      every [] (fun x -> x mod 2 = 0) = true;;
      every [2;4;6] (fun x -> x mod 2 = 0 ) = true;;
      every [1;-3;5] (fun x -> x > 0) = false;;
    ]}
*/

let every: (t('a), 'a => bool) => bool;

let someU: (t('a), (. 'a) => bool) => bool;
/** [some xs p]
    @return true if at least one of the elements in [xs] satifies [p], where [p] is a {i predicate}: a function taking
    an element and returning a [bool].

    @example {[
      some [] (fun x -> x mod 2 = 0) = false ;;
      some [1;2;4] (fun x -> x mod 2 = 0) = true;;
      some [-1;-3;-5] (fun x -> x > 0) = false;;
    ]}
*/

let some: (t('a), 'a => bool) => bool;

let every2U: (t('a), t('b), (. 'a, 'b) => bool) => bool;
/** [every2 xs ys p] returns true if predicate [p xi yi] is true for all pairs of elements
  up to the shorter length (i.e. [min (length xs) (length ys)])
    @example {[
      every2 [1;2;3] [0;1] (>) = true;;
      every2 [] [1] (fun  x y -> x > y) = true;;
      every2 [2;3] [1] (fun  x y -> x > y) = true;;
      every2 [0;1] [5;0] (fun x y -> x > y) = false;
    ]}
*/

let every2: (t('a), t('b), ('a, 'b) => bool) => bool;

let some2U: (t('a), t('b), (. 'a, 'b) => bool) => bool;
/** [some2 xs ys p] returns true if [p xi yi] is true for any pair of elements
  up to the shorter length (i.e. [min (length xs) (length ys)])

    @example {[
      some2 [0;2] [1;0;3] (>) = true ;;
      some2 [] [1] (fun  x y -> x > y) =  false;;
      some2 [2;3] [1;4] (fun  x y -> x > y) = true;;
    ]}
*/

let some2: (t('a), t('b), ('a, 'b) => bool) => bool;

/** [cmpByLength l1 l2]

    Compare two lists solely by length. Returns -1 if [length l1] is less than [length l2],
    0 if [length l1] equals [length l2], and 1 if [length l1] is greater than [length l2].

    @example {[
    cmpByLength [1;2] [3;4;5;6] = -1;;
    cmpByLength [1;2;3] [4;5;6] = 0;;
    cmpByLength [1;2;3;4] [5;6] = 1;;
    ]}

*/

let cmpByLength: (t('a), t('a)) => int;

let cmpU: (t('a), t('a), (. 'a, 'a) => int) => int;
/**
    Compare elements one by one [f x y]. [f] returns
      - a negative number if [x] is “less than” [y]
      - zero if [x] is “equal to” [y]
      - a positive number if [x] is “greater than” [y]
    The comparison returns the first non-zero result of [f], or zero if [f] returns zero for all [x] and [y].
    If all items have compared equal, but [xs] is exhausted first, return -1. ([xs] is shorter)
    If all items have compared equal, but [ys] is exhausted first, return 1 ([xs] is longer)


    @example {[
      cmp [3] [3;7] (fun a b -> compare a b) = -1
      cmp [5;3] [5] (fun a b -> compare a b)  = 1
      cmp [|1; 3; 5|] [|1; 4; 2|] (fun a b -> compare a b) = -1;;
      cmp [|1; 3; 5|] [|1; 2; 3|] (fun a b -> compare a b) = 1;;
      cmp [|1; 3; 5|] [|1; 3; 5|] (fun a b -> compare a b) = 0;;
    ]}

   {b Attention}: The total ordering of List is different from Array,
   for Array, we compare the length first and, only if the lengths are equal, elements one by one.
   For lists, we just compare elements one by one
*/

let cmp: (t('a), t('a), ('a, 'a) => int) => int;

let eqU: (t('a), t('a), (. 'a, 'a) => bool) => bool;
/**
   [eq xs ys eqElem]
   check equality of [xs] and [ys] using [eqElem] for equality on elements, where [eqElem] is a function
   that returns true if items [x] and [y] meet some criterion for equality, false otherwise.
   [eq] false if length of [xs] and [ys] are not the same.

    @example {[
      eq [1;2;3] [1;2] (=) = false ;;
      eq [1;2] [1;2] (=) = true;;
      eq [1; 2; 3] [-1; -2; -3] (fun a b -> abs a = abs b) = true;;
    ]}
*/

let eq: (t('a), t('a), ('a, 'a) => bool) => bool;

let hasU: (t('a), 'b, (. 'a, 'b) => bool) => bool;
/**
    [has xs eqFcn] returns true if the list contains at least one element for which [eqFcn x] returns
    true
    @example {[
      has [1;2;3] 2 (=) = true;;
      has [1;2;3] 4 (=) = false;;
      has [-1;-2;-3] 2 (fun a b -> abs a = abs b) = true;;
    ]}
*/

let has: (t('a), 'b, ('a, 'b) => bool) => bool;

let getByU: (t('a), (. 'a) => bool) => option('a);
/** [getBy xs p] returns [Some value] for the first value in [xs] that satisifies the predicate function [p]; returns [None] if no element satisifies the function.

  @example {[
      getBy [1;4;3;2] (fun x -> x mod 2 = 0) = Some 4
      getBy [15;13;11] (fun x -> x mod 2 = 0) = None
    ]}
*/

let getBy: (t('a), 'a => bool) => option('a);

let keepU: (t('a), (. 'a) => bool) => t('a);
/** [keep  xs p] returns a list of all elements in [xs] which satisfy the predicate function [p]

    @example {[
      keep [1;2;3;4] (fun x -> x mod 2 = 0) =
      [2;4]
    ]}
*/

let keep: (t('a), 'a => bool) => t('a);

/** [filter  xs p] returns a list of all elements in [xs] which satisfy the predicate function [p]

    @example {[
      filter [1;2;3;4] (fun x -> x mod 2 = 0) =
      [2;4]
    ]}
*/

[@deprecated
  "This function will soon be deprecated. Please, use `List.keep` instead."
]
let filter: (t('a), 'a => bool) => t('a);

let keepWithIndexU: (t('a), (. 'a, int) => bool) => t('a);
/** [keepWithIndex xs p] returns a list of all elements in [xs] which satisfy the predicate function [p]

    @example {[
      keepWithIndex [1;2;3;4] (fun _x i -> i mod 2 = 0)
      =
      [1;3]
    ]}
*/

let keepWithIndex: (t('a), ('a, int) => bool) => t('a);

/** [filterWithIndex xs p] returns a list of all elements in [xs] which satisfy the predicate function [p]

    @example {[
      filterWithIndex [1;2;3;4] (fun _x i -> i mod 2 = 0)
      =
      [1;3]
    ]}
*/

[@deprecated
  "This function will soon be deprecated. Please, use `List.keepWithIndex` instead."
]
let filterWithIndex: (t('a), ('a, int) => bool) => t('a);

let keepMapU: (t('a), (. 'a) => option('b)) => t('b);
/** [keepMap xs f] applies [f] to each element of [xs]. If [f xi] returns [Some value], then [value] is kept in the resulting list; if [f xi] returns [None], the element is not retained in the result.

    @example {[
      keepMap [1;2;3;4] (fun x -> if x mod 2 = 0 then Some (-x ) else None)
      =
      [-2;-4]
    ]}
*/

let keepMap: (t('a), 'a => option('b)) => t('b);

/** [keepMap xs f] applies [f] to each element of [xs]. If [f xi] returns [Some value], then [value] is kept in the resulting list; if [f xi] returns [None], the element is not retained in the result.

    @example {[
      keepMap [1;2;3;4] (fun x -> if x mod 2 = 0 then Some (-x ) else None)
      =
      [-2;-4]
    ]}
*/

let partitionU: (t('a), (. 'a) => bool) => (t('a), t('a));
/** [partition xs p] creates a pair of lists; the first list consists of all elements of [xs] that satisfy the predicate function [p]; the second list consists of all elements of [xs] that do not satisfy [p]

    @example {[
      partition [1;2;3;4] (fun x -> x mod 2 = 0) =
      ([2;4], [1;3])
    ]}
*/

let partition: (t('a), 'a => bool) => (t('a), t('a));

/** [partition xs p] creates a pair of lists; the first list consists of all elements of [xs] that satisfy the predicate function [p]; the second list consists of all elements of [xs] that do not satisfy [p]

    @example {[
      partition [1;2;3;4] (fun x -> x mod 2 = 0) =
      ([2;4], [1;3])
    ]}
*/
/** [unzip xs] takes a list of pairs and creates a pair of lists. The first list contains all the first items of the pairs; the second list contains all the second items.

    @example {[
      unzip [(1,2) ; (3,4)] = ([1;3], [2;4]);;
      unzip [(1,2) ; (3,4) ; (5,6) ; (7,8)] = ([1;3;5;7], [2;4;6;8]);;
    ]}
*/

let unzip: t(('a, 'b)) => (t('a), t('b));

/** [unzip xs] takes a list of pairs and creates a pair of lists. The first list contains all the first items of the pairs; the second list contains all the second items.

    @example {[
      unzip [(1,2) ; (3,4)] = ([1;3], [2;4]);;
      unzip [(1,2) ; (3,4) ; (5,6) ; (7,8)] = ([1;3;5;7], [2;4;6;8]);;
    ]}
*/

let getAssocU: (t(('a, 'c)), 'b, (. 'a, 'b) => bool) => option('c);
/** [getAssoc xs k eq]

    return the second element of a pair in [xs] where the first element equals [x] as per the predicate
    function [eq], or [None] if not found
    @example {[
      getAssoc [ 1, "a"; 2, "b"; 3, "c"] 2 (=) = Some "b"
      getAssoc [9, "morning"; 15, "afternoon"; 22, "night"] 3 (fun a b -> a mod 12 = b mod 12) = Some "afternoon"
    ]}
*/

let getAssoc: (t(('a, 'c)), 'b, ('a, 'b) => bool) => option('c);

let hasAssocU: (t(('a, 'c)), 'b, (. 'a, 'b) => bool) => bool;
/** [hasAssoc xs k eq]
     return true if there is a pair in [xs] where the first element equals [k] as per the predicate
     funtion [eq]
    @example {[
      hasAssoc [1, "a"; 2, "b"; 3,"c"] 1 (=) = true;;
      hasAssoc [9, "morning"; 15, "afternoon"; 22, "night"] 3 (fun a b -> a mod 12 = b mod 12) = true;;
    ]}
*/

let hasAssoc: (t(('a, 'c)), 'b, ('a, 'b) => bool) => bool;

let removeAssocU: (t(('a, 'c)), 'b, (. 'a, 'b) => bool) => t(('a, 'c));
/** [removeAssoc xs k eq]
    Return a list after removing the first pair whose first value is [k] per the equality predicate [eq]; if not found, return a new list identical to [xs].
    @example {[
      removeAssoc [1,"a"; 2, "b"; 3, "c" ] 1 (=) =
        [2, "b"; 3, "c"]
      removeAssoc [1,"a"; 2, "b"; 3, "c" ] 99 (=) =
        [1, "a"; 2, "b"; 3, "c"]
    ]}
*/

let removeAssoc: (t(('a, 'c)), 'b, ('a, 'b) => bool) => t(('a, 'c));

let setAssocU: (t(('a, 'c)), 'a, 'c, (. 'a, 'a) => bool) => t(('a, 'c));
/** [setAssoc xs k v eq]
    if [k] exists in [xs] by satisfying the [eq] predicate, return a new list
    with the key and value replaced by the new [k] and [v]; otherwise, return a new
    list with the pair [k, v] added to the head of [xs].
    @example {[
      setAssoc [1,"a"; 2, "b"; 3, "c"] 2 "x" (=) =
      [1,"a"; 2, "x"; 3,"c"] ;;

      setAssoc [1,"a"; 3, "c"] 2 "b" (=) =
      [2,"b"; 1,"a"; 3, "c"]

      setAssoc [9, "morning"; 3, "morning?!"; 22, "night"] 15 "afternoon"
        (fun a b -> a mod 12 = b mod 12) = [9, "morning"; 15, "afternoon"; 22, "night"]
    ]}

    Note carefully the last example! Since [15 mod 12] equals [3 mod 12], {i both} the key and value are
    replaced in the list.
*/

let setAssoc: (t(('a, 'c)), 'a, 'c, ('a, 'a) => bool) => t(('a, 'c));

let sortU: (t('a), (. 'a, 'a) => int) => t('a);
/** [sort xs]
    Returns a sorted list.
    @example {[
      sort [5; 4; 9; 3; 7] (fun a b -> a - b) = [3; 4; 5; 7; 9]
    ]}
*/

let sort: (t('a), ('a, 'a) => int) => t('a);
