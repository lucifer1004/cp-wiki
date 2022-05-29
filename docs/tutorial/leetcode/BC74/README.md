# Leetcode 第74场双周赛题解

## Problem A - [将数组划分成相等数对](https://leetcode.cn/problems/divide-array-into-equal-pairs/)

### 方法一：计数

统计并检查是否所有数字都出现了偶数次。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def divideArray(self, nums: List[int]) -> bool:
        return all(x % 2 == 0 for x in collections.Counter(nums).values())
```

:::

## Problem B - [字符串中最多数目的子字符串](https://leetcode.cn/problems/maximize-number-of-subsequences-in-a-string/)

### 方法一：分情况讨论

分两个字母一样和不一样两种情况讨论。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumSubsequenceCount(self, text: str, pattern: str) -> int:
        if pattern[0] == pattern[1]:
            n = text.count(pattern[0])
            return n * (n + 1) // 2
        else:
            na = text.count(pattern[0])
            nb = text.count(pattern[1])
            ans = max(na, nb)
            for ch in text:
                if ch == pattern[1]:
                    nb -= 1
                if ch == pattern[0]:
                    ans += nb
            return ans
```

:::

## Problem C - [将数组和减半的最少操作次数](https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/)

### 方法一：优先队列+贪心

每次将当前最大的数字减半即可。为避免小数，将所有数左移 32 位。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
from heapq import *

class Solution:
    def halveArray(self, nums: List[int]) -> int:
        s = sum(nums) << 32
        tot = 0
        nums = [-(num << 32) for num in nums]
        heapify(nums)
        ans = 0
        while tot * 2 < s:
            large = heappop(nums)
            tot -= large / 2
            heappush(nums, large / 2)
            ans += 1
        return ans
```

:::

## Problem D - [用地毯覆盖后的最少白色砖块](https://leetcode.cn/problems/minimum-white-tiles-after-covering-with-carpets/)

### 方法一：动态规划

$dp[i][j]$ 表示前 $i$ 块瓷砖用 $j$ 块地毯覆盖后的最少白色砖块数。

复杂度：

- 时间复杂度$\mathcal{O}(NK)$。
- 空间复杂度$\mathcal{O}(NK)$。

::: details 参考代码（C++）

```cpp
const int INF = 1e9;

class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int n = floor.size();
        if (numCarpets * carpetLen >= n)
            return 0;
        
        vector<vector<int>> dp(n + 1, vector<int>(numCarpets + 1, INF));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            int last = max(0, i - carpetLen);
            
            for (int j = 0; j < numCarpets; ++j)
                dp[i][j + 1] = min(dp[i][j + 1], dp[last][j]);
            
            int extra = floor[i - 1] - '0';
            for (int j = 0; j <= numCarpets; ++j)
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + extra);
        }
        
        return dp[n][numCarpets];
    }
};
```

:::

<Utterances />
