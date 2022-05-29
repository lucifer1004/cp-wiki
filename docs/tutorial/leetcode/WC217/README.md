# Leetcode 第217场周赛题解

## Problem A - [最富有客户的资产总量](https://leetcode.cn/problems/richest-customer-wealth/)

没啥可说的，Python大法好。

时间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumWealth(self, accounts: List[List[int]]) -> int:
        return max([sum(l) for l in accounts])
```

:::

## Problem B - [找出最具竞争力的子序列](https://leetcode.cn/problems/find-the-most-competitive-subsequence/)

贪心。每次找出$[L,N-K+M]$范围内的最小值（右端点的选取是为了保证剩下的数字够用），将其加入子序列，并更新$L$为其下一个位置。初始状态$L=0$。

### 方法一 稀疏表

我们可以使用稀疏表来进行区间最小值查询。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码（C++，稀疏表）

```cpp
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        int d = int(log2(n));
        vector<vector<int>> lo(n, vector<int>(d + 1));
        for (int i = 0; i < n; ++i)
            lo[i][0] = i;
        for (int k = 1; k <= d; ++k)
            for (int i = 0; i < n; ++i) {
                lo[i][k] = lo[i][k - 1];
                int r = i + (1 << (k - 1));
                if (r < n && nums[lo[r][k - 1]] < nums[lo[i][k]])
                    lo[i][k] = lo[r][k - 1];
            }
        auto query = [&](int l, int r) {
            int k = log2(r - l + 1);
            int L = lo[l][k], R = lo[r - (1 << k) + 1][k];
            if (nums[L] <= nums[R])
                return L;
            return R;
        };
        vector<int> ans;
        int L = 0, m = 0;
        while (m < k) {
            int idx = query(L, n - k + m);
            ans.emplace_back(nums[idx]);
            L = idx + 1;
            m++;
        }
        return ans;
    }
};
```

:::

### 方法二 优先队列

因为区间是不断向右移动的，所以可以通过维护优先队列来求出当前的最小值。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++，优先队列）

```cpp
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (int i = 0; i < n - k + 1; ++i)
            pq.emplace(nums[i], i);
        vector<int> ans;
        int l = 0;
        for (int i = 0; i < k; ++i) {
            while (pq.top().second < l)
                pq.pop();
            auto [num, idx] = pq.top();
            pq.pop();
            l = idx + 1;
            ans.emplace_back(num);
            if (i < k - 1)
                pq.emplace(nums[n - k + i + 1], n - k + i + 1);
        }
        return ans;
    }
};
```

:::

### 方法三 单调队列

我们可以将方法二中使用的优先队列改为单调队列，从而进一步优化时间复杂度。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++，单调队列）

```cpp
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq;
        for (int i = 0; i < n - k + 1; ++i) {
            while (!dq.empty() && nums[dq.back()] > nums[i]) 
                dq.pop_back();
            dq.push_back(i);
        }
        vector<int> ans;
        int l = 0;
        for (int i = 0; i < k; ++i) {
            while (dq.front() < l)
                dq.pop_front();
            int idx = dq.front();
            int num = nums[idx];
            dq.pop_front();
            l = idx + 1;
            ans.emplace_back(num);
            if (i < k - 1) {
                while (!dq.empty() && nums[dq.back()] > nums[n - k + 1 + i])
                    dq.pop_back();
                dq.push_back(n - k + 1 + i);
            }
        }
        return ans;
    }
};
```

:::

## Problem C - [使数组互补的最少操作次数](https://leetcode.cn/problems/minimum-moves-to-make-array-complementary/)

我们考虑任意一个数对$(a,b)$，不妨假设$a\leq b$。假设最终选定的和值为$target$，则我们可以发现，对于$(a,b)$这个数对：

- 当$target<1+a$时，需要操作两次；
- 当$1+a\leq target<a+b$时，需要操作一次；
- 当$target=a+b$时，不需要操作；
- 当$a+b<target\leq b+limit$时，需要操作一次；
- 当$target>b+limit$时，需要操作两次。

我们设初始操作次数为两次。令$target$从数轴最左端开始向右移动，我们会发现：

- 在$1+a$处，操作次数减少一次；
- 在$a+b$处，操作次数减少一次；
- 在$a+b+1$处，操作次数增加一次；
- 在$b+limit+1$处，操作次数增加一次。

因此，我们可以遍历数组中的所有数对，求出每个数对的这四个关键位置，然后更新差分数组。最后，我们遍历（扫描）差分数组，就可以找到令总操作次数最小的$target$，同时可以得到最少的操作次数。

- 时间复杂度$\mathcal{O}(N+L)$。
- 空间复杂度$\mathcal{O}(L)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> delta(limit * 2 + 2);
        for (int i = 0; i < n / 2; ++i) {
            int lo = 1 + min(nums[i], nums[n - i - 1]);
            int hi = limit + max(nums[i], nums[n - i - 1]);
            int sum = nums[i] + nums[n - i - 1];
            delta[lo]--;
            delta[sum]--;
            delta[sum + 1]++;
            delta[hi + 1]++;
        }
        int now = n;
        int ans = n;
        for (int i = 2; i <= limit * 2; ++i) {
            now += delta[i];
            ans = min(ans, now);
        }
        return ans;
    }
};
```

:::

## Problem D - [数组的最小偏移量](https://leetcode.cn/problems/minimize-deviation-in-array/)

我们可以首先将所有数字都通过反复除以$2$变为奇数，然后将这些数都放入一个`set`中（同时记录下编号以便查询原始值）。为了减小偏移量，我们每次贪心地对最小的元素进行乘$2$的操作，直到不能再继续进行下去为止（最小的元素已经是偶数，并且等于其原始值）。这个过程中，`set`中最大元素和最小元素的最小差值就是我们要求的答案。

- 时间复杂度$\mathcal{O}(\sum(\log a_i)\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        int n = nums.size();
        set<pair<int, int>> ms;
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            while (num % 2 == 0)
                num >>= 1;
            ms.emplace(num, i);
        }
        int ans = ms.rbegin()->first - ms.begin()->first;
        while (ms.begin()->first < nums[ms.begin()->second] || ms.begin()->first % 2 == 1) {
            auto [num, idx] = *ms.begin();
            ms.erase(ms.begin());
            ms.emplace(num << 1, idx);
            ans = min(ans, ms.rbegin()->first - ms.begin()->first);
        }
        return ans;
    }
};
```

:::

<Utterances />
