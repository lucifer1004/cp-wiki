# Leetcode 第50场双周赛题解

## Problem A - [最少操作使数组递增](https://leetcode-cn.com/problems/minimum-operations-to-make-the-array-increasing/)

因为只能增加数不能减少数，所以从左向右贪心操作即可（如果已经比前一个大，就不操作；否则使其变为前一个数加一）。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0, last = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            int target = max(nums[i], last + 1);
            ans += target - nums[i];
            last = target;
        }
        return ans;
    }
};
```

:::

## Problem B - [统计一个圆中点的数目](https://leetcode-cn.com/problems/queries-on-number-of-points-inside-a-circle/)

考虑到数据范围，直接暴力计算即可。

- 时间复杂度为$\mathcal{O}(NQ)$。
- 空间复杂度$\mathcal{O}(Q)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> ans;
        for (auto &query: queries) {
            int x = query[0], y = query[1], r = query[2];
            int cnt = 0;
            for (auto &point : points) {
                int dx = x - point[0], dy = y - point[1];
                if (dx * dx + dy * dy <= r * r)
                    cnt++;
            }
            ans.emplace_back(cnt);
        }
        return ans;
    }
};
```

:::

## Problem C - [每个查询的最大异或值](https://leetcode-cn.com/problems/maximum-xor-for-each-query/)

可以预计算出每一个前缀异或和（或计算出总异或和，然后在每次移除元素时进行更新）。

对于给定的前缀异或和，为了使得最终结果最大，我们应当把当前异或和为$1$的位设为$0$，当前异或和为$0$的位设为$1$。当然，最多不能超过$K$位。

- 时间复杂度$\mathcal{O}(NK)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        vector<int> ans;
        int val = 0;
        for (int num : nums)
            val ^= num;
        while (!nums.empty()) {
            int ret = 0;
            for (int i = 0; i < maximumBit; ++i) {
                if ((val & (1 << i)) == 0)
                    ret ^= (1 << i);
            }
            ans.emplace_back(ret);
            val ^= nums.back();
            nums.pop_back();
        }
        return ans;
    }
};
```

:::

## Problem D - [使字符串有序的最少操作次数](https://leetcode-cn.com/problems/minimum-number-of-operations-to-make-string-sorted/)

### 方法一：枚举更小排列的数目

操作看起来很唬人，实际上就是求当前排列的前一个排列。因此，我们实际要做的就是求给定排列的字典序。

我们首先考虑，给定每一个字母的频率，我们能够构造多少种排列？

显然，答案为$\dfrac{N!}{\prod n_i!}$，其中$\sum n_i=N$。

那么，我们就可以逐位进行操作，对于每一位，我们枚举比当前字母小的所有字母，统计出以它们开始的排列的数目，这些都是比当前排列小的。注意这里可以复用计算结果，不需要每次全部重新计算。

最后，就可以得到当前排列的字典序。

- 时间复杂度$\mathcal{O}(N(|\sum|+\log M))$。其中$|\sum|$为字典大小，$M=10^9+7-2=10^9+5$。
- 空间复杂度$\mathcal{O}(N+|\sum|)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

ll fexp(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1)
            ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}

ll inv(ll x) {
    return fexp(x, MOD - 2);
}

class Solution {
public:
    int makeStringSorted(string s) {
        ll ans = 0;
        int n = s.size();
        vector<int> cnt(26);
        for (char c : s)
            cnt[c - 'a']++;
        vector<ll> fac(n + 1), invfac(n + 1);
        fac[0] = invfac[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fac[i] = fac[i - 1] * i % MOD;
            invfac[i] = inv(fac[i]);
        }
        
        for (int i = 0; i < n; ++i) {
            ll tot = fac[n - 1 - i];
            for (int k = 0; k < 26; ++k)
                tot = tot * invfac[cnt[k]] % MOD;
            for (int j = 0; j < s[i] - 'a'; ++j) {
                if (cnt[j])
                    ans = (ans + tot * cnt[j] % MOD) % MOD;
            }
            cnt[s[i] - 'a']--;
        }
        
        return ans;
    }
};
```

:::

### 方法二：树状数组+线性逆元

我们可以使用树状数组来维护每个字母的频率，同时用线性求逆元的方法获取`invfac`（可参考[OI-Wiki](https://oi-wiki.org/math/inverse/#n)）。这样的时间复杂度是$\mathcal{O}(N\log|\sum|+\log M)$。

<Utterances />
