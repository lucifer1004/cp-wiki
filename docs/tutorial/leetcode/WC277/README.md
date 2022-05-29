# Leetcode 第277场周赛题解

## Problem A - [元素计数](https://leetcode.cn/problems/count-elements-with-strictly-smaller-and-greater-elements/)

### 方法一：模拟

只要不是最小值或最大值，就是符合要求的数。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countElements(self, nums: List[int]) -> int:
        lo, hi = min(nums), max(nums)
        return len([num for num in nums if num != lo and num != hi])
```

:::

## Problem B - [按符号重排数组](https://leetcode.cn/problems/rearrange-array-elements-by-sign/)

### 方法一：模拟

将正数和负数分为两组，然后构造结果即可。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def rearrangeArray(self, nums: List[int]) -> List[int]:
        pos = [num for num in nums if num > 0]
        neg = [num for num in nums if num < 0]
        return list(itertools.chain(*[[p, n] for p, n in zip(pos, neg)]))
```

:::

## Problem C - [找出数组中的所有孤独数字](https://leetcode.cn/problems/find-all-lonely-numbers-in-the-array/)

### 方法一：哈希表

哈希表计数之后逐个判断即可。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findLonely(self, nums: List[int]) -> List[int]:
        cnt = collections.Counter(nums)
        return [num for num in nums if cnt[num] == 1 and (num - 1) not in cnt and (num + 1) not in cnt]
```

:::

## Problem D - [基于陈述统计最多好人数](https://leetcode.cn/problems/maximum-good-people-based-on-statements/)

### 方法一：枚举

二进制枚举哪几个是好人，之后判断是否存在矛盾。

- 时间复杂度$\mathcal{O}(N^2\cdot2^N)$
- 空间复杂度$\mathcal{O}(1)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumGood(vector<vector<int>>& s) {
        int n = s.size();
        int ans = 0;
        for (int i = (1 << n) - 1; i >= 0; --i) {
            int m = __builtin_popcount(i);
            if (m < ans)
                continue;
            bool valid = true;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    for (int k = 0; k < n; ++k) {
                        if ((s[j][k] == 0 && ((i & (1 << k)) > 0)) || (s[j][k] == 1 && ((i & (1 << k)) == 0))) {
                            valid = false;
                            break;
                        }
                    }
                }
                if (!valid)
                    break;
            }
            if (valid)
                ans = max(ans, m);
        }
        return ans;
    }
};
```

:::

<Utterances />
