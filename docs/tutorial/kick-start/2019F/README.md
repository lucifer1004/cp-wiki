# Google Kick Start 2019 Round F 题解

## Problem A - Flattening

### 题目描述

给定一列数 $a_1,a_2...a_n$，问至少改变几个数字，可以使得相邻两个数字不相同的对数不超过 $k$ 对。

**示例：**
$$n=8,k=2$$
$$a=[300,100,300,300,200,100,800,500]$$

答案为 $3$，一种可行的策略是：

- $a_2$ 100->300
- $a_6$ 100->200
- $a_7$ 800->200

注意，不管数字的改变有多大，只计算为一次改变。

### 题解

可以参考 [LC265-粉刷房子](https://leetcode.cn/problems/paint-house-ii/)

预先对数字进行标号处理，记为 $nums[1]...nums[t]$。

我们用 $f[i][j][m]$ 表示前 $i$ 个数，至多包含 $j$ 对不相同的相邻数字，且最后一个数字为 $nums[m]$ 时的最少改变次数。可以得到转移方程：

$f[i][j][m]=\min(f[i-1][j][m], minf[i-1][j-1]) + (a[i] != nums[m])$

其中 $minf[i-1][j-1]$ 为预先维护的最小值。

$f[i-1][j][m]$ 的情况，由于上一个数字是 $nums[m]$，和当前增加的这个数字一样，所以不会增加不一致的对数。
$minf[i-1][j-1]$ 的情况，不管取得最小值时的最后一个数字是什么，至多增加一对不一致的对数，所以不一致对数不会超过 $j$。

最后一项，表示如果当前数字不为 $nums[m]$，则需要进行一次改变。

由于转移方程只涉及 $i-1$和$j-1$，所以可以用滚动数组处理。不过本题对空间的要求不高（$n\leq100$），直接三维数组毫无压力。

最后的答案就是 $\min f[n][j][m]$。

::: details 参考代码

<<< @/docs/tutorial/kick-start/2019F/src/a.cpp

:::

## Problem B - Teach Me

### 题目描述

给定 $n$ 个人和 $s$ 项技能，每个人掌握不超过 $5$ 项技能，但至少掌握一项技能，问有多少对 $(i,j)$，满足第 $i$ 个人可以给第 $j$ 个人教技能。

数据范围：$n\leq50000,s\leq1000$。

### 题解

这一题比赛时没有做出来大数据集，用 bitset 暴力过了小数据集。比赛之后看了前几名的代码，才恍然大悟。
这题的数据范围其实包含了暗示。每个人掌握不超过5项技能，这就意味着每个人的技能的子集至多 $C_5^1+C_5^2+C_5^3+C_5^4+C_5^5=31个$。对于每个人，给他的技能集的每个子集计一次数。那么最后得到的每个技能集的计数次数，就是覆盖该技能集的技能集总数，也即这个人教不了的人的数量。
所以最后第 $i$ 个人能够教的人的数量就等于 $n-hash[skill_i]$。

最后一个问题是如何表示 $skill_i$。本题中由于 $s\leq1000$，可以用一个 1001 进制的 5 位数来表示，也就是用一个 `long long`。为了保证表示的唯一性，要对技能进行排序。当然，其实用字符串之类的表示方式也完全可行，不过在运算效率上就要逊色不少了。

::: details 参考代码

<<< @/docs/tutorial/kick-start/2019F/src/b.cpp

:::

## Problem C - Spectating Villages

### 题目描述

$n$ 个村子由 $n-1$ 条无向边连接，保证任意两个村子可达（也即构成一棵树）。每个村子有一盏灯，一个村子点亮灯之后，所有相邻的村子也会被照亮。每个村子有一个美观值 $b_i$（$-10^5\leq b_i\leq 10^5$）。现在可以点亮任意多盏灯（也可以一盏都不点亮），求所有被照亮的村子的美观值总和的最大值。

### 题解

一道非常典型的树形动态规划。在把题目给出的无根树转为有根树之后，我们可以很容易地发现：

- 对于叶子节点，只有点灯、不点灯两种情况。
- 对于非叶子节点，有点灯、不点灯且不被点亮、不点灯但被点亮（也即至少一个孩子节点点灯）三种情况。

所以我们可以用一个二维数组$f[i][0,1,2]$来记录每个节点所在子树的最大美观值。

- $f[i][0]=\sum_{j\in adj[i]} \max(f[j][0], f[j][2])$。
- $f[i][1]=\sum_{j\in adj[i]} \max(f[j][0], f[j][1] - b_j, f[j][2] - b_j)+b_j$
- $f[i][2]$ 稍微复杂一些，需要比较所有的 $\max(f[j][0], f[j][2])$ 和 $f[j][1]$。如果存在 $f[j][1]\leq\max(f[j][0], f[j][2])$，那么直接取总和即可；否则需要用与对应的 $\max(f[j][0], f[j][2])$ 差距最小的 $f[j][1]$ 去替换，这样才能保证至少有一个孩子节点的灯是亮的，从而当前节点是被照亮的。

::: details 参考代码

<<< @/docs/tutorial/kick-start/2019F/src/c.cpp

:::

<Utterances />
