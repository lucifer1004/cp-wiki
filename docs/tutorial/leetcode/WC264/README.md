# Leetcode 第264场周赛题解

## Problem A - [句子中的有效单词数](https://leetcode-cn.com/problems/number-of-valid-words-in-a-sentence/)

### 方法一：正则表达式

构造一个正则表达式对每个token进行校验即可。

::: details 参考代码（Python 3）

```python
import re

class Solution:
    def countValidWords(self, sentence: str) -> int:
        return len(list(filter(lambda x: re.match('^[a-z]*([a-z]-[a-z])?[a-z]*[!\.,]?$', x), sentence.split())))
```

:::

## Problem B - [下一个更大的数值平衡数](https://leetcode-cn.com/problems/next-greater-numerically-balanced-number/)

### 方法一：打表

打表暴力求出所有不超过`1224444`（因为本题中$N\le1000000$）的数值平衡数，之后对于每一询问直接二分查找即可。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
import bisect

nums = [1, 22, 122, 212, 221, 333, 1333, 3133, 3313, 3331, 4444, 14444, 22333, 23233, 23323, 23332, 32233, 32323, 32332, 33223, 33232, 33322, 41444, 44144, 44414, 44441, 55555, 122333, 123233, 123323, 123332, 132233, 132323, 132332, 133223, 133232, 133322, 155555, 212333, 213233, 213323, 213332, 221333, 223133, 223313, 223331, 224444, 231233, 231323, 231332, 232133, 232313, 232331, 233123, 233132, 233213, 233231, 233312, 233321, 242444, 244244, 244424, 244442, 312233, 312323, 312332, 313223, 313232, 313322, 321233, 321323, 321332, 322133, 322313, 322331, 323123, 323132, 323213, 323231, 323312, 323321, 331223, 331232, 331322, 332123, 332132, 332213, 332231, 332312, 332321, 333122, 333212, 333221, 422444, 424244, 424424, 424442, 442244, 442424, 442442, 444224, 444242, 444422, 515555, 551555, 555155, 555515, 555551, 666666, 1224444]

class Solution:
    def nextBeautifulNumber(self, n: int) -> int:
        return nums[bisect.bisect_right(nums, n)]
```

:::

## Problem C - [统计最高分的节点数目](https://leetcode-cn.com/problems/count-nodes-with-the-highest-score/)

### 方法一：DFS

我们可以通过DFS求出每个节点为根的子树的大小，从而就能求出这个节点的分数。因为题目限定了这是一棵二叉树，所以删除与一个节点相连的边后，至多会形成三个子树，因此分数的最大值在长整型范围内，用一个长整型来保存即可（整型有可能溢出）。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
    long long hi;
    int n, hi_cnt;
    vector<int> cnt;
    vector<vector<int>> adj;
    
    void dfs(int u) {
        cnt[u] = 1;
        for (int v : adj[u]) {
            dfs(v);
            cnt[u] += cnt[v];
        }
        long long rem = max(1, n - cnt[u]);
        for (int v : adj[u])
            rem *= cnt[v];
        if (rem > hi) {
            hi = rem;
            hi_cnt = 0;
        }
        if (rem == hi)
            hi_cnt++;
    }
public:
    int countHighestScoreNodes(vector<int>& parents) {
        n = parents.size();
        adj = vector<vector<int>>(n);
        for (int i = 1; i < n; ++i)
            adj[parents[i]].push_back(i);
        
        cnt = vector<int>(n);
        hi = 0, hi_cnt = 0;
        dfs(0);

        return hi_cnt;
    }
};
```

:::

## Problem D - [并行课程 III](https://leetcode-cn.com/problems/parallel-courses-iii/)

### 方法一：DAG上的动态规划

本题是DAG（有向无环图）上动态规划的经典模板题。因为同一时间开始的课程数不限，所以我们只要按照拓扑序来处理课程，就可以求出每个课程的最早开始时间，从而就可以求出其最早结束时间。所有课程的最早结束时间的最大值就是本题的答案。

- 时间复杂度$\mathcal{O}(V+E)$。
- 空间复杂度$\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> adj(n);
        vector<int> deg(n);
        for (auto &relation : relations) {
            int u = relation[0] - 1, v = relation[1] - 1;
            adj[u].push_back(v);
            deg[v]++;
        }
        
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (deg[i] == 0)
                q.emplace(i);
        
        vector<int> dp(n);
        while (!q.empty()) {
            int u = q.front();
            dp[u] += time[u];
            q.pop();
            for (int v : adj[u]) {
                dp[v] = max(dp[v], dp[u]);
                deg[v]--;
                if (deg[v] == 0)
                    q.emplace(v);
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};
```

:::

<Utterances />
