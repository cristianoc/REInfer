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
