# Leetcode 第274场周赛题解

## Problem A - [检查是否所有 A 都在 B 之前](https://leetcode.cn/problems/check-if-all-as-appears-before-all-bs/)

### 方法一：模拟

按题意检查即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def checkString(self, s: str) -> bool:
        return s.rfind('a') < (len(s) if s.find('b') == -1 else s.find('b'))
```

:::

## Problem B - [银行中的激光束数量](https://leetcode.cn/problems/number-of-laser-beams-in-a-bank/)

### 方法一：模拟

逐行遍历，过程中维护上一个非空行中的设备数量。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def numberOfBeams(self, bank: List[str]) -> int:
        last = 0
        ans = 0
        for row in bank:
            devices = row.count('1')
            if devices > 0:
                ans += last * devices
                last = devices
        return ans
```

:::

一行版本：

::: details 参考代码（Python 3）

```python
class Solution:
    def numberOfBeams(self, bank: List[str]) -> int:
        return functools.reduce(lambda x, row: (rc:=row.count('1'), x[1] + x[2] * rc, rc if rc > 0 else x[2]), bank, (0, 0, 0))[1]
```

:::

## Problem C - [摧毁小行星](https://leetcode.cn/problems/destroying-asteroids/)

### 方法一：贪心

显然应该从小到大摧毁小行星。排序后逐个检查即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def asteroidsDestroyed(self, mass: int, asteroids: List[int]) -> bool:
        asteroids.sort()
        for asteroid in asteroids:
            if mass < asteroid:
                return False
            mass += asteroid
        return True
```

:::

一行版本：

::: details 参考代码（Python 3）

```python
class Solution:
    def asteroidsDestroyed(self, mass: int, asteroids: List[int]) -> bool:
        return functools.reduce(lambda x, asteroid: (x[0], False) if not x[1] or x[0] < asteroid else (x[0] + asteroid, True), sorted(asteroids), (mass, True))[1]
```

:::

## Problem D - [参加会议的最多员工数](https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/)

### 方法一：DFS

分析题目后，我们可以知道，有两种方式安排员工：

1. 所有被安排的员工构成一个环：A->B->C->D->…->A
2. 所有被安排的员工为若干个组，每个组的结构为：A->B->…->C↔D<-E<-…<-F

针对第一种情况，我们需要找出图中的最大环。在本题的限制之下（每个节点的出度都为1），不会出现环套环的情况，因此我们只需要枚举出所有的环即可。

针对第二种情况，我们需要在所有二元环的基础上，对于每一个二元环，在**反向图**中分别找出以其两个端点开始的最长链（注意排除二元环的另一方）。

> 在下面的参考代码中，对第一种情况的计算也是在反向图中进行的。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
    int n, max_loop, from_pairs;
    vector<int> color, dep;
    vector<pair<int, int>> pairs;
    vector<vector<int>> rev;
    
    void dfs(int u) {
        color[u] = 1;
        
        for (int v : rev[u]) {
            if (!color[v]) {
                dep[v] = dep[u] + 1;
                dfs(v);
            } else if (color[v] == 1) {
                int loop = dep[u] - dep[v] + 1;
                max_loop = max(max_loop, loop);
                if (loop == 2)
                    pairs.emplace_back(u, v);
            }
        }
        
        color[u] = 2;
    }
    
    int dfs2(int u, int p, int d) {
        int max_depth = d;
        
        for (int v : rev[u]) {
            if (v != p)
                max_depth = max(max_depth, dfs2(v, p, d + 1));
        }

        return max_depth;
    }

public:
    int maximumInvitations(vector<int>& favorite) {
        n = favorite.size();
        color = vector<int>(n);
        dep = vector<int>(n);
        max_loop = 0;
        
        rev = vector<vector<int>>(n);
        for (int i = 0; i < n; ++i)
            rev[favorite[i]].emplace_back(i);
        
        for (int i = 0; i < n; ++i) {
            if (!color[i])
                dfs(i);
        }
        
        from_pairs = 0;
        for (auto &[u, v] : pairs) {
            from_pairs += dfs2(u, v, 1);
            from_pairs += dfs2(v, u, 1);
        }
        
        return max(max_loop, from_pairs);
    }
};
```

:::

<Utterances />
