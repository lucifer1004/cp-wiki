# Leetcode 第298场周赛题解

## Problem A - [兼具大小写的最好英文字母](https://leetcode.cn/problems/greatest-english-letter-in-upper-and-lower-case/)

### 方法一：穷举

- 时间复杂度 $\mathcal{O}(|S| + |\Sigma|)$。
- 空间复杂度 $\mathcal{O}(min(|S|, |\Sigma|))$。

::: details 参考代码（Python 3）

```python
class Solution:
    def greatestLetter(self, s: str) -> str:
        chars = set(s)
        for i in range(25, -1, -1):
            ch = chr(ord('A') + i)
            if ch in chars and ch.lower() in chars:
                return ch
        return ''
```

:::

## Problem B - [个位数字为 K 的整数之和](https://leetcode.cn/problems/sum-of-numbers-with-units-digit-k/)

### 方法一：穷举

- 时间复杂度 $\mathcal{O}(1)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumNumbers(self, num: int, k: int) -> int:
        if num == 0:
            return 0
        for i in range(1, 11):
            if i * k % 10 == num % 10 and i * k <= num:
                return i
        return -1
```

:::

## Problem C - [小于等于 K 的最长二进制子序列](https://leetcode.cn/problems/longest-binary-subsequence-less-than-or-equal-to-k/)

### 方法一：动态规划

注意内层循环的顺序。

- 时间复杂度 $\mathcal{O}(|S|^2)$ 。
- 空间复杂度 $\mathcal{O}(|S|)$ 。

::: details 参考代码（Python 3）

```python
class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        n = len(s)
        dp = [k + 1] * (n + 1)
        dp[0] = 0
        for i in range(n):
            for j in range(i, -1, -1):
                if dp[j] > k:
                    continue
                if dp[j] * 2 + int(s[i]) <= k:
                    dp[j + 1] = min(dp[j + 1], dp[j] * 2 + int(s[i]))
        
        for i in range(n, -1, -1):
            if dp[i] <= k:
                return i
            
        return -1
};
```

:::

## Problem D - [卖木头块](https://leetcode.cn/problems/selling-pieces-of-wood/)

### 方法一：动态规划

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    ll sellingWood(int m, int n, vector<vector<int>>& prices) {
        vector<vector<ll>> dp(m + 1, vector<ll>(n + 1));
        for (auto p : prices)
            dp[p[0]][p[1]] = max(dp[p[0]][p[1]], (ll)p[2]);
        
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k < i; ++k)
                    dp[i][j] = max(dp[i][j], dp[k][j] + dp[i - k][j]);
                for (int k = 1; k < j; ++k)
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
        
        return dp[m][n];
    }
};
```

<Utterances />
