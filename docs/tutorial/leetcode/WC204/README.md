# Leetcode 第204场周赛题解

## Problem A - [重复至少 K 次且长度为 M 的模式](https://leetcode-cn.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/)

穷举所有长度为$M$的串并检查。同样是写枚举，Python的优势就凸显出来了，毕竟可以直接列表切片以及切片判相等。

::: details 参考代码（Python3）

```python
class Solution:
    def containsPattern(self, arr: List[int], m: int, k: int) -> bool:
        n = len(arr)
        ans = 1
        for i in range(n - m):
            j = i + m
            cnt = 1
            while j + m - 1 < n:
                if arr[i:i+m] == arr[j:j+m]:
                    cnt += 1
                else:
                    break
                j += m
            ans = max(ans, cnt)
        return ans >= k
```

:::

此外，这题还可以用正则表达式一行解决，当然，这需要对正则表达式比较熟悉才行，如果现场调试正则表达式，花的时间可能要比直接枚举还多上不少。

::: details 参考代码（JavaScript）

```js
var containsPattern = function(arr, m, k) {
    return new RegExp(`(\\d{${m}})\\1{${k - 1}}`).test(arr.join(''));
};
```

:::

## Problem B - [乘积为正数的最长子数组长度](https://leetcode-cn.com/problems/maximum-length-of-subarray-with-positive-product/)

首先用$0$将原数组分成若干子区间分别求解（因为$0$一定不在答案区间中）。

对于每一个子区间，我们需要乘积为正数，也就是负数的个数应该为偶数。采用前缀异或的方式一次遍历求解即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0)
                continue;
            int j = i;
            while (j + 1 < n && nums[j + 1] != 0)
                j++;
            vector<int> first(2, n + 1);
            first[0] = i - 1;
            int now = 0;
            for (int k = i; k <= j; ++k) {
                if (nums[k] < 0)
                    now ^= 1;
                ans = max(ans, k - first[now]);
                first[now] = min(first[now], k);
            }
            i = j;
        }
        return ans;
    }
};
```

:::

## Problem C - [使陆地分离的最少天数](https://leetcode-cn.com/problems/minimum-number-of-days-to-disconnect-island/)

先跑一遍并查集，如果连通分量数量超过$2$或者为$0$，则不需要任何修改，答案为$0$。

再跑一遍Tarjan找割点。如果有割点，则答案为$1$；否则答案为$2$（因为无论陆地怎样分布，相邻陆地数目最少的那块陆地的相邻数目最大为$2$）。

::: details 参考代码（C++）

```cpp
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

class Solution {
    int idx = 0;
    bool found = false;
    vector<int> p, sz, dfn, low;
    vector<vector<int>> adj;
    void tarjan(int u, int p) {
        dfn[u] = low[u] = ++idx;
        int children = 0;
        for (int v : adj[u]) {
            if (!dfn[v]) {
                children++;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (p == -1 && children >= 2)
                    found = true;
                else if (p != -1 && low[v] >= dfn[u])
                    found = true;
            }
            else if (v != p)
                low[u] = min(low[u], dfn[v]);
        }
    }
    
    int find(int u) {
        return p[u] == u ? u : p[u] = find(p[u]);
    }
    
    void connect(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv)
            return;
        if (sz[pu] >= sz[pv]) {
            p[pv] = pu;
            sz[pu] += sz[pv];
        } else {
            p[pu] = pv;
            sz[pv] += sz[pu];
        }
    }
    
public:
    int minDays(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int N = n * m;
        p = vector<int>(N, -1);
        sz = vector<int>(N, 1);
        int ans = N;
        adj = vector<vector<int>>(N);
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j) {
                if (!grid[i][j])
                    continue;
                int u = i * m + j;
                if (p[u] == -1)
                    p[u] = u;
                int cnt = 0;
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dy[k], nj = j + dx[k];
                    if (ni < 0 || ni >= n || nj < 0 || nj >= m || !grid[ni][nj])
                        continue;
                    int v = ni * m + nj;
                    cnt++;
                    if (p[v] == -1)
                        p[v] = v;
                    connect(u, v);
                    adj[u].emplace_back(v);
                    adj[v].emplace_back(u);
                }
                ans = min(ans, cnt);
            }
        int components = 0;
        for (int i = 0; i < N; ++i) {
            if (p[i] != -1 && i == find(i))
                components++;
        }
        if (components >= 2 || components == 0)
            return 0;
        
        for (int i = 0; i < N; ++i) {
            if (p[i] != -1) {
                dfn = vector<int>(N);
                low = vector<int>(N);
                tarjan(i, -1);
                break;
            }
        }
        
        return found ? 1 : 2;
    }
};
```

:::

## Problem D - [将子数组重新排序得到同一个二叉查找树的方案数](https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/)

对于任何一个数组，确定根节点（首个元素）后，我们可以将剩下元素分成大于根节点（右子树）和小于根节点（左子树）两种。容易发现，交换右子树中元素与左子树中元素之间的位置，不影响最后生成的二叉查找树。因此，设右子树有$n$个元素，左子树有$m$个元素，总的方法数就等于$C_{n+m}^n\cdot F(left)\cdot F(right)$。$F(left)$和$F(right)$递归求解即可。最后记得要减$1$（去掉自身）。

::: details 参考代码（C++）

```cpp
#define MAXN 1005

typedef long long ll;
const ll MOD = 1e9 + 7;

ll fac[MAXN], rev[MAXN];

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

ll C(ll n, ll k) {
    return fac[n] * rev[k] % MOD * rev[n - k] % MOD;
}

class Solution {
    ll dfs(vector<int> &nums) {
        if (nums.size() <= 1)
            return 1;
        vector<int> small, large;
        for (int i = 1; i < nums.size(); ++i)
            if (nums[i] > nums[0])
                large.emplace_back(nums[i]);
            else
                small.emplace_back(nums[i]);
        ll n = large.size(), m = small.size();
        ll fn = dfs(large), fm = dfs(small);
        return C(n + m, n) * fn % MOD * fm % MOD;
    }
public:
    int numOfWays(vector<int>& nums) {
        fac[0] = 1, rev[0] = 1;
        for (int i = 1; i <= nums.size(); ++i) {
            fac[i] = fac[i - 1] * i % MOD;
            rev[i] = fexp(fac[i], MOD - 2);
        }
        return (dfs(nums) % MOD - 1 + MOD) % MOD;
    }
};
```

:::

<Utterances />
