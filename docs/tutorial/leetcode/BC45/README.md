# Leetcode 第45场双周赛题解

## Problem A - [唯一元素的和](https://leetcode-cn.com/problems/sum-of-unique-elements/)

计数然后累加符合要求的元素即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def sumOfUnique(self, nums: List[int]) -> int:
        cnt = collections.Counter(nums)
        ans = 0
        for key in cnt:
            if cnt[key] == 1:
                ans += key
        return ans
```

:::

## Problem B - [任意子数组和的绝对值的最大值](https://leetcode-cn.com/problems/maximum-absolute-sum-of-any-subarray/)

跟子数组和的最大值这道经典题其实很像，只不过我们除了要记录以当前位置结尾的最大值，还需要记录一个最小值。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        ans = 0
        lo = 0
        hi = 0
        for num in nums:
            lo = min(0, lo + num)
            hi = max(0, hi + num)
            ans = max(ans, abs(lo), abs(hi))
        return ans
```

:::

## Problem C - [删除字符串两端相同字符后的最短长度](https://leetcode-cn.com/problems/minimum-length-of-string-after-deleting-similar-ends/)

因为并不存在决策（一定是能删则删），所以只要一直按要求模拟即可。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumLength(string s) {
        int n = s.size();
        int l = 0, r = n - 1;
        while (l < r && s[l] == s[r]) {
            int nl = l, nr = r;
            while (nl + 1 < n && s[nl + 1] == s[l])
                nl++;
            while (nr - 1 >= 0 && s[nr - 1] == s[r])
                nr--;
            l = nl + 1, r = nr - 1;
        }
        return max(0, r - l + 1);
    }
};
```

:::

## Problem D - [最多可以参加的会议数目 II](https://leetcode-cn.com/problems/maximum-number-of-events-that-can-be-attended-ii/)

离散化之后，扫描进行动态规划即可。

- 时间复杂度$\mathcal{O}(N(K+\log N))$
- 空间复杂度$\mathcal{O}(NK)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        set<int> s;
        for (auto &v : events)
            s.insert(v[0]), s.insert(v[1]);
        unordered_map<int, int> mp;
        int idx = 0;
        for (int i : s)
            mp[i] = ++idx;
        vector<vector<pair<int, int>>> end(idx + 1);
        for (auto &v : events) {
            end[mp[v[1]]].emplace_back(mp[v[0]], v[2]);
        }
                
        vector<vector<int>> dp(idx + 1, vector<int>(k + 1));
        dp[0][0] = 0;
        int ans = 0;
        for (int i = 1; i <= idx; ++i) {
            for (int j = k; j >= 0; --j) {
                dp[i][j] = dp[i - 1][j];
                if (j < k) {
                    for (auto [start, value] : end[i])
                        dp[i][j + 1] = max(dp[i][j + 1], dp[start - 1][j] + value);
                }
            }
        }
        
        for (int i = 1; i <= k; ++i)
            ans = max(ans, dp[idx][i]);
        
        return ans;
    }
};
```

:::

<Utterances />
