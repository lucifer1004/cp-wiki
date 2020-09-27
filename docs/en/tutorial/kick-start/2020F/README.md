# Google Kick Start 2020 Round D Tutorial

## Problem A - [ATM Queue](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4ed8)

It takes a person $\left\lceil\frac{A_i}{X}\right\rceil$ rounds to withdraw $A_i$. So we can turn $A_i$ into pairs $(\left\lceil\frac{A_i}{X}\right\rceil, i)$, then sort the pairs to get the final sequence.

Total time complexity is $O(N\log N)$ since we need to sort.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/a.cpp

:::

## Problem B - [Metal Harvest](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4b8b)

First we need to sort all the time segments. Since there are no overlaps, we then handle them one by one. During the process, we keep record of the right endpoint of the last coverage, $R$.

For each segment, if it can be covered by the last coverage, we do nothing. Otherwise, we will need to cover a length of $r_i-\max(l_i,R)$, which requires $\left\lceil\frac{r_i-\max(l_i,R)}{K}\right\rceil$ robots. After adding those robots, we update $R$ with $\max(l_i, R)+K\cdot\left\lceil\frac{r_i-\max(l_i,R)}{K}\right\rceil$.

Total time complexity is $O(N\log N)$ since we need to sort.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/b.cpp

:::

## Problem C - [Painters' Duel](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f47fb)

The museum can be easily represented by a graph with $S^2$ nodes, and each node has at most $3$ edges.

The hardest point is to represent the current state of the museum. Since there are at most $6^2=36$ rooms, a $64$-bit integer is just enough. We can use the last $40$ bits for rooms, $[41,50]$ for person $B$ (who moves second), and $[51,60]$ for person $A$ (who moves first). A room bit is set if it is under construction or it has been painted in previous steps.

Then we can do DFS.

There are in total three cases for each step:

- $A$ can move.
- $A$ cannot move while $B$ can move.
- Both people cannot move.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/c.cpp

:::

## Problem D - [Yeetzhee](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4dea)

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/d.cpp

:::

<Utterances />
