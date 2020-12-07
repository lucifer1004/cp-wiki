---
sidebarDepth: 3
---

# 强连通分量

## 定义

## Tarjan算法

桥，割点，现在是强连通分量。Tarjan算法生动地向我们展示了什么叫做一招鲜，吃遍天。

还是老套路，记录每个点的到达次序`dfn`以及从该点出发能够到达的最小编号`low`，同时每个点按遍历顺序入栈。如果一个点最终的`dfn`和`low`相等，此时从栈顶到该点的所有点就构成一个强连通分量。

## Kosaraju算法

Kosaraju算法的出发点是：一个连通分量是强连通分量，当且仅当连通分量中所有边都反向后，它仍然是一个连通分量。我们在第一次遍历的时候，在一个点递归完成后将其入栈。然后将所有边反向，再按照出栈顺序进行遍历，就能够得到所有的强连通分量。

## 模板

- [AtCoder Library](https://atcoder.github.io/ac-library/production/document_en/scc.html)（[源码](https://github.com/atcoder/ac-library/blob/master/atcoder/internal_scc.hpp)） 该模板使用的是Tarjan算法。

## 练习题

### [BS - Connected-Cities](https://binarysearch.com/problems/Connected-Cities)

::: details 提示

判断所有点是否构成一个强连通分量即可。

:::

### [BS - Cheapest Cost to All Cities](https://binarysearch.com/problems/Cheapest-Cost-to-All-Cities)

::: details 提示一

找出所有强连通分量，缩点。

:::

::: details 提示二

此时，原图的每一个连通分量都是一个有向无环图。所有非0且入度为0的新“点”，都需要一条入边。

:::

::: details 提示三

第一条出边必须从0所在的新“点”为根的子树上连出来。之后的出边就可以从所有点中`costs_from`最小的点连出来了。

:::

<Utterances />
