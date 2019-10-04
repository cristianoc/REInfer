[@react.component]
let make = (~message) => {
  <div onClick={_event => Js.log("clicked!")}>
    {React.string(message)}
  </div>;
};