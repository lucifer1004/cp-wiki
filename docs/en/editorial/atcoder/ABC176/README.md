# AtCoder Beginner Contest 176 Editorial

## Problem A - [Takoyaki](https://atcoder.jp/contests/abc176/tasks/abc176_a)

The time needed equals to $\left\lceil\frac{N}{X}\right\rceil\cdot T$.

::: spoiler Code (Python3)

<<<@/docs/editorial/atcoder/ABC176/src/a.py

:::

## Problem B - [Multiple of 9](https://atcoder.jp/contests/abc176/tasks/abc176_b)

Let $n=\sum a_i\times10^i$, since $\forall i,10^i\equiv1(\mod9)$, we have $n\equiv\sum a_i(\mod 9)$ . So we just need to check the sum of all the digits of $n$.

::: spoiler Code (Python3)

<<<@/docs/editorial/atcoder/ABC176/src/b.py

:::

## Problem C - [Step](https://atcoder.jp/contests/abc176/tasks/abc176_c)

Just greedily increase current number to the maximum to its left, and then update the maximum if current number is larger than it.

::: spoiler 参考代码（C++）

<<<@/docs/editorial/atcoder/ABC176/src/d.cpp

:::

## Problem D - [Wizard in Maze](https://atcoder.jp/contests/abc176/tasks/abc176_d)

It's a very typical $0$-$1$ BFS, since the cost is $0$ if we go along the roads, while the cost is $1$ if we cast a magic spell.

Compared to ordinary BFS, we need to use a deque instead of a single-ended queue. For relaxations that cost $0$, we do `push_front`, while for those cost $1$, we do `push_back`. In this way, the elements in the deque are kept in an non-decreasing order, which means we will happily take the current value as the optimal value when we first reach the target position. 

::: spoiler 参考代码（C++）

<<<@/docs/editorial/atcoder/ABC176/src/d.cpp

:::


## Problem E - [Bomber](https://atcoder.jp/contests/abc176/tasks/abc176_e)

First, we can simply count how many targets there are in each row and each column.

Supposing the maximum of rows is $R_{max}$, and $C_{max}$ for columns. It is obvious that we can never achieve any value greater than $R_{max}+C_{max}$. In addition, we may not achieve $R_{max}+C_{max}$ because there might be a target at the crossing point of the row and the column, in which case this target is counted twice. So our worst case value is $R_{max}+C_{max}-1$ if we choose a row from those having $R_{max}$, and a column from those having $C_{max}$. Since all other choices cannot give better results, we only need to consider these rows and columns.

There might still be a log of combinations (worst case $O(NM)$). However, we do not need to check these combinations one by one. We can consider it from the perspective of targets. Say there are $n$ rows of $R_{max}$ and $m$ columns of $C_{max}$, if the number of target is smaller than $nm$, then it is ensured than there is at least one combination which will give us $R_{max}+C_{max}$. Otherwise, there are not so many combinations, so we can check them one by one, until we find a combination giving $R_{max}+C_{max}$, or we finish all the combinations and none is suitable, then we will have $R_{max}+C_{max}-1$ instead.

::: spoiler 参考代码（C++）

<<<@/docs/editorial/atcoder/ABC176/src/e.cpp

:::

## Problem F - [Brave CHAIN](https://atcoder.jp/contests/abc176/tasks/abc176_f)

There is an obvious $O(N^3)$ DP idea, in which we maintain states $dp[i][j]$, meaning the maximum we can get when we choose to keep numbers (not indices) $i$ and $j$. But this is not enough to pass.

Do we always need to update all the states? For each segment of length $3$, only a few of all states can be updated, because we are only given at most $3$ different numbers, which means we do not have many choices.

So, how to do state transitions? Supposing we are considering $a,b,c$.

- If $a=b=c$, then we should choose them all. In this case, instead of updating states, we should keep the number of such triplets in a separate variable. So the transition is $O(1)$.
- We change the current reserved numbers to two of $a,b,c$, e.g., $(a,b)$. In this case, we have two further choices
    - Make no triplets, and update $dp[a][b]$ to current global optimal value $opt$.
    - Make a triplet using two reserved $c$ and current $c$, then update $dp[a][b]$ to $dp[c][c]+1$.
    The transition is $O(1)$.
- We change one of the reserved number to one of $a,b,c$, e.g., $a$. In this case, we need to enumerate the other reserved number $x$, and we have two further choices
    - Make no triplets, and update $dp[a][x]$ to local optimal value $local\_opt[x]$, which means the best value we can get when we reserve at least one $x$.
    - Particularly, if $b=c$, then we can update $dp[a][x]$ to $dp[b][x]+1$
    The transition is $O(N)$
    
So the overall time complexity becomes $O(N^2)$, which is acceptable. It should be noted that all these updates should not be applied instantly. Instead, we store them and apply them at last.

During the update $dp[i][j]\rightarrow val$, we need to update

- Global optimum $opt\rightarrow\max\{opt,val\}$
- Local optimum $local\_opt[i]\rightarrow\max\{local\_opt[i],val\}$, and $local\_opt[j]\rightarrow\max\{local\_opt[j],val\}$
- State $dp[i][j]\rightarrow\{dp[i][j],val\}$, and $dp[j][i]\rightarrow\{dp[j][i],val\}$

After all these, we still have not handled the last number $last$. So we need to compare $opt$ and $dp[last][last]+1$. After that, we add to $opt$ the number of natural triplets $triplets$, and now we have the answer.

::: spoiler 参考代码（C++）

<<<@/docs/editorial/atcoder/ABC176/src/f.cpp

:::

<Utterances />
