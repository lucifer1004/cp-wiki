# AtCoder Beginner Contest 186 Editorial

[Video Editorial](https://www.youtube.com/watch?v=gU9nK5hzBjA)

<iframe width="560" height="315" src="https://www.youtube.com/embed/gU9nK5hzBjA" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A - [Brick](https://atcoder.jp/contests/abc186/tasks/abc186_a)

The answer is $\left\lfloor\frac{N}{W}\right\rfloor$.

Time complexity is $\mathcal{O}(1)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC186/src/a.py

:::

## Problem B - [Blocks on Grid](https://atcoder.jp/contests/abc186/tasks/abc186_b)

The answer is $\sum A_{i,j}-\min A_{i,j}\cdot NM$.

Time complexity is $\mathcal{O}(NM)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC186/src/b.py

:::

## Problem C - [Unlucky 7](https://atcoder.jp/contests/abc186/tasks/abc186_c)

Just enumerate and check each number.

Time complexity is $\mathcal{O}(N\log N)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC186/src/c.py

:::

## Problem D - [Sum of difference](https://atcoder.jp/contests/abc186/tasks/abc186_d)

Note that:

$$
\begin{aligned}
\sum_{i=1}^{N-1}\sum_{j=i+1}^N|A_i-A_j|&=\frac{1}{2}\sum_{i=1}^{N-1}\sum_{j=i+1}^N2|A_i-A_j|\\
&=\frac{1}{2}\sum_{i=1}^{N-1}\sum_{j=i+1}^N|A_i-A_j|+|A_j-A_i|\\
&=\frac{1}{2}\sum_{i=1}^{N}\sum_{j=1}^N|A_i-A_j|
\end{aligned}
$$

We can first sort the array and then calculate the sum using prefix sum.

Time complexity is $\mathcal{O}(N\log N)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC186/src/d.py

:::

## Problem E - [Throne](https://atcoder.jp/contests/abc186/tasks/abc186_e)

Denote $X$ as the number of moves, and $Y$ as the number of loops.

$$
XK+S=YN
$$

So,

$$
YN-XK=S
$$

We can first use extended GCD on $N$ and $K$ to get,

$$
Y'N+X'K=gcd(N,K)
$$

If $S$ cannot be divided by $gcd(N,K)$, we have no answer. Otherwise, we multiply both sides with $\frac{S}{gcd(N,K)}$,

$$
Y''N+X''K=S
$$

Then we use $lcm(N,K)$ to minimize $Y$ and thus get the answer $X$.

Time complexity is $\mathcal{O}(\log(\min(N,K)))$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC186/src/e.py

:::

## Problem F - [Rook on Grid](https://atcoder.jp/contests/abc186/tasks/abc186_f)

First consider right-down routes, then down-right routes. There might be duplicates, which can be handled with data structures such as Fenwick tree or Balanced Binary Search Tree.

Time complexity is $\mathcal{O}(W+H\log W)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC186/src/f.cpp

:::

<Utterances />
