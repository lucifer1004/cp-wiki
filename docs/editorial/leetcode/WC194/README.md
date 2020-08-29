# Leetcode 第194场周赛题解

## Problem A - [数组异或操作](https://leetcode-cn.com/problems/xor-operation-in-an-array/)

模拟。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int xorOperation(int n, int start) {
        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans ^= (start + 2 * i);
        return ans;
    }
};
```

:::

## Problem B - [保证文件名唯一](https://leetcode-cn.com/problems/making-file-names-unique/)

按要求进行模拟。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        unordered_set<string> s;
        unordered_map<string, int> dict;
        vector<string> ans;
        for (string name : names) {
            if (!s.count(name)) {
                ans.emplace_back(name);
                s.insert(name);
                dict[name] = 1;
            } else {
                int idx = dict[name];
                while (s.count(name + "(" + to_string(idx) + ")"))
                    idx++;
                string t = name + "(" + to_string(idx) + ")";
                s.insert(t);
                ans.emplace_back(t);
                dict[name] = idx + 1;
                dict[t] = 1;
            }
        }
        return ans;
    }
};
```

:::

## Problem C - [避免洪水泛滥](https://leetcode-cn.com/problems/avoid-flood-in-the-city/)

首先一次遍历找到每一个下雨天下雨的池塘上一次下雨的日子。然后开始从最后一天倒推：

- 如果这一天下雨，那么需要检查下雨的池塘是否为空。
  - 如果不为空，说明有无法解决的冲突，无解。
  - 如果为空，那么将其置为满。同时，如果这一池塘之前还下过雨，就把之前下雨的记录加入大根堆中，等待消除矛盾。
- 如果这一天不下雨，并且大根堆非空（有需要消除的矛盾），就取出堆顶元素（最靠近的一个下雨天），将对应的池塘排空。

如果最后大根堆非空，代表还有未消除的矛盾，无解。

总时间复杂度为$O(n\log n)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n);
        unordered_map<int, int> pos;
        vector<int> last(n, -1);
        unordered_map<int, bool> full;
        for (int i = 0; i < n; ++i) {
            if (rains[i] > 0) {
                if (pos.count(rains[i]))
                    last[i] = pos[rains[i]];
                pos[rains[i]] = i;
            }
        }
        priority_queue<pair<int, int>> pq;
        for (int i = n - 1; i >= 0; --i) {
            if (rains[i] > 0) {
                if (full[rains[i]])
                    return {};
                ans[i] = -1;
                full[rains[i]] = true;
                if (last[i] == -1)
                    continue;
                else
                    pq.push({last[i], rains[i]});
            } else {
                if (pq.empty())
                    ans[i] = 1;
                else {
                    pair<int, int> top = pq.top();
                    pq.pop();
                    ans[i] = top.second;
                    full[top.second] = false;
                }
            }
        }
        if (!pq.empty())
            return {};
        return ans;
    }
};
```

:::

## Problem D - [找到最小生成树里的关键边和伪关键边](https://leetcode-cn.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/)

本题与[CF160D - Edges in MST]([https://codeforces.com/contest/160/problem/D](https://codeforces.com/contest/160/problem/D))相同。

### 方法一 暴力枚举

首先用Kruskal算法进行一次常规的MST，得到最小权值。

对于每条边，再进行两次额外的MST：

- 强制从该边开始MST（直接将该边加入生成树的边集）：如果最后的权值大于最小权值，说明该边既不是关键边，也不是非关键边
- 删除该边后再MST：如果最后的权值大于最小权值，或者图不连通，说明该边为关键边；否则该边可能为非关键边（结合上面一次的结果可以最终判断该边是否是非关键边）。

该方法的时间复杂度为$O(E^2)$，在本题的数据范围内可以通过。

::: details 参考代码（C++）

```cpp
struct Edge {
    int u, v, w, idx;

    bool operator<(const Edge &other) const {
        return w < other.w || (w == other.w && u < other.u) || (w == other.w && u == other.u && v < other.v);
    }
};

class UnionFind {
    int n;
    vector<int> parent, size;

public:
    UnionFind(int n) {
        this->n = n;
        parent = vector<int>(n);
        size = vector<int>(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int idx) {
        if (parent[idx] == idx)
            return idx;
        return parent[idx] = find(parent[idx]);
    }

    bool is_connected(int a, int b) {
        return find(a) == find(b);
    }

    void connect(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa != fb) {
            if (size[fa] > size[fb]) {
                parent[fb] = fa;
                size[fa] += size[fb];
            } else {
                parent[fa] = fb;
                size[fb] += size[fa];
            }
        }
    }

    int components() {
        vector<bool> is_root(n);
        for (int i = 0; i < n; ++i)
            is_root[find(i)] = true;
        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans += is_root[i];
        return ans;
    }
};

class Solution {
    int n;
    vector<Edge> e;
    vector<vector<int>> edges;

    int MST(int prioritize, int ignore) {
        UnionFind uf(n);
        int ans = 0;
        if (prioritize != -1) {
            vector<int> v = edges[prioritize];
            uf.connect(v[0], v[1]);
            ans += v[2];
        }
        for (Edge ei : e) {
            if (ei.idx == prioritize || ei.idx == ignore)
                continue;
            if (!uf.is_connected(ei.u, ei.v)) {
                uf.connect(ei.u, ei.v);
                ans += ei.w;
            }
        }
        if (uf.components() > 1)
            return INT_MAX;
        return ans;
    }

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges) {
        this->n = n;
        this->edges = edges;
        for (int i = 0; i < edges.size(); ++i)
            e.emplace_back(Edge{edges[i][0], edges[i][1], edges[i][2], i});
        sort(e.begin(), e.end());
        int mst = MST(-1, -1);
        vector<int> critical, non_critical;
        for (int i = 0; i < edges.size(); ++i) {
            int with = MST(i, -1);
            int without = MST(-1, i);
            if (with > mst)
                continue;
            if (without > mst)
                critical.emplace_back(i);
            else
                non_critical.emplace_back(i);
        }
        return {critical, non_critical};
    }
};
```

:::

### 方法二 Tarjan+并查集

维护一个所有顶点的并查集。将所有边按权值升序排序，然后将权值相同的边作为一组，从权值最小的组开始逐组处理。

每一组处理过程中，如果某条边的两个顶点已经在同一连通分量中，该边一定不在任何最小生成树中。否则该边至少是在一个最小生成树中，也即至少为非关键边。

接下来，将这些边加入邻接表构成新的图，然后在新的图上使用Tarjan算法找出所有的桥边。桥边一定是关键边。

最后，合并新连通的连通分量，也即“缩点”。

运行过程的瓶颈是排序，所以总时间复杂度为$O(E\log E)$。

::: details 参考代码（C++）

```cpp
#define INF 0x3f3f3f3f

struct Edge {
    int from, to, value;

    Edge(int from, int to, int value) : from(from), to(to), value(value) {}
};

class Graph {
    int n, idx;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> dfn, low, ans, parent, size;
    vector<bool> vis;

    int find(int a) { return parent[a] == a ? a : parent[a] = find(parent[a]); }

    void connect(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa != fb) {
            if (size[fa] > size[fb]) {
                parent[fb] = fa;
                size[fa] += size[fb];
            } else {
                parent[fa] = fb;
                size[fb] += size[fa];
            }
        }
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++idx;
        for (int ei : adj[u]) {
            if (vis[ei])
                continue;
            vis[ei] = true;
            Edge &e = edges[ei];
            int cv = find(e.from) + find(e.to) - u;
            int v = find(cv);
            if (!dfn[v]) {
                tarjan(v);
                if (dfn[u] < low[v])
                    ans[ei] = 0;
            }
            low[u] = min(low[u], low[v]);
        }
    }

public:
    explicit Graph(int n) : n(n) {
        adj = vector<vector<int >>(n);
        dfn = vector<int>(n, -1);
        low = vector<int>(n, INF);
        parent = vector<int>(n);
        size = vector<int>(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    void add_edge(int u, int v, int w) {
        adj[u].emplace_back(edges.size());
        adj[v].emplace_back(edges.size());
        edges.emplace_back(u, v, w);
    }

    vector<vector<int>> solve() {
        int m = edges.size();
        vector<int> order(m);
        for (int i = 0; i < m; ++i)
            order[i] = i;
        sort(order.begin(), order.end(),
             [&](int i, int j) { return edges[i].value < edges[j].value; });
        ans = vector<int>(m, -1);
        vis = vector<bool>(m);
        for (int start = 0; start < m; ++start) {
            int end = start;

            // 将相同权值的边归为一组进行处理
            while (end + 1 < m &&
                   edges[order[end + 1]].value == edges[order[start]].value)
                end++;

            // 清除处理上一组时连的边
            for (int k = start; k <= end; ++k) {
                auto[u, v, w] = edges[order[k]];
                int fu = find(u), fv = find(v);
                adj[fu].clear();
                adj[fv].clear();
                dfn[fu] = dfn[fv] = 0;
            }

            // 连上新边
            // 如果该边的两个端点已经在一个连通分量中，该边一定不在最小生成树中
            for (int k = start; k <= end; ++k) {
                auto[u, v, w] = edges[order[k]];
                int fu = find(u), fv = find(v);
                if (fu != fv) {
                    adj[fu].emplace_back(order[k]);
                    adj[fv].emplace_back(order[k]);
                    ans[order[k]] = 1;
                }
            }

            // Tarjan算法找出桥边
            // 桥边是关键边，其余非桥边是非关键边
            idx = 0;
            for (int k = start; k <= end; ++k) {
                auto[u, v, w] = edges[order[k]];
                int fu = find(u), fv = find(v);
                if (!dfn[fu])
                    tarjan(fu);
                if (!dfn[fv])
                    tarjan(fv);
            }

            // 合并连通分量，也就是所谓的“缩点”
            for (int k = start; k <= end; ++k) {
                auto[u, v, w] = edges[order[k]];
                connect(u, v);
            }
            start = end;
        }

        vector<vector<int>> ret(2);
        for (int i = 0; i < m; ++i)
            if (~ans[i]) ret[ans[i]].emplace_back(i);
        return ret;
    }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges) {
        Graph g(n);
        for (auto v : edges)
            g.add_edge(v[0], v[1], v[2]);
        return g.solve();
    }
};
```

:::

<Utterances />
