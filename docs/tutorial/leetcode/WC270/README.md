# Leetcode 第270场周赛题解

## Problem A - [找出 3 位偶数](https://leetcode-cn.com/problems/finding-3-digit-even-numbers/)

### 方法一：暴力

枚举$[100, 999]$中的所有偶数，然后判断它们是否能由原数组中的数字构成。

- 时间复杂度$\mathcal{O}(N + C)$，其中$C$为区间内偶数的数目。
- 空间复杂度$\mathcal{O}(N + C)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findEvenNumbers(self, digits: List[int]) -> List[int]:
        cnt = collections.Counter(digits)
        return [num for num in range(100, 1000, 2) if all(str(num).count(ch) <= cnt[int(ch)] for ch in set(str(num)))]
```

:::

## Problem B - [删除链表的中间节点](https://leetcode-cn.com/problems/delete-the-middle-node-of-a-linked-list/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode *p = head;
        vector<ListNode *> nodes;
        while (p != nullptr) {
            nodes.push_back(p);
            p = p->next;
        }
        
        int n = nodes.size();
        if (n == 1)
            return nullptr;
        
        int mid = n / 2;
        ListNode *pre = nodes[mid - 1];
        ListNode *nxt = (mid + 1 < n) ? nodes[mid + 1] : nullptr;
        pre->next = nxt;
        
        return nodes[0];
    }
};
```

:::

## Problem C - [从二叉树一个节点到另一个节点每一步的方向](https://leetcode-cn.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/)

### 方法一：DFS+BFS

先DFS建出邻接表，然后BFS求解。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
    unordered_map<int, vector<pair<int, int>>> adj;
    
    void dfs(TreeNode *u, TreeNode *p) {
        if (p != nullptr)
            adj[u->val].emplace_back(p->val, 0);
        
        if (u->left != nullptr) {
            adj[u->val].emplace_back(u->left->val, 1);
            dfs(u->left, u);
        }
        
        if (u->right != nullptr) {
            adj[u->val].emplace_back(u->right->val, 2);
            dfs(u->right, u);
        }
    }
    
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        dfs(root, nullptr);
        
        unordered_map<int, pair<int, int>> pre;
        unordered_set<int> vis;
        queue<int> q;
        q.push(startValue);
        vis.insert(startValue);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == destValue)
                break;
            
            for (auto [v, t] : adj[u]) {
                if (!vis.count(v)) {
                    vis.insert(v);
                    pre[v] = make_pair(u, t);
                    q.push(v);
                }
            }
        }
        
        string ans;
        string edge = "ULR";
        int p = destValue;
        while (pre.count(p)) {
            auto [u, t] = pre[p];
            ans.push_back(edge[t]);
            p = u;
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

:::

## Problem D - [合法重新排列数对](https://leetcode-cn.com/problems/valid-arrangement-of-pairs/)

### 方法一：欧拉回路

确定有解的情况下，说明以数字为节点，以数对为边，一定存在欧拉路。

为了便于求解，我们首先判断是否存在奇点。如果存在，那么我们需要增加一条边连接两个奇点，从而将欧拉路变为欧拉回路。

变为欧拉回路之后，就可以任选起点，然后在$\mathcal{O}(N)$时间内找到一条合法的回路。

接下来我们需要处理两个特殊情况：
- 如果之前加过边，我们需要将加的边删去；
- 得到的答案有可能反向了。此时需要将所有边反向，再将答案数组整体反向。

复杂度方面，
- 不考虑最后用`map`判断是否反向的话，时间复杂度$\mathcal{O}(N)$；如果实现一下`vector<int>`的哈希函数，可以替换为`unordered_map`，从而保证整体时间复杂度仍为$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int n = pairs.size();
        unordered_map<int, unordered_multiset<int>> in, out;
        unordered_set<int> keys;
        
        for (int i = 0; i < n; ++i) {
            int f = pairs[i][0], s = pairs[i][1];
            out[f].insert(s);
            in[s].insert(f);
            keys.insert(f), keys.insert(s);
        }
        
        int u = -1, v = -1;
        for (auto k : keys) {
            int delta = (int)out[k].size() - (int)in[k].size();
            if (delta == 1)
                u = k;
            if (delta == -1)
                v = k;
        }
        
        if (u != -1) {
            out[v].insert(u);
        }
                    
        int first = out.begin()->first;
        stack<int> st;
        st.push(first);
        vector<int> res;
        while (!st.empty()) {
            int u = st.top();
            if (out[u].empty()) {
                res.push_back(u);
                st.pop();
            } else {
                int v = *out[u].begin();
                out[u].erase(out[u].begin());
                st.push(v);
            }
        }
        
        vector<vector<int>> ans;
        for (int i = 0; i + 1 < res.size(); ++i)
            ans.push_back({res[i], res[i + 1]});
        
        // 如果一开始有奇点，那么得到的结果会多出一条边，找到这条边并将其删去
        // 原来的答案为S - E - T，其中E为多出的那条边
        // 那么新的答案就是T - S
        if (ans.size() > n) {
            for (int i = 0; i <= n; ++i) {
                int p = ans[i][0], q = ans[i][1];
                if ((p == u && q == v) || (p == v && q == u)) {
                    vector<vector<int>> new_ans;
                    if (i < n)
                        new_ans.insert(new_ans.end(), ans.begin() + i + 1, ans.end());
                    if (i > 0)
                        new_ans.insert(new_ans.end(), ans.begin(), ans.begin() + i);
                    ans = move(new_ans);
                    break;
                }
            }
        }
        
        // 判断是否需要反向
        map<vector<int>, int> mp;
        for (auto &p : pairs)
            mp[p]++;

        for (int i = 0; i < n; ++i) {
            if (mp[ans[i]] == 0) {
                for (int i = 0; i < n; ++i)
                    reverse(ans[i].begin(), ans[i].end());
                reverse(ans.begin(), ans.end());
                break;
            }
            mp[ans[i]]--;
        }  
        
        return ans;
    }
};
```

:::

<Utterances />
