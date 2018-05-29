open! StatisticalTypeChecking;

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
  let styp = styp2 -- styp1;
  Js.log(styp1 |. PrettyPrint.styp);
  Js.log(styp2 |. PrettyPrint.styp);
  Js.log(styp |. PrettyPrint.styp);
};

let testSmallDiff = () => {
  /* let styp1 = {| {"x": "hello", "y":"world"} |} |. Js.Json.parseExn |. Styp.fromJson;
     let styp2 = {| {"x": null} |} |. Js.Json.parseExn |. Styp.fromJson; */
  /* let styp1 = {| [{"x": {"y" : "hello"}}] |} |. Js.Json.parseExn |. Styp.fromJson;
     let styp2 = {| [{"x": {"z" : "hello"}}] |} |. Js.Json.parseExn |. Styp.fromJson; */
  /* let styp1 = {| null |} |. Js.Json.parseExn |. Styp.fromJson;
     let styp2 = {| 3 |} |. Js.Json.parseExn |. Styp.fromJson; */
  let styp1 = {| [null,2] |} |. Js.Json.parseExn |. fromJson;
  let styp2 = {| [3] |} |. Js.Json.parseExn |. fromJson;
  let (stypA1, stypA2, stypB) = diffCheck(styp1, styp2);
  Js.log2("styp1", styp1 |. PrettyPrint.styp);
  Js.log2("styp2", styp2 |. PrettyPrint.styp);
  Js.log2("stypA1", stypA1 |. PrettyPrint.styp);
  Js.log2("stypA2", stypA2 |. PrettyPrint.styp);
  Js.log2("stypB", stypB |. PrettyPrint.styp);
  Js.log2("stypB ++ stypA1", stypB ++ stypA1 |. PrettyPrint.styp);
  Js.log2("stypB ++ stypA2", stypB ++ stypA2 |. PrettyPrint.styp);
};

let testBigDiff = () => {
  let styp1 = Lazy.force(bronze);
  let styp2 = Lazy.force(platinum);
  let (stypA1, stypA2, stypB) = diffCheck(styp1, styp2);
  /* Js.log2("styp1", styp1 |. PrettyPrint.styp);
     Js.log2("styp2", styp2 |. PrettyPrint.styp); */
  Js.log2("stypA1", stypA1 |. PrettyPrint.styp);
  Js.log2("stypA2", stypA2 |. PrettyPrint.styp);
  Js.log2("stypB", stypB |. PrettyPrint.styp);
};


let test = () => testBigDiff();