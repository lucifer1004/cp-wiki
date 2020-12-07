---
sidebarDepth: 3
---

# 桥和割点

## 定义

我们称无向图$G=\{V,E\}$中的一条边$e$为**桥**，当且仅当删除这条边后，图中的连通分量数量增加。**桥**也称为**割边**。

我们称无向图$G=\{V,E\}$中的一个顶点$v$为**割点**，当且仅当删除这个顶点（及所有与其相连的边）后，图中的连通分量数量增加。

## Tarjan算法

利用Tarjan算法，可以经过一次DFS，在$O(V+E)$的时间内求出图中的所有桥和割点。

::: tip 前置知识

DFS序。

:::

Tarjan算法的核心思想是，除了记录节点的DFS序$dfn[u]$，同时用数组$low[u]$记录从$u$出发，在不经过从其父节点到其的那条边的情况下，所能到达的节点中最小的DFS序。

## 在线算法

## 练习题

### [LC684 - 冗余连接](https://leetcode-cn.com/problems/redundant-connection/)

::: details 提示

本题官方题解提供的是并查集解法，但也可以通过Tarjan算法，从最后一条边开始依次判断是否桥边。如果不是桥边，则是一个冗余连接，可以将其删除。

:::

::: details 参考代码（C++）

```cpp
class Solution {
    int n, idx = 0;
    vector<int> dfn, low;
    vector<vector<int>> adj;
    void tarjan(int u, int p) {
        dfn[u] = low[u] = ++idx;
        for (int v : adj[u]) {
            if (v == p)
                continue;
            if (!dfn[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
            } else
                low[u] = min(low[u], dfn[v]);
        }
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        n = edges.size();
        adj = vector<vector<int>>(n + 1);
        for (auto v : edges) {
            adj[v[0]].emplace_back(v[1]);
            adj[v[1]].emplace_back(v[0]);
        }
        dfn = vector<int>(n + 1);
        low = vector<int>(n + 1);
        tarjan(1, 0);
        for (int i = n - 1; i >= 0; --i) {
            int &u = edges[i][0], &v = edges[i][1];
            if (dfn[u] >= low[v] && dfn[v] >= low[u])
                return edges[i];
        }
        return {};
    }
};
```

:::
