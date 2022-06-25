# Leetcode 第81场双周赛题解

## Problem A - [统计星号](https://leetcode.cn/problems/count-asterisks/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(|S|)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countAsterisks(string s) {
        int ans = 0, seg = 0;
        for (char c : s) {
            if (c == '|')
                seg++;
            else if (c == '*' && seg % 2 == 0)
                ans++;
        }
        return ans;
    }
};
```

:::

## Problem B - [统计无向图中无法互相到达点对数](https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/)

### 方法一：统计连通块

用 BFS 、DFS 或者并查集等方法均可，找出每个连通块就可以求出可以互相到达的点对数，再用总数减去它就得到了要求的答案。

- 时间复杂度 $\mathcal{O}(V+E)$。
- 空间复杂度 $\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        long long ans = 1LL * n * (n - 1) / 2;
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<bool> vis(n);
        
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            
            vis[i] = true;
            queue<int> q;
            q.push(i);
            int sz = 1;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                        sz++;
                    }
                }
            }
            
            ans -= 1LL * sz * (sz - 1) / 2;
        }
        
        return ans;
    }
};
```

:::

## Problem C - [操作后的最大异或和](https://leetcode.cn/problems/maximum-xor-after-operations/)

### 方法一：脑筋急转弯

考虑二进制的第 k 位，如果所有数这一位都为 0，就无法通过操作使得结果中这一位为 1，否则必然可以通过若干次操作使得这一位的 1 的数目为奇数个，从而结果中这一位为 1。因此所有数按位或的结果就是本题的答案。

- 时间复杂度 $\mathcal{O}(N)$ 。
- 空间复杂度 $\mathcal{O}(1)$ 。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        int ans = 0;
        for (int num : nums)
            ans |= num;
        return ans;
    }
};
```

:::

## Problem D - [不同骰子序列的数目](https://leetcode.cn/problems/number-of-distinct-roll-sequences/)

### 方法一：动态规划

因为和上两次的结果不能相同，所以记录之前两次的状态即可。

- 时间复杂度 $\mathcal{O}(N\cdot C^3)$，其中 $C=6$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

ll dp[7][7]{}, ndp[7][7]{};
int g[7][7];

class Solution {
public:
    int distinctSequences(int n) {
        memset(dp, 0, sizeof(dp));      
        dp[0][0] = 1;
        
        for (int i = 1; i <= 6; ++i)
            for (int j = 1; j <= 6; ++j)
                g[i][j] = __gcd(i, j);
        
        for (int i = 0; i < n; ++i) {
            memset(ndp, 0, sizeof(ndp));
            
            for (int a = 0; a <= 6; ++a) {
                for (int b = 0; b <= 6; ++b) {
                    if (dp[a][b] == 0)
                        continue;
                    
                    for (int c = 1; c <= 6; ++c) {
                        if (c == a || c == b || (b != 0 && g[b][c] != 1))
                            continue;

                        ndp[b][c] += dp[a][b];
                        ndp[b][c] %= MOD;
                    }
                }
            }
            
            swap(dp, ndp);
        }
        
        ll ans = 0;
        
        for (int a = 0; a <= 6; ++a) {
            for (int b = 0; b <= 6; ++b) {
                ans += dp[a][b];
                ans %= MOD;
            }
        }
        
        return ans;
    }
};
```

:::

<Utterances />
