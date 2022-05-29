# Leetcode 第207场周赛题解

## Problem A - [重新排列单词间的空格](https://leetcode.cn/problems/rearrange-spaces-between-words/)

模拟题，关键是细心。

时间复杂度$O(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string reorderSpaces(string text) {
        vector<string> words;
        int spaces = 0;
        string curr;
        for (char c : text) {
            if (c == ' ') {
                if (!curr.empty())
                    words.emplace_back(curr);
                spaces++;
                curr.clear();
            } else
                curr.push_back(c);
        }
        if (!curr.empty())
            words.emplace_back(curr);
        int n = words.size();
        string ans;
        if (n == 1) {
            ans = words[0];
            for (int i = 0; i < spaces; ++i)
                ans.push_back(' ');
        } else {
            int c = spaces / (n - 1);
            for (int i = 0; i < n; ++i) {
                ans += words[i];
                if (i < n - 1)
                    for (int j = 0; j < c; ++j)
                        ans.push_back(' ');
            }
            for (int j = 0; j < spaces % (n - 1); ++j)
                ans.push_back(' ');
        }
        return ans;
    }
};
```

:::

## Problem B - [拆分字符串使唯一子字符串的数目最大](https://leetcode.cn/problems/split-a-string-into-the-max-number-of-unique-substrings/)

枚举所有的拆分方式，然后加上一点点剪枝。

时间复杂度$O(N\cdot2^N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxUniqueSplit(string s) {
        int n = s.size();
        int ans = 1;
        for (int i = 0; i < (1 << n); ++i) {
            vector<bool> v(n);
            for (int j = 0; j < n; ++j)
                v[j] = (i & (1 << j)) > 0;
            int hi = 0;
            for (int j = 1; j < n; ++j)
                if (v[j] != v[j - 1])
                    hi++;
            hi++;
            if (hi <= ans)
                continue;
            int l = 0;
            unordered_set<string> st;
            bool ok = true;
            for (int j = 1; j < n; ++j) {
                if (v[j] != v[j - 1]) {
                    string sub = s.substr(l, j - 1 - l + 1);
                    if (st.count(sub)) {
                        ok = false;
                        break;
                    }
                    st.insert(sub);
                    l = j;
                }
            }
            if (!ok)
                continue;
            string sub = s.substr(l, n - l);
            if (st.count(sub))
                ok = false;
            st.insert(sub);
            if (ok)
                ans = max(ans, (int)st.size());
        }
        return ans;
    }
};
```

:::

更好的方法是使用回溯（~~我发现我不太喜欢写回溯，于是有时候很吃亏~~），因为实际上有很多状态是没有必要枚举的（在前面就已经出现了重复的）。

::: details 参考代码（C++，回溯）

```cpp
class Solution {
    int n, ans = 0;
    unordered_set<string> st;
    void dfs(string &s, int pos) {
        if (pos == n)
            ans = max(ans, (int)st.size());
        int rest = n - pos;
        if (st.size() + rest <= ans)
            return;
        for (int i = pos; i < n; ++i) {
            string sub = s.substr(pos, i - pos + 1);
            if (st.count(sub))
                continue;
            st.insert(sub);
            dfs(s, i + 1);
            st.erase(sub);
        }
    }
public:
    int maxUniqueSplit(string s) {
        n = s.size();
        dfs(s, 0);
        return ans;
    }
};
```

:::

## Problem C - [矩阵的最大非负积](https://leetcode.cn/problems/maximum-non-negative-product-in-a-matrix/)

动态规划，记录每个位置上可以得到的最大非负乘积和最大非正乘积即可。

时间复杂度$O(NM)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;
const ll INF = 1ll << 60;

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<ll>> f(n, vector<ll>(m, INF)), g(n, vector<ll>(m, INF));
        if (grid[0][0] >= 0)
            f[0][0] = grid[0][0];
        if (grid[0][0] <= 0)
            g[0][0] = grid[0][0];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (i > 0) {
                    if (f[i - 1][j] != INF) {
                        if (grid[i][j] >= 0) {
                            if (f[i][j] == INF)
                                f[i][j] = f[i - 1][j] * grid[i][j];
                            else
                                f[i][j] = max(f[i][j], f[i - 1][j] * grid[i][j]);
                        }
                        if (grid[i][j] <= 0)
                            g[i][j] = min(g[i][j], f[i - 1][j] * grid[i][j]);
                    }
                    if (g[i - 1][j] != INF) {
                        if (grid[i][j] <= 0) {
                            if (f[i][j] == INF)
                                f[i][j] = g[i - 1][j] * grid[i][j];
                            else
                                f[i][j] = max(f[i][j], g[i - 1][j] * grid[i][j]);
                        }
                        if (grid[i][j] >= 0)
                            g[i][j] = min(g[i][j], g[i - 1][j] * grid[i][j]);
                    }
                }
                if (j > 0) {
                    if (f[i][j - 1] != INF) {
                        if (grid[i][j] >= 0) {
                            if (f[i][j] == INF)
                                f[i][j] = f[i][j - 1] * grid[i][j];
                            else
                                f[i][j] = max(f[i][j], f[i][j - 1] * grid[i][j]);
                        }
                        if (grid[i][j] <= 0)
                            g[i][j] = min(g[i][j], f[i][j - 1] * grid[i][j]);
                    }
                    if (g[i][j - 1] != INF) {
                        if (grid[i][j] <= 0) {
                            if (f[i][j] == INF)
                                f[i][j] = g[i][j - 1] * grid[i][j];
                            else
                                f[i][j] = max(f[i][j], g[i][j - 1] * grid[i][j]);
                        }
                        if (grid[i][j] >= 0)
                            g[i][j] = min(g[i][j], g[i][j - 1] * grid[i][j]);
                    }
                }
            }
        if (f[n - 1][m - 1] == INF)
            return -1;
        return f[n - 1][m - 1] % MOD;
    }
};
```

:::

## Problem D - [连通两组点的最小成本](https://leetcode.cn/problems/minimum-cost-to-connect-two-groups-of-points/)

因为已知第二组点的数量较少，所以对第二组点的连通状态进行状态压缩，然后依次处理第一组中的点即可。

对于第一组中的每个点，第一种做法是直接连一条边，第二种做法是连接若干个第二组中当前还没有连通的点。对于第一种做法，直接枚举$M$个点；对于第二种做法，假设当前未连通的点为$mask$，我们需要枚举它的子集，这里可以用[位运算枚举子集](https://cp-wiki.vercel.app/basic/enumerate/#%E6%9E%9A%E4%B8%BE%E5%AD%90%E9%9B%86)的方法来进行优化。

最后的总时间复杂度为$O(NM\cdot3^M)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        int n = cost.size(), m = cost[0].size();
        vector<int> dp(1 << m, INF);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> ndp(1 << m, INF);
            for (int last = 0; last < (1 << m); ++last) {
                if (dp[last] == INF)
                    continue;
                for (int j = 0; j < m; ++j) {
                    int nxt = last | (1 << j);
                    ndp[nxt] = min(ndp[nxt], dp[last] + cost[i][j]);
                }
                int v = (1 << m) - 1 - last;
                if (v > 0) {
                    for (int j = v; j > 0; j = v & (j - 1)) {
                        int c = 0;
                        for (int k = 0; k < m; ++k)
                            if (j & (1 << k))
                                c += cost[i][k];
                        int nxt = last | j;
                        ndp[nxt] = min(ndp[nxt], dp[last] + c);
                    }
                }
            }
            dp = move(ndp);
        }
        return dp.back();
    }
};
```

:::

<Utterances />
