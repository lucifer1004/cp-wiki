# Leetcode 第284场周赛题解

## Problem A - [找出数组中的所有 K 近邻下标](https://leetcode-cn.com/problems/find-all-k-distant-indices-in-an-array/)

### 方法一：暴力

暴力检查每个位置是否符合要求。

- 时间复杂度 $\mathcal{O}(NK)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:
        ans = []
        n = len(nums)
        for i in range(n):
            good = False
            for j in range(max(0, i - k), min(n, i + k + 1)):
                if nums[j] == key:
                    good = True
                    break
            if good:
                ans.append(i)
        return ans
```

:::

### 方法二：分别找出左边和右边最近的 `key`

我们可以先从左向右，再从右向左进行两次遍历，从而找出每个位置左边和右边最近的 `key`，并判断是否满足条件。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:
        n = len(nums)
        good = [False] * n
        last_key = -1
        for i in range(n):
            if nums[i] == key:
                last_key = i
            if last_key != -1 and i - last_key <= k:
                good[i] = True
        last_key = -1
        for i in range(n - 1, -1, -1):
            if nums[i] == key:
                last_key = i
            if last_key != -1 and last_key - i <= k:
                good[i] = True
        return [i for i in range(n) if good[i]]    
```

:::

## Problem B - [统计可以提取的工件](https://leetcode-cn.com/problems/count-artifacts-that-can-be-extracted/)

### 方法一：模拟

逐个检查工件，判断是否每个部分都已经裸露出来。

- 时间复杂度 $\mathcal{O}(N+M)$，其中 $N$ 为工件数，$M$ 为挖掘数。
- 空间复杂度 $\mathcal{O}(N+M)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def digArtifacts(self, n: int, artifacts: List[List[int]], dig: List[List[int]]) -> int:
        d = set(map(tuple, dig))
        return len([1 for r1, c1, r2, c2 in artifacts if all((r, c) in d for r in range(r1, r2 + 1) for c in range(c1, c2 + 1))])
```

:::

## Problem C - [K 次操作后最大化顶端元素](https://leetcode-cn.com/problems/maximize-the-topmost-element-after-k-moves/)

### 方法一：分类讨论

本题的边界情况较多，需要细致地进行讨论。

- 如果 $k=0$，也即不进行任何操作，那么顶端元素必然为 $nums[0]$
- 如果 $n=1$，也即只有一个元素，同时操作次数为奇数次，那么我们必然只能按照“删除——放入——删除”这样的序列进行操作，因此最后一次操作必然是删除，此时栈必定为空
- 如果 $k<n$，我们可以有两种选择
    - 先删除 $k-1$ 次，然后将这 $k-1$ 个元素中的最大值放回
    - 删除 $k$ 次，剩下第 $k + 1$ 个元素在栈顶
- 如果 $k=n$，我们只能删除 $k - 1$ 次然后将其中的最大值放回。我们不能删除 $k$ 次，因为这样会导致栈为空。
- 如果 $k>n$，我们总能够取到所有元素中的最大值
    - 若 $k=n+1$，我们可以先删除所有元素，然后放回最大值
    - 若 $k = n + 2$，我们可以先删除所有元素，然后先放回非最大值的任意一个值，再放回最大值（注意 $n=1$ 且 $k$ 为奇数的情形已经在前面排除了）
    - 若 $k = n + 2m + 1$，我们可以先按照 $k=n+1$ 的方式操作，再将最大值删除并放回 $m$ 次
    - 若 $k = n + 2m + 2$，我们可以先按照 $k=n+2$ 的方式操作，再将最大值删除并放回 $m$ 次。

综上，我们可以写出代码。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumTop(self, nums: List[int], k: int) -> int:
        if k == 0:
            return nums[0]
        
        n = len(nums)
        if n == 1 and k % 2 == 1:
            return -1
        
        if k < n:
            return max(nums[k], max([0] + nums[:k - 1]))
        
        if k == n:
            return max(nums[:k - 1])
        
        return max(nums)
```

:::

## Problem D - [得到要求路径的最小带权子图](https://leetcode-cn.com/problems/minimum-weighted-subgraph-with-the-required-paths/)

### 方法一：在原图和反图上求最短路径

考虑从 `src1` 和 `src2` 分别前往 `dest` 的最短路径。显然，这一路径最后总有一部分是重合的。也即，存在一个中间点 `M`，使得我们从 `src1` 到 `dest` 的最短路径为 `src1--M--dest`，`src2` 到 `dest` 的最短路径为 `src2--M--dest`。当然，`M` 有可能与 `src1`、`src2` 或 `dest` 中的某个点重合。

注意到，此时 `src1--M`、`src2--M`、`M--dest` 这三段路径没有重复的边。所以，此时这三段路程之和就等于子图的边权和。

我们现在需要尝试找到 `M` 点。显然，`M` 应该满足：

$$
dist[src1][M] + dist[src2][M] + dist[M][dest] = \min(dist[src1][V] + dist[src2][V] + dist[V][dest])
$$
其中 $dist[i][j]$ 表示从 $i$ 到 $j$ 的最短距离。

因此，我们在原图上，以 `src1` 和 `src2` 为源点求两次单源最短路径，再在反图（所有边反向形成的图）上以 `dest` 为源点求一次单源最短路径，就可以得到我们需要的答案。

- 时间复杂度 $\mathcal{O}(E\log V)$。需要注意的是，下面代码的复杂度实际上会略高于这一理论值，因为在某一元素已经入队但距离再次被更新时，并没有逐出原先在队列中的元素。
- 空间复杂度 $\mathcal{O}(E+V)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

const ll INF = 1e12;

class Solution {
    vector<ll> dijkstra(vector<vector<pair<int, int>>> &adj, int s) {
        int n = adj.size();
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        vector<ll> dis(n, INF);
        dis[s] = 0;
        pq.emplace(0, s);
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dis[u])
                continue;
            
            for (auto [v, w] : adj[u]) {
                if (d + w < dis[v]) {
                    dis[v] = d + w;
                    pq.emplace(dis[v], v);
                }
            }
        }
        
        return dis;
    }
    
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pair<int, int>>> adj(n), rev(n);
        for (auto &e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            rev[e[1]].emplace_back(e[0], e[2]);
        }
        
        auto da = dijkstra(adj, src1);
        auto db = dijkstra(adj, src2);
        auto dt = dijkstra(rev, dest);
        
        ll ans = INF;
        for (int i = 0; i < n; ++i)
            ans = min(ans, da[i] + db[i] + dt[i]);
        
        return ans == INF ? -1 : ans;
    }
};
```

:::

<Utterances />
