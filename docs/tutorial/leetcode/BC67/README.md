# Leetcode 第67场双周赛题解

## Problem A - [找到和最大的长度为 K 的子序列](https://leetcode-cn.com/problems/find-subsequence-of-length-k-with-the-largest-sum/)

### 方法一：排序

先排序找出最大的$K$个数，然后再将它们按照原数组中的位置排序。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        return [nums[i] for i in sorted([x[1] for x in sorted([(num, i) for i, num in enumerate(nums)])[-k:]])]
```

:::


## Problem B - [适合打劫银行的日子](https://leetcode-cn.com/problems/find-good-days-to-rob-the-bank/)

### 方法一：动态规划

从左到右递推找出每个数左边最长不上升子串的长度，再从右到左递推找出每个数右边最长不上升子串的长度；左右长度都满足的即为好日子。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        vector<int> l(n), r(n);
        for (int i = 1; i < n; ++i)
            if (security[i] <= security[i - 1])
                l[i] = l[i - 1] + 1;
        for (int i = n - 2; i >= 0; --i)
            if (security[i] <= security[i + 1])
                r[i] = r[i + 1] + 1;
        vector<int> ans;
        for (int i = 0; i < n; ++i)
            if (l[i] >= time && r[i] >= time)
                ans.emplace_back(i);
        return ans;
    }
};
```

:::

## Problem C - [引爆最多的炸弹](https://leetcode-cn.com/problems/detonate-the-maximum-bombs/)

### 方法一：BFS或DFS

首先根据每个炸弹的位置和引爆范围，计算出它可以直接引爆哪些其他炸弹，然后连边。注意这里的边是**有向边**，因为A可以引爆B，不代表B可以引爆A。

之后就是每个炸弹都作为源点BFS/DFS一次，求出所有答案中的最大值即可。

- 时间复杂度$\mathcal{O}(N^3)$。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

ll dis(int x1, int y1, int x2, int y2) {
    return 1LL * (x1 - x2) * (x1 - x2) + 1LL * (y1 - y2) * (y1 - y2);
}

class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            auto &p = bombs[i];
            for (int j = 0; j < n; ++j) {
                auto &q = bombs[j];
                if (dis(p[0], p[1], q[0], q[1]) <= 1LL * p[2] * p[2])
                    adj[i].emplace_back(j);
            }
        }
        
        int ans = 1;
        for (int i = 0; i < n; ++i) {
            vector<bool> vis(n);
            vis[i] = true;
            queue<int> q;
            q.push(i);
            int cnt = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        cnt++;
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
            ans = max(ans, cnt);
        }
        
        return ans;
    }
};
```

:::

### 方法二：位优化Floyd

在建立有向图后，我们可以使用位优化的Floyd来进行第二步计算。

- 时间复杂度$\mathcal{O}(N^3/W)$，其中$W$为字长。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
using bs = bitset<100>;

ll dis(int x1, int y1, int x2, int y2) {
    return 1LL * (x1 - x2) * (x1 - x2) + 1LL * (y1 - y2) * (y1 - y2);
}

class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<bs> d(n);
        for (int i = 0; i < n; ++i) {
            d[i].set(i);
            auto &p = bombs[i];
            for (int j = 0; j < n; ++j) {
                auto &q = bombs[j];
                if (dis(p[0], p[1], q[0], q[1]) <= 1LL * p[2] * p[2])
                    d[i].set(j);
            }
        }
        
        for (int mid = 0; mid < n; ++mid) 
            for (int s = 0; s < n; ++s) {
                if (d[s][mid])
                    d[s] |= d[mid];
            }
        
        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans = max(ans, (int)d[i].count());
        
        return ans;
    }
};
```

:::

## Problem D - [序列顺序查询](https://leetcode-cn.com/problems/sequentially-ordinal-rank-tracker/)

### 方法一：平衡树

本题中需要使用支持查询第$i$位元素的平衡树。`set`或`multiset`是不行的，因为不支持按位查询。不过我们还有PBDS（Policy-based data structures），在力扣上也是可以直接使用的。

注意这里比较函数用了`less`，而分数要从大到小，所以这里分数取相反数后再插入。

当然，其他的平衡树也都是可以的，Splay、Treap、红黑树……有模板的可以用模板，不过手写的话就要慢一点了。

- 插入和查询的时间复杂度都为$\mathcal{O}(\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

class SORTracker {
    ordered_set<pair<int, string>> s;
    int counter = 0;
public:
    SORTracker() {}
    
    void add(string name, int score) {
        s.insert(make_pair(-score, name));
    }
    
    string get() {
        return s.find_by_order(counter++)->second;
    }
};
```

:::

### 方法二：双set

注意到本题中的查询操作并不是随机进行的，而是按照严格递增的方式，我们可以采用类似数据流中中位数的方式，维护两个`set`来实现本题要求的功能。

- 插入的时间复杂度都为$\mathcal{O}(\log N)$，查询的时间复杂度在均摊意义下为$\mathcal{O}(\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class SORTracker {
    set<pair<int, string>, greater<>> s1;
    set<pair<int, string>> s2;
    int counter = 0;
public:
    SORTracker() {}
    
    void add(string name, int score) {
        s1.emplace(-score, name);
        if (*s1.begin() > *s2.begin()) {
            s2.insert(*s1.begin());
            s1.erase(s1.begin());
        }
    }
    
    string get() {
        counter++;
        while (s1.size() > counter) {
            s2.insert(*s1.begin());
            s1.erase(s1.begin());
        }
        while (s1.size() < counter) {
            s1.insert(*s2.begin());
            s2.erase(s2.begin());
        }
        return s1.begin()->second;
    }
};
```

:::

<Utterances />
