# Leetcode 第231场周赛题解

## Problem A - [检查二进制字符串字段](https://leetcode.cn/problems/check-if-binary-string-has-at-most-one-segment-of-ones/)

一次遍历即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool checkOnesSegment(string s) {
        int ans = 0;
        char last = '0';
        for (char c : s) {
            if (c == '1' && last == '0') {
                ans++;
            }
            last = c;
        }
        return ans <= 1;
    }
};
```

:::

## Problem B - [构成特定和需要添加的最少元素](https://leetcode.cn/problems/minimum-elements-to-add-to-form-a-given-sum/)

计算出差值的绝对值$\Delta=|goal-\sum nums|$，则最后的答案为$\left\lceil\frac{\Delta}{limit}\right\rceil$。实际实现时需要注意除法中包含负数时的结果可能与预期不符，最好的办法是单独处理$\Delta=0$的情形。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        ll sum = 0;
        for (int num : nums)
            sum += num;
        ll delta = abs(sum - goal);
        if (delta == 0)
            return 0;
        return (delta - 1) / limit + 1;
    }
};
```

:::

## Problem C - [从第一个节点出发到最后一个节点的受限路径数](https://leetcode.cn/problems/number-of-restricted-paths-from-first-to-last-node/)

从$N$开始跑一次单源Dijkstra，之后按照$dist$升序进行动态规划求解。

- 时间复杂度$\mathcal{O}(E\log V)$。
- 空间复杂度$\mathcal{O}(E+V)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], d = edge[2];
            adj[u].emplace_back(v, d);
            adj[v].emplace_back(u, d);
        }
        vector<int> dist(n + 1, INT_MAX);
        dist[n] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, n);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u])
                continue;
            for (auto [v, c] : adj[u]) {
                if (d + c < dist[v]) {
                    dist[v] = d + c;
                    pq.emplace(dist[v], v);
                }
            }
        }
        vector<int> order(n);
        for (int i = 0; i < n; ++i)
            order[i] = i + 1;
        sort(order.begin(), order.end(), [&](int u, int v) {
            return dist[u] < dist[v]; 
        });
        vector<ll> ans(n + 1);
        ans[n] = 1;
        for (int u : order) {
            for (auto [v, c] : adj[u]) {
                if (dist[v] > dist[u]) {
                    ans[v] = (ans[v] + ans[u]) % MOD;
                }
            }
        }
        return ans[1];
    }
};
```

:::

## Problem D - [使所有区间的异或结果为零](https://leetcode.cn/contest/weekly-contest-231/problems/make-the-xor-of-all-segments-equal-to-zero/)

容易发现，最后得到的数组一定满足：

- $a_1=a_{k+1}=a_{2k+1}=\dots$
- $a_2=a_{k+2}=a_{2k+2}=\dots$
- $\dots$

因此可以考虑将同一组中的数放在一起进行考虑。

首先，我们对每一组分别进行计数。

接下来，我们用动态规划求解。$dp[val]$表示处理到当前组时，异或值为$val$的最小修改次数。显然初值（考虑第一组之前）为：

- $dp[0]=0$
- $dp[val]=\infty\ (val\neq0)$

在转移时，我们有两种选择：

1. 将当前组的数全都改为同一个值，此时不管我们之前如何选择，都可以利用这一个值的选择得到任何一个异或值，那么我们自然应该选择之前的代价中最小的那个，此时的代价为$size[i]+\min{dp[val]}$，新状态的异或值可以为$[0,2^D)$中的任意一个值。这一转移需要进行$K$次。
2. 使用当前组中的某一个值$val'$。此时我们需要枚举之前的异或值$val$（或枚举达到的目标值，二者是等价的），此时的代价为$size[i]-cnt[i][val']+dp[val]$，新状态的异或值为$val\oplus val'$。这一转移最多需要进行$N$次。

- 时间复杂度$\mathcal{O}(2^D\cdot(K+N))$。其中$D=10$。
- 空间复杂度$\mathcal{O}(N + 2^D)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        vector<unordered_map<int, int>> groups(k);
        vector<int> size(k);
        for (int i = 0; i < k; ++i) {
            for (int j = i; j < n; j += k) {
                groups[i][nums[j]]++;
                size[i]++;
            }
        }
        
        vector<int> dp(1 << 10, INF);
        dp[0] = 0;
        for (int i = 0; i < k; ++i) {
            int lo = *min_element(dp.begin(), dp.end());
            vector<int> ndp(1 << 10, lo + size[i]);
            for (int j = 0; j < (1 << 10); ++j) {
                if (dp[j] == INF)
                    continue;
                for (auto [p, freq] : groups[i]) {
                    int nxt = p ^ j;
                    ndp[nxt] = min(ndp[nxt], dp[j] + size[i] - freq);
                }
            }
            dp = move(ndp);
        }
        
        return dp[0];
    }
};
```

:::

<Utterances />
