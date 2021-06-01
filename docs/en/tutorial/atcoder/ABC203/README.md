# AtCoder Beginner Contest 203 Editorial

## Problem A -  [Chinchirorin](https://atcoder.jp/contests/abc203/tasks/abc203_a)

- If $a=b$, print $c$.
- If $a=c$, print $b$.
- If $b=c$, print $a$.
- Otherwise, print $0$.

- Time complexity is $\mathcal{O}(1)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC203/src/a.rs

:::

## Problem B - [AtCoder Condominium](https://atcoder.jp/contests/abc203/tasks/abc203_b)

Under the given constraints, the answer can be expressed as:

$$
\dfrac{n(n+1)}{2}\cdot k\cdot100+\dfrac{k(k+1)}{2}\cdot n
$$

- Time complexity is $\mathcal{O}(1)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC203/src/b.rs

:::

## Problem C - [Friends and Travel costs](https://atcoder.jp/contests/abc203/tasks/abc203_c)

First, sort the friends according to their distances. Then we enumerate the friends. When we do not have enough money to go to the place of the current friend, we break the loop, spend the remaining money and stop.

- Time complexity is $\mathcal{O}(N\log N)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC203/src/c.rs

:::

## Problem D - [Pond](https://atcoder.jp/contests/abc203/tasks/abc203_d)

If the median of a section is $M$, then there should be at least $\left\lceil\dfrac{K^2}{2}\right\rceil$ numbers in this section that satisfy $A_{ij}\le M$.

Based on this observation, we can binary search for the answer. Given the guess of the median $M$, we first turn the original matrix into a $0$-$1$ matrix, in which $0$ means $A_{ij}>M$ and $1$ means $A_{ij}\le M$. Then we can find the sum of all $K\times K$ sections in $\mathcal{O}(N^2)$ time based on the precalculated $2$-D prefix sum. If the maximum among all section sums is smaller than $\left\lceil\dfrac{K^2}{2}\right\rceil$, it means the guessed median is too large, and vice versa.

- Time complexity is $\mathcal{O}(N^2\log\operatorname{AMAX})$, in which $\operatorname{AMAX}=10^9$.
- Space complexity is $\mathcal{O}(N^2)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC203/src/d.cpp

:::

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC203/src/d.rs

:::

## Problem E - [White Pawn](https://atcoder.jp/contests/abc203/tasks/abc203_e)

Since we can only move down, we will divide the black pawns into groups based on their row number, and process the groups in the ascending order.

We maintain a hash set of the available columns during the processing. A black pawn located in the $j$-th column will make the $j$-th column unavailable if it is originally available, while if either the $j-1$-th column or the $j+1$-th column is originally available, the $j$-th column will be available regardless of its original state. So we should record the removals and insertions, then handle the removals before handling the insertions.

- Time complexity is $\mathcal{O}(N\log N)$.
- Space complexity is $\mathcal{O}(N)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC203/src/e.rs

:::

## Problem F - [Weed](https://atcoder.jp/contests/abc203/tasks/abc203_f)

The original order does not matter in this problem, so we can safely sort the heights in the ascending order. Then we can calculate for each height the range it can cover if it is the highest at the moment of an operation, and we will have an increasing array of segments.

For example, the heights $[2, 3, 4, 9]$ will become segments $[[1, 1], [1, 2], [2, 3], [4, 4]]$.

Our goal is to choose several non-overlapping segments such that the remaining positions do not exceed $K$. And we need to first minimize the number of chosen segments and then minimize the number of remaining positions.

An observation is that in this problem, the segments are not arbitrary. Consider the situation in which Aoki removes no weeds at first. Then Takahashi would need to operate at most $\log\operatorname{\max A_i} + 1$ times, since in each operation, the maximum height of the remaining weeds is at least cut by half.

So we will need no more than $\log\operatorname{\max A_i} + 1$ operations.

Now we can use dynamic programming to solve this problem. Let $dp[i][j]$ mean the minimum number of remaining weeds (that is to say, Aoki needs to pull these weeds at first) if we cover the range $[1,i]$ with $j$ operations. There are two types of transitions:

1. We perform an operation with the $i$-th weed as the highest, thus transit from $(l[i]-1,j-1)$  to $(i,j)$.
2. We skip the $i$-th weed (let Aoki pull it), thus transit from $(i-1,j)$ to $(i,j)$.

- Time complexity is $\mathcal{O}(N\log\operatorname{HMAX})$, where $\operatorname{HMAX}=10^9$.
- Space complexity is $\mathcal{O}(N\log\operatorname{HMAX})$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC203/src/f.rs

:::

<Utterances />