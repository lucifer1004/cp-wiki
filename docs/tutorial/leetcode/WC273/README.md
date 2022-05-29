# Leetcode 第273场周赛题解

## Problem A - [反转两次的数字](https://leetcode.cn/contest/problems/a-number-after-a-double-reversal/)

### 方法一：观察

对于非零的数字，必须末尾不含零，也即不能被$10$整除。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def isSameAfterReversals(self, num: int) -> bool:
        return num == 0 or num % 10 != 0
```

:::

## Problem B - [执行所有后缀指令](https://leetcode.cn/problems/execution-of-all-suffix-instructions-staying-in-a-grid/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def executeInstructions(self, n: int, startPos: List[int], s: str) -> List[int]:
        d = {'L': (0, -1), 'R': (0, 1), 'U': (-1, 0), 'D': (1, 0)}
        ans = []
        for i in range(len(s)):
            cmd = 0
            r, c = startPos
            for j in range(i, len(s)):
                nr, nc = r + d[s[j]][0], c + d[s[j]][1]
                if 0 <= nr < n and 0 <= nc < n:
                    r, c = nr, nc
                    cmd += 1
                else:
                    break
            ans.append(cmd)
        return ans
```

:::

## Problem C - [相同元素的间隔之和](https://leetcode.cn/problems/intervals-between-identical-elements/)

### 方法一：前缀和+单指针

每个数字单独处理，单指针移动过程中基于前缀和思想维护左右两端的贡献之和。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def getDistances(self, arr: List[int]) -> List[int]:
        d = collections.defaultdict(list)
        for i, num in enumerate(arr):
            d[num].append(i)
            
        ans = [0] * len(arr)
        for v in d.values():
            m = len(v)
            cval = sum(v) - v[0] * m
            for i, pos in enumerate(v):
                delta = v[i] - v[i - 1] if i >= 1 else 0
                cval += i * delta - (m - i) * delta
                ans[pos] = cval
            
        return ans
```

:::

## Problem D -[还原原数组](https://leetcode.cn/problems/recover-the-original-array/)

### 方法一：哈希表

由于$k>0$，最大的那个数必然是来自`higher`。在$N\le1000$的数据规模下，直接枚举最大的那个数对应的`lower`中的数即可。

在确定了$k$之后，基于哈希表，从最小的键开始依次处理即可。如果出现匹配不上的情况，就说明当前的$k$值不对。

- 时间复杂度$\mathcal{O}(N^2)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（Python 3）

```python
class Solution:
    def recoverArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        nums.sort()
        keys = sorted(list(set(nums)))
        for i in range(n - 2, n // 2 - 2, -1):
            delta = nums[n - 1] - nums[i]
            if delta == 0 or delta % 2 == 1:
                continue
            cnt = collections.Counter(nums)
            ok = True
            ans = []
            for key in keys:
                if cnt[key] == 0:
                    continue
                if cnt[key + delta] < cnt[key]:
                    ok = False
                    break
                cnt[key + delta] -= cnt[key]
                ans += [key + delta // 2] * cnt[key]
                cnt[key] = 0
            if ok:
                return ans
        return []
```

:::

<Utterances />
