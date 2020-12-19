# AtCoder Beginner Contest 186 题解

[视频题解](https://www.youtube.com/watch?v=gU9nK5hzBjA)

<iframe width="560" height="315" src="https://www.youtube.com/embed/gU9nK5hzBjA" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A - [Brick](https://atcoder.jp/contests/abc186/tasks/abc186_a)

答案为$\left\lfloor\frac{N}{W}\right\rfloor$。

时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC186/src/a.py

:::

## Problem B - [Blocks on Grid](https://atcoder.jp/contests/abc186/tasks/abc186_b)

因为只能减少不能增加，所以答案为$\sum A_{i,j}-\min A_{i,j}\cdot NM$。

时间复杂度$\mathcal{O}(NM)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC186/src/b.py

:::

## Problem C - [Unlucky 7](https://atcoder.jp/contests/abc186/tasks/abc186_c)

直接遍历$1\dots N$，检查每个数字的十进制和八进制表示中是否含有数字`7`即可。

时间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC186/src/c.py

:::

## Problem D - [Sum of difference](https://atcoder.jp/contests/abc186/tasks/abc186_d)

注意到：

$$
\begin{aligned}
\sum_{i=1}^{N-1}\sum_{j=i+1}^N|A_i-A_j|&=\frac{1}{2}\sum_{i=1}^{N-1}\sum_{j=i+1}^N2|A_i-A_j|\\
&=\frac{1}{2}\sum_{i=1}^{N-1}\sum_{j=i+1}^N|A_i-A_j|+|A_j-A_i|\\
&=\frac{1}{2}\sum_{i=1}^{N}\sum_{j=1}^N|A_i-A_j|
\end{aligned}
$$

排序后利用前缀和求解即可。

时间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC186/src/d.py

:::

## Problem E - [Throne](https://atcoder.jp/contests/abc186/tasks/abc186_e)

令$X$为移动次数，$Y$为移动圈数，则有：

$$
XK+S=YN
$$

从而

$$
YN-XK=S
$$

这是一个典型的同余方程，这里可以利用扩展GCD先求解得到：

$$
Y'N+X'K=gcd(N,K)
$$

如果$S$不能被$gcd(N,K)$整除，则无解。否则，我们先将两边同时乘上$\frac{S}{gcd(N,K)}$，得到：

$$
Y''N+X''K=S
$$

然后我们利用$lcm(N,K)$最小化$Y$后就可以得到答案$X$。

时间复杂度$\mathcal{O}(\log(\min(N,K)))$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC186/src/e.py

:::

## Problem F - [Rook on Grid](https://atcoder.jp/contests/abc186/tasks/abc186_f)

先考虑先向右再向下的走法；再考虑先向下再向右的走法，这里可能有重复，可以利用树状数组或平衡二叉树等数据结构求解。

时间复杂度$\mathcal{O}(W+H\log W)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC186/src/f.cpp

:::

<Utterances />
