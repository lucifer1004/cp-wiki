# Leetcode 第289场周赛题解

## Problem A - [计算字符串的数字和](https://leetcode.cn/problems/calculate-digit-sum-of-a-string/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(|S|)$。
- 空间复杂度 $\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def digitSum(self, s: str, k: int) -> str:
        while len(s) > k:
            s = ''.join(str(sum(map(int, s[i:i+k])))
                        for i in range(0, len(s), k))
        return s
```

:::

## Problem B - [完成所有任务需要的最少轮数](https://leetcode.cn/problems/minimum-rounds-to-complete-all-tasks/)

### 方法一：计数

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumRounds(self, tasks: List[int]) -> int:
        values = list(collections.Counter(tasks).values())
        return -1 if values.count(1) > 0 else sum((val - 1) // 3 + 1 for val in values)
```

:::


## Problem C - [转角路径的乘积中最多能有几个尾随零](https://leetcode.cn/problems/maximum-trailing-zeros-in-a-cornered-path/)

### 方法一：前缀和 + 枚举

- 时间复杂度 $\mathcal{O}(NM)$。
- 空间复杂度 $\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> two(n, vector<int>(m)), five(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int val = grid[i][j];
                while (val % 2 == 0) {
                    two[i][j]++;
                    val /= 2;
                }

                while (val % 5 == 0) {
                    five[i][j]++;
                    val /= 5;
                }
            }
        }

        vector<vector<int>> row2(n, vector<int>(m + 1)),
            row5(n, vector<int>(m + 1)), col2(m, vector<int>(n + 1)),
            col5(m, vector<int>(n + 1));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                row2[i][j + 1] = row2[i][j] + two[i][j];
                row5[i][j + 1] = row5[i][j] + five[i][j];
            }
        }

        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                col2[j][i + 1] = col2[j][i] + two[i][j];
                col5[j][i + 1] = col5[j][i] + five[i][j];
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                int zt = two[i][j], zf = five[i][j];
                int ut = col2[j][i], uf = col5[j][i];
                int lt = row2[i][j], lf = row5[i][j];
                int rt = row2[i][m] - row2[i][j + 1], rf = row5[i][m] - row5[i][j + 1];
                int dt = col2[j][n] - col2[j][i + 1], df = col5[j][n] - col5[j][i + 1];

                vector<int> possible{
                    min(ut + lt + zt, uf + lf + zf), min(ut + rt + zt, uf + rf + zf),
                    min(dt + lt + zt, df + lf + zf), min(dt + rt + zt, df + rf + zf)};

                ans = max(ans, *max_element(possible.begin(), possible.end()));
            }

        return ans;
    }
};
```

:::

## Problem D - [相邻字符不同的最长路径](https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/)

### 方法一：DFS

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
    string t;
    int n, ans;
    vector<vector<int>> adj;

    int dfs(int u) {
        int fst = 0, sec = 0;
        for (int v : adj[u]) {
            int clen = dfs(v);
            if (t[v] == t[u])
                continue;
            if (clen > fst) {
                sec = fst;
                fst = clen;
            } else if (clen > sec)
                sec = clen;
        }
        ans = max(ans, fst + sec + 1);
        return fst + 1;
    }

public:
    int longestPath(vector<int>& parent, string s) {
        t = s;
        n = s.size();
        adj = vector<vector<int>>(n);
        for (int i = 0; i < n; ++i) {
            int p = parent[i];
            if (p != -1) adj[p].push_back(i);
        }

        ans = 0;
        dfs(0);
        return ans;
    }
};
```

:::

<Utterances />
