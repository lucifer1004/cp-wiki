# Leetcode 第34场双周赛题解

## Problem A - [矩阵对角线元素的和](https://leetcode-cn.com/problems/matrix-diagonal-sum/)

直接按照题意进行累加，同时注意避免重复即可。

::: details 参考代码（Python 3）

```python
class Solution:
    def diagonalSum(self, mat: List[List[int]]) -> int:
        ans = 0
        n = len(mat)
        for i in range(n):
            ans += mat[i][i]
            if i != n - i - 1:
                ans += mat[i][n - i - 1]
        return ans
```

:::

## Problem B - [分割字符串的方案数](https://leetcode-cn.com/problems/number-of-ways-to-split-a-string/)

一遍扫描记录下所有`1`的位置。如果总数不是$3$的倍数，显然无解；如果总数为$0$，那么可以用插板法，答案为$n-1\choose 2$。

如果总数大于$0$且为$3$的倍数，设总数为$3t$，我们显然应该在第$t$和$t+1$个`1`之间做一个分割，在第$2t$和$2t+1$个`1`之间做第二个分割。假设第一个交界处的总长度为$l_1$，第二个交界处的总长度为$l_2$，我们分别使用插板法，可以知道答案为${l_1\choose1}{l_2\choose1}=l_1l_2$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int numWays(string s) {
        vector<int> a;
        int n = s.size();
        for (int i = 0; i < n; ++i)
            if (s[i] == '1')
                a.emplace_back(i);
        int m = a.size();
        if (m % 3 != 0)
            return 0;
        if (a.empty())
            return (ll)(n - 1) * (n - 2) / 2 % MOD;
        int t = m / 3;
        int d1 = a[t] - a[t - 1], d2 = a[t * 2] - a[t * 2 - 1];
        return (ll)d1 * d2 % MOD;
    }
};
```

:::

## Problem C - [删除最短的子数组使剩余数组有序](https://leetcode-cn.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/)

~~一开始看错题目，以为可以删除子序列，当成LIS来做怒吃两发WA。~~

因为要删除子数组，也就是连续段，所以我们只能是取一个前缀加一个后缀来构造一个不减的序列。我们不能取中间的段，因为我们没有办法既删除左边又删除右边。

考虑最长的不减的前缀，假设其长度为$L$。显然，我们在左边取得越长，相应地在右边能取的就越短。所以可以用双指针来求解。

为了避免边界情况的讨论，可以在原数组开头加一个$-1$，结尾加一个$10^9$作为哨兵。

时间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int l = 0;
        while (l + 1 < n && arr[l] <= arr[l + 1])
            l++;
        if (l == n - 1)
            return 0;
        vector<int> v = {-1};
        v.insert(v.end(), arr.begin(), arr.end());
        v.emplace_back(1e9);
        int ans = 0, r = n + 1;
        for (int i = l + 1; i >= -1; --i) {
            while (v[r - 1] <= v[r] && v[r - 1] >= v[i] && r - 1 > i)
                r--;
            ans = max(ans, i + n + 1 - r);
        }
        return n - ans;
    }
};
```

:::

## Problem D - [统计所有可行路径](https://leetcode-cn.com/problems/count-all-possible-routes/)

比较明显的动态规划，用$dp[location][used\_fuel]$表示当前在$location$位置，用了$used\_fuel$的可行路径数，然后枚举下一个位置进行转移。

起始状态是$dp[start][0]=1$，其余为$0$。

时间复杂度$O(N^2F)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int n = locations.size();
        vector<vector<ll>> dp(n, vector<ll>(fuel + 1, 0));
        dp[start][0] = 1;
        for (int f = 0; f < fuel; ++f)
            for (int i = 0; i < n; ++i) {
                if (dp[i][f] == 0)
                    continue;
                for (int j = 0; j < n; ++j) {
                    if (j == i)
                        continue;
                    ll cost = abs(locations[i] - locations[j]);
                    if (f + cost <= fuel)
                        dp[j][f + cost] = (dp[j][f + cost] + dp[i][f]) % MOD;
                }
            }
        ll ans = 0;
        for (int i = 0; i <= fuel; ++i)
            ans = (ans + dp[finish][i]) % MOD;
        return ans;
    }
};
```

:::

<Utterances />
