open! TypeCheck;

let testSmall = () => {
  /* let small = Js.Json.parseExn({| [{"x": "hello"}, {"x":null, "y":0}] |}); */
  /* let small = Js.Json.parseExn({| [1,2,3] |}); */
  /* let small = Js.Json.parseExn({| {"numbers":[1,2,3]} |}); */
  /* let small = Js.Json.parseExn({| [{"numbers":[1,2,3]},{"numbers":[4,5]} ] |}); */
  /* let small =
     Js.Json.parseExn(
       {| [ {"target": {"x": "abc" }}, {"target": {"x": "abc" }}, {"target":null} ] |},
     ); */
  let small = Js.Json.parseExn({| [{"name":null} ] |});

  let styp = fromJson(small);
  Js.log(styp |. PrettyPrint.styp);
};

let platinum =
  lazy (Query.reasonPlatinumThread |. Js.Json.parseExn |. fromJson);

let bronze = lazy (Query.reasonBronzeThread |. Js.Json.parseExn |. fromJson);

let testBronze = () => Js.log(Lazy.force(bronze) |. PrettyPrint.styp);
let testPlatinum = () => Js.log(Lazy.force(platinum) |. PrettyPrint.styp);

let testSmallAbduce = () => {
  /* let styp1 = {| [{"x": "hello"}] |} |. Js.Json.parseExn |. Styp.fromJson;
     let styp2 = {| [{"y": "hello"}] |} |. Js.Json.parseExn |. Styp.fromJson; */
  let styp1 = {| {"x": "hello"} |} |. Js.Json.parseExn |. fromJson;
  let styp2 = {| {"x": null} |} |. Js.Json.parseExn |. fromJson;
  let styp = Abduction.(styp2 -- styp1);
  Js.log(styp1 |. PrettyPrint.styp);
  Js.log(styp2 |. PrettyPrint.styp);
  Js.log(styp |. PrettyPrint.styp);
};

open Diff;

let logDiff = ({styp1, styp2, stypA1, stypA2, stypB}) => {
  Js.log2("styp1", styp1 |. PrettyPrint.styp);
  Js.log2("styp2", styp2 |. PrettyPrint.styp);
  Js.log2("stypB", stypB |. PrettyPrint.styp);
  Js.log2("stypA1", stypA1 |. PrettyPrint.styp);
  Js.log2("stypA2", stypA2 |. PrettyPrint.styp);
};

let testSmallDiff = n => {
  let examples = [|
    ({| {"x": "hello", "y":"world"} |}, {| {"x": null} |}),
    ({| [{"x": {"y" : "hello"}}] |}, {| [{"x": {"z" : "hello"}}] |}),
    ("null", "3"),
    ("[null,2]", "[3]"),
    ({| [{"a":3},{"b":3}] |}, {| [] |}),
  |];
  let styp1 = examples[n] |. fst |. Js.Json.parseExn |. fromJson;
  let styp2 = examples[n] |. snd |. Js.Json.parseExn |. fromJson;
  let diff = diffCheck(styp1, styp2);
  logDiff(diff);
  diff;
};

let testBigDiff = () => {
  let styp1 = Lazy.force(bronze);
  let styp2 = Lazy.force(platinum);
  let diff = diffCheck(styp1, styp2);
  logDiff(diff);
  diff;
};

let testDynamicallyTypedJson = () => {
  open! DynTypedJson;

  let json1 = Js.Json.parseExn({| null |});
  let json2 = Js.Json.parseExn({| {"b":3} |});

  let x = ref(json1);
  Js.log2("x:", x.json);

  x := json2;
  Js.log2("x:", x.json);

  let x1 = x @ "b";
  Js.log2("x1:", x1.json);
};

let res = testSmallDiff(4);
/* let res = testBigDiff(); */
let test = () => res;

/* testDynamicallyTypedJson(); */