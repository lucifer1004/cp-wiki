# Leetcode 第76场双周赛题解

## Problem A - [找到最接近 0 的数字](https://leetcode.cn/problems/find-closest-number-to-zero/)

### 方法一：枚举

枚举答案即可。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findClosestNumber(self, nums: List[int]) -> int:
        return min(nums, key = lambda x: (abs(x), -x))
```

:::

## Problem B - [买钢笔和铅笔的方案数](https://leetcode.cn/problems/number-of-ways-to-buy-pens-and-pencils/)

### 方法一：枚举

枚举较贵的商品的购买件数。

- 时间复杂度 $\mathcal{O}(\frac{N}{\max(C_1,C_2)})$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python）

```python
class Solution:
    def waysToBuyPensPencils(self, total: int, cost1: int, cost2: int) -> int:
        if cost1 < cost2:
            cost1, cost2 = cost2, cost1
        return sum((total - pen * cost1) // cost2 + 1 for pen in range(total // cost1 + 1))
```

:::

## Problem C - [设计一个 ATM 机器](https://leetcode.cn/problems/design-an-atm-machine/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(1)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
prices = [20, 50, 100, 200, 500]

class ATM:

    def __init__(self):
        self.v = [0] * 5


    def deposit(self, banknotesCount: List[int]) -> None:
        for i in range(5):
            self.v[i] += banknotesCount[i]


    def withdraw(self, amount: int) -> List[int]:
        u = [0] * 5
        for i in range(4, -1, -1):
            u[i] = min(amount // prices[i], self.v[i])
            amount -= u[i] * prices[i]
            
        if amount != 0:
            return [-1]
        for i in range(5):
            self.v[i] -= u[i]
        return u
```

:::

## Problem D - [节点序列的最大得分](https://leetcode.cn/problems/maximum-score-of-a-node-sequence/)

### 方法一：枚举

记录每个点得分前三高的邻居，然后枚举路径的中间一条边并向两侧扩展。这里记录前三高是因为要去掉中间一条边上的两个点，以及扩展到同一个点的情形。

复杂度：

- 时间复杂度 $\mathcal{O}(V+E)$。
- 空间复杂度 $\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
class Solution {
    int n;
    vector<int> s;
    vector<vector<int>> adj;

public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        n = scores.size();
        s = scores;
        adj = vector<vector<int>>(n);
        vector<priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>> nei_pq(n);
        int ans = -1;
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            nei_pq[u].emplace(scores[v], v);
            nei_pq[v].emplace(scores[u], u);
            if (nei_pq[u].size() > 3)
                nei_pq[u].pop();
            if (nei_pq[v].size() > 3)
                nei_pq[v].pop();
        }
        vector<vector<pair<int, int>>> nei(n);
        for (int i = 0; i < n; ++i)
            while (!nei_pq[i].empty()) {
                nei[i].push_back(nei_pq[i].top());
                nei_pq[i].pop();
            }

        for (auto& e : edges) {
            int u = e[0], v = e[1];
            for (auto [_, r] : nei[u]) {
                if (r == u || r == v)
                    continue;
                for (auto [_, t] : nei[v]) {
                    if (t == u || t == v || t == r)
                        continue;
                    ans = max(ans, scores[u] + scores[v] + scores[r] + scores[t]);
                }
            }
        }

        return ans;
    }
};
```

:::

<Utterances />
