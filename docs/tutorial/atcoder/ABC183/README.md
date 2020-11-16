# AtCoder Beginner Contest 183 题解

[视频题解](https://www.youtube.com/watch?v=paWC0OYpOHk)

## Problem A - [ReLU](https://atcoder.jp/contests/abc183/tasks/abc183_a)

直接输出$\max(0,N)$即可，时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC183/src/a.py

:::

## Problem B - [Billiards](https://atcoder.jp/contests/abc183/tasks/abc183_b)

简单的几何计算，令$G'$为$G$关于$x$轴的对称点，连接$SG$，计算其与$x$轴交点的横坐标

$$
x=S_x+(G_x-S_x)\frac{S_y-0}{S_y-(-G_y)}
$$

即为答案。

时间复杂度$\mathcal{O}(1)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC183/src/b.py

:::

## Problem C - [Travel](https://atcoder.jp/contests/abc183/tasks/abc183_c)

$N$很小，枚举所有路线即可。

时间复杂度$\mathcal{O}(N!)$。

::: details 参考代码 （Python 3）

<<<@/docs/tutorial/atcoder/ABC183/src/c.py

:::

## Problem D - [Water Heater](https://atcoder.jp/contests/abc183/tasks/abc183_d)

扫描线算法。

对于第$i$个人，给$S_i$增加$P_i$，同时给$T_i$减少$P_i$。

从第一分钟开始扫描，如果在某一时刻总需求超过了总供给，则无解。

时间复杂度$\mathcal{O}(N+T)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC183/src/d.cpp

:::

## Problem E - [Queen on Grid](https://atcoder.jp/contests/abc183/tasks/abc183_e)

动态规划。记录每行、每列和每条对角线当前的前缀方法总和即可。

到达$(i,j)$的方法总数为$dp[i][j]=row[i]+col[j]+diag[i-j+w]$。之后，再用$dp[i][j]$去更新$row[i]$、$col[j]$和$diag[i-j+w]$。

如果$(i,j)$是墙，需要把$row[i]$、$col[j]$和$diag[i-j+w]$都清零。

时间复杂度$\mathcal{O}(HW)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC183/src/e.cpp

:::

## Problem F - [Confluence](https://atcoder.jp/contests/abc183/tasks/abc183_f)

并查集，合并时把包含不同班级较少的合并到较多的里面去。

时间复杂度$\mathcal{O}(N\log N+Q)$。

::: details 参考代码 （C++）

<<<@/docs/tutorial/atcoder/ABC183/src/f.cpp

:::

<Utterances />
