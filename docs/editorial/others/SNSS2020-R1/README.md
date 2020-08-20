# SnarkNews Summer Series - 2020 Round 1 题解

## Problem A - [Electric Lighting](https://contest.yandex.com/snss2020/contest/19320/problems/)

### 题目描述

有$N$个矩形（四个顶点的坐标均为非负整数），要求找到一个最佳的整数点，使得该点到每个矩形四个顶点的Manhattan距离的最小值的总和最小。求出这个最小值。

### 题解

容易看出$x$-轴和$y$-轴可以分别处理，这样就转化为了一维的问题：在数轴上有$N$条线段，要求找到一个最佳的整数点，使得该点到每条线段的两个端点的Manhattan距离的最小值的总和最小。

设$f(x,AB)=min(|x-a|,|x-b|)$，观察可知，函数在$(-\infty,a]$和$[\frac{a+b}{2},b]$单调递减，在$[a,\frac{a+b}{2}]$和$[b,+\infty)$单调递增。所以，我们可以知道$F(x)=\sum_if(x,L_i)$的最小值一定可以在某条线段的端点处取得。

在$x$从左向右移动的过程中，$F(x)$的值如何变化？这与当前每条线段的状态有关。参照上面的讨论，我们可以用每条线段的左端点、中点和右端点确定四个区间。当$x$处在第一和第三区间时，$x$向右移动，值减小；当$x$处在第二和第四区间时，$x$向右移动，值增大。因此，我们可以对所有线段的端点和中点进行离散化，然后使用扫描线算法求解。

::: spoiler 参考代码（C++）

<<< @/docs/editorial/others/SNSS2020-R1/src/a.cpp

:::

## Problem B - [Loading](https://contest.yandex.com/snss2020/contest/19320/problems/B/)

### 题目描述

有$A$个$5$，$B$个$4$，$C$个$3$，$D$个$2$，$E$个$1$，现在用容量为$5$的盒子去装，至少要几个盒子？

### 题解

贪心：

- 首先放$5$
- 放$4$，同时放$1$
- 放$3$，同时放$2$；如果还有空位置，放$1$
- 放$2$，同时放$1$
- 放$1$

::: spoiler 参考代码（C++）

<<< @/docs/editorial/others/SNSS2020-R1/src/b.cpp

:::

## Problem B - [Corporate Names](https://contest.yandex.com/snss2020/contest/19320/problems/C/)

### 题目描述

显然，公司名和缩略名可以构成二分图，因为数据范围比较小，直接跑一遍匈牙利算法即可。

### 题解

::: spoiler 参考代码（C++）

<<< @/docs/editorial/others/SNSS2020-R1/src/c.cpp

:::
