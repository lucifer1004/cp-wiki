# Leetcode 第58场双周赛题解

## Problem A - [删除字符使字符串变好](https://leetcode.cn/problems/delete-characters-to-make-fancy-string/)

### 方法一：模拟

如果相同的字母连续出现第三次，则之后每次出现相同的字母都将其删除（也即不插入答案字符串）。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string makeFancyString(string s) {
        string ans;
        char last = '$';
        int cnt = 0;
        for (char c : s) {
            if (c == last) {
                if (++cnt <= 2)
                    ans.push_back(c);
            } else {
                ans.push_back(c);
                last = c;
                cnt = 1;
            }
        }
        return ans;
    }
};
```

:::


## Problem B - [检查操作是否合法](https://leetcode.cn/problems/check-if-move-is-legal/)

### 方法一：模拟

从给定的位置开始枚举8个方向，判断是否能形成“好线段”。具体来说，需要满足下面的要求：

- 中间有至少一个颜色相异的格子
- 结尾处有一个颜色相同的格子

如果找到了一条“好线段”，就可以判定为合法操作。如果所有方向都没有形成“好线段”，就是一个非法操作。

- 时间复杂度为$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
const int d[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const int n = 8;

class Solution {
public:
    bool checkMove(vector<vector<char>>& board, int r, int c, char color) {
        int bw = 'B' + 'W';
        auto valid = [&](int i, int j) {
            return i >= 0 && i < n && j >= 0 && j < n;
        };
        
        for (int k = 0; k < 8; ++k) {
            int nr = r + d[k][0], nc = c + d[k][1];
            int len = 0;
            while (valid(nr, nc) && board[nr][nc] + color == bw) {
                len++, nr += d[k][0], nc += d[k][1];
            }
            if (valid(nr, nc) && board[nr][nc] == color && len > 0)
                return true;
        }
        return false;
    }
};
```

:::


## Problem C - [K 次调整数组大小浪费的最小总空间](https://leetcode.cn/problems/minimum-total-space-wasted-with-k-resizing-operations/)

### 方法一：动态规划

容易发现每次调整大小影响的是一个连续区间。给定一个区间$[l,r]$，我们显然应该将大小设置为这个区间内的最大值，这样的浪费是最少的。

令$dp[i][j]$表示到第$i$个位置为止，共调整了$j$次大小时的最小浪费值。我们从$dp[i][j]$出发，枚举下一个区间的结束位置$nxt$，就可以更新$dp[nxt][j + 1]$。

最后的答案就是$dp[n][k]$，因为多调整一次，浪费的空间一定不会增大，所以最优解一定是在用满$k$次调整时取得。

- 时间复杂度$\mathcal{O}(N^2K)$。
- 空间复杂度$\mathcal{O}(NK)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0;
        int hi = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            hi = max(hi, nums[i]);
            sum += nums[i];
            dp[i + 1][0] = hi * (i + 1) - sum;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                int hi = 0, sum = 0;
                for (int nxt = i + 1; nxt <= n; ++nxt) {
                    hi = max(hi, nums[nxt - 1]);
                    sum += nums[nxt - 1];
                    dp[nxt][j + 1] = min(dp[nxt][j + 1], dp[i][j] + hi * (nxt - i) - sum);
                }
            }
        }
        return dp[n][k];
    }
};
```

:::

## Problem D - [两个回文子字符串长度的最大乘积](https://leetcode.cn/problems/maximum-product-of-the-length-of-two-palindromic-substrings/)

### 方法一：Manacher算法

考虑数据规模$10^5$，容易想到使用线性的Manacher算法来求出每个位置为中心时的最长回文串长度。因为题目规定了必须是长度为奇数的回文串，所以也就不需要进行插入特殊字符这种操作。

题目要求两个回文子字符串不能重叠，那么，我们只要分别求出$S$的每个前缀包含的最长回文串长度，以及每个后缀包含的最长回文串长度，就可以枚举前缀来求出最大值了。

问题的关键就变为了，如何利用Manacher算法的结果来求出前缀包含的最长回文串长度。

容易想到递推，但会遇到一个问题，有可能一个回文串超过了当前前缀的长度，那么自然不能直接用它的长度。应该怎么处理呢？注意到，对于所有超过当前前缀长度的回文串，由于受到了当前前缀的限制，它们的最大长度（单侧）即为中心位置到当前前缀结尾的距离，所以，能够形成的最长回文串必然是由最靠前的一个这样的回文串所形成的。因此，我们用单指针指向第一个长度超出当前前缀长度的回文串中心位置即可。如果当前指针指向的位置的回文串已经被完全覆盖，我们就继续后移直到找到下一个符合条件的位置。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
vector<int> manacher_pre(const string &s) {
    int n = s.size();
    vector<int> a(n), hi(n, 1);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int j = (i > r) ? 1 : min(a[l + r - i], r - i + 1);
        while (i >= j && i + j < n && s[i - j] == s[i + j])
            j++;
        a[i] = j--;
        if (i + j > r) {
            l = i - j;
            r = i + j;
        }
    } // Manacher算法，因为只考虑奇数长度的回文串，不需要对原串进行插入特殊字符的操作
    int chi = 0; // 单指针，指向当前第一个没有被覆盖的回文串的中心位置
    for (int i = 0; i < n; ++i) {
        if (i >= 1)
            hi[i] = hi[i - 1];
        while (chi + a[chi] - 1 < i) // 被覆盖，右移指针寻找下一个没有被覆盖的中心位置
            chi++;
        hi[i] = max(hi[i], i - chi + 1);
    }
    return hi;
}

class Solution {
public:
    long long maxProduct(string s) {
        int n = s.size();
        string rs(s.rbegin(), s.rend());
        auto lhi = manacher_pre(s), rhi = manacher_pre(rs); // lhi为前缀包含的最大回文串长度（单侧），rhi为后缀包含的最大回文串长度（单侧）
        long long ans = 1;
        for (int i = 0; i < n - 1; ++i) // 枚举前缀
            ans = max(ans, 1LL * (2 * lhi[i] - 1) * (2 * rhi[n - 2 - i] - 1)); 
        return ans;
    }
};
```

> 代码中运行了两次Manacher，实际上是没有必要的，这里这样写是可以节约一些代码量。

:::

<Utterances />
