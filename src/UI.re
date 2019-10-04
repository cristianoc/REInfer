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
      | Click => Update({collapsed: !state.collapsed})
      },
    render: ({state: {collapsed}, send}) => {
      let arrowClassName =
        "tree-view_arrow" ++ (collapsed ? " tree-view_arrow-collapsed" : "");
      let containerClassName =
        "tree-view_children"
        ++ (collapsed ? " tree-view_children-collapsed" : "");

      <div className="tree-view">
        <div className="tree-view_item" onClick={_ => send(Click)}>
          <div className=arrowClassName />
          <span> nodeLabel </span>
        </div>
        <div className=containerClassName>
          {collapsed ? ReasonReact.null : child}
        </div>
      </div>;
    },
  };
};

let node = (~style=?, x) =>
  <span className="node" ?style> {ReasonReact.string(x)} </span>;

let nodeGreen = x => x->(node(~style=Color.(style(green))));

let nodeBrown = x => x->(node(~style=Color.(style(brown))));

let questionMark = p =>
  <span style=Color.(style(red))>
    {ReasonReact.string(" ? " ++ P.toString(p))}
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
        (styp: styp, ~ctx: p, ~fmt: fmt): ReasonReact.reactElement => {
  let typ = styp.typ->(toComponentT(~ctx=styp.p, ~fmt));
  let style = Color.(style(stypIsNull(styp) ? red : black));
  let shouldAddDecorator =
    switch (styp.typ) {
    | Empty
    | Number(_)
    | String(_)
    | Boolean(_) => true
    | _ => false
    };
  stypIsNull(styp)
    ? <div style className="node"> {ReasonReact.string("null")} </div>
    : <div style>
        {shouldAddDecorator
           ? typ->(addDecorator(~styp, ~right=true, ~ctx, ~fmt)) : typ}
      </div>;
}
and addDecorator =
    (x: ReasonReact.reactElement, ~styp: styp, ~right, ~ctx: p, ~fmt: fmt)
    : ReasonReact.reactElement => {
  let pUnchanged = ctx == P.zero && styp.p == P.zero;
  let pString =
    if (fmt.percent && ctx != P.zero) {
      (P.toFloat(styp.p) /. P.toFloat(ctx))->Js.Float.toString;
    } else {
      (fmt.plus ? "+" : "") ++ P.toString(styp.p);
    };
  let p =
    fmt.hideP || fmt.hideZeroOne && (pUnchanged || styp.p == P.one)
      ? ReasonReact.null
      : <span style=Color.(style(blue))>
          {ReasonReact.string(pString)}
        </span>;
  let o =
    switch (styp.o) {
    | NotOpt => ReasonReact.null
    | Opt(p1) => questionMark(p1)
    };
  right ? <span> x p o </span> : <span> p o x </span>;
}
and toComponentT = (typ: typ, ~ctx: p, ~fmt: fmt): ReasonReact.reactElement =>
  switch (typ) {
  | Empty => nodeBrown("empty")
  | Same(typ) =>
    <TreeView
      key="same"
      nodeLabel={nodeBrown("same")}
      collapsed=true
      child={typ->(toComponentT(~ctx, ~fmt))}
    />
  | Number(_)
  | String(_)
  | Boolean(_) => typ->constToString->nodeGreen
  | Object(d) =>
    let doEntry = (i, (lbl, styp)) =>
      <span
        key={string_of_int(i)}
        style=Color.(style(styp.p == P.zero ? grey : black))>
        <TreeView
          key={string_of_int(i)}
          nodeLabel={
            node(lbl)->(addDecorator(~styp, ~right=true, ~ctx, ~fmt))
          }
          collapsed=false
          child={styp->(toComponentStyp(~ctx, ~fmt))}
        />
      </span>;

    ReasonReact.array(Js.Dict.entries(d)->(Array.mapWithIndex(doEntry)));
  | Array(styp) when stypIsEmpty(styp) =>
    <span>
      {node("[")->(addDecorator(~styp, ~right=false, ~ctx, ~fmt))}
      {node("]")}
    </span>
  | Array(styp) =>
    <span style=Color.(style(styp.p == P.zero ? grey : black))>
      <TreeView
        nodeLabel={
          node("[")->(addDecorator(~styp, ~right=false, ~ctx, ~fmt))
        }
        collapsed=false
        child={styp->(toComponentStyp(~ctx, ~fmt))}
      />
      {node("]")}
    </span>
  | Union(styps) =>
    let doEntry = (i, styp) =>
      <TreeView
        key={string_of_int(i)}
        nodeLabel={
          node("u" ++ string_of_int(i + 1))
          ->(addDecorator(~styp, ~right=true, ~ctx, ~fmt))
        }
        collapsed=false
        child={styp->(toComponentStyp(~ctx, ~fmt))}
      />;

    <div>
      "union"->nodeBrown
      {styps->(List.mapWithIndex(doEntry))->List.toArray->ReasonReact.array}
    </div>;

  | Diff(t, lhs, rhs) =>
    let side = (~left) => {
      let lbl = left ? "lhs" : "rhs";
      let styp = left ? lhs : rhs;
      <TreeView
        key=lbl
        nodeLabel={lbl->nodeBrown}
        collapsed=false
        child={
          Styp.stypIsEmpty(styp)
            ? ReasonReact.null : styp->(toComponentStyp(~ctx, ~fmt=fmtDelta))
        }
      />;
    };
    <div className="row">
      <div className="column3"> {side(~left=true)} </div>
      <div className="column3">
        <TreeView
          nodeLabel={"common"->nodeBrown}
          collapsed=false
          child={t->(toComponentT(~ctx, ~fmt))}
        />
      </div>
      <div className="column3"> {side(~left=false)} </div>
    </div>;
  };

module Styp = {
  let component = ReasonReact.statelessComponent("Styp");
  let make = (~name, ~styp, ~fmt=fmtDefault, _) => {
    ...component,
    render: _ =>
      <TreeView
        nodeLabel={node(name)}
        collapsed=true
        child={styp->(toComponentStyp(~ctx=P.zero, ~fmt))}
      />,
  };
};

module Diff = {
  let component = ReasonReact.statelessComponent("Diff");
  let make = (~diff: Diff.t, _) => {
    ...component,
    render: _ =>
      <div>
        <div className="centerText">
          {ReasonReact.string @@ "Inferred Types"}
        </div>
        <div className="row">
          <div className="column2">
            <Styp styp={diff.styp1} name="styp1" />
          </div>
          <div className="column2">
            <Styp styp={diff.styp2} name="styp2" />
          </div>
        </div>
        <div className="centerText">
          {ReasonReact.string @@ "Common Part"}
        </div>
        <div> <Styp styp={diff.stypB} name="stypB" /> </div>
        <div className="centerText"> {ReasonReact.string @@ "Deltas"} </div>
        <div className="row">
          <div className="column2">
            <Styp name="stypA1" styp={diff.stypA1} fmt=fmtDelta />
          </div>
          <div className="column2">
            <Styp name="stypA2" styp={diff.stypA2} fmt=fmtDelta />
          </div>
        </div>
      </div>,
  };
};