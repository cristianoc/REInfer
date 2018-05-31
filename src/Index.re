module Main = {
  let component = ReasonReact.statelessComponent("Page");

  let make = _children => {
    ...component,
    render: _self => {
      let diff = Demo.test();
      <div> <UI.Diff diff /> </div>;
    },
  };
};

ReactDOMRe.renderToElementWithId(<Main />, "main");