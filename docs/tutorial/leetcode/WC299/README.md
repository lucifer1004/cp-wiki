# Leetcode 第299场周赛题解

## Problem A - [判断矩阵是否是一个 X 矩阵](https://leetcode.cn/problems/check-if-matrix-is-x-matrix/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(N^2)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool checkXMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (i == j || i + j == n - 1) {
                    if (grid[i][j] == 0)
                        return false;
                } else {
                    if (grid[i][j] != 0)
                        return false;
                }
            }
        return true;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def checkXMatrix(self, grid: List[List[int]]) -> bool:
        n = len(grid)
        return all(grid[i][j] == 0 for i in range(n) for j in range(n) if i + j != n - 1 and i != j) and all(grid[i][j] != 0 for i in range(n) for j in range(n) if i + j == n - 1 or i == j)
```

:::

## Problem B - [统计放置房子的方式数](https://leetcode.cn/problems/count-number-of-ways-to-place-houses/)

### 方法一：动态规划

两侧可以单独算。每侧的情况类似于 Fibonacci 数列，可以用矩阵快速幂更快地求出，但没有必要。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;

class Solution {
public:
    int countHousePlacements(int n) {
        int a = 1, b = 2;
        for (int i = 2; i <= n; ++i) {
            int tmp = b;
            b = (a + b) % MOD;
            a = tmp;
        }
        return 1LL * b * b % MOD;
    }
};
```

:::

## Problem C - [拼接数组的最大分数](https://leetcode.cn/problems/maximum-score-of-spliced-array/)

### 方法一：动态规划

求出差数组的最大子数组和即可。

- 时间复杂度 $\mathcal{O}(N)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
class Solution {
    int solve(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> d(n);
        for (int i = 0; i < n; ++i)
            d[i] = nums2[i] - nums1[i];
        
        int hi = 0, now = 0, lo = 0;
        for (int di : d) {
            now += di;
            hi = max(hi, now - lo);
            lo = min(lo, now);
        }
        
        int ans = 0;
        for (int num : nums1)
            ans += num;
        
        return ans + hi;
    }
    
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        return max(solve(nums1, nums2), solve(nums2, nums1));
    }
};
```

:::

## Problem D - [从树中删除边的最小分数](https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/)

### 方法一：树形动态规划

- 时间复杂度 $\mathcal{O}(N^2)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
class Solution {
    int n, ans, tot;
    vector<int> nums, xorsum;
    vector<vector<int>> adj;
    
    vector<int> dfs(int u, int p) {
        vector<int> values;
        xorsum[u] = nums[u];
        for (int v : adj[u]) {
            if (v == p)
                continue;
            
            auto vv = dfs(v, u);
            xorsum[u] ^= xorsum[v];
            
            for (int vvi : vv) {
                for (int vi : values) {
                    int lo = min(vi, min(vvi, tot ^ vi ^ vvi));                        
                    int hi = max(vi, max(vvi, tot ^ vi ^ vvi));
                    ans = min(ans, hi - lo);
                }
            }
            
            values.insert(values.end(), vv.begin(), vv.end());
        }
        
        if (u != 0) {
            for (int vi : values) {
                int lo = min(vi, min(xorsum[u] ^ vi, tot ^ xorsum[u]));           
                int hi = max(vi, max(xorsum[u] ^ vi, tot ^ xorsum[u]));
                ans = min(ans, hi - lo);
            }
        }
        
        values.push_back(xorsum[u]);
        return values;
    }
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        n = nums.size();
        adj = vector<vector<int>>(n);
        xorsum = vector<int>(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        tot = 0;
        for (int num : nums)
            tot ^= num;
        
        this->nums = nums;
        ans = INT_MAX;
        dfs(0, -1);
        
        return ans;
    }
};
```

<Utterances />
