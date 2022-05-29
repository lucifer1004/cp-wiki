# Leetcode 第48场双周赛题解

## Problem A - [字符串中第二大的数字](https://leetcode.cn/problems/second-largest-digit-in-a-string/)

模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

注意这里最多10个数字，所以可以认为`set`操作的时间复杂度为常数。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int secondHighest(string s) {
        set<int> st;
        for (char c : s)
            if ('0' <= c && c <= '9')
                st.insert(c - '0');
        if (st.size() < 2)
            return -1;
        return *prev(prev(st.end()));
    }
};
```

:::

如果用Python的话一行就可以搞定。

::: details 参考代码（Python 3）

```python
class Solution:
    def secondHighest(self, s: str) -> int:
        v = sorted(list(set(map(int, (filter(lambda x: x.isnumeric(), list(s)))))), reverse=True)
        return -1 if len(v) < 2 else v[1]
```

:::

## Problem B - [设计一个验证系统](https://leetcode.cn/problems/design-authentication-manager/)

理解题意后直接模拟即可。

- 生成和更新操作的时间复杂度为$\mathcal{O}(1)$，计数操作的时间复杂度为$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class AuthenticationManager {
    int timeToLive;
    unordered_map<string, int> mp;
public:
    AuthenticationManager(int timeToLive): timeToLive(timeToLive) {}
    
    void generate(string tokenId, int currentTime) {
        mp[tokenId] = currentTime + timeToLive;
    }
    
    void renew(string tokenId, int currentTime) {
        if (mp.count(tokenId) && mp[tokenId] > currentTime)
            mp[tokenId] = currentTime + timeToLive;
    }
    
    int countUnexpiredTokens(int currentTime) {
        int ans = 0;
        for (auto [key, expirationTime] : mp)
            if (expirationTime > currentTime)
                ans++;
        return ans;
    }
};
```

:::

## Problem C - [你能构造出连续值的最大数目](https://leetcode.cn/problems/maximum-number-of-consecutive-values-you-can-make/)

如果做过[LC330 - 按要求补齐数组](https://leetcode.cn/problems/patching-array/)，那么本题就非常简单了。

- 显然，我们应当从最小的数字开始——所以要对原数组进行排序。
- 如果当前最大表示到$K$，此时数组中还未使用的最小元素为$a_i$
    - 如果$a_i>K+1$，那么我们无论如何也表示不出$K+1$，结束求解。
    - 如果$a_i\leq K+1$，由于我们已经能表示$[0,K]$，则在使用$a_i$后一定可以表示$[0,K+a_i]$，所以我们进行更新$K\rightarrow K+a_i$，继续求解。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(), coins.end());
        int now = 0;
        for (int coin : coins) {
            if (coin <= now + 1) 
                now += coin;
            else
                break;
        }
        return now + 1;
    }
};
```

:::

## Problem D - [N 次操作后的最大分数和](https://leetcode.cn/problems/maximize-score-after-n-operations/)

看到$N$的取值范围就知道是Bitmask DP。预处理出所有的GCD，之后从0状态开始动态规划即可。当前的轮次可以从状态二进制中$1$的个数求出。

- 时间复杂度$\mathcal{O}(N^2(\log MAX+2^N))$。
- 空间复杂度$\mathcal{O}(N^2+2^N)$。

::: details 参考代码（C++）

```cpp
int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(1 << n, 0);
        vector<vector<int>> g(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                g[i][j] = gcd(nums[i], nums[j]);
        for (int state = 0; state < (1 << n); ++state) {
            int cnt = __builtin_popcount(state);
            if (cnt & 1)
                continue;
            int now = cnt / 2 + 1;
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j) {
                    if ((state & (1 << i)) || (state & (1 << j)))
                        continue;
                    int nxt = state | (1 << i) | (1 << j);
                    dp[nxt] = max(dp[nxt], dp[state] + g[i][j] * now);
                }
        }
        return dp.back();
    }
};
```

:::

<Utterances />
