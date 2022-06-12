# Leetcode 第297场周赛题解

## Problem A - [计算应缴税款总额](https://leetcode.cn/problems/calculate-amount-paid-in-taxes/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def calculateTax(self, brackets: List[List[int]], income: int) -> float:
        ans = 0.0
        last = 0
        for u, p in brackets:
            t = min(income - last, u - last)
            ans += t * p / 100
            last = u
            if income <= u:
                break
        return ans
```

:::

## Problem B - [网格中的最小路径代价](https://leetcode.cn/problems/minimum-path-cost-in-a-grid/)

### 方法一：动态规划

排序后从小到大分组即可。

- 时间复杂度 $\mathcal{O}(NM^2)$。
- 空间复杂度 $\mathcal{O}(M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int n = grid.size(), m = grid[0].size();
        vector<int> dp(grid[0].begin(), grid[0].end());
        for (int i = 1; i < n; ++i) {
            vector<int> ndp(m, INT_MAX);
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < m; ++k) {
                    ndp[k] = min(ndp[k], grid[i][k] + dp[j] + moveCost[grid[i - 1][j]][k]);
                }
            }
            dp = move(ndp);
        }
        return *min_element(dp.begin(), dp.end());
    }
};
```

:::

## Problem C - [公平分发饼干](https://leetcode.cn/problems/fair-distribution-of-cookies/)

### 方法一：状态压缩动态规划

- 时间复杂度 $\mathcal{O}(N\cdot2^N+K\cdot3^N)$ 。
- 空间复杂度 $\mathcal{O}(K\cdot2^N)$ 。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
        int n = cookies.size();
        vector<int> sum(1 << n);
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    sum[i] = sum[i ^ (1 << j)] + cookies[j];
                    break;
                }
            }
        }
        
        vector<vector<int>> dp(1 << n, vector<int>(k + 1, INT_MAX));
        dp[0][0] = 0;
        
        int msk = (1 << n) - 1;
        for (int i = 0; i + 1 < (1 << n); ++i) {
            int rem = msk ^ i;
            for (int j = 0; j < k; ++j) {
                if (dp[i][j] == INT_MAX)
                    continue;
                for (int s = rem; s > 0; s = (s - 1) & rem) {
                    dp[i ^ s][j + 1] = min(dp[i ^ s][j + 1], max(dp[i][j], sum[s]));
                }
            }
        }
        
        return dp[msk][k];
    }
};
```

:::

## Problem D - [公司命名](https://leetcode.cn/problems/naming-a-company/)

### 方法一：统计首字母间的二维冲突矩阵

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        int n = ideas.size();
        vector<string> subs(n);
        long long ans = 0;
        
        vector<int> v(26);
        unordered_map<string, int> suf;
        for (int i = 0; i < n; ++i) {
            auto &s = ideas[i];
            int ch = s[0] - 'a';
            subs[i] = s.substr(1, s.size() - 1);
            v[ch]++;
            suf[subs[i]] ^= 1 << ch;
        }
        
        vector<vector<int>> c(26, vector<int>(26));
        for (int i = 0; i < n; ++i) {
            auto &s = ideas[i];
            int sufi = suf[subs[i]];
            for (int j = 0; j < 26; ++j) {
                if ((1 << j) & sufi)
                    c[s[0] - 'a'][j]++;
            }
        }
        
        for (int i = 0; i < n; ++i) {
            auto &s = ideas[i];
            int sufi = suf[subs[i]];
            for (int j = 0; j < 26; ++j) {
                if (!((1 << j) & sufi))
                    ans += v[j] - c[s[0] - 'a'][j];
            }
        }
        
        return ans;
    }
};
```

<Utterances />
