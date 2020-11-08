# AtCoder Beginner Contest 182 题解

## Problem A - [twiblr](https://atcoder.jp/contests/abc182/tasks/abc182_a)

直接输出$2A+100-B$即可，时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC182/src/a.py

:::

## Problem B - [Almost GCD](https://atcoder.jp/contests/abc182/tasks/abc182_b)

暴力穷举。时间复杂度$\mathcal{O}(N\cdot\max(a))$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC182/src/b.py

:::

## Problem C - [To 3](https://atcoder.jp/contests/abc182/tasks/abc182_c)

利用一个数能被$3$整除当且仅当其各位之和能被$3$整除。

- 如果本身能被$3$整除，则不需要删除。
- 如果被$3$除余$1$，则首先看是否能删去$1$个$1$，然后看是否能删去$2$个$2$。
- 如果被$3$除余$1$，则首先看是否能删去$1$个$2$，然后看是否能删去$2$个$1$。

时间复杂度$\mathcal{O}(\log N)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC182/src/c.py

:::

## Problem D - [Wandering](https://atcoder.jp/contests/abc182/tasks/abc182_d)

记录最远位置$ans$，当前位置$pos$，前缀和$sum$，以及前缀和的最大值$hi$。

在每一轮中，首先更新前缀和，然后更新前缀和的最大值，本轮能达到的最大值显然是$pos+hi$，用其更新$ans$，再用$pos+sum$更新$pos$。

时间复杂度$\mathcal{O}(N)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC182/src/d.cpp

:::

## Problem E - [Akari](https://atcoder.jp/contests/abc182/tasks/abc182_e)

将所有灯和墙都放到矩形中，然后逐行从左到右扫描一遍，再从右到左扫描一遍；逐列从上到下扫描一遍，再从下到上扫描一遍。最后统计亮着的格子即可。

时间复杂度$\mathcal{O}(HW)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC182/src/e.cpp

:::

## Problem F - [Valid payments](https://atcoder.jp/contests/abc182/tasks/abc182_f)

我们实际上就是要求出满足

$$
\sum k_ia_i=x
$$

并且满足

$$
\forall k_i, |k_ia_i| < a_{i+1}
$$

的整数元组$\{k_i\}$的种数。

我们不妨从小到大进行选择。容易看到，我们其实只需要记录当前每一个可能达到的总数以及对应的方法数，而不需要记录对应的具体方案。因为$a_{i+1}$总是$a_i$的倍数，所以在选择完$a_i$的系数$k_i$后，我们需要保证此时的总数能够被$a_{i+1}$整除。同时，因为$|k_ia_i| < a_{i+1}$的限制，因此，对于每一个原有的状态，我们实际上只能有两种选择。

我们以$\{x,1\}$作为初始状态开始递推。看起来，状态数会以指数规模增长，但实际上，任意时刻，我们最多同时保留两个状态，因此总时间复杂度为$\mathcal{O}(N)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC182/src/f.cpp

:::

<Utterances />
