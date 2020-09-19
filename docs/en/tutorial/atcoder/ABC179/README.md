# AtCoder Beginner Contest 179 Tutorial

## Problem A - [Plural Form](https://atcoder.jp/contests/abc179/tasks/abc179_a)

Just implement the logic.

Time complexity $O(|S|)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC179/src/a.py

:::

## Problem B - [Go to Jail](https://atcoder.jp/contests/abc179/tasks/abc179_b)

Use a counter to store current consecutive doublets, and check whether the counter has ever gone up to $3$.

Time complexity $O(N)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC179/src/b.py

:::

## Problem C - [A x B + C](https://atcoder.jp/contests/abc179/tasks/abc179_c)

For a specific $C$, the number of $(A, B)$ pairs equals to the number of factors of $N-C$.

Note that the number of factors can be calculated via prime factorization. If 

$$
n=p_1^{a_1}p_2^{a_2}\dots p_k^{a_k}
$$

Then the number of factors is 

$$
\prod_{i=1}^k(a_i+1)
$$

So we just perform prime factorization on all integers $1\dots N-1$, and calculate the sum of the number of factors.

Considering the number of prime numbers within $[1,x]$ can be approximated by $\frac{x}{\ln x}$, the total time complexity is $O(\frac{N\sqrt{N}}{\log N})$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC179/src/c.cpp

:::

## Problem D - [Leaping Tak](https://atcoder.jp/contests/abc179/tasks/abc179_d)

Suppose that we are currently at position $x$, where can we come from?

We need to check all segments, and find a corresponding (if there is) segment $[l,r]$, which consists of the positions that can be our last position. Then we add $sum(l,r)$ to $dp[x]$.

Since we need to calculate $sum(l,r)$ quickly, instead of using $dp[i]$, we use the prefix sum $sum[i]$.

Time complexity is $O(NK)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC179/src/d.cpp

:::

## Problem E - [Sequence Sum](https://atcoder.jp/contests/abc179/tasks/abc179_e)

Obviously, after enough operations, the sequence will start looping forever. Since $M\leq10^5$, the length of the loop cannot be longer than $10^5$, so we just find the loop and calculate the result.

Be careful that the start point of the loop is not necessarily $X$.

Time complexity is $O(M)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC179/src/e.cpp

:::

## Problem F - [Simplified Reversi](https://atcoder.jp/contests/abc179/tasks/abc179_f)

When we put a white stone, how many black stones will be changed to white?

If we are performing the first type of operation, the number depends on the topmost white stone in the chosen column. If we are performing the second type of operation, the number depends on the leftmost white stone in the chosen row.

What effects will our operation have on the board? The first type of operation will affect all rows within $[1, X]$ (where $X$ is the topmost white stone's row), and the second type of operation will affect all columns within $[1,X]$ (where $X$ is the leftmost white stone's column).

So we just use two segment trees, one for columns and the other for rows. For each node, we store the maximum value in the segment. Particularly, for a leaf node, its maximum value equals to the topmost/leftmost position.

Then when we apply an operation, it is like performing a cut on $[1,X]$, which sets all values $>X$ to $X$.

Time complexity is $O(Q\log N)$.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC179/src/f.cpp

:::

<Utterances />
