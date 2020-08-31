# Codeforces Round 666 (CF1396) Editorial

## Div. 2 Problem A - [Juggling Letters](https://codeforces.com/contest/1397/problem/A)

Just count the number of every letter, and check whether every number can be divided by $N$.

::: details Code (Python 3)

<<< @/docs/editorial/codeforces/1396/src/2a.py

:::

## Div. 2 Problem B - [Power Sequence](https://codeforces.com/contest/1397/problem/B)

First sort the array in ascending order, then enumerate $c$. We can constrain the range of $c$ by $c^{n-1}<=2\sum a_i$, otherwise we can simply change all $a_i$ to $1$ and that will cost less.

::: details Code (Python 3)

<<< @/docs/editorial/codeforces/1396/src/2b.py

:::

## Problem A - [Multiples of Length](https://codeforces.com/contest/1396/problem/A)

We can make use of the fact that $N-1$ and $N$ are coprime. First we operate on $[1,N-1]$ whose length is $N-1$, then we operate on $[2,N]$ whose length is also $N-1$. After two operations, we can make all numbers divided by $N$. Finally we operate on $[1,N]$ whose length is $N$, and we can just add $-a_i$ to each $a_i$ ($a_i$ may have changed after the previous operations).

Note that $N=1$ is an edge case.

::: details Code (C++)

<<< @/docs/editorial/codeforces/1396/src/a.cpp

:::

## Problem B - [Stoned Game](https://codeforces.com/contest/1396/problem/B)

If $\max a_i>\sum a_i - \max a_i$, then T can always win. He can just take stones from the largest pile, while HL can only take from the rest piles. Since $\max a_i>\sum a_i - \max a_i$, there is definitely a time when HL has no stone to take after T takes a stone.

Otherwise, $\max a_i\leq\sum a_i - \max a_i$, then both players can avoid $\max a_i>\sum a_i - \max a_i$ with the following strategy:

- If the maximum pile is currently available, just take from it
- Otherwise, it means that the maximum pile has just been taken, so we have $\max a_i\leq\sum a_i - \max a_i - 1$. No matter which pile we take a stone from, we will have $\max a_i\leq\sum a_i - \max a_i$ afterwards.

So the winner depends on the parity of stones. If the total number of stones is odd, then T wins, otherwise HL wins.

::: details Code (C++)

<<< @/docs/editorial/codeforces/1396/src/b.cpp

:::

## Problem C - [Monster Invaders](https://codeforces.com/contest/1396/problem/C)

First, let's consider one level. We have two ways to clear all monsters:

- Kill the boss with one shot. We use pistol to kill all normal monsters, then use AWP to kill the boss. The total time cost is $p[i]=a[i]\cdot r_1+r_3$.
- Kill the boss with two shots. We can use pistol to kill all normal monsters, and then attack the boss once. Or we can use the laser gun to kill all normal monsters while damaging the boss at the same time. Then we are forced to leave. The next time we reach this level, we use pistol again to kill the boss. If we only consider the time spent on reloading, the total time cost is $q[i]=\min((a[i]+1)\cdot r_1, r_2)+r_1$.

Now we can consider the general route. Let's reflect on where we shall end.

![P3配图](./P3.png)
Supposing we end at $3$, our best choice should be like the figure above. That is to say, we first come to $3$, then we go to the other end and go back to $3$. Otherwise we will spend extra time on teleportation.

So we can divide the total time cost into three parts. The time cost of $[1,2]$, the time cost of $[3,8]$ and the time cost of moving from $2$ to $3$ which is $d$.

Let $L[i]$ be the minimal time to clear $[1,i]$ and stop at level $i$, $R[i]$ be the minimal time to clear $[i,N]$ and stop at level $i$, our final answer would be

$$
\min_{i=1}^NL[i]+R[i+1]+d
$$

In order to avoid edge cases, we can let $L[0]=R[N+1]=-d$.

Then we need to solve $L[i]$ and $R[i]$.

$R[n]$ is special, because there are no further levels. We can choose to kill all monsters in $p[n]$, or use the teleportation twice and spend $q[n]+2d$. For rest $R[i]$, since we need to go from $i$ to $i+1$ and then go back to $i$, so we must have passed level $i$ twice. So the total time cost is 

$$
R[i]=R[i+1]+2d+\min(p[i],q[i])
$$

Then we will consider $L[i]$. For $L[i]$, we have two strategies.

1. Not going back. We go from level $i-1$ to level $i$ then kill all monsters, using $L[i-1]+d+p[i]$.
2. Going back. We take the route $i-2\rightarrow i-1\rightarrow i\rightarrow i-1\rightarrow i$. Since we have passed level $i-1$ and $i$ twice, we can use both $p[i-1]$ and $q[i-1]$, and $p[i]$ and $q[i]$.

Comparing the two strategies, we will have

$$
L[i]=\min(L[i-1]+d+p[i],L[i-2]+4d+\min(p[i-1],q[i-1])+\min(p[i],q[i]))
$$

::: tip Why don't we consider going back further?

Consider route $i-3\rightarrow i-2\rightarrow i-1\rightarrow i\rightarrow i-1\rightarrow i-2\rightarrow i-1\rightarrow i$.

It can be rearranged to $i-3\rightarrow i-2\rightarrow i-1\rightarrow i-2\rightarrow i-1\rightarrow i\rightarrow i-1\rightarrow i$, and the length does not change. Moreover, both routes pass level $i-2$, $i-1$ and $i$ at least twice. So these two routes come to the same optimal value. The second part of the rearranged route is just what we have considered ($i-2\rightarrow i-1\rightarrow i\rightarrow i-1\rightarrow i$), yet the first part of the rearranged route ($i-3\rightarrow i-2\rightarrow i-1\rightarrow i-2$) is no better than $L[i-2]$ so we do not need to consider it.

:::

We can then use the formula we come to earlier to calculate the final answer.

::: details Code (C++)

<<< @/docs/editorial/codeforces/1396/src/c.cpp

:::

## Problem D - [Rainbow Rectangles](https://codeforces.com/contest/1396/problem/D)

Not yet.

## Problem E - [Distance Matching](https://codeforces.com/contest/1396/problem/E)

Not yet.

<Utterances />
