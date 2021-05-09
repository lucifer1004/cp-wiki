# Leetcode 第240场周赛题解

## Problem A - [人口最多的年份](https://leetcode-cn.com/problems/maximum-population-year/)

> 本题是[存活人数](https://leetcode-cn.com/problems/living-people-lcci/)的数据弱化版本。

### 方法一：暴力

本题数据范围很小，可以暴力求解。对于每一个人，逐年遍历计数；最后求出最大值。

- 时间复杂度$\mathcal{O}(ND)$。
- 空间复杂度$\mathcal{O}(D)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumPopulation(self, logs: List[List[int]]) -> int:
        cnt = [0] * 2051
        for b, d in logs:
            for j in range(b, d):
                cnt[j] += 1
        hi = 1950
        for i in range(1950, 2050):
            if cnt[i] > cnt[hi]:
                hi = i
        return hi
```

:::

### 方法二：差分数组

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<int> cnt(101);
        for (auto &log : logs)
            cnt[log[0] - 1950]++, cnt[log[1] - 1950]--;
        int hi = 0;
        for (int i = 1; i < 101; ++i) {
            cnt[i] += cnt[i - 1];
            if (cnt[i] > cnt[hi])
                hi = i;
        }
        return hi + 1950;
    }
};
```

:::

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度为$\mathcal{O}(D)$。

## Problem B - [下标对中的最大距离](https://leetcode-cn.com/problems/maximum-distance-between-a-pair-of-values/)

### 方法一：双指针

利用两个数组均为非递增数组的条件，双指针求解。

- 时间复杂度$\mathcal{O}(N+M)$。
- 不考虑两个输入数组，空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        int ans = 0;
        int ptr = -1;
        for (int i = 0; i < n; ++i) {
            while (ptr + 1 < m && nums1[i] <= nums2[ptr + 1])
                ptr++;
            ans = max(ans, ptr - i);
        }
        return ans;
    }
};
```

:::

## Problem C - [子数组最小乘积的最大值](https://leetcode-cn.com/problems/maximum-subarray-min-product/)

### 方法一：前缀和+单调栈

经典单调栈题目。因为数组元素都为正数，所以子数组最小值的元素位置一定时，子数组长度越大，得到的乘积越大。

我们利用单调栈可以求出每个元素作为最小值时的最长子数组，再利用预计算的前缀和求得乘积。最后取所有乘积的最大值即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();
        vector<ll> s(n + 1);
        for (int i = 1; i <= n; ++i)
            s[i] = s[i - 1] + nums[i - 1];
        
        vector<int> l(n, 0), r(n, n - 1);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] > nums[i]) {
                r[st.top()] = i - 1;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && nums[st.top()] > nums[i]) {
                l[st.top()] = i + 1;
                st.pop();
            }
            st.push(i);
        }
        
        ll ans = 0;
        for (int i = 0; i < n; ++i)
            ans = max(ans, (s[r[i] + 1] - s[l[i]]) * nums[i]);
        
        return ans % MOD;
    }
};
```

:::

## Problem D - [有向图中最大颜色值](https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/)

### 方法一：拓扑排序+DAG上动态规划

首先利用拓扑排序判断是否有环，同时可以得到拓扑序列。

按照拓扑序列反向进行动态规划即可。

在动态规划时，我们可以每次只考虑一种字母。每个字母出现次数最大值的最大值即为我们需要的答案。

- 时间复杂度$\mathcal{O}((N+M)|\sum|)$。
- 空间复杂度$\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<int> deg(n);
        vector<vector<int>> adj(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1];
            deg[v]++;
            adj[u].emplace_back(v);
        }
        
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (deg[i] == 0)
                q.push(i);
        }
        
        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.emplace_back(u);
            for (int v : adj[u]) {
                deg[v]--;
                if (deg[v] == 0)
                    q.push(v);
            }
        }
        
        if (topo.size() != n)
            return -1;
        
        int ans = 0;
        for (int color = 0; color < 26; ++color) {
            vector<int> dp(n);
            for (int i = n - 1; i >= 0; --i) {
                int u = topo[i];
                for (int v : adj[u])
                    dp[u] = max(dp[u], dp[v]);
                if (colors[u] - 'a' == color)
                    dp[u]++;
                ans = max(ans, dp[u]);
            }
        }
        
        return ans;
    }
};
```

:::


<Utterances />
