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
