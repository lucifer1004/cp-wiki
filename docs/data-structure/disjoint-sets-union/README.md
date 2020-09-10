---
sidebarDepth: 3
---

# 并查集

## 学习资源

### [ITMO Academy: pilot course](https://codeforces.com/edu/course/2/lesson/7)

来自Codeforces EDU。包括视频教程、图文教程和18道练习题

## 练习题

### [BS742 - Graph Weight Queries](https://binarysearch.io/problems/Graph-Weight-Queries)

::: details 提示一
离线查询。
:::

::: details 提示二
查询和边都按照权重从小到大排序，逐步向图中添加边。
:::

::: details 参考代码（C++）

```cpp
#include "solution.hpp"
using namespace std;

class Solution {
    vector<int> p, sz;
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
    int solve(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size();
        p = vector<int>(n << 1);
        sz = vector<int>(n << 1, 1);
        for (int i = 0; i < (n << 1); ++i)
            p[i] = i;
        auto cmp = [](vector<int> &a, vector<int> &b){
           return a[2] < b[2]; 
        };
        sort(edges.begin(), edges.end(), cmp);
        sort(queries.begin(), queries.end(), cmp);
        int idx = 0, ans = 0;
        for (auto q : queries) {
            while (idx < n && edges[idx][2] <= q[2]) {
                connect(edges[idx][0], edges[idx][1]);
                idx++;
            }
            if (find(q[0]) == find(q[1]))
                ans++;
        }
        return ans;
    }
};
```

:::

::: details 在线解法
本题同样可以在线求解。我们需要分两步进行。首先，求出最大值意义下的最小生成树。然后，对于这棵最小生成树，用倍增法求LCA；在预处理的过程中，除了得到第$i$级的祖先，同时求得到这一祖先的路径上的最大权重。对于每一个查询，首先求出LCA，然后让$u$和$v$分别上移到LCA位置，记录路径上的最大权重。将这个最大权重与查询的限制条件进行比较即可。
:::

<Utterances />
