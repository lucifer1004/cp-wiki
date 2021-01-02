# AtCoder Beginner Contest 187 题解

[视频题解](https://www.youtube.com/watch?v=pcPlZAiC3HY)

<iframe width="560" height="315" src="https://www.youtube.com/embed/pcPlZAiC3HY" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A - [Large Digits](https://atcoder.jp/contests/abc187/tasks/abc187_a)

按要求求出两个数的每位之和，进行比较即可。

时间复杂度$\mathcal{O}(\log(AB))$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC187/src/a.py

:::

## Problem B - [Gentle Pairs](https://atcoder.jp/contests/abc187/tasks/abc187_b)

枚举所有点对求斜率。

时间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC187/src/b.py

:::

## Problem C - [1-SAT](https://atcoder.jp/contests/abc187/tasks/abc187_c)

用两个HashSet分别存储不带`!`和带`!`的字符串的纯字符部分，求两个HashSet的交集。若有交集，则输出其中任意一个字符串；否则按要求输出`satisfiable`。

时间复杂度$\mathcal{O}(N)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC187/src/c.cpp

:::

## Problem D - [Choose Me](https://atcoder.jp/contests/abc187/tasks/abc187_d)

将所有城镇按照$2A_i+B_i$降序排列，然后贪心选取即可。

时间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC187/src/d.cpp

:::

## Problem E - [Through Path](https://atcoder.jp/contests/abc187/tasks/abc187_e)

采用类似线段树中“Lazy propagation”的方法，将变动的数值存在子树的树根处。如果某一修改操作是对除某一子树以外的节点进行，则全局加上$x$，同时对该子树加上$-x$。最后递归求值即可。

时间复杂度$\mathcal{O}(N+Q)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC187/src/e.cpp

:::

## Problem F - [Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f)

预处理求出每一子集能否由单个连通分量组成。然后进行子集动态规划。注意使用枚举子集的优化，将这部分的时间复杂度从$\mathcal{O}(4^N)$降低到$\mathcal{O}(3^N)$。

时间复杂度$\mathcal{O}(N^2\cdot2^N+3^N)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC187/src/f.cpp

:::

<Utterances />
