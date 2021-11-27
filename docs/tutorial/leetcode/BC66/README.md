# Leetcode 第66场双周赛题解

## Problem A - [统计出现过一次的公共字符串](https://leetcode-cn.com/problems/count-common-words-with-one-occurrence/)

### 方法一：模拟

按要求计数并判断即可。

- 时间复杂度$\mathcal{O}(|N_1|+|N_2|)$。这里因为字符串有长度限制，所以可以认为哈希操作的时间复杂度为常数。
- 空间复杂度$\mathcal{O}(|N_1|+|N_2|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countWords(self, words1: List[str], words2: List[str]) -> int:
        c1 = collections.Counter(words1)
        c2 = collections.Counter(words2)
        return len([key for key in c1 if c1[key] == 1 and c2[key] == 1])
```

:::


## Problem B - [从房屋收集雨水需要的最少水桶数](https://leetcode-cn.com/problems/minimum-number-of-buckets-required-to-collect-rainwater-from-houses/)

### 方法一：贪心

从左到右遍历，如果可能，尽量将水桶放在房屋右边（这样可能还能为下一栋房屋服务）。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumBuckets(self, street: str) -> int:
        n = len(street)
        ans = 0
        last = -2
        
        for i, ch in enumerate(street):
            if ch == 'H':
                if last == i - 1:
                    continue
                if i + 1 < n and street[i + 1] == '.':
                    last = i + 1
                    ans += 1
                elif i >= 1 and street[i - 1] == '.':
                    last = i - 1
                    ans += 1
                else:
                    return -1
                    
        return ans
```

:::

## Problem C - [网格图中机器人回家的最小代价](https://leetcode-cn.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/)

### 方法一：脑筋急转弯

实际上，我们可以发现在不绕路的情况下，无论怎么走，机器人回家的代价都是恒定的。我们算出这个代价即可。

- 时间复杂度$\mathcal{O}(R+C)$。
- 空间复杂度$\mathcal{O}(R+C)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        int sr = startPos[0], sc = startPos[1];
        int hr = homePos[0], hc = homePos[1];
        
        int ans = 0;
        for (; sr < hr; sr++) {
            ans += rowCosts[sr + 1];
        }
        for (; sr > hr; sr--) {
            ans += rowCosts[sr - 1];
        }
        
        for (; sc < hc; sc++) {
            ans += colCosts[sc + 1];
        }
        for (; sc > hc; sc--) {
            ans += colCosts[sc - 1];
        }
        
        return ans;
    }
};
```

:::

## Problem D - [统计农场中肥沃金字塔的数目](https://leetcode-cn.com/problems/count-fertile-pyramids-in-a-land/)

### 方法一：动态规划

我们只需要考虑正金字塔，之后将原数组倒转再求一遍就能得到倒金字塔的个数。

对于正金字塔来说，令$dp[i][j]$表示以$grid[i][j]$为顶点的金字塔的最大阶数，我们可以发现这样的递推关系：

$$
dp[i][j]=\left\{\begin{aligned}
& \min(dp[i+1][j-1], dp[i+1][j], dp[i+1][j+1]) + 1 & \quad grid[i][j]=1 \\
& 0 & \quad grid[i][j] = 0
\end{aligned}\right.
$$

因此按行逆序递推即可。因为当前行的值只与下一行的结果有关，所以可以用滚动数组来优化空间。

最后的正金字塔总个数即为$\sum \max(0, dp[i][j]-1)$。

再倒转原数组，求出倒金字塔个数，二者相加即为答案。

- 时间复杂度$\mathcal{O}(RC)$。
- 空间复杂度$\mathcal{O}(C)$。

::: details 参考代码（C++）

```cpp
class Solution {
    int count(vector<vector<int>> &grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> dp(m + 2); // 在首尾各增加了一个哨兵位，以避免对边界情况的讨论。
        
        int ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            vector<int> ndp(m + 2);
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 0)
                    continue;
                
                ndp[j + 1] = min(dp[j], min(dp[j + 1], dp[j + 2])) + 1;
                ans += ndp[j + 1] - 1;
            }
            dp = move(ndp); // 滚动数组
        }
        
        return ans;
    }
    
public:
    int countPyramids(vector<vector<int>>& grid) {
        int ans = count(grid);
        reverse(grid.begin(), grid.end());
        ans += count(grid);
        
        return ans;
    }
};
```

:::

<Utterances />
