# Leetcode 第38场双周赛题解

## Problem A - [按照频率将数组升序排序](https://leetcode-cn.com/problems/sort-array-by-increasing-frequency/)

按照要求，先统计频率，然后排序。

时间复杂度$O(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        map<int, int> cnt;
        for (int num : nums)
            cnt[num]++;
        vector<pair<int, int>> v(cnt.begin(), cnt.end());
        sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b){
            return a.second < b.second || (a.second == b.second && a.first > b.first);
        });
        vector<int> ans;
        for (auto &p : v)
            for (int i = 0; i < p.second; ++i)
                ans.emplace_back(p.first);
        return ans;
    }
};
```

:::

## Problem B - [两点之间不包含任何点的最宽垂直面积](https://leetcode-cn.com/problems/widest-vertical-area-between-two-points-containing-no-points/)

将所有点按照$x$坐标排序，然后找到相邻两个点之间最大的$\Delta x$即可。

时间复杂度$O(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](vector<int> &a, vector<int> &b){
            return a[0] < b[0];
        });
        int ans = 0;
        for (int i = 0; i + 1 < points.size(); ++i)
            ans = max(ans, points[i + 1][0] - points[i][0]);
        return ans;
    }
};
```

:::

## Problem C - [统计只差一个字符的子串数目](https://leetcode-cn.com/problems/count-substrings-that-differ-by-one-character/)

枚举不同的那一个字符的位置，然后向两端扩展。

时间复杂度$O(|S||T|\min(|S|,|T|))$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countSubstrings(string s, string t) {
        int n = s.size(), m = t.size();
        int mlen = min(n, m);
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (s[i] == t[j])
                    continue;
                int l = 0;
                while (i - (l + 1) >= 0 && j - (l + 1) >= 0 && s[i - (l + 1)] == t[j - (l + 1)])
                    l++;
                int r = 0;
                while (i + (r + 1) < n && j + (r + 1) < m && s[i + (r + 1)] == t[j + (r + 1)])
                    r++;
                ans += (l + 1) * (r + 1);
            }
        return ans;
    }
};
```

:::

## Problem D - [通过给定词典构造目标字符串的方案数](https://leetcode-cn.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/)

预处理得到词典中的第$i$位有多少个字母$c$，记录为$can[i][c]$。

使用动态规划求解方案总数，$dp[j]$表示当前构造到目标字符串第$j$位的方法总数。按顺序遍历词典的每一位，然后对状态进行转移。

最后的答案即为$dp[N]$。

时间复杂度$O(NM+TM)$。其中$N$为目标词的长度，$M$为词典中单词的长度，$T$为词典中单词的个数。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int numWays(vector<string>& words, string target) {
        int n = target.size();
        int m = words[0].size();
        vector<vector<int>> can(m + 1, vector<int>(26));
        for (auto &word : words)
            for (int i = 0; i < m; ++i) 
                can[i + 1][word[i] - 'a']++;
        vector<ll> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= m; ++i)
            for (int j = n; j >= 1; --j)
                dp[j] = (dp[j] + dp[j - 1] * can[i][target[j - 1] - 'a']) % MOD;
        return dp[n];
    }
};
```

:::

<Utterances />
