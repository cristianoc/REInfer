// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Js_dict from "bs-platform/lib/es6/js_dict.js";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Styp$ReactTemplate from "./Styp.js";
import * as Belt_List$ReactTemplate from "./Belt_List.js";

var counter = /* record */[/* contents */0];

function gen(param) {
  counter[0] = counter[0] + 1 | 0;
  return String(counter[0]);
}

var Key = {
  counter: counter,
  gen: gen
};

var black = "#000000";

var blue = "#0000FF";

var brown = "#795E26";

var green = "#09885A";

var grey = "#979797";

var red = "#D60A0A";

function style(color) {
  return {
          color: color
        };
}

var Color = {
  black: black,
  blue: blue,
  brown: brown,
  green: green,
  grey: grey,
  red: red,
  style: style
};

function reducer(state, action) {
  return /* record */[/* collapsed */!state[/* collapsed */0]];
}

function UI$TreeView(Props) {
  var nodeLabel = Props.nodeLabel;
  var collapsed = Props.collapsed;
  var child = Props.child;
  var match = React.useReducer(reducer, /* record */[/* collapsed */collapsed]);
  var dispatch = match[1];
  var state = match[0];
  var match$1 = state[/* collapsed */0];
  var arrowClassName = "tree-view_arrow" + (
    match$1 ? " tree-view_arrow-collapsed" : ""
  );
  var match$2 = state[/* collapsed */0];
  var containerClassName = "tree-view_children" + (
    match$2 ? " tree-view_children-collapsed" : ""
  );
  var match$3 = state[/* collapsed */0];
  return React.createElement("div", {
              className: "tree-view"
            }, React.createElement("div", {
                  className: "tree-view_item",
                  onClick: (function (param) {
                      return dispatch(/* Click */0);
                    })
                }, React.createElement("div", {
                      className: arrowClassName
                    }), React.createElement("span", undefined, nodeLabel)), React.createElement("div", {
                  className: containerClassName
                }, match$3 ? null : child));
}

var TreeView = {
  reducer: reducer,
  make: UI$TreeView
};

function node(style, x) {
  var tmp = {
    className: "node"
  };
  if (style !== undefined) {
    tmp.style = Caml_option.valFromOption(style);
  }
  return React.createElement("span", tmp, x);
}

function nodeGreen(x) {
  return node(Caml_option.some(style(green)), x);
}

function nodeBrown(x) {
  return node(Caml_option.some(style(brown)), x);
}

function questionMark(p) {
  return React.createElement("span", {
              style: style(red)
            }, " ? " + Styp$ReactTemplate.P.toString(p));
}

var fmtDefault = /* record */[
  /* plus */false,
  /* percent */false,
  /* hideZeroOne */false,
  /* hideP */false
];

var fmtDelta = /* record */[
  /* plus */true,
  /* percent */false,
  /* hideZeroOne */false,
  /* hideP */false
];

function toComponentStyp(styp, ctx, fmt) {
  var typ = toComponentT(styp[/* typ */0], styp[/* p */2], fmt);
  var match = Styp$ReactTemplate.stypIsNull(styp);
  var style$1 = style(match ? red : black);
  var match$1 = styp[/* typ */0];
  var shouldAddDecorator;
  if (typeof match$1 === "number") {
    shouldAddDecorator = true;
  } else {
    switch (match$1.tag | 0) {
      case /* Number */1 :
      case /* String */2 :
      case /* Boolean */3 :
          shouldAddDecorator = true;
          break;
      default:
        shouldAddDecorator = false;
    }
  }
  var match$2 = Styp$ReactTemplate.stypIsNull(styp);
  if (match$2) {
    return React.createElement("div", {
                className: "node",
                style: style$1
              }, "null");
  } else {
    return React.createElement("div", {
                style: style$1
              }, shouldAddDecorator ? addDecorator(typ, styp, true, ctx, fmt) : typ);
  }
}

function addDecorator(x, styp, right, ctx, fmt) {
  var pUnchanged = Caml_obj.caml_equal(ctx, Styp$ReactTemplate.P.zero) && Caml_obj.caml_equal(styp[/* p */2], Styp$ReactTemplate.P.zero);
  var pString;
  if (fmt[/* percent */1] && Caml_obj.caml_notequal(ctx, Styp$ReactTemplate.P.zero)) {
    pString = (Styp$ReactTemplate.P.toFloat(styp[/* p */2]) / Styp$ReactTemplate.P.toFloat(ctx)).toString();
  } else {
    var match = fmt[/* plus */0];
    pString = (
      match ? "+" : ""
    ) + Styp$ReactTemplate.P.toString(styp[/* p */2]);
  }
  var match$1 = fmt[/* hideP */3] || fmt[/* hideZeroOne */2] && (pUnchanged || Caml_obj.caml_equal(styp[/* p */2], Styp$ReactTemplate.P.one));
  var p = match$1 ? null : React.createElement("span", {
          style: style(blue)
        }, pString);
  var match$2 = styp[/* o */1];
  var o = match$2 ? questionMark(match$2[0]) : null;
  if (right) {
    return React.createElement("span", undefined, x, p, o);
  } else {
    return React.createElement("span", undefined, p, o, x);
  }
}

function toComponentT(typ, ctx, fmt) {
  if (typeof typ === "number") {
    return nodeBrown("empty");
  } else {
    switch (typ.tag | 0) {
      case /* Same */0 :
          return React.createElement(UI$TreeView, {
                      nodeLabel: nodeBrown("same"),
                      collapsed: true,
                      child: toComponentT(typ[0], ctx, fmt),
                      key: "same"
                    });
      case /* Object */4 :
          var doEntry = function (i, param) {
            var styp = param[1];
            var match = Caml_obj.caml_equal(styp[/* p */2], Styp$ReactTemplate.P.zero);
            return React.createElement("span", {
                        key: String(i),
                        style: style(match ? grey : black)
                      }, React.createElement(UI$TreeView, {
                            nodeLabel: addDecorator(node(undefined, param[0]), styp, true, ctx, fmt),
                            collapsed: false,
                            child: toComponentStyp(styp, ctx, fmt),
                            key: String(i)
                          }));
          };
          return Belt_Array.mapWithIndex(Js_dict.entries(typ[0]), doEntry);
      case /* Array */5 :
          var styp = typ[0];
          if (Styp$ReactTemplate.stypIsEmpty(styp)) {
            return React.createElement("span", undefined, addDecorator(node(undefined, "["), styp, false, ctx, fmt), node(undefined, "]"));
          } else {
            var match = Caml_obj.caml_equal(styp[/* p */2], Styp$ReactTemplate.P.zero);
            return React.createElement("span", {
                        style: style(match ? grey : black)
                      }, React.createElement(UI$TreeView, {
                            nodeLabel: addDecorator(node(undefined, "["), styp, false, ctx, fmt),
                            collapsed: false,
                            child: toComponentStyp(styp, ctx, fmt)
                          }), node(undefined, "]"));
          }
      case /* Union */6 :
          var doEntry$1 = function (i, styp) {
            return React.createElement(UI$TreeView, {
                        nodeLabel: addDecorator(node(undefined, "u" + String(i + 1 | 0)), styp, true, ctx, fmt),
                        collapsed: false,
                        child: toComponentStyp(styp, ctx, fmt),
                        key: String(i)
                      });
          };
          return React.createElement("div", undefined, nodeBrown("union"), Belt_List$ReactTemplate.toArray(Belt_List$ReactTemplate.mapWithIndex(typ[0], doEntry$1)));
      case /* Diff */7 :
          var rhs = typ[2];
          var lhs = typ[1];
          var side = function (left) {
            var lbl = left ? "lhs" : "rhs";
            var styp = left ? lhs : rhs;
            var match = Styp$ReactTemplate.stypIsEmpty(styp);
            return React.createElement(UI$TreeView, {
                        nodeLabel: nodeBrown(lbl),
                        collapsed: false,
                        child: match ? null : toComponentStyp(styp, ctx, fmtDelta),
                        key: lbl
                      });
          };
          return React.createElement("div", {
                      className: "row"
                    }, React.createElement("div", {
                          className: "column3"
                        }, side(true)), React.createElement("div", {
                          className: "column3"
                        }, React.createElement(UI$TreeView, {
                              nodeLabel: nodeBrown("common"),
                              collapsed: false,
                              child: toComponentT(typ[0], ctx, fmt)
                            })), React.createElement("div", {
                          className: "column3"
                        }, side(false)));
      default:
        return nodeGreen(Styp$ReactTemplate.constToString(typ));
    }
  }
}

function UI$Styp(Props) {
  var name = Props.name;
  var styp = Props.styp;
  var match = Props.fmt;
  var fmt = match !== undefined ? match : fmtDefault;
  return React.createElement(UI$TreeView, {
              nodeLabel: node(undefined, name),
              collapsed: true,
              child: toComponentStyp(styp, Styp$ReactTemplate.P.zero, fmt)
            });
}

var Styp = {
  make: UI$Styp
};

function UI$Diff(Props) {
  var diff = Props.diff;
  return React.createElement("div", undefined, React.createElement("div", {
                  className: "centerText"
                }, "Inferred Types"), React.createElement("div", {
                  className: "row"
                }, React.createElement("div", {
                      className: "column2"
                    }, React.createElement(UI$Styp, {
                          name: "styp1",
                          styp: diff[/* styp1 */0]
                        })), React.createElement("div", {
                      className: "column2"
                    }, React.createElement(UI$Styp, {
                          name: "styp2",
                          styp: diff[/* styp2 */1]
                        }))), React.createElement("div", {
                  className: "centerText"
                }, "Common Part"), React.createElement("div", undefined, React.createElement(UI$Styp, {
                      name: "stypB",
                      styp: diff[/* stypB */4]
                    })), React.createElement("div", {
                  className: "centerText"
                }, "Deltas"), React.createElement("div", {
                  className: "row"
                }, React.createElement("div", {
                      className: "column2"
                    }, React.createElement(UI$Styp, {
                          name: "stypA1",
                          styp: diff[/* stypA1 */2],
                          fmt: fmtDelta
                        })), React.createElement("div", {
                      className: "column2"
                    }, React.createElement(UI$Styp, {
                          name: "stypA2",
                          styp: diff[/* stypA2 */3],
                          fmt: fmtDelta
                        }))));
}

var Diff = {
  make: UI$Diff
};

export {
  Key ,
  Color ,
  TreeView ,
  node ,
  nodeGreen ,
  nodeBrown ,
  questionMark ,
  fmtDefault ,
  fmtDelta ,
  toComponentStyp ,
  addDecorator ,
  toComponentT ,
  Styp ,
  Diff ,
  
}
/* react Not a pure module */
