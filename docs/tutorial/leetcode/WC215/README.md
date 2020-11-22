# Leetcode 第215场周赛题解

## Problem A - [设计有序流](https://leetcode-cn.com/problems/design-an-ordered-stream/)

模拟。

- 插入操作的均摊时间复杂度为$O(1)$。因为指针是单向移动的。
- 空间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class OrderedStream {
    int ptr = 1;
    vector<string> v;
public:
    OrderedStream(int n) {
        v = vector<string>(n + 1);
    }
    
    vector<string> insert(int id, string value) {
        v[id] = value;
        vector<string> ret;
        while (ptr < v.size() && !v[ptr].empty())
            ret.emplace_back(v[ptr++]);
        return ret;
    }
};
```

:::

## Problem B - [确定两个字符串是否接近](https://leetcode-cn.com/problems/determine-if-two-strings-are-close/)

首先判断长度是否相等。在长度相等的情况下，题目中的两种操作可以理解为：

1. 对字符串进行任意排列
2. 交换两个字符的频次

所以实际上，我们需要判断的是：

1. 两个字符串的字符集是否一致
2. 两个字符串的字符频率集是否一致

统计频次，分别进行判断即可。

- 时间复杂度$O(|l_1|+|l_2|+C\log C)$，$C$为字母表的大小。
- 空间复杂度$O(C)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        int l1 = word1.size(), l2 = word2.size();
        if (l1 != l2)
            return false;
        vector<int> v1(26), v2(26);
        for (char c : word1)
            v1[c - 'a']++;
        for (char c : word2)
            v2[c - 'a']++;
        for (int i = 0; i < 26; ++i)
            if ((v1[i] > 0) ^ (v2[i] > 0))
                return false;
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        for (int i = 0; i < 26; ++i)
            if (v1[i] != v2[i])
                return false;
        return true;
    }
};     
```

:::

## Problem C - [将 x 减到 0 的最小操作数](https://leetcode-cn.com/problems/minimum-operations-to-reduce-x-to-zero/)

使用双指针。初始状态左指针在前缀和大于等于$x$的第一个位置处。之后右指针从最右边开始左移，左指针相应向左移动。在过程中不断更新最优解。

- 时间复杂度$O(N)$。
- 空间复杂度$O(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        int sum = 0;
        int l = 0;
        while (l < n && sum < x)
            sum += nums[l++];
        if (sum < x)
            return -1;
        int ans = INT_MAX;
        if (sum == x) {
            ans = l;
            if (l == n)
                return n;
        }
        int rsum = 0;
        for (int r = n - 1; r >= 0; --r) {
            rsum += nums[r];
            while (l >= 1 && rsum + sum > x)
                sum -= nums[--l];
            if (sum + rsum == x)
                ans = min(ans, n - r + l);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
```

:::

## Problem D - [最大化网格幸福感](https://leetcode-cn.com/problems/maximize-grid-happiness/)

较麻烦的三进制状态压缩动态规划。可以利用类似滑动窗口（或者叫轮廓线）的方法进一步优化时间复杂度（参见[zerotrac](https://leetcode-cn.com/problems/maximize-grid-happiness/solution/zui-da-hua-wang-ge-xing-fu-gan-by-zerotrac2/)和[newhar](https://leetcode-cn.com/problems/maximize-grid-happiness/solution/you-yi-chong-zhuang-ya-jiao-zuo-hua-dong-chuang-ko/)的题解）。这里仅给出基本的按行动态规划的实现。

- 时间复杂度$O(IE\cdot\max(N,M)\cdot3^{2\cdot\min(N,M)})$。
- 空间复杂度$O(K)$。

::: details 参考代码（C++）

```cpp
int dp[26][26][243];
int three[6] = {1, 3, 9, 27, 81, 243};
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int g[243][243];
int points[3] = {0, 120, 40};
int delta[3][3] = {{0, 0, 0}, {0, -60, -10}, {0, -10, 40}};

class Solution {
public:
    int getMaxGridHappiness(int m, int n, int intro, int extro) {
        if (m < n)
            swap(m, n);
        for (int i = 0; i <= intro; ++i)
            for (int j = 0; j <= extro; ++j)
                for (int k = 0; k < three[n]; ++k)
                    dp[i][j][k] = -1;
        dp[0][0][0] = 0;
        int ans = 0;
        
        auto get_points = [&](int last, int nxt) {
            int pts = 0;
            vector<vector<int>> mat(2, vector<int>(n));
            for (int j = 0; j < n; ++j) {
                mat[0][j] = last % 3;
                last /= 3;
                mat[1][j] = nxt % 3;
                nxt /= 3;
            }
            for (int j = 0; j < n; ++j) {
                pts += points[mat[1][j]];
                pts += delta[mat[0][j]][mat[1][j]];
                if (j + 1 < n)
                    pts += delta[mat[1][j]][mat[1][j + 1]];
            }
            return pts;
        };
        for (int i = 0; i < three[n]; ++i)
            for (int j = 0; j < three[n]; ++j)
                g[i][j] = get_points(i, j);
        
        vector<pair<int, int>> decode(three[n]);
        for (int i = 0; i < three[n]; ++i) {
            int d = i;
            while (d) {
                if (d % 3 == 1)
                    decode[i].first++;
                if (d % 3 == 2)
                    decode[i].second++;
                d /= 3;
            }
        }
        
        for (int i = 0; i < m; ++i) {
            for (int p = intro; p >= 0; --p)
                for (int q = extro; q >= 0; --q) {
                    for (int last = 0; last < three[n]; ++last) {
                        if (dp[p][q][last] == -1)
                            continue;
                        for (int nxt = 1; nxt < three[n]; ++nxt) {
                            auto [a, b] = decode[nxt];
                            if (p + a > intro || q + b > extro)
                                continue;
                            dp[p + a][q + b][nxt] = max(dp[p + a][q + b][nxt], dp[p][q][last] + g[last][nxt]);
                        }
                        dp[p][q][0] = max(dp[p][q][0], dp[p][q][last]);
                        if (last != 0)
                            dp[p][q][last] = -1;
                    }
                }
        }
        for (int i = 0; i <= intro; ++i)
            for (int j = 0; j <= extro; ++j)
                for (int k = 0; k < three[n]; ++k)
                    ans = max(ans, dp[i][j][k]);
        return ans;
    }
};
```

:::

<Utterances />
