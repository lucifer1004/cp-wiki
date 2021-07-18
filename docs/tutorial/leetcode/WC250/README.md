# Leetcode 第250场周赛题解

## Problem A - [可以输入的最大单词数](https://leetcode-cn.com/problems/maximum-number-of-words-you-can-type/)

### 方法一：模拟

拆分成单词后，检查每个单词是否含有损坏的字母即可。

- 时间复杂度$\mathcal{O}(|S|)$。

- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def canBeTypedWords(self, text: str, brokenLetters: str) -> int:
        words = text.split()
        broken = set(brokenLetters)
        ans = 0
        for word in words:
            can = True
            for ch in word:
                if ch in broken:
                    can = False
                    break
            if can:
                ans += 1
        return ans
```

:::

## Problem B - [新增的最少台阶数](https://leetcode-cn.com/problems/add-minimum-number-of-rungs/)

### 方法一：贪心

要求新增台阶数最少，我们就贪心地尽可能用上每一块已有的台阶。如果相邻两块台阶之间的距离$\Delta$超过了$dist$，我们就增加$\left\lfloor\frac{\Delta-1}{dist}\right\rfloor$块台阶。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int addRungs(vector<int>& rungs, int dist) {
        int now = 0, ans = 0;
        for (int rung : rungs) {
            ans += (rung - now - 1) / dist;
            now = rung;
        }
        return ans;
    }
};
```

:::

## Problem C - [扣分后的最大得分](https://leetcode-cn.com/problems/maximum-number-of-points-with-cost/)

### 方法一：动态规划

显然当前行的分数只与上一行的选择有关，因此容易想到使用动态规划求解。但朴素的动态规划算法中，我们对于当前行的每一列，都需要考虑上一行的每一列，总时间复杂度为$\mathcal{O}(RC^2)$会超时。

如何进行优化呢？

对于某一列，我们可以考虑上一行所选定的列在其左侧还是在其右侧。

首先考虑左侧的情况。我们从左到右依次处理。假设当前来自左侧的最大值为$lmax$，则每次右移时，$lmax$会变为$max(lmax-1, dp[i])$。这是因为，如果上一行选择的列在左边，不管它具体在哪一个位置，这次右移时一定会减少$1$的分数；而如果选择当前列正上方的格子，则不会扣除分数。

右侧的情况与之类似。

这样，我们就在$\mathcal{O}(C)$的时间里完成了一行的转移，从而将总时间复杂度降低到了$\mathcal{O}(RC)$。

- 时间复杂度$\mathcal{O}(RC)$。
- 空间复杂度$\mathcal{O}(C)$。

::: details 参考代码（C++）

```c++
class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int n = points.size(), m = points[0].size();
        vector<long long> dp(m);
        for (int i = 0; i < n; ++i) {
            vector<long long> ndp(m);
            long long lmax = 0;
            for (int j = 0; j < m; ++j) {
                lmax = max(lmax - 1, dp[j]);
                ndp[j] = max(ndp[j], lmax);
            }
            long long rmax = 0;
            for (int j = m - 1; j >= 0; --j) {
                rmax = max(rmax - 1, dp[j]);
                ndp[j] = max(ndp[j], rmax);
            }
            for (int j = 0; j < m; ++j)
                ndp[j] += points[i][j];
            dp = move(ndp);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

:::

## Problem D - [查询最大基因差](https://leetcode-cn.com/problems/maximum-genetic-difference-query/)

### 方法一：0-1字典树+离线查询

在回答一次查询时，我们需要考虑的是$node_i$及其所有的祖先节点。注意到在DFS过程中，我们访问到一个节点时，栈中的元素恰好是其和其所有祖先节点，因此想到利用DFS来离线完成查询。

具体的做法是，把查询按照$node_i$进行分组，然后进行DFS。DFS到某一个节点时，完成所有询问这一节点的查询。

求最大异或和的经典方法是0-1字典树。字典树中越靠近根部的节点代表更高的二进制位。对于给定的$val$，我们按照二进制位由高到低处理，对于第$i$位，如果字典树中存在与$val$的第$i$位相异的节点，则进入对应分支，并将这一位对应的数值累加入最后的答案；否则，我们进入另一分支，同时答案保持不变。

本题中，我们需要在DFS过程中对0-1字典树进行动态更新。因为节点出栈时需要将其对应的贡献删去，这里为了简化操作，我们不删除字典树中节点，而是给每个节点增加一个计数值。在节点入栈时将其二进制位所对应的字典树节点加一，而在出栈时将对应节点减一。计数值为$0$的节点在查询时应当视同不存在。

- 时间复杂度$\mathcal{O}((N+Q)K)$。其中$K$为考虑的二进制位数。
- 空间复杂度$\mathcal{O}(N+Q+2^K)$。

::: details 参考代码（C++）

```cpp
const int K = 20;

struct TrieNode {
    int cnt = 0;
    TrieNode *children[2]{};
};

void dfs(int u, vector<vector<int>> &adj, vector<vector<pair<int, int>>> &groups, TrieNode *trie, vector<int> &ans) {
    TrieNode *p = trie;
    for (int k = K - 1; k >= 0; --k) {
        int nxt = (u & (1 << k)) ? 1 : 0;
        if (!p->children[nxt])
            p->children[nxt] = new TrieNode();
        p = p->children[nxt];
        p->cnt++;
    }
    
    for (auto [val, idx] : groups[u]) {
        p = trie;
        int hi = 0;
        for (int k = K - 1; k >= 0; --k) {
            int nxt = (val & (1 << k)) ? 0 : 1;
            if (p->children[nxt] && p->children[nxt]->cnt) {
                p = p->children[nxt];
                hi ^= (1 << k);
            } else {
                if (!p->children[nxt ^ 1])
                    p->children[nxt ^ 1] = new TrieNode();
                p = p->children[nxt ^ 1];
            }
        }
        ans[idx] = hi;
    }
    
    for (int v : adj[u]) {
        dfs(v, adj, groups, trie, ans);
    }
    
    p = trie;
    for (int k = K - 1; k >= 0; --k) {
        int nxt = (u & (1 << k)) ? 1 : 0;
        p = p->children[nxt];
        p->cnt--;
    }
}

class Solution {
public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        int root = -1;
        int n = parents.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            if (parents[i] == -1)
                root = i;
            else
                adj[parents[i]].emplace_back(i);
        } 
        
        assert(root != -1);
        
        int q = queries.size();
        vector<int> ans(q);
        vector<vector<pair<int, int>>> groups(n);
        for (int i = 0; i < q; ++i) {
            int node = queries[i][0], val = queries[i][1];
            groups[node].emplace_back(val, i);
        }
        TrieNode *trie = new TrieNode();
        
        dfs(root, adj, groups, trie, ans);
        
        return ans;
    }
};
```

:::

<Utterances />