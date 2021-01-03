# Leetcode 第222场周赛题解

## Problem A - [卡车上的最大单元数](https://leetcode-cn.com/problems/maximum-units-on-a-truck/)

因为箱子可以一个一个装，所以显然应该优先选择单元数最大的箱子，因此对箱子类型按照单元数目降序排序，然后贪心选取即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(boxTypes.begin(), boxTypes.end(), [](vector<int> &a, vector<int> &b){
            return a[1] > b[1]; 
        });
        int ans = 0;
        for (auto &v : boxTypes) {
            int can = min(v[0], truckSize);
            ans += can * v[1];
            truckSize -= can;
        }
        return ans;
    }
};
```

:::

## Problem B - [大餐计数](https://leetcode-cn.com/problems/count-good-meals/)

用哈希表统计每种美味程度的餐品的数目，然后对于每一种美味程度，枚举$2$的幂次即可。注意最后得到的结果要除以$2$再取模，因为每一个组合我们计算了两次。

- 时间复杂度$\mathcal{O}(N\log MAXN)$，本题中$MAXN=2^{21}$（可以由两个$2^{20}$$组合得到）。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        ll ans = 0;
        unordered_map<int, int> cnt;
        for (int i : deliciousness)
            cnt[i]++;
        for (auto [i, f] : cnt) {
            for (int k = 0; k <= 21; ++k) {
                int mask = 1 << k;
                int comp = mask - i;
                if (comp < 0)
                    continue;
                if (comp != i && cnt.count(comp))
                    ans += 1LL * f * cnt[comp];
                if (comp == i && f >= 2)
                    ans += 1LL * f * (f - 1);
            }
        }
        return ans / 2 % MOD;
    }
};
```

:::

## Problem C - [将数组分成三个子数组的方案数](https://leetcode-cn.com/problems/ways-to-split-array-into-three-subarrays/)

双指针+二分。

- 双指针保证中间区间的和不小于左边区间。
- 二分查找能够使得中间区间的和不大于右边区间的最右位置。

当然，为了快速计算各区间的和，计算前缀和也是一个必不可少的准备工作。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; ++i)
            s[i] = s[i - 1] + nums[i - 1];
        ll ans = 0;
        int m = 2;
        for (int l = 1; l <= n - 2; ++l) {
            int L = s[l];
            m = max(m, l + 1);
            while (m < n && s[m] - L < L)
                m++;
            if (m == n)
                break;
            int lo = m, hi = n - 1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                if (s[n] - s[mid] < s[mid] - L)
                    hi = mid - 1;
                else
                    lo = mid + 1;
            }
            ans += hi - m + 1;
        }
        return ans % MOD;
    }
};
```

:::

## Problem D - [得到子序列的最少操作次数](https://leetcode-cn.com/problems/minimum-operations-to-make-a-subsequence/)

本题中，一个初看不起眼的条件成为了解题的最关键要素，也即“$target$不包含任何重复元素”。

不难看出，本题是一个最长公共子序列问题，但是两个数组的长度达到了$10^5$，而通常的最长公共子序列的动态规划解法的时间复杂度为$\mathcal{O}(NM)$，显然会超时。

不妨考虑一下我们是如何进行动态规划的。当且仅当$a[i]=b[j]$时，我们可以得到$dp[i][j]=dp[i-1][j-1]+1$，而其余情况下公共子序列的长度是不会增长的。这提示我们进一步关注两个数组之间的相等关系。

因为$target$不包含任何重复元素，所以我们可以对所有元素从左到右进行编号。之后，我们将$arr$中的元素替换为对应的编号（如果在$target$中存在相同元素的话）或$-1$（如果不存在这一元素）。

这时，我们不难发现，如果要使用$arr$中的某个元素，我们在其之前只能使用编号比它小的元素。

::: warning 注意
如果$target$中存在相同元素，我们还需要考虑$arr$中的这一元素应当作为第几个该元素，而对于前面每一个元素也都需要考虑这一点，这一方法的复杂度将会极大地劣化。
:::

这样，最长公共子序列就变成了最长上升子序列，而我们知道后者是有$\mathcal{O}(N\log N)$的解法的，于是本题得以解决。

- 时间复杂度$\mathcal{O}(M\log\min(N,M))$，这里$\min(N,M)$是因为我们得到的公共子序列长度不会超过$\min(N,M)$，于是我们进行二分搜索的时间复杂度为$\mathcal{O}(\log\min(N,M))$。
- 空间复杂度$\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> dict;
        for (int i = 0; i < target.size(); ++i)
            dict[target[i]] = i;
        vector<int> rank(arr.size());
        for (int i = 0; i < arr.size(); ++i)
            if (dict.count(arr[i]))
                rank[i] = dict[arr[i]];
            else
                rank[i] = -1;
        vector<int> LIS;
        for (int i : rank) {
            if (i == -1)
                continue;
            auto it = lower_bound(LIS.begin(), LIS.end(), i);
            if (it == LIS.end())
                LIS.emplace_back(i);
            else
                *it = i;
        }
        return target.size() - LIS.size();
    }
};
```

:::

<Utterances />
