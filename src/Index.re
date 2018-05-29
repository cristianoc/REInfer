module Main = {
  let component = ReasonReact.statelessComponent("Page");

  let make = (~message, _children) => {
    ...component,
    render: _self => <div> (ReasonReact.string(message)) </div>,
  };
};

ReactDOMRe.renderToElementWithId(
  <Main message="Check the console" />,
  "main",
);

Js.log("TODO");