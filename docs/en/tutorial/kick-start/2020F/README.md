# Google Kick Start 2020 Round F Tutorial

## Problem A - [ATM Queue](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4ed8)

It takes a person $\left\lceil\frac{A_i}{X}\right\rceil$ rounds to withdraw $A_i$. So we can turn $A_i$ into pairs $(\left\lceil\frac{A_i}{X}\right\rceil, i)$, then sort the pairs to get the final sequence.

Total time complexity is $O(N\log N)$ since we need to sort.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/a.cpp

:::

## Problem B - [Metal Harvest](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4b8b)

First we need to sort all the time segments. Since there are no overlaps, we then handle them one by one. During the process, we keep record of the right endpoint of the last coverage, $R$.

For each segment, if it can be covered by the last coverage, we do nothing. Otherwise, we will need to cover a length of $r_i-\max(l_i,R)$, which requires $\left\lceil\frac{r_i-\max(l_i,R)}{K}\right\rceil$ robots. After adding those robots, we update $R$ with $\max(l_i, R)+K\cdot\left\lceil\frac{r_i-\max(l_i,R)}{K}\right\rceil$.

Total time complexity is $O(N\log N)$ since we need to sort.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/b.cpp

:::

## Problem C - [Painters' Duel](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f47fb)

The museum can be easily represented by a graph with $S^2$ nodes, and each node has at most $3$ edges.

The hardest point is how to represent the current state of the museum. Since there are at most $6^2=36$ rooms, a $64$-bit integer is just enough. We can use the last $40$ bits for rooms, $[41,50]$ for person $B$ (who moves second), and $[51,60]$ for person $A$ (who moves first). A room bit is set if it is under construction or it has been painted in previous steps.

Then we can do DFS.

There are in total three cases for each step:

- $A$ can move to a room. From all choices, we need to choose the one that minimizes the points (since the role of $A$ and $B$ are swapped).   
- $A$ cannot move while $B$ can move. We just swap $A$ and $B$ and continue.
- Neither $A$ nor $B$ can move. This is a boundary condition. The value is $0$.

Of course, we will use memoization to avoid duplicate calculation.

The theoretical time complexity is $O(2^{S^2})$ which is huge, but as in many other DFS problems, many conditions are automatically pruned, and this solution is enough to pass all test cases.

::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/c.cpp

:::

## Problem D - [Yeetzhee](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4dea)

An intuition is that we should not reroll dices unless current situation is already invalid.

Similar to Problem C, the hardest point is how to represent a state, and how to validate it.

Here, prefix sum can be a good choice. We use $S[i]$ to represent the number of colors (I change "numbers" to "colors" just for narrative convenience) that have occured no more than $i$ times.

For example, if the target state is $[1,2,2,3]$ (which implies that $N=8$) and $M=6$, the target prefix sum can be represented as $[2,3,5,6]$ (the array is truncated at $i=3$ since the largest frequency is $3$). And the original prefix sum is $[6,6,6,6]$. For any valid state, all elements in the prefix sum array should be larger than or equal to the corresponding element in the target prefix sum array, because numbers in the prefix sum array can only decrease.

During each transition, we enumerate all current states. For each state $(S, p, e)$ where $S$ is the prefix sum, $p$ is its probability and $e$ is the expected value of rolling times, we first find all valid updates. An update $(i_k, c_k)$ is valid, only if there is at least one color occuring $i_k$ times (which means $c_k=S[i_k]-S[i_k-1]>0$) and $S[i_k]>target[i_k]$. We can then count the number of good colors $g$. We are expected to roll $\frac{M}{g}$ times to get a good color. This update is stored as $(S',p\cdot\frac{c_k}{g},e+\frac{M}{g})$.

We then apply all updates. For a new state $S'$, its probability is the sum of all updates targeted at it, while its expected value is the weighted sum of all updates targeted at it.

The time complexity is hard to estimate. But since the partition number of $50$ is $\sim10^6$, there will not be too many states at each step. So this solution can pass all the test cases.
 
::: details Code (C++)

<<< @/docs/tutorial/kick-start/2020F/src/d.cpp

:::

<Utterances />
