# Educational Codeforces Round 97 (CF1437) Tutorial

## Problem A - [Marketing Scheme](https://codeforces.com/contest/1437/problem/A)

::: details Hint
What will happen if $r\geq2l$?
:::

::: details Solution
Suppose that $r\geq2l$, then at least we need to cover $[l,2l]$. Obviously, we must have $a>l$, since the length of the segment is already longer than $l$. Now if $l<a\leq2l$, there are at most $l$ modules of $a$ which are no less than $\frac{a}{2}$, which cannot cover the segment whose length is $l+1$. But if $a>2l$, then $l$ cannot be a good value.

On the contrary, if $r<2l$, we can always choose $a=2l$ which will be a valid answer.

So this problem can be simplified to judging whether $r<2l$ holds.

Time complexity is $O(1)$.
:::

::: details Code (Python 3)

<<< @/docs/tutorial/codeforces/1437/src/a.py

:::

## Problem B - [Reverse Binary Strings](https://codeforces.com/contest/1437/problem/B)

::: details Hint
How many $00$ or $11$ pairs can be reduced within one reverse?
:::

::: details Solution
We can reduce the number of $00$ or $11$ pairs by at most $2$ within one reverse. So we can simply count the total number of such pairs, and get the answer.

Time complexity is $O(N)$.
:::

::: details Code (Python 3)

<<< @/docs/tutorial/codeforces/1437/src/b.py

:::

## Problem C - [Chef Monocarp](https://codeforces.com/contest/1437/problem/C)

::: details Hint

1. We will never use numbers larger than $2n$.
2. The original sequence of the array does not matter.

:::

::: details Solution
We will never put out an oven at $t>2n$, because $a[i]\leq n$, so even if we put out the first oven at $t=n$, we can put out the last oven at $t=2n-1$. Thus in any case that we put out an oven at $t>2n$, we can always reduce the total unpleasant values by replacing it with a smaller timestamp. Actually, the upper limit can be further squeezed, but $2n$ is fine enough.

We can sort the array first, then do simple dynamic programming, with $dp[t]$ meaning the total unpleasant values if the last oven is put out at $t$.

Since time is monotonic, when we consider the next oven, we can only transit from smaller timestamps. For the $i$-th oven, we will update $dp[t]$ with $\min_{t'<t}(dp[t'])+|t-a[i]|$. In order to save time, we can maintain a prefix minimum $lo$ during the iteration.

Total time complexity is $O(N^2)$, which is enough to pass the time limit.
:::

::: details Code (Python 3)

<<< @/docs/tutorial/codeforces/1437/src/c.py

:::

## Problem D - [Minimal Height Tree](https://codeforces.com/contest/1437/problem/D)

::: details Hint
Just go greedy.
:::

::: details Solution
We can arrange the nodes greedily. Unless the current number is smaller than the last one, we will keep connecting the numbers to the current parent node. Otherwise, we will move to the next parent node (which might be at the next level).

Time complexity is $O(N)$.
:::

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1437/src/d.cpp

:::

## Problem E - [Make It Increasing](https://codeforces.com/contest/1437/problem/E)

::: details Hint

1. We can add two sentinel elements at either end of $a$ and $b$. Then the original problem will be split into several subtasks.
2. For each subtask, we actually need to find the longest increasing subsequence.

:::

::: details Solution
The first step is to split the original problem into subtasks. Each subtask has four parameters, $l$ and $r$ for the start and the end of the interval, and $lo$ and $hi$ for the minimum valid value of the left end, and the maximum valid value of the right end.

Then for each subtask, we have three situations:

- $l>r$, which means the interval is empty. The answer is $0$.
- $l=r$, which means the length of the interval is $1$. The answer depends on whether $a[l]$ fits in $[lo,hi]$.
- $l<r$. In this case, we need to find the longest increasing subsequence. However, there are two differences compared to the classical LIS problem. One is that, if the current number does not fit in its valid range (which can be calculated using $lo$, $hi$, and $i$), it cannot be used in the LIS. The other difference is that we cannot use $a[i]$ directly. Considering the following case, $[2,5,3,1]$. Can we make an LIS with $[2,3]$? In this problem, we cannot, because there will be no room for the middle elements. How can we take the distance into consideration? We can use $a[i]-i$ instead of $a[i]$, and now we will find the longest non-decreasing subsequence instead of the longest increasing subsequence.

The algorithm for LIS is a classical DP enhanced with binary search, which takes $O(L\log L)$ time for an interval of length $L$.

So we have the total time complexity of $O(N\log N)$.
:::

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1437/src/e.cpp

:::

## Problem F - [Emotional Fishermen](https://codeforces.com/contest/1437/problem/F)

::: details Hint
When the current maximum value is $a$, what is the maximum possible value of the second-largest number?
:::

::: details Solution
An important observation is that, if the current maximum is $max$, then the current second-largest number $second$ must follow $2second<max$.

First, we will sort the numbers. Then we can find $pre[i]$ for each $i$, which means the largest index that can be included in the set when the largest number is $a[i]$ (after sorting).

After that, we will do dynamic programming, where $dp[i]$ means the number of valid permutations when the current largest number is $a[i]$. There are two types of transitions:

1. From $dp[i]$ to $dp[i]$. This requires that we choose a number $a[j]$ where $j\leq pre[i]$. The possible choices can be determined from the current size of the set, since all numbers except $a[i]$ that are in the set right now must have indices $\leq i$.
2. From $dp[j]$ to $dp[i]$, where $j\leq pre[i]$. To calculate this type of transition quickly, we can calculate the prefix sum of the $dp$ array after each iteration.

The original state is $dp[i]=1$, which means the set contains $a[i]$ only.

The total time complexity is $O(N^2)$.
:::

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1437/src/f.cpp

:::

## Problem G - [Death DBMS](https://codeforces.com/contest/1437/problem/G)

::: details Hint
We need to find the occurrences of all names in a given string. Aha-Corasick Automaton is just made for this.
:::

::: details Solution
This is a very typical ACA problem. Since there might be duplicate names, we can use a set for each name in order to maintain the largest value of this name.

For each query, we need to travel up the trie following the fail pointers, in order to collect all the valid names we have met, and find the maximum value.
:::

::: details Code (C++)

<<< @/docs/tutorial/codeforces/1437/src/g.cpp

:::

<Utterances />
