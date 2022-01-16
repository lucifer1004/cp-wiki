# Leetcode 第276场周赛题解

## Problem A - [将字符串拆分为若干长度为 k 的组](https://leetcode-cn.com/problems/divide-a-string-into-groups-of-size-k/)

### 方法一：模拟

按题意操作即可。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def divideString(self, s: str, k: int, fill: str) -> List[str]:
        n = len(s)
        if n % k != 0:
            s += fill * (k - n % k)
        return [s[t:t+k] for t in range(0, len(s), k)]
```

:::

## Problem B - [得到目标值的最少行动次数](https://leetcode-cn.com/problems/minimum-moves-to-reach-target-score/)

### 方法一：递归倒推

不妨逆向考虑这一问题，此时加一操作变为减一，乘二操作变为除以二。我们从目标值开始。如果当前值为奇数，那么只能使用减一；如果当前值为偶数，且可以进行除以二操作，显然要优于使用减一。

按照这一思路递归求解即可。注意在除以二操作的剩余次数变为零时，可以直接求得结果。

- 时间复杂度 $\mathcal{O}(\log N)$。
- 如不计入递归调用的消耗，空间复杂度为 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minMoves(self, target: int, maxDoubles: int) -> int:
        if target == 1:
            return 0
        if maxDoubles == 0:
            return target - 1
        return self.minMoves(target // 2, maxDoubles - 1) + target % 2 + 1
```

:::

## Problem C - [解决智力问题](https://leetcode-cn.com/problems/solving-questions-with-brainpower/)

### 方法一：动态规划

容易想到动态规划求解。

令 $dp[i]$ 表示第 $i$ 天开始时可以取得的最高分数。显然 $dp[i]=0$，而我们要求的答案即为 $dp[N]$。

- 如果这一天不做题，则直接以当前分数更新第 $i + 1$ 天开始时的最高分数。
- 如果这一天选择做题，则以当前分数加上题目分数的新得分来更新第 $\min(N, i + skip + 1)$ 天开始时的最高分数。在这一天做题的情况下，中间的天数不能再做题，因此它们都被跳过，不需要更新。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n + 1);
        for (int i = 0; i < n; ++i) {
            dp[i + 1] = max(dp[i], dp[i + 1]);
            int nxt = min(i + 1 + questions[i][1], n);
            dp[nxt] = max(dp[nxt], dp[i] + questions[i][0]);
        }
        return dp[n];
    }
};
```

:::

## Problem D - [同时运行 N 台电脑的最长时间](https://leetcode-cn.com/problems/maximum-running-time-of-n-computers/)

### 方法一：二分答案

直接寻找最优安排方案看起来很困难。尝试变换角度：

- 在现有条件的基础上给定天数，判断是否能够维持这些电脑同时运行。

假设目标天数为 $k$。则此时，每块电池最多用 $k$ 天，也即最多供给 $k$ 单位电能。从而所有电池能够供给的总电能为 $\sum\min(k, batteries[i])$。只要这一总和不小于 $Nk$，就说明能够满足要求。

为什么呢？我们可以这样来安排：

将 $k$ 天想象成 $k$ 个队列。现在对于每一块电池，我们从上到下，依次给每个队列分配一单位的电能，如果到达了最下方的队列则从最上方再次开始，直到电池电量耗尽，或已经分配了 $k$ 单位的电能。显然，不会有电池在同一队列中出现两次。另一方面，由于上面计算得到的总和不小于 $Nk$，最后每个队列中的元素数量一定不小于 $N$。

朴素的方法在每次检查时求和，时间复杂度为$\mathcal{O}(M\log\frac{\sum batteries}{N})$。但我们可以进一步优化时间复杂度。在对 $batteries$ 数组排序并计算前缀和后，我们在二分时不再需要遍历所有元素。

- 时间复杂度$\mathcal{O}((M+\log\frac{\sum batteries}{N})\log M)$
- 空间复杂度$\mathcal{O}(M)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        int m = batteries.size();
        sort(batteries.begin(), batteries.end());
        vector<long long> pre(m + 1);
        for (int i = 0; i < m; ++i)
            pre[i + 1] = pre[i] + batteries[i];
        
        auto check = [&](long long mid) {
            int k = upper_bound(batteries.begin(), batteries.end(), mid) - batteries.begin();
            return pre[k] + mid * (m - k) >= mid * n; 
        };
        
        long long lo = 0, hi = pre[m] / n;
        while (lo <= hi) {
            long long mid = (lo + hi) >> 1;
            if (check(mid))
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        
        return hi;
    }
};
```

:::

<Utterances />
