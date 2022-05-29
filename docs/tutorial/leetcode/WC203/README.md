# Leetcode 第203场周赛题解

## Problem A - [圆形赛道上经过次数最多的扇区](https://leetcode.cn/problems/most-visited-sector-in-a-circular-track/)

可以直接模拟，但其实只需要考虑起点和终点。如果起点小于等于终点，那么多走的就是起点到终点这一段；否则，多走的就是起点到$n$，然后$1$到终点。注意要求升序返回，所以对于第二种情况，把两段的位置颠倒一下即可。

::: details 参考代码（Python3）

```python
class Solution:
    def mostVisited(self, n: int, rounds: List[int]) -> List[int]:
        return list(range(rounds[0], rounds[-1] + 1)) if rounds[0] <= rounds[-1] else (list(range(1, rounds[-1] + 1)) + list(range(rounds[0], n + 1)))
```

:::

## Problem B - [你可以获得的最大硬币数目](https://leetcode.cn/problems/maximum-number-of-coins-you-can-get/)

贪心。每次把当前最大的给Alice，最小的给Bob，次大的给自己。降序排列后，取第$2,4,6,\cdots,2n$项即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        int n = piles.size() / 3;
        sort(piles.rbegin(), piles.rend());
        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans += piles[1 + i * 2];
        return ans;
    }
};
```

:::

## Problem C - [查找大小为 M 的最新分组](https://leetcode.cn/problems/find-latest-group-of-size-m/)

用一个数组记录当前每种长度的1串的个数，用并查集维护串的长度。

::: details 参考代码（C++）

```cpp
class Solution {
    vector<int> sz, f;
    int find(int u) {
        return f[u] == u ? u : f[u] = find(f[u]);
    }

    void connect(int u, int v) {
        int fu = find(u), fv = find(v);
        if (fu == fv)
            return;
        if (sz[fu] >= sz[fv]) {
            f[fv] = fu;
            sz[fu] += sz[fv];
        } else {
            f[fu] = fv;
            sz[fv] += sz[fu];
        }
    }
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        sz = vector<int>(n + 1);
        f = vector<int>(n + 1);
        vector<int> len(n + 1);
        int ans = -1, turn = 0;
        for (int i : arr) {
            turn++;
            sz[i] = 1;
            f[i] = i;
            len[1]++;
            if (i > 1 && sz[i - 1]) {
                len[sz[find(i - 1)]]--;
                len[sz[find(i)]]--;
                connect(i, i - 1);
                len[sz[find(i)]]++;
            }
            if (i < n && sz[i + 1]) {
                len[sz[find(i + 1)]]--;
                len[sz[find(i)]]--;
                connect(i, i + 1);
                len[sz[find(i)]]++;
            }
            if (len[m])
                ans = turn;
        }
        return ans;
    }
};
```

:::

## Problem D - [石子游戏 V](https://leetcode.cn/problems/stone-game-v/)

本题是典型的区间DP问题。很容易想到用$dp[l][r]$为$[l,r]$区间内进行游戏能够取得的最大值，然后枚举分割点，更新结果即可。这样的时间复杂度是$O(n^3)$。

一般来说，这样的问题有递推和记忆化递归两种实现方式。通常我们会觉得这两种方法是等价的，但这道题比赛时我用的$O(n^3)$递推超时了好几次，而比赛后发现很多人用的记忆化递归却轻松通过了。区别在哪里呢？在递推过程中，所有状态都会被求解出来；而在记忆化递归过程中，有一些无效的状态是不会被访问到的，这样就节约了大量的时间。比赛后，我模拟了$100$次$N=500$时随机数组的求解情况，记忆化递归的递归函数平均调用次数只有$1.3\times10^6$，最大也不过$1.4\times10^6$，远远小于$500^3=1.25\times10^8$；而相比之下，递推则是实打实计算了所有的状态，一个都没有漏。

我们可以进行一些感性的分析。在枚举分割点的过程中，因为我们每次取的都是数值更小的那半边，假定所有数的大小差不多，就相当于是取了长度更短的那一半，也就是说，在递归过程中，问题规模实际上至少是减半的。当然，可以构造出极端数据，比如$[2^n,2^{n-1},\cdots,2,1,1,2,\cdots,2^{n-1},2^n]$，这组数据的递归用时是随机数据的四倍，并且随着$n$增大，严格按照$n^3$增长。

::: details 参考代码：记忆化递归（Python3）

```python
from functools import lru_cache

class Solution:
    def stoneGameV(self, s: List[int]) -> int:
        pre = [0]
        for i in s:
            pre.append(pre[-1] + i)

        @lru_cache(None)
        def dfs(l, r):
            if l == r:
                return 0
            ans = 0
            for k in range(l, r):
                left = pre[k] - pre[l - 1]
                right = pre[r] - pre[k]
                if left < right:
                    ans = max(ans, left + dfs(l, k))
                elif left > right:
                    ans = max(ans, right + dfs(k + 1, r))
                else:
                    ans = max(ans, left + max(dfs(l, k), dfs(k + 1, r)))
            return ans

        return dfs(1, len(s))
```

:::

当然，这道题还有复杂度更优的，$O(n^2)$的算法。容易想到，对于固定的区间$[l,r]$，随着分割点$k$从做向右移动，一定会有一个转折点，使得从取左边一半变为从右边一半。在$O(n^3)$的方法中，我们实际上是从左到右遍历了一遍，但实际上，我们只需要考虑转折点和其右边一点的情况即可。这里，我们定义转折点为满足$sum[l,k]\leq sum[k+1,r]$的最大的$k$。容易发现，固定$l$，随着$r$增大，转折点单调增大，因此我们可以遍历$l$，用$O(n^2)$的时间求出所有转折点$mid[l][r]$。

但要注意的是，我们并不能直接使用$dp[l][k]+sum[l][k]$来代表转折点左边的情况，因为完全有可能$dp[l][k-1]+sum[l][k-1]>dp[l][k]+sum[l][k]$，这时就会导致错过最优解。同理，右边也是如此。

因此，我们还需要额外用两个数组来记录这一最大值，它们分别为$L[l][r]=\max_{i=l}^{r}(dp[l][i] + sum[l][i])$，$R[l][r]=\max_{i=l}^{r}(dp[i][r] + sum[i][r])$。这两个数组的更新可以在每次求解得到$dp[l][r]$
后顺带进行。

所以，我们虽然只考虑了转折点和其右边一点，但实际上转折点$k$处的$L[l][k]$代表了它和它左边所有的取法中的最优解；同样，转折点右边一点处的$R[k+1][r]$代表了它和它右边所有取法中的最优解。看起来我们只讨论了两个位置，但实际上等于考虑了所有的分割点，因此一定可以得到最优解。

::: details 参考代码（C++）

```cpp
# define N 501

class Solution {
    int dp[N][N], L[N][N], R[N][N], mid[N][N], sum[N];
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + stoneValue[i - 1];
            L[i][i] = R[i][i] = stoneValue[i - 1];
        }
        for (int l = 1; l < n; ++l) {
            int idx = l;
            for (int r = l + 1; r <= n; ++r) {
                while (idx < r && sum[idx + 1] - sum[l - 1] <= sum[r] - sum[idx + 1])
                    idx++;
                mid[l][r] = idx;
            }
        }
        for (int len = 2; len <= n; ++len)
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                dp[l][r] = L[l][r] = R[l][r] = 0;
                for (int k = mid[l][r]; k <= mid[l][r] + 1; ++k) {
                    if (k >= r)
                        continue;
                    int left = sum[k] - sum[l - 1];
                    int right = sum[r] - sum[k];
                    if (left < right)
                        dp[l][r] = max(dp[l][r], L[l][k]);
                    else if (left > right)
                        dp[l][r] = max(dp[l][r], R[k + 1][r]);
                    else
                        dp[l][r] = max(dp[l][r], max(L[l][k], R[k + 1][r]));
                }
                L[l][r] = max(L[l][r - 1], dp[l][r] + sum[r] - sum[l - 1]);
                R[l][r] = max(R[l + 1][r], dp[l][r] + sum[r] - sum[l - 1]);
            }
        return dp[1][n];
    }
};
```

:::

<Utterances />
