# Leetcode 第238场周赛题解

## Problem A - [K 进制表示下的各位数字总和](https://leetcode.cn/contest/weekly-contest-238/problems/sum-of-digits-in-base-k/)

模拟。

- 时间复杂度$\mathcal{O}(\log_kN)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int sumBase(int n, int k) {
        int ans = 0;
        while (n) {
            ans += n % k;
            n /= k;
        }
        return ans;
    }
};
```

:::

## Problem B - [最高频元素的频数](https://leetcode.cn/contest/weekly-contest-238/problems/frequency-of-the-most-frequent-element/)

排序+双指针。

因为只有+1操作，所以我们只可能获得更多的大元素。因此，我们首先将数组升序排列。

之后，我们采用双指针来考虑操作次数的限制。如果将当前区间内的元素全都变为区间右端点所需的操作次数超过$k$，我们就将区间左端点右移。

- 时间复杂度$\mathcal{O}(N\log N)$，因为我们需要对数组进行排序。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        ll sum = 0;
        int l = 0;
        for (int r = 0; r < n; ++r) {
            sum += nums[r];
            while (1LL * nums[r] * (r - l + 1) - sum > k) {
                sum -= nums[l];
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
```

:::

## Problem C - [所有元音按顺序排布的最长子字符串](https://leetcode.cn/contest/weekly-contest-238/problems/longest-substring-of-all-vowels-in-order/)

模拟。如果当前有串，并且当前字母可以接到当前的串后，就接上。如果不能接上，但当前字母为`a`，则可以利用其作为新串的起点。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int longestBeautifulSubstring(string word) {
        string ref = "aeiou";
        int ans = 0;
        int start = -1;
        int now = 0;
        for (int i = 0; i < word.size(); ++i) {
            if (start == -1) {
                if (word[i] != 'a')
                    continue;
                else {
                    start = i;
                    now = 0;
                }
            } else {
                if (now < 4 && word[i] == ref[now + 1]) 
                    now++;
                else if (word[i] != ref[now]) {
                    if (word[i] == 'a')
                        start = i, now = 0;
                    else
                        start = -1;
                }
            }
            
            if (start != -1 && now == 4)
                ans = max(ans, i - start + 1);
        }
        
        return ans;
    }
};
```

:::

## Problem D - [最高建筑高度](https://leetcode.cn/contest/weekly-contest-238/problems/maximum-building-height/)

首先，我们将所有限制条件按照坐标升序排列。

我们首先从左到右，计算每个受限位置只考虑来自左边的约束时能取得的最大高度；然后从右到左，计算每个受限位置只考虑来自右边的约束时能取得的最大高度。

这样我们就得到了每一个受限位置处的最大高度。这时，我们考虑相邻两个受限位置中间的区域能够取得的最大高度。假设左边的高度为$L$，右边的高度为$R$，中间的距离为$D$，则我们在这段区间能取得的最大高度必须满足$H-L+H-R\leq D$，从而$H\leq\dfrac{L+R+D}{2}$。

需要注意的是，最右边的一个区间需要单独考虑，因为它只受到左约束，而没有右约束。

- 时间复杂度$\mathcal{O}(M\log M)$，因为我们需要对限制条件进行排序。
- 空间复杂度$\mathcal{O}(M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        int m = restrictions.size();
        if (m == 0)
            return n - 1;
        restrictions.push_back({1, 0});
        m++;
        sort(restrictions.begin(), restrictions.end());
        vector<int> l(m), r(m);
        l[0] = 0;
        for (int i = 1; i < m; ++i) {
            int left = l[i - 1];
            int dist = restrictions[i][0] - restrictions[i - 1][0];
            l[i] = min(restrictions[i][1], left + dist);
        }
        r[m - 1] = restrictions[m - 1][1];
        for (int i = m - 2; i >= 0; --i) {
            int right = r[i + 1];
            int dist = restrictions[i + 1][0] - restrictions[i][0];
            r[i] = min(restrictions[i][1], right + dist);
        }
        int ans = 0;
        for (int i = 0; i < m - 1; ++i) {
            int lh = min(l[i], r[i]);
            int rh = min(l[i + 1], r[i + 1]);
            int dist = restrictions[i + 1][0] - restrictions[i][0];
            ans = max(ans, (lh + rh + dist) / 2);
        }
        ans = max(ans, n - restrictions[m - 1][0] + min(l[m - 1], r[m - 1]));
        
        return ans;
    }
};
```

:::


<Utterances />
