# AtCoder Beginner Contest 177 题解

## Problem A - [Don't be late](https://atcoder.jp/contests/abc177/tasks/abc177_a)

### 题目描述

有$T$分钟，每分钟能跑$S$米，能不能到一个距离为$D$米的地方？

### 题解

比较能跑的最远距离和需要跑的距离即可。

::: details 参考代码（Python）

<<<@/docs/tutorial/atcoder/ABC177/src/a.py

:::

## Problem B - [Substring](https://atcoder.jp/contests/abc177/tasks/abc177_b)

### 题目描述

给定两个字符串$S$和$T$（$|T|\leq|S|\leq1000$），问至少需要修改$T$中的几个字母，可以将$T$变为$S$的子串？

### 题解

数据范围很小，枚举即可。

::: details 参考代码（Python）

<<<@/docs/tutorial/atcoder/ABC177/src/b.py

:::

## Problem C - [Sum of product of pairs](https://atcoder.jp/contests/abc177/tasks/abc177_c)

### 题目描述

求$\prod_{i<j} a_ia_j\mod 1000000007$ 。

### 题解

$\prod_{i<j} a_ia_j=\frac{\sum a_i(\sum a_j-a_i)}{2}$，注意取模意义下除以$2$要变为乘$2$的逆元。

::: details 参考代码（Python）

<<<@/docs/tutorial/atcoder/ABC177/src/c.py

:::

## Problem D - [Friends](https://atcoder.jp/contests/abc177/tasks/abc177_d)

### 题目描述

有$N$（$N\leq2\times10^5$）个人和$M$（$M\leq2\times10^5$）对朋友关系，朋友关系可以传递，求要让每个分组中任意两人都不是朋友，最少要分多少组？

### 题解

并查集找出最大的连通分量即为答案。

::: details 参考代码（C++）

<<<@/docs/tutorial/atcoder/ABC177/src/d.cpp

:::

## Problem E - [Coprime](https://atcoder.jp/contests/abc177/tasks/abc177_e)

### 题目描述

有$N$（$N\leq10^6$）个数，这些数都不超过$10^6$。如果这些数两两互质，输出`pairwise coprime`；如果这些数互质，输出`setwise coprime`，否则输出`not coprime`。

### 题解

质因数分解，统计含有每个质因子的数的个数，然后求出最大的个数。如果这个值为$1$，说明两两互质；如果这个值小于$N$，说明总体互质。

::: details 参考代码（C++）

<<<@/docs/tutorial/atcoder/ABC177/src/e.cpp

:::

## Problem F - [I hate Shortest Path Problem](https://atcoder.jp/contests/abc177/tasks/abc177_f)

### 题目描述

有一个$H+1$（$H\leq2\times10^5$）行$W$（$W\leq2\times10^5$）列的方阵，只能向下或向右走。前$H$行每行从$A_i$到$B_i$不能向下走。求出走到第$2,3,\cdots,H+1$行所需要的最短步数。

### 题解

使用线段树求解。对于某一行，如果这行不能向下走的区间是$[L,R]$，则：

- 对$[1,L-1]$和$[R+1,W]$整段加一
- $[L,R]$区间更新为$f(L-1)+i-L+1$（因为这个区间必须从$L-1$这个位置走过来）

需要查询的是区间最小值。

实现以上两种操作和一种查询即可。

::: details 参考代码（C++）

<<<@/docs/tutorial/atcoder/ABC177/src/f.cpp

:::

::: tip 小贴士

如果题目改为可以向左或向右走，只需要对数据结构稍作修改即可。

:::

::: details 参考代码（C++）

<<<@/docs/tutorial/atcoder/ABC177/src/f2.cpp

:::

<Utterances />
