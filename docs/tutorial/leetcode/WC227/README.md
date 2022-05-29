# Leetcode 第227场周赛题解

## Problem A - [检查数组是否经排序和轮转得到](https://leetcode.cn/problems/check-if-array-is-sorted-and-rotated/)

### 方法一：暴力

因为数据范围比较小，所以暴力枚举轮转是完全可行的。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def check(self, nums: List[int]) -> bool:
        asc = sorted(nums)
        for i in range(0, len(nums)):
            rot = nums[i:] + nums[:i]
            if rot == asc:
                return True
        return False
```

:::

### 方法二：利用有序数组的性质

一个长度大于$1$的升序数组，无论怎么轮转，只会出现一处相邻位置为递减（这里的“相邻位置”包括了最后一个元素和第一个元素相邻）的情况。反之，如果一个数组相邻位置为递减只有一次，那么一定可以通过轮转得到排序数组。

因此，我们只需要检查相邻位置为递减的次数即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Rust）

```rust
impl Solution {
    pub fn check(nums: Vec<i32>) -> bool {
        let mut dec = 0;
        for i in 0..nums.len() {
            let nxt = nums[(i + 1) % nums.len()];
            if nums[i] > nxt {
                dec += 1;
            }
        }
        dec <= 1
    }
}
```

:::

## Problem B - [移除石子的最大得分](https://leetcode.cn/problems/maximum-score-from-removing-stones/)

贪心地用最大的那堆跟另外两堆先匹配，另外两堆优先选择剩下数量较多的那堆。

如果最后另外两堆还有剩余，按照上面的取法，这两堆剩余数量之差不会超过$1$，所以能够最大程度配对。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumScore(self, a: int, b: int, c: int) -> int:
        hi = max(a, b, c)
        lo = min(a, b, c)
        mid = sum([a, b, c]) - hi - lo
        ans = 0
        ans += min(hi, lo + mid)
        if lo + mid > hi:
            ans += (lo + mid - hi) // 2
        return ans
```

:::

## Problem C - [构造字典序最大的合并字符串](https://leetcode.cn/problems/largest-merge-of-two-strings/)

### 方法一：贪心

每次贪心选取两个字符串头部较大的那一个。如果相等，则一直向后比较。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string largestMerge(string word1, string word2) {
        string ans;
        int n = word1.size(), m = word2.size();
        int l = 0, r = 0;
        auto check = [&](int i, int j) {
            while (i < n && j < m) {
                if (word1[i] > word2[j]) {
                    return true;
                }
                if (word1[i] < word2[j]) {
                    return false;
                }
                i++;
                if (i == n)
                    return false;
                j++;
                if (j == m)
                    return true;
            }
            return true;
        };
        while (l < n || r < m) {
            if (r == m || (l < n && check(l, r))) {
                ans.push_back(word1[l]);
                l++;
            } else {
                ans.push_back(word2[r]);
                r++;
            }
        }
        return ans;
    }
};
```

:::

### 方法二：后缀数组优化（略）

本题利用后缀数组可以优化到线性复杂度，但这已经远远超出了面试的要求。

## Problem D - [最接近目标值的子序列和](https://leetcode.cn/problems/closest-subsequence-sum/)

本题和[ABC184F - Programming Contest](https://atcoder.jp/contests/abc184/tasks/abc184_f)是一样的。其核心思想是[折半搜索（Meet in the middle）](/basic/enumerate/#%E6%8A%98%E5%8D%8A%E6%90%9C%E7%B4%A2)。

折半搜索往往可以从题目的数据范围中得到暗示。$40$是最常见的标志，因为$2^{40}$远远超过了一般的时间限制，但$2^{20}$则是较容易处理的。

### 方法一：折半搜索

本题中，我们可以将原数组分为两部分，分别枚举两部分可能得到的子集和，然后将两个子集和分别排序（或使用有序数据结构进行维护，如平衡二叉搜索树），再使用双指针等方法求解答案。

- 时间复杂度$\mathcal{O}(N\cdot2^{N/2})$。
- 空间复杂度$\mathcal{O}(2^{N/2})$。

::: details 参考代码（C++，平衡二叉搜索树+二分查找）

```cpp
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int left = (n + 1) / 2;
        set<int> L, R;
        vector<int> sl(1 << left), sr(1 << (n - left));
        L.insert(0), R.insert(0);
        for (int i = 0; i < (1 << left); ++i) {
            int s = 0;
            for (int j = 0; j < left; ++j)
                if (i & (1 << j)) {
                    L.insert(sl[i] = sl[i ^ (1 << j)] + nums[j]);
                    break;
                }
        }
        
        for (int i = 0; i < (1 << (n - left)); ++i) {
            int s = 0;
            for (int j = 0; j < (n - left); ++j)
                if (i & (1 << j)) {
                    R.insert(sr[i] = sr[i ^ (1 << j)] + nums[j + left]);
                    break;
                }
        }
        
        int ans = INT_MAX;
        for (int i : L) {
            auto it = R.lower_bound(goal - i);
            if (it != R.end())
                ans = min(ans, abs(*it + i - goal));
            if (it != R.begin())
                ans = min(ans, abs(*prev(it) + i - goal));
        }
        
        return ans;
    }
};
```

:::

实际运行下来，排序+双指针的方法要快上不少。并且这里不需要去重！如果用哈希表等进行去重，对于随机数据来说，时间开销反而是增加的。

::: details 参考代码（C++, 排序+双指针）

```cpp
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int left = (n + 1) / 2;
        vector<int> sl(1 << left), sr(1 << (n - left));
        for (int i = 0; i < (1 << left); ++i) {
            int s = 0;
            for (int j = 0; j < left; ++j)
                if (i & (1 << j)) {
                    sl[i] = sl[i ^ (1 << j)] + nums[j];
                    break;
                }
        }
        
        for (int i = 0; i < (1 << (n - left)); ++i) {
            int s = 0;
            for (int j = 0; j < (n - left); ++j)
                if (i & (1 << j)) {
                    sr[i] = sr[i ^ (1 << j)] + nums[j + left];
                    break;
                }
        }
        
        int ans = INT_MAX;
        sort(sl.begin(), sl.end()), sort(sr.begin(), sr.end());

        int l = 0, r = sr.size() - 1;
        while (l < sl.size() && r >= 0) {
            ans = min(ans, abs(sl[l] + sr[r] - goal));
            if (sl[l] + sr[r] > goal)
                r--;
            else if (sl[l] + sr[r] < goal)
                l++;
            else
                break;
        }
        
        return ans;
    }
};
```

:::

### 方法二：子集和枚举的优化

事实上，我们可以将子集和的枚举和排序两步操作合二为一，也即直接得到有序的子集和。

优化的具体方法是：

- 以$[0]$作为初始状态
- 每次，我们使用双指针方法进行$[a_1,a_2,a_3,\dots,a_k]$与$[a_1+x,a_2+x,a_3+x,\dots,a_k+x]$两个有序数组的归并

得到有序子集和之后的处理和上面相同。

- 时间复杂度$\mathcal{O}(2^{N/2})$。
- 空间复杂度$\mathcal{O}(2^{N/2})$。

::: details 参考代码（C++）

```cpp
class Solution {
    vector<int> subset_sum(vector<int> &nums, int l, int r) {
        int tot = 1 << (r - l + 1);
        vector<int> ans(tot), nxt(tot);
        for (int i = l; i <= r; ++i) {
            int p0 = 0, p1 = 0, limit = 1 << (i - l);
            cout << p0 + p1 << " ";
            while (p0 < limit || p1 < limit) {
                if (p1 == limit || (p0 < limit && ans[p0] <= ans[p1] + nums[i]))
                    nxt[p0 + p1] = ans[p0], p0++;
                else 
                    nxt[p0 + p1] = ans[p1] + nums[i], p1++;
            }
            swap(ans, nxt);
        }
        return ans;
    }

public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int left = (n + 1) / 2;
        vector<int> sl = subset_sum(nums, 0, left - 1), sr = subset_sum(nums, left, n - 1);
        
        int ans = INT_MAX;

        int l = 0, r = sr.size() - 1;
        while (l < sl.size() && r >= 0) {
            ans = min(ans, abs(sl[l] + sr[r] - goal));
            if (sl[l] + sr[r] > goal)
                r--;
            else if (sl[l] + sr[r] < goal)
                l++;
            else
                break;
        }
        
        return ans;
    }
};
```

:::

<Utterances />
