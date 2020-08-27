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

::: details 提示三

考虑两种转移：删除当前字母，总花费加一；保留当前字母，在AC自动机上移动。

:::

::: details 参考代码（C++）

<<<@/docs/string/aho-corasick/src/CF1400F.cpp

:::
