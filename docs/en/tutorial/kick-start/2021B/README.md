# Google Kick Start 2021 Round B Tutorial

Here are my solutions to Google Kick Start 2021 Round B. Some of them (C & D) are not optimal, albeit they passed all the test cases.

## Problem A - [Increasing Substring](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a882)

We simply go ahead and try appending the current letter after the last letter.

Complexity:

- Time complexity is $\mathcal{O}(|S|)$.
- Space complexity is $\mathcal{O}(|S|)$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021B/src/a.cpp

:::

## Problem B - [Longest Progression](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a3a5)

For $N\leq3$, it is obvious that the answer is $N$.

For $N\geq4$, we can first calculate $l[i]$, which denotes the length of the longest arithmetic array from left till $i$ without making any changes, and $r[i]$, which denotes the length of the longest arithmetic array from right till $i$ without making changes.

Then we check each position $i$ to see if we could get a longer length by changing $a[i]$ so that we can:

- combine $l[i-1]$ and $r[i+1]$ 
- combine $l[i-1]$ and $a[i+1]$
- combine $a[i-1]$ and $r[i+1]$

And the complexity:

- Time complexity is $\mathcal{O}(N)$.

- Space complexity is $\mathcal{O}(N)$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021B/src/b.cpp

:::

## Problem C - [Consecutive Primes](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a8e6)

The official solution leverages the concept of prime gap, and is a very beautiful brute-force solution.

However, since the test cases are bundled, we can also pass Test 3 if we use Euler sieve to generate all primes smaller than $\sqrt{\text{MAXN}}$ optimally, and then use binary search for each query. Note that we need to make $\text{MAXN}$ a bit larger than $10^{18}$ so that we will also generate the smallest prime that is larger than $10^9$. 

And the complexity:

- Time complexity is $\mathcal{O}(\sqrt{\text{MAXN}}+Q\log\frac{\sqrt{\text{MAXN}}}{\ln\sqrt{\text{MAXN}}})$.
- Space complexity is $\mathcal{O}(\sqrt{\text{MAXN}})$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021B/src/c.cpp

:::

## Problem D - [Truck Delivery](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a885)

The official solution uses segment tree. However, we can also use blocking to solve this problem.

We separate edges into blocks according to their limits $L_i$, and each block will have an optimal size of $\sqrt{N}$.

We first do a depth-first search to gather the information we need. That is, for each node, we would like to know the GCD value of all the edges whose limits are within the same block ($acc[i][j]$ in the code below), along the path from the root (capital city) to the current node. Also, we would like to know the previous edge ($last[i][j]$ in the code below) that has a limit that falls within a certain block, along the path.

For each query, we first determine the block $j$ that $W_i$ belongs to. Then we can safely calculate the GCD value of all the blocks that are smaller than $j$. For the $j$-th block, however, we need to check each edge to find out whether $L_k\leq W_i$, which can be done with the help of the $last$ array.

And the complexity:

- Time complexity is $\mathcal{O}((N+Q)\sqrt{N})$, if the block size is set as $\sqrt{N}$. (In the code below, I used a constant block size of $500$ to avoid discretization.) Also note that all $L_i$ are distinct, so each block with size $\sqrt{N}$ can contain at most $\sqrt{N}$ edges, which ensures the correctness of the time complexity.
- Space complexity is $\mathcal{O}(N\sqrt{N})$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2021B/src/d.cpp

:::

<Utterances />
