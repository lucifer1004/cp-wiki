# Leetcode 第30场双周赛题解

## Problem A - [转变日期格式](https://leetcode.cn/problems/reformat-date/)

模拟题，使用字符串操作比较方便的语言可以加快速度。或者可以直接用语言内置的日期库。

::: details 参考代码（Python3）

```python
class Solution:
    def reformatDate(self, date: str) -> str:
        a, b, c = date.split(' ')
        d = {"Jan": "01", "Feb": "02", "Mar": "03", "Apr": "04", "May": "05", "Jun": "06", "Jul": "07", "Aug": "08", "Sep": "09", "Oct": "10", "Nov": "11", "Dec": "12"}
        day = a[:-2]
        if len(day) == 1:
            day = "0" + day
        month = d[b]
        year = c
        return "{}-{}-{}".format(year, month, day)
```

:::

## Problem B - [子数组和排序后的区间和](https://leetcode.cn/problems/range-sum-of-sorted-subarray-sums/)

方法一：利用前缀和暴力枚举所有子数组的和，排序后再累加计算区间和。时间复杂度$O(n^2\log n)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        int m = n * (n + 1) / 2;
        vector<int> sum(n + 1);
        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + nums[i - 1];
        vector<int> v;
        v.reserve(m);
        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; ++j)
                v.emplace_back(sum[j] - sum[i - 1]);
        sort(v.begin(), v.end());
        ll ans = 0;
        for (int i = left - 1; i < right; ++i)
            ans = (ans + v[i]) % MOD;
        return ans;
    }
};
```

:::

方法二：二分查找+双指针求解前$k$小子数组和的和。

为了求解前$k$小子数组的和，首先要求出第$k$小的子数组的和。这个和值可以通过二分查找求得。在每次查找过程中，需要统计小于等于当前值的子数组的个数，这可以通过对前缀和数组进行双指针操作来实现。

在求得第$k$小的和值后，首先求出小于该和值的子数组的个数和总和。这可以通过对前缀和的前缀和数组进行双指针操作来实现。最后，再根据差值，加上等于该和值的子数组的总和，即得到结果。

最后，要得到$[left,right]$区间的结果，只需要用$f(right)-f(left-1)$即可。注意对结果取模。

总的时间复杂度为$O(N\log S)$，其中$S$为数组元素的总和。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
    int n;
    vector<int> pre, prepre;
    
    int search(int k) {
        int l = 1, r = pre[n];
        while (l <= r) {
            int mid = (l + r) >> 1, cnt = 0;
            int i = 0, j = 0;
            while (i < n) {
                while (j < n && pre[j + 1] - pre[i] <= mid)
                    j++;
                cnt += j - i;
                i++;
            }
            if (cnt < k)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }
    
    int sum(int k) {
        if (k == 0)
            return 0;
        int target = search(k);
        int cnt = 0;
        ll ans = 0;
        int i = 0, j = 0;
        while (i < n) {
            while (j < n && pre[j + 1] - pre[i] < target)
                j++;
            cnt += j - i;
            ans += prepre[j] - prepre[i] - (j - i) * pre[i];
            i++;
        }
        ans += (k - cnt) * target;
        return ans % MOD;
    }
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        this->n = n;
        pre = vector<int>(n + 1);
        prepre = vector<int>(n + 1);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + nums[i - 1];
            prepre[i] = prepre[i - 1] + pre[i];
        }
        int r = sum(right);
        int l = sum(left - 1);
        return (r - l + MOD) % MOD;
    }
};
```

:::

## Problem C - [三次操作后最大值与最小值的最小差](https://leetcode.cn/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/)

首先将数组排序，之后枚举在左边和在右边进行操作的次数即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if (n <= 4)
            return 0;
        sort(nums.begin(), nums.end());
        int ans = INT_MAX;
        for (int i = 0; i <= 3; ++i) {
            ans = min(ans, nums[n - 4 + i] - nums[i]);
        }
        return ans;
    }
};
```

:::

## Problem D - [石子游戏 IV](https://leetcode.cn/problems/stone-game-iv/)

边界条件是$dp[1]=true$，之后递推求解即可。对于某种状态$dp[state]$，只要有一种取法能够使得剩下的数对应状态$dp[state-k*k]=false$，该状态即为获胜状态；否则为失败状态。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1);
        dp[1] = true;
        for (int i = 2; i <= n; ++i) {
            bool win = false;
            for (int k = 1; k * k <= i; ++k)
                if (!dp[i - k * k]) {
                    win = true;
                    break;
                }
            dp[i] = win;
        }
        return dp[n];
    }
};
```

:::

<Utterances />
