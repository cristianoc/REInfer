module Main = {
  let component = ReasonReact.statelessComponent("Page");

  let make = _children => {
    ...component,
    render: _self => <div> (Demo.test() |. UI.toComponent(~ctx=None)) </div>,
  };
};

ReactDOMRe.renderToElementWithId(<Main />, "main");