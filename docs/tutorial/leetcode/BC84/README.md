# Leetcode 第84场双周赛题解

## Problem A - [合并相似的物品](https://leetcode.cn/problems/merge-similar-items/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def mergeSimilarItems(self, items1: List[List[int]], items2: List[List[int]]) -> List[List[int]]:
        cnt = collections.Counter()
        for v, w in items1:
            cnt[v] += w
        for v, w in items2:
            cnt[v] += w
        return sorted([v, cnt[v]] for v in cnt)
```

:::

## Problem B - [统计坏数对的数目](https://leetcode.cn/problems/count-number-of-bad-pairs/)

### 方法一：哈希表

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countBadPairs(self, nums: List[int]) -> int:
        n = len(nums)
        cnt = collections.Counter(i - num for i, num in enumerate(nums))
        ans = n * (n - 1) // 2
        for v in cnt:
            ans -= cnt[v] * (cnt[v] - 1) // 2
        return ans
```

:::

## Problem C - [任务调度器 II](https://leetcode.cn/problems/task-scheduler-ii/)

### 方法一：模拟

注意到任务必须按顺序完成，直接模拟即可。

::: details 参考代码（Python 3）

```python
class Solution:
    def taskSchedulerII(self, tasks: List[int], space: int) -> int:
        n = len(tasks)
        last = dict()
        t = 0
        for task in tasks:
            if task in last:
                t = max(t + 1, last[task] + space + 1)
            else:
                t += 1
            last[task] = t
        return t
```

:::


## Problem D - [将数组排序的最少替换次数](https://leetcode.cn/problems/minimum-replacements-to-sort-the-array/)

### 方法一：贪心

从后向前处理，在尽可能少分组的情况下，使得分组中的最大元素不超过下一个元素。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumReplacement(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        last = nums[-1]
        for i in range(n - 2, -1, -1):
            lo = nums[i] // last
            if nums[i] % last != 0:
                lo += 1
            last = nums[i] // lo
            ans += lo - 1
        return ans
```

:::

<Utterances />
