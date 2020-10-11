# Leetcode 第210场周赛题解

## Problem A - [括号的最大嵌套深度](https://leetcode-cn.com/problems/maximum-nesting-depth-of-the-parentheses/)

只有括号是有效字符，其他字符都不需要考虑。每次遇到括号就更新当前深度，如果当前深度大于最大深度就更新最大深度。

时间复杂度$O(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxDepth(string s) {
        int d = 0, md = 0;
        for (char c : s) {
            if (c == '(')
                md = max(md, ++d);
            if (c == ')')
                d--;
        }
        return md;
    }
};
```

:::

## Problem B - [最大网络秩](https://leetcode-cn.com/problems/maximal-network-rank/)

题目说得很高深，其实就是问，图中任意找出两个点，以其中至少一个为端点的不重复的边的数目的最大值是多少？

首先把边集转为邻接表，然后枚举即可。我们可以先确定一个点，然后首先枚举与其邻接的点（结果需要减去$1$以去重）；然后枚举剩余的点（结果不需要去重）。

总时间复杂度$O(N^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        int ans = 0;
        vector<vector<int>> adj(n);
        for (auto road : roads)
            adj[road[0]].emplace_back(road[1]), adj[road[1]].emplace_back(road[0]);
        for (int i = 0; i < n; ++i) {
            vector<bool> v(n);
            for (int j : adj[i]) {
                ans = max(ans, (int)adj[i].size() + (int)adj[j].size() - 1);
                v[j] = true;
            }
            for (int j = i + 1; j < n; ++j)
                if (!v[j])
                    ans = max(ans, (int)adj[i].size() + (int)adj[j].size());
        }
        return ans;
    }
};
```

:::

## Problem C - [分割两个字符串得到回文串](https://leetcode-cn.com/problems/split-two-strings-to-make-palindrome/)

以$A_\text{prefix}+B_\text{suffix}$为例，如果它是一个回文串，考虑它的左半边，有两种情况：

1. 前一段，满足$A[i]=B[n-i+1]$，后一段，满足$A[i]=A[n-i+1]$
2. 前一段，满足$A[i]=B[n-i+1]$，后一段，满足$B[i]=B[n-i+1]$

我们先考虑第一种情况。显然，我们可以使用贪心策略，如果$A[i]=B[n-i+1]$能够满足，就一直使用$B$；当这一条件不满足时，再改为使用$A$。

交换$A$和$B$，我们就可以解决$B_\text{prefix}+A_\text{suffix}$的第一种情况。

类似地，我们可以解决第二种情况。但这里有一个更简单的方法，考虑到$A_\text{prefix}+B_\text{suffix}=B'_\text{prefix}+A'_\text{suffix}$，我们只需要将$A$和$B$都取为倒序，然后再进行两次检查，就可以得到最终的结果，而不需要对第二种情况进行单独讨论。

最终，我们一共对四种情况进行了计算，分别是$(A,B),(B,A),(A',B'),(B',A')$，总时间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
    bool check(string a, string b) {
        int n = a.size();
        bool flag = true;
        for (int i = 0; i < n / 2; ++i) {
            if (flag) {
                if (a[i] != b[n - 1 - i])
                    flag = false;
            }
            if (!flag)
                if (a[i] != a[n - 1 - i])
                    return false;
        }
        return true;
    }
public:
    bool checkPalindromeFormation(string a, string b) {
        if (check(a, b) || check(b, a))
            return true;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        if (check(a, b) || check(b, a))
            return true;
        return false;
    }
};
```

:::

## Problem D - [统计子树中城市之间最大距离](https://leetcode-cn.com/problems/count-subtrees-with-max-distance-between-cities/)

注意到数据范围$N\leq15$，我们可以枚举子集的构成方式。（这里吐槽一下题目的命名，用“子树”这个叫法，很容易让人误解，因此我们下面统一称为“子集”。）

对于每一种子集，我们可以用树形动态规划进行求解。对于每一个节点，我们要求出以其为根节点的子树中的最大距离和最大深度。最大深度很容易求得，最大距离则需要分几种情况进行讨论：

1. 从该节点到该字数中深度最大的节点
2. 从以该节点的一个孩子节点为根节点的子树中深度最大的节点，到以该节点的另一个孩子节点为根节点的子树中深度最大的节点
3. 从以该节点的一个孩子节点为根节点的子树中的一个节点，到同一子树中的另一节点

容易看出，第一种和第三种情况比较容易解决，我们只要利用对孩子节点进行递归得到的结果即可计算出来。对于第二种情况，我们则需要记录所有孩子节点的最大深度中最大的两个值。

需要注意的是，我们在DFS过程中还需要记录访问过的城市数量，最后与子集中的城市数量进行比较，如果二者不相等，则说明该子集不连通，是一个非法的子集，应当予以排除。

总时间复杂度为$O(N\cdot2^N)$。

::: warning 注意

我们应当构建一次邻接表，然后在DFS过程中判断每条边是否存在于当前子集中，而不是针对每一子集构建一次邻接表。虽然二者的时间复杂度是相同的，但如果采用后者，也即每次重新构建邻接表，那么每次都需要访问所有边，而实际上有很多边在DFS过程中并不会被访问到。另一方面，`vector`的创建也有很大的额外开销。

实际上，经过测试，这两种方法的运行时间相差超过了10倍。

:::

::: details 参考代码（C++）

```cpp
class Solution {
    vector<vector<int>> adj;
    int cities = 0;
    bitset<16> bs;
    pair<int, int> dfs(int u, int d, int p) {
        int max_dist = 0, max_depth = d;
        cities++;
        int m1 = -1, m2 = -1;
        for (int v : adj[u]) {
            if (bs[v] && v != p) {
                auto [dis, dep] = dfs(v, d + 1, u);
                max_depth = max(max_depth, dep);
                max_dist = max(max_dist, dis);
                if (m1 < dep) {
                    m2 = m1;
                    m1 = dep;
                } else if (m2 < dep)
                    m2 = dep;
            }
        }
        max_dist = max(max_dist, max_depth - d);
        if (m2 > 0)
            max_dist = max(max_dist, m1 + m2 - 2 * d);
        return {max_dist, max_depth};
    }
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        vector<int> ans(n - 1);
        adj = vector<vector<int>>(n);
        for (auto e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        for (int i = 1; i < (1 << n); ++i) {
            bs = bitset<16>(i);
            int idx = 0;
            while (!bs[idx])
                idx++;
            cities = 0;
            auto [max_dist, max_depth] = dfs(idx, 0, -1);
            if (cities == bs.count() && max_dist > 0)
                ans[max_dist - 1]++;
        }
        return ans;
    }
};
```

:::

<Utterances />
