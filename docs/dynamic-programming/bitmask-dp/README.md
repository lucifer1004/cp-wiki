---
sidebarDepth: 3
---

# 状态压缩动态规划

状态压缩动态规划（英文一般称为bitmask DP），指的是一类使用二进制（也有使用三进制等的情形）数来表示动态规划中的状态的动态规划方法。其时间复杂度一般包含$2^N$或$3^N$（如果进行了子集枚举）的项，因此是指数而非多项式时间的算法。

在编程竞赛中，状态压缩动态规划的一个明显标志是题目中某一参数的上限为一个很小的常数（通常不超过20）。同时，题目中存在某种非此即彼的状态，比如工作是否完成，灯是否点亮，等式是否满足，数值的奇偶，等等。

## 练习题

### [LC464 - 我能赢吗](https://leetcode-cn.com/problems/can-i-win/)（[题解](https://leetcode-cn.com/problems/can-i-win/solution/zhuang-tai-ya-suo-ji-yi-hua-di-gui-by-lucifer1004/)）

### [LC465 - 最优账单平衡](https://leetcode-cn.com/problems/optimal-account-balancing/solution/)（[题解](https://leetcode-cn.com/problems/optimal-account-balancing/solution/zhuang-tai-ya-suo-dong-tai-gui-hua-by-lu-2qrt/)）

本题与[BS - Minimum Number of Transfers to Settle Debts](https://binarysearch.com/problems/Minimum-Number-of-Transfers-to-Settle-Debts)（[English Editorial](https://binarysearch.com/problems/Minimum-Number-of-Transfers-to-Settle-Debts/editorials/3448671)）是相同的。

::: details 提示一

如果$k$个人的总收支是0，则我们可以用最多$k-1$次操作使得其中每一个人的收支都变为0。因此，本题实际上就是要将这些人分成总收支为0的小组，且使得小组的数目最多。

:::

::: details 提示二

预处理每一个分组的总收支后，进行状态压缩动态规划。注意这里需要用到[枚举子集](/basic/enumerate/#枚举子集)的方法。

:::

### [LC691 - 贴纸拼词](https://leetcode-cn.com/problems/stickers-to-spell-word/)（[题解](https://leetcode-cn.com/problems/stickers-to-spell-word/solution/zhuang-tai-ya-suo-dpji-you-hua-by-lucifer1004/)）

::: details 提示

优化枚举顺序，可以减少重复计算，从而加快计算速度。

:::

### [LC864 - 获取所有钥匙的最短路径](https://leetcode-cn.com/problems/shortest-path-to-get-all-keys/)（[题解](https://leetcode-cn.com/problems/shortest-path-to-get-all-keys/solution/zhuang-tai-ya-suo-bfs-by-lucifer1004/)）

### [LC1349 - 参加考试的最大学生数](https://leetcode-cn.com/problems/maximum-students-taking-exam/)（[题解](https://leetcode-cn.com/problems/maximum-students-taking-exam/solution/zhuang-tai-ya-suo-dp-by-lucifer1004/)）

::: tip 注意

本题有多项式时间的网络流解法。

:::

### [LC1371 - 每个元音包含偶数次的最长子字符串](https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)（[题解](https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/solution/zhuang-tai-ya-suo-ji-lu-yuan-yin-zi-mu-chu-xian-qi/)）

### [LC1434 - 每个人戴不同帽子的方案数](https://leetcode-cn.com/problems/number-of-ways-to-wear-different-hats-to-each-other/)（[题解](https://leetcode-cn.com/problems/number-of-ways-to-wear-different-hats-to-each-other/solution/zhuang-tai-ya-suo-ji-lu-mei-ge-ren-shi-fou-dai-sha/)）

::: details 提示

表示帽子的状态（是否分配给了人）需要$2^{40}$个数，但注意到$N\leq10$，我们可以反过来表示人的状态（是否戴上了帽子），这样最多只有$2^{10}$个状态。

:::

### [LC1494 - 并行课程 II](https://leetcode-cn.com/problems/parallel-courses-ii/)

### [LC1595 - 连通两组点的最小成本](https://leetcode-cn.com/problems/minimum-cost-to-connect-two-groups-of-points/)（[题解](https://leetcode-cn.com/problems/minimum-cost-to-connect-two-groups-of-points/solution/zhuang-tai-ya-suo-dpmei-ju-zi-ji-you-hua-by-lucife/)）

::: tip 注意

本题有多项式时间的网络流解法。

:::

### [LC1723 - 完成所有工作的最短时间](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/)（[题解](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/solution/er-fen-zhuang-ya-dp-by-lucifer1004-198p/)）

::: details 提示

二分答案 + 状态压缩动态规划。

:::

### [LCP13 - 寻宝](https://leetcode-cn.com/problems/xun-bao/)（[题解](https://leetcode-cn.com/problems/xun-bao/solution/bfszhuang-tai-ya-suo-dp-by-lucifer1004/)）

::: details 提示

BFS预处理距离之后进行状态压缩动态规划。这里的状态为机关的打开情况。

:::

### [ABC152F - Tree and Constraints](https://atcoder.jp/contests/abc152/tasks/abc152_f)

::: details 提示

最短路径 + 状态压缩动态规划。

:::

### [ABC195F - Coprime Present](https://atcoder.jp/contests/abc195/tasks/abc195_f)（[English Editorial](/en/tutorial/atcoder/ABC195/#problem-f-coprime-present)）

::: details 提示

72以内的质数一共有20个。

:::
