# Leetcode 第233场周赛题解

## Problem A - [最大升序子数组和](https://leetcode-cn.com/problems/maximum-ascending-subarray-sum/)

双指针找出每一个升序子数组即可。暴力$\mathcal{O}(N^2)$亦可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxAscendingSum(self, nums: List[int]) -> int:
        ans = 0
        n = len(nums)
        p = 0
        while p < n:
            last = 0
            s = 0
            q = p
            while q < n and nums[q] > last:
                s += nums[q]
                last = nums[q]
                q += 1
            p = q
            ans = max(ans, s)
        return ans
```

:::

## Problem B - [积压订单中的订单总数](https://leetcode-cn.com/problems/number-of-orders-in-the-backlog/)

小根堆存放积压的销售订单，大根堆存放积压的购买订单。按题意模拟即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        priority_queue<pair<int, ll>> buy;
        priority_queue<pair<int, ll>, vector<pair<int, ll>>, greater<>> sell;
        for (auto &order : orders) {
            int price = order[0];
            ll amount = order[1];
            int t = order[2];
            if (t == 0) { // Buy
                while (amount > 0 && !sell.empty() && sell.top().first <= price) {
                    ll lo = min(amount, sell.top().second);
                    amount -= lo;
                    ll rem = sell.top().second - lo;
                    int p = sell.top().first;
                    sell.pop();
                    if (rem) {
                        sell.emplace(p, rem);
                    }
                }
                if (amount)
                    buy.emplace(price, amount);
            } else { // Sell
                while (amount > 0 && !buy.empty() && buy.top().first >= price) {
                    ll lo = min(amount, buy.top().second);
                    amount -= lo;
                    ll rem = buy.top().second - lo;
                    int p = buy.top().first;
                    buy.pop();
                    if (rem) {
                        buy.emplace(p, rem);
                    }
                }
                if (amount)
                    sell.emplace(price, amount);
            }
        }
        ll ans = 0;
        while (!buy.empty()) {
            ans += buy.top().second;
            buy.pop();
        }
        while (!sell.empty()) {
            ans += sell.top().second;
            sell.pop();
        }
        return ans % MOD;
    }
};
```

:::

## Problem C - [有界数组中指定下标处的最大值](https://leetcode-cn.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/)

在确定了$index$处的数值后，我们可以找到可能的最小总和：也即向左递减直到$1$，向右递减直到$1$的情况下的总和。如果这一最小总和不超过$M$（最大总和），那么我们就找到了一个可行解。

据此，我们可以二分答案求解。

- 时间复杂度$\mathcal{O}(\log M)$。其中$M$为最大总和。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;

ll calc_min(ll len, ll hi) {
    if (len >= hi)
        return hi * (hi + 1) / 2 + (len - hi);
    return (hi + hi - len + 1) * len / 2;
}

class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        int left = index, right = n - index - 1;
        int lo = 1, hi = maxSum - (n - 1);
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            ll lmin = calc_min(left, mid - 1);
            ll rmin = calc_min(right, mid - 1);
            if (lmin + rmin + mid > maxSum)
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        return hi;
    }
};
```

:::

## Problem D - [统计异或值在范围内的数对有多少](https://leetcode-cn.com/problems/count-pairs-with-xor-in-a-range/)

首先，$[L,R]$范围内的计数问题，可以转化为$[0,R]$和$[0,L-1]$的计数问题。

接下来，考虑$[0,H]$的问题如何进行求解。参考[LC1707 -  与数组中元素的最大异或值](https://leetcode-cn.com/problems/maximum-xor-with-an-element-from-array/)等几道题，对于这种数组异或计数的问题，0-1字典树是一个很有效的解决方案。本题中，我们同样可以使用0-1字典树进行求解。

1. 构造字典树。注意要在每个节点处记录当前节点为根节点的子树中包含数组元素的总个数。
2. 遍历数组中的元素。对于每一个元素，在字典树中从最高位开始进行一次DFS（具体实现可参考代码）。
    - 如果走使得当前位异或值为$1$的分支，则要求之后最小值小于等于$H$。
    - 如果走使得当前为异或值为$0$的分支，且之后的最大值也小于等于$H$，则可以不进行DFS，直接利用节点上的计数。

最后，因为题目要求的是$i<j$的数对，而我们统计时没有区分先后关系，所以结果要除以$2$。这里有一个细节，对于$(i,i)$，也即与自身异或的这种情况，因为异或值一定为$0$，所以无论上界是多少，计数时总是会计入这种情况，那么在做减法的时候，就自然消去了。

::: details 参考代码（C++）

```cpp
struct TrieNode {
    int val, cnt = 0;
    TrieNode *son[2]{};
};

class Solution {
    vector<int> nums;
    TrieNode *root;
    
    int dfs(TrieNode *p, int now, int num, int k, int hi) {
        int flag = (num & (1 << k)) ? 1 : 0;
        int ans = 0;
        if (p->son[flag]) {
            if ((now ^ (1 << k)) - 1 <= hi) {
                ans += p->son[flag]->cnt;
            } else {
                ans += dfs(p->son[flag], now, num, k - 1, hi);
            }
        }
        if ((now ^ (1 << k)) <= hi) {
            if (p->son[1 - flag])
                ans += dfs(p->son[1 - flag], now ^ (1 << k), num, k - 1, hi);
        }
        return ans;
    }
    
    int count(int hi) {
        int ans = 0;
        TrieNode *p = root;
        for (int num : nums) {
            ans += dfs(p, 0, num, 15, hi);
        }
        return ans;
    }
public:
    int countPairs(vector<int>& nums, int low, int high) {
        this->nums = nums;
        root = new TrieNode();
        
        for (int num : nums) {
            TrieNode *p = root;
            for (int k = 15; k >= 0; --k) {
                int flag = (num & (1 << k)) ? 1 : 0;
                if (!p->son[flag]) {
                    p->son[flag] = new TrieNode();
                }
                p = p->son[flag];
                p->cnt++;
            }
        }
        
        return (count(high) - count(low - 1)) / 2;
    }
};
```

:::

<Utterances />
