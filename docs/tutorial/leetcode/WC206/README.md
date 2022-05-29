# Leetcode 第206场周赛题解

## Problem A - [二进制矩阵中的特殊位置](https://leetcode.cn/problems/special-positions-in-a-binary-matrix/)

枚举，时间复杂度$O(nm(n+m))$。更好的做法是先记录每一行的$1$的位置，如果这一行只有一个$1$，再去检查这个$1$是否也是其所在列唯一的$1$，这样可以把时间复杂度优化到$O(nm)$，但因为比赛时数据范围非常小，直接暴力做法就可以了。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int ans = 0;
        int n = mat.size(), m = mat[0].size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (!mat[i][j])
                    continue;
                bool ok = true;
                for (int k = 0; k < n; ++k)
                    if (k != i && mat[k][j]) {
                        ok = false;
                        break;
                    }
                for (int k = 0; k < m; ++k)
                    if (k != j && mat[i][k]) {
                        ok = false;
                        break;
                    }
                ans += ok;
            }
        return ans;
    }
};
```

:::

## Problem B - [统计不开心的朋友](https://leetcode.cn/problems/count-unhappy-friends/)

首先把$preferences$转化为邻接矩阵的形式，然后遵循题意暴力枚举所有的朋友对，逐个检查是否不开心即可。

时间复杂度$O(n^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<vector<int>> mat(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n - 1; ++j)
                mat[i][preferences[i][j]] = n - j;
        vector<bool> unhappy(n);
        for (auto p : pairs)
            for (auto q: pairs) {
                if (p == q)
                    continue;
                int x = p[0], y = p[1], u = q[0], v = q[1];
                if (mat[x][u] > mat[x][y] && mat[u][x] > mat[u][v])
                    unhappy[x] = true;
                if (mat[x][v] > mat[x][y] && mat[v][x] > mat[v][u])
                    unhappy[x] = true;
                if (mat[y][u] > mat[y][x] && mat[u][y] > mat[u][v])
                    unhappy[y] = true;
                if (mat[y][v] > mat[y][x] && mat[v][y] > mat[v][u])
                    unhappy[y] = true;
            }
        int ans = 0;
        for (int i : unhappy)
            ans += i;
        return ans;
    }
};
```

:::

## Problem C - [连接所有点的最小费用](https://leetcode.cn/problems/min-cost-to-connect-all-points/)

最小生成树的模板题。因为任意两个点都可以连接，所以属于稠密图，有一种特殊的Prim算法可以达到$O(V^2)=O(n^2)$的时间复杂度，而通常使用的Prim或Kruskal的时间复杂度为$O(E\log V)=O(n^2\log n)$。

常见的$O(E\log V)$的最小生成树算法大家都比较熟悉了，这里着重讲一下$O(V^2)$的特殊Prim算法。

这一算法的核心与我们熟悉的Prim算法是一致的，逐步加点。但这一算法中维护了一个全局的最小边集$e$，其中$e_i$代表从顶点$v_i$出发的最短边的长度。显然，边集$e$的大小为$V$。

每次我们从当前的最小边集中，找出未被选取过的点中的最小$e_i$，然后将$i$点加入点集，这一步操作的时间复杂度为$O(V)$。

当我们选取一个新的点之后，就可以用这个新的点去更新所有未被选取的点所对应的$e_i$。这一步操作的时间复杂度为$O(V)$。

因为我们要添加$V$个点，所以总时间复杂度为$O(V^2)$。

::: details 参考代码（C++）

```cpp
#define INF 0x3f3f3f3f

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        int ans = 0;
        vector<bool> vis(n);
        vector<int> min_dist(n, INF);
        min_dist[0] = 0;
        for (int i = 0; i < n; ++i) {
            int u = -1;
            int gmin = INF;
            for (int j = 0; j < n; ++j) {
                if (!vis[j] && min_dist[j] <= gmin) {
                    gmin = min_dist[j];
                    u = j;
                }
            }
            ans += gmin;
            vis[u] = true;
            for (int j = 0; j < n; ++j) 
                if (!vis[j]) {
                    int new_dist = abs(points[j][0] - points[u][0]) + abs(points[j][1] - points[u][1]);
                    min_dist[j] = min(min_dist[j], new_dist);
                }
        }
        return ans;
    }
};
```

:::

## Problem D - [检查字符串是否可以通过排序子字符串得到另一个字符串](https://leetcode.cn/problems/check-if-string-is-transformable-with-substring-sort-operations/)

观察到，操作前后，任何一种逆序对（所有满足$i>j$的不同的二元组$(i,j)$）的数目都只能减少而不能增加。反过来，只要逆序对的数目不增加，就一定会存在一种合法的操作将其变换得到。（这一步的严格证明暂时还没有想到。）

因此，在排除$s$和$t$不是互为排列这一特殊情况之后，只要检查每种逆序数的数目是否有增加即可。

具体的做法是，记录下$s$中第$i$个$c$前面$0$到$9$的数字分别有多少个，然后对应检查$t$中的第$i$个$c$前面的数字个数，看看逆序数数目是否有增加即可。

总时间复杂度为$O(CN)$，其中$C=10$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool isTransformable(string s, string t) {
        vector<int> cs(10), ct(10);
        for (char c : s)
            cs[c - '0']++;
        for (char c : t)
            ct[c - '0']++;
        for (int i = 0; i < 10; ++i)
            if (cs[i] != ct[i])
                return false;
        vector<vector<vector<int>>> rs(10);
        vector<int> fs(10);
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - '0';
            rs[c].push_back(fs);
            fs[c]++;
        }
        vector<int> ft(10);
        for (int i = 0; i < t.size(); ++i) {
            int c = t[i] - '0';
            int idx = ft[c];
            for (int j = 0; j < c; ++j) {
                if (ft[j] < rs[c][idx][j])
                    return false;
            }
            ft[c]++;
        }
        return true;
    }
};
```

:::

<Utterances />
