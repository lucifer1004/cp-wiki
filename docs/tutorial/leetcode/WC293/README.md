# Leetcode 第293场周赛题解

## Problem A - [移除字母异位词后的结果数组](https://leetcode.cn/problems/find-resultant-array-after-removing-anagrams/)

### 方法一：栈

- 时间复杂度 $\mathcal{O}(\sum|S_i|\log|S_i|)$。
- 空间复杂度 $\mathcal{O}(\sum |S_i|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def removeAnagrams(self, words: List[str]) -> List[str]:
        ans = []
        for word in words:
            if len(ans) == 0 or sorted(word) != sorted(ans[-1]):
                ans.append(word)
        return ans
```

:::

## Problem B - [不含特殊楼层的最大连续楼层数](https://leetcode.cn/problems/maximum-consecutive-floors-without-special-floors/)

### 方法一：排序

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxConsecutive(self, bottom: int, top: int, special: List[int]) -> int:
        floors = [bottom - 1] + sorted(special) + [top + 1]
        return max(u - d - 1 for u, d in zip(floors[1:], floors[:-1]))
```

:::

## Problem C - [按位与结果大于零的最长组合](https://leetcode.cn/problems/largest-combination-with-bitwise-and-greater-than-zero/)

### 方法一：逐位考虑

- 时间复杂度 $\mathcal{O}(NK)$ 。
- 空间复杂度 $\mathcal{O}(N)$，可以进一步优化到 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def largestCombination(self, candidates: List[int]) -> int:
        return max(len([c for c in candidates if (c & (1 << i)) > 0]) for i in range(30))
```

:::

## Problem D - [统计区间中的整数数目](https://leetcode.cn/problems/count-integers-in-intervals/)

### 方法一：维护有序区间集合

- 添加一个新区间的均摊时间复杂度为 $\mathcal{O}(\log N)$，查询时间复杂度为 $\mathcal{O}(1)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class CountIntervals {
    set<pair<int, int>> s;
    int cnt;
public:
    CountIntervals() {
        cnt = 0;
    }
    
    void add(int left, int right) {
        auto it = s.lower_bound(make_pair(left, left));
        if (it != s.begin())
            it--;
        
        vector<pair<int, int>> to_erase;
        for (; it != s.end(); ++it) {
            auto [l, r] = *it;
            if (l > right + 1) break;
            if (r < left - 1) continue;
            left = min(left, l);
            right = max(right, r);
            to_erase.push_back(*it);
        }
        
        for (auto &p : to_erase) {
            cnt -= p.second - p.first + 1;
            s.erase(p);
        }
        
        s.emplace(left, right);
        cnt += right - left + 1;
    }
    
    int count() {
        return cnt;
    }
};
```

:::

<Utterances />
