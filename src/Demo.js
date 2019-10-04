// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as Belt_List from "bs-platform/lib/es6/belt_List.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Diff$ReactTemplate from "./Diff.js";
import * as Styp$ReactTemplate from "./Styp.js";
import * as Samples$ReactTemplate from "./Samples.js";
import * as Caml_builtin_exceptions from "bs-platform/lib/es6/caml_builtin_exceptions.js";
import * as Serialize$ReactTemplate from "./Serialize.js";
import * as TypeCheck$ReactTemplate from "./TypeCheck.js";
import * as DynTypedJson$ReactTemplate from "./DynTypedJson.js";

function testSmall(param) {
  var small = JSON.parse(" [{\"name\":null} ] ");
  var styp = TypeCheck$ReactTemplate.fromJson(undefined, small);
  console.log(JSON.stringify(Styp$ReactTemplate.stypToJson(styp)));
  return /* () */0;
}

function logDiff(diff) {
  console.log(JSON.stringify(Diff$ReactTemplate.toJson(diff)));
  return /* () */0;
}

function testSmallDiff($staropt$star, n) {
  var mode = $staropt$star !== undefined ? $staropt$star : TypeCheck$ReactTemplate.defaultMode;
  var examples = /* array */[
    /* tuple */[
      " {\"x\": \"hello\"} ",
      " {\"x\": null, \"y\":0} "
    ],
    /* tuple */[
      " [ \"hell\", 0, \"world\"] ",
      " [ \"hell\", \"o\", \"world\"] "
    ],
    /* tuple */[
      " [\"h\", \"e\", \"l\", \"l\", \"o\", \"w\", \"o\", \"r\", \"l\", \"d\"] ",
      " [\"h\", \"e\", \"l\", \"l\", 0, \"w\", \"o\", \"r\", \"l\", \"d\"] "
    ],
    /* tuple */[
      "[null,2,3,4]",
      "[3]"
    ],
    /* tuple */[
      " [{\"x\": {\"y\" : \"hello\"}}] ",
      " [{\"x\": {\"z\" : \"hello\"}}] "
    ],
    /* tuple */[
      "null",
      "3"
    ],
    /* tuple */[
      " [{\"a\":3},{\"b\":3}] ",
      " [] "
    ],
    /* tuple */[
      " [null,{\"b\":3}] ",
      " [] "
    ],
    /* tuple */[
      " [3, \"hello\", true, 4] ",
      " [1,2,3] "
    ],
    /* tuple */[
      " 3 ",
      " \"abc\" "
    ],
    /* tuple */[
      "[{\"x\": [\"p\",\"s\"]}]",
      "[{\"x\":[\"p\",\"b\"]},\n         {\"x\":[\"p\",\"s\"]},\n         {\"x\": [\"p\",\"s\"]}]"
    ]
  ];
  var styp1 = TypeCheck$ReactTemplate.fromJson(mode, JSON.parse(Belt_Array.getExn(examples, n)[0]));
  var styp2 = TypeCheck$ReactTemplate.fromJson(mode, JSON.parse(Belt_Array.getExn(examples, n)[1]));
  var diff = Diff$ReactTemplate.diffCheck(styp1, styp2);
  logDiff(diff);
  return diff;
}

function testSamples($staropt$star, param) {
  var mode = $staropt$star !== undefined ? $staropt$star : TypeCheck$ReactTemplate.defaultMode;
  var partial_arg = mode;
  var styps = Belt_List.map(Belt_List.map(/* :: */[
            " {\"x\": 1, \"y\":\"hello\"} ",
            /* :: */[
              " {\"x\": 2} ",
              /* :: */[
                " {\"x\": 3, \"y\":null} ",
                /* [] */0
              ]
            ]
          ], (function (prim) {
              return JSON.parse(prim);
            })), (function (param) {
          return TypeCheck$ReactTemplate.fromJson(partial_arg, param);
        }));
  return Samples$ReactTemplate.getAllDiffs(Samples$ReactTemplate.fromList(styps));
}

function testDynamicallyTypedJson(param) {
  var json1 = JSON.parse(" null ");
  var json2 = JSON.parse(" {\"b\":3} ");
  var x = DynTypedJson$ReactTemplate.ref(json1);
  console.log("x:", x[/* json */0]);
  DynTypedJson$ReactTemplate.$colon$eq(x, json2);
  console.log("x:", x[/* json */0]);
  if (DynTypedJson$ReactTemplate.$less$great(x, DynTypedJson$ReactTemplate.$$null)) {
    var x1 = DynTypedJson$ReactTemplate.$at(x, "b");
    console.log("x1:", x1[/* json */0]);
    return /* () */0;
  } else {
    return 0;
  }
}

function testSerializer(o, testName) {
  var s = Serialize$ReactTemplate.toString(o);
  var o1 = Serialize$ReactTemplate.fromString(s);
  if (Caml_obj.caml_notequal(o, o1)) {
    console.log("Serialize " + testName);
    console.log("o:", o);
    console.log("s:", s);
    console.log("o1:", o1);
    throw [
          Caml_builtin_exceptions.assert_failure,
          /* tuple */[
            "Demo.re",
            93,
            4
          ]
        ];
  }
  return o;
}

var res_000 = testSmallDiff(undefined, 0);

var res = /* :: */[
  res_000,
  /* [] */0
];

function test(param) {
  return res;
}

testDynamicallyTypedJson(/* () */0);

export {
  testSmall ,
  logDiff ,
  testSmallDiff ,
  testSamples ,
  testDynamicallyTypedJson ,
  testSerializer ,
  res ,
  test ,
  
}
/* res Not a pure module */
