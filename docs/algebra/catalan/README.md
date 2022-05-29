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

## 卡特兰数的性质

- 参考资料：[Koshy et al., 2006](https://www.maa.org/sites/default/files/Koshy-CMJ-2006.pdf)

### 奇偶性

卡特兰数$C_n$是奇数，当且仅当$n=2^k-1$。

证明：

$$
C_n=\frac{(2n)!}{(n+1)!n!}=\frac{(2n-1)!!\cdot2^n}{(n+1)!}
$$

显然$(2n-1)!!$中不含$2$，所以要判断$C_n$的奇偶性，也就要判断$(n+1)!$含有多少个$2$。

这时，我们有：

$$
T=\lfloor\frac{n+1}{2}\rfloor+\lfloor\frac{n+1}{4}\rfloor+\cdots+\lfloor\frac{n+1}{2^k}\rfloor<n+1
$$

也即$T\leq n$。其中$k=\argmax_t(2^t\leq n+1)$。

下面我们要说明$n=2^k-1$是等号成立的充要条件。

充分性是显然的，将$n=2^k-1$代入上式，可得：

$$
T=2^{k-1}+2^{k-2}+\cdots+1=2^k-1=n
$$

下面说明必要性。设$n=2^k+x,0\leq x<2^k-1$，则$n+1<2^{k+1}$，也即$k=\argmax_t(2^t\leq n+1)$依然成立。

此时，原式左边变为：

$$
l.h.s=2^k-1+\lfloor\frac{x+1}{2}\rfloor+\lfloor\frac{x+1}{4}\rfloor+\cdots+\lfloor\frac{x+1}{2^k}\rfloor
$$

从而:

$$
l.h.s<2^k-1+x+1=2^k+x=n
$$

这样，我们就说明了原命题的充要性。进而可知，$C_n$为奇数，当且仅当$n=2^k-1$。

### 质数

所有卡特兰数中只有两个质数，$C_2=2$以及$C_3=5$。

## 练习题

### [BS - Planar Edges](https://binarysearch.com/problems/Planar-Edges)

### [LC22 - 括号生成](https://leetcode.cn/problems/generate-parentheses/)

::: tip 小贴士
本题要求给出具体的方案。如果只需要给出方案总数，那么结果即为卡特兰数。
:::

<Utterances />
