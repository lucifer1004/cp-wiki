# Leetcode 第269场周赛题解

## Problem A - [找出数组排序后的目标下标](https://leetcode-cn.com/problems/find-target-indices-after-sorting-array/)

### 方法一：暴力

排序后统计即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def targetIndices(self, nums: List[int], target: int) -> List[int]:
        return [i for i, num in enumerate(sorted(nums)) if num == target]
```

:::

## Problem B - [半径为 k 的子数组平均值](https://leetcode-cn.com/problems/k-radius-subarray-averages/)

### 方法一：模拟

求出所有长度为$2k+1$的子数组和平均值即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        s = 0
        ans = [-1] * n
        for i in range(n):
            s += nums[i]
            if i >= 2 * k:
                ans[i - k] = s // (2 * k + 1)
                s -= nums[i - k * 2]
        return ans
```

:::

## Problem C - [从数组中移除最大值和最小值](https://leetcode-cn.com/problems/removing-minimum-and-maximum-from-array/)

### 方法一：贪心

如果只有一个元素，答案显然为$1$。

否则，找出最大值和最小值的位置，考虑三种情况：

- 只取左边
- 只取右边
- 取两边

取三种情况的最小代价即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return 1
        l = nums.index(min(nums))
        r = nums.index(max(nums))
        if l > r:
            l, r = r, l
        return min(n - (r - l - 1), r + 1, n - l)
```

:::

## Problem D - [找出知晓秘密的所有专家](https://leetcode-cn.com/problems/find-all-people-with-secret/)

### 方法一：多源BFS

将所有会议按照召开的时间分组，然后从早到晚考虑每一组会议。

每一组会议构成了一个图，我们在这个图上从所有当前已经知晓秘密的专家开始进行多源BFS即可。

代码实现有一些需要注意的细节，如果不小心，会导致超时。

- 时间复杂度$\mathcal{O}(N+E+MAXT)$
- 空间复杂度$\mathcal{O}(N+E)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<bool> known(n);
        known[0] = true;
        known[firstPerson] = true;
  
        int maxT = 0;
        for (auto &meeting : meetings)
            maxT = max(maxT, meeting[2]);
        vector<vector<pair<int, int>>> time(maxT + 1);
        for (auto &meeting : meetings)
            time[meeting[2]].emplace_back(meeting[0], meeting[1]);
        
        vector<vector<int>> adj(n); // 复用邻接表
        for (int i = 1; i <= maxT; ++i) {
            if (time[i].empty())
                continue;
            
            unordered_set<int> vis; // 用集合，而不是布尔数组
            queue<int> q;
            for (auto &[u, v] : time[i]) { // 设置邻接表
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
                if (known[u] && !vis.count(u)) {
                    vis.insert(u);
                    q.push(u);
                }
                if (known[v] && !vis.count(v)) {
                    vis.insert(v);
                    q.push(v);
                }
            }
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (!vis.count(v)) {
                        known[v] = true;
                        vis.insert(v);
                        q.push(v);
                    }
                }
            }
            
            for (auto &[u, v] : time[i]) { // 还原邻接表
                adj[u].clear();
                adj[v].clear();
            }
        }
        
        vector<int> ans;
        for (int i = 0; i < n; ++i)
            if (known[i])
                ans.push_back(i);
        return ans;
    }
};
```

:::

<Utterances />
