# AtCoder Beginner Contest 190 Editorial

[Video Editorial](https://www.youtube.com/watch?v=K6_AzyUn8OM)

<iframe width="560" height="315" src="https://www.youtube.com/embed/K6_AzyUn8OM" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A -  [Very Very Primitive Game](https://atcoder.jp/contests/abc190/tasks/abc190_a)

The person that goes first need to have more candies than the other person to win the game. So we just check if the condition is satisfied.

- Time complexity is $\mathcal{O}(1)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC190/src/a.rs

:::

## Problem B - [Magic 3](https://atcoder.jp/contests/abc190/tasks/abc190_b)

We check each spell to see if there is a spell that has $X_i<S$ and $Y_i>D$.

- Time complexity is $\mathcal{O}(N)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC190/src/b.rs

:::

## Problem C - [Bowls and Dishes](https://atcoder.jp/contests/abc190/tasks/abc190_c)

We enumerate all possible situations (there are $2^K$ int total), and find the maximum number of conditions that can be satisfied.

- Time complexity is $\mathcal{O}(2^K(K+M))$.
- Space complexity is $\mathcal{O}(N)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC190/src/c.rs

:::

## Problem D - [Staircase Sequences](https://atcoder.jp/contests/abc190/tasks/abc190_d)

Suppose the first element of the sequence is $a$ and there are $n$ elements, then the sum of the sequence will be $\frac{(a+a+n-1)n}{2}=N$. So we can find all the factors of $2N$ and check each factor to see if it can be valid $n$ by ensuring that $\frac{2N}{n}+1-n=2a$ should be an even number.

- Time complexity is $\mathcal{O}(\sqrt{N})$.
- Space complexity is $\mathcal{O}(M)$ where $M$ is the number of factors of $2N$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC190/src/d.rs

:::

## Problem E - [Magical Ornament](https://atcoder.jp/contests/abc190/tasks/abc190_e)

We can view the adjacent pairs as edges, then we can use BFS to find the shortest distance between each pair of "significant gems" (the gems listed in $C_i$), which forms a distance matrix.

Then we do a bitmask DP. The state is $dp[mask][last]$, where $mask$ represents the significant gems we have collected, and $last$ means the last gem (which must be a significant gem) in the sequence. For each state, we enumerate the next significant gem $next$ to do the transitions.

The final answer is $\min_i{dp[2^K-1][i]}$.

- Time complexity is $\mathcal{O}(KN+K^2\cdot2^K)$.
- Space complexity is $\mathcal{O}(N+M+K\cdot2^K)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC190/src/e.rs

:::

## Problem F - [Shift and Inversions](https://atcoder.jp/contests/abc190/tasks/abc190_f)

We first use Fenwick Tree or a merge-sort-like (which is actually CQD Divide & Conquer) method to find the number of inversions in the original sequence. Then we observe that when we do the rotation, only the inversions that include the current leading number change. Suppose the leading number is $K$ (we use $1$-index here), then we will lose $K-1$ inversions and gain $N-K$ inversions. So within each rotation, the total number of inversions changes by $N+1-2K$.

- Time complexity is $\mathcal{O}(N\log N)$.
- Space complexity is $\mathcal{O}(N)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC190/src/f.rs

:::

<Utterances />
