```
styp = (typ:o)::p
typ not of the form union(stypU)
————————————————————————————————
|- u(styp) = styp
```

```
styp = (typ:o)::p
typ = union(stypU)
——————————————————
|- u(styp) = stypU
```

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
(typ1 # typ2)
u(styp1) = stypU1  u(styp2) = stypU2
|- stypU1 + stypU2 = stypU  |-o1+o2=o  p1+p2=p
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
stypU2 = styp2
styp2' = (union(stypU2),o2)::p2
|- <stypA1,stypA2> + <stypB> = styp1,styp2'
————————————————————————————————————————————
|- <stypA1,stypA2> + <stypB> = styp1,styp2
```

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
typ1 not of the form union(-)
typ2 = union(stypU2)
stypU1 = styp1
styp1' = (union(stypU1),o1)::p1
|- <stypA1,stypA2> + <stypB> = styp1',styp2
————————————————————————————————————————————
|- <stypA1,stypA2> + <stypB> = styp1,styp2
```

```
styp1 = (typ1,o1)::p1  styp2 = (typ2,o2)::p2
typ1 = union(stypU1)  typ2 = union(stypU2)
|- <stypUA1,stypUA2> + <stypUB> = stypU1,stypU2
oA1 = sumO(stypUA1)  pA1 = sumP(stypUA1)
oA2 = sumO(stypUA2)  pA2 = sumP(stypUA2)
oB = sumO(stypUB)  pB = sumP(stypUB)
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
stypUA1' = stypA1 | stypUA1  stypUA2' = stypA2 | stypUA2
stypUB' = stypB | stypUB
——————————————————————————————————————————————————————————————————————
|- <stypUA1',stypUA2'> + <stypUB'> = (styp1 | stypU1),(styp2 | stypU2)
```

```
stypU1 # stypU2 (for all pairs)
——————————————————————————————————————————————————————————————————————
|- <stypU1,stypU2> + <empty> = stypU1,stypU2
```
