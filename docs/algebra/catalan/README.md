---
sidebarDepth: 3
---

# 卡特兰数

卡特兰数（Catalan numbers, [OEIS A000108](https://oeis.org/A000108)）是一个非常重要的数列。其前10项为：

```
1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862
```

其递推公式为

$$
C(N)=\sum_{i=0}^{N-1}C(i)C(N-1-i)
$$

其中边界条件为$C(0)=1$。

进一步地，可以求出其通项公式为

$$
C(N)=\frac{2N\choose N}{N+1}=\frac{(2N)!}{N!(N+1)!}
$$

卡特兰数是一个非常神奇的序列，它与许多看似千差万别的问题都有着紧密的关联。这些问题包括：

- 有效的括号表达式
- 二叉搜索树的结构
- 有效的出栈序列
- 凸多边形的三角划分
- ……

## 练习题

### [BS - Planar Edges](https://binarysearch.com/problems/Planar-Edges)

### [LC22 - 括号生成](https://leetcode-cn.com/problems/generate-parentheses/)

::: tip 小贴士
本题要求给出具体的方案。如果只需要给出方案总数，那么结果即为卡特兰数。
:::

<Utterances />
