# Google Kick Start 2020 Round F 题解

## Problem A - [ATM Queue](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4ed8)

一个人要用$\left\lceil\frac{A_i}{X}\right\rceil$轮才能取到$A_i$。所以我们可以把$A_i$变为二元组$(\left\lceil\frac{A_i}{X}\right\rceil, i)$，然后排序就可以得到最终的序列。

因为进行了排序，最终的时间复杂度为$O(N\log N)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2020F/src/a.cpp

:::

## Problem B - [Metal Harvest](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4b8b)

首先，我们对所有区间进行排序。因为区间不会有重叠，所以我们可以逐个处理。在这个过程中，我们一直记录着当前最后一个覆盖的右端点$R$。

对于每个区间，如果它已经被最后一个覆盖完全覆盖，我们不需要进行任何操作。否则，我们需要对一段长度为$r_i-\max(l_i,R)$的区间进行覆盖，这需要$\left\lceil\frac{r_i-\max(l_i,R)}{K}\right\rceil$个机器人。在添加了这些机器人后，我们将$R$更新为$\max(l_i, R)+K\cdot\left\lceil\frac{r_i-\max(l_i,R)}{K}\right\rceil$。

因为进行了排序，最终的时间复杂度为$O(N\log N)$。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2020F/src/b.cpp

:::

## Problem C - [Painters' Duel](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f47fb)

博物馆的结构可以用一个有$S^2$个节点，同时每个节点拥有不超过$3$条边的无向图来表示。

最困难的是如何表示当前游戏的局面。因为最多只有$6^2=36$个房间，一个$64$位整数就可以满足我们的需要。我们可以用最后$40$位记录房间的状态，$[41,50]$位记录$B$（后动的人）的位置，$[51,60]$位记录$A$（先动的人）的位置。如果一个房间已经被画过，或者正在维修，就将对应的位置为$1$。

接下来就可以用DFS来进行求解。

每一步有三种情况：

- $A$可以移动。从所有可选的房间中，我们需要找到一个可以最小化下一步得分的房间（因为在下一步中$A$和$B$的身份会互换）。  
- $A$无法移动，而$B$可以移动。直接交换$A$和$B$，进入下一步操作。
- $A$和$B$都无法移动。这是边界条件，返回$0$。

当然，我们会进行记忆化，以避免重复的计算。

理论的时间复杂度为$O(2^{S^2})$，这很大，但就像许多DFS问题一样，许多状态并不会被访问到，所以这一方法已经足够通过所有的测试。

::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2020F/src/c.cpp

:::

## Problem D - [Yeetzhee](https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4dea)

一个关键点是：除非当前状态已经不合法，否则我们不应当重新投掷骰子（严格证明暂时无法给出）。

在这一前提之下，我们就可以进行动态规划了。和C题一样，难点在于如何表示状态，并判断一个状态是否合法。

我们可以使用前缀和来表示状态。令$S[i]$表示出现次数不超过$i$次的数字的数目。比如说，如果最终的目标是$[1,2,2,3]$（这说明$N=8$）同时$M=6$，则目标状态的前缀和为$[2,3,5,6]$（因为最大的频率是$3$，所以将数组在$i=3$处截断），而初始状态的前缀和为 $[6,6,6,6]$。对于任何一个合法的中间状态，其所有位置都不应小于目标状态的对应位置，因为在转移过程中，前缀和中的元素只会减小而不会增大。

在每次转移中，我们枚举所有当前的合法状态。对于一个状态$(S,p,e)$，其中$S$表示前缀和，$p$表示这一状态的概率，$e$表示到达这一状态掷骰子次数的期望，我们首先找出所有可能的更新。一个更新$(i_k,c_k)$是合法的，当且仅当至少有一个数字出现了$i_k$次（也即$c_k=S[i_k]-S[i_k-1]>0$），同时$S[i_k]>target[i_k]$。我们可以求出所有“好”的数字的个数$g$。则我们在这一步掷骰子次数的期望为$\frac{M}{g}$。而这一个更新会被记录为$(S',p\cdot\frac{c_k}{g},e+\frac{M}{g})$。

接下来，我们应用所有的更新。对于一个新状态$S'$，它的概率为所有以其为目标的更新的概率之和，而它的期望为所有以其为目标的更新的期望的加权和（权值为归一化概率，也即需要把每一个概率值除以总概率）。

时间复杂度的计算是比较困难的。但是因为$50$的划分数大约为$10^6$量级，在整个动态规划过程中并不会产生太多的状态，因此可以顺利地通过所有测试。
 
::: details 参考代码（C++）

<<< @/docs/tutorial/kick-start/2020F/src/d.cpp

:::

<Utterances />