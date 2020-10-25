# Leetcode 第212场周赛题解

## Problem A - [按键持续时间最长的键](https://leetcode-cn.com/problems/slowest-key/)

模拟。

- 时间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        int last = 0;
        char c = 'a';
        int t = 0;
        for (int i = 0; i < releaseTimes.size(); ++i) {
            int ti = releaseTimes[i] - last;
            if (ti > t || (ti == t && keysPressed[i] > c)) {
                t = ti;
                c = keysPressed[i];
            }
            last = releaseTimes[i];
        }
        return c;
    }
};
```

:::

## Problem B - [等差子数组](https://leetcode-cn.com/problems/arithmetic-subarrays/)

模拟。对于每一个询问，将对应的子数组排序后检查是否为等差数组。

- 时间复杂度$O(MN\log N)$

::: details 参考代码（Python 3）

```python
class Solution:
    def checkArithmeticSubarrays(self, nums: List[int], l: List[int], r: List[int]) -> List[bool]:
        ans = []
        for li, ri in zip(l, r):
            a = nums[li : ri + 1]
            a.sort()
            ok = True
            for i in range(2, len(a)):
                if a[i] - a[i - 1] != a[1] - a[0]:
                    ok = False
                    break
            ans.append(ok)
        return ans
```

:::

## Problem C - [最小体力消耗路径](https://leetcode-cn.com/problems/path-with-minimum-effort/)

BFS+二分答案。

检查当前答案是否合法的方法是：只允许使用消耗不超过当前答案的路径。

- 时间复杂度$O(NM\log H_\text{max})$

::: details 参考代码（C++）

```cpp
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        auto valid = [&](int th){
            queue<pair<int, int>> q;
            vector<vector<bool>> vis(n, vector<bool>(m));
            vis[0][0] = true;
            q.emplace(0, 0);
            while (!q.empty()) {
                auto [i, j] = q.front();
                q.pop();
                if (i == n - 1 && j == m - 1)
                    return true;
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dy[k], nj = j + dx[k];
                    if (ni < 0 || ni >= n || nj < 0 || nj >= m || vis[ni][nj] || abs(heights[ni][nj] - heights[i][j]) > th)
                        continue;
                    vis[ni][nj] = true;
                    q.emplace(ni, nj);
                }
            }
            return false;
        };
        
        int l = 0, r = 1e6;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (!valid(mid))
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }
};
```

:::

## Problem D - [矩阵转换后的秩](https://leetcode-cn.com/problems/rank-transform-of-a-matrix/)

并查集+拓扑排序。

首先，将每行及每列中相等的元素找出来，然后连并查集的边，注意这里不需要连所有边，只要相邻两个连边即可。在后面的过程中，我们只考虑并查集中每一个连通分量的根节点。

接下来，每行每列分别排序，根据排序后的大小关系连拓扑排序的边。同样，这里也不需要连所有边，只要相邻两个大小不等的元素连边即可。

然后，进行拓扑排序。每个点的秩初始都为$1$，在拓扑排序过程中，如果有一条$u\to v$的边，则将$v$的秩设置为$\max(rank(v), rank(u)+1)$。其余操作同一般的拓扑排序。

最后，将矩阵中每个点的秩设置为并查集中其所在的连通分量的根节点的秩即可。

- 时间复杂度$O(NM\log\max(N,M))$，瓶颈为排序。

::: details 参考代码（C++）

```cpp
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
};

class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        UnionFind uf(n * m);
        for (int i = 0; i < n; ++i) {
            map<int, vector<int>> mp;
            for (int j = 0; j < m; ++j)
                mp[matrix[i][j]].emplace_back(i * m + j);
            for (auto &[num, vec] : mp) {
                for (int k = 0; k + 1 < vec.size(); ++k)
                    uf.connect(vec[k], vec[k + 1]);
            }
        }
        for (int j = 0; j < m; ++j) {
            map<int, vector<int>> mp;
            for (int i = 0; i < n; ++i)
                mp[matrix[i][j]].emplace_back(i * m + j);
            for (auto &[num, vec] : mp) {
                for (int k = 0; k + 1 < vec.size(); ++k)
                    uf.connect(vec[k], vec[k + 1]);
            }
        }
        vector<vector<int>> adj(n * m);
        vector<int> indegree(n * m);
        for (int i = 0; i < n; ++i) {
            vector<pair<int, int>> v(m);
            for (int j = 0; j < m; ++j)
                v[j] = make_pair(matrix[i][j], j);
            sort(v.begin(), v.end());
            for (int j = 0; j + 1 < m; ++j)
                if (v[j].first != v[j + 1].first) {
                    int uu = uf.find(i * m + v[j].second);
                    int vv = uf.find(i * m + v[j + 1].second);
                    adj[uu].emplace_back(vv);
                    indegree[vv]++;
                }
        }
        for (int j = 0; j < m; ++j) {
            vector<pair<int, int>> v(n);
            for (int i = 0; i < n; ++i)
                v[i] = make_pair(matrix[i][j], i);
            sort(v.begin(), v.end());
            for (int i = 0; i + 1 < n; ++i)
                if (v[i].first != v[i + 1].first) {
                    int uu = uf.find(v[i].second * m + j);
                    int vv = uf.find(v[i + 1].second * m + j);
                    adj[uu].emplace_back(vv);
                    indegree[vv]++;
                }
        }
        vector<int> ans(n * m, 1);
        queue<int> q;
        for (int i = 0; i < n * m; ++i) {
            if (uf.find(i) == i && indegree[i] == 0)
                q.emplace(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                ans[v] = max(ans[v], ans[u] + 1);
                indegree[v]--;
                if (indegree[v] == 0)
                    q.emplace(v);
            }
        }
        vector<vector<int>> result(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                result[i][j] = ans[uf.find(i * m + j)];
        return result;
    }
};
```

:::

<Utterances />
