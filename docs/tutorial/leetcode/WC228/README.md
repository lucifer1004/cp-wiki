# Leetcode 第228场周赛题解

## Problem A - [生成交替二进制字符串的最少操作数](https://leetcode-cn.com/problems/minimum-changes-to-make-alternating-binary-string/)

我们或者将字符串变为`0101...0101`，或者将字符串变成`1010...1010`。所以，我们统计奇数和偶数位置上`0`和`1`的数目，然后选择两种方案中较优的那个即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minOperations(self, s: str) -> int:
        oz = 0
        oo = 0
        ez = 0
        eo = 0
        for i, c in enumerate(s):
            if i % 2 == 0:
                if c == '0':
                    ez += 1
                else:
                    eo += 1
            else:
                if c == '0':
                    oz += 1
                else:
                    oo += 1
        return min(oz + eo, ez + oo)
```

:::

## Problem B - [统计同构子字符串的数目](https://leetcode-cn.com/problems/count-number-of-homogenous-substrings/)

找出每一个最长的由相同字符组成的子串，假设其长度为$L$，则其对答案的贡献为$\frac{L(L+1)}{2}$。

注意最后的结果要取模。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countHomogenous(self, s: str) -> int:
        x = '$'
        cnt = 0
        ans = 0
        for c in s + '#':
            if c == x:
                cnt += 1
            else:
                ans += cnt * (cnt + 1) // 2
                x = c
                cnt = 1
        return ans % 1000000007
```

:::

## Problem C - [袋子里最少数目的球](https://leetcode-cn.com/problems/minimum-limit-of-balls-in-a-bag/)

可能第一反应会考虑每次贪心选取球最多的那个袋子将其分为两半。但本题的操作次数最多可以达到$10^9$，逐次进行模拟显然是不现实的；另一方面，样例1（只有一个袋子，里面装着9个球，最多操作2次）也已经说明这一贪心策略是不对的。如果我们采用贪心方法，得到的结果会是$[9]\rightarrow[5,4]\rightarrow[4,3,2]$，最后的代价是$4$，而按照样例中的方法$[9]\rightarrow[6,3]\rightarrow[3,3,3]$，最后的代价是$3$。

不妨考虑下面这个问题：

如果要求最后的代价不超过$K$，我们最少需要操作多少次？

我们可以先考虑只有一个袋子的情形。假设袋子里有$M>K$个球，为了使代价不超过$K$，同时操作次数尽可能小，我们应当每次分出$K$个球。这样，我们一共需要分$\lfloor\frac{M-1}{K}\rfloor$次。

扩展到$N$个袋子的情形：因为袋子之间没有相互影响，我们只要把每个袋子的结果累加起来即可，也即总共需要$\sum\lfloor\frac{M_i}{K}\rfloor$次。

解决了这一问题，我们就可以利用二分答案的方法来求解原问题了。

- 时间复杂度$\mathcal{O}(N\log MAXN)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumSize(self, nums: List[int], maxOperations: int) -> int:
        lo = 1
        hi = max(nums)
        while lo <= hi:
            mid = (lo + hi) // 2
            tot = 0
            for num in nums:
                tot += (num - 1) // mid
            if tot <= maxOperations:
                hi = mid - 1
            else:
                lo = mid + 1
        return lo
```

:::

## Problem D - [一个图中连通三元组的最小度数](https://leetcode-cn.com/contest/weekly-contest-228/problems/minimum-degree-of-a-connected-trio-in-a-graph/)

### 方法一：暴力

数据范围$N\leq400$是一个典型的$\mathcal{O}(N^3)$范围，所以直接暴力枚举三元组即可。

为了快速判断连通性，可以先把边集转为邻接矩阵。同时我们统计每个点的度数，方便最后计算总度数（对于一个连通三元组，总度数为三个点的总度数减去它们内部的度数，也就是$2\times3=6$）。

- 时间复杂度$\mathcal{O}(N^3)$。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<bool>> d(n, vector<bool>(n));
        vector<int> deg(n);
        for (auto &e : edges) {
            d[e[0] - 1][e[1] - 1] = d[e[1] - 1][e[0] - 1] = true;
            deg[e[0] - 1]++;
            deg[e[1] - 1]++;
        }
        int ans = INT_MAX;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                if (!d[i][j])
                    continue;
                for (int k = j + 1; k < n; ++k) {
                    if (d[i][k] && d[j][k]) 
                        ans = min(ans, deg[i] + deg[j] + deg[k] - 6);
                }
            }
        return ans == INT_MAX ? -1 : ans;
    }
};
```

:::

### 方法二：给无向图定向

考虑更大的数据范围$N\leq2\times10^5,M\leq\min(\frac{N(N-1)}{2},2\times10^5)$。此时上面的暴力解法显然不再成立。

一个可行的做法是给无向图定向。这里需要用到一些推导。

- 我们把所有边的方向定为从度数小的点连向度数大的点（如果度数相等则可以任意连接，下面的参考代码中是从标号小的连向标号大的）。
- 可以证明，此时任意点的出度不会超过$\sqrt{2M}$。因为如果一个点的出度超过了$\sqrt{2M}$，则由于我们上面的规则，可知这些点的度数也都大于$\sqrt{2M}$，从而这些点的总度数将超过$2M$，而这是不可能的。

有了这一保证，我们就可以逐个枚举第一个点$u$，枚举其所有相邻点$v$，然后枚举$v$的所有相邻点$w$，检查$u,v,w$是否能构成连通三元组，然后更新答案。

总复杂度是多少呢？枚举$u$和$v$的时间复杂度是$\mathcal{O}(M)$；而对于每一对$(u,v)$，由于$v$的出度不超过$\sqrt{2M}$，所以枚举$w$的时间复杂度是$\mathcal{O}(\sqrt{M})$。

- 时间复杂度$\mathcal{O}(M^{\frac{3}{2}})$。
- 空间复杂度$\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> d(n);
        for (auto &e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            d[u].insert(v), d[v].insert(u);
        }
        
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            if (d[u].size() < d[v].size() || (d[u].size() == d[v].size() && u < v))
                adj[u].emplace_back(v);
            else
                adj[v].emplace_back(u);
        }

        int ans = INT_MAX;
        for (int u = 0; u < n; ++u)
            for (int v : adj[u])
                for (int w : adj[v])
                    if (d[u].count(w))
                        ans = min(ans, (int)(d[u].size() + d[v].size() + d[w].size() - 6));
        
        return ans == INT_MAX ? -1 : ans;
    }
};
```

:::

<Utterances />
