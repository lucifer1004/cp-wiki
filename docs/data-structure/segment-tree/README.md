# 线段树

## 什么是线段树

线段树是一种树型数据结构，树中的每个节点代表一段$[L,R]$的区间，一个节点的左孩子和右孩子的区间不相交且其并恰好等于该节点对应的区间。树的叶子节点对应的区间为$[L,L]$，也即单点。

下图给出了一个对应区间为$[1,4]$的线段树示例。

![线段树示例](./segment-tree.png)

线段树常用于含修改的区间查询。比较裸的题目会直接包含若干种操作，其中一些为修改操作，另一些为查询操作。还有些题目，则需要通过一定的观察才能发现可以用线段树进行求解。

## 标记永久化

标记永久化指的是不下传懒标记，而是在每次查询时，逐层考虑懒标记中的信息。对于主席树、树套树等复杂数据结构，标记永久化有减小常数的作用，并能够一定程度上减少代码量。

## 练习题

### 模板题：[Codeforces Edu Segment Tree P1 S1B](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B)

单点修改+区间查询。

::: spoiler 参考实现（Kotlin）

<<< @/docs/data-structure/segment-tree/src/CF-EDU-ST-P1-S1B.kt

:::

### 模板题：[洛谷P3372](https://www.luogu.com.cn/problem/P3372)

区间修改+区间查询。因为修改和查询都是区间操作，所以需要使用懒标记。

::: spoiler 参考实现：普通版本（C++）

<<< @/docs/data-structure/segment-tree/src/LG-P3372-Normal.cpp

:::

我们也可以引入标记永久化，虽然对这一题来说，性能上无法有明显提升，但代码量可以略微减少一些。

::: spoiler 参考实现：标记永久化版本（C++）

<<< @/docs/data-structure/segment-tree/src/LG-P3372-Persistent-Tag.cpp

:::
