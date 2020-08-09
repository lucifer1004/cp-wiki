# Leetcode 第201场周赛题解

## Problem A -  [整理字符串](https://leetcode-cn.com/problems/make-the-string-great/)

数据范围很小，直接模拟即可，注意题面中的**反之亦然**。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    string makeGood(string s) {
        while (true) {
            int n = s.size();
            string t;
            for (int i = 0; i < n; ++i) {
                if (i + 1 < n && (s[i] - s[i + 1] == 'a' - 'A' || s[i] - s[i + 1] == 'A' - 'a'))
                    i++;
                else
                    t.push_back(s[i]);  
            }
            if (t == s)
                return t;
            s = t;
        }
        return "";
    }
};
```

:::

## Problem B - [找出第 N 个二进制字符串中的第 K 位](https://leetcode-cn.com/problems/find-kth-bit-in-nth-binary-string/)

因为数据范围比较小，实际上可以暴力模拟。不过正确的做法是递归。

首先，我们可以知道第$n$个字符串的长度一定为$2^n-1$，所以可以计算出$k$是位于前半段，中间，还是后半段。然后分别处理即可。

注意递归的边界条件。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    char findKthBit(int n, int k) {
        if (n == 1)
            return '0';
        int len = (1 << n) - 1;
        int mid = (len + 1) / 2;
        if (k == mid)
            return '1';
        if (k > mid)
            return '1' - findKthBit(n - 1, len + 1 - k) + '0';
        return findKthBit(n - 1, k);
    }
};
```

:::

## Problem C - [和为目标值的最大数目不重叠非空子数组数目](https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/)

和前一天晚上的第四题类似，子串/子数组的题目中，前缀数组是一个常用的手段。这里为了使得子数组数目尽可能大，需要当前的子数组尽可能小，所以我们要保存每一个和值对应的最后一个位置。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> dp(n + 1);
        unordered_map<int, int> dict;
        int sum = 0;
        dict[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1];
            sum += nums[i - 1];
            int delta = sum - target;
            if (dict.count(delta))
                dp[i] = max(dp[i], dp[dict[delta]] + 1);
            dict[sum] = i;
        }
        return dp[n];
    }
};
```

:::

## Problem D - [切棍子的最小成本](https://leetcode-cn.com/problems/minimum-cost-to-cut-a-stick/)

逆向思考，既然不管按照什么顺序切，最后切成的子段总是一样的，我们就可以把问题变成从子段开始合并，直到合并成一个整体。这样就成了最经典的区间DP问题。

::: spoiler 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());
        vector<int> seg;
        int l = 0;
        for (int i : cuts)
            seg.emplace_back(i - l), l = i;
        seg.emplace_back(n - l);
        int m = seg.size();
        vector<int> s(m + 1);
        for (int i = 1; i <= m; ++i)
            s[i] = s[i - 1] + seg[i - 1];
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, INF));
        for (int i = 1; i <= m; ++i)
            dp[i][i] = 0;
        for (int k = 2; k <= m; ++k)
            for (int i = 1; i + k - 1 <= m; ++i) {
                int r = i + k - 1;
                for (int j = i; j < r; ++j)
                    dp[i][r] = min(dp[i][r], dp[i][j] + dp[j + 1][r] + s[r] - s[i - 1]);
            }
        return dp[1][m];
    }
};
```

::: 