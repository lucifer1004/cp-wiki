# Leetcode 第196场周赛题解

## Problem A - [判断能否形成等差数列](https://leetcode.cn/problems/can-make-arithmetic-progression-from-sequence/)

排序后检查相邻两项的差是否都相等。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int d = arr[1] - arr[0];
        for (int i = 1; i + 1 < arr.size(); ++i)
            if (arr[i + 1] - arr[i] != d)
                return false;
        return true;
    }
};
```

:::

## Problem B - [所有蚂蚁掉下来前的最后一刻](https://leetcode.cn/problems/last-moment-before-all-ants-fall-out-of-a-plank/)

这道题有点脑筋急转弯的意思。看起来要处理非常繁琐的碰撞过程，但实际上两只蚂蚁碰撞时，可以视为什么事都没有发生。原因在于：两只蚂蚁相遇时，它们已经走的总时间必然是相等的。假设A蚂蚁本来还需要走$t_A$，B蚂蚁本来还需要走$t_B$，则这两只蚂蚁的总用时分别为$t_0+t_A$和$t_0+t_B$；那么交换方向之后，这两只蚂蚁的总用时变为$t_0+t_B$和$t_0+t_A$。因此，无论中间发生多少次碰撞，$N$只蚂蚁各自总用时的集合是不变的。所以只要按照每只蚂蚁单独走的情形，计算最长用时即可。

::: details 参考代码（Python3）

```python
class Solution:
    def getLastMoment(self, n: int, left: List[int], right: List[int]) -> int:
        return max(0 if len(left) == 0 else max(left), 0 if len(right) == 0 else n - min(right))
```

:::

## Problem C - [统计全 1 子矩形](https://leetcode.cn/problems/count-submatrices-with-all-ones/)

方法一：动态规划

$dp[i][j][k]$表示右下角为$(i,j)$，高度为$k$的矩形的数目。显然，$dp[i][j][k]$可以由$dp[i][j-1][k]$递推得到。

::: details 参考代码（C++）

```cpp
int dp[155][155][155];

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        int ans = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (mat[i - 1][j - 1] == 0)
                    continue;
                for (int k = 1; k <= i; ++k) {
                    if (mat[i - k][j - 1] == 0)
                        break;
                    dp[i][j][k] = 1 + dp[i][j - 1][k];
                    ans += dp[i][j][k];
                }
            }
        }
        return ans;
    }
};
```

:::

方法二：单调栈

令$f[i][j]$表示以$(i,j)$为结尾的最长连续1串的长度，显然可以通过递推在$O(nm)$时间内求出。

接下来，我们遍历每一列，考虑最右边为该列的矩形的个数。

对于任意一列，原问题就变成了对于高度序列$\{f[1][j],\cdots,f[n][j]\}$，求出能够构成的矩形数目。这一问题可以通过单调栈的方式在$O(n)$时间内求解。因此，总的时间复杂度为$O(nm)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> f(n + 2, vector<int>(m + 1));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (mat[i - 1][j - 1] == 1)
                    f[i][j] = f[i][j - 1] + 1;
            }
        int ans = 0;
        for (int j = 1; j <= m; ++j) {
            stack<pair<int, int>> st;
            for (int i = 1; i <= n + 1; ++i) {
                int pos = i;
                while (!st.empty() && st.top().first > f[i][j]) {
                    auto [h, left] = st.top();
                    st.pop();
                    int last = st.empty() ? 0 : st.top().first;
                    int h0 = max(last, f[i][j]);
                    int len = i - left;
                    ans += (h - h0) * len * (len + 1) / 2;
                    pos = left;
                }
                if (st.empty() || st.top().first < f[i][j])
                    st.push({f[i][j], pos});
            }
        }
        return ans;
    }
};
```

:::

## Problem D - [最多 K 次交换相邻数位后得到的最小整数](https://leetcode.cn/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/)

显然，从贪心的角度考虑，我们应该尽可能把最小的数移到最前面。但是由于有步数限制，我们不一定能取到最小的数。因此，使用$10$个`set`分别维护$0\cdots9$的位置。

我们从最高位开始取数，每次从$0$开始，如果对应数字的位置中的最小位置与当前位置的距离不超过剩余交换次数，就选择该数进行交换。

需要注意的是，在进行了交换之后，部分数的位置会发生变化，因此用一个树状数组维护位置的变化量，以计算准确的位置。

::: details 参考代码（C++）

```cpp
class Solution {
    int n;
    vector<int> a;
    int lowbit(int x) {
        return x & (-x);
    }
    void update(int idx, int delta) {
        for (; idx <= n; idx += lowbit(idx))
            a[idx] += delta;
    }
    int query(int idx) {
        int ans = 0;
        for (; idx > 0; idx -= lowbit(idx))
            ans += a[idx];
        return ans;
    }
public:
    string minInteger(string num, int k) {
        vector<set<int>> s(10);
        n = num.size();
        string ans;
        a = vector<int>(n + 1);
        for (int i = 0; i < n; ++i)
            s[num[i] - '0'].insert(i);
        int idx = 0, left = 0;
        vector<bool> vis(n);
        while (idx < n) {
            int curr = num[idx] - '0';
            int m = idx;
            for (int j = 0; j < curr; ++j) {
                if (s[j].empty())
                    continue;
                int p = *s[j].begin();
                int d = (p + query(p + 1)) - (idx + query(idx + 1));
                if (d > k)
                    continue;
                else {
                    m = p;
                    k -= d;
                    break;
                }
            }
            if (m != idx) {
                vis[m] = true;
                left++;
                update(idx + 1, 1);
                update(m + 1, -1);
            } else {
                vis[idx] = true;
                while (idx < n && vis[idx])
                    idx++;
            }
            ans.push_back(num[m]);
            s[num[m] - '0'].erase(m);
        }
        return ans;
    }
};
```

:::

<Utterances />
