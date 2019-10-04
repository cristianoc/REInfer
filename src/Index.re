open Belt;

module Main = {
  let component = ReasonReact.statelessComponent("Page");

  let make = _children => {
    ...component,
    render: _self => {
      let diffs = Demo.test();
      <div>
        {diffs
         ->List.toArray
         ->(
             Array.mapWithIndex((i, diff) =>
               <div key={i->string_of_int}>
                 <h3>
                   {ReasonReact.string("Sample " ++ string_of_int(i))}
                 </h3>
                 <UI.Diff diff />
               </div>
             )
           )
         ->ReasonReact.array}
      </div>;
    },
  };
};

ReactDOMRe.renderToElementWithId(<Main />, "main");