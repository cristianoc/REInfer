// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Js_dict from "bs-platform/lib/es6/js_dict.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";

var tagID = "tag320775503";

var undefinedID = "undefined290180182";

function copy(o_) {
  var match = Array.isArray(o_);
  if (match) {
    return o_.slice(0);
  } else {
    return Object.assign({ }, o_);
  }
}

function wrapTag(o_) {
  var match = typeof o_;
  switch (match) {
    case "object" :
        if (o_ === null) {
          return o_;
        } else {
          var o1 = copy(o_);
          var keys = Object.keys(o1);
          for(var i = 1 ,i_finish = keys.length; i <= i_finish; ++i){
            var key = Belt_Array.getExn(keys, i - 1 | 0);
            o1[key] = wrapTag(Js_dict.get(o_, key));
          }
          var tagOpt = Js_dict.get(o_, "tag");
          if (tagOpt !== undefined) {
            return /* array */[
                    tagID,
                    Caml_option.valFromOption(tagOpt),
                    o1
                  ];
          } else {
            return o1;
          }
        }
    case "undefined" :
        return /* array */[undefinedID];
    default:
      return o_;
  }
}

function unwrapTag(o_) {
  var match = typeof o_;
  if (match === "object" && o_ !== null) {
    var match$1 = Array.isArray(o_);
    var match$2 = match$1 ? Belt_Array.get(o_, 0) : undefined;
    if (match$2 !== undefined) {
      var id = Caml_option.valFromOption(match$2);
      if (id === undefinedID) {
        return ;
      } else if (id === tagID) {
        var tag = Belt_Array.getExn(o_, 1);
        var innerObj = Belt_Array.getExn(o_, 2);
        innerObj["tag"] = tag;
        unwrapKeys(innerObj);
        return innerObj;
      }
      
    }
    var o1 = copy(o_);
    unwrapKeys(o1);
    return o1;
  } else {
    return o_;
  }
}

function unwrapKeys(o) {
  var keys = Object.keys(o);
  for(var i = 1 ,i_finish = keys.length; i <= i_finish; ++i){
    var key = Belt_Array.getExn(keys, i - 1 | 0);
    o[key] = unwrapTag(Js_dict.get(o, key));
  }
  return /* () */0;
}

function toString(o) {
  return JSON.stringify(wrapTag(o));
}

function fromString(s) {
  return unwrapTag(JSON.parse(s));
}

export {
  toString ,
  fromString ,
  
}
/* No side effect */
