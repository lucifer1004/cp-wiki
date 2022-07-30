# Leetcode 第302场周赛题解

## Problem A - [数组能形成多少数对](https://leetcode.cn/problems/maximum-number-of-pairs-in-array/)

### 方法一：暴力

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def numberOfPairs(self, nums: List[int]) -> List[int]:
        cnt = collections.Counter(nums)
        prs = sum(cnt[key] // 2 for key in cnt)
        return [prs, len(nums) - prs * 2]
```

:::

## Problem B - [数位和相等数对的最大和](https://leetcode.cn/problems/max-sum-of-a-pair-with-equal-sum-of-digits/)

### 方法一：暴力

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        v = collections.defaultdict(list)
        for num in nums:
            v[sum(map(int, str(num)))].append(num)
        ans = -1
        for num in v:
            if len(v[num]) >= 2:
                v[num].sort(reverse=True)
                ans = max(ans, v[num][0] + v[num][1])
        return ans
```

:::

## Problem C - [裁剪数字后查询第 K 小的数字](https://leetcode.cn/problems/query-kth-smallest-trimmed-number/)

### 方法一：暴力

- 时间复杂度 $\mathcal{O}(Q\sum |W_i|\log\sum |W_i|)$ 。
- 空间复杂度 $\mathcal{O}(\sum |W_i|)$ 。

::: details 参考代码（Python 3）

```python
class Solution:
    def smallestTrimmedNumbers(self, nums: List[str], queries: List[List[int]]) -> List[int]:
        m = len(nums[0])
        ans = []
        for k, trim in queries:
            clipped = [(num[-trim:], i) for i, num in enumerate(nums)]
            clipped.sort()
            ans.append(clipped[k - 1][1])
        return ans
```

:::

### 方法二：基数排序（略）

## Problem D - [使数组可以被整除的最少删除次数](https://leetcode.cn/problems/minimum-deletions-to-make-array-divisible/)

### 方法一：数学

- 时间复杂度 $\mathcal{O}(N\log N)$ 。
- 空间复杂度 $\mathcal{O}(1)$ 。

::: details 参考代码（Python 3）

```python
from math import gcd

class Solution:
    def minOperations(self, nums: List[int], numsDivide: List[int]) -> int:
        g = 0
        for num in numsDivide:
            g = gcd(g, num)
        nums.sort()
        for i in range(len(nums)):
            if g % nums[i] == 0:
                return i
        return -1
```

<Utterances />
