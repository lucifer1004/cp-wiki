# Leetcode 第203场周赛题解

## Problem A - [圆形赛道上经过次数最多的扇区](https://leetcode-cn.com/problems/most-visited-sector-in-a-circular-track/)

可以直接模拟，但其实只需要考虑起点和终点。如果起点小于等于终点，那么多走的就是起点到终点这一段；否则，多走的就是起点到$n$，然后$1$到终点。注意要求升序返回，所以对于第二种情况，把两段的位置颠倒一下即可。

::: spoiler 参考代码（Python3）

```python
class Solution:
    def mostVisited(self, n: int, rounds: List[int]) -> List[int]:
        return list(range(rounds[0], rounds[-1] + 1)) if rounds[0] <= rounds[-1] else (list(range(1, rounds[-1] + 1)) + list(range(rounds[0], n + 1)))
```

:::

## Problem B - [你可以获得的最大硬币数目](https://leetcode-cn.com/problems/maximum-number-of-coins-you-can-get/)

贪心。每次把当前最大的给Alice，最小的给Bob，次大的给自己。降序排列后，取第$2,4,6,\cdots,2n$项即可。

::: spoiler 参考代码（C++）

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

## Problem C - [查找大小为 M 的最新分组](https://leetcode-cn.com/problems/find-latest-group-of-size-m/)

用一个数组记录当前每种长度的1串的个数，用并查集维护串的长度。

::: spoiler 参考代码（C++）

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

## Problem D - [石子游戏 V](https://leetcode-cn.com/problems/stone-game-v/)

::: spoiler 参考代码（C++）

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
