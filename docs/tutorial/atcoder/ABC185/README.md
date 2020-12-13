# AtCoder Beginner Contest 185 题解

[视频题解](https://www.youtube.com/watch?v=sq-A_1kBvPQ)

<iframe width="560" height="315" src="https://www.youtube.com/embed/sq-A_1kBvPQ" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A - [ABC Preparation](https://atcoder.jp/contests/abc185/tasks/abc185_a)

直接输出四个数的最小值。

时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC185/src/a.py

:::

## Problem B - [Smartphone Addiction](https://atcoder.jp/contests/abc185/tasks/abc185_b)

模拟。

时间复杂度$\mathcal{O}(M)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC185/src/b.py

:::

## Problem C - [Duodecim Ferra](https://atcoder.jp/contests/abc185/tasks/abc185_c)

答案为${L-1}\choose11$。

时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC185/src/c.py

:::

## Problem D - [Stamp](https://atcoder.jp/contests/abc185/tasks/abc185_d)

计算出所有白色区间。最短的区间长度即为$k$的最佳取值，之后计算需要的邮票总数即可。

时间复杂度$\mathcal{O}(M)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC185/src/d.py

:::

## Problem E - [Sequence Matching](https://atcoder.jp/contests/abc185/tasks/abc185_e)

类似于最长公共子序列。考虑$dp[i-1][j],dp[i][j-1],dp[i-1][j-1]$三种转移。

时间复杂度$\mathcal{O}(NM)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC185/src/e.py

:::

## Problem F - [Range Xor Query](https://atcoder.jp/contests/abc185/tasks/abc185_f)

线段树，单点更新，区间查询。直接用AC-Library模板即可。

时间复杂度$\mathcal{O}((N+Q)\log N)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC185/src/f.cpp

:::

<Utterances />
