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
  let make = (~nodeLabel, ~collapsed, ~child, _) => {
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
          (collapsed ? ReasonReact.null : child)
        </div>
      </div>;
    },
  };
};

let node = (~style=?, x) =>
  <span className="node" ?style> (ReasonReact.string(x)) </span>;

let nodeGreen = x => x |. node(~style=Color.(style(green)));

let nodeBrown = x => x |. node(~style=Color.(style(brown)));

let questionMark = p =>
  <span style=Color.(style(red))>
    (ReasonReact.string(" ? " ++ P.toString(p)))
  </span>;

type fmt = {
  plus: bool /* print '+' in front of number */,
  percent: bool /* show percentage instead of absolute numbers */,
  hideZeroOne: bool /* hide p when it's 0 or 1 */,
  hideP: bool /* hide p completely */,
};

let fmtDefault = {
  plus: false,
  percent: false,
  hideZeroOne: false,
  hideP: false,
};
let fmtDelta = {plus: true, percent: false, hideZeroOne: false, hideP: false};

let rec toComponentStyp =
        (styp: styp, ~ctx: p, ~fmt: fmt)
        : ReasonReact.reactElement => {
  let pUnchanged = ctx == P.zero && styp.p == P.zero;
  let color = Color.(stypIsNull(styp) ? red : pUnchanged ? grey : black);
  let typ = styp.typ |. toComponentT(~ctx=styp.p, ~fmt);
  let style = Color.style(color);
  let decorator =
    switch (styp.typ) {
    | Number(_)
    | String(_)
    | Boolean(_) => styp |. stypToDecorator(~ctx, ~fmt)
    | _ => ReasonReact.null
    };
  stypIsNull(styp) ?
    <div style className="node"> (ReasonReact.string("null")) </div> :
    <div style> typ decorator </div>;
}
and stypToDecorator = (styp: styp, ~ctx: p, ~fmt: fmt) => {
  let pUnchanged = ctx == P.zero && styp.p == P.zero;
  let pString =
    if (fmt.percent && ctx != P.zero) {
      P.toFloat(styp.p) /. P.toFloat(ctx) |. string_of_float;
    } else {
      (fmt.plus ? "+" : "") ++ P.toString(styp.p);
    };
  let p =
    fmt.hideP || fmt.hideZeroOne && (pUnchanged || styp.p == P.one) ?
      ReasonReact.null :
      <span style=Color.(style(blue))> (ReasonReact.string(pString)) </span>;
  let o =
    switch (styp.o) {
    | NotOpt => ReasonReact.null
    | Opt(p1) => questionMark(p1)
    };
  <span> p o </span>;
}
and toComponentT = (typ: typ, ~ctx: p, ~fmt: fmt) : ReasonReact.reactElement =>
  switch (typ) {
  | Empty => nodeBrown("empty")
  | Same(typ) =>
    <TreeView
      key="same"
      nodeLabel=(nodeBrown("same"))
      collapsed=true
      child=(typ |. toComponentT(~ctx, ~fmt))
    />
  | Number(_)
  | String(_)
  | Boolean(_) => typ |. constToString |. nodeGreen
  | Object(d) =>
    let doEntry = (i, (lbl, styp)) =>
      <TreeView
        key=(string_of_int(i))
        nodeLabel={
          <span>
            (node(lbl))
            (styp |. stypToDecorator(~ctx, ~fmt))
          </span>
        }
        collapsed=false
        child=(styp |. toComponentStyp(~ctx, ~fmt))
      />;

    ReasonReact.array(Js.Dict.entries(d) |. Array.mapWithIndex(doEntry));
  | Array(styp) when stypIsEmpty(styp) =>
    <span>
      (styp |. stypToDecorator(~ctx, ~fmt))
      (node("["))
      (node("]"))
    </span>
  | Array(styp) =>
    <span>
      <TreeView
        nodeLabel={
          <span> (styp |. stypToDecorator(~ctx, ~fmt)) (node("[")) </span>
        }
        collapsed=false
        child=(styp |. toComponentStyp(~ctx, ~fmt))
      />
      (node("]"))
    </span>
  | Union(styps) =>
    let doEntry = (i, styp) =>
      <TreeView
        key=(string_of_int(i))
        nodeLabel={
          <span>
            (node("u" ++ string_of_int(i + 1)))
            (styp |. stypToDecorator(~ctx, ~fmt))
          </span>
        }
        collapsed=false
        child=(styp |. toComponentStyp(~ctx, ~fmt))
      />;

    <div>
      ("union" |. nodeBrown)
      (
        styps
        |. List.mapWithIndex(doEntry)
        |. List.toArray
        |. ReasonReact.array
      )
    </div>;

  | Diff(t, lhs, rhs) =>
    let side = (~left) => {
      let lbl = left ? "lhs" : "rhs";
      let styp = left ? lhs : rhs;
      Styp.stypIsEmpty(styp) ?
        ReasonReact.null :
        <TreeView
          key=lbl
          nodeLabel=(lbl |. nodeBrown)
          collapsed=true
          child=(styp |. toComponentStyp(~ctx, ~fmt=fmtDelta))
        />;
    };
    <div>
      <TreeView
        nodeLabel=("common" |. nodeBrown)
        collapsed=true
        child=(t |. toComponentT(~ctx, ~fmt))
      />
      (side(~left=true))
      (side(~left=false))
    </div>;
  };

module Styp = {
  let component = ReasonReact.statelessComponent("Styp");
  let make = (~name, ~styp, ~fmt=fmtDefault, _) => {
    ...component,
    render: _ =>
      <TreeView
        nodeLabel=(node(name))
        collapsed=true
        child=(styp |. toComponentStyp(~ctx=P.zero, ~fmt))
      />,
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