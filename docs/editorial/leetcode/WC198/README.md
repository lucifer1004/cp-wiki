# Leetcode 第198场周赛题解

## Problem A - [换酒问题](https://leetcode-cn.com/problems/water-bottles/)

直接模拟即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numWaterBottles(int a, int b) {
        int ans = a, bottles = a;
        while (bottles >= b) {
            ans += bottles / b;
            bottles = bottles / b + bottles % b;
        }
        return ans;
    }
};
```

:::

## Problem B - [子树中标签相同的节点数](https://leetcode-cn.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)

DFS过程中记录当前节点子树中每种标签的数目即可。

::: details 参考代码（C++）

```cpp
class Solution {
    int n;
    vector<int> ans;
    vector<vector<int>> adj;
    string labels;
    vector<int> dfs(int u, int p) {
        vector<int> cnt(26);
        cnt[labels[u] - 'a'] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                vector<int> child = dfs(v, u);
                for (int i = 0; i < 26; ++i)
                    cnt[i] += child[i];
            }
        }
        ans[u] = cnt[labels[u] - 'a'];
        return cnt;
    }
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        ans = vector<int>(n);
        adj = vector<vector<int>>(n);
        this->labels = labels;
        this->n = n;
        for (auto v : edges) {
            adj[v[0]].emplace_back(v[1]);
            adj[v[1]].emplace_back(v[0]);
        }
        dfs(0, -1);
        return ans;
    }
};
```

:::

## Problem C - [最多的不重叠子字符串](https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-substrings/)

首先提取出可以独立成立的所有区间，然后将这些区间按照左端点排序，再进行动态规划求取最优方案。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> first(26, -1), last(26, -1);
        vector<vector<int>> v(26);
        for (int i = 0; i < n; ++i) {
            int d = s[i] - 'a';
            v[d].emplace_back(i);
            if (first[d] == -1)
                first[d] = i;
            last[d] = i;
        }
        for (int k = 0; k < 26; ++k) {
            for (int i = 0; i < 26; ++i) {
                if (first[i] == -1)
                    continue;
                    for (int j = 0; j < 26; ++j) {
                        if (j == i)
                            continue;
                        int l = first[i], r = last[i];
                        auto lit = lower_bound(v[j].begin(), v[j].end(), l);
                        auto rit = lower_bound(v[j].begin(), v[j].end(), r);
                        if (rit - lit > 0) {
                            first[i] = min(first[i], first[j]);
                            last[i] = max(last[i], last[j]);
                        }
                    }
                }
        }

        vector<pair<int, int>> seg;
        for (int i = 0; i < 26; ++i) {
            if (first[i] != -1)
                seg.emplace_back(first[i], last[i]);
        }
        sort(seg.begin(), seg.end());
        int num = 0, len = n;
        vector<int> best;
        int m = seg.size();
        vector<int> f(m), g(m);
        vector<vector<int>> h(m);
        for (int i = 0; i < m; ++i) {
            int clen = seg[i].second - seg[i].first + 1;
            f[i] = 1;
            g[i] = clen;
            h[i] = {i};
            for (int j = 0; j < i; ++j) {
                if (seg[j].second < seg[i].first) {
                    if (f[j] + 1 > f[i] || (f[j] + 1 == f[i] && g[j] + clen < g[i])) {
                        f[i] = f[j] + 1;
                        g[i] = g[j] + clen;
                        h[i] = h[j];
                        h[i].emplace_back(i);
                    }   
                }
            }
            if (f[i] > num || (f[i] == num && g[i] < len)) {
                num = f[i];
                len = g[i];
                best = h[i];
            }
        }
        vector<string> ans;
        for (int i : best)
            ans.emplace_back(s.substr(seg[i].first, seg[i].second - seg[i].first + 1));
        return ans;
    }
};
```

:::

## Problem D - [找到最接近目标值的函数值](https://leetcode-cn.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/)

容易发现，在$l$固定时，$func(arr,l,r)$的结果是单调递减的，因此可以再通过二分查找找到与$target$最接近的两个值（一前一后），然后更新结果。为了快速计算$func(arr,l,r)$，可以预构建一个稀疏表。

::: details 参考代码（C++）

```cpp
#define K 20

class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int n = arr.size();
        vector<vector<int>> st(n, vector<int>(K));
        for (int i = 0; i < n; ++i)
            st[i][0] = arr[i];
        for (int k = 1; k < K; ++k) {
            for (int i = 0; i < n; ++i) {
                st[i][k] = st[i][k - 1];
                int r = i + (1 << (k - 1));
                if (r < n)
                    st[i][k] &= st[r][k - 1];
            }
        }
        auto query = [&](int l, int r) {
            if (l == r)
                return arr[l];
            int len = r - l + 1;
            int depth = log2(len - 1);
            return st[l][depth] & st[r - (1 << depth) + 1][depth];
        };
        int ans = INT_MAX;
        for (int l = 0; l < n; ++l) {
            int lo = l, hi = n - 1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                int f = query(l, mid);
                if (f == target)
                    return 0;
                if (f < target)
                    hi = mid - 1;
                else
                    lo = mid + 1;
            }
            for (int i = max(l, lo - 1); i < min(n, lo + 1); ++i)
                ans = min(ans, abs(query(l, i) - target));
        }
        return ans;
    }
};
```

:::

再观察一下，可以发现，在固定一个端点的情况下，无论另一端点如何取值，$func(arr,l,r)$至多有$\log C$种不同的取值，因为只要某一位变为了$0$，之后就无法回到$1$。因此，我们可以得到一个更为简洁的解法。始终使用一个集合维护当前的合法取值，然后不断将右边的下一个数与集合中元素求与，并把该数也加入集合。从而，在任意时刻，这一集合都包含了右端点固定情况下的所有合法取值。因此，我们只需要遍历右端点，同时在每次遍历时计算当前集合中所有元素与目标值的曼哈顿距离，并更新答案。这样的总时间复杂度是$O(N\log C)$。

::: details 参考代码（Python3）

```python
class Solution:
    def closestToTarget(self, arr: List[int], target: int) -> int:
        ans = abs(arr[0] - target)
        valid = {arr[0]}
        for num in arr:
            valid = {x & num for x in valid} | {num}
            ans = min(ans, min(abs(x - target) for x in valid))
        return ans
```

:::

<Utterances />
