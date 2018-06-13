open Belt;
open Styp;

let rec toJsonStyp = (styp: styp) : Js.Json.t => {
  let jsonT = styp.typ |. toJsonTyp;
  let oString =
    switch (styp.o) {
    | NotOpt => ""
    | Opt(p1) => "?" ++ P.toString(p1)
    };

  let dict = Js.Dict.empty();
  dict |. Js.Dict.set("typ", jsonT);
  dict |. Js.Dict.set("p", styp.p |. P.toString |. Js.Json.string);
  dict |. Js.Dict.set("o", oString |. Js.Json.string);
  dict |. Js.Json.object_;
}
and toJsonTyp = (typ: typ) : Js.Json.t =>
  switch (typ) {
  | Empty => Js.Json.string("empty")
  | Same(typ) =>
    [|("same", typ |. toJsonTyp)|] |. Js.Dict.fromArray |. Js.Json.object_
  | Number(_)
  | String(_)
  | Boolean(_) => typ |. constToString |. Js.Json.string
  | Object(d) =>
    let doEntry = ((lbl, styp)) => (lbl, styp |. toJsonStyp);
    Js.Dict.entries(d)
    |. Array.map(doEntry)
    |. Js.Dict.fromArray
    |. Js.Json.object_;
  | Array(styp) => [|styp |. toJsonStyp|] |. Js.Json.array
  | Union(styps) =>
    styps
    |. List.mapWithIndex((i, styp) =>
         ("u" ++ string_of_int(i), styp |. toJsonStyp)
       )
    |. Js.Dict.fromList
    |. Js.Json.object_
  | Diff(typ, _, _) => typ |. toJsonTyp
  };
let styp = styp => styp |. toJsonStyp |. Js.Json.stringify;