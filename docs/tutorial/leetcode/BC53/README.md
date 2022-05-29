# Leetcode 第53场双周赛题解

## Problem A - [长度为三且各字符不同的子字符串](https://leetcode.cn/problems/substrings-of-size-three-with-distinct-characters/)

### 方法一：暴力

本题数据范围较小，因此暴力枚举即可。如果数据规模更大，同时子字符串长度从$3$变为$k$，则可以使用滑动窗口来进行优化。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countGoodSubstrings(string s) {
        int ans = 0;
        for (int i = 0; i + 2 < s.size(); ++i)
            if (s[i] != s[i + 1] && s[i] != s[i + 2] && s[i + 1] != s[i + 2])
                ans++;
        return ans;
    }
};
```

:::

Python一行解法：

::: details 参考代码（Python 3）

```python
class Solution:
    def countGoodSubstrings(self, s: str) -> int:
        return len([i for i in range(len(s) - 2) if len(set(s[i:i + 3])) == 3])
```

:::

::: tip 注意

这一解法的空间复杂度并不是$\mathcal{O}(1)$。

:::

## Problem B - [数组中最大数对和的最小值](https://leetcode.cn/problems/minimize-maximum-pair-sum-in-array/)

### 方法一：贪心

显然，我们应当将最大元素和最小元素配对，否则无论将最大元素与其他哪一个元素配对，数对和都不会更小。依次类推，我们需要把第二大的元素和第二小的元素配对，第三大的元素和第三小的元素配对……

- 时间复杂度为$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        for (int i = 0; i < n / 2; ++i)
            ans = max(ans, nums[i] + nums[n - i - 1]);
        return ans;
    }
};
```

:::

Python一行解法：

::: details 参考代码（Python 3）

```python
class Solution:
    def minPairSum(self, nums: List[int]) -> int:
        return max(a + b for a, b in zip(sorted(nums), sorted(nums)[::-1]))
```

:::

::: tip 注意

这一解法的空间复杂度并不是$\mathcal{O}(1)$。

:::

## Problem C - [矩阵中最大的三个菱形和](https://leetcode.cn/problems/get-biggest-three-rhombus-sums-in-a-grid/)

### 方法一：前缀和

令$l[i][j][k]$表示从$(i,j)$开始，向左上方走$k$步的和；$r[i][j][k]$表示从$(i,j)$开始，向右上方走$k$步的和。借鉴前缀和的做法，我们可以在$\mathcal{O}(NM\min(N,M))$的时间里求出这些和。

题目要求三个最大的不同的菱形和，因此我们使用一个`set`来存储这些和，每当`set`中元素超过$3$个，我们就删去最小的那个值。因为任意时刻`set`中的元素数目不会超过$4$个，所以所有对`set`的操作的时间复杂度可以视为$\mathcal{O}(1)$。

我们可以枚举菱形最下方的点和菱形的大小来遍历所有的菱形。设菱形最下方的点为$(i,j)$。对于一个面积不为$0$的菱形，其边界上的元素之和可以表示为四边的元素和减去四个顶点的元素和。而四边的元素和可以借助上面求出的前缀和快速获得。这样我们就可以在$\mathcal{O}(1)$时间内求得这一菱形的边界元素和。总共有$\mathcal{O}(NM\min(N,M))$个这样的菱形，因此总的时间复杂度也为$\mathcal{O}(NM\min(N,M))$。

注意面积为$0$的菱形需要单独处理。

- 时间复杂度$\mathcal{O}(NM\min(N,M))$。
- 空间复杂度$\mathcal{O}(NM\min(N,M))$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int h = min(n, m);
        vector<vector<vector<int>>> l(n, vector<vector<int>>(m, vector<int>(h)));
        vector<vector<vector<int>>> r(l);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                l[i][j][0] = r[i][j][0] = grid[i][j];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                for (int k = 1; i + k < n && j + k < m; ++k)
                    l[i + k][j + k][k] = l[i + k - 1][j + k - 1][k - 1] + grid[i + k][j + k]; 
                for (int k = 1; i + k < n && j - k >= 0; ++k)
                    r[i + k][j - k][k] = r[i + k - 1][j - k + 1][k - 1] + grid[i + k][j - k];
            }
        set<int> pq;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                pq.insert(grid[i][j]);
                if (pq.size() > 3)
                    pq.erase(pq.begin());
                for (int k = 1; i - k * 2 >= 0 && j - k >= 0 && j + k < m; ++k) {
                    int s = l[i][j][k] + r[i][j][k] + r[i - k][j - k][k] + l[i - k][j + k][k] - grid[i][j] - grid[i - k][j - k] - grid[i - k][j + k] - grid[i - 2 * k][j];
                    pq.insert(s);
                    if (pq.size() > 3)
                        pq.erase(pq.begin());
                }
            }
        return vector<int>(pq.rbegin(), pq.rend());
    }
};
```

:::

## Problem D - [两个数组最小的异或值之和](https://leetcode.cn/problems/minimum-xor-sum-of-two-arrays/)

### 方法一：状态压缩动态规划

看到$n=14$，考虑使用状态压缩动态规划。

本题中的状态是很显然的，我们可以用$state$表示当前`nums2`数组中元素的使用情况。对于给定的$state$，我们可以选择一个尚未使用的元素（设其为`nums2`的第$k$个元素，则需要满足$state\ \&\ 2^k=0$）与`nums1`的当前元素配对，从而进行状态转移（$state\rightarrow state\ |\ 2^k$）。

初值为$dp[0]=0$，其余为$\infty$。

- 时间复杂度$\mathcal{O}(N^2\cdot2^N)$。
- 空间复杂度$\mathcal{O}(2^N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = (1 << n) - 1; j >= 0; --j) {
                if (dp[j] < INT_MAX) {
                    for (int k = 0; k < n; ++k) {
                        if ((j & (1 << k)) == 0) {
                            int nxt = j ^ (1 << k);
                            dp[nxt] = min(dp[nxt], dp[j] + (nums1[i] ^ nums2[k]));
                        }
                    }
                }
            }
        }
        return dp[(1 << n) - 1];
    }
};
```

:::

事实上，对于一个给定的$state$，我们可以根据其二进制中$1$的个数来求出添加下一个元素时，对应于`nums1`中的第几个元素，从而可以将时间复杂度降低到$\mathcal{O}(N\cdot2^N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i + 1 < (1 << n); ++i) {
            int j = __builtin_popcount(i);
            for (int k = 0; k < n; ++k)
                if (!(i & (1 << k)))
                    dp[i ^ (1 << k)] = min(dp[i ^ (1 << k)], dp[i] + (nums1[j] ^ nums2[k]));
        }
        return dp[(1 << n) - 1];
    }
};
```

:::

<Utterances />
