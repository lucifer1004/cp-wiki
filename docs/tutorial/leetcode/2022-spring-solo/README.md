# 2021年力扣杯秋季赛个人赛题解

## Problem A - [宝石补给](https://leetcode-cn.com/contest/season/2022-spring/problems/WHnhjV/)

### 方法一：模拟

直接模拟即可。

- 时间复杂度$\mathcal{O}(Q)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def giveGem(self, gem: List[int], operations: List[List[int]]) -> int:
        for u, v in operations:
            amt = gem[u] // 2
            gem[u] -= amt
            gem[v] += amt
        return max(gem) - min(gem)
```

:::


## Problem B - [烹饪料理](https://leetcode-cn.com/contest/season/2022-spring/problems/UEcfPD/)

### 方法一：枚举

枚举所有做菜方法并检查是否符合要求。

- 时间复杂度为$\mathcal{O}(N\cdot 2^N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def perfectMenu(self, materials: List[int], cookbooks: List[List[int]], attribute: List[List[int]], limit: int) -> int:
        n = len(cookbooks)
        ans = -1
        for i in range(1, 1 << n):
            s = [0] * 5
            x = 0
            y = 0
            for j in range(n):
                if (i & (1 << j)) != 0:
                    s = [si + mi for si, mi in zip(s, cookbooks[j])]
                    x += attribute[j][0]
                    y += attribute[j][1]
            if y >= limit and all(si <= mi for si, mi in zip(s, materials)):
                ans = max(ans, x)
        return ans
```

:::


## Problem C - [黑白翻转棋](https://leetcode-cn.com/contest/season/2021-fall/problems/fHi6rV/)

### 方法一：中序遍历 + 线段树

首先中序遍历得到所有值，然后将这些数值离散化。将修改操作变为线段树上的赋值操作。这里绕了个弯，保存的是每个点最后一次被修改的时间，然后根据这个时间去查询最后一次生效的修改是什么操作。直接赋值为颜色也是可以的。

- 时间复杂度$\mathcal{O}(N+(N+Q)\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
struct SegmentTreeNode {
    int data = 0, l = 0, r = 0;
    bool lazy = false;

    void combine(SegmentTreeNode other) {
        data = max(data, other.data);
    }

    inline void reset() {
        data = 0;
        lazy = false;
    }
};

class SegmentTree {
    int n;
    vector<SegmentTreeNode> nodes;

    void calc(int idx) {
        nodes[idx].reset();
        nodes[idx].combine(nodes[idx << 1]);
        nodes[idx].combine(nodes[idx << 1 | 1]);
    }

    void build(int idx, int l, int r) {
        nodes[idx].l = l, nodes[idx].r = r;
        if (l == r)
            nodes[idx].data = 0;
        else {
            int mid = (l + r) >> 1;
            build(idx << 1, l, mid);
            build(idx << 1 | 1, mid + 1, r);
            calc(idx);
        }
    }

    void push_down(int idx) {
        if (!nodes[idx].lazy)
            return;
        for (int i = idx << 1; i <= (idx << 1 | 1); ++i) {
            nodes[i].data = max(nodes[i].data, nodes[idx].data);
            nodes[i].lazy = true;
        }
        nodes[idx].lazy = false;
    }

public:
    explicit SegmentTree(int n) {
        this->n = n;
        nodes = vector<SegmentTreeNode>((n + 1) << 2);
    }

    void init() { build(1, 1, n); }

    void update(int idx, int l, int r, int x) {
        if (l <= nodes[idx].l && r >= nodes[idx].r) {
            nodes[idx].data = x;
            nodes[idx].lazy = true;
        } else {
            push_down(idx);
            int mid = (nodes[idx].l + nodes[idx].r) >> 1;
            if (l <= mid)
                update(idx << 1, l, r, x);
            if (r > mid)
                update(idx << 1 | 1, l, r, x);
            calc(idx);
        }
    }

    SegmentTreeNode query(int idx, int l, int r) {
        if (l <= nodes[idx].l && r >= nodes[idx].r)
            return nodes[idx];
        push_down(idx);
        SegmentTreeNode ans;
        int mid = (nodes[idx].l + nodes[idx].r) >> 1;
        if (l <= mid)
            ans.combine(query(idx << 1, l, r));
        if (r > mid)
            ans.combine(query(idx << 1 | 1, l, r));
        return ans;
    }
};

class Solution {
    vector<int> v;

    void dfs(TreeNode *u) {
        if (u == nullptr)
            return;

        dfs(u->left);
        v.push_back(u->val);
        dfs(u->right);
    }
public:
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        dfs(root);
        unordered_map<int, int> mp;
        
        for (int i = 0; i < v.size(); ++i)
            mp[v[i]] = i + 1;

        int n = v.size();
        SegmentTree st(n);
        st.init();
        for (int i = 0; i < ops.size(); ++i) {
            int l = mp[ops[i][1]], r = mp[ops[i][2]];
            st.update(1, l, r, i + 1);
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int t = st.query(1, i, i).data;
            if (t > 0 && ops[t - 1][0] == 1)
                ans++;
        }
        
        return ans;
    }
};
```

:::

## Problem D - [守护太空城](https://leetcode-cn.com/contest/season/2022-spring/problems/EJvmW4/)

### 方法一：状态压缩动态规划

经过若干预处理后，枚举上一个位置处的残余能量罩状态和当前位置处放置能量罩的状态进行转移。

- 时间复杂度$\mathcal{O}(N\cdot 2^K\cdot 3^K)$。
- 空间复杂度$\mathcal{O}(2^K + 3^K)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;
const int T[6] = {1, 3, 9, 27, 81, 243};

class Solution {
public:
    int defendSpaceCity(vector<int>& time, vector<int>& position) {
        int N = 0;
        for (int pi : position)
            N = max(N, pi);
        N++;
        vector<int> status(N + 1);
        int K = 1;
        for (int i = 0; i < time.size(); ++i) {
            K = max(K, time[i]);
            int t = time[i] - 1;
            int p = position[i] + 1;
            status[p] |= 1 << t;
        }
        
        vector<int> cost(T[K]), my(T[K]), nxt(T[K]);
        vector<vector<int>> op(T[K]);
        for (int i = 0; i < T[K]; ++i) {
            int last = 0;
            int now = i;
            for (int k = 0; k < K; ++k) {
                int curr = now % 3;
                op[i].push_back(curr);
                if (curr > 0)
                    my[i] |= 1 << k;
                if (curr == 2)
                    nxt[i] |= 1 << k;
                now /= 3;
                if (curr != last) {
                    if (curr > 0)
                        cost[i] += curr + 1;
                } else {
                    if (curr > 0)
                        cost[i]++;
                }
                last = curr;
            }
        }

        vector<int> dp(1 << K, INF);
        dp[0] = 0;
        for (int i = 1; i <= N; ++i) {
            vector<int> ndp(1 << K, INF);
            for (int last = 0; last < (1 << K); ++last) {
                if (dp[last] == INF)
                    continue;
                for (int j = 0; j < T[K]; ++j) {
                    if (last & my[j])
                        continue;
                    if (i == N && nxt[j] > 0)
                        continue;
                    int cover = last | my[j];
                    if ((cover | status[i]) != cover)
                        continue;
                    
                    ndp[nxt[j]] = min(ndp[nxt[j]], dp[last] + cost[j]);
                }
            }
            
            dp = move(ndp);
        }
        
        return *min_element(dp.begin(), dp.end());
    }
};
```

:::

## Problem E - [夺回据点](https://leetcode-cn.com/contest/season/2022-spring/problems/s5kipK/)

### 方法一：找出割点，然后分别处理每个连通块

先用 Tarjan 算法找出割点，去掉这些点会剩下若干个连通块。

- 抛弃掉同时与多个割点相连的连通块。
- 求出剩余的连通块中的最小权值。

如果仅有一个连通块，答案就是这个最小权值；否则，答案为所有最小权值之和减去它们的最大值。

- 时间复杂度$\mathcal{O}(V+E)$。
- 空间复杂度$\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
    int n, idx = 0;
    ll ans = 0;
    int hi = 0;
    vector<int> c, dfn, low;
    vector<bool> vis, flag, vis2;
    vector<vector<int>> adj, adj2;
    unordered_set<int> meet;
    vector<int> cuts;

    void tarjan(int u, int p) {
        vis[u] = true;
        dfn[u] = low[u] = ++idx;
        int child = 0;
        for (int v : adj[u]) {
            if (!vis[v]) {
                child++;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (p != u && low[v] >= dfn[u] && !flag[u]) {
                    flag[u] = true;
                    cuts.push_back(u);
                }
            } else if (v != p)
                low[u] = min(low[u], dfn[v]);
        }

        if (p == u && child >= 2 && !flag[u]) {
            flag[u] = true;
            cuts.push_back(u);
        }
    }

    int dfs(int u, int p) {
        int lo = c[u];
        for (int v : adj[u]) {
            if (flag[v])
                meet.insert(v);
            if (flag[v] || vis2[v])
                continue;
            vis2[v] = true;
            lo = min(lo, dfs(v, u));
        }
        if (meet.size() >= 2)
            return 0;
        return lo;
    }

public:
    ll minimumCost(vector<int>& cost, vector<vector<int>>& roads) {
        this->c = cost;
        n = (int)cost.size();
        adj = vector<vector<int>>(n);
        dfn = vector<int>(n);
        low = vector<int>(n);
        vis = vector<bool>(n);
        flag = vector<bool>(n);
        for (auto &road : roads) {
            adj[road[0]].push_back(road[1]);
            adj[road[1]].push_back(road[0]);
        }

        tarjan(0, 0);

        vis2 = vector<bool>(n);
        int comp = 0;
        for (int i = 0; i < n; ++i)
            if (!flag[i] && !vis2[i]) {
                vis2[i] = true;
                meet.clear();
                int ret = dfs(i, i);
                hi = max(hi, ret);
                ans += ret;
                comp++;
            }

        return comp == 1 ? ans : ans - hi;
    }
};
```

:::

<Utterances />
