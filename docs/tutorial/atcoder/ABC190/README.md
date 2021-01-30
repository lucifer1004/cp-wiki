# AtCoder Beginner Contest 190 题解

[视频题解](https://www.youtube.com/watch?v=K6_AzyUn8OM)

<iframe width="560" height="315" src="https://www.youtube.com/embed/K6_AzyUn8OM" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A -  [Very Very Primitive Game](https://atcoder.jp/contests/abc190/tasks/abc190_a)

先动的人必须有更多的糖果才能赢，所以我们只要检查这一条件是否满足即可。

- 时间复杂度$\mathcal{O}(1)$
- 空间复杂度$\mathcal{O}(1)$

::: details 参考代码（Rust）

<<<@/docs/tutorial/atcoder/ABC190/src/a.rs

:::

## Problem B - [Magic 3](https://atcoder.jp/contests/abc190/tasks/abc190_b)

我们检查是否存在满足$X_i<S$且$Y_i>D$的咒语。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(1)$

::: details 参考代码（Rust）

<<<@/docs/tutorial/atcoder/ABC190/src/b.rs

:::

## Problem C - [Bowls and Dishes](https://atcoder.jp/contests/abc190/tasks/abc190_c)

枚举所有的选择情况（一共$2^K$种），从中找到最大结果即可。

- 时间复杂度$\mathcal{O}(2^K(K+M))$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（Rust）

<<<@/docs/tutorial/atcoder/ABC190/src/c.rs

:::

## Problem D - [Staircase Sequences](https://atcoder.jp/contests/abc190/tasks/abc190_d)

假设数列首元素为$a$，一共有$n$个元素，则总和为$\frac{(a+a+n-1)n}{2}=N$。所以我们可以枚举$2N$的所有因子，检查其是否可以作为$N$。判断的条件是$\frac{2N}{n}+1-n=2a$必须是偶数。

- 时间复杂度$\mathcal{O}(\sqrt{N})$
- 空间复杂度$\mathcal{O}(M)$，其中$M$是$2N$的因子数。

::: details 参考代码（Rust）

<<<@/docs/tutorial/atcoder/ABC190/src/d.rs

:::

## Problem E - [Magical Ornament](https://atcoder.jp/contests/abc190/tasks/abc190_e)

我们可以把邻接对看成边，然后通过BFS找出所有关键宝石之间的最短路径，这些最短路径构成一个最短路径矩阵。

接下来我们进行状态压缩动态规划。状态为$dp[mask][last]$，其中$mask$表示我们已经获取到的关键宝石，$last$表示当前序列的最后一个宝石（一定是一个关键宝石）。对于每一个状态，我们枚举$next$，也即下一个选取的关键宝石来进行转移。

最后的答案就是$\min_i{dp[2^K-1][i]}$。

- 时间复杂度$\mathcal{O}(KN+K^2\cdot2^K)$
- 空间复杂度$\mathcal{O}(N+M+K\cdot2^K)$

::: details 参考代码（Rust）

<<<@/docs/tutorial/atcoder/ABC190/src/e.rs

:::

## Problem F - [Shift and Inversions](https://atcoder.jp/contests/abc190/tasks/abc190_f)

我们可以用树状数组或类似归并排序的方法（实际上是CDQ分治）来求出原序列的逆序数。接下来，我们注意到当把$K$（从$1$开始的）从序列开始移动到序列结尾时，减少了$K-1$个逆序对，同时新增了$N-K$个逆序对，因此变化量为$N+1-2K$。这样我们就可以逐个求出所有序列的逆序数了。

- 时间复杂度$\mathcal{O}(N\log N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（Rust）

<<<@/docs/tutorial/atcoder/ABC190/src/f.rs

:::

<Utterances />
