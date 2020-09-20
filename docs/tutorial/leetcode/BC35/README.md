# Leetcode 第35场双周赛题解

## Problem A - [所有奇数长度子数组的和](https://leetcode-cn.com/problems/sum-of-all-odd-length-subarrays/)

预先计算前缀和，然后枚举所有奇数长度的子数组即可（先枚举长度，再枚举起点；或者先枚举起点，再枚举长度都可以）。

时间复杂度$O(N^2)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def sumOddLengthSubarrays(self, arr: List[int]) -> int:
        n = len(arr)
        s = [0]
        for i in arr:
            s.append(s[-1] + i)
        ans = 0
        for i in range(1, n + 1, 2):
            for j in range(1, n + 1):
                if j + i - 1 > n:
                    break
                ans += s[j + i - 1] - s[j - 1]
        return ans
```

:::

## Problem B - [所有排列中的最大和](https://leetcode-cn.com/problems/maximum-sum-obtained-of-any-permutation/)

显然应当把较大的数放在计数次数较多的位置上。所以我们首先要统计每个位置的计数次数。

因为每次询问是一段连续区间，同时这题的查询是在所有修改之后，所以我们可以用差分数组的方法来进行计数。（如果需要在修改过程中进行查询，就要用树状数组了）。

最后对差分数组求前缀和就能得到每个位置的计数次数。把原数组和计数次数分别按降序排列，然后相乘累加即可得到答案。

总时间复杂度$O(N\log N)$（因为要排序）。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size();
        vector<int> d(n + 2);
        for (auto v : requests) {
            int l = v[0] + 1, r = v[1] + 1;
            d[l]++;
            d[r + 1]--;
        }
        vector<int> t(n);
        t[0] = d[1];
        for (int i = 1; i < n; ++i)
            t[i] = t[i - 1] + d[i + 1];
        sort(t.rbegin(), t.rend());
        sort(nums.rbegin(), nums.rend());
        ll ans = 0;
        for (int i = 0; i < n; ++i)
            ans = (ans + (ll)nums[i] * t[i]) % MOD;
        return ans;
    }
};
```

:::

## Problem C - [使数组和能被 P 整除](https://leetcode-cn.com/problems/make-sum-divisible-by-p/)

经典的前缀哈希套路题。要使数组和能被$P$整除，就需要去掉一个子数组，这个子数组模$P$的余数和原始数组模$P$的余数相等。

所以问题就变成了，求一个最短的模$P$余$X$的子数组。用前缀哈希记录每一个余数的前缀的最长长度即可。

时间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int ans = -1;
        unordered_map<int, int> last;
        ll sum = 0;
        for (int num : nums)
            sum += num;
        int target = sum % p;
        if (target == 0)
            return 0;
        last[0] = 0;
        int n = nums.size();
        ll now = 0;
        for (int i = 1; i <= n; ++i) {
            now += nums[i - 1];
            now %= p;
            ll need = (now - target + p) % p;
            if (last.count(need)) {
                int len = i - last[need];
                if (ans == -1)
                    ans = len;
                else
                    ans = min(ans, len);
            }
            last[now] = i;
        }
        return ans == n ? -1 : ans;
    }
};
```

:::

## Problem D - [奇怪的打印机 II](https://leetcode-cn.com/problems/strange-printer-ii/)

首先，我们可以找出每种颜色对应的最左、最右、最上和最下位置，从而确定其所覆盖的矩形范围。

接下来，我们枚举颜色对，检查这两种颜色的矩形是否有交集。如果矩形存在交集，则检查交集中的颜色，如果交集中这两种颜色都有，则本题无解；否则，交集中有的那种颜色需要后涂色，这时我们就连一条从后涂色的颜色向先涂色的颜色的有向边。

最后，我们对颜色图进行拓扑排序，如果可以得到一个合法的拓扑序列，则本题有解。

时间复杂度$O(NMC^2)$。

::: details 参考代码（C++）

```cpp
#define C 60
#define INF 0x3f3f3f3f

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        int n = targetGrid.size(), m = targetGrid[0].size();
        vector<int> l(C + 1, INF), r(C + 1, 0), u(C + 1, INF), d(C + 1, 0);
        vector<bool> vis(C + 1);
        vector<vector<int>> adj(C + 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                int c = targetGrid[i][j];
                vis[c] = true;
                l[c] = min(l[c], j + 1);
                r[c] = max(r[c], j + 1);
                u[c] = min(u[c], i + 1);
                d[c] = max(d[c], i + 1);
            }
        vector<int> in(C + 1);
        int cnt = 0;
        for (int i = 1; i <= C; ++i) {
            if (!vis[i])
                continue;
            cnt++;
            for (int j = 1; j <= C; ++j) {
                if (!vis[j] || i == j)
                    continue;
                int L = max(l[i], l[j]), R = min(r[i], r[j]);
                int U = max(u[i], u[j]), D = min(d[i], d[j]);
                bool vi = false, vj = false;
                for (int p = U; p <= D; ++p)
                    for (int q = L; q <= R; ++q) {
                        if (targetGrid[p - 1][q - 1] == i)
                            vi = true;
                        if (targetGrid[p - 1][q - 1] == j)
                            vj = true;
                    }
                if (vi && vj)
                    return false;
                if (vi)
                    adj[i].emplace_back(j), in[j]++;
                if (vj)
                    adj[j].emplace_back(i), in[i]++;
            }
        }
        queue<int> q;
        for (int i = 1; i <= C; ++i)
            if (vis[i] && in[i] == 0)
                q.push(i);
        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.emplace_back(u);
            for (int v : adj[u]) {
                in[v]--;
                if (in[v] == 0)
                    q.push(v);
            }
        }
        return cnt == (int)topo.size();
    }
};
```

:::

<Utterances />
