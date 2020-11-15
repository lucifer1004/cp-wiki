# Google Kick Start 2020 Round H Tutorial

## Problem A - [Retype](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff49/000000000043adc7)

We only have two options, thus

$$
ans=K-1+\min(N + 1, K - S + N - S + 1)
$$

Time complexity is $O(1)$.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020H/src/a.cpp

:::

## Problem B - [Boring Numbers](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff49/000000000043b0c6)

All problems such that require counting of numbers within range $[L,R]$ can be transformed into solving for $[0,R]$ and $[0,L]$ separately, and taking their difference as the final answer.

Now suppose $X$ has $D$ digits and we want to count boring numbers within $[0,X]$.

First, let's consider all numbers with $d<D$ digits. For $d$ digits, we can generate $5^d$ boring nubmers since we have $5$ options for each position (the most significant nubmer must be add so it cannot be $0$). So all numbers with $d<D$ digits make a contribution of $\sum_{i<D}5^i$.

Then we consider numbers with $D$ digits and are no larger than $X$.

Start from the most significant digit, and suppose that we are at the $i$-th digit now.

- If $X[i]$ does not satisfy the requirement of parity, we just need to count the digits that are smaller than $X[i]$ and can satisfy the parity (we can precalculate such numbers in $b[X[i]]$), then add to the total number $b[X[i]]\cdot5^{D-i}$. Since for these $b[X[i]]$ numbers, the following $D-i$ digits can be chose arbitrarily. In this case, we can stop right here.
- Otherwise, we first count the digits that are smaller than $X[i]$ and can satisfy the parity (we can precalculate such numbers in $a[X[i]]$) and add to the total number $a[X[i]]\cdot5^{D-i}$. Then we are going to count boring numbers that have exactly same $i$ digits as $X$ and continue our processing. Note that if $i=D$, we need to add $1$ to the total number, since this means $X$ itself is a boring number.

Time complexity is $O(\log R)$ if we exclude the precalculations.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020H/src/b.cpp

:::

## Problem C - [Rugby](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff49/000000000043b027)

Apparently, we can solve for $x$ and $y$ independently.

First consider $y$. Since all the people will be in the same row, this becomes a classical problem in which we just need to take the median of $Y_i$ as the meeting place.

Then we consider $x$. It is obvious that once we determine the starting point $x$, the optimal movement is determined. The leftmost person will go to the leftmost cell, and the rest follow.

Thus we can solve this problem via ternary search. In order to prove the correctness, we need to prove that $dist(x)$ has only one extreme point, which is also its minimum point. (If we consider integer points, there might be two, but the two must be $x$ and $x+1$).

Obviously, when $x+N-1\leq\min(X_i)$, $dist(x)$ decreases with $x$. While when $x\geq\max(X_i)$, $dist(x)$ increases with $x$.

We then observe that, when we move the starting point from $x$ to $x+1$, there will be $k(x)$ people who will move $1$ less, and $N-k(x)$ people who will move $1$ more. So $dist(x+1)-dist(x)=N-2\cdot k(x)$. During the process where $x$ moves from $-\infty$ to $\infty$, $k(x)$ goes to $0$ from $N$, and will never increase. So $dist(x+1)-dist(x)$ will increase from $-N$ to $N$ and will never increase. So $dist(x)$ will take its extreme value (also its minimum) at the minimum $x$ that makes $dist(x+1)-dist(x)\geq0$.

The final time complexity is $O(N\log N+N\log MAX)$, in which $MAX$ is our search range.

::: details Code (C++, ternary search)

<<< @/docs/tutorial/kick-start/2020H/src/c.cpp

:::

We can also do binary search on $dist(x+1)-dist(x)$, or $k(x)$, and the solution is very similar.

::: details Code (C++, binary search)

<<< @/docs/tutorial/kick-start/2020H/src/c1.cpp

:::

## Problem D - [Friends](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff49/000000000043aee7)

If we build a graph with the strings, we will have too many edges.

So instead we can build a graph with different letters (in this problem we have $C=26$ letters). We will save this graph in an adjacent matrix.

The initial setting is $d[i][j]=\infty$ and $d[i][i]=0$. Then we enumerate on all $N$ strings. If two different letters $a$ and $b$ both occur in the same string $S$, we set $d[a][b]=d[b][a]=1$. The meaning is that, if we have a string $S'$ with $a$ and another string $S''$ with $b$, we can build a chain $S'\to S\to S''$ which has $1$ middle point.

Then we do Floyd-Warshall on this adjacent matrix. Now $d[i][j]$ means the minimum middle points that are needed to build a chain from $i$ to $j$.

For each query, we enumerate on letters in $S[X_i]$ and $S[Y_i]$, and the final answer will be

$$
\min_{p\in S[X_i],q\in S[Y_i]}d[p][q] + 2
$$

If the answer is $\infty$, we just output $-1$.

The total time complexity is $O((N+Q)L^2+C^3)$, in which $C=26$ is the size of the alphabet.
 
::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020H/src/d.cpp

:::

<Utterances />