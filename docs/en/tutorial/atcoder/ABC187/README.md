# AtCoder Beginner Contest 187 Editorial

[Video Editorial](https://www.youtube.com/watch?v=pcPlZAiC3HY)

<iframe width="560" height="315" src="https://www.youtube.com/embed/pcPlZAiC3HY" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A - [Large Digits](https://atcoder.jp/contests/abc187/tasks/abc187_a)

Calculate the sum of digits and compare.

Time complexity is $\mathcal{O}(\log(AB))$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC187/src/a.py

:::

## Problem B - [Gentle Pairs](https://atcoder.jp/contests/abc187/tasks/abc187_b)

Enumerate all pairs and calculate the slope.

Time complexity is $\mathcal{O}(N^2)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC187/src/b.py

:::

## Problem C - [1-SAT](https://atcoder.jp/contests/abc187/tasks/abc187_c)

Use two HashSets to store strings with `!` and without `!` separately. If their intersection is non-empty, we can output any string in it, otherwise we output `satisfiable`.

Time complexity is $\mathcal{O}(N)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC187/src/c.cpp

:::

## Problem D - [Choose Me](https://atcoder.jp/contests/abc187/tasks/abc187_d)

Sort all the towns by $2A_i+B_i$ in the descending order, then make speeches greedily.

Time complexity is $\mathcal{O}(N\log N)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC187/src/d.cpp

:::

## Problem E - [Through Path](https://atcoder.jp/contests/abc187/tasks/abc187_e)

Store the changes lazily at the root of each subtree. If in one operation, the nodes to be modified do not form a subtree, then they must be the compliment of a subtree. In this case, we add $x$ to all nodes (the value is stored in a global variable), and add $-x$ to the subtree. After all modifications, we can get the value of each node recursively.

Time complexity is $\mathcal{O}(N+Q)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC187/src/e.cpp

:::

## Problem F - [Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f)

Precalculate if a subset can be made up of a single connected components, then do a subset DP.

Time complexity is $\mathcal{O}(N^2\cdot2^N+3^N)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC187/src/f.cpp

:::

<Utterances />
