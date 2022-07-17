# Leetcode 第82场双周赛题解

## Problem A - [计算布尔二叉树的值](https://leetcode.cn/problems/evaluate-boolean-binary-tree/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(H)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool evaluateTree(TreeNode* root) {
        if (root->left == nullptr)
            return root->val;
        
        bool a = evaluateTree(root->left);
        bool b = evaluateTree(root->right);
        if (root->val == 2)
            return a || b;
        return a && b;
    }
};
```

:::

## Problem B - [坐上公交的最晚时间](https://leetcode.cn/problems/the-latest-time-to-catch-a-bus/)

### 方法一：排序 + 双指针 + 贪心

- 时间复杂度 $\mathcal{O}(N\log N + M\log M)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
// 这题我的代码不够清晰，就用 0x3f 的了。

class Solution {
public:
    int latestTimeCatchTheBus(vector<int> &buses, vector<int> &passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());
        int j = 0, c;
        for (int t: buses)
            for (c = capacity; c && j < passengers.size() && passengers[j] <= t; ++j)
                --c;
        --j;
        int ans = c ? buses.back() : passengers[j]; // 在发车时到达公交站 or 上一个上车的乘客
        while (j >= 0 && passengers[j--] == ans) --ans; // 往前找没人到达的时刻
        return ans;
    }
};

// 作者：endlesscheng
// 链接：https://leetcode.cn/problems/the-latest-time-to-catch-a-bus/solution/pai-xu-by-endlesscheng-h9w9/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

:::

## Problem C - [最小差值平方和](https://leetcode.cn/problems/minimum-sum-of-squared-difference/)

### 方法一：优先队列 + 贪心

- 时间复杂度 $\mathcal{O}(N\log N)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        priority_queue<pair<long long, int>> pq;
        int n = nums1.size();
        for (int i = 0; i < n; ++i)
            pq.emplace(abs(nums1[i] - nums2[i]), 1);
        pq.emplace(0, 0);
        
        int k = k1 + k2;
        while (k > 0 && pq.top().first > 0) {
            auto [v, f] = pq.top();
            pq.pop();
            if (f == 0)
                continue;
            
            if (!pq.empty()) {
                auto [v1, f1] = pq.top();
                pq.pop();
                if (k >= (v - v1) * f) {
                    k -= (v - v1) * f;
                    pq.emplace(v1, f + f1);
                } else {
                    int d = k / f;
                    pq.emplace(v1, f1);
                    pq.emplace(v - d, f - k % f);
                    pq.emplace(v - d - 1, k % f);
                    k = 0;
                }
            }
        }
        
        long long ans = 0;
        while (!pq.empty()) {
            auto [v, f] = pq.top();
            pq.pop();
            ans += v * v * f;
        }
        
        return ans;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
from heapq import heappush, heappop

class Solution:
    def minSumSquareDiff(self, nums1: List[int], nums2: List[int], k1: int, k2: int) -> int:
        pq = []
        n = len(nums1)
        for i in range(n):
            heappush(pq, (-abs(nums1[i] - nums2[i]), 1))
        heappush(pq, (0, 0))
            
        k = k1 + k2
        while k > 0 and len(pq) > 0 and pq[0][0] < 0:
            v, f = heappop(pq)
            v = -v
            if f == 0:
                continue
            
            if len(pq) > 0:
                v1, f1 = heappop(pq)
                v1 = -v1
                if k >= (v - v1) * f:
                    k -= (v - v1) * f
                    heappush(pq, (-v1, f + f1))
                else:
                    d = k // f
                    heappush(pq, (-v1, f1))
                    heappush(pq, (-(v - d), f - k % f))
                    heappush(pq, (-(v - d - 1), k % f))
                    k = 0
        
        ans = 0
        while len(pq) > 0:
            v, f = heappop(pq)
            ans += v * v * f
        
        return ans
```

:::

## Problem D - [元素值大于变化阈值的子数组](https://leetcode.cn/problems/subarray-with-elements-greater-than-varying-threshold/)

### 方法一：排序 + 并查集

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
struct UnionFind {
    int n;
    vector<int> parent, size;

    UnionFind(int n) {
        this->n = n;
        parent = vector<int>(n);
        size = vector<int>(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int idx) {
        if (parent[idx] == idx)
            return idx;
        return parent[idx] = find(parent[idx]);
    }

    void connect(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa != fb) {
            if (size[fa] > size[fb]) {
                parent[fb] = fa;
                size[fa] += size[fb];
            } else {
                parent[fa] = fb;
                size[fb] += size[fa];
            }
        }
    }
};

class Solution {
public:
    int validSubarraySize(vector<int> &nums, int threshold) {
        int n = nums.size();
        vector<int> order(n);
        for (int i = 0; i < n; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j) {
            return nums[i] > nums[j];
        });

        int ptr = 0;
        UnionFind uf(n);
        for (int i = 1; i <= n; ++i) {
            int now = threshold / i + 1;
            while (ptr < n && nums[order[ptr]] >= now) {
                int k = order[ptr];
                if (k > 0 && nums[k - 1] >= now)
                    uf.connect(k - 1, k);
                if (k + 1 < n && nums[k + 1] >= now)
                    uf.connect(k, k + 1);
                if (uf.size[uf.find(k)] >= i)
                    return i;
                ptr++;
            }
        }

        return -1;
    }
};
```

:::

<Utterances />
