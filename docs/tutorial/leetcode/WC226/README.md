# Leetcode 第226场周赛题解

## Problem A - [盒子中小球的最大数量](https://leetcode.cn/problems/maximum-number-of-balls-in-a-box/)

因为数据范围比较小，所以暴力枚举即可。

- 时间复杂度$\mathcal{O}((H-L)\log H)$。
- 空间复杂度$\mathcal{O}(\log H)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countBalls(self, lowLimit: int, highLimit: int) -> int:
        cnt = collections.Counter()
        for i in range(lowLimit, highLimit + 1):
            cnt[sum(map(int, list(str(i))))] += 1
        return max(cnt.values())
```

:::

### 思考

如果数据范围达到$10^{18}$呢？

::: details 提示
可以采用数位DP的方法，具体可以参考[@Heltion](https://leetcode.cn/u/heltion/)的[题解](https://leetcode.cn/problems/maximum-number-of-balls-in-a-box/solution/shu-wei-dpzuo-fa-by-heltion-5wvg/)。
:::

## Problem B - [从相邻元素对还原数组](https://leetcode.cn/problems/restore-the-array-from-adjacent-pairs/)

因为所有数字都不同，所以首尾两个数字只会出现一次，而其他每个数字会出现两次。

因此，我们从任意一个只出现一次的数字开始，用类似拓扑排序的方法就可以还原出整个数组。当然，我们还原出的也可能是原数组的倒序，因为我们并不知道哪一个是头，哪一个是尾。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int>> adj;
        unordered_map<int, int> in_deg;
        for (auto &v : adjacentPairs) {
            adj[v[0]].emplace_back(v[1]);
            adj[v[1]].emplace_back(v[0]);
            in_deg[v[0]]++;
            in_deg[v[1]]++;
        }
        int start;
        for (auto [num, deg] : in_deg) {
            if (deg == 1) {
                start = num;
                break;
            }
        }
        queue<int> q;
        q.emplace(start);
        vector<int> ans;
        unordered_set<int> vis;
        vis.emplace(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ans.emplace_back(u);
            for (int v : adj[u]) {
                if (!vis.count(v)) {
                    vis.emplace(v);
                    q.emplace(v);
                }
            }
        }
        return ans;
    }
};
```

:::

### 思考

如果原数组中存在相同的元素呢？

## Problem C - [你能在你最喜欢的那天吃到你最喜欢的糖果吗？](https://leetcode.cn/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/)

这题题意有些绕人，但只要理解清楚，实现起来还是比较简单的（需要注意一些细节）。

规则二限制了我们必须按顺序吃糖果，同时，因为同一天可以吃不同类型的糖果，所以我们只要预处理计算出糖果数目的前缀和即可。

对于每一个询问，我们考虑两种极端情况：

- 每天按照上限$dailyCap_i$去吃，也无法把$favoriteType_i$之前的所有糖果吃完（包括刚好吃完的情形，因为我们还需要至少吃一个$favoriteType_i$类型的糖果）。
- 每天按照下限$1$去吃，也会在$favoriteDay_i$之前把$favoriteType_i$及之前的所有糖果吃完。

这两种情况是无解的，剩下都是有解的情况。

- 时间复杂度$\mathcal{O}(N+Q)$，其中$N$是糖果的种数，$Q$是询问的个数。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        int q = queries.size(), n = candiesCount.size();
        vector<bool> ans(q);
        vector<ll> pre(n + 1);
        for (int i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] + candiesCount[i - 1];
        for (int i = 0; i < q; ++i) {
            int t = queries[i][0], d = queries[i][1], c = queries[i][2];
            ll before = pre[t];
            
            // Cannot eat type t even if we eat c candies every day.
            if (1LL * c * (d + 1) <= before)
                continue;
            
            // Type t has been eaten out before day d.
            if (d >= pre[t + 1])
                continue;
            
            ans[i] = true;
        }
        return ans;
    }
};
```

:::

### 思考

如果再增加一条规则：每天只能吃同一种类型的糖果，应该如何解题呢？

## Problem D - [回文串分割 IV](https://leetcode.cn/problems/palindrome-partitioning-iv/)

本题的数据范围较小，$\mathcal{O}(N^2)$的复杂度就足够通过。因此，我们只需要：

- 用简单的中心扩展法以$\mathcal{O}(N^2)$的时间复杂度找出所有回文串。这里用Manacher可以将时间复杂度降到$\mathcal{O}(N)$，但并没有必要。
- 枚举第一段和第二段的结束位置，检查是否能分成三个回文串，同样是$\mathcal{O}(N^2)$的时间复杂度。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        vector<vector<bool>> palin(n, vector<bool>(n));
        for (int i = 0; i < n; ++i) {
            int l = i, r = i;
            while (l >= 0 && r < n && s[l] == s[r]) {
                palin[l][r] = true;
                l--;
                r++;
            }
            l = i, r = i + 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                palin[l][r] = true;
                l--;
                r++;
            }
        }
        for (int i = 0; i + 2 < n; ++i)
            for (int j = i + 1; j + 1 < n; ++j) {
                if (palin[0][i] && palin[i + 1][j] && palin[j + 1][n - 1])
                    return true;
            }
        return false;
    }
};
```

:::

### 思考

如果题目改成：能否分成$k$（$k\leq10$）个回文子串呢？

<Utterances />
