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

let baseType = x =>
  <span className="node" style=(ReactDOMRe.Style.make(~color="orange", ()))>
    (ReasonReact.string(x))
  </span>;

let questionMark =
  <span style=(ReactDOMRe.Style.make(~color="red", ()))>
    (ReasonReact.string(" ? "))
  </span>;

type fmt = {
  plus: bool /* print '+' in front of number */,
  percent: bool /* show percentage instead of absolute numbers */,
  same: bool /* print same */
};

let fmtDefault = {plus: false, percent: true, same: false};
let fmtDelta = {plus: true, percent: false, same: true};

let rec toComponent =
        (styp: styp, ~ctx: p, ~fmt: fmt)
        : ReasonReact.reactElement => {
  let pUnchanged = ctx == 0 && styp.p == 0;
  let color = stypIsNull(styp) ? "red" : pUnchanged ? "grey" : "black";
  let pString =
    if (fmt.percent && ctx != 0) {
      float_of_int(styp.p) /. float_of_int(ctx) |. string_of_float;
    } else {
      (fmt.plus ? "+" : "") ++ string_of_int(styp.p);
    };
  let p =
    pUnchanged || styp.p == 1 ?
      ReasonReact.null :
      <span style=(ReactDOMRe.Style.make(~color="green", ()))>
        (ReasonReact.string(pString))
      </span>;
  let o = styp.o == Opt ? questionMark : ReasonReact.null;
  let t = styp.t |. toComponentT(~ctx=styp.p, ~fmt);
  let style = ReactDOMRe.Style.make(~color, ());
  stypIsNull(styp) ?
    <div style className="node"> (ReasonReact.string("null")) </div> :
    <div style> p o t </div>;
}
and toComponentT = (t: t, ~ctx: p, ~fmt: fmt) : ReasonReact.reactElement =>
  switch (t) {
  | Same => baseType(fmt.same ? "same" : "empty")
  | Number => baseType("number")
  | String => baseType("string")
  | Boolean => baseType("boolean")
  | Object(d) =>
    let doEntry = (i, (lbl, styp)) =>
      <TreeView key=(string_of_int(i)) nodeLabel=(node(lbl)) collapsed=false>
        (styp |. toComponent(~ctx, ~fmt))
      </TreeView>;

    <div>
      (ReasonReact.array(Js.Dict.entries(d) |. Array.mapWithIndex(doEntry)))
    </div>;
  | Array(styp) when stypIsSame(styp) => baseType("[]")
  | Array(styp) =>
    <span>
      <TreeView nodeLabel=(baseType("[")) collapsed=false>
        (styp |. toComponent(~ctx, ~fmt))
      </TreeView>
      (baseType("]"))
    </span>
  };

module Styp = {
  let component = ReasonReact.statelessComponent("Styp");
  let make = (~name, ~styp, ~fmt=fmtDefault, _) => {
    ...component,
    render: _ =>
      <TreeView nodeLabel=(node(name)) collapsed=true>
        (styp |. toComponent(~ctx=0, ~fmt))
      </TreeView>,
  };
};

module Diff = {
  let component = ReasonReact.statelessComponent("Diff");
  let make = (~diff: Typecheck.diff, _) => {
    ...component,
    render: _ =>
      <div>
        <div className="row">
          <div className="column2">
            <Styp styp=diff.styp1 name="styp1" />
          </div>
          <div className="column2">
            <Styp styp=diff.styp2 name="styp2" />
          </div>
        </div>
        <div className="column1"> <Styp styp=diff.stypB name="stypB" /> </div>
        <div className="row">
          <div className="column2">
            <Styp name="stypA1" styp=diff.stypA1 fmt=fmtDelta />
          </div>
          <div className="column2">
            <Styp name="stypA2" styp=diff.stypA2 fmt=fmtDelta />
          </div>
        </div>
      </div>,
  };
};