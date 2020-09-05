# SnarkNews Summer Series 2020 Round 2 题解

## Problem B - [Sequence Analysis](https://contest.yandex.com/snss2020/contest/19321/problems/B/)

### 题目描述

给定两个序列$A$和$B$，求其公共子序列的总数$\mod 998244353$。

### 题解

动态规划。如果$A_i\neq B_j$，$dp[i][j]=dp[i][j-1]+dp[i-1][j]-dp[i-1][j-1]$（容斥原理），如果$A_i=B_j$，还要额外加上$dp[i-1][j-1]+1$。

::: details 参考代码（C++）

<<< @/docs/tutorial/others/SNSS2020-R2/src/b.cpp

:::

## Problem D - [Meet Readers](https://contest.yandex.com/snss2020/contest/19321/problems/D/)

### 题目描述

有$N$个作家，每个人可以在$[l_i,r_i)$的时间范围内参加会议，参会的不满度是$W_i$。问，要使得$[L,R)$的范围内都有人，并使得不满度的最大值最小的情况下，应该怎么安排（不要求作家的人数最少）。

### 题解

二分答案。判断可行性时，将作家按照时间段排序，然后扫描即可。细节的处理需要稍加注意，必须是连续覆盖$[L,R)$，中间不能有中断。

::: details 参考代码（C++）

<<< @/docs/tutorial/others/SNSS2020-R2/src/d.cpp

:::

## Problem E - [Distance in Line](https://contest.yandex.com/snss2020/contest/19321/problems/E/)

### 题目描述

$Q$个人按照`L`、`R`、`U`、`D`的顺序排队，问相隔$N$位的两个人总共有多少次相邻。

### 题解

模拟。俄文机翻的英文不是很通顺，不过在纸上尝试一下之后就能比较容易弄懂题目的意思。只要按照序列把整个队伍的形状画出来，然后判断一下有多少间隔为$N$的位置是相邻（包括对角线）的。

::: details 参考代码（C++）

<<< @/docs/tutorial/others/SNSS2020-R2/src/e.cpp

:::

<Utterances />
