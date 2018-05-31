open Belt;
open Styp;

let s = x => <div> (ReasonReact.string(x)) </div>;

let rec toComponent =
        (styp: styp, ~ctx: option(p))
        : ReasonReact.reactElement =>
  styp.t |. toComponentT(~ctx)
and toComponentT = (t: t, ~ctx: option(p)) : ReasonReact.reactElement =>
  switch (t) {
  | Same => s("same")
  | Number => s("number")
  | String => s("string")
  | Boolean => s("boolean")
  | Object(d) =>
    let doEntry = ((lbl, styp)) =>
      <div> (s(lbl)) (styp |. toComponent(~ctx)) </div>;
    <div>
      (ReasonReact.array(Js.Dict.entries(d) |. Array.map(doEntry)))
    </div>;
  /* | Array(styp) when simpleEmptyArray && stypIsSame(styp) =>
     [||] |. Js.Json.array */
  | Array(styp) => <div> (s("[]")) (styp |. toComponent(~ctx)) </div>
  };