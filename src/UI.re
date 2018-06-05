open Belt;
open Styp;

module Key = {
  let counter = ref(0);
  let gen = () => {
    incr(counter);
    string_of_int(counter^);
  };
};

module Color = {
  let black = "#000000";
  let blue = "#0000FF";
  let brown = "#795E26";
  let green = "#09885A";
  let grey = "#979797";
  let red = "#D60A0A";
  let style = color => ReactDOMRe.Style.make(~color, ());
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

let node = (~style=?, x) =>
  <span className="node" ?style> (ReasonReact.string(x)) </span>;

let baseType = x =>
  <span className="node" style=Color.(style(green))>
    (ReasonReact.string(x))
  </span>;

let questionMark = p =>
  <span style=Color.(style(red))>
    (ReasonReact.string(" ? " ++ P.toString(p)))
  </span>;

type fmt = {
  plus: bool /* print '+' in front of number */,
  percent: bool /* show percentage instead of absolute numbers */,
  same: bool /* print same */
};

let fmtDefault = {plus: false, percent: true, same: false};
let fmtDelta = {plus: true, percent: false, same: true};

let rec toComponentStyp =
        (styp: styp, ~ctx: p, ~fmt: fmt)
        : ReasonReact.reactElement => {
  let pUnchanged = ctx == P.zero && styp.p == P.zero;
  let color = Color.(stypIsNull(styp) ? red : pUnchanged ? grey : black);
  let pString =
    if (fmt.percent && ctx != P.zero) {
      P.toFloat(styp.p) /. P.toFloat(ctx) |. string_of_float;
    } else {
      (fmt.plus ? "+" : "") ++ P.toString(styp.p);
    };
  let p =
    pUnchanged || styp.p == P.one ?
      ReasonReact.null :
      <span style=Color.(style(blue))> (ReasonReact.string(pString)) </span>;
  let o =
    switch (styp.o) {
    | NotOpt => ReasonReact.null
    | Opt(p1) => questionMark(p1)
    };
  let t = styp.t |. toComponentT(~ctx=styp.p, ~fmt);
  let style = Color.style(color);
  stypIsNull(styp) ?
    <div style className="node"> (ReasonReact.string("null")) </div> :
    <div style> p o t </div>;
}
and toComponentT = (t: t, ~ctx: p, ~fmt: fmt) : ReasonReact.reactElement =>
  switch (t) {
  | Empty => baseType(fmt.same ? "same" : "empty")
  | Number => baseType("number")
  | String => baseType("string")
  | Boolean => baseType("boolean")
  | Object(d) =>
    let doEntry = (i, (lbl, styp)) =>
      <TreeView key=(string_of_int(i)) nodeLabel=(node(lbl)) collapsed=false>
        (styp |. toComponentStyp(~ctx, ~fmt))
      </TreeView>;

    <div>
      (ReasonReact.array(Js.Dict.entries(d) |. Array.mapWithIndex(doEntry)))
    </div>;
  | Array(styp) when stypIsEmpty(styp) => node("[]")
  | Array(styp) =>
    <span>
      <TreeView nodeLabel=(node("[")) collapsed=false>
        (styp |. toComponentStyp(~ctx, ~fmt))
      </TreeView>
      (node("]"))
    </span>
  | Annotation(s, t, arr) =>
    let doEntry = (i, (lbl, styp)) =>
      styp |. stypIsEmpty ?
        ReasonReact.null :
        <TreeView
          key=(string_of_int(i)) nodeLabel=(node(lbl)) collapsed=true>
          (styp |. toComponentStyp(~ctx, ~fmt=fmtDelta))
        </TreeView>;

    <div>
      <TreeView
        key=s
        nodeLabel=(node(~style=Color.(style(brown)), s))
        collapsed=true>
        (t |. toComponentT(~ctx, ~fmt))
      </TreeView>
      (ReasonReact.array(arr |. Array.mapWithIndex(doEntry)))
    </div>;
  };

module Styp = {
  let component = ReasonReact.statelessComponent("Styp");
  let make = (~name, ~styp, ~fmt=fmtDefault, _) => {
    ...component,
    render: _ =>
      <TreeView nodeLabel=(node(name)) collapsed=true>
        (styp |. toComponentStyp(~ctx=P.zero, ~fmt))
      </TreeView>,
  };
};

module Diff = {
  let component = ReasonReact.statelessComponent("Diff");
  let make = (~diff: Diff.t, _) => {
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