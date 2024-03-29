---
sidebarDepth: 3
---

# 枚举

枚举就是指尝试所有可能的情况。枚举是最基础的算法，但同样是枚举，枚举策略的好坏，将极大影响代码实现的复杂度，以及程序的运行效率。

## 枚举的顺序

枚举的顺序可能影响程序的运行效率。比如题目要求符合条件的最大的数，那么从大到小进行枚举可能就比从小到大进行枚举更加合适。

枚举的顺序还可能影响程序的正确性。比如在Floyd算法中，必须在最外层循环枚举中间点；如果把这一顺序搞错，最后就不能保证求出的解是正确的。

## 状态的表示

有这样一类可以用布尔量表示的状态，比如灯的开关，课程是否学过，某个人是否被选取。这样的状态，我们可以用一个二进制数（或者当$n$更大时，可以使用C++ STL中的`bitset`）来进行表示。这种用二进制数表示状态的方法被称为**状态压缩**。状态压缩在很多题目中都有重要的价值。

## 枚举子集

假设我们有一个用二进制数$x$表示的集合（某一位为$1$代表集合含有对应元素，反之则代表集合中不含对应元素），我们应该如何来枚举它的子集？

朴素的想法是，枚举所有小于等于该数的二进制数，逐个检查当前枚举到的$y$其是否是$x$的子集（是否满足$x|y=x$）。

还可以做得更好吗？答案是肯定的。

```cpp
for (int i = 1; i < (1 << n); ++i) {
    for (int j = i; j; j = (j - 1) & i) {
        // ...
    }
}
```

上面这段代码中最关键的部分就是`j = (j - 1) & i`。这一步操作，首先将$j$减一，从而把$j$最右边的$1$变成了$0$，然后把之后的所有$0$变成了$1$。再与$i$求与，就保证了得到的结果是$i$的子集，并且，它一定是所有是$i$的子集，并且小于$j$的二进制数中最大的一个。利用这一方式，我们可以倒序枚举出$j$的所有子集，并且中间不会经过任何不合法的状态。

如果我们对$n$个元素的所有子集进行子集的枚举，上面的两重循环可以在$O(3^n)$的时间复杂度内完成。

## 折半搜索

折半搜索（Meet in the middle），是一种对暴力枚举的优化策略。通过将原数据集分为两部分，然后对两部分分别进行枚举，再对两部分各自的搜索结果进行组合。如果最后一步的组合中，可以利用哈希表等将对二元组的枚举变为对一侧元素的枚举，就可以将整体的时间复杂度开方，从$O(2^N)$降低到$O(2^{N/2})$。

## 学习资源

### [Matters Computational](https://www.springer.com/gp/book/9783642147630)

- 第六章：枚举组合
- 第七章：枚举分组（将$n$个球放到$k$个盒子里）
- 第八章：枚举子集
- 第十章：枚举排列
- 第十三章：枚举可重集（`multiset`）的子集
- 第十五章：枚举括号序
- 第十六章：枚举整数拆分
- 第十七章：枚举集合拆分

本书包含大量奇技淫巧，强烈建议收藏一本。

### 参考链接

- [Geeks for Geeks - Meet in the middle](https://www.geeksforgeeks.org/meet-in-the-middle/)
- [OI Wiki - 折半搜索](https://oi-wiki.org/search/bidirectional/#_2)

## 练习题

### [LC46 - 全排列](https://leetcode.cn/problems/permutations/)

枚举不含重复元素数组的全排列。

### [LC47 - 全排列 II](https://leetcode.cn/problems/permutations-ii/)

枚举含有重复元素数组的全排列。

### [LC1494 - 并行课程 II](https://leetcode.cn/problems/parallel-courses-ii/) 

枚举子集。

### [LC805 - 数组的均值分割](https://leetcode.cn/problems/split-array-with-same-average/submissions/)

折半搜索。
