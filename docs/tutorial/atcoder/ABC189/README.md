# AtCoder Beginner Contest 189 题解

## Problem A -  [Slot](https://atcoder.jp/contests/abc189/tasks/abc189_a)

检查是否满足$C_1=C_2=C_3$即可。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Rust）

<<<@/docs/tutorial/atcoder/ABC189/src/a.rs

:::

## Problem B - [Alcoholic](https://atcoder.jp/contests/abc189/tasks/abc189_b)

因为Takahashi按顺序喝酒，所以我们直接模拟喝酒过程，在每一杯喝完之后检查是否醉酒即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Rust）

<<<@/docs/tutorial/atcoder/ABC189/src/b.rs

:::

## Problem C - [Mandarin Orange](https://atcoder.jp/contests/abc189/tasks/abc189_c)

这是一道经典题，实际上跟[LC84 - 柱状图中最大的矩形](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)是一样的。我们可以用单调栈解决本题。

在栈中，我们存储高度值和它们对应的起始位置。栈是升序的，也即最大的元素在栈顶。

现在考虑位置$i$，除非栈已经为空，或者栈顶元素的高度值小于当前高度，我们一直将栈顶元素出栈。在这一过程中，我们不断更新答案（每一个被弹出的高度值最远可以延伸到$i-1$处），同时记录下最左的位置。接下来我们把当前的高度和最左的位置一起入栈。

为了避免单独处理边界情况，我们在数组最后加上一个$0$。

- 时间复杂度$\mathcal{O}(N)$.
- 空间复杂度$\mathcal{O}(N)$.

::: details 参考代码 （Rust）

<<<@/docs/tutorial/atcoder/ABC189/src/c.rs

:::

## Problem D - [Logical Expression](https://atcoder.jp/contests/abc189/tasks/abc189_d)

一道非常简单的动态规划。我们只需要保存两个数，使得当前结果为`false`的方法数$f$，以及使得当前结果为`true`的方法数$t$，转移如下：

$$
(f,t)=\left\{\begin{aligned} & (2f+t,t) & s_i=\text{AND}\\ & (f, 2t+f) & s_i=\text{OR}\end{aligned}\right.
$$

- 时间复杂度$\mathcal{O}(N)$.
- 空间复杂度$\mathcal{O}(1)$.

::: details 参考代码（Rust）

<<<@/docs/tutorial/atcoder/ABC189/src/d.rs

:::

## Problem E - [Rotate and Flip](https://atcoder.jp/contests/abc189/tasks/abc189_e)

很自然想到首先对所有询问按照时间点进行排序，然后离线处理。

下面，我们来看看四种操作的结果。对于点$(x,y)$：

- 操作一的结果为$(y,-x)$
- 操作二的结果为$(-y, x)$
- 操作三的结果为$(2p-x,y)$
- 操作四的结果为$(x,2p-y)$

因为每种操作都是对所有点同时进行的，我们不会去逐个计算每个点的变化，而是计算得到最后的变换规则。

操作一和二交换了$x$和$y$，同时改变了其中某一个轴的符号。操作三和四翻转了某一个轴，然后再加上$2p$。我们使用五个变量来记录这些操作的合成效果。$swap$表示$x$和$y$是否被交换，$s_x$表示当前$x$轴的符号，$s_y$表示当前$y$轴的符号，$c_x$表示$x$轴的额外变化量，$c_y$表示$y$轴的额外变化量。

对于四种操作：

- 操作一：$swap$被翻转，$c_x$和$c_y$被交换，$s_x$和$s_y$被交换，之后$s_y$和$c_y$被翻转。
- 操作二：$swap$被翻转，$c_x$和$c_y$被交换，$s_x$和$s_y$被交换，之后$s_x$和$c_x$被翻转。
- 操作三：$s_x$被翻转，$c_x$翻转后加上$2p$。
- 操作四：$s_y$被翻转，$c_y$翻转后加上$2p$。

对于每一询问，我们首先进行操作直到操作次数满足要求。接下来，我们利用上面的五个变量计算最终的点的位置：

- 如果$swap$为`false`，则结果为$(s_xx_0+c_x,s_yy_0+c_y)$
- 如果$swap$为`true`，则结果为$(s_xy_0+c_x,s_yx_0+c_y)$

- 时间复杂度$\mathcal{O}(Q\log Q)$。
- 空间复杂度$\mathcal{O}(Q)$。

::: details 参考代码 （Rust）

<<<@/docs/tutorial/atcoder/ABC189/src/e.rs

:::

## Problem F - [Sugoroku2](https://atcoder.jp/contests/abc189/tasks/abc189_f)

我们首先考虑下面这个简化的问题：

- 我们有一项任务，成功的概率为$p_s$，成功的花费为$E_s$；失败的概率为$p_f=1-p_s$，花费为$E_f$。
- 如果成功了，我们即刻停止；否则我们将再次尝试。
- 最后的总花费的期望是多少？

这个期望可以表达为：

$$
E=E_sp_s+(E_f+E_s)p_fp_s+(2E_f+E_s)p_f^2p_s+\cdots
$$

从而：

$$
E_sp_s+p_fp_s((E_f+E_s)+(2E_f+E_s)p_f+\cdots)
$$

为此，我们需要计算

$$
\sum_s=E_s+E_sp_f+E_sp_f^2+\cdots=E_s\frac{1}{1-p_f}=\frac{E_s}{p_s}
$$

和

$$
\sum_f=E_f+2E_fp_f+3E_fp_f^2+\cdots
$$

后者的计算相对困难一些。

事实上，我们有：

$$
\sum_fp_f=E_fp_f+2E_fp_f^2+\cdots
$$

从而：

$$
(1-p_f)\sum_f=E_f(1+p_f+p_f^2+\cdots)=E_f\frac{1}{1-p_f}=\frac{E_f}{p_s}
$$

所以：

$$
\sum_f=\frac{E_f}{p_s^2}
$$

接下来我们将这两个和代入原式，就可以得到：

$$
E=E_sp_s+p_fp_s(\sum_f+\sum_s)=E_sp_s+p_fp_s(\frac{E_s}{p_s}+\frac{E_f}{p_s^2})=E_sp_s+(1-p_s)(E_s+\frac{E_f}{p_s})
$$

接下来我们回到原来的问题，想办法计算$E_s$、$E_f$以及$p_s$。

这里，如果我们到达了第$N$个位置，我们就成功了；如果我们被送回了$0$位置，我们就失败了。

求解的方法与 [LC837 - 新21点](https://leetcode-cn.com/problems/new-21-game/)类似。我们利用所有能够到达当前位置的位置的概率之和来计算到达当前位置的概率：

$$
p_i=\frac{\sum_p}{M}
$$

当然，损坏的格子不会对$\sum_p$作出贡献。同时，我们需要在计算完第$i$个位置之后将$p_i$加入$\sum_p$（如果$i$没有损坏的话），同时将$p_{i-M}$减去（如果$i\geq M$且第$i-M$个格子没有损坏）。

但除了概率，我们还需要计算期望$E_i$，它可以表示为：

$$
E_i=\frac{\sum p_j(E_j+1)}{\sum_p}=1+\frac{\sum p_jE_j}{\sum_p}
$$

这个表达式提示我们计算$p_iE_i$而非$E_i$：

$$
p_iE_i=\frac{\sum_p}{M}+\frac{\sum p_jE_j}{M}
$$

因此，我们可以用和计算$p_i$类似的方法来计算$p_iE_i$。注意损坏的格子不会对$\sum_{pE}$作出贡献，但是会对$p_fE_f$作出贡献。

因为超过第$N$个格子也被视为到达第$N$个格子，因此我们的循环会在第$N-1$个格子处停止。对于每一个能够从其到达第$N$个格子的位置，我们根据比例$\frac{i+M-N+1}{M}$计算其对$p_N$和$p_NE_N$的贡献。

最后，我们就得到了$p_fE_f$，$p_s=p_N$以及$p_sE_s=p_NE_N$，利用这些值和前面推导得到的公式，我们可以计算出最终的答案$E$。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码 （Rust）

<<<@/docs/tutorial/atcoder/ABC189/src/f.rs

:::

<Utterances />
