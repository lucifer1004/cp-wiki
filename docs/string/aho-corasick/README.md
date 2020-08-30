---
sidebarDepth: 3
---

# AC自动机

## 练习题

### [洛谷 P5357 - AC自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357)

### [CF1400F - x-prime Substrings](https://codeforces.com/contest/1400/problem/F)

::: details 提示一

可以通过DFS枚举出所有的x-prime string。

:::

::: details 提示二

利用所有的x-prime string构建AC自动机。

:::

:::: details 提示三

考虑两种转移：删除当前字母，总花费加一；保留当前字母，在AC自动机上移动。

::: tip 小贴士

本题中，由于任意一个$x$-prime串都不会是其他$x$-prime串的后缀（否则它们的数位和不等），所以在AC自动机上移动时，并不需要利用`fail`指针逐级上跳。但务必注意，只有很少的题目能够满足这一条件，不要因此在其他AC自动机的题目上吃到WA（~~就像我在[ADAJOBS](./#spoj-ada-and-jobs)那题一样~~）。

:::

::::

::: details 参考代码（C++）

<<<@/docs/string/aho-corasick/src/CF1400F.cpp

:::

### [SPOJ - Ada and Jobs](https://www.spoj.com/problems/ADAJOBS/)

本题的难点在于，字符串是动态添加的，但我们不可能在每次查询时都重新构建整个AC自动机。那么应该如何做呢？

::: details 提示一

离线所有修改操作和查询，在构建AC自动机时给每个终止节点一个时间戳（代表它是第几个被添加的字符串）；同时，记录每个查询操作发生时字典中总单词数。这样，我们只需要构建一次AC自动机。在每次匹配的过程中，我们需要匹配到时间戳小于等于对应查询操作时间戳的终止节点才算是匹配成功。

:::

::: details 提示二

在匹配过程中，并不需要逐级跳`fail`指针来查找是否存在匹配。可以在构建自动机时顺便将时间戳下推。

:::

::: details 参考代码（C++）

<<<@/docs/string/aho-corasick/src/SPOJ-ADAJOBS.cpp

:::
