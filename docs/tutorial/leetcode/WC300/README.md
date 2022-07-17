# Leetcode 第300场周赛题解

## Problem A - [解密消息](https://leetcode.cn/problems/decode-the-message/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(|K|+|M|)$。
- 空间复杂度 $\mathcal{O}(|\Sigma|+|M|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def decodeMessage(self, key: str, message: str) -> str:
        d = dict()
        for ki in key:
            if 'a' <= ki <= 'z' and ki not in d:
                d[ki] = chr(ord('a') + len(d))
        return ''.join(d[mi] if 'a' <= mi <= 'z' else mi for mi in message)
```

:::

## Problem B - [螺旋矩阵 IV](https://leetcode.cn/problems/spiral-matrix-iv/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(MN)$。
- 空间复杂度 $\mathcal{O}(MN)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> ans(m, vector<int>(n, -1));
        int l = 0, r = n - 1, u = 0, d = m - 1, i = 0, j = 0;
        int dir = 0;
        
        auto chdir = [&]() {
            bool moved = false;
            while (!moved) {
                if (dir == 0) {
                    if (j + 1 <= r) {
                        moved = true;
                        j++;
                    }
                    else {
                        dir = 1;
                        u++;
                    }
                } else if (dir == 1) {
                    if (i + 1 <= d) {
                        moved = true;
                        i++;
                    }
                    else {
                        dir = 2;
                        r--;
                    }
                } else if (dir == 2) {
                    if (j - 1 >= l) {
                        moved = true;
                        j--;
                    }
                    else {
                        dir = 3;
                        l++;
                    }
                } else {
                    if (i - 1 >= u) {
                        moved = true;
                        i--;
                    }
                    else {
                        dir = 0;
                        d--;
                    }
                }
            }
        };
        
        while (head != nullptr) {
            ans[i][j] = head->val;
            head = head->next;
            if (head != nullptr)
                chdir();
        }
        
        return ans;
    }
};
```

:::

## Problem C - [知道秘密的人数](https://leetcode.cn/problems/number-of-people-aware-of-a-secret/)

### 方法一：动态规划

- 时间复杂度 $\mathcal{O}(N)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;

class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        int know = 0;
        for (int i = 2; i <= n; ++i) {
            if (i - forget >= 1)
                know = (know + MOD - dp[i - forget]) % MOD;
            if (i - delay >= 1)
                know = (know + dp[i - delay]) % MOD;
            dp[i] = know;
        }
        
        int ans = 0;
        for (int i = max(1, n - forget + 1); i <= n; ++i)
            ans = (ans + dp[i]) % MOD;
        
        return ans;
    }
};
```

:::

## Problem D - [网格图中递增路径的数目](https://leetcode.cn/problems/number-of-increasing-paths-in-a-grid/)

### 方法一：拓扑排序 + 动态规划

- 时间复杂度 $\mathcal{O}(NM\log(NM))$ 。
- 空间复杂度 $\mathcal{O}(NM)$ 。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;
const int d[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m));
        vector<pair<int, int>> ord(n * m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ord[i * m + j] = make_pair(i, j);
        
        sort(ord.begin(), ord.end(), [&](pair<int, int> &a, pair<int, int> &b) {
            return grid[a.first][a.second] < grid[b.first][b.second];
        });
        
        int ans = 0;
        for (auto [i, j] : ord) {
            dp[i][j] = (dp[i][j] + 1) % MOD;
            for (int k = 0; k < 4; ++k) {
                int ni = i + d[k][0], nj = j + d[k][1];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] > grid[i][j])
                    dp[ni][nj] = (dp[ni][nj] + dp[i][j]) % MOD;
            }
            ans = (ans + dp[i][j]) % MOD;
        }
        
        return ans;
    }
};
```

<Utterances />
