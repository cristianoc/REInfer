open Belt;
open Styp;

let s = x => <div> (ReasonReact.string(x)) </div>;

let questionMark =
  <div style=(ReactDOMRe.Style.make(~color="red", ()))>
    (ReasonReact.string("?"))
  </div>;

let rec toComponent =
        (styp: styp, ~ctx: option(p))
        : ReasonReact.reactElement => {
  let ctxZero = ctx == None || ctx == Some(0);
  let color = ctxZero ? "grey" : "black";
  let p =
    styp.p == 0 || styp.p == 1 ?
      ReasonReact.null :
      <div style=(ReactDOMRe.Style.make(~color="green", ()))>
        (ReasonReact.string("+" ++ string_of_int(styp.p)))
      </div>;
  let style = ReactDOMRe.Style.make(~color, ());
  stypIsNull(styp) ?
    <div style> (ReasonReact.string("null")) </div> :
    <div style>
      (styp.o == Opt ? questionMark : ReasonReact.null)
      p
      (styp.t |. toComponentT(~ctx=Some(styp.p)))
    </div>;
}
and toComponentT = (t: t, ~ctx: option(p)) : ReasonReact.reactElement =>
  switch (t) {
  | Same => s("same")
  | Number => s("number")
  | String => s("string")
  | Boolean => s("boolean")
  | Object(d) =>
    let doEntry = ((lbl, styp)) =>
      <div>
        (s(lbl))
        <div style=(ReactDOMRe.Style.make(~marginLeft="20px", ()))>
          (styp |. toComponent(~ctx))
        </div>
      </div>;
    <div>
      (ReasonReact.array(Js.Dict.entries(d) |. Array.map(doEntry)))
    </div>;
  | Array(styp) when stypIsSame(styp) => s("[]")
  | Array(styp) =>
    <div>
      (s("["))
      <div style=(ReactDOMRe.Style.make(~marginLeft="20px", ()))>
        (styp |. toComponent(~ctx))
      </div>
      (s("]"))
    </div>
  };

module Styp = {
  type state = {visible: bool};
  type actions =
    | Click;
  let component = ReasonReact.reducerComponent("Styp");
  let make = (~name, ~styp, _) => {
    ...component,
    initialState: () => {visible: false},
    reducer: (action, state) =>
      switch (action) {
      | Click => Update({visible: ! state.visible})
      },
    render: ({send, state: {visible}}) =>
      <div>
        <button
          onClick=(_ => send(Click))
          style=(ReactDOMRe.Style.make(~height="50px", ~width="200px", ()))>
          (ReasonReact.string(name))
        </button>
        (
          visible ?
            <div style=(ReactDOMRe.Style.make(~marginLeft="20px", ()))>
              (styp |. toComponent(~ctx=None))
            </div> :
            ReasonReact.null
        )
      </div>,
  };
};

module Diff = {
  let component = ReasonReact.statelessComponent("Diff");
  let make = (~diff: Typecheck.diff, _) => {
    ...component,
    render: _ =>
      <div>
        <Styp styp=diff.stypA1 name="stypA1" />
        <Styp styp=diff.stypA2 name="stypA2" />
        <Styp styp=diff.stypB name="stypB" />
        <Styp styp=diff.styp1 name="styp1" />
        <Styp styp=diff.styp2 name="styp2" />
      </div>,
  };
};