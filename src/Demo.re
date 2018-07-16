open Belt;
let testSmall = () => {
  let small = Js.Json.parseExn({| [{"name":null} ] |});

  let styp = TypeCheck.fromJson(small);
  Js.log(styp |. Styp.stypToJson |. Js.Json.stringify);
};

let logDiff = diff => Js.log(diff |. Diff.toJson |. Js.Json.stringify);

let testSmallDiff = (~mode=TypeCheck.defaultMode, n) => {
  let examples = [|
    ({| {"x": "hello"} |}, {| {"x": null, "y":0} |}),
    ({| [ "hell", 0, "world"] |}, {| [ "hell", "o", "world"] |}),
    (
      {| ["h", "e", "l", "l", "o", "w", "o", "r", "l", "d"] |},
      {| ["h", "e", "l", "l", 0, "w", "o", "r", "l", "d"] |},
    ),
    ("[null,2,3,4]", "[3]"),
    ({| [{"x": {"y" : "hello"}}] |}, {| [{"x": {"z" : "hello"}}] |}),
    ("null", "3"),
    ({| [{"a":3},{"b":3}] |}, {| [] |}),
    ({| [null,{"b":3}] |}, {| [] |}),
    ({| [3, "hello", true, 4] |}, {| [1,2,3] |}),
    ({| 3 |}, {| "abc" |}),
    (
      {|[{"x": ["p","s"]}]|},
      {|[{"x":["p","b"]},
         {"x":["p","s"]},
         {"x": ["p","s"]}]|},
    ),
  |];
  let styp1 =
    examples
    |. Array.getExn(n)
    |. fst
    |. Js.Json.parseExn
    |. TypeCheck.fromJson(~mode);
  let styp2 =
    examples
    |. Array.getExn(n)
    |. snd
    |. Js.Json.parseExn
    |. TypeCheck.fromJson(~mode);
  let diff = Diff.diffCheck(styp1, styp2);
  logDiff(diff);
  diff;
};

let testSamples = (~mode=TypeCheck.defaultMode, ()) => {
  let styps =
    [{| {"x": 1, "y":"hello"} |}, {| {"x": 2} |}, {| {"x": 3, "y":null} |}]
    |. List.map(Js.Json.parseExn)
    |. List.map(TypeCheck.fromJson(~mode));
  Samples.(styps |. fromList |. getAllDiffs);
};

/* let testBigDiff = () => {
     let styp1 =
       Query.reasonBronzeThread |. Js.Json.parseExn |. TypeCheck.fromJson;
     let styp2 =
       Query.reasonPlatinumThread |. Js.Json.parseExn |. TypeCheck.fromJson;
     let diff = Diff.diffCheck(styp1, styp2);
     logDiff(diff);
     diff;
   }; */

let testDynamicallyTypedJson = () => {
  open! DynTypedJson;

  let json1 = Js.Json.parseExn({| null |});
  let json2 = Js.Json.parseExn({| {"b":3} |});

  let x = ref(json1);
  Js.log2("x:", x.json);

  x := json2;
  Js.log2("x:", x.json);

  if (x != null) {
    let x1 = x @ "b";
    Js.log2("x1:", x1.json);
  };
};

let testSerializer = (o, testName) => {
  let s = Serialize.toString(o);
  let o1 = Serialize.fromString(s);
  if (o != o1) {
    Js.log("Serialize " ++ testName);
    Js.log2("o:", o);
    Js.log2("s:", s);
    Js.log2("o1:", o1);
    assert(false);
  };
  o;
};

let res = [testSmallDiff(0)];
/* let res = [testSmallDiff(~mode=TypeCheck.singletonMode, 2)]; */
/* let res = [testBigDiff()]; */
/* let res = testSamples(); */
let test = () => res |. testSerializer("diff");

/* fails: serialization of functions
   let _ = (x => x + 1) |. testSerializer("function");
   */

/* fails: serialization of cyclic values
   type cyclic =
     | C(cyclic);
   let rec cyclic = C(cyclic);
   let _ = cyclic |. testSerializer("cyclic");
   */

testDynamicallyTypedJson();