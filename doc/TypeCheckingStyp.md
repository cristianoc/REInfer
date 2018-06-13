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
