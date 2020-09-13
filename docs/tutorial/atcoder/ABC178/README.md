# AtCoder Beginner Contest 178 题解

## Problem A - [Not](https://atcoder.jp/contests/abc178/tasks/abc178_a)

直接输出$1-x$，时间复杂度$O(1)$。

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/a.py

:::

## Problem B - [Product Max](https://atcoder.jp/contests/abc178/tasks/abc178_b)

一眼看下去，似乎有很多种情况，但实际上需要考虑的只有端点，也就是$\{ac,ad,bc,bd\}$。

时间复杂度$O(1)$。

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/b.py

:::

## Problem C - [Ubiquity](https://atcoder.jp/contests/abc178/tasks/abc178_c)

简单的容斥原理。

$$
\text{有0有9的序列}=\text{所有序列}-\text{没有0的序列}-\text{没有9的序列}+\text{既没有0也没有9的序列}
$$

所以最后的答案是$10^n-2\cdot9^n+8^n$。

时间复杂度为$O(\log n)$。

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/c.py

:::

## Problem D - [Redistribution](https://atcoder.jp/contests/abc178/tasks/abc178_d)

枚举分成多少个数。

假设分成$k$个数，我们首先从$n$中去掉$2k$，这样所有的数只要大于等于$1$就可以了。接下来就可以用插板法解决，一共$n-2k-1$个空，要插入$k-1$个板子，方法数就是 $n-2k-1\choose k-1$。

时间复杂度为$O(n)$，如果我们不考虑预计算阶乘及阶乘的逆元的时间代价的话。

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/d.py

:::

## Problem E - [Dist Max](https://atcoder.jp/contests/abc178/tasks/abc178_e)

这道题目网上很容易能搜索到，但更重要的是理解这一类问题的本质。

我们的目标是求取$\max|x_i-x_j|+|y_i-y_j|$。暴力穷举需要 $O(N^2)$ 的时间，显然会超时。

关键点是把绝对值符号进行展开。我们需要知道，绝对值$|x|=\max\{x,-x\}$。

所以在本题中

$$
|x_i-x_j|+|y_i-y_j|=\max\{x_i-x_j+y_i-y_j,x_i-x_j+y_j-y_i,x_j-x_i+y_i-y_j,x_j-x_i+y_j-y_i\}
$$

我们将每一项重新组合，把相同下标的项组合到一起

$$
|x_i-x_j|+|y_i-y_j|=\max\{x_i+y_i-(x_j+y_j),x_i-y_i-(x_j-y_j),-x_i+y_i-(-x_j+y_j),-x_i-y_i-(-x_j-y_j)\}
$$

接下来就能得到

$$
\max|x_i-x_j|+|y_i-y_j|=\max\{\max(x_i+y_i-(x_j+y_j)),\max(x_i-y_i-(x_j-y_j)),\max(-x_i+y_i-(-x_j+y_j)),\max(-x_i-y_i-(-x_j-y_j))\}
$$

通过记录每种形式的最大值和最小值，我们可以在 $O(N)$ 内求得答案。

如果你在比赛中参考了网上的解析，这没有什么问题。但更重要的是理解原理。 $|x|=\max\{x,-x\}$ 这一简单的表达式，可以在很多问题中发挥大作用。

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC178/src/e.cpp

:::

## Problem F - [Contrast](https://atcoder.jp/contests/abc178/tasks/abc178_f)

这题和Codeforces今年有一道$nAmB$的题目很像。

首先我们找出所有的冲突数，也即两个序列共有的数。我们把它们按照数值分组，然后用一个大根堆存储。每次，我们取出最上面两组，从中各取出一个位置，然后交叉放置，也即$x\rightarrow y,y\rightarrow x$；唯一的例外情况是只剩三组，且每组只有一个位置，此时我们采用轮换的方式，也即$x\rightarrow y,y\rightarrow z,z\rightarrow x$。

在此之后，最多只剩一种冲突数。我们首先考虑这个数（注意，不能只考虑冲突的部分，而要考虑所有部分。考虑这个例子：$\{1,2\},\{2,2\}$，只有一对冲突的$2$，但我们必须同时考虑第二个序列中的两个$2$），尝试将它们都放入合法的位置。

如果这一步不能完成，说明无解。

在此之后，所有剩下的数都不会引发冲突，我们只要按次序放入空位即可。

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC178/src/f.cpp

:::

<Utterances />
