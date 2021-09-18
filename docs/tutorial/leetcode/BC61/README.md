# Leetcode 第61场双周赛题解

## Problem A - [差的绝对值为 K 的数对数目](https://leetcode-cn.com/problems/count-number-of-pairs-with-absolute-difference-k/)

### 方法一：暴力穷举

枚举每一个数对，判断是否满足要求。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (abs(nums[i] - nums[j]) == k)
                    ans++;
        return ans;
    }
};
```

:::

### 方法二：计数

对于当前数字$num$，它可以与之前的$num-k$或$num+k$构成数对。因此我们在遍历过程中对数字进行计数即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countKDifference(self, nums: List[int], k: int) -> int:
        cnt = collections.Counter()
        ans = 0
        for num in nums:
            ans += cnt[num - k] + cnt[num + k]
            cnt[num] += 1
        return ans
```

:::


## Problem B - [从双倍数组中还原原数组](https://leetcode-cn.com/problems/find-original-array-from-doubled-array/)

### 方法一：贪心

计数后，按从小到大的顺序贪心处理（尽可能让$2n$与$n$匹配）即可。注意$0$需要单独考虑。

- 时间复杂度为$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findOriginalArray(self, changed: List[int]) -> List[int]:
        n = len(changed)
        cnt = collections.Counter(changed)
        keys = sorted(cnt.keys())
        ans = []
        for key in keys:
            if key == 0:
                if cnt[key] % 2 != 0:
                    return []
                else:
                    ans += [0] * (cnt[key] // 2)
            elif cnt[key] > 0:
                if cnt[key * 2] < cnt[key]:
                    return []
                else:
                    ans += [key] * cnt[key]
                    cnt[key * 2] -= cnt[key]
        return ans
```

:::


## Problem C - [出租车的最大盈利](https://leetcode-cn.com/problems/maximum-earnings-from-taxi/)

### 方法一：动态规划

将所有路程按照起点排序，然后动态规划。

这里需要在动态规划的过程中对$dp$数组求前缀最大值，注意到我们已经对路程进行排序，所以使用单指针即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        sort(rides.begin(), rides.end());
        vector<long long> dp(n + 1);
        int i = 0;
        for (auto &ride : rides) {
            while (i < ride[0]) {
                dp[i + 1] = max(dp[i + 1], dp[i]);
                i++;
            }
            dp[ride[1]] = max(dp[ride[1]], dp[ride[0]] + ride[1] - ride[0] + ride[2]);
        }
        while (i < n) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
            i++;
        }
        return dp[n];
    }
};
```

:::

## Problem D - [使数组连续的最少操作数](https://leetcode-cn.com/problems/minimum-number-of-operations-to-make-array-continuous/)

### 方法一：排序+双指针

我们考虑改变后的数组中最大的未被改变的数和最小的未被改变的数，它们的差必然小于$N$。这提示我们对原数组排序后使用双指针求解。

我们利用双指针确定左右边界，同时用一个`map`或`unordered_map`记录这段范围内有多少不同的数字，这些不同的数字也就是我们可以不用改变保留到最终结果中的数字。我们在双指针遍历过程中可以得到最多能保留的数字个数，从而就可以求出需要的最少操作次数。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = n;
        unordered_map<int, int> cnt;
        for (int i = 0, j = 0; j < nums.size(); j++) {
            cnt[nums[j]]++;
            while (nums[i] + n - 1 < nums[j]) {
                cnt[nums[i]]--;
                if (cnt[nums[i]] == 0)
                    cnt.erase(nums[i]);
                i++;
            }
            ans = min(ans, n - (int)cnt.size());
        }
        return ans;
    }
};
```

:::

### 思考

事实上，我们可以将额外的空间复杂度优化到$\mathcal{O}(1)$，想想如何做？

<Utterances />
