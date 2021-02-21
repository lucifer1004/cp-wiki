# Leetcode 第229场周赛题解

## Problem A - [交替合并字符串](https://leetcode-cn.com/problems/merge-strings-alternately/)

按要求模拟即可。

- 时间复杂度$\mathcal{O}(|word1|+|word2|)$。
- 空间复杂度$\mathcal{O}(|word1|+|word2|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int l1 = word1.size(), l2 = word2.size();
        string ans;
        int p1 = 0, p2 = 0;
        while (p1 < l1 || p2 < l2) {
            if (p1 < l1)
                ans.push_back(word1[p1++]);
            if (p2 < l2)
                ans.push_back(word2[p2++]);
        }
        return ans;
    }
};
```

:::

## Problem B - [移动所有球到每个盒子所需的最小操作数](https://leetcode-cn.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/)

分别考虑把所有左边的球移到当前盒子的操作数，以及把所有右边的球移到当前盒子的操作数。

对于左边的情况，我们只需要维护当前一共的球数，就能够计算出再向右移动一位需要的额外花费。

右边的情况可以类似地进行处理。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        vector<int> l(n), r(n);
        int ln = 0, tot = 0;
        for (int i = 0; i < n; ++i) {
            l[i] = tot;
            if (boxes[i] == '1')
                ln++;
            tot += ln;
        }
        int rn = 0;
        tot = 0;
        for (int i = n - 1; i >= 0; --i) {
            r[i] = tot;
            if (boxes[i] == '1')
                rn++;
            tot += rn;
        }
        vector<int> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = l[i] + r[i];
        return ans;
    }
};
```

:::

## Problem C - [执行乘法运算的最大分数](https://leetcode-cn.com/problems/maximum-score-from-performing-multiplication-operations/)

考虑当前已经从$nums$左边取了$L$个数，从右边取了$R$个数，则对于第$L+R+1$个数，$multipliers[L+R+1]$（这里下标从$1$开始）的取值是确定的，而在$nums$中，我们可以选择$nums[L+1]$或$nums[N-R-1]$。由于这里无论我们选择左边还是右边，都与前面的$L+R$次选择无关，满足无后效性的要求，所以我们可以考虑进行动态规划，用$dp[L][R]$表示左边取$L$个，右边取$R$个数时的最大分数。

实际上，如果已经取了$K$个数，而左边取了$L$个，右边自然是取了$N-L$个，因此我们可以进一步将空间降低到一维。

- 时间复杂度$\mathcal{O}(M^2)$。
- 空间复杂度$\mathcal{O}(M)$。

::: details 参考代码（C++）

```cpp
#define INF 0x3f3f3f3f

class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size(), m = multipliers.size();
        vector<int> dp(m + 1, -INF);
        dp[0] = 0;
        for (int i = 0; i < m; ++i) {
            vector<int> ndp(m + 1, -INF);
            for (int j = 0; j <= i; ++j) {
                ndp[j + 1] = max(ndp[j + 1], dp[j] + nums[j] * multipliers[i]);
                ndp[j] = max(ndp[j], dp[j] + nums[n - 1 - (i - j)] * multipliers[i]);
            }
            dp = move(ndp);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

:::

## Problem D - [由子序列构造的最长回文串的长度](https://leetcode-cn.com/problems/maximize-palindrome-length-from-subsequences/)

实际上就是一个有条件限制的最长回文子序列问题。考虑串$S=word1+word2$，这里的限制条件就是前$|word1|$个字符中至少取一个，且后$|word2|$个字符中至少取一个。

我们首先考虑没有限制条件的最长回文子序列。这是一个经典的动态规划问题，我们有两种做法：

1. 中心扩展，$dp[L][R]$表示$S[L\dots R]$范围的最长回文子序列。
2. 令$T=S'$（$S$的倒序），然后求$S$和$T$的最长公共子序列。

考虑引入限制条件。我们使用三个数组，分别记录使用了$word1$的最长回文子序列，使用了$word2$的最长回文子序列和既使用了$word1$又使用了$word2$的最长回文子序列的长度。

在每一次转移时，我们根据当前字符的归属情况（属于$word1$还是$word2$）来决定是否能进行转移。

需要注意的是，这里我们应该使用上面的方法一（方法二可能也可以，但是会比较复杂），因为方法一中，我们是同时使用了两个字符，可以确保归属情况的正确处理。

- 时间复杂度$\mathcal{O}((|word1|+|word2|)^2)$。
- 空间复杂度$\mathcal{O}((|word1|+|word2|)^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int longestPalindrome(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        string s = word1 + word2;
        vector<vector<int>> lcs1(n + m + 1, vector<int>(n + m + 1));
        vector<vector<int>> lcs2(n + m + 1, vector<int>(n + m + 1));
        vector<vector<int>> lcs12(n + m + 1, vector<int>(n + m + 1));
        for (int len = 1; len <= n + m; ++len)
            for (int l = 1; l + len - 1 <= n + m; ++l) {
                int r = l + len - 1;
                bool use1 = l <= n;
                bool use2 = r > n;
                if (len == 1) {
                    if (use1)
                        lcs1[l][l] = 1;
                    if (use2)
                        lcs2[l][l] = 1;
                    continue;
                }
                if (s[l - 1] == s[r - 1]) {
                    if (use1 && use2) {
                        lcs12[l][r] = lcs12[l + 1][r - 1] + 2;
                    }
                    if (use1) {
                        if (lcs2[l + 1][r - 1] > 0)
                            lcs12[l][r] = max(lcs12[l][r], lcs2[l + 1][r - 1] + 2);
                        lcs1[l][r] = lcs1[l + 1][r - 1] + 2;
                    }
                    if (use2) {
                        if (lcs1[l + 1][r - 1] > 0)
                            lcs12[l][r] = max(lcs12[l][r], lcs1[l + 1][r - 1] + 2);
                        lcs2[l][r] = lcs2[l + 1][r - 1] + 2;
                    }
                }
                lcs12[l][r] = max(lcs12[l][r], max(lcs12[l + 1][r], lcs12[l][r - 1]));
                lcs1[l][r] = max(lcs1[l][r], max(lcs1[l + 1][r], lcs1[l][r - 1]));
                lcs2[l][r] = max(lcs2[l][r], max(lcs2[l + 1][r], lcs2[l][r - 1]));
        }
        return lcs12[1][n + m];
    }
};
```

:::

<Utterances />
