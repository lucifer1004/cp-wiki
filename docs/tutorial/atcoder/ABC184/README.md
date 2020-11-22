# AtCoder Beginner Contest 184 题解

[视频题解](https://www.youtube.com/watch?v=wnYpGt72S0w)

## Problem A - [Determinant](https://atcoder.jp/contests/abc184/tasks/abc184_a)

直接计算即可。

时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC184/src/a.py

:::

## Problem B - [Quizzes](https://atcoder.jp/contests/abc184/tasks/abc184_b)

模拟。

时间复杂度$\mathcal{O}(N)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC184/src/b.py

:::

## Problem C - [Super Ryuma](https://atcoder.jp/contests/abc184/tasks/abc184_c)

分情况讨论：

1. 起点和终点重合，总步数为$0$。
2. 一步可到达（共对角线或曼哈顿距离不超过$3$），总步数为$1$。
3. 走两次对角线，设此时中间点为$(r,c)$，可得到关于$r$和$c$的二元一次方程组，判断其是否有整数解（其实就是判断奇偶）。如果有整数解，总步数为$2$。
4. 枚举起点的邻近点，然后判断是否一步可到达。如果可到达，则总步数为$2$。
5. 其他所有情况都可以通过移动到一个相邻的格子转化为第三种情况，从而总步数为$3$。

时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC184/src/c.py

:::

## Problem D - [increment of coins](https://atcoder.jp/contests/abc184/tasks/abc184_d)

记忆化递归。

时间复杂度$\mathcal{O}(T^3)$，其中$T=100$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC184/src/d.cpp

:::

## Problem E - [Third Avenue](https://atcoder.jp/contests/abc184/tasks/abc184_e)

BFS。注意同一种类型的传送点只考虑一次。

时间复杂度$\mathcal{O}(HW)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC184/src/e.cpp

:::

## Problem F - [Programming Contest](https://atcoder.jp/contests/abc184/tasks/abc184_f)

折半搜索。

时间复杂度$\mathcal{O}(N\cdot2^{\frac{N}{2}})$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC184/src/f.cpp

:::

<Utterances />
