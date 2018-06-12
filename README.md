## Statistical Type Inference and Diff for sampled JSON data


## Run Project

```sh
npm install
npm start
# in another tab
npm run serve
# in another tab
code .
```

Then open the served page in the browser (use latest version).


### Example

```
val1:
{"x":"hello"}

val2:
{"x":null, "y":0}
```

The statistical type inferred will be
```
  {"x":(string?::1), "y":(number:: 1)} :: 2
```

which represented in % form is
```
  {"x":(string? 50%), "y":(number 50%)}
```

So `"x"` is nullable, and 50% of the time is present and not null.
Instead `"y"` is a number, and is present 50% of the time.

## References

* Tree view UI adapted from [react-treeview](https://github.com/chenglou/react-treeview).

* Abduction in shape analysis <https://dl.acm.org/citation.cfm?id=2049700>.

## License

This project is [MIT-licensed](./LICENSE.md).


# Do Not Read

Do not read past this point.

## Formalisation


### Values

```
val ::=
  123 |
  “abc” |
  true | false |
  null |
  obj |
  [ val1, …, valn ]

obj ::= { x1:val, …, xn:val }
```
### Types

Types: `t`

```
t ::=
  empty |
  number |
  string |
  boolean |
  t? |
  {x1:t, …, xn:t} |
  [ t ]
```

### Statistical Types


Statistical types: `styp`

```
o ::= opt(p) | notOpt
```

```
styp ::= (typ,o)::p
```

Abbreviation: write `typ?n::p` or `typ::p`.

```
typ ::=
  empty |
  number |
  string |
  boolean |
  {x1:styp1, …, xn:stypn} |
  [styp]
```

### Type checking for Types


Type checking for `t`: ` |- val : t`

```
|- 123 : number
```

```
|- “abc” : string
```

```
|- true : boolean  |- false : boolean
```

```
|- null : t?
```

```
|- val1:t1  …  |- valn:tn
————————————————————————————————————————————————
|- {x1:val1, …, xn:valn} : {x1:t1, …, xn:tn}
```

```
|- [] : [empty]
```

```
|- val1:t  …  |- valn:t  (n>0)
——————————————————————————————————
|- [val1, …, valn] : [t]
```


### Erasure of Statistical Types

Erasure: `|- |styp| = t`

```
|- |typ| = t
———————————————————
|- |(typ,o)::p| = t
```

```
|- |empty| = empty
```

```
|- |number| = number
```

```
|- |string| = string
```

```
|- |boolean| = boolean
```

```
|- |styp1| = t1 … |- |stypn| = tn
————————————————————————————————————————————————————
|- |{x1:styp1, …, xn:stypn}| = {x1:t1, …, xn:tn}
```

```
|- |styp| = t
———————————————————
|- |[styp]| = [t]
```

### Type checking for Statistical Types

Type checking for styp:  `|- val : styp`


```
|- 123 : number::1
```

```
|- “abc” : string::1
```

```
|- true : boolean::1  |- false : boolean::1
```

```
———————————————————-
|- null : (typ?1 :: 1)
```

```
            |- val1:styp1  …  |- valn:stypn
—————————————————————————————————————————————————————
|- {x1:val1, …, xn:valn} : {x1:styp1, …, xn:stypn}::1
```

```
|- [] : [empty]
```

```
|- val1:styp1  …  |- valn:stypn  |- styp1 + … + stypn = styp  (n>0)
———————————————————————————————————————————————————————————————————
                  |- [val1, …, valn] : [styp]
```

weakening nullable:

```
 |- val : (typ::p)
——————————————————
|- val : (typ?0 :: p)
```

weakening obj:

```
|- val : ({x1:styp1, …, xn:stypn}, o) :: p
———————————————————————————————————————————————————————
|- val : ({x1:styp1, …, xn:stypn, x0:(typ :: 0)}, o) :: p
```


### Sum of Statistical Types

Sum operations `|- styp1 + styp2 = styp` and `|- typ1 + typ2 = typ` and `|- o1 + o2 = o`

Notice this defines a partial commutative monoid.

```
|- typ1+typ2=typ  |-o1+o2=o  p1+p2=p
——————————————————————————————————————————————
|- (typ1,o1)::p1 + (typ2,o2)::p2 = (typ::o)::p
```

```
|- notOpt+o = o+notOpt = o  |- opt(p1)+opt(p2) = opt(p1+p2)
```


```
|- empty + typ = typ + empty = typ
```

```
|- number + number = number
```

```
|- string + string = string
```

```
|- boolean + boolean = boolean
```

```
|- styp1 + styp1’ = styp1’’ … |- stypn + stypn’ = stypn’’
|- o’’ = o + o’
—————————————————————————————————————————————————————————
|- ({x1:styp1, …, xn:stypn}, o) :: p  +
   ({x1:styp1’, …, xn:stypn’}, o’) :: p’  =
   ({x1:styp1’’, …, xn:stypn’’}, o’’) :: p’’
```

```
  |- styp1 + styp2 = styp
————————————————————————————
|- [styp1::p1] + [styp2::p2]
```


### Inference of Statistical Types from value samples

Statistical type inference: `|- val1, …, valn -> styp`

```
|- [val1, …, valn] : [styp]
———————————————————————————
 |- val1, …, valn -> styp
```

### Abduction for Statistical Types

Abduction: `|- styp1 + <stypA> = styp2` and `|- typ1 + <typA> = typ2` and `|- o1 + <oA> = o2`.

Want smallest solution w.r.t. `<=` where `styp1 <= styp2` if there is `styp` such that `|- styp1 + styp = styp2`.

Abduction computes the smallest representation of the difference between statistical types.

(Note negation corresponding to + does not exist)


```
|- typ1 + <typA> = typ2  |- o1 + <oA> = o2  |- p1 + <pA> = p2
—————————————————————————————————————————————————————————————
|- (typ1,o1)::p2 + <(typA,oA)::pA> = (typ2,o2)::p2
```

```
|- notOpt + <notOpt> = notOpt
```

```
|- notOpt + <opt(p)> = opt(p) 
```

```
|- opt(p) + <notOpt> = opt(p)
```

```
             p2 > p1
-----------------------------------
|- opt(p1) + <opt(p2-p1)> = opt(p2)
```


```
|- empty + <typ> = typ
```

```
|- number + <empty> = number
```

```
|- string + <empty> = string
```

```
|- boolean + <empty> = boolean
```

```
|- {G1} + <{GA}> = {G2}  |- styp1 + <stypA> = styp2
———————————————————————————————————————————————————
|- {G1, x:styp1} + <{GA, x:stypA}> = {G2, x:styp2}
```


```
|- {G1} + <{GA}> = {G2}  (x not in G1)
—————————————————————————————————————————
|- {G1} + <{GA, x:styp2}> = {G2, x:styp2}
```


```
|- {G1} + <{GA}> = {}  |- typ1 + <typA> = typ1  |- o1 + <oA> = notOpt
—————————————————————————————————————————————————————————————————————
|- {G1, x:((typ1,o1)::p1)} + <{GA, x:((typA,oA)::(-p1))}> = {}
```

```
|- typ1 + <{G, x:(empty, notOpt)::0> = typ2
———————————————————————————————————————
|- typ1 + <{G}> = typ2
```

```
|- typ1 + <{}> = typ2
————————————————————
|- typ1 + <empty> = typ2
```

```
|- styp1 + <stypA> = styp2
————————————————————————————————
|- [styp1] + <[stypA]> = [styp2]
```

```
|- typ1 + <[(empty, notOpt)::0]> = typ2
———————————————————————————————————
|- typ1 + <empty> = typ2
```


### Diff for Statistical Types

Abduction: `|- <stypA1,stypA2> + <stypB> = styp1,styp2`
and `|- <typA1,typA2> + <typB> = typ1,typ2` and `|- <oA1,oA2> + <oB> = o1,o2`.



Want largest solution w.r.t. `<=` for the `B` part, and smallest for the `A1` and `A2` parts, where `styp1 <= styp2` if there is `styp` such that `|- styp1 + styp = styp2`.


Let `stypEmpty = (empty, notOpt, 0)`.


```
|- <typA1,typA2> + <typB> = (typ1,typ2)  |- <oA1,oA2> + <oB> = o1,o2
pB = min(p1,p2)  pA1 = p1-pB  pA2 = p2-pB
stypA1 = (typA1,oA1)::pA1  stypA2 = (typA2,oA2)::pA2
stypB = (typB,oB)::pB
————————————————————————————————————————————————————————————————————
|- <stypA1,stypA2> + <stypB> = (typ1,o1)::p1,(typ2,o2)::p2
```


```
|- <notOpt,o2> + <notOpt> = notOpt,o2
```

```
|- <o1,notOpt> + <notOpt> = o1,notOpt
```

```
|- <notOpt,notOpt> + <opt(p)> = opt(p),opt(p)
```

```
                     p1 < p2
————————————————————————————————————————————————————
|- <notOpt,opt(p2-p1)> + <opt(p1)> = opt(p1),opt(p2)
```

```
                     p2 < p1
————————————————————————————————————————————————————
|- <opt(p1-p2),notOpt> + <opt(p2)> = opt(p1),opt(p2)
```


```
|- <empty,typ2> + <empty> = empty,typ2
```

```
|- <typ1,empty> + <empty> = typ1,empty
```

```
|- <empty,empty> + <number> = number,number
```

```
|- <empty,empty> + <string> = string,string
```

```
|- <empty,empty> + <boolean> = boolean,boolean
```

```
|- <{GA1},{GA2}> + <{GB}> = {G1},{G2}
|- <stypA1,stypA2> + <stypB> = styp1,styp2
typA1 = stypA1==stypEmpty ? {GA1,x:stypA1} : {GA1}
typA2 = stypA2==stypEmpty ? {GA2,x:stypA2} : {GA2}
typB = {GB,x:stypB}
——————————————————————————————————————————————————————
|- <typA1,typA2> + <typB> = {G1,x:styp1},{G2,x2:styp2}
```


```
|- <{GA1},{GA2}> + <{GB}> = {G1},{G2}  (x not in G2)
typA1 = styp1==stypEmpty ? {GA1,x:styp1} : {GA1}
————————————————————————————————————————————————————
|- <typA1,{GA2}> + <{GB}> = {G1,x:styp1},{G2}
```


```
|- <{GA1},{GA2}> + <{GB}> = {G1},{G2}  (x not in G1)
typA2 = styp2==stypEmpty ? {GA2,x:styp2} : {GA2}
————————————————————————————————————————————————————
|- <{GA1},tA2> + <{GB}> = {G1},{G2,x:styp2}
```

```
|- <{},typA2> + <typB> = typ1,typ2
—————————————————————————————————————
|- <empty,typA2> + <typB> = typ1,typ2
```

```
|- <typA1,{}> + <typB> = typ1,typ2
—————————————————————————————————————
|- <typA1,empty> + <typB> = typ1,typ2
```

```
|- <stypA1,stypA2> + <stypB> = styp1,styp2
————————————————————————————————————————————————————
|- <[stypA1],[stypA2]> + <[stypB]> = [styp1],[styp2]
```

```
|- <[stypEmpty], typA2> + <typB> = typ1,typ2
————————————————————————————————————————————
|- <empty, typA2> + <typB> = typ1,typ2
```

```
|- <typA1, [stypEmpty]> + <typB> = typ1,typ2
————————————————————————————————————————————
|- <typA1, empty> + <typB> = typ1,typ2
```

### Extension: Union Types

```
stypU ::= styp1 | ... | stypn

typ += union(stypU)
```

Write ```typ1 # typ2``` when there is no `typ` such that `|- typ1 + typ2 = typ`, with the corresponding extension ```styp1 # styp2```.

The sum of `stypU` written `|- stypU1 + stypU2 = stypU` is defined below.
The conversion `|- u(styp) = stypU` is also defined below.


```
styp = (typ:o)::p
typ not of the form u(stypU)
————————————————————————————
|- u(styp) = styp
```

```
styp = (typ:o)::p
typ = u(stypU)
——————————————————
|- u(styp) = stypU
```

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
(typ1 # typ2)
u(styp1) = stypU1  u(styp2) = stypU2
|- stypU1 U stypU2 = stypU  |-o1+o2=o  p1+p2=p
——————————————————————————————————————————————
|- styp1 + styp2 = (union(stypU)::o)::p
```

```
 |- styp1 + styp2 = styp  |- stypU1 + stypU2 = stypU
———————————————————————————————————————————————————————
|- (styp1 | stypU1) + (styp2 | stypU2) = (styp | stypU)
```

```
stypU1 # stypU2 (for all pairs)
—————————————————————————————————————————————————————
|- stypU1 + stypU2 = stypU1 | stypU2
```

Diff is extended as follows:

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
typ1 = union(stypU1)
typ2 not of the form union(-)
u(styp2) = stypU2
styp2' = (union(stypU2),o2)::p2
|- <stypA1,stypA2> + <stypB> = styp1,styp2'
————————————————————————————————————————————
|- <stypA1,stypA2> + <stypB> = styp1,styp2
```

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
typ1 not of the form union(-)
typ2 = union(stypU2)
u(styp1) = stypU1
styp1' = (union(stypU1),o1)::p1
|- <stypA1,stypA2> + <stypB> = styp1',styp2
————————————————————————————————————————————
|- <stypA1,stypA2> + <stypB> = styp1,styp2
```

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
typ1 = union(stypU1)  typ2 = union(stypU2)
|- <oA1,oA2> + <oB> = o1,o2
|- <pA1,pA2> + <pB> = p1,p2
|- <stypUA1,stypUA2> + <stypUB> = stypU1,stypU2
stypA1 = (union(stypUA1),oA1)::pA1  stypA2 = (union(stypUA2),oA2)::pA2
stypB = (union(stypUB),oB)::pB
——————————————————————————————————————————————————————————————————————
|- <stypA1,stypA2> + <stypB> = styp1,styp2
```

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
|- typ1 + typ2 = typ
|- <stypA1,stypA2> + <stypB> = styp1,styp2
|- <stypUA1,stypUA2> + <stypUB> = stypU1,stypU2
stupUA1' = stypA1 | stypUA1  stupUA2' = stypA2 | stypUA2
stupUB' = stypB | stypUB
——————————————————————————————————————————————————————————————————————
|- <stypUA1',stypUA2'> + <stypUB'> = (styp1 | stypU1),(styp2 | stypU2)
```


```
stypU1 # stypU2 (for all pairs)
——————————————————————————————————————————————————————————————————————
|- <stypU1,stypU2> + <empty> = stypU1,stypU2
```



