# Google Kick Start 2022 Round A Tutorial

Here are my solutions to Google Kick Start 2022 Round A.

## Problem A - [Speed Typing](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e7021)

### Solution I: Single Pointer

We use a pointer which points to the position to be matched in the target string. We then enumerate the original string and move forward the pointer whenever a match is found.

If the target string is fully matched, the answer will be the difference between the length of the original string and the target string, otherwise there will be no valid answer.

Complexity:

- Time complexity is $\mathcal{O}(|S|+|T|)$
- Space complexity is $\mathcal{O}(1)$

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2022A/src/a.cpp

:::

## Problem B - [Challenge Nine](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e7997)

### Solution I: Math + Greedy

We know that a number is divided by 9 is equivalent to that its digit sum can be divided by 9. We can quickly determine the digit we need based on this. If the number is already divided by 9, we can add either 0 or 9, but to make the answer the smallest, we will choose 0 instead.

We then look for the position of insertion greedily. We enumerate from to left and find the first position which is larger than the digit to be inserted.

However, when we are inserting 0, we cannot place it at the beginning, so we have to put it in the second place.

Complexity:

- Time complexity is $\mathcal{O}(N)$
- Space complexity is $\mathcal{O}(N)$

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2022A/src/b.cpp

:::

## Problem C - [Palindrome Free Strings](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e762e)

### Solution I: Dynamic Programming

Any palindrom with length $\ge$ 5 must either contain a 5-character palindrom or a 6-character palindrom. So we can find all the 5- and 6- palindroms and mark them, then maintain the possible situations of the last 6 positions during a dynamic programming.

Complexity:

- Time complexity is $\mathcal{O}(2^K\cdot|S|)$, where $K=5$
- Space complexity is $\mathcal{O}(2^K)$

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2022A/src/c.cpp

:::

## Problem D - [Interesting Integers](https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e73ea)

### Solution I: Digit Dynamic Programming

Such problems that ask for interval $[L,R]$ can usually be transformed to $F(R)-F(L-1)$. In this problem, $F(x)$ means the number of good numbers in the interval $[1,x]$.

Then we can calculate $F(x)$ via digit dynamic programming.

- We need to consider the relationship between digit product and digit sum. When the digit sum is fixed, we only need to record the GCD of the digit product and the digit sum.
- We can only use numbers no larger than $x$. Such problems with an upper bound or a lower bound can be solved by using a flag to denote whether the current prefix is equal to the bound.
- We need an extra flag to denote whether we are still within the leading zeros.

Suppose the upper bound has $N$ digits, then the digit sum cannot exceed $9N$. Then we can enumerate the digit sums. For a fixed digit sum $sum$, we do a 4-dimension DP like $dp[p][s][z][same]$, in which:

- $p$ denotes the GCD of the digit product and $sum$
- $s$ denotes the current digit sum
- $z$ denotes whether the current number is larger than zero
- $same$ denotes whether the current prefix is equal to that of the upper bound

The contribution of this DP to the final answer is $dp[sum][sum][1][0]+dp[sum][sum][1][1]$.

The details of the dynamic programming can be found in the code below.

Complexity:

- Time complexity is $\mathcal{O}(S^{5/2}\cdot ND)$, where $S\le9\times12=108$, $N$ is the length of the upper bound and $D=10$
- Time complexity is $\mathcal{O}(S^2)$

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2022A/src/d.cpp

:::

<Utterances />
