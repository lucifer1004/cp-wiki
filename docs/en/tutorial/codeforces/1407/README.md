# Codeforces Round 669 (CF1407) Tutorial

## Problem A - [Ahahahahahahahaha](https://codeforces.com/contest/1407/problem/A)

Since we can delete at most $N/2$ numbers, we can always choose to delete the one that occurs less. If $0$ and $1$ occur the same times, we choose to keep $0$ and delete $1$.

Note that if we choose to keep $1$, we need to check the parity and make a correction if needed.

Time complexity is $O(N)$.

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1407/src/a.cpp

:::

## Problem B - [Big Vova](https://codeforces.com/contest/1407/problem/B)

We can greedily take the element which makes the $GCD$ of it and current $GCD_t$ largest. If there are many, we can choose any of them, because the rest will be taken in the following rounds.

Time complexity is $O(N^2\log A)$, in which $A$ is the largest number in the array.

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1407/src/b.cpp

:::

## Problem C - [Chocolate Bunny](https://codeforces.com/contest/1407/problem/C)

Consider any $a<b$, we have $b\mod a<a=a\mod b$. That is to say, if we query $(i,j)$ and then $j_i$, we can determine the smaller one of $p_i$ and $p_j$, since $p$ is a permutation and there are no equal elements.

So we start from $p_1$ and $p_2$. Each time, we make two queries, determine the smaller one and keep the index of the larger one and continue queries. After $2(n-1)$ queries, we can determine all $p_i<n$，and the current kept index $p_k=n$.

Time complexity is $O(N)$.

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1407/src/c.cpp

:::

## Problem D - [Discrete Centrifugal Jumps](https://codeforces.com/contest/1407/problem/D)

Valid moves can only be in one of the following situations:

- $h_j$ is the first non smaller than $h_i$ to its right
- $h_j$ is the first non greater than $h_i$ to its right
- $h_i$ is the first non smaller than $h_j$ to its left
- $h_i$ is the first non greater than $h_j$ to its left

Note that $i+1=j$ must have been included in the situations.

We can use monotonic stack to gather the information. After that, we just do a BFS.

Time complexity is $O(N)$.

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1407/src/d.cpp

:::

## Problem E - [Egor in the Republic of Dagestan](https://codeforces.com/contest/1407/problem/E)

Think reversely and color greedily.

All edges $(u,v,t)$ are stored at $v$ side. We start BFS from $N$. Considering node $v$ and edge $(u,v,t)$. If $u$ has been colored to $t$, then this edge cannot be cut and we need to enqueue $u$. Otherwise we set $u$ to the opposite color of $t$ to cut this edge. This coloring strategy is optimal because a node visited earlier corresponds to a shorter distance to $N$.

If after the BFS we have not visited $1$, then it is possible to make $1$ and $N$ not connected. Otherwise $dist[1]$ is just the maximal shortest path distance we are required to find. The coloring has been determined during BFS. For those uncolored nodes, either color is OK.

Time complexity is $O(N+M)$.

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1407/src/e.cpp

:::

<Utterances />
