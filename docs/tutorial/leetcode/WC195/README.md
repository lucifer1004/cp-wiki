# Leetcode 第195场周赛题解

## Problem A - [判断路径是否相交](https://leetcode-cn.com/problems/path-crossing/)

直接模拟机器人的行走过程，用一个集合维护当前已经经过的位置。

::: details 参考代码（Python3）

```python
class Solution:
    def isPathCrossing(self, path: str) -> bool:
        s = set()
        s.add((0, 0))
        x = 0
        y = 0
        dx = {"N": 0, "S": 0, "E": 1, "W": -1};
        dy = {"N": 1, "S": -1, "E": 0, "W": 0};
        for c in path:
            x += dx[c]
            y += dy[c]
            if (x, y) in s:
                return True;
            s.add((x, y))
        return False
```

:::

## Problem B - [检查数组对是否可以被 k 整除](https://leetcode-cn.com/problems/check-if-array-pairs-are-divisible-by-k/)

按余数进行统计，然后考虑$k$的奇偶性分别讨论即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        vector<int> cnt(k);
        for (int i : arr)
            cnt[(i % k + k) % k]++;
        if (k & 1) {
            for (int i = 1; i <= k / 2; ++i)
                if (cnt[i] != cnt[k - i])
                    return false;
            if (cnt[0] & 1)
                return false;
            return true;
        } else {
            for (int i = 1; i < k / 2; ++i)
                if (cnt[i] != cnt[k - i])
                    return false;
            if ((cnt[0] & 1) || (cnt[k / 2] & 1))
                return false;
            return true;
        }
    }
};
```

:::

## Problem C - [满足条件的子序列数目](https://leetcode-cn.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/)

排序后使用双指针求解。

假设当前右指针位置为$r$，左边能够满足$nums[i]+nums[r]\leq target$的$i$的最大值为$l$，则最大值为$a_r$的子序列中，满足条件的子序列数目为子序列总数减去$a_0,\cdots,a_l$一个都没有取的子序列总数。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;

class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> two(n);
        two[0] = 1;
        for (int i = 1; i < n; ++i)
            two[i] = (two[i - 1] << 1) % MOD;
        int ans = 0, l = 0;
        for (int r = n - 1; r >= 0; --r) {
            if (l > r)
                l = r;
            if (nums[l] + nums[r] > target)
                continue;
            while (l < r && nums[l + 1] + nums[r] <= target)
                l++;
            if (l == r)
                ans = (ans + two[r]) % MOD;
            else
                ans = (ans + two[r] - two[r - l - 1]) % MOD;
        }
        if (ans < 0)
            ans += MOD;
        return ans;
    }
};
```

:::


## Problem D - [满足不等式的最大值](https://leetcode-cn.com/problems/max-value-of-equation/)

凡是含绝对值$|x|$的式子，都可以考虑用$|x|=\max\{x,-x\}$进行转化。

本题中，$y_i+y_j+|x_i-x_j|=\max\{y_i+x_i+(y_j-x_j),y_i-x_i+(y_j+x_j)\}$，因此可以用两个单调队列分别降序记录当前可用的$y-x$和$y+x$的值。在更新之前，首先利用$|x_i-x_j|\leq k$这一限制条件从队首删除不符合要求的元素。

本题数组已经按照$x$升序排列。如果原始数组无序，则首先还需要自行排序。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        int n = points.size();
        deque<pair<int, int>> plus, minus;
        plus.push_back({points[0][1] + points[0][0], 0});
        minus.push_back({points[0][1] - points[0][0], 0});
        int ans = INT_MIN;
        for (int i = 1; i < n; ++i) {
            while (!plus.empty() && points[plus.front().second][0] < points[i][0] - k)
                plus.pop_front();
            while (!minus.empty() && points[minus.front().second][0] < points[i][0] - k)
                minus.pop_front();
            int cplus = points[i][1] + points[i][0], cminus = points[i][1] - points[i][0];
            if (!plus.empty())
                ans = max(ans, cminus + plus.front().first);
            if (!minus.empty())
                ans = max(ans, cplus + minus.front().first);
            while (!plus.empty() && plus.back().first <= cplus)
                plus.pop_back();
            plus.push_back({cplus, i});
            while (!minus.empty() && minus.back().first <= cminus)
                minus.pop_back();
            minus.push_back({cminus, i});
        }
        return ans;
    }
};
```

:::

<Utterances />
