# AtCoder Beginner Contest 185 Tutorial

See the [Video Tutorial](https://www.youtube.com/watch?v=sq-A_1kBvPQ).

<iframe width="560" height="315" src="https://www.youtube.com/embed/sq-A_1kBvPQ" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

And here are the solutions.

## Problem A - [ABC Preparation](https://atcoder.jp/contests/abc185/tasks/abc185_a)

Just output the minimum of the four numbers.

Time complexity is $\mathcal{O}(1)$。

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC185/src/a.py

:::

## Problem B - [Smartphone Addiction](https://atcoder.jp/contests/abc185/tasks/abc185_b)

Simulation.

Time complexity is $\mathcal{O}(M)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC185/src/b.py

:::

## Problem C - [Duodecim Ferra](https://atcoder.jp/contests/abc185/tasks/abc185_c)

The answer is ${L-1}\choose11$.

Time complexity is $\mathcal{O}(1)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC185/src/c.py

:::

## Problem D - [Stamp](https://atcoder.jp/contests/abc185/tasks/abc185_d)

Find all white segments. The length of the shortest segment will be the optimal value for $k$. Then just calculate $\sum\lceil\frac{l_i}{k}\rceil$, where $l_i$ is the length of the $i$-th white segment.

Time complexity is $\mathcal{O}(M)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC185/src/d.py

:::

## Problem E - [Sequence Matching](https://atcoder.jp/contests/abc185/tasks/abc185_e)

Similar to the Longest Common Subsequence problem. Consider transitions from $dp[i-1][j],dp[i][j-1],dp[i-1][j-1]$.

Time complexity is $\mathcal{O}(NM)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC185/src/e.py

:::

## Problem F - [Range Xor Query](https://atcoder.jp/contests/abc185/tasks/abc185_f)

A typical segment tree with single update and range query. Just use the template in AC-Library.

Time complexity is $\mathcal{O}((N+Q)\log N)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC185/src/f.cpp

:::

<Utterances />
