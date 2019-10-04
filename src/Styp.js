// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Js_dict from "bs-platform/lib/es6/js_dict.js";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as Belt_List from "bs-platform/lib/es6/belt_List.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Pervasives from "bs-platform/lib/es6/pervasives.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_primitive from "bs-platform/lib/es6/caml_primitive.js";
import * as Caml_builtin_exceptions from "bs-platform/lib/es6/caml_builtin_exceptions.js";

function $caret(prim, prim$1) {
  return prim + prim$1 | 0;
}

function $neg$neg(prim, prim$1) {
  return prim - prim$1 | 0;
}

function toString(prim) {
  return String(prim);
}

function toFloat(prim) {
  return prim;
}

var P = {
  zero: 0,
  one: 1,
  "^": $caret,
  "--": $neg$neg,
  toString: toString,
  toFloat: toFloat
};

function constToString(typ) {
  if (typeof typ === "number") {
    throw [
          Caml_builtin_exceptions.assert_failure,
          /* tuple */[
            "Styp.re",
            53,
            9
          ]
        ];
  } else {
    switch (typ.tag | 0) {
      case /* Number */1 :
          return "number" + Belt_Option.mapWithDefault(typ[0], "", (function (f) {
                        return ":" + f.toString();
                      }));
      case /* String */2 :
          return "string" + Belt_Option.mapWithDefault(typ[0], "", (function (s) {
                        return ":" + s;
                      }));
      case /* Boolean */3 :
          return "boolean" + Belt_Option.mapWithDefault(typ[0], "", (function (b) {
                        return ":" + Pervasives.string_of_bool(b);
                      }));
      default:
        throw [
              Caml_builtin_exceptions.assert_failure,
              /* tuple */[
                "Styp.re",
                53,
                9
              ]
            ];
    }
  }
}

function stripDiffStyp(styp) {
  return /* record */[
          /* typ */stripDiffTyp(styp[/* typ */0]),
          /* o */styp[/* o */1],
          /* p */styp[/* p */2]
        ];
}

function stripDiffTyp(_typ) {
  while(true) {
    var typ = _typ;
    if (typeof typ === "number") {
      return typ;
    } else {
      switch (typ.tag | 0) {
        case /* Same */0 :
            return /* Same */Block.__(0, [stripDiffTyp(typ[0])]);
        case /* Object */4 :
            return /* Object */Block.__(4, [Js_dict.map(stripDiffStyp, typ[0])]);
        case /* Array */5 :
            return /* Array */Block.__(5, [stripDiffStyp(typ[0])]);
        case /* Union */6 :
            return /* Union */Block.__(6, [Belt_List.map(typ[0], stripDiffStyp)]);
        case /* Diff */7 :
            _typ = typ[0];
            continue ;
        default:
          return typ;
      }
    }
  };
}

function typIsEmpty(typ) {
  if (typeof typ === "number" || !typ.tag) {
    return true;
  } else {
    return false;
  }
}

function stypIsNull(styp) {
  var match = styp[/* o */1];
  if (match && typIsEmpty(styp[/* typ */0])) {
    return Caml_obj.caml_equal(styp[/* p */2], match[0]);
  } else {
    return false;
  }
}

var stypEmpty = /* record */[
  /* typ : Empty */0,
  /* o : NotOpt */0,
  /* p */0
];

function stypIsEmpty(styp) {
  if (styp[/* o */1] || !typIsEmpty(styp[/* typ */0])) {
    return false;
  } else {
    return Caml_obj.caml_equal(styp[/* p */2], 0);
  }
}

function stypToUnion(styp) {
  var match = styp[/* typ */0];
  if (typeof match === "number" || match.tag !== /* Union */6) {
    return /* :: */[
            styp,
            /* [] */0
          ];
  } else {
    return match[0];
  }
}

function compareEntries(param, param$1) {
  return Caml_primitive.caml_string_compare(param[0], param$1[0]);
}

function makeObject(arr) {
  return /* Object */Block.__(4, [Js_dict.fromList(Belt_List.sort(Belt_List.fromArray(arr), compareEntries))]);
}

var compareStyp = Caml_obj.caml_compare;

function makeUnion(styps) {
  return /* Union */Block.__(6, [Belt_List.sort(styps, compareStyp)]);
}

function pToJson(p) {
  return String(p);
}

function stypToJson(styp) {
  var dict = { };
  dict["typ"] = typToJson(styp[/* typ */0]);
  var match = styp[/* o */1];
  if (match) {
    dict["opt"] = String(match[0]);
  }
  dict["p"] = String(styp[/* p */2]);
  return dict;
}

function typToJson(typ) {
  if (typeof typ === "number") {
    return Js_dict.fromArray(/* array */[/* tuple */[
                  "kind",
                  "Empty"
                ]]);
  } else {
    switch (typ.tag | 0) {
      case /* Same */0 :
          return Js_dict.fromArray(/* array */[
                      /* tuple */[
                        "kind",
                        "Same"
                      ],
                      /* tuple */[
                        "typ",
                        typToJson(typ[0])
                      ]
                    ]);
      case /* Object */4 :
          var entries = Js_dict.fromArray(Belt_Array.map(Js_dict.entries(typ[0]), (function (param) {
                      return /* tuple */[
                              param[0],
                              stypToJson(param[1])
                            ];
                    })));
          return Js_dict.fromArray(/* array */[
                      /* tuple */[
                        "kind",
                        "Object"
                      ],
                      /* tuple */[
                        "entries",
                        entries
                      ]
                    ]);
      case /* Array */5 :
          var typ$1 = stypToJson(typ[0]);
          return Js_dict.fromArray(/* array */[
                      /* tuple */[
                        "kind",
                        "Array"
                      ],
                      /* tuple */[
                        "typ",
                        typ$1
                      ]
                    ]);
      case /* Union */6 :
          var entries$1 = Js_dict.fromArray(Belt_Array.mapWithIndex(Belt_List.toArray(typ[0]), (function (i, styp) {
                      return /* tuple */[
                              "u" + String(i),
                              stypToJson(styp)
                            ];
                    })));
          return Js_dict.fromArray(/* array */[
                      /* tuple */[
                        "kind",
                        "Union"
                      ],
                      /* tuple */[
                        "entries",
                        entries$1
                      ]
                    ]);
      case /* Diff */7 :
          var common = typToJson(typ[0]);
          var lhs = stypToJson(typ[1]);
          var rhs = stypToJson(typ[2]);
          return Js_dict.fromArray(/* array */[
                      /* tuple */[
                        "kind",
                        "Diff"
                      ],
                      /* tuple */[
                        "common",
                        common
                      ],
                      /* tuple */[
                        "lhs",
                        lhs
                      ],
                      /* tuple */[
                        "rhs",
                        rhs
                      ]
                    ]);
      default:
        var kind;
        if (typeof typ === "number") {
          throw [
                Caml_builtin_exceptions.assert_failure,
                /* tuple */[
                  "Styp.re",
                  133,
                  15
                ]
              ];
        } else {
          switch (typ.tag | 0) {
            case /* Number */1 :
                kind = "Number";
                break;
            case /* String */2 :
                kind = "String";
                break;
            case /* Boolean */3 :
                kind = "Boolean";
                break;
            default:
              throw [
                    Caml_builtin_exceptions.assert_failure,
                    /* tuple */[
                      "Styp.re",
                      133,
                      15
                    ]
                  ];
          }
        }
        return Js_dict.fromArray(/* array */[
                    /* tuple */[
                      "kind",
                      kind
                    ],
                    /* tuple */[
                      "value",
                      constToString(typ)
                    ]
                  ]);
    }
  }
}

export {
  P ,
  constToString ,
  stripDiffStyp ,
  stripDiffTyp ,
  typIsEmpty ,
  stypIsNull ,
  stypEmpty ,
  stypIsEmpty ,
  stypToUnion ,
  compareEntries ,
  makeObject ,
  compareStyp ,
  makeUnion ,
  pToJson ,
  stypToJson ,
  typToJson ,
  
}
/* No side effect */
