# Leetcode 第219场周赛题解

## Problem A - [比赛中的配对次数](https://leetcode.cn/problems/count-of-matches-in-tournament/)

显然一场比赛淘汰一个队伍，所以淘汰$N-1$个队伍需要$N-1$场比赛。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numberOfMatches(int n) {
        return n - 1;
    }
};
```

:::

## Problem B - [十-二进制数的最少数目](https://leetcode.cn/problems/partitioning-into-minimum-number-of-deci-binary-numbers/)

因为并没有限制单个“十=二进制数”中1的个数，所以我们找出原数字中最大的一位即为答案。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）
```cpp
class Solution {
public:
    int minPartitions(string n) {
        return *max_element(n.begin(), n.end()) - '0';
    }
};
```
:::

## Problem C - [石子游戏 VII](https://leetcode.cn/problems/stone-game-vii/)

区间DP。首先预处理出石子数的前缀和，然后按照区间长度从小到大进行动态规划。我们发现，移掉一个石子之后，可以看成是新区间上的一场新游戏，只是先后手互换，因此最后的得分应当取为相反数。

从而转移方程为：

$$
dp[l][r]=\max(\sum_{i=l+1}^r stones[i] - dp[l+1][r], \sum_{i=l}^{r-1} stones[i] - dp[l][r-1])
$$

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）
```cpp
int dp[1005][1005];

class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        for (int i = 1; i <= n; ++i)
            dp[i][i] = 0;
        vector<int> sum {0};
        for (int stone : stones)
            sum.emplace_back(sum.back() + stone);
        for (int len = 2; len <= n; ++len)
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                dp[l][r] = max(sum[r] - sum[l] - dp[l + 1][r], sum[r - 1] - sum[l - 1] - dp[l][r - 1]);
            }
        return dp[1][n];
    }
};
```
:::

## Problem D - [堆叠长方体的最大高度](https://leetcode.cn/problems/maximum-height-by-stacking-cuboids/)

考虑两个长方体，假设其三边分别为$(a_1,b_1,c_1)$和$(a_2,b_2,c_2)$。这里不妨假设$a_1\leq b_1\leq c_1$，$a_2\leq b_2\leq c_2$。

我们可以发现，假设两个长方体能够拼接到一起（不妨假设第一个长方体较小），则必然有：

$$
a_1\leq a_2,b_1\leq b_2,c_1\leq c_2
$$

进一步地，我们可以发现，如果两个长方体是能够拼接在一起的，则它们可以从**任何**一个面进行拼接。

本题允许我们任意旋转长方体，看起来我们需要讨论6种排列情况，但实际上，因为我们希望高度尽可能高，所以根据上面的观察，我们应该选择从较短的两条边组成的面进行拼接。

因此，我们进行两次排序：

1. 将每个长方体的三边升序排列。
2. 将所有长方体升序排列（这里是按照长宽高递增来考虑的，显然，这与题目中的描述是等价的）。因为最优解下，长方体从小到大排列的次序必然是升序排列，所以这一步排序可以保证我们能够得到最优解。

之后，我们就可以进行朴素的$\mathcal{O}(N^2)$动态规划了。对于第$i$个长方体，我们依次考虑第$[1\dots i-1]$个长方体，看看是否能够将第$i$个长方体拼接在它的下方，然后更新当前的最大值。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 题外话
一开始没注意到高度也有约束，折腾了好久……大家有时间不妨也思考下，如果没有对高度的约束，应该怎么做。比赛时我想了几种方法都不行，欢迎大家和我讨论。
:::

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        int n = cuboids.size();
        for (auto &c : cuboids)
            sort(c.begin(), c.end());
        sort(cuboids.begin(), cuboids.end());
        vector<int> dp(n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j)
                if (cuboids[j][1] <= cuboids[i][1] && cuboids[j][2] <= cuboids[i][2])
                    dp[i] = max(dp[i], dp[j]);
            dp[i] += cuboids[i][2];
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

:::

<Utterances />
