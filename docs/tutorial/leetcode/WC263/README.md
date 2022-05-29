# Leetcode 第263场周赛题解

## Problem A - [检查句子中的数字是否递增](https://leetcode.cn/problems/check-if-numbers-are-ascending-in-a-sentence/)

### 方法一：模拟

直接模拟即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def areNumbersAscending(self, s: str) -> bool:
        nums = list(map(int, filter(lambda x: x.isnumeric(), s.split())))
        return all([pre < nxt for pre, nxt in zip(nums[:-1], nums[1:])])
```

:::

## Problem B - [简易银行系统](https://leetcode.cn/problems/simple-bank-system/)

### 方法一：模拟

直接按要求模拟即可。

- 除初始化外，各操作的时间复杂度均为$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Bank {
    int n;
    vector<long long> balance;
    
    bool is_valid_account(int account) {
        return account >= 1 && account <= n;
    }
public:
    Bank(vector<long long>& balance): balance(balance), n(balance.size()) {}
    
    bool transfer(int account1, int account2, long long money) {
        if (!is_valid_account(account1) || !is_valid_account(account2)) return false;
        
        if (balance[account1 - 1] >= money) {
            balance[account1 - 1] -= money;
            balance[account2 - 1] += money;
            return true;
        }
        
        return false;
    }
    
    bool deposit(int account, long long money) {
        if (!is_valid_account(account)) return false;
        balance[account - 1] += money;
        return true;
    }
    
    bool withdraw(int account, long long money) {
        if (!is_valid_account(account)) return false;
        if (balance[account - 1] < money)
            return false;
        balance[account - 1] -= money;
        return true;
    }
};
```

:::

## Problem C - [统计按位或能得到最大值的子集数目](https://leetcode.cn/problems/count-number-of-maximum-bitwise-or-subsets/)

### 方法一：暴力

注意到数据范围很小，暴力枚举即可。

- 时间复杂度$\mathcal{O}(N\cdot2^N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int hi = 0, cnt = 0, n = nums.size();
        for (int i = 1; i < (1 << n); ++i) {
            int res = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j))
                    res |= nums[j];
            }
            if (res > hi) {
                hi = res;
                cnt = 0;
            }
            if (res == hi)
                cnt++;
        }
        return cnt;
    }
};
```

:::

## Problem D - [到达目的地的第二短时间](https://leetcode.cn/problems/second-minimum-time-to-reach-destination/)

### 方法一：BFS + 二次松弛

注意到$time$和$change$都是全局统一的，我们到达一个点的时间，实际上是由经过的边数唯一确定的。

现在假设到达点$n$最短需要经过$k$条边，则我们可以知道，经过$k+2$条边一定可以到达$n$——只需要随意去一个相邻点再回头即可。题目要求第二短时间，这就说明我们只需要考虑是否能经过$k+1$条边到达点$n$即可。

解决方法是，在BFS时允许对每个点进行两次松弛，也即，在第一次到达这个点（假设经过的距离为$d$），以及第一次经过距离$d+1$到达这个点时，都对这个点进行松弛。

最后，如果我们可以经过$k+1$条边到达点$n$，最短时间就是行动$k+1$次的总时间；否则，最短时间就是行动$k+2$次的总时间。因为每个点最多入队两次，所以时间复杂度和标准的BFS一样，还是线性的。

- 时间复杂度$\mathcal{O}(V+E)$。
- 空间复杂度$\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> adj(n);
        for (auto &edge : edges) {
            int u = edge[0] - 1, v = edge[1] - 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        queue<int> q;
        vector<int> d(n, INF);
        vector<bool> can(n);
        d[0] = 0;
        q.emplace(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (d[u] + 1 < d[v]) {
                    d[v] = d[u] + 1;
                    q.emplace(v);
                } else if (d[u] == d[v] || (can[u] && d[u] <= d[v])) {
                    if (!can[v])
                        q.emplace(v);
                    can[v] = true;
                }
            }
        }
        
        int dist = d[n - 1] + 2;
        if (can[n - 1]) 
            dist--;
        
        int t = 0;
        while (dist--) {
            t += time;
            if (dist > 0 && t % (2 * change) >= change)
                t = (t / (2 * change) + 1) * 2 * change;
        }
        
        return t;
    }
};
```

:::

<Utterances />
