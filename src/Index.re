module Main = {
  [@react.component]
  let make = () => {
    let diffs = Demo.test();
    <div>
      {diffs
       ->Belt_List.toArray
       ->(
           Belt.Array.mapWithIndex((i, diff) =>
             <div key={i->string_of_int}>
               <h3> {React.string("Sample " ++ string_of_int(i))} </h3>
               <UI.Diff diff />
             </div>
           )
         )
       ->React.array}
    </div>;
  };
};

ReactDOMRe.renderToElementWithId(<Main />, "main");