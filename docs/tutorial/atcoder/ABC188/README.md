# AtCoder Beginner Contest 188 题解

[视频题解](https://www.youtube.com/watch?v=AV8LJWgWL7I)

<iframe width="560" height="315" src="https://www.youtube.com/embed/AV8LJWgWL7I" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Problem A -  [Three-Point Shot](https://atcoder.jp/contests/abc188/tasks/abc188_a)

直接判断是否满足$|X-Y|\leq2$即可。

时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC188/src/a.py

:::

## Problem B - [Orthogonality](https://atcoder.jp/contests/abc188/tasks/abc188_b)

直接计算即可。

时间复杂度$\mathcal{O}(N)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC188/src/b.py

:::

## Problem C - [ABC Tournament](https://atcoder.jp/contests/abc188/tasks/abc188_c)

找出前一半的最大值和后一半的最大值，二者中较小的那一个对应的序号就是最后的答案。

时间复杂度$\mathcal{O}(2^N)$。

::: details 参考代码 （Python）

<<<@/docs/tutorial/atcoder/ABC188/src/c.py

:::

## Problem D - [Snuke Prime](https://atcoder.jp/contests/abc188/tasks/abc188_d)

离散化后，利用差分数组计算出每一段区间不订阅时的费用总和，然后依次计算每个区间的最小费用。

时间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC188/src/d.cpp

:::

## Problem E - [Peddler](https://atcoder.jp/contests/abc188/tasks/abc188_e)

从$N$开始倒序进行动态规划即可。

时间复杂度$\mathcal{O}(N+M)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC188/src/e.cpp

:::

## Problem F - [+1-1x2](https://atcoder.jp/contests/abc188/tasks/abc188_f)

- 如果$X\geq Y$，答案为$X-Y$
- 如果$X<Y$，采用BFS求解。为了减少状态分支数，从$Y$而非$X$开始。对于每一个当前值$Y'$，首先尝试用$d+|Y'-X|$更新最优解。然后，如果$Y'>X$，再进一步考虑使用三种操作：
    - 如果$Y'$为偶数，则$\div2$（$\times2$的逆操作）
    - 如果$Y'$为奇数，考虑$+1$或$-1$。
    特别地，如果当前队首元素的操作步数已经大于等于最优解，则提前结束搜索。

::: details 参考代码 （Python）

<<<@/docs/tutorial/atcoder/ABC188/src/f.py

:::

<Utterances />
