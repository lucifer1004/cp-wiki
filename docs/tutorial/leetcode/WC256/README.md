# Leetcode 第256场周赛题解

## Problem A - [学生分数的最小差值](https://leetcode-cn.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/)

### 方法一：贪心

想要差值最小，一定是选择排序后连续的$K$个学生，因此排序后枚举即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        arr = sorted(nums)
        return min(arr[i + k - 1] - arr[i] for i in range(len(nums) - k + 1))
```

:::

## Problem B - [找出数组中的第 K 大整数](https://leetcode-cn.com/problems/find-the-kth-largest-integer-in-the-array/)

### 方法一：排序

直接排序得到答案。

- 时间复杂度$\mathcal{O}(N\log N)$。此处将大整数的运算视为常数。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def kthLargestNumber(self, nums: List[str], k: int) -> str:
        return str(sorted(map(int, nums), reverse=True)[k - 1])
```

:::

## Problem C - [完成任务的最少工作时间段](https://leetcode-cn.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/)

### 方法一：状态压缩动态规划

本题为NP Hard，在$N$较小时可以使用状态压缩动态规划求解。

为了节约时间，预处理计算出每一个子集的和。之后采用枚举子集的方式进行动态规划即可。

- 时间复杂度$\mathcal{O}(N\cdot2^N+3^N)$。
- 空间复杂度$\mathcal{O}(2^N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        vector<int> sum(1 << n);
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    sum[i] = sum[i ^ (1 << j)] + tasks[j];
                    break;
                }
            }
        }
        
        vector<int> dp(1 << n, 1e9);
        dp[0] = 0;
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = i; j; j = (j - 1) & i) {
                if (sum[j] > sessionTime)
                    continue;
                dp[i] = min(dp[i], dp[i ^ j] + 1);
            }
        }
        
        return dp[(1 << n) - 1];
    }
};
```

:::

## Problem D - [不同的好子序列数目](https://leetcode-cn.com/problems/number-of-unique-good-subsequences/)

### 方法一：动态规划

在经典的 [940. 不同的子序列 II](https://leetcode-cn.com/problems/distinct-subsequences-ii/)代码基础上稍作改动即可。

- 如果当前位置为`0`，不额外加上$1$，也即不考虑所有以`0`开始的子序列。
- 单独处理单个`0`的这种情况。

复杂度：

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int numberOfUniqueGoodSubsequences(string binary) {
        vector<ll> dp(2);
        ll ans = 0;
        bool has_zero = false;
        for (char c : binary) {
            int ch = c - '0';
            if (ch == 0)
                has_zero = true;
            ll curr = (ans + ch - dp[ch] + MOD) % MOD;
            ans = (ans + curr) % MOD;
            dp[ch] = (dp[ch] + curr) % MOD;
        }
        if (has_zero)
            ans = (ans + 1) % MOD;
        
        return ans;
    }
};
```

:::

<Utterances />
