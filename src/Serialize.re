/* wrap tags as they are not supported by json stringify */
let tagID = "tag320775503";
/* wrap undefined as it is not supported by json stringify */
let undefinedID = "undefined290180182";

[@bs.val] external isArray: 'a => bool = "Array.isArray";

let copy = (o_: 'a): 'a => {
  let o = o_->Obj.magic;
  isArray(o)
    ? Belt.Array.copy(o)->Obj.magic
    : Js.Obj.assign(Js.Obj.empty(), o)->Obj.magic;
};
let rec wrapTag = o_ => {
  let o = Obj.magic(o_);
  switch (Js.typeof(o)) {
  | "undefined" => [|undefinedID|]->Obj.magic
  | "object" when o === Js.null => o
  | "object" =>
    let o1 = copy(o);
    let keys = Js.Dict.keys(o1);
    for (i in 1 to Belt.Array.length(keys)) {
      let key = keys->(Belt.Array.getExn(i - 1));
      o1->(Js.Dict.set(key, o->(Js.Dict.get(key))->Obj.magic->wrapTag));
    };
    let tagOpt = Js.Dict.get(o, "tag");
    switch (tagOpt) {
    | None => o1
    | Some(tag) => [|tagID, tag, o1|]->Obj.magic
    };
  | _ => o
  };
};
let rec unwrapTag = o_ => {
  let o = Obj.magic(o_);
  switch (Js.typeof(o)) {
  | "object" when o === Js.null => o
  | "object" =>
    switch (isArray(o) ? o->Belt.Array.get(0) : None) {
    | Some(id) when id == undefinedID => Js.undefined->Obj.magic
    | Some(id) when id == tagID =>
      let tag = o->(Belt.Array.getExn(1));
      let innerObj = o->(Belt.Array.getExn(2));
      innerObj->(Js.Dict.set("tag", tag));
      unwrapKeys(innerObj);
      innerObj;
    | _ =>
      let o1 = copy(o);
      unwrapKeys(o1);
      o1;
    }
  | _ => o
  };
}
and unwrapKeys = o => {
  let keys = Js.Dict.keys(o);
  for (i in 1 to Array.length(keys)) {
    let key = keys->(Belt.Array.getExn(i - 1));
    o->(Js.Dict.set(key, o->(Js.Dict.get(key))->Obj.magic->unwrapTag));
  };
};
let toString = o => {
  let o1 = wrapTag(o);
  Js.Json.stringify(o1);
};
let fromString = s => {
  let o = Js.Json.parseExn(s);
  unwrapTag(o);
};