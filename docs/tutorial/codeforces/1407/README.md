# Codeforces Round 669 (CF1407) 题解

## Problem A - [Ahahahahahahahaha](https://codeforces.com/contest/1407/problem/A)

### 题目描述

长度为$N$（$N$为偶数）的$01$串，要求删去至多$N/2$个数，使得剩下的数满足交错和$a_1-a_2+a_3\dots=0$。

### 题解

因为至多删去$N/2$个数，所以我们总可以删除$0$和$1$中出现次数较少的那一种。出现次数相同时我们选择留下$0$，因为$0$的交错和总为$0$。

但要特别注意，如果留下的是$1$，需要检查一下总个数是否为偶数，如果不是，还需要进行调整。

时间复杂度$O(N)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/codeforces/1407/src/a.cpp

:::

## Problem B - [Big Vova](https://codeforces.com/contest/1407/problem/B)

### 题目描述

要求将数组$a_i$重新排序，使得$c_i=GCD(a_1,\dots,a_i)$所构成的序列字典序最大。

### 题解

每次贪心地从剩下元素中找出能使得其与当前最大公约数的最大公约数最大的元素即可。如果存在多个，选择其中任何一个都行，因为剩下几个在接下来的轮次里也一定会被选到。

时间复杂度$O(N^2\log A)$，其中$A$是数组中的最大元素。

::: details 参考代码（C++）

<<< @/docs/tutorial/codeforces/1407/src/b.cpp

:::

## Problem C - [Chocolate Bunny](https://codeforces.com/contest/1407/problem/C)

### 题目描述

交互题。给定$1$到$N$的一个排列$p$，每次可以询问两个位置$i$和$j$，系统会告诉你$p_i\mod p_j$。要求用不超过$2n$次询问确定$p$。

### 题解

考虑任意两个不相等的数$a<b$，则必有$b\mod a<a=a\mod b$。也就是说，两个数正反各询问一次，就可以确定较小那个数的值。

所以我们从$1$和$2$开始，每次确定小的数，保留大的数的位次，继续向后询问。经过$2(n-1)$次询问后，我们可以确定所有小于$n$的数，那么此时的最大位次对应的数即为$n$。

时间复杂度$O(N)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/codeforces/1407/src/c.cpp

:::

## Problem D - [Discrete Centrifugal Jumps](https://codeforces.com/contest/1407/problem/D)

### 题目描述

给定一系列高度$h_i$，规定可以从$i$移动到$j$（$i<j$），当且仅当满足下列条件中的一种：

- $i+1=j$
- $\min(h_i,h_j)>\max_{k=i+1}^{j-1} h_k$
- $\max(h_i,h_j)<\min_{k=i+1}^{j-1} h_k$

求从$1$到$N$的最少移动次数。

### 题解

不难发现，合法的移动只有：

- $h_j$是$h_i$右边第一个不小于$h_i$的
- $h_j$是$h_i$右边第一个不大于$h_i$的
- $h_i$是$h_j$左边第一个不小于$h_j$的
- $h_i$是$h_j$左边第一个不大于$h_j$的

注意$i+1=j$一定包含在上面的情况中，不需要单独讨论。

因此跑四次单调栈获取上述信息后，进行BFS即可。

时间复杂度$O(N)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/codeforces/1407/src/d.cpp

:::

## Problem E - [Egor in the Republic of Dagestan](https://codeforces.com/contest/1407/problem/E)

### 题目描述

有一个$N$个节点$M$条边的有向图。每条边有黑白两种颜色（黑色为$0$，白色为$1$）。现在要给每个节点染色，染色之后所有不同颜色的出边都失效。找出一种染色方案，使得$1$到$N$不连通，或最短距离尽可能大。

### 题解

逆向思考，贪心染色。

所有边$(u,v,t)$都存在$v$处。从$N$开始进行BFS。对于当前访问到的节点$v$，考虑边$(u,v,t)$。如果当前$u$已经被设为颜色$t$，则不可能阻断这条边，将$u$入队；否则，将$u$设为$t$的相反颜色，从而阻断这条边。这样的染色方法一定是最优的，因为后访问到的节点对应更长的距离，所以一定应该优先解决先访问到的节点。

如果最后无法访问到$1$，则说明存在使得$1$到$N$不连通的染色方案；否则到$1$的距离即为所要求的最大最短距离。染色方案在BFS过程中已经确定。没有访问到的点可以染成任意一种颜色。

::: details 参考代码（C++）

<<< @/docs/tutorial/codeforces/1407/src/e.cpp

:::

<Utterances />
