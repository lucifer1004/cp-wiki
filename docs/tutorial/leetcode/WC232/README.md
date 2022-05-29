# Leetcode 第232场周赛题解

## Problem A - [仅执行一次字符串交换能否使两个字符串相等](https://leetcode.cn/problems/check-if-one-string-swap-can-make-strings-equal/)

一次遍历即可。统计出所有不同的位置：

- 如果全都相同：可以将任意位置的字符与其自身进行一次交换。
- 如果只有一处不同，或超过两处不同：无法通过一次交换使两个字符串相等。
- 如果恰好有两处不同：检查交换这个两个位置是否能使这两个字符串相等。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        vector<int> diff;
        for (int i = 0; i < s1.size(); ++i)
            if (s1[i] != s2[i]) {
                diff.emplace_back(i);
                if (diff.size() > 2)
                    return false;
            }
        if (diff.empty())
            return true;
        if (diff.size() != 2)
            return false;
        return s1[diff[0]] == s2[diff[1]] && s1[diff[1]] == s2[diff[0]];
    }
};
```

:::

## Problem B - [找出星型图的中心节点](https://leetcode.cn/problems/find-center-of-star-graph/)

因为$N\geq3$，所以星型图中有且只有中心节点的度数大于$1$，因此只要统计节点的度数即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        unordered_map<int, int> cnt;
        for (auto &edge : edges) {
            cnt[edge[0]]++;
            if (cnt[edge[0]] > 1)
                return edge[0];
            cnt[edge[1]]++;
            if (cnt[edge[1]] > 1)
                return edge[1];
        }
        return 0;
    }
};
```

:::

## Problem C - [最大平均通过率](https://leetcode.cn/problems/maximum-average-pass-ratio/)

在大根堆中存储每个班级中增加一个通过学生后通过率的提升量，每次贪心地将学生安排到通过率提升最大的班级中即可。

- 时间复杂度$\mathcal{O}(M\log N)$。其中$N$为班级数量，$M$为额外的学生数量。
- 空间复杂度$\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        vector<int> total(n), pass(n);
        for (int i = 0; i < n; ++i)
            pass[i] = classes[i][0], total[i] = classes[i][1];
        
        auto calc = [&](int idx) {
            double original = (double) pass[idx] / (double) total[idx];
            double update = (double) (pass[idx] + 1) / (double) (total[idx] + 1);  
            return update - original;
        };
        
        priority_queue<pair<double, int>> pq;
        for (int i = 0; i < n; ++i) {
            pq.emplace(calc(i), i);
        }
        
        while (extraStudents) {
            extraStudents--;
            auto [delta, idx] = pq.top();
            pq.pop();
            pass[idx]++;
            total[idx]++;
            pq.emplace(calc(idx), idx);
        }
        
        double sum = 0.0;
        for (int i = 0; i < n; ++i)
            sum += (double) pass[i] / (double) total[i];
        
        return sum / n;
    }
};
```

:::

## Problem D - [好子数组的最大分数](https://leetcode.cn/problems/maximum-score-of-a-good-subarray/)

使用单调栈：

- 从左到右遍历，找到每个数右边第一个比它小的数的位置；
- 从右到左遍历，找到每个数左边第一个比它小的数的位置。

利用这两个值，可以得到以某一个数为最小值的最大区间范围。检查所有包含了$k$位置的区间，就可以得到所要求的的最大分数。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> left(n, -1), right(n, n);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] > nums[i]) {
                right[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && nums[st.top()] > nums[i]) {
                left[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int l = left[i] + 1, r = right[i] - 1;
            if (l <= k && r >= k)
                ans = max(ans, (r - l + 1) * nums[i]);
        }
        return ans;
    }
};
```

:::

<Utterances />
