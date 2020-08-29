# AtCoder Beginner Contest 177 题解

## Problem A - [Don't be late](https://atcoder.jp/contests/abc177/tasks/abc177_a)

Just compare how far he can go and how far he needs to go.

::: details Code (Python3)

<<<@/docs/editorial/atcoder/ABC177/src/a.py

:::

## Problem B - [Substring](https://atcoder.jp/contests/abc177/tasks/abc177_b)

Since $|S|\leq1000$, we can just enumerate all possibilities and take the minimum.

::: details Code (Python3)

<<<@/docs/editorial/atcoder/ABC177/src/b.py

:::

## Problem C - [Sum of product of pairs](https://atcoder.jp/contests/abc177/tasks/abc177_c)

We have

$$\prod_{i<j} a_ia_j=\frac{\sum a_i(\sum a_j-a_i)}{2}$$

Note that

$$\frac{1}{2}(\mod P)\equiv2^{P-2}(\mod P)$$

::: details Code (Python3)

<<<@/docs/editorial/atcoder/ABC177/src/c.py

:::

## Problem D - [Friends](https://atcoder.jp/contests/abc177/tasks/abc177_d)

Just use DSU to find the biggest connected component. Since for one group, we can choose at most one person from each component.

::: details Code (C++)

<<<@/docs/editorial/atcoder/ABC177/src/d.cpp

:::

## Problem E - [Coprime](https://atcoder.jp/contests/abc177/tasks/abc177_e)

Just perform prime factor decompositon on all numbers, and find the maximum occurrence among all prime factors (each element counts only once).

If the maximum is equal to or less than $1$, the numbers are pairwise coprime. If the maximum is less than $N$, they are setwise coprime. Otherwise they are not coprime.

::: details Code (C++)

<<<@/docs/editorial/atcoder/ABC177/src/e.cpp

:::

## Problem F - [I hate Shortest Path Problem](https://atcoder.jp/contests/abc177/tasks/abc177_f)

We can use segment tree. For each row, if the prohibited range is $[L,R]$, then we need to 

- add one to $[1,L-1]$ and $[R+1,W]$ (just go down)
- update [L,R] to $f(i)=f(L-1)+i-L+1$ (since we must go right from $L-1$)

We need to query the range minimum.

So we can just implement the two types of operations and the range minimum query.

::: details Code (C++)

<<<@/docs/editorial/atcoder/ABC177/src/f.cpp

:::

::: tip Tips

If we are also allowed to go left, we only need to make a few modifications to the code above. For range $[L,R]$, we can both come from the left and the right. But no matter where we come from, the range minimum is at either $L$ or $R$.

:::

::: details Code (C++, modified problem)

<<<@/docs/editorial/atcoder/ABC177/src/f2.cpp

:::

<Utterances />
