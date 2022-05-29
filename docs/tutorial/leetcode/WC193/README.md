# Leetcode 第193场周赛题解

## Problem A - [一维数组的动态和](https://leetcode.cn/problems/running-sum-of-1d-array/)

就是前缀和。直接递推计算即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> ans = {nums[0]};
        for (int i = 1; i < nums.size(); ++i)
            ans.emplace_back(ans.back() + nums[i]);
        return ans;
    }
};
```

:::

## Problem B - [不同整数的最少数目](https://leetcode.cn/problems/least-number-of-unique-integers-after-k-removals/)

贪心去除数量最少的整数，直到用完删除次数。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> cnt;
        for (int i : arr)
            cnt[i]++;
        vector<int> c;
        for (auto p : cnt)
            c.emplace_back(p.second);
        sort(c.begin(), c.end());
        int t = c.size();
        int sum = 0;
        for (int i = 0; i < t; ++i) {
            sum += c[i];
            if (sum > k)
                return t - i;
        }
        return 0;
    }
};
```

:::

## Problem C - [制作 m 束花所需的最少天数](https://leetcode.cn/problems/minimum-number-of-days-to-make-m-bouquets/)

二分答案。检查第$mid$天能够制作多少束花。

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if (n / k < m)
            return -1;
        int l = 1, r = 1e9;
        auto check = [&](int x) {
            vector<bool> flower(n);
            for (int i = 0; i < n; ++i)
                if (bloomDay[i] <= x)
                    flower[i] = true;
            int bunch = 0, curr = 0;
            for (int i = 0; i < n; ++i) {
                if (flower[i])
                    curr++;
                else {
                    bunch += curr / k;
                    curr = 0;
                }
            }
            bunch += curr / k;
            return bunch;
        };
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid) < m)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }
};
```

:::

## Problem D - [树节点的第 K 个祖先](https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/)

倍增法求LCA（最近公共祖先）中的基础步骤。

::: details 参考代码（C++）

```cpp
class TreeAncestor {
    vector<vector<int>> p;
public:
    TreeAncestor(int n, vector<int>& parent) {
        p = vector<vector<int>>(n, vector<int>(18, -1));
        for (int i = 0; i < n; ++i)
            p[i][0] = parent[i];
        for (int k = 1; k < 18; ++k)
            for (int i = 0; i < n; ++i) {
                if (p[i][k - 1] == -1)
                    continue;
                p[i][k] = p[p[i][k - 1]][k - 1];
            }
    }
    
    int getKthAncestor(int node, int k) {
        for (int i = 17; i >= 0; --i)
            if (k & (1 << i)) {
                node = p[node][i];
                if (node == -1)
                    break;
            }
        return node;
    }
};
```

:::

<Utterances />
