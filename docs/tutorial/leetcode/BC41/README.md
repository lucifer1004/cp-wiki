# Leetcode 第41场双周赛题解

## Problem A - [统计一致字符串的数目](https://leetcode-cn.com/problems/count-the-number-of-consistent-strings/)

直接模拟即可。

- 时间复杂度$\mathcal{O}(|A|+\sum|W_i|)$。
- 空间复杂度$\mathcal{O}(C)$，$C$为字母表大小，本题中为26。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int ans = 0;
        vector<bool> good(26);
        for (char c : allowed)
            good[c - 'a'] = true;
        for (string &word : words) {
            bool ok = true;
            for (char c : word)
                if (!good[c - 'a']) {
                    ok = false;
                    break;
                }
            if (ok)
                ans++;
        }
        return ans;
    }
};
```

:::

## Problem B - [有序数组中差绝对值之和](https://leetcode-cn.com/problems/sum-of-absolute-differences-in-a-sorted-array/)

抓住原数组**有序**这一条件。首先计算出所有数的和，然后从左向右依次处理，过程中维护左边数的总和和右边数的总和，则可以在$\mathcal{O}(1)$时间内计算出任一位置数与其他所有数的差的绝对值之和。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        int right = 0;
        for (int num : nums)
            right += num;
        int left = 0;
        for (int i = 0; i < n; ++i) {
            right -= nums[i];
            if (i > 0)
                ans[i] += nums[i] * i - left;
            if (i < n - 1)
                ans[i] += right - nums[i] * (n - 1 - i);
            left += nums[i];
        }
        return ans;
    }
};
```

:::

## Problem C - [石子游戏 VI](https://leetcode-cn.com/problems/stone-game-vi/)

我们发现，一枚石子的价值实际上等于$a[i]+b[i]$：

- 对Alice来说，拿走这枚石子，自己得了$a[i]$分，同时Bob少了$b[i]$分，因此等于得了$a[i]+b[i]$分
- 对Bob来说，同理。

因此，我们将石子按照$a[i]+b[i]$降序排列，两个人会按照这个顺序依次取石子。在这一情况下，计算两个人的总得分进行比较即可。

- 时间复杂度$\mathcal{O}(N\log N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int n = aliceValues.size();
        vector<int> order(n);
        for (int i = 0; i < n; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return aliceValues[i] + bobValues[i] > aliceValues[j] + bobValues[j]; 
        });
        int alice = 0, bob = 0;
        for (int i = 0; i < n; ++i) {
            int id = order[i];
            if (i % 2 == 0)
                alice += aliceValues[id];
            else
                bob += bobValues[id];
        }
        if (alice > bob)
            return 1;
        if (alice == bob)
            return 0;
        return -1;
    }
};
```

:::

## Problem D - [从仓库到码头运输箱子](https://leetcode-cn.com/problems/delivering-boxes-from-storage-to-ports/)

### 方法一：线段树

- 前缀和：为了计算一段区间内箱子的总重量，以判断是否超出限制，我们预计算重量的前缀和。
- 动态规划：我们使用$dp[i]$表示以第$i$个箱子为区间结束时的最小成本。
- 线段树：我们在线段树中维护最后一个开放区间起点在$[l,r]$区间内时的最小成本。
- 双指针：我们用双指针来维护当前的开放区间。

首先说明一下“开放区间”的概念：当我们在考虑第$i$个箱子的时候，我们实际上有两种选择。一是以它作为区间的起点；二是将它加入到现有的以$i-1$为右端点，并且能够继续加入箱子的区间中，这样的区间就称为“开放区间”。显然，由于数量和重量的限制，最左侧的开放区间会首先失效（不能再加入箱子），因此可以使用双指针的方法。

代码的主体部分很简单，分为以下步骤：

1. 维护左指针：如果当前左指针到右指针（第$i$个箱子）这段区间不合法，则不断将左指针右移。
2. 计算以当前箱子为结束的最小成本，也即$dp[i]$。
    - 首先，我们可以从$i$开始，到$i$结束，此时的成本为$dp[i-1]+2$。
    - 如果当前左指针在$i$的左侧，也即存在“开放区间”，我们查询线段树上的$[l,i-1]$区间的最小值。
    - $dp[i]$取为二者中较小的那一个值。
3. 更新线段树。
    - 加入以第$i$个箱子为开始的最小成本，对$i$单点赋值为$dp[i-1]+2$。注意区分线段树和动态规划数组的含义！线段树存放的是以$i$开始的成本，而数组中存放的是以$i$结束的成本。
    - 考虑第$i+1$个箱子，如果其与第$i$个箱子的编号不同，则需要对线段树的$[l,i]$区间整体加上1（因为需要进行一次码头间的移动），也即进行一次区间修改。

最后的答案就是$dp[n]$。

代码量主要在线段树部分，我们需要实现两种修改操作：区间修改和单点赋值。这里不具体解释实现过程，感兴趣的可以查阅线段树相关教程。

- 时间复杂度$\mathcal{O}(N\log N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
#define lson (idx << 1)
#define rson (idx << 1 | 1)
#define MAXN 100005

typedef long long ll;
const int INF = 0x3f3f3f3f;

struct Node {
    int l, r, v, lazy;
} s[MAXN << 2];

void calc(int idx) { s[idx].v = min(s[lson].v, s[rson].v); }

void build(int idx, int l, int r) {
    s[idx].l = l, s[idx].r = r, s[idx].v = INF, s[idx].lazy = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
}

void pushdown(int idx) {
    if (s[idx].lazy)
        for (int i = lson; i <= rson; ++i) {
            s[i].v += s[idx].lazy;
            s[i].lazy += s[idx].lazy;
        }
    s[idx].lazy = 0;
}

void setp(int idx, int pos, int x) {
    if (s[idx].l == pos && s[idx].r == pos) {
        s[idx].v = x;
        return;
    }
    pushdown(idx);
    int mid = (s[idx].l + s[idx].r) >> 1;
    if (pos <= mid)
        setp(lson, pos, x);
    else
        setp(rson, pos, x);
    calc(idx);
}

void update(int idx, int l, int r, int x) {
    if (s[idx].l >= l && s[idx].r <= r) {
        s[idx].v += x;
        s[idx].lazy += x;
        return;
    }
    pushdown(idx);
    int mid = (s[idx].l + s[idx].r) >> 1;
    if (mid >= l)
        update(lson, l, r, x);
    if (mid + 1 <= r)
        update(rson, l, r, x);
    calc(idx);
}

int query(int idx, int l, int r) {
    if (s[idx].l >= l && s[idx].r <= r)
        return s[idx].v;
    pushdown(idx);
    int mid = (s[idx].l + s[idx].r) >> 1;
    int ans = INF;
    if (mid >= l)
        ans = min(ans, query(lson, l, r));
    if (mid + 1 <= r)
        ans = min(ans, query(rson, l, r));
    return ans;
}

class Solution {
public:
    int boxDelivering(vector<vector<int>> &boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        if (n == 1)
            return 2;
        vector<ll> w(n + 1);
        for (int i = 1; i <= n; ++i)
            w[i] = w[i - 1] + boxes[i - 1][1];
        build(1, 1, n);
        
        vector<int> dp(n + 1);
        auto valid = [&](int l, int r) {
            return r - l + 1 <= maxBoxes && w[r] - w[l - 1] <= maxWeight;
        };
        int l = 1;
        for (int i = 1; i <= n; ++i) {
            while (l < i && !valid(l, i))
                l++;
            int lo = dp[i - 1] + 2;
            if (l < i)
                lo = min(lo, query(1, l, i - 1));
            dp[i] = lo;
            setp(1, i, dp[i - 1] + 2);
            if (i < n && boxes[i][0] != boxes[i - 1][0])
                update(1, l, i, 1);
        }
        return dp[n];
    }
};
```

:::

### 方法二：优先队列

我们注意到，在方法一中，实际上是在用线段树维护当前所有合法的“开放区间”的最小成本。我们是否可以直接用优先队列（堆）来对这一最小成本进行维护呢？

答案是肯定的。方法一中，我们采用区间修改的办法来维护所有“开放区间”的成本。显然，我们无法接受对所有元素进行修改。但我们可以逆向思考，修改新加入的元素，而非修改原有的元素。

这里，我们用变量$diff$维护全局截止到目前为止相邻箱子属于不同码头的次数，则在将以第$i$个箱子为起点的“开放区间”加入堆中时，我们加入$dp[i-1]+2-diff$；而在考虑“开放区间”时，我们则使用堆的最小值加上$diff$来得到实际的总成本。

- 时间复杂度$\mathcal{O}(N\log N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int boxDelivering(vector<vector<int>> &boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        if (n == 1)
            return 2;
        vector<ll> w(n + 1);
        for (int i = 1; i <= n; ++i)
            w[i] = w[i - 1] + boxes[i - 1][1];
        
        vector<int> dp(n + 1);
        auto valid = [&](int l, int r) {
            return r - l + 1 <= maxBoxes && w[r] - w[l - 1] <= maxWeight;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        int l = 1, diff = 0;
        for (int i = 1; i <= n; ++i) {
            while (l < i && !valid(l, i))
                l++;
            int lo = dp[i - 1] + 2;
            while (!pq.empty() && pq.top().second < l)
                pq.pop();
            if (!pq.empty())
                lo = min(lo, pq.top().first + diff);
            dp[i] = lo;
            pq.emplace(dp[i - 1] + 2 - diff, i);
            if (i < n && boxes[i][0] != boxes[i - 1][0])
                diff++;
        }
        return dp[n];
    }
};
```

:::

### 方法三 单调队列

在方法二的基础上，我们可以进一步用单调队列替换优先队列来维护最小成本，从而将时间复杂度降低到$\mathcal{O}(N)$。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int boxDelivering(vector<vector<int>> &boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        if (n == 1)
            return 2;
        vector<ll> w(n + 1);
        for (int i = 1; i <= n; ++i)
            w[i] = w[i - 1] + boxes[i - 1][1];
        
        vector<int> dp(n + 1);
        auto valid = [&](int l, int r) {
            return r - l + 1 <= maxBoxes && w[r] - w[l - 1] <= maxWeight;
        };
        deque<pair<int, int>> dq;
        int l = 1, diff = 0;
        for (int i = 1; i <= n; ++i) {
            while (l < i && !valid(l, i))
                l++;
            int lo = dp[i - 1] + 2;
            while (!dq.empty() && dq.front().second < l)
                dq.pop_front();
            if (!dq.empty())
                lo = min(lo, dq.front().first + diff);
            dp[i] = lo;
            int cost = dp[i - 1] + 2 - diff;
            while (!dq.empty() && dq.back().first >= cost)
                dq.pop_back();
            dq.emplace_back(cost, i);
            if (i < n && boxes[i][0] != boxes[i - 1][0])
                diff++;
        }
        return dp[n];
    }
};
```

:::

<Utterances />
