# Leetcode 第77场双周赛题解

## Problem A - [统计是给定字符串前缀的字符串数目](https://leetcode.cn/problems/count-prefixes-of-a-given-string/)

### 方法一：计数

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countPrefixes(self, words: List[str], s: str) -> int:
        cnt = collections.Counter(words)
        return sum(cnt[s[:i]] for i in range(1, len(s) + 1))
```

:::

## Problem B - [最小平均差](https://leetcode.cn/problems/minimum-average-difference/)

### 方法一：枚举

枚举每个位置。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumAverageDifference(self, nums: List[int]) -> int:
        n = len(nums)
        right = sum(nums)
        left = 0
        ans = -1
        best = int(1e10)
        for i in range(n):
            left += nums[i]
            right -= nums[i]
            lavg = left // (i + 1)
            ravg = right // max(1, n - i - 1)
            curr = abs(lavg - ravg)
            if curr < best:
                ans = i
                best = curr
        return ans
```

:::

## Problem C - [统计网格图中没有被保卫的格子数](https://leetcode.cn/problems/count-unguarded-cells-in-the-grid/)

### 方法一：线性探查 * 4

从上到下、从下到上、从左到右、从右到左四个方向各线性探查一次即可。

- 时间复杂度 $\mathcal{O}(NM)$。
- 空间复杂度 $\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> vis(m, vector<int>(n));
        for (auto &g : guards)
            vis[g[0]][g[1]] = 1;
        for (auto &w : walls)
            vis[w[0]][w[1]] = 2;
        for (int i = 0; i < m; ++i) {
            int now = 0;
            for (int j = 0; j < n; ++j) {
                if (vis[i][j] == 1)
                    now = 1;
                else if (vis[i][j] == 2)
                    now = 0;
                else if (vis[i][j] == 0 && now == 1)
                    vis[i][j] = 3;
            }
            
            now = 0;
            for (int j = n - 1; j >= 0; --j) {
                if (vis[i][j] == 1)
                    now = 1;
                else if (vis[i][j] == 2)
                    now = 0;
                else if (vis[i][j] == 0 && now == 1)
                    vis[i][j] = 3;
            }
        }
        
        for (int j = 0; j < n; ++j) {
            int now = 0;
            for (int i = 0; i < m; ++i) {
                if (vis[i][j] == 1)
                    now = 1;
                else if (vis[i][j] == 2)
                    now = 0;
                else if (vis[i][j] == 0 && now == 1)
                    vis[i][j] = 3;
            }
            
            now = 0;
            for (int i = m - 1; i >= 0; --i) {
                if (vis[i][j] == 1)
                    now = 1;
                else if (vis[i][j] == 2)
                    now = 0;
                else if (vis[i][j] == 0 && now == 1)
                    vis[i][j] = 3;
            }
        }
        
        int ans = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (vis[i][j] == 0)
                    ans++;
        
        return ans;
    }
};
```

:::

## Problem D - [逃离火灾](https://leetcode.cn/problems/escape-the-spreading-fire/)

### 方法一：BFS + 二分答案

首先多源 BFS 预计算得到每个格子被火烧着的时间，然后二分答案，每次 BFS 检查是否能从起点到达终点。注意判断时要区分是否是最后一个格子。

复杂度：

- 时间复杂度 $\mathcal{O}(NM\log NM)$。
- 空间复杂度 $\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
const int d[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

class Solution {
  public:
    int maximumMinutes(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<int>> days(n, vector<int>(m, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    days[i][j] = 0;
                    q.emplace(i, j);
                }
            }

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            for (int k = 0; k < 4; ++k) {
                int ni = i + d[k][0], nj = j + d[k][1];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m ||
                    days[ni][nj] != -1 || grid[ni][nj] == 2)
                    continue;
                days[ni][nj] = days[i][j] + 1;
                q.emplace(ni, nj);
            }
        }

        auto can_go = [&](int day) {
            vector<vector<int>> vis(n, vector<int>(m, -1));
            vis[0][0] = day;

            queue<pair<int, int>> q;
            q.emplace(0, 0);

            while (!q.empty()) {
                auto [i, j] = q.front();
                q.pop();

                for (int k = 0; k < 4; ++k) {
                    int ni = i + d[k][0], nj = j + d[k][1];
                    if (ni < 0 || ni >= n || nj < 0 || nj >= m ||
                        grid[ni][nj] == 2 ||
                        vis[ni][nj] != -1 ||
                        (days[ni][nj] != -1 &&
                         (vis[i][j] + 1 > days[ni][nj])))
                        continue;
                    if (vis[i][j] + 1 == days[ni][nj] && (ni != n - 1 || nj != m - 1))
                        continue;
                    vis[ni][nj] = vis[i][j] + 1;
                    q.emplace(ni, nj);
                }
            }

            return vis[n - 1][m - 1] != -1;
        };

        int lo = 0, hi = n * m;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;

            if (can_go(mid))
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        if (hi == n * m) return 1e9;
        return hi;
    }
};
```

:::

<Utterances />
