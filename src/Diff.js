// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Js_dict from "bs-platform/lib/es6/js_dict.js";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as Belt_List from "bs-platform/lib/es6/belt_List.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Belt_SetString from "bs-platform/lib/es6/belt_SetString.js";
import * as Styp$ReactTemplate from "./Styp.js";
import * as Caml_builtin_exceptions from "bs-platform/lib/es6/caml_builtin_exceptions.js";
import * as TypeCheck$ReactTemplate from "./TypeCheck.js";

function diffStyp(styp1, styp2) {
  var match = styp1[/* typ */0];
  var match$1 = styp2[/* typ */0];
  var exit = 0;
  if (typeof match === "number" || match.tag !== /* Union */6) {
    exit = 2;
  } else {
    var styps1 = match[0];
    var exit$1 = 0;
    if (typeof match$1 === "number" || match$1.tag !== /* Union */6) {
      exit$1 = 3;
    } else {
      return diffUnion(styp1, styp2, styps1, match$1[0]);
    }
    if (exit$1 === 3) {
      return diffUnion(styp1, styp2, styps1, /* :: */[
                  styp2,
                  /* [] */0
                ]);
    }
    
  }
  if (exit === 2 && typeof match$1 !== "number" && match$1.tag === /* Union */6) {
    return diffUnion(styp1, styp2, /* :: */[
                styp1,
                /* [] */0
              ], match$1[0]);
  }
  if (TypeCheck$ReactTemplate.plusTyp(match, match$1) === undefined) {
    return diffUnion(styp1, styp2, /* :: */[
                styp1,
                /* [] */0
              ], /* :: */[
                styp2,
                /* [] */0
              ]);
  } else {
    var match$2 = diffTyp(match, match$1);
    var match$3 = diffO(styp1[/* o */1], styp2[/* o */1]);
    var pB = Caml_obj.caml_min(styp1[/* p */2], styp2[/* p */2]);
    var pA1 = Styp$ReactTemplate.P["--"](styp1[/* p */2], pB);
    var pA2 = Styp$ReactTemplate.P["--"](styp2[/* p */2], pB);
    var stypA1_000 = /* typ */match$2[/* typA1 */0];
    var stypA1_001 = /* o */match$3[0];
    var stypA1 = /* record */[
      stypA1_000,
      stypA1_001,
      /* p */pA1
    ];
    var stypA2_000 = /* typ */match$2[/* typA2 */1];
    var stypA2_001 = /* o */match$3[1];
    var stypA2 = /* record */[
      stypA2_000,
      stypA2_001,
      /* p */pA2
    ];
    var stypB_000 = /* typ */match$2[/* typB */2];
    var stypB_001 = /* o */match$3[2];
    var stypB = /* record */[
      stypB_000,
      stypB_001,
      /* p */pB
    ];
    return /* record */[
            /* styp1 */styp1,
            /* styp2 */styp2,
            /* stypA1 */stypA1,
            /* stypA2 */stypA2,
            /* stypB */stypB
          ];
  }
}

function diffO(o1, o2) {
  if (o1) {
    if (o2) {
      var p2 = o2[0];
      var p1 = o1[0];
      var match = Caml_obj.caml_greaterthan(p1, p2);
      var match$1 = Caml_obj.caml_greaterthan(p2, p1);
      return /* tuple */[
              match ? /* Opt */[Styp$ReactTemplate.P["--"](p1, p2)] : /* NotOpt */0,
              match$1 ? /* Opt */[Styp$ReactTemplate.P["--"](p2, p1)] : /* NotOpt */0,
              /* Opt */[Caml_obj.caml_min(p1, p2)]
            ];
    } else {
      return /* tuple */[
              o1,
              /* NotOpt */0,
              /* NotOpt */0
            ];
    }
  } else {
    return /* tuple */[
            /* NotOpt */0,
            o2,
            /* NotOpt */0
          ];
  }
}

function diffTyp(typ1, typ2) {
  var makeSame = function (typ) {
    return /* record */[
            /* typA1 : Same */Block.__(0, [typ]),
            /* typA2 : Same */Block.__(0, [typ]),
            /* typB */typ
          ];
  };
  var exit = 0;
  var exit$1 = 0;
  if (typeof typ1 === "number") {
    exit$1 = 3;
  } else {
    switch (typ1.tag | 0) {
      case /* Number */1 :
          if (typeof typ2 === "number") {
            exit$1 = 3;
          } else {
            switch (typ2.tag | 0) {
              case /* Same */0 :
                  exit$1 = 3;
                  break;
              case /* Number */1 :
                  if (Caml_obj.caml_equal(typ1[0], typ2[0])) {
                    return makeSame(typ1);
                  } else {
                    exit = 2;
                  }
                  break;
              case /* Array */5 :
                  break;
              default:
                exit = 2;
            }
          }
          break;
      case /* String */2 :
          if (typeof typ2 === "number") {
            exit$1 = 3;
          } else {
            switch (typ2.tag | 0) {
              case /* Same */0 :
                  exit$1 = 3;
                  break;
              case /* String */2 :
                  if (Caml_obj.caml_equal(typ1[0], typ2[0])) {
                    return makeSame(typ1);
                  } else {
                    exit = 2;
                  }
                  break;
              case /* Array */5 :
                  break;
              default:
                exit = 2;
            }
          }
          break;
      case /* Boolean */3 :
          if (typeof typ2 === "number") {
            exit$1 = 3;
          } else {
            switch (typ2.tag | 0) {
              case /* Same */0 :
                  exit$1 = 3;
                  break;
              case /* Boolean */3 :
                  if (Caml_obj.caml_equal(typ1[0], typ2[0])) {
                    return makeSame(typ1);
                  } else {
                    exit = 2;
                  }
                  break;
              case /* Array */5 :
                  break;
              default:
                exit = 2;
            }
          }
          break;
      case /* Object */4 :
          var d1 = typ1[0];
          if (typeof typ2 === "number") {
            exit$1 = 3;
          } else {
            switch (typ2.tag | 0) {
              case /* Same */0 :
                  exit$1 = 3;
                  break;
              case /* Object */4 :
                  var d2 = typ2[0];
                  var dA1 = { };
                  var dA2 = { };
                  var dB = { };
                  var doItem2 = function (param) {
                    var styp2 = param[1];
                    var lbl = param[0];
                    var match = Js_dict.get(d1, lbl);
                    if (match !== undefined) {
                      var match$1 = diffStyp(match, styp2);
                      var stypA2 = match$1[/* stypA2 */3];
                      var stypA1 = match$1[/* stypA1 */2];
                      if (!Styp$ReactTemplate.stypIsEmpty(stypA1)) {
                        dA1[lbl] = stypA1;
                      }
                      if (!Styp$ReactTemplate.stypIsEmpty(stypA2)) {
                        dA2[lbl] = stypA2;
                      }
                      dB[lbl] = match$1[/* stypB */4];
                      return /* () */0;
                    } else if (Styp$ReactTemplate.stypIsEmpty(styp2)) {
                      return 0;
                    } else {
                      dA2[lbl] = styp2;
                      return /* () */0;
                    }
                  };
                  var doItem1 = function (param) {
                    var styp1 = param[1];
                    var lbl = param[0];
                    var match = Js_dict.get(d2, lbl);
                    if (match !== undefined || Styp$ReactTemplate.stypIsEmpty(styp1)) {
                      return /* () */0;
                    } else {
                      dA1[lbl] = styp1;
                      return /* () */0;
                    }
                  };
                  Belt_Array.forEach(Js_dict.entries(d2), doItem2);
                  Belt_Array.forEach(Js_dict.entries(d1), doItem1);
                  var entries1 = Js_dict.entries(dA1);
                  var entries2 = Js_dict.entries(dA2);
                  var t = Styp$ReactTemplate.makeObject(entries1);
                  var match = entries1.length === 0;
                  var typA1 = match ? /* Same */Block.__(0, [t]) : t;
                  var t$1 = Styp$ReactTemplate.makeObject(entries2);
                  var match$1 = entries2.length === 0;
                  var typA2 = match$1 ? /* Same */Block.__(0, [t$1]) : t$1;
                  var typB = Styp$ReactTemplate.makeObject(Js_dict.entries(dB));
                  return /* record */[
                          /* typA1 */typA1,
                          /* typA2 */typA2,
                          /* typB */typB
                        ];
              case /* Array */5 :
                  break;
              default:
                exit = 2;
            }
          }
          break;
      case /* Array */5 :
          if (typeof typ2 === "number") {
            exit$1 = 3;
          } else {
            switch (typ2.tag | 0) {
              case /* Same */0 :
                  exit$1 = 3;
                  break;
              case /* Array */5 :
                  var match$2 = diffStyp(typ1[0], typ2[0]);
                  var stypA2 = match$2[/* stypA2 */3];
                  var stypA1 = match$2[/* stypA1 */2];
                  var match$3 = Styp$ReactTemplate.stypIsEmpty(stypA1);
                  var typA1$1 = match$3 ? /* Same */Block.__(0, [/* Array */Block.__(5, [stypA1])]) : /* Array */Block.__(5, [stypA1]);
                  var match$4 = Styp$ReactTemplate.stypIsEmpty(stypA2);
                  var typA2$1 = match$4 ? /* Same */Block.__(0, [/* Array */Block.__(5, [stypA2])]) : /* Array */Block.__(5, [stypA2]);
                  var typB$1 = /* Array */Block.__(5, [match$2[/* stypB */4]]);
                  return /* record */[
                          /* typA1 */typA1$1,
                          /* typA2 */typA2$1,
                          /* typB */typB$1
                        ];
              default:
                exit = 2;
            }
          }
          break;
      default:
        exit$1 = 3;
    }
  }
  if (exit$1 === 3) {
    if (typeof typ2 === "number" || !(typ2.tag && typeof typ1 !== "number")) {
      return /* record */[
              /* typA1 */typ1,
              /* typA2 */typ2,
              /* typB : Empty */0
            ];
    } else {
      switch (typ1.tag | 0) {
        case /* Same */0 :
            return /* record */[
                    /* typA1 */typ1,
                    /* typA2 */typ2,
                    /* typB : Empty */0
                  ];
        case /* Union */6 :
            exit = 2;
            break;
        case /* Diff */7 :
            return /* record */[
                    /* typA1 : Empty */0,
                    /* typA2 */typ2,
                    /* typB : Empty */0
                  ];
        
      }
    }
  }
  if (exit === 2 && typeof typ2 !== "number") {
    switch (typ2.tag | 0) {
      case /* Array */5 :
          break;
      case /* Diff */7 :
          return /* record */[
                  /* typA1 */typ1,
                  /* typA2 : Empty */0,
                  /* typB : Empty */0
                ];
      default:
        
    }
  }
  throw [
        Caml_builtin_exceptions.assert_failure,
        /* tuple */[
          "Diff.re",
          127,
          21
        ]
      ];
}

function diffUnion(styp1, styp2, styps1, styps2) {
  var findMatch = function (t, _ts, _acc) {
    while(true) {
      var acc = _acc;
      var ts = _ts;
      if (ts) {
        var ts1 = ts[1];
        var t1 = ts[0];
        if (TypeCheck$ReactTemplate.plusTyp(t[/* typ */0], t1[/* typ */0]) !== undefined) {
          return /* tuple */[
                  t1,
                  Belt_List.concat(Belt_List.reverse(acc), ts1)
                ];
        } else {
          _acc = /* :: */[
            t1,
            acc
          ];
          _ts = ts1;
          continue ;
        }
      } else {
        return ;
      }
    };
  };
  var plus = function (ls1, ls2) {
    if (ls1) {
      var ts1 = ls1[1];
      var t1 = ls1[0];
      var match = findMatch(t1, ls2, /* [] */0);
      if (match !== undefined) {
        var match$1 = match;
        var match$2 = plus(ts1, match$1[1]);
        var match$3 = diffStyp(t1, match$1[0]);
        return /* record */[
                /* stypUA1 : :: */[
                  match$3[/* stypA1 */2],
                  match$2[/* stypUA1 */0]
                ],
                /* stypUA2 : :: */[
                  match$3[/* stypA2 */3],
                  match$2[/* stypUA2 */1]
                ],
                /* stypUB : :: */[
                  match$3[/* stypB */4],
                  match$2[/* stypUB */2]
                ]
              ];
      } else {
        var diffUnion = plus(ts1, ls2);
        return /* record */[
                /* stypUA1 : :: */[
                  t1,
                  diffUnion[/* stypUA1 */0]
                ],
                /* stypUA2 */diffUnion[/* stypUA2 */1],
                /* stypUB */diffUnion[/* stypUB */2]
              ];
      }
    } else {
      return /* record */[
              /* stypUA1 : [] */0,
              /* stypUA2 */ls2,
              /* stypUB : [] */0
            ];
    }
  };
  var match = plus(styps1, styps2);
  var toUnion = function (styps) {
    var styps1 = Belt_List.keep(styps, (function (styp) {
            return !Styp$ReactTemplate.stypIsEmpty(styp);
          }));
    if (styps1) {
      if (styps1[1]) {
        return Styp$ReactTemplate.makeUnion(styps1);
      } else {
        return styps1[0][/* typ */0];
      }
    } else {
      return /* Empty */0;
    }
  };
  var toStyp = function (stypU) {
    var typ = toUnion(stypU);
    var p = Belt_List.reduce(stypU, Styp$ReactTemplate.P.zero, (function (p, styp) {
            return Styp$ReactTemplate.P["^"](p, styp[/* p */2]);
          }));
    var o = Belt_List.reduce(stypU, /* NotOpt */0, (function (o, styp) {
            return TypeCheck$ReactTemplate.plusO(o, styp[/* o */1]);
          }));
    return /* record */[
            /* typ */typ,
            /* o */o,
            /* p */p
          ];
  };
  return /* record */[
          /* styp1 */styp1,
          /* styp2 */styp2,
          /* stypA1 */toStyp(match[/* stypUA1 */0]),
          /* stypA2 */toStyp(match[/* stypUA2 */1]),
          /* stypB */toStyp(match[/* stypUB */2])
        ];
}

function combineStyp(stypA1, stypA2, stypB) {
  if (Caml_obj.caml_notequal(stypA1[/* p */2], Styp$ReactTemplate.P.zero) || stypA1[/* o */1] !== /* NotOpt */0 || Caml_obj.caml_notequal(stypA2[/* p */2], Styp$ReactTemplate.P.zero) || stypA2[/* o */1] !== /* NotOpt */0) {
    return /* record */[
            /* typ : Diff */Block.__(7, [
                stypB[/* typ */0],
                stypA1,
                stypA2
              ]),
            /* o */stypB[/* o */1],
            /* p */stypB[/* p */2]
          ];
  } else {
    return /* record */[
            /* typ */combineTyp(stypA1[/* typ */0], stypA2[/* typ */0], stypB[/* typ */0]),
            /* o */stypB[/* o */1],
            /* p */stypB[/* p */2]
          ];
  }
}

function combineTyp(typA1, typA2, typB) {
  var exit = 0;
  if (typeof typA1 === "number") {
    exit = 2;
  } else {
    switch (typA1.tag | 0) {
      case /* Object */4 :
          break;
      case /* Same */0 :
      case /* Array */5 :
          exit = 2;
          break;
      default:
        return typB;
    }
  }
  if (exit === 2) {
    var exit$1 = 0;
    if (typeof typA2 === "number") {
      exit$1 = 3;
    } else {
      switch (typA2.tag | 0) {
        case /* Object */4 :
            break;
        case /* Same */0 :
        case /* Array */5 :
            exit$1 = 3;
            break;
        default:
          return typB;
      }
    }
    if (exit$1 === 3) {
      if (typeof typB === "number") {
        return typB;
      } else {
        switch (typB.tag | 0) {
          case /* Object */4 :
              break;
          case /* Array */5 :
              var getStyp = function (typ) {
                if (typeof typ === "number" || typ.tag !== /* Array */5) {
                  return Styp$ReactTemplate.stypEmpty;
                } else {
                  return typ[0];
                }
              };
              var stypA1 = getStyp(typA1);
              var stypA2 = getStyp(typA2);
              return /* Array */Block.__(5, [combineStyp(stypA1, stypA2, typB[0])]);
          default:
            return typB;
        }
      }
    }
    
  }
  if (typeof typA1 !== "number" && typA1.tag === /* Array */5) {
    return typB;
  }
  if (typeof typA2 !== "number") {
    switch (typA2.tag | 0) {
      case /* Same */0 :
      case /* Object */4 :
          break;
      default:
        return typB;
    }
  }
  if (typeof typB === "number" || typB.tag !== /* Object */4) {
    return typB;
  } else {
    var dictB = typB[0];
    var d = { };
    var getDict = function (typ) {
      if (typeof typ === "number") {
        return { };
      } else if (typ.tag === /* Object */4) {
        return typ[0];
      } else {
        return { };
      }
    };
    var dictA1 = getDict(typA1);
    var dictA2 = getDict(typA2);
    var doItem = function (lbl) {
      var getStyp = function (dict) {
        var match = Js_dict.get(dict, lbl);
        if (match !== undefined) {
          return match;
        } else {
          return Styp$ReactTemplate.stypEmpty;
        }
      };
      d[lbl] = combineStyp(getStyp(dictA1), getStyp(dictA2), getStyp(dictB));
      return /* () */0;
    };
    Belt_SetString.forEach(Belt_SetString.union(Belt_SetString.union(Belt_SetString.fromArray(Object.keys(dictA1)), Belt_SetString.fromArray(Object.keys(dictA2))), Belt_SetString.fromArray(Object.keys(dictB))), doItem);
    return Styp$ReactTemplate.makeObject(Js_dict.entries(d));
  }
}

function diff(styp1, styp2) {
  var d = diffStyp(styp1, styp2);
  return /* record */[
          /* styp1 */d[/* styp1 */0],
          /* styp2 */d[/* styp2 */1],
          /* stypA1 */d[/* stypA1 */2],
          /* stypA2 */d[/* stypA2 */3],
          /* stypB */combineStyp(d[/* stypA1 */2], d[/* stypA2 */3], d[/* stypB */4])
        ];
}

function diffCheck(styp1, styp2) {
  var d = diffStyp(styp1, styp2);
  if (!Caml_obj.caml_equal(TypeCheck$ReactTemplate.$caret(d[/* stypB */4], d[/* stypA1 */2]), styp1)) {
    throw [
          Caml_builtin_exceptions.assert_failure,
          /* tuple */[
            "Diff.re",
            246,
            2
          ]
        ];
  }
  if (!Caml_obj.caml_equal(TypeCheck$ReactTemplate.$caret(d[/* stypB */4], d[/* stypA2 */3]), styp2)) {
    throw [
          Caml_builtin_exceptions.assert_failure,
          /* tuple */[
            "Diff.re",
            247,
            2
          ]
        ];
  }
  return /* record */[
          /* styp1 */d[/* styp1 */0],
          /* styp2 */d[/* styp2 */1],
          /* stypA1 */d[/* stypA1 */2],
          /* stypA2 */d[/* stypA2 */3],
          /* stypB */combineStyp(d[/* stypA1 */2], d[/* stypA2 */3], d[/* stypB */4])
        ];
}

function toJson(diff) {
  var styp1 = Styp$ReactTemplate.stypToJson(diff[/* styp1 */0]);
  var styp2 = Styp$ReactTemplate.stypToJson(diff[/* styp2 */1]);
  var stypB = Styp$ReactTemplate.stypToJson(diff[/* stypB */4]);
  var stypA1 = Styp$ReactTemplate.stypToJson(diff[/* stypA1 */2]);
  var stypA2 = Styp$ReactTemplate.stypToJson(diff[/* stypA2 */3]);
  return Js_dict.fromArray(/* array */[
              /* tuple */[
                "styp1",
                styp1
              ],
              /* tuple */[
                "styp2",
                styp2
              ],
              /* tuple */[
                "stypB",
                stypB
              ],
              /* tuple */[
                "stypA1",
                stypA1
              ],
              /* tuple */[
                "stypA2",
                stypA2
              ]
            ]);
}

var inlineDifferences = true;

export {
  inlineDifferences ,
  diffStyp ,
  diffO ,
  diffTyp ,
  diffUnion ,
  combineStyp ,
  combineTyp ,
  diff ,
  diffCheck ,
  toJson ,
  
}
/* No side effect */
