open Styp;

type t = {
  mutable json: Js.Json.t,
  styp: ref(styp),
};

let empty = () => {json: Js.Json.null, styp: ref(stypEmpty)};

let log = x => {
  Js.log2("json:", x.json);
  Js.log2("styp:", x.styp^ |. stypToJson |. Js.Json.stringify);
};

let assignJson = (x, json) => {
  x.styp := TypeCheck.(++)(x.styp^, TypeCheck.fromJson(json));
  x.json = json;
};

let getFld = (x, fld) => {
  if (x.styp^.o != NotOpt) {
    Js.log(
      "Type error: access field " ++ fld ++ " of object with nullable type",
    );
    log(x);
    assert(false);
  };
  let styp1 =
    switch (x.styp^.typ) {
    | Styp.Object(dict) =>
      let styp1 = dict |. Js.Dict.unsafeGet(fld);
      let stypP = x.styp^.p;
      let styp1P = styp1.p;
      let stypOP =
        switch (x.styp^.o) {
        | NotOpt => P.zero
        | Opt(p) => p
        };
      if (stypP != P.(++)(styp1P, stypOP)) {
        Js.log(
          "Type error: access field " ++ fld ++ " of object with optional type",
        );
        log(x);
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

let null = empty();

let makeNotNullable = x => {
  let styp = x.styp^;
  if (styp.o != NotOpt) {
    let stypOP =
      switch (styp.o) {
      | NotOpt => P.zero
      | Opt(p) => p
      };
    x.styp := {...styp, o: NotOpt, p: P.(styp.p -- stypOP)};
  };
};
let (==) = (x, y) => {
  let magicX = Obj.magic(x);
  let magicY = Obj.magic(y);
  switch (magicX == null, magicY == null) {
  | (true, true) => true
  | (true, false) =>
    makeNotNullable(magicY);
    false;
  | (false, true) =>
    makeNotNullable(magicX);
    false;
  | (false, false) => x == y
  };
};

let (!=) = (x, y) => ! (x == y);

let ref = json => {
  let x = empty();
  x |. assignJson(json);
  x;
};

let (:=) = assignJson;

let (@) = getFld;