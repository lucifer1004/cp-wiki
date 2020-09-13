# AtCoder Beginner Contest 178 Tutorial

## Problem A - [Not](https://atcoder.jp/contests/abc178/tasks/abc178_a)

Just output $1-x$, which takes $O(1)$ time.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/a.py

:::

## Problem B - [Product Max](https://atcoder.jp/contests/abc178/tasks/abc178_b)

At first glance, there seem to be many conditions. But after you realize that the maximum must be within the set $\{ac,ad,bc,bd\}$, things become a lot easier.

Time complexity is $O(1)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/b.py

:::

## Problem C - [Ubiquity](https://atcoder.jp/contests/abc178/tasks/abc178_c)

Simple inclusion-exclusion.

$$
\text{seq with both 0 and 9}=\text{all seq}-\text{seq without 0}-\text{seq without 9}+\text{seq without 0 or 9}.
$$

So the answer equals to $10^n-2\cdot9^n+8^n$.

Time complexity is $O(\log n)$.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/c.py

:::

## Problem D - [Redistribution](https://atcoder.jp/contests/abc178/tasks/abc178_d)

Enumerate how many numbers there are.

For example, when there are $k$ numbers, we first take $2k$ out of $n$, so now all numbers should be larger than or equal to $1$, instead of $3$. Then the problem becomes, how many ways there are, if we want to separate $n-2k$ into $k$ numbers. This can be considered as insert $k-1$ partitions into $n-2k-1$ positions, which is $n-2k-1\choose k-1$.

Time complexity is $O(n)$, if we consider that the calculation of factorials and their modulo inverses takes constant time.

::: details Code (Python 3)

<<<@/docs/tutorial/atcoder/ABC178/src/d.py

:::

## Problem E - [Dist Max](https://atcoder.jp/contests/abc178/tasks/abc178_e)

This is a well-known problem and solutions can be easily found on the Internet. However, what is more important is to grasp the essence of such problems.

Our target is to find $\max|x_i-x_j|+|y_i-y_j|$. Brute force will not work because it takes $O(N^2)$ time which we cannot afford.

The key point is to expand absolute values. We should be aware that there is another definition of $|x|$, that is $|x|=\max\{x,-x\}$.

So in this problem, we have

$$
|x_i-x_j|+|y_i-y_j|=\max\{x_i-x_j+y_i-y_j,x_i-x_j+y_j-y_i,x_j-x_i+y_i-y_j,x_j-x_i+y_j-y_i\}
$$

Which can be further rearranged to 

$$
|x_i-x_j|+|y_i-y_j|=\max\{x_i+y_i-(x_j+y_j),x_i-y_i-(x_j-y_j),-x_i+y_i-(-x_j+y_j),-x_i-y_i-(-x_j-y_j)\}
$$

Then we have 

$$
\max|x_i-x_j|+|y_i-y_j|=\max\{\max(x_i+y_i-(x_j+y_j)),\max(x_i-y_i-(x_j-y_j)),\max(-x_i+y_i-(-x_j+y_j)),\max(-x_i-y_i-(-x_j-y_j))\}
$$

Which can be easily done in $O(N)$ time by storing maximum and minimum of each of the four forms.

If you have referred to a solution on the Internet, that is OK. But the important thing is to understand how this works. The simple expression $|x|=\max\{x,-x\}$ can help you in many more problems.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC178/src/e.cpp

:::

## Problem F - [Contrast](https://atcoder.jp/contests/abc178/tasks/abc178_f)

This problem is similar to [CF1381C - Mastermind](https://codeforces.com/contest/1381/problem/C).

First we need to handle the conflicting numbers. The strategy is based on swapping. We use a max-heap to store all conflicting numbers. Each time, we pick one from the top group $x$, and one from the second top group $y$, and put an $x$ at the $y$'s position, while putting a $y$ at the $x$'s position. There is only one exceptional case. If there are three groups left in the heap, and they all have only one position left, we should make a triplet swap, $x\rightarrow y,y\rightarrow z,z\rightarrow x$.

After this, there can be at most one conflicting group left. We try to put all the nubmers of this group (not only the conflicting ones, considering the $\{1,2\},\{2,2\}$ example, there is only one pair of conflicting $2$, but we need to handle all $2$s) into valid positions.

If this cannot be done, then this configuration has no solution.

After that, we can put the rest numbers (which cannot cause conflicts) into the rest positions.

::: details Code (C++)

<<<@/docs/tutorial/atcoder/ABC178/src/f.cpp

:::

<Utterances />
