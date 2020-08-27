# Educational Codeforces Round 94 (CF1400) 题解

## Problem A - [String Similarity](https://codeforces.com/contest/1400/problem/A)

### 题目描述

给定一个长度为$2n-1$的字符串，要求构造一个长度为$n$的字符串，使得其与原字符串所有长度为$n$的子串都至少有一个位置相同。

### 题解

最简单的构造就是用第一个子串的第一位，第二个子串的第二位……观察后会发现这些位置刚好是原字符串的第$1,3,\cdots,2n-1$位。

::: details 参考代码（C++）

<<< @/docs/editorial/codeforces/1400/src/a.cpp

:::

## Problem B - [RPG Protagonist](https://codeforces.com/contest/1400/problem/B)

### 题目描述

两个人能带的东西的重量分别为$p$和$f$，两种东西的重量分别为$s$和$w$，数量分别为$cs$和$cw$，求两个人能带的东西的数量总和的最大值。

### 题解

一开始以为有贪心策略，但事实证明就是得穷举。

两种东西对称，所以我们可以通过交换，保证$s\leq w$。

因为$\sum cs\leq2\times10^5$且$\sum cw\leq2\times10^5$，所以直接穷举第一个人拿$s$的数量，再让第一个人尽量拿$w$。之后第二个人先尽量拿$s$，再尽量拿$w$。

::: details 参考代码（C++）

<<< @/docs/editorial/codeforces/1400/src/b.cpp

:::

## Problem C - [Binary String Reconstruction](https://codeforces.com/contest/1400/problem/C)

### 题目描述

在长度为$n$的串$w$的基础上，按照以下方法构造长度为$n$的串$s$:

- 如果$w_{i-x}=1$或$w_{i+x}=1$，则$s_i=1$（$i-x$和$i+x$需要是合法的下标）
- 否则$s_i=0$

给定$s$和$x$，重构$w$。

### 题解

逆向思考。$s_i=0$说明$w_{i-x}=w_{i+1}=0$，我们可以把$w$串先设为全$1$，然后根据$s$中$0$的情况对$w$进行对应修改。之后我们再检查$w$中剩余的$1$是否能保证$s$中的每个$1$成立。

因为这样构造出的$w$一定是所有满足$0$的条件中含$1$数量最多的，所以如果这样的$w$都不能满足$1$的条件，就一定无解。

::: details 参考代码（C++）

<<< @/docs/editorial/codeforces/1400/src/c.cpp

:::

## Problem D - [Zigzags](https://codeforces.com/contest/1400/problem/D)

### 题目描述

给定长度为$N$（$N\leq3000$）的数组，求满足$i<j<k<l$，同时满足$a_i=a_k$和$a_j=a_l$的四元组$(i,j,k,l)$的数目。

### 题解

容易求出$a_i=a_j=a_k=a_l$的四元组数目。

接下来求$a_i\neq a_j$情况下符合条件的四元组数目。

我们可以先固定$l$，然后枚举$j$的位置。在$j$移动的过程中，$j$左边和$j$右边的计数器分别只会有一个元素的数量发生变化，因此可以在$O(1)$时间内更新左右两边的配对数。当$a_j=a_l$时，我们就可以将当前的配对数加入答案。

总时间复杂度为$O(n^2)$。

::: details 参考代码（C++）

<<< @/docs/editorial/codeforces/1400/src/d.cpp

:::

## Problem E - [Clear the Multiset](https://codeforces.com/contest/1400/problem/E)

### 题目描述

给定一个长度为$N$（$N\leq5000$）的数组，每次可以进行以下任一操作：

1. 将一段连续区间减$1$，要求操作前区间所有数都大于$0$
2. 将某个位置置为$0$

问将所有位置变为$0$所需要的最小操作数。

### 题解

观察后可以得出一个结论：如果对某个区间$[L,R]$进行第一种操作，至少需要进行$\min_{i=L}^R a_i$次，否则的话，并不能减少需要进行第二种操作的次数，总次数不会减少。因此，我们可以从$[1,N]$开始进行DFS，每次利用$\min_{i=L}^R a_i$把原始区间分割成若干小区间。对于每个区间，我们比较其进行第一种操作时所需要的次数和只进行第二种操作时所需要的次数。因为总共形成的区间不会超过$N$个，所以可以在$O(N^2)$的时间复杂度内解决本题。

::: details 参考代码（C++）

<<< @/docs/editorial/codeforces/1400/src/e.cpp

:::

## Problem F - [x-Prime Substrings](https://codeforces.com/contest/1400/problem/F)

### 题目描述

定义$x$-Prime串为所含数字之和为$x$（1\leq x\leq20），且其除了自身之外的所有子串的数字之和都无法整除$x$的串。问，从原始串$s$（$|s|\leq 1000$）中至少删除多少个数字后，可以使得$s$的所有子串都不为$x$-Prime串？

### 题解

因为$x$并不大，我们可以枚举出所有的$x$-Prime串（$x=19$的时候最多，有两千多个）。

这时可以发现原问题变成了一个字符串与多个模式串的匹配问题，自然地想到使用刚才枚举出的$x$-Prime串来构建一个Aho-Corasick自动机。

接下来就是简单的动态规划了。$dp[i][j]$表示$s$的前$i$位，经过删除后的串在AC自动机上的位置为$j$时所能取得的最小值。有两种转移方式：

- 放弃$i+1$，最小值加一。
- 取$i+1$，串在AC自动机上的位置移动到$nxt=nodes[j].children[s_{i+1}]$。如果$nxt$不为终点，则可以进行这一转移，最小值不变。

::: details 参考代码（C++）

<<< @/docs/editorial/codeforces/1400/src/f.cpp

:::

## Problem G - [Mercenaries](https://codeforces.com/contest/1400/problem/G)

### 题目描述

有$N$个雇佣兵（$N\leq3\times10^5$），每个人要求组团的人数在$[L_i,R_i]$之间。另外有$m$（$m\leq20$）条规则，规定了$A_i$和$B_i$不能一起组团。求组建雇佣兵团的方法数（模$998244353$）。

### 题解

考虑使用容斥原理来求解。

总方法数等于不考虑规则的方法数，减去至少违反一条规则的方法数，加上至少违反两条规则的方法数……

需要预先计算出每种团队规模下，可选的雇佣兵人数$can[i]$。这可以通过扫描算法来求解。

在给定的违反规则情况下，我们至少要选择这些规则中涉及到的$k$个人。因为$m\leq20$，所以$k\leq40$。另一方面，这$k$个人会把可选的人数范围压缩到$[L,R]$，其中$L=\max L_i$，$R=\min R_i$。所以，这一情况下的总方法数就为$\sum_{i=L}^R C_{can[i]-k}^{i-k}$。因为我们需要枚举所有$2^m$种规则集，所以需要尽快计算出这一组合数的总和。为此，我们计算所有$k\leq2m$情况下的前缀和$\sum_{i=1}^jC_{can[i]-k}^{i-k}$，从而可以在$O(1)$时间内计算出刚才的方法数。

预计算$n!$的开销为$O(n\log MOD)$，预计算前缀和的开销为$O(nm)$，每种规则下的计算开销为$O(m\log m)$（因为使用`set`来维护这些规则涉及到的不同的人），所以最后的总时间复杂度为$O(n\log MOD+nm+2^mm\log m)$。

::: details 参考代码（C++）

<<< @/docs/editorial/codeforces/1400/src/g.cpp

:::

<Utterances />
