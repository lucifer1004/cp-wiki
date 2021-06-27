# Leetcode 第247场周赛题解

## Problem A - [两个数对之间的最大乘积差](https://leetcode-cn.com/problems/maximum-product-difference-between-two-pairs/)

### 方法一：贪心

找到最大的两个数字和最小的两个数字即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

也可以在$\mathcal{O}(N)$时间内找到需要的这四个数字。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxProductDifference(self, nums: List[int]) -> int:
        nums.sort()
        return nums[-1] * nums[-2] - nums[0] * nums[1]
```

:::

## Problem B - [循环轮转矩阵](https://leetcode-cn.com/problems/cyclically-rotating-a-grid/)

### 方法一：模拟

按顺序找出每一层的所有位置，然后进行轮转即可。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> ans(grid);
        for (int i = 0; i < min(n, m) / 2; ++i) {
            vector<int> pos;
            int p = i, q = i;
            pos.emplace_back(p * m + q);
            while (p + 1 < n - i) {
                p++;
                pos.emplace_back(p * m + q);
            }
            while (q + 1 < m - i) {
                q++;
                pos.emplace_back(p * m + q);
            }
            while (p - 1 >= i) {
                p--;
                pos.emplace_back(p * m + q);
            }
            while (q - 1 > i) {
                q--;
                pos.emplace_back(p * m + q);
            }
            int c = k % pos.size();
            for (int j = 0; j < pos.size(); ++j) {
                int now = pos[j];
                int ni = now / m, nj = now % m;
                int pre = pos[(j - c + pos.size()) % pos.size()];
                int pi = pre / m, pj = pre % m;
                ans[ni][nj] = grid[pi][pj];
            }
        }
        
        return ans;
    }
};
```

:::

## Problem C - [最美子字符串的数目](https://leetcode-cn.com/problems/number-of-wonderful-substrings/)

### 方法一：状态压缩+前缀异或和

我们可以使用一个二进制数记录原字符串的每个前缀中各个字母的奇偶性，并统计每一个状态的出现次数。

根据题意，好的状态为$0$和所有$2^i$。所以，我们遍历到每一个位置时，只需要计数所有与当前状态异或之后为好状态的状态的出现次数之和，即可得到以当前位置为结尾的最美子字符串的数目。

- 时间复杂度$\mathcal{O}(NK)$，其中$K=10$。
- 空间复杂度$\mathcal{O}(2^K)$。

::: details 参考代码（C++）

```cpp
const int K = 10;

class Solution {
public:
    long long wonderfulSubstrings(string word) {
        int n = word.size();
        int state = 0;
        vector<int> cnt(1 << K);
        cnt[0] = 1;
        vector<int> good{0};
        for (int i = 0; i < K; ++i)
            good.emplace_back(1 << i);
        
        long long ans = 0;
        for (char c : word) {
            int t = 1 << (c - 'a');
            state ^= t;
            for (int g : good)
                ans += cnt[state ^ g];
            cnt[state]++;
        }
        
        return ans;
    }
};
```

:::

## Problem D - [统计为蚁群构筑房间的不同顺序](https://leetcode-cn.com/problems/count-ways-to-build-rooms-in-an-ant-colony/)

### 方法一：树上的动态规划

题目给定的条件能够唯一确定一棵以$0$为根的树。我们考虑任意一棵子树。显然我们需要首先构建这棵子树的根节点，而对于这一子树的每一子树，我们可以首先考虑某一个子树对应的节点在构建序列中所占据的位置，这可以通过组合数计算出来。接下来，我们需要考虑这一子树的子树中节点的构建顺序，而这就是原问题的一个子问题，从而可以递归求解。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;
const int N = 100005;

bool inited = false;
ll fac[N], ifac[N], ans[N];
int sz[N];
vector<vector<int>> adj;
ll fexp(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1)
            ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}
ll C(int n, int k) {
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void init() {
    inited = true;
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    ifac[N - 1] = fexp(fac[N - 1], MOD - 2);
    for (int i = N - 2; i >= 1; --i)
        ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}

void dfs(int u) {
    sz[u] = 0;
    for (int v : adj[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
    
    int tot = sz[u];
    ans[u] = 1;
    for (int v : adj[u]) {
        ans[u] = ans[u] * ans[v] % MOD;
        ans[u] = ans[u] * C(tot, sz[v]) % MOD;
        tot -= sz[v];
    }
    
    sz[u]++;
}

class Solution {
public:
    int waysToBuildRooms(vector<int>& prevRoom) {
        if (!inited)
            init();
        
        int n = prevRoom.size();
        adj = vector<vector<int>>(n);
        for (int i = 1; i < n; ++i)
            adj[prevRoom[i]].emplace_back(i);
        
        dfs(0);
        
        return ans[0];
    }
};
```

:::

<Utterances />
