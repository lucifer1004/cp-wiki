---
sidebarDepth: 3
---

# 小大合并

小大合并是一个非常实用的策略，但却很少被专门提及。其中心思想是，在处理两组或多组状态的合并（可能是同一级状态之间的合并；也可能是父子状态之间的合并）时，始终将状态数较少的那一组向状态数较多的那一组进行合并，以减少状态移动或修改的次数。

## 练习题

### [CF1455G - Forbidden Value](https://codeforces.com/contest/1455/problem/G)

::: details 提示一
显然我们应当保存对应每一个数值的最小代价。不难发现，进入If分支相当于是从对应于If条件的那个数值出发，这样可以得到一些新的最小代价；而在结束If分支之后，我们需要将这些代价与上一层的代价进行合并。可以通过递归，利用系统栈来保存进入嵌套的If分支前的状态。
:::

::: details 提示二
我们可以利用小大合并的思想，每次总是将状态数较少的那一组向状态数较多的那一组进行合并。
:::

::: details 参考代码（C++）
<<< @/docs/tutorial/codeforces/1455/src/g.cpp
:::

### [ABC183F - Confluence](https://atcoder.jp/contests/abc183/tasks/abc183_f)

::: details 提示
利用并查集，合并时把包含不同班级较少的合并到较多的里面去。
:::

::: details 参考代码 （C++）
<<<@/docs/tutorial/atcoder/ABC183/src/f.cpp
:::

<Utterances />
