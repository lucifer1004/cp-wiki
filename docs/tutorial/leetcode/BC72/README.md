# Leetcode 第72场双周赛题解

## Problem A - [统计数组中相等且可以被整除的数对](https://leetcode.cn/problems/count-equal-and-divisible-pairs-in-an-array/)

### 方法一：暴力

直接枚举所有数对并检查是否符合要求。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countPairs(self, nums: List[int], k: int) -> int:
        ans = 0
        n = len(nums)
        for i in range(n):
            for j in range(i + 1, n):
                if nums[i] == nums[j] and (i * j) % k == 0:
                    ans += 1
        return ans
```

:::

## Problem B - [找到和为给定整数的三个连续整数](https://leetcode.cn/problems/find-three-consecutive-integers-that-sum-to-a-given-number/)

### 方法一：数学

三个连续整数 $i-1,i,i+1$ 的和为 $3i$，因此当且仅当给定整数为 3 的倍数时有解。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def sumOfThree(self, num: int) -> List[int]:
        return [] if num % 3 != 0 else [num // 3 - 1, num // 3, num // 3 + 1]
```

:::

## Problem C - [拆分成最多数目的偶整数之和](https://leetcode.cn/problems/maximum-split-of-positive-even-integers/)

### 方法一：贪心

从小到大使用所有的偶数，最后剩余部分不够大时，添加到上一个数中即可。

- 时间复杂度$\mathcal{O}(\sqrt{N})$。
- 空间复杂度$\mathcal{O}(\sqrt{N})$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumEvenSplit(self, finalSum: int) -> List[int]:
        if finalSum % 2 != 0:
            return []
        ans = []
        now = 2
        while finalSum > 0:
            if finalSum < now:
                ans[-1] += finalSum
                finalSum = 0
            else:
                ans.append(now)
                finalSum -= now
                now += 2
        return ans
```

:::

## Problem D - [统计数组中好三元组数目](https://leetcode.cn/problems/count-good-triplets-in-an-array/)

### 方法一：树状数组/线段树

首先用哈希表记录每个数在数组二中的位置，然后按照数组一的顺序依次处理。

我们考虑以当前数字作为三元组中间数字的好三元组的数目。第一个数字需要是之前已经遍历过的，并且在数组二中的位置比当前数字更靠前的；第三个数字需要是当前还没有遍历过的，并且在数组二中的位置比当前数字更靠后的。这里只对数字的位置有要求，而对数字具体的值没有要求。

如何快速求出满足条件的第一个数字和第三个数字的个数呢？

以 $[4,0,1,3,2]\quad[4,1,0,2,3]$为例，考虑我们的遍历过程：

首先处理的是 4，此时数组二中的出现情况为：

$[4,X,X,X,X]$

我们需要统计的是 4 之前的有值的个数（0 个），以及 4 之后的没有值的个数（4 个）。因此以 4 为中间数字能形成 0 个好三元组。

接下来是 0，此时数组二中的出现情况为：

$[4,X,0,X,X]$

0 之前有值的个数（1 个），0 之后没有值的个数（2 个）。因此以 0 为中间数字能形成 2 个好三元组。

接下来是 1，此时数组二中的出现情况为：

$[4,1,0,X,X]$

1 之前有值的个数（1 个），1 之后没有值的个数（2 个）。因此以 1 为中间数字能形成 2 个好三元组。

接下来是 3，此时数组二中的出现情况为：

$[4,1,0,X,3]$

3 之前有值的个数（3 个），3 之后没有值的个数（0 个）。因此以 3 为中间数字能形成 0 个好三元组。

最后是 2，此时数组二中的出现情况为：

$[4,1,0,2,3]$

2 之前有值的个数（3 个），2 之后没有值的个数（0 个）。因此以 2 为中间数字能形成 0 个好三元组。

最后的答案是 4。

因为我们并不关心数字具体的值，而只关心是否出现过，所以我们实际上可以把数组二的出现情况用一个 0–1 数组来表示：

$[1,0,0,0,0]\rightarrow[1,0,1,0,0]\rightarrow[1,1,1,0,0]\rightarrow[1,1,1,0,1]\rightarrow[1,1,1,1,1]$

这时可以看出，我们用树状数组（或者线段树）就能快速更新状态，并求出我们需要的两个数值（左边的 1 的个数和右边的 0 的个数）。

理清思路之后，代码的实现是比较容易的。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
template <class T> class FenwickTree {
  int limit;
  vector<T> arr;

  int lowbit(int x) { return x & (-x); }

public:
  FenwickTree(int limit) {
    this->limit = limit;
    arr = vector<T>(limit + 1);
  }

  void update(int idx, T delta) {
    for (; idx <= limit; idx += lowbit(idx))
      arr[idx] += delta;
  }

  T query(int idx) {
    T ans = 0;
    for (; idx > 0; idx -= lowbit(idx))
      ans += arr[idx];
    return ans;
  }
};

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        FenwickTree<int> occur(n);
        unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i)
            pos[nums2[i]] = i + 1;
        
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int idx = pos[nums1[i]];
            
            int left = occur.query(idx);
            int right = n - idx - (occur.query(n) - occur.query(idx));
            ans += 1LL * left * right;
            
            occur.update(idx, 1);
        }
        
        return ans;
    }
};
```

:::

<Utterances />
