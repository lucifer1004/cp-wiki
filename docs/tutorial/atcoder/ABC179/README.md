# AtCoder Beginner Contest 179 题解

## Problem A - [Plural Form](https://atcoder.jp/contests/abc179/tasks/abc179_a)

直接实现逻辑即可。时间复杂度为$O(|S|)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC179/src/a.py

:::

## Problem B - [Go to Jail](https://atcoder.jp/contests/abc179/tasks/abc179_b)

按要求计数即可。时间复杂度为$O(N)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC179/src/b.py

:::

## Problem C - [A x B + C](https://atcoder.jp/contests/abc179/tasks/abc179_c)

固定$C$，符合条件的二元组$(A, B)$的数目就等于$N-C$的因子数，而一个正整数的因子数可以通过质因数分解求得。

设

$$
n=p_1^{a_1}p_2^{a_2}\dots p_k^{a_k}
$$

则其因子数为

$$
\prod_{i=1}^k(a_i+1)
$$

所以我们就计算$1\dots N-1$每个数的因子数，然后求和即可。

因为$[1,x]$范围内的质数个数近似为$\frac{x}{\ln x}$，总时间复杂度为$O(\frac{N\sqrt{N}}{\log N})$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC179/src/c.cpp

:::

## Problem D - [Leaping Tak](https://atcoder.jp/contests/abc179/tasks/abc179_d)

考虑我们当前处在$x$位置，我们上一步可能来自哪里？

我们需要检查所有的区间，然后找出对应的区间$[l,r]$（如果这样的区间存在的话），这一区间包含了所有能够利用原区间中的步长跳跃到当前位置的位置，也即上一步可能的位置。接下来我们将$sum(l,r)$累加到$dp[x]$上。

因为我们需要快速计算$sum(l,r)$，所以实际上我们可以使用前缀和$sum[i]$，而非$dp[i]$。

时间复杂度为$O(NK)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC179/src/d.cpp

:::

## Problem E - [Sequence Sum](https://atcoder.jp/contests/abc179/tasks/abc179_e)

显然，操作足够多次后，一定会开始循环。因为$M\leq10^5$，所以循环的长度不超过$10^5$，因此我们直接模拟找出循环节即可。

需要注意的是，循环节的起点未必是$X$。

总时间复杂度为$O(M)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC179/src/e.cpp

:::

## Problem F - [Simplified Reversi](https://atcoder.jp/contests/abc179/tasks/abc179_f)

当我们放一个白石头的时候，会改变多少黑石头的颜色？

对于第一种操作，这是由该列最上面的白石头决定的；对于第二种操作，这是由该行最左边的白石头决定的。

而每种操作的影响是什么呢？第一种操作会影响$1\dots X$行（$X$是操作的列最上面的白石头所在的行），而第二种操作会影响$1\dots X$列（$X$是操作的行最左边的白石头所在的列）。

很自然地想到用线段树来处理。一个储存每行最上面的白石头，另一个储存每列最左边的白石头。对于非叶结点，我们存储区间的最大值。因为我们每次操作相当于一个切割，把所有大于$X$的数都变为$X$，因此，存储区间最大值，可以让我们很方便地判断当前的切割是否产生了影响。

时间复杂度为$O(Q\log N)$.

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC179/src/f.cpp

:::

<Utterances />
