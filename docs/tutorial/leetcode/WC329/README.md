# Leetcode 第329场周赛题解

## Problem A - [交替数字和](https://leetcode.cn/contest/weekly-contest-329/problems/alternating-digit-sum/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(\log N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def alternateDigitSum(self, n: int) -> int:
        return sum((1 - i % 2 * 2) * d for i, d in enumerate(map(int, str(n))))
```

:::

## Problem B - [根据第 K 场考试的分数排序](https://leetcode.cn/problems/sort-the-students-by-their-kth-score/)

### 方法一：排序

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(NM)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def sortTheStudents(self, score: List[List[int]], k: int) -> List[List[int]]:
        return sorted(score, key=lambda x: -x[k])
```

:::

## Problem C - [执行逐位运算使字符串相等](https://leetcode.cn/problems/apply-bitwise-operations-to-make-strings-equal/)

### 方法一：找规律

- 时间复杂度 $\mathcal{O}(N)$ 。
- 空间复杂度 $\mathcal{O}(1)$ 。

::: details 参考代码（Python 3）

```python
class Solution:
    def makeStringsEqual(self, s: str, target: str) -> bool:
        return s == target or ('1' in s and '1' in target)
```

:::

## Problem D - [拆分数组的最小代价](https://leetcode.cn/problems/minimum-cost-to-split-an-array/)

### 方法一：朴素动态规划

- 时间复杂度 $\mathcal{O}(N^2)$ 。
- 空间复杂度 $\mathcal{O}(N^2)$ 。

::: details 参考代码（Python 3）

```python
class Solution:
    def minCost(self, nums: List[int], k: int) -> int:
        n = len(nums)
        c = [[0] * n for _ in range(n)]
        dp = [int(1e18)] * n
        dp[0] = k
        c[0][nums[0]] = 1
        for i in range(1, n):
            dp[i] = min(dp[:i]) + k
            num = nums[i]
            c[i][num] = 1
            for j in range(i):
                c[j][num] += 1
                if c[j][num] == 2:
                    dp[j] += 2
                elif c[j][num] > 2:
                    dp[j] += 1
        return min(dp)
```

:::

### 方法二：线段树（区间加，区间最小值）优化

- 时间复杂度 $\mathcal{O}(N\log N)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
#include <atcoder/lazysegtree>

using ll = long long;
using S = ll;
using F = ll;

S op(S a, S b) { return min(a, b); }
S e() { return 1e18; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

class Solution {
  public:
    int minCost(vector<int>& nums, int k) {
        int n = nums.size();
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
        unordered_map<int, vector<int>> pos;
        seg.set(0, k);
        pos[nums[0]].push_back(0);
        for (int i = 1; i < n; ++i) {
            int num = nums[i];
            seg.set(i, seg.prod(0, i) + k);
            auto& p = pos[num];
            int m = p.size();
            if (m >= 2) {
                seg.apply(0, p[m - 2] + 1, 1);
                seg.apply(p[m - 2] + 1, p[m - 1] + 1, 2);
            } else if (m == 1) {
                seg.apply(0, p[0] + 1, 2);
            }
            p.push_back(i);
        }

        return seg.all_prod();
    }
};
```

<Utterances />
