# AtCoder Beginner Contest 188 Editorial

[Video Editorial](https://www.youtube.com/watch?v=AV8LJWgWL7I)

<iframe width="560" height="315" src="https://www.youtube.com/embed/AV8LJWgWL7I" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A -  [Three-Point Shot](https://atcoder.jp/contests/abc188/tasks/abc188_a)

Check if $|X-Y|\leq2$.

Time complexity is $\mathcal{O}(1)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC188/src/a.py

:::

## Problem B - [Orthogonality](https://atcoder.jp/contests/abc188/tasks/abc188_b)

Just calculate the inner product,

Time complexity is $\mathcal{O}(N)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC188/src/b.py

:::

## Problem C - [ABC Tournament](https://atcoder.jp/contests/abc188/tasks/abc188_c)

Find the maximum of the lower half and the upper half, and compare them. The index of the smaller value is the answer we need.

Time complexity is $\mathcal{O}(2^N)$.

::: details Code (Python)

<<<@/docs/tutorial/atcoder/ABC188/src/c.py

:::

## Problem D - [Snuke Prime](https://atcoder.jp/contests/abc188/tasks/abc188_d)

First discretize the endpoints ($a_i-1$ and $b_i+1$ should also be taken into consideration). Then use a difference array to find the cost of each segment without a subscription, then calculate the minimum cost for each segment and sum them up.

Time complexity is $\mathcal{O}(N\log N)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC188/src/d.cpp

:::

## Problem E - [Peddler](https://atcoder.jp/contests/abc188/tasks/abc188_e)

Do dynamic programming in a reverse order (from $N$ to $1$).

Time complexity is $\mathcal{O}(N+M)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC188/src/e.cpp

:::

## Problem F - [+1-1x2](https://atcoder.jp/contests/abc188/tasks/abc188_f)

- If $X\geq Y$, the answer if $X-Y$.
- Otherwise, we use BFS to solve this problem. To reduce the number of states, we start from $Y$ instead of $X$. For each current value $Y'$, first try updating the answer with $d+|Y'-X|$. If $Y'>X$, then further consider the following cases:
    - If $Y'$ is even, use $\div2$ (reverse of $\times2$)
    - Otherwise, use $+1$ or $-1$.
    Specially, if the steps of the front element is equal to or larger than the answer, we can stop the search.

::: details Code (Python)

<<<@/docs/tutorial/atcoder/ABC188/src/f.py

:::

<Utterances />
