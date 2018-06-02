open Belt;
open Styp;

module Key = {
  let counter = ref(0);
  let gen = () => {
    incr(counter);
    string_of_int(counter^);
  };
};

module TreeView = {
  type state = {collapsed: bool};
  type actions =
    | Click;
  let component = ReasonReact.reducerComponent("TreeView");
  let make = (~nodeLabel, ~collapsed, children) => {
    ...component,
    initialState: () => {collapsed: collapsed},
    reducer: (action, state) =>
      switch (action) {
      | Click => Update({collapsed: ! state.collapsed})
      },
    render: ({state: {collapsed}, send}) => {
      let arrowClassName =
        "tree-view_arrow" ++ (collapsed ? " tree-view_arrow-collapsed" : "");
      let containerClassName =
        "tree-view_children"
        ++ (collapsed ? " tree-view_children-collapsed" : "");

      <div className="tree-view ">
        <div className="tree-view_item  " onClick=(_ => send(Click))>
          <div className=arrowClassName />
          <span> nodeLabel </span>
        </div>
        <div className=containerClassName>
          (collapsed ? ReasonReact.null : ReasonReact.array(children))
        </div>
      </div>;
    },
  };
};

let node = x => <span className="node"> (ReasonReact.string(x)) </span>;

let questionMark =
  <span style=(ReactDOMRe.Style.make(~color="red", ()))>
    (ReasonReact.string(" ? "))
  </span>;

let rec toComponent =
        (styp: styp, ~ctx: option(p))
        : ReasonReact.reactElement => {
  let ctxZero = ctx == None || ctx == Some(0);
  let color = ctxZero ? "grey" : stypIsNull(styp) ? "red" : "black";
  let p =
    styp.p == 0 || styp.p == 1 ?
      ReasonReact.null :
      <span style=(ReactDOMRe.Style.make(~color="green", ()))>
        (ReasonReact.string("+" ++ string_of_int(styp.p)))
      </span>;
  let o = styp.o == Opt ? questionMark : ReasonReact.null;
  let t = styp.t |. toComponentT(~ctx=Some(styp.p));
  let style = ReactDOMRe.Style.make(~color, ());
  stypIsNull(styp) ?
    <div style className="node"> (ReasonReact.string("null")) </div> :
    <div style> p o t </div>;
}
and toComponentT = (t: t, ~ctx: option(p)) : ReasonReact.reactElement =>
  switch (t) {
  | Same => node("same")
  | Number => node("number")
  | String => node("string")
  | Boolean => node("boolean")
  | Object(d) =>
    let doEntry = (i, (lbl, styp)) =>
      <TreeView key=(string_of_int(i)) nodeLabel=(node(lbl)) collapsed=false>
        (styp |. toComponent(~ctx))
      </TreeView>;

    <div>
      (ReasonReact.array(Js.Dict.entries(d) |. Array.mapWithIndex(doEntry)))
    </div>;
  | Array(styp) when stypIsSame(styp) => node("[]")
  | Array(styp) =>
    <span>
      <TreeView nodeLabel=(node("[")) collapsed=false>
        (styp |. toComponent(~ctx))
      </TreeView>
      (node("]"))
    </span>
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
        (visible ? styp |. toComponent(~ctx=None) : ReasonReact.null)
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