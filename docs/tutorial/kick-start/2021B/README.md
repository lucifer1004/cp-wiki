# Google Kick Start 2021 Round B 题解

## Problem A - [Increasing Substring](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a882)

遍历字符串，尝试将当前字母接到上一个字母之后即可。

复杂度：
- 时间复杂度为$\mathcal{O}(|S|)$。
- 空间复杂度为$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2021B/src/a.cpp

:::

## Problem B - [Longest Progression](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a3a5)

对于$N\leq3$，结果显然为$N$。

对于$N\geq4$，我们可以首先计算出$l[i]$，也即从左边开始到$i$结束的最长等差数列（不对数组进行改变）的长度；以及$r[i]$，也即从右边开始到$i$结束的最长等差数列（不对数组进行改变）的长度。接下来我们检查每个位置，看看我们是否能通过改变这一位置来得到一个更长的等差数列：

- 结合$l[i-1]$和$r[i+1]$ 
- 结合$l[i-1]$和$a[i+1]$
- 结合$a[i-1]$和$r[i+1]$

复杂度：
- 时间复杂度为$\mathcal{O}(N)$。
- 空间复杂度为$\mathcal{O}(N)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2021B/src/b.cpp

:::

## Problem C - [Consecutive Primes](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a8e6)

官方题解利用了素数间隔的知识，给出了一个非常优美的暴力解法。

不过，我们也可以利用欧拉筛在线性时间内求出所有不超过$\sqrt{\text{MAXN}}$的素数，然后二分求解每一个询问。注意这里$\text{MAXN}$需要比$10^{18}$略大一些，这样才能生成比$10^9$大的最小质数。

复杂度：
- 时间复杂度为$\mathcal{O}(\sqrt{\text{MAXN}}+Q\log\frac{\sqrt{\text{MAXN}}}{\ln\sqrt{\text{MAXN}}})$。
- 空间复杂度为$\mathcal{O}(\sqrt{\text{MAXN}})$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2021B/src/c.cpp

:::

## Problem D - [Truck Delivery](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a885)

官方题解使用了线段树。不过，我们也可以利用分块解决本题。

我们按照限重$L_i$将边分块，每个块的最优大小是$\sqrt{N}$。

我们首先进行一次DFS来获取需要的信息。对于每个节点，我们需要计算出从根节点到该节点的路径上属于每个分块的边的权重的GCD结果（也即下面代码中的$acc[i][j]$），以及从根节点到该节点的路径上属于每个分块的上一条边的序号（也即下面代码中的$last[i][j]$）。

对于每次查询，我们首先确定$W_i$所属的块的序号$j$。所有小于$j$的块的结果都是我们需要的。而对于第$j$个块，我们利用$last$数组找出路径上所有属于该块的边，并检查是否$L_k\leq W_i$。

复杂度：
- 时间复杂度为$\mathcal{O}((N+Q)\sqrt{N})$，如果块的大小设置为$\sqrt{N}$。在下面的代码中，块的大小被固定为500，这是为了避免对边的限重进行离散化。注意到$L_i$各不相同，所以每个大小为$\sqrt{N}$的块里至多有$\sqrt{N}$条边，这保证了时间复杂度的正确性。
- 空间复杂度为$\mathcal{O}(N\sqrt{N})$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2021B/src/d.cpp

:::

<Utterances />
