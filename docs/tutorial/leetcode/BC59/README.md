# Leetcode 第59场双周赛题解

## Problem A - [使用特殊打字机键入单词的最少时间](https://leetcode.cn/problems/minimum-time-to-type-word-using-special-typewriter/)

### 方法一：贪心

每次要么正转，要么倒转，取较小的一种转法即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minTimeToType(string word) {
        int now = 0, ans = 0;
        for (char c : word) {
            int ch = c - 'a';
            ans += 1 + min((ch - now + 26) % 26, (now - ch + 26) % 26);
            now = ch;
        }
        return ans;
    }
};
```

:::


## Problem B - [最大方阵和](https://leetcode.cn/problems/maximum-matrix-sum/)

### 方法一：贪心

我们发现，对两个负元素操作，可以消去两个负号；每次对两个一正一负的元素进行操作，就可以将负号移动位置。所以有如下结论：

- 如果一开始有偶数个负号，那么我们可以经过若干次操作消去所有负号；如果一开始有奇数个负号，那么最后可以只剩下一个负号。
- 如果最后剩下一个负号，我们可以将这个负号移动到任意位置。因此，我们应当将其移动到绝对值最小的位置。

那么就可以很容易地求得答案。

- 时间复杂度为$\mathcal{O}(RC)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        long long ans = 0, lo = LLONG_MAX, neg = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                ans += abs(matrix[i][j]);
                lo = min(lo, (long long)abs(matrix[i][j]));
                if (matrix[i][j] < 0)
                    neg++;
            }
        if (neg % 2 == 1)
            ans -= lo * 2;
        return ans;
    }
};
```

:::


## Problem C - [到达目的地的方案数](https://leetcode.cn/problems/number-of-ways-to-arrive-at-destination/)

### 方法一：Dijkstra算法

在标准Dijkstra算法基础上加一个$ways$数组记录方案数即可。

- 时间复杂度$\mathcal{O}(E\log E)$（因为使用`priority_queue`没有移除无效元素）。
- 空间复杂度$\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto &road : roads) {
            int u = road[0], v = road[1], t = road[2];
            adj[u].emplace_back(v, t);
            adj[v].emplace_back(u, t);
        }
        
        vector<ll> dis(n, LLONG_MAX), ways(n);
        dis[0] = 0;
        ways[0] = 1;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [t, u] = pq.top();
            pq.pop();
            if (t > dis[u])
                continue;
            for (auto [v, w] : adj[u]) {
                if (t + w < dis[v]) {
                    dis[v] = t + w;
                    ways[v] = 0;
                    pq.emplace(t + w, v);
                }
                if (t + w == dis[v])
                    ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
        
        return ways[n - 1];
    }
};
```

:::

## Problem D - [划分数字的方案数](https://leetcode.cn/problems/number-of-ways-to-separate-numbers/)

### 方法一：动态规划

本题较难。

容易想到$\mathcal{O}(N^3)$的动态规划：用$dp[i][j]$表示到第$i$个位置，最后一个数字的长度为$j$时的方案数，则其对应的上一个数的结尾应该是$i-j$，我们就可以枚举$dp[i-j][k]$，$k\le j$。其中，$k<j$的部分可以直接加上（因为前面的数字长度较短，所以一定更小），但$k=j$时，我们需要判断两个数字的大小关系。

利用前缀和的方法可以将$k<j$的部分优化到$\mathcal{O}(1)$时间，但此时整体的复杂度还是$\mathcal{O}(N^3)$，因为最坏情况下，所有数字都相同（比如3500个`9`），则我们对于每一个$k=j$的情形都需要进行$\mathcal{O}(N)$时间的比较。

如何优化比较呢？这里，我们可以进行一次预处理的动态规划来加速比较。

令$c[i][j]$表示第一个串从$i$开始，第二个串从$j$开始，且满足第一个串不大于第二个串的最长长度。显然$c[i][j]$可以由$c[i+1][j+1]$转移得到。

求得$c[i][j]$之后，我们在进行比较时就只需要判断$c[i-2j][i-j]\ge j$是否成立即可。

- 时间复杂度$\mathcal{O}(|S|^2)$。
- 空间复杂度$\mathcal{O}(|S|^2)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int numberOfCombinations(string num) {
        if (num[0] == '0')
            return 0;
        
        int n = num.size();
        vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
        dp[1] = vector<ll>(n + 1, 1);
        dp[1][0] = 0;
        
        vector<vector<int>> c(n, vector<int>(n));
        for (int len = 1; len <= n; ++len)
            for (int i = n - 1 - len; i >= 0; --i) {
                if (num[i] < num[i + len])
                    c[i][i + len] = n - i - len;
                else if (num[i] == num[i + len]) {
                    if (i + len == n - 1)
                        c[i][i + len] = 1;
                    else
                        c[i][i + len] = c[i + 1][i + len + 1] + 1;
                }
            }
        
        auto cmp = [&](int l, int r, int len) {
            if (l < 0)
                return false;
            return c[l][r] >= len;
        };
        
        for (int i = 2; i <= n; ++i) {
            dp[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                if (num[i - j] == '0')
                    continue;
                if (cmp(i - 2 * j, i - j, j))
                    dp[i][j] = (dp[i][j] + dp[i - j][j]) % MOD;
                else
                    dp[i][j] = (dp[i][j] + dp[i - j][j - 1]) % MOD;   
            }
            for (int j = 1; j <= n; ++j)
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
        }
        
        return dp[n][n];
    }
};
```

:::

<Utterances />
