open Styp;

type t = {
  mutable json: Js.Json.t,
  styp: ref(styp),
};

let empty = () => {json: Js.Json.null, styp: ref(stypEmpty)};

let assignJson = (x, json) => {
  x.styp := TypeCheck.(++)(x.styp^, TypeCheck.fromJson(json));
  x.json = json;
};

let getFld = (x, fld) => {
  if (x.styp^.o != NotOpt) {
    Js.log(
      "Type error: access field " ++ fld ++ " of object with nullable type",
    );
    Js.log(x);
    assert(false);
  };
  let styp1 =
    switch (x.styp^.typ) {
    | Styp.Object(dict) =>
      let styp1 = dict |. Js.Dict.unsafeGet(fld);
      if (x.styp^.p != styp1.p) {
        Js.log(
          "Type error: access field " ++ fld ++ " of object with optional type",
        );
        Js.log(x);
        assert(false);
      };
      styp1;
    | _ => assert(false)
    };
  let json =
    switch (x.json |. Js.Json.decodeObject) {
    | None => assert(false)
    | Some(dict) => dict |. Js.Dict.unsafeGet(fld)
    };
  {json, styp: ref(styp1)};
};

let ref = json => {
  let x = empty();
  x |. assignJson(json);
  x;
};

let (:=) = assignJson;

let (@) = getFld;