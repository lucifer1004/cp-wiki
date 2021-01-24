# AtCoder Beginner Contest 189 Editorial

## Problem A -  [Slot](https://atcoder.jp/contests/abc189/tasks/abc189_a)

Just check whether $C_1=C_2=C_3$.

- Time complexity is $\mathcal{O}(1)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC189/src/a.rs

:::

## Problem B - [Alcoholic](https://atcoder.jp/contests/abc189/tasks/abc189_b)

Since Takahashi drinks in the given order, we just simulate how he drinks and check if he is drunken after drinking the current glass.

- Time complexity is $\mathcal{O}(N)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC189/src/b.rs

:::

## Problem C - [Mandarin Orange](https://atcoder.jp/contests/abc189/tasks/abc189_c)

This is a classical problem. It is the same as [LC84 - Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/). We can solve this problem using a monotonic stack.

In the stack, we store heights and their starting positions. We keep the elements in the stack in an ascending order, that is to say, the largest height is at the top.

Now when we have a new height at position $i$, we pop from the stack until the stack is empty, or the largest height is smaller than the current height. During the process, we update our answer (each popped height can extend to as far as $i-1$), and also record the leftmost position. Then we push the current height along with the leftmost position into the stack.

To avoid handling borders, we can add a $0$ at the end of the array.

- Time complexity is $\mathcal{O}(N)$.
- Space complexity is $\mathcal{O}(N)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC189/src/c.rs

:::

## Problem D - [Logical Expression](https://atcoder.jp/contests/abc189/tasks/abc189_d)

This is a very simple dynamic programming problem. We just store two values, $f$ for the number of ways to get `false` and $t$ for the number of ways to get `true`. The transition is 

$$
(f,t)=\left\{\begin{aligned} & (2f+t,t) & s_i=\text{AND}\\ & (f, 2t+f) & s_i=\text{OR}\end{aligned}\right.
$$

- Time complexity is $\mathcal{O}(N)$.
- Space complexity is $\mathcal{O}(1)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC189/src/d.rs

:::

## Problem E - [Rotate and Flip](https://atcoder.jp/contests/abc189/tasks/abc189_e)

It is natural to think of sorting the queries first, according to their timestamps.

Now let's look at the operations. Suppose we have $(x,y)$:

- Operation I changes it to $(y,-x)$
- Operation II changes it to $(-y, x)$
- Operation III changes it to $(2p-x,y)$
- Operation IV changes it to $(x,2p-y)$

Since the operations are applied to all points at the same time, we will not calculate the position of each point, instead, we want to know the final transform.

Operation I & II swaps $x$ and $y$, while changing the sign of one axis. Operation III & IV flips one axis and then adds $2p$ to it. To handle all the operations, we will use five variables, $swap$ denoting if $x$ and $y$ are swapped, $s_x$ denoting the sign of the current $x$ axis, $s_y$ denoting the sign of the current $y$ axis, $c_x$ denoting the extra value for $x$ and $c_y$ denoting the extra value for $y$.

Now we have:

- Operation I: $swap$ is flipped, $c_x$ and $c_y$ is swapped, $s_x$ and $s_y$ is swapped, then $s_y$ and $c_y$ are flipped.
- Operation II: $swap$ is flipped, $c_x$ and $c_y$ is swapped, $s_x$ and $s_y$ is swapped, then $s_x$ and $c_x$ are flipped.
- Operation III: $s_x$ is flipped, and $c_x$ is flipped then added $2p$.
- Operation IV: $s_y$ is flipped, and $c_y$ is flipped then added $2p$.

For each query, after applying enough operations, we can answer the query according to the five variables:

- If $swap$ is `false`, the answer will be $(s_xx_0+c_x,s_yy_0+c_y)$
- If $swap$ is `true`, the answer will be $(s_xy_0+c_x,s_yx_0+c_y)$

- Time complexity is $\mathcal{O}(Q\log Q)$.
- Space complexity is $\mathcal{O}(Q)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC189/src/e.rs

:::

## Problem F - [Sugoroku2](https://atcoder.jp/contests/abc189/tasks/abc189_f)

Let's first simplify this problem to the following form:

- There is a mission, our succeeding probability is $p_s$, and the cost is $E_s$, while our failing probability is $p_f=1-p_s$, and the cost is $E_f$.
- We will stop as long as we succeed, otherwise we keep trying.
- What is the expected value of our total cost?

The expected value of the total cost can be represented as:

$$
E=E_sp_s+(E_f+E_s)p_fp_s+(2E_f+E_s)p_f^2p_s+\cdots
$$

It equals to:

$$
E_sp_s+p_fp_s((E_f+E_s)+(2E_f+E_s)p_f+\cdots)
$$

We need to calculate two sums:

$$
\sum_s=E_s+E_sp_f+E_sp_f^2+\cdots=E_s\frac{1}{1-p_f}=\frac{E_s}{p_s}
$$

and

$$
\sum_f=E_f+2E_fp_f+3E_fp_f^2+\cdots
$$

which is a bit harder.

Actually, we have:

$$
\sum_fp_f=E_fp_f+2E_fp_f^2+\cdots
$$

So we have:

$$
(1-p_f)\sum_f=E_f(1+p_f+p_f^2+\cdots)=E_f\frac{1}{1-p_f}=\frac{E_f}{p_s}
$$

So

$$
\sum_f=\frac{E_f}{p_s^2}
$$

Then we return to the original equation and now we have:

$$
E=E_sp_s+p_fp_s(\sum_f+\sum_s)=E_sp_s+p_fp_s(\frac{E_s}{p_s}+\frac{E_f}{p_s^2})=E_sp_s+(1-p_s)(E_s+\frac{E_f}{p_s})
$$

Now we return to the original problem and try to calculate $E_s$, $E_f$ and $p_s$.

Here, if we arrive at the $N$-th position, we succeed. If we are sent back to the $0$-th position, we fail.

The idea is similar to [LC837 - New 21 Game](https://leetcode.com/problems/new-21-game/). We store the sum of the probability of the positions which can come to the current position, then 

$$
p_i=\frac{\sum_p}{M}
$$

Of course, the broken positions will not contribute to $\sum_p$. Also, we need to add $p_i$ (if $i$ is not broken) and remove $p_{i-M}$ (if $i-M$ is not broken) when $i\geq M$.

But here we also need the expected value $E_i$, which can be represented as:

$$
E_i=\frac{\sum p_j(E_j+1)}{\sum_p}=1+\frac{\sum p_jE_j}{\sum_p}
$$

The expression indicates that instead of calculating $E_i$, we can calculate $p_iE_i$ instead:

$$
p_iE_i=\frac{\sum_p}{M}+\frac{\sum p_jE_j}{M}
$$

In a similar manner, we can calculate $p_iE_i$ accumulatively. Note that the broken positions' $pE$ contributes to $p_fE_f$ instead of $\sum_{pE}$.

Since surpassing the $N$-th position is also counted as reaching the $N$-th position, our enumeration will stop at the $N-1$-th position. For each position that can reach the $N$-th position, we will calculate its contribution to $p_N$ and $p_NE_N$ according to the proportion $\frac{i+M-N+1}{M}$.

Finally, we can get $p_fE_f$, $p_s=p_N$ and $p_sE_s=p_NE_N$, and with these values, we can calculate the final answer $E$.

- Time complexity is $\mathcal{O}(N)$.
- Space complexity is $\mathcal{O}(N)$.

::: details Code (Rust)

<<<@/docs/tutorial/atcoder/ABC189/src/f.rs

:::

<Utterances />
