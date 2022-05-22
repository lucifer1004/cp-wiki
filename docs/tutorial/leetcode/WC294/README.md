# Leetcode 第294场周赛题解

## Problem A - [字母在字符串中的百分比](https://leetcode.cn/problems/percentage-of-letter-in-string/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(|S|)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def percentageLetter(self, s: str, letter: str) -> int:
        return s.count(letter) * 100 // len(s)
```

:::

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int percentageLetter(string s, char letter) {
        int n = s.size();
        int cnt = 0;
        for (char c : s)
            if (c == letter)
                cnt++;
        return cnt * 100 / n;
    }
};
```

:::

## Problem B - [装满石头的背包的最大数量](https://leetcode.cn/problems/maximum-bags-with-full-capacity-of-rocks/)

### 方法一：排序 + 贪心

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumBags(self, capacity: List[int], rocks: List[int], additionalRocks: int) -> int:
        rem = sorted([c - r for c, r in zip(capacity, rocks)])
        for i, ri in enumerate(rem):
            if additionalRocks >= ri:
                additionalRocks -= ri
            else:
                return i
        return len(rocks)
```

:::

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int n = capacity.size();
        vector<int> rem(n);
        for (int i = 0; i < n; ++i)
            rem[i] = capacity[i] - rocks[i];
        sort(rem.begin(), rem.end());
        for (int i = 0; i < n; ++i) {
            if (additionalRocks >= rem[i])
                additionalRocks -= rem[i];
            else
                return i;
        }
        return n;
    }
};
```

:::

## Problem C - [表示一个折线图的最少线段数](https://leetcode.cn/problems/minimum-lines-to-represent-a-line-chart/)

### 方法一：排序

- 时间复杂度 $\mathcal{O}(N\log N)$ 。
- 空间复杂度 $\mathcal{O}(1)$ 。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumLines(vector<vector<int>>& stockPrices) {
        int n = stockPrices.size();
        if (n <= 2) return n - 1;
        sort(stockPrices.begin(), stockPrices.end());
        int ans = 1;
        for (int i = 1; i + 1 < n; ++i) {
            int lx = stockPrices[i][0] - stockPrices[i - 1][0];
            int ly = stockPrices[i][1] - stockPrices[i - 1][1];
            int rx = stockPrices[i + 1][0] - stockPrices[i][0];
            int ry = stockPrices[i + 1][1] - stockPrices[i][1];
            if (1LL * lx * ry != 1LL * ly * rx) ans++;
        }
        return ans;
    }
};
```

:::

## Problem D - [巫师的总力量和](https://leetcode.cn/problems/sum-of-total-strength-of-wizards/)

### 方法一：单调栈 + 前缀和

一共使用两次单调栈和三次前缀和。

- 时间复杂度为 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int totalStrength(vector<int>& strength) {
        int n = strength.size();
        vector<int> l(n, -1), r(n, n);
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && strength[i] < strength[s.top()]) {
                r[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        s = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && strength[i] <= strength[s.top()]) {
                l[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        vector<ll> pre(n + 1), apre(n + 1), dpre(n + 2);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = (pre[i] + strength[i]) % MOD;
            apre[i + 1] = (apre[i] + 1LL * (i + 1) * strength[i]) % MOD;
        }
        for (int i = n; i >= 1; --i) {
            dpre[i] = (dpre[i + 1] + 1LL * (n - i + 1) * strength[i - 1]) % MOD;
        }

        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            ll left = i - l[i], right = r[i] - i;
            ll lsum =
                apre[i] - apre[l[i] + 1] - (pre[i] - pre[l[i] + 1]) * (l[i] + 1);
            lsum = lsum * right % MOD;
            if (lsum < 0) lsum += MOD;
            ll rsum =
                dpre[i + 2] - dpre[r[i] + 1] - (pre[r[i]] - pre[i + 1]) * (n - r[i]);
            rsum = rsum * left % MOD;
            if (rsum < 0) rsum += MOD;
            ans += (lsum + rsum + left * right % MOD * strength[i] % MOD) % MOD * strength[i] % MOD;
            ans %= MOD;
        }
        return ans;
    }
};
```

:::

<Utterances />
