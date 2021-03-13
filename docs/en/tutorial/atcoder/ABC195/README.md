# AtCoder Beginner Contest 195 Editorial

## Problem A -  [Health M Death](https://atcoder.jp/contests/abc195/tasks/abc195_a)

Just check if $H\equiv 0\pmod{M}$.

- Time complexity is $\mathcal{O}(1)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC195/src/a.rs

:::

## Problem B - [Many Oranges](https://atcoder.jp/contests/abc195/tasks/abc195_b)

> Note that $W$ is in kilogram, so we need to use $1000W$ instead of $W$.

Let's first consider the upper bound.

We will try to use $A$ as many times as we can to achieve the upper bound. Problem is that there might be leftover grams, which we need to assign to the $hi=\lfloor\frac{1000W}{A}\rfloor$ oranges, and we can assign at most $k(B-A)$ grams. If the leftover is larger than $k(B-A)$, then this problem has no solution.

Now that the upper bound has been fixed (or the problem is doomed), we turn to the lower bound. Now we will use $B$ as many times as we can. First, we get $\lfloor\frac{1000W}{B}\rfloor$ oranges. Then we need to consider the leftover. If there are no leftover grams, then we have $lo=\lfloor\frac{1000W}{B}\rfloor$, otherwise, we have $lo=\lfloor\frac{1000W}{B}\rfloor+1$. It can be shown that we can always make $lo=\lfloor\frac{1000W}{B}\rfloor+1$ oranges when there are leftover grams, since the no-solution situation has been excluded in the previous phase.

- Time complexity is $\mathcal{O}(1)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC195/src/b.rs

:::

## Problem C - [Comma](https://atcoder.jp/contests/abc195/tasks/abc195_c)

- $[1, 9]$: 9 numbers, each has 0 commas.
- $[10, 99]$: 90 numbers, each has 0 commas.
- $[100,999]$: 900 numbers, each has 0 commas.
- $[1000,9999]$: 9000 numbers, each has 1 comma.
- $\cdots$

Based on the pattern above,  we can simply start from $1000$ and multiply by $10$ in each turn until $N$ is exceeded.

- Time complexity is $\mathcal{O}(\log_{10}N)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC195/src/c.rs

:::

## Problem D - [Shipping Center](https://atcoder.jp/contests/abc195/tasks/abc195_d)

Note that $N,M,Q$ are all very small, we can solve this problem via some brute force.

For each query, we collect all the available boxes, and sort them in the ascending order with respect to their capacities. For each box, we greedily choose the mose valuable baggage from all that have not been used and the box can contain.

- Time complexity is $\mathcal{O}(QM(N+\log M))$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC195/src/d.rs

:::

## Problem E - [Lucky 7 Battle](https://atcoder.jp/contests/abc195/tasks/abc195_e)

It is easy to observe that only the number modulo $7$ is important in this game. So we will have exactly $7$ states, denoting the current modulo.

Instead of going forward, we go backward because we only know the winning/losing state at the end of the game: $0=\text{Takahashi wins}$ and $\text{others}=\text{Aoki wins}$.

For each step, we enumerate all $7$ modulos, and calculate their successors: $a = (last * 10) \% 7$, and $b=(last*10+s[i])\%7$.

If Takahashi moves, he needs either $a$ or $b$ to be a winning state (for Takahashi) so that $last$ will be a winning state.

if Aoki moves, he needs either $a$ and $b$ to be a losing state (for Takahashi) so that $last$ will be a losing state, otherwise (both $a$ and $b$ are winning states), $last$ will be a winning state.

And we only need to check if $0$ is a winning state at first.

- Time complexity is $\mathcal{O}(CN)$, where $C=7$.
- Space complexity is $\mathcal{O}(C)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC195/src/e.rs

:::

## Problem F - [Coprime Present](https://atcoder.jp/contests/abc195/tasks/abc195_f)

An important observation is that, if there are two numbers that are not coprime, then the largest prime factor of their $\gcd$ will not exceed $71$.

We list all the prime numbers that are no larger than $71$. There are exactly $20$ such primes:

$$
[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]
$$

Then we can solve this problem via bitmask DP. The state would be all the prime factors that occur in our chosen set. We will start from $dp[0]=1$ (for the empty set) and all other $dp$ values equal to $0$.

For each number $A\leq i\leq B$, we find its bitmask representation (denoting which prime factors it has), and only make transitions from those states that do not conflict (sharing common prime factors) with this number.

- Time complexity is $\mathcal{O}((B-A+1)\cdot2^C)$, where $C=20$.
- Space complexity is $\mathcal{O}(2^C)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC195/src/f.rs

:::

<Utterances />