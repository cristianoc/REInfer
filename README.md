## Statistical Type Inference and Abduction for sampled JSON data

## Run Project

```sh
npm install
npm start
# in another tab
npm run serve
# in another tab
code .
```

Then open the served page in **Chrome**. Keep Chrome developer tools always open, and select **Disable cache** in the **Network** settings.

## Build for Production

```sh
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version.

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.

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

Types: `typ`

```
typ ::=
  empty |
  number |
  string |
  boolean |
  typ? |
  {x1:typ, …, xn:typ} |
  [ typ ]
```

### Statistical Types


Statistical types: `styp`

```
o ::= opt | notOpt
```

```
styp ::= (t,o)::p
```

Abbreviation: write `t?::p` or `t::p`.

```
t ::=
  empty |
  number |
  string |
  boolean |
  {x1:styp1, …, xn:stypn} |
  [styp]
```

### Type checking for Types


Type checking for `typ:  |- val : typ`

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
|- null : typ?
```

```
|- val1:typ1  …  |- valn:typn
————————————————————————————————————————————————
|- {x1:val1, …, xn:valn} : {x1:typ1, …, xn:typn}
```

```
|- [] : [empty]
```

```
|- val1:typ  …  |- valn:typ  (n>0)
——————————————————————————————————
|- [val1, …, valn] : [typ::n]
```


### Erasure of Statistical Types

Erasure: `|- |styp| = typ`

```
|- |t| = typ
———————————————————
|- |(t,o)::p| = typ
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
|- |styp1| = typ1 … |- |stypn| = typn
————————————————————————————————————————————————————
|- |{x1:styp1, …, xn:stypn}| = {x1:typ1, …, xn:typn}
```

```
|- |styp| = typ
———————————————————
|- |[styp]| = [typ]
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
———————————————————
|- null : (t? :: 0)
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
 |- val : (t::p)
——————————————————
|- val : (t? :: p)
```

weakening obj:

```
|- val : ({x1:styp1, …, xn:stypn}, o) :: p
———————————————————————————————————————————————————————
|- val : ({x1:styp1, …, xn:stypn, x0:(t :: 0)}, o) :: p
```


### Sum of Statistical Types

Combining `styp: |- styp1 + styp2 = styp` and `|- t1 + t2 = t`

```
|- t1+t2=t  |-o1+o2=o  p1+p2=p
————————————————————————————————————————
|- (t1,o1)::p1 + (t2,o2)::p2 = (t::o)::p
```

```
|- notOpt+o = o+notOpt = o  |- opt+o = o+opt = opt
```


```
|- empty + t = t + empty = t
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
o’’=(o==opt ? o : o’)
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

Abduction: `|- styp1 + <stypA> = styp2` and `|- t1 + <tA> = t2`

Want smallest solution w.r.t. `<=`
E.g. `notOpt < Opt`  `empty <= t`  subset on `Gamma`

Abduction computes the smallest representation of the difference between statistical types.

(Note negation corresponding to + does not exist)


```
|- o1 + <oA> = o2  |- t1 + <tA> = t2  |- p1 + <pA> = p2
———————————————————————————————————————————————————————
|- (t1,o1)::p2 + <(tA,oA)::pA> = (t2,o2)::p2
```

```
|- notOpt + <notOpt> = notOpt
```

```
|- notOpt + <opt> = opt 
```

```
|- opt + <notOpt> = opt
```

```
|- empty + <t> = t
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
|- {G1} + <{GA}> = {}  |- t1 + <tA> = t1  |- o1 + <oA> = notOpt
———————————————————————————————————————————————————————————————
|- {G1, x:((t1,o1)::p1)} + <{GA, x:((tA,oA)::(-p1))}> = {}
```

```
|- t1 + <{G, x:(empty, notOpt)::0> = t2
———————————————————————————————————————
|- t1 + <{G}> = t2
```

```
|- t1 + <{}> = t2
————————————————————
|- t1 + <empty> = t2
```

```
|- styp1 + <stypA> = styp2
————————————————————————————————
|- [styp1] + <[stypA]> = [styp2]
```

```
|- t1 + <[(empty, notOpt)::0]> = t2
———————————————————————————————————
|- t1 + <empty> = t2
```


### Diff for Statistical Types

Abduction: `|- <stypA1,stypA2> + <stypB> = styp1,styp2`
and `|- <tA1,tA2> + <tB> = t1,t2`

Want smallest solution w.r.t. `<=` for the `A1`, `A2` part, and largest for the `B` part.

E.g. `notOpt < Opt`, `empty <= t` and subset on `Gamma`.

Let `stypEmpty = (empty, notOpt, 0)`.


```
|- <tA1,tA2> + <tB> = (t1,t2)  |- <oA1,oA2> + <oB> = o1,o2
pB = min(p1,p2)  pA1 = p1-pB  pA2 = p2-pB
stypA1 = (tA1,oA1)::pA1  stypA2 = (tA2,oA2)::pA2
stypB = (tB,oB)::pB
——————————————————————————————————————————————————————————
|- <stypA1,stypA2> + <stypB> = (t1,o1)::p1,(t2,o2)::p2
```


```
|- <notOpt,o2> + <notOpt> = notOpt,o2
```

```
|- <o1,notOpt> + <notOpt> = o1,notOpt
```

```
|- <notOpt,notOpt> + <opt> = opt,opt
```

```
|- <empty,t2> + <empty> = empty,t2
```

```
|- <t1,empty> + <empty> = t1,empty
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
tA1 = stypA1==stypEmpty ? {GA1,x:stypA1} : {GA1}
tA2 = stypA2==stypEmpty ? {GA2,x:stypA2} : {GA2}
tAB = {GB,x:stypB}
————————————————————————————————————————————————
|- <tA1,tA2> + <tB> = {G1,x:styp1},{G2,x2:styp2}
```


```
|- <{GA1},{GA2}> + <{GB}> = {G1},{G2}  (x not in G2)
tA1 = styp1==stypEmpty ? {GA1,x:styp1} : {GA1}
————————————————————————————————————————————————————
|- <tA1,{GA2}> + <{GB}> = {G1,x:styp1},{G2}
```


```
|- <{GA1},{GA2}> + <{GB}> = {G1},{G2}  (x not in G1)
tA2 = styp2==stypEmpty ? {GA2,x:styp2} : {GA2}
————————————————————————————————————————————————————
|- <{GA1},tA2> + <{GB}> = {G1},{G2,x:styp2}
```

```
|- <{},tA2> + <tB> = t1,t2
—————————————————————————————
|- <empty,tA2> + <tB> = t1,t2
```

```
|- <tA1,{}> + <tB> = t1,t2
—————————————————————————————
|- <tA1,empty> + <tB> = t1,t2
```

```
|- <stypA1,stypA2> + <stypB> = styp1,styp2
————————————————————————————————————————————————————
|- <[stypA1],[stypA2]> + <[stypB]> = [styp1],[styp2]
```

```
|- <[stypEmpty], tA2> + <tB> = t1,t2
————————————————————————————————————
|- <empty, tA2> + <tB> = t1,t2
```

```
|- <tA1, [stypEmpty]> + <tB> = t1,t2
————————————————————————————————————
|- <tA1, empty> + <tB> = t1,t2
```