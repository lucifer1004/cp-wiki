# 2021年力扣杯秋季赛个人赛题解

## Problem A - [无人机方阵](https://leetcode-cn.com/contest/season/2021-fall/problems/0jQkd0/)

### 方法一：计数

因为只需要考虑颜色而不需要考虑位置，直接对颜色进行计数即可。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（Python 3）

```python
from collections import Counter

class Solution:
    def minimumSwitchingTimes(self, source: List[List[int]], target: List[List[int]]) -> int:
        cs = Counter()
        ct = Counter()
        for row in source:
            for cell in row:
                cs[cell] += 1
        for row in target:
            for cell in row:
                ct[cell] += 1
        ans = 0
        for key in cs:
            ans += max(0, cs[key] - ct[key])
        return ans
```

:::


## Problem B - [心算挑战](https://leetcode-cn.com/contest/season/2021-fall/problems/uOAnQW/)

### 方法一：贪心

显然应该将奇数和偶数元素分别考虑。

在选取$i$个奇数和$cnt-i$个偶数的情况下，我们应该选取最大的$i$个奇数和最大的$cnt-i$个偶数。因此我们需要对奇数和偶数数组分别排序，然后讨论$i$的选取。

- 时间复杂度为$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxmiumScore(self, cards: List[int], cnt: int) -> int:
        odd = []
        even = []
        for card in cards:
            if card % 2 == 0:
                even.append(card)
            else:
                odd.append(card)
        even.sort(reverse=True)
        odd.sort(reverse=True)
        peven = [0]
        podd = [0]
        for ei in even:
            peven.append(peven[-1] + ei)
        for oi in odd:
            podd.append(podd[-1] + oi)
            
        neven = len(even)
        nodd = len(odd)
        ans = 0
        for e in range(cnt % 2, min(neven, cnt) + 1, 2):
            o = cnt - e
            if o > nodd:
                continue
            ans = max(ans, peven[e] + podd[o])
            
        return ans
```

:::


## Problem C - [黑白翻转棋](https://leetcode-cn.com/contest/season/2021-fall/problems/fHi6rV/)

### 方法一：模拟

枚举每个空格子，然后模拟在这个位置放黑棋后棋盘的变化即可。

模拟过程逐轮进行，并且每一轮中只需要考虑由上一轮产生的黑子所带来的影响即可，这样可以避免重复讨论。

- 时间复杂度$\mathcal{O}((NM)^3)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
const int d[8][2] = {{-1, 0}, {-1, -1}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

class Solution {
public:
    int flipChess(vector<string>& c) {
        int n = c.size(), m = c[0].size();
        int ans = 0;
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (c[i][j] != '.')
                    continue;
                
                int curr = 0;
                vector<string> b(c);
                set<pair<int, int>> change;
                change.emplace(i, j);
                while (!change.empty()) {
                    set<pair<int, int>> nchange;
                    for (auto [ci, cj] : change)
                        b[ci][cj] = 'X';
                    for (auto [ci, cj] : change) {
                        for (int k = 0; k < 8; ++k) {
                            int ni = ci, nj = cj;
                            bool stop = false;
                            vector<pair<int, int>> white;
                            while (true) {
                                ni += d[k][0], nj += d[k][1];
                                if (ni < 0 || ni >= n || nj < 0 || nj >= m || b[ni][nj] == '.') {
                                    stop = true;
                                    break;
                                }
                                if (b[ni][nj] == 'X')
                                    break;
                                white.emplace_back(ni, nj);
                            }
                            if (!stop)
                                for (auto [wi, wj] : white)
                                    nchange.emplace(wi, wj);
                        }
                    }
                    curr += nchange.size();
                    change = move(nchange);
                }
                
                ans = max(ans, curr);
        }
        
        return ans;
    }
};
```

:::

## Problem D - [玩具套圈](https://leetcode-cn.com/contest/season/2021-fall/problems/vFjcfV/)

### 方法一：数据结构

注意到$R$很小，最大不超过$10$，因此我们可以：

1. 将`circles`按照$x$坐标分组，每组中按$y$坐标排序。
2. 对于每个`toy`，我们考虑$[x_i-r,x_i+r]$这个范围内的每个组。对于每个组，我们考虑其中与$y_i$最接近的两个`circle`，并判断是否能覆盖。

- 时间复杂度$\mathcal{O}(NR\log M+M\log M)$。
- 空间复杂度$\mathcal{O}(M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int circleGame(vector<vector<int>>& toys, vector<vector<int>>& circles, int r) {
        unordered_map<int, set<int>> mp;
        for (auto &circle : circles) {
            int x = circle[0], y = circle[1];
            mp[x].emplace(y);
        }
        
        int ans = 0;
        for (auto &toy : toys) {
            int x = toy[0], y = toy[1], ri = toy[2];
            if (ri > r)
                continue;
            
            bool found = false;
            for (int xx = x - r; xx <= x + r; ++xx) {
                if (!mp.count(xx))
                    continue;
                
                auto &s = mp[xx];
                auto it = s.lower_bound(y);
                if (it != s.begin()) {
                    int yy = *prev(it);
                    long long dis = 1LL * (xx - x) * (xx - x) + 1LL * (yy - y) * (yy - y);
                    if (dis <= (r - ri) * (r - ri)) {
                        found = true;
                        break;
                    }
                }
                
                if (it != s.end()) {
                    int yy = *it;
                    long long dis = 1LL * (xx - x) * (xx - x) + 1LL * (yy - y) * (yy - y);
                    if (dis <= (r - ri) * (r - ri)) {
                        found = true;
                        break;
                    }
                }
            }
            
            if (found)
                ans++;
        }
        
        return ans;
    }
};
```

:::

## Problem E - [十字路口的交通](https://leetcode-cn.com/contest/season/2021-fall/problems/vFjcfV/)

### 方法一：动态规划

我们用$dp[i][j][k][r]$表示四个方向分别走了$i$、$j$、$k$、$r$辆车时的最小用时。初始条件为$dp[0][0][0][0]=0$。

对于每个状态，我们枚举$2^4$种走车的可能，并进行转移。

为了判断每种转移是否合法，我们进行一次预处理，在预处理中将所有存在冲突的转移进行标记。

- 预处理时间复杂度$\mathcal{O}(16\cdot2^{16})$，每次运行时间复杂度$\mathcal{O}(64N^4)$。
- 空间复杂度$\mathcal{O}(N^4+2^{16})$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;
int dp[21][21][21][21];
bool g[1 << 16];
map<char, int> dc;
bool inited = false;

void init() {
    inited = true;
    
    dc['E'] = 0, dc['S'] = 1, dc['W'] = 2, dc['N'] = 3;
    
    // EE = 0, ES = 1, EW = 2, EN = 3
    // SE = 4, SS = 5, SW = 6, SN = 7
    // WE = 8, WS = 9, WW = 10, WN = 11
    // NE = 12, NS = 13, NW = 14, NN = 15

    set<pair<int, int>> inv;
    for (int i : {6, 7, 8, 9, 12, 13})
        inv.emplace(1, i);
    for (int i : {6, 7, 11, 12, 13, 14})
        inv.emplace(2, i);
    for (int i : {7, 11})
        inv.emplace(3, i);

    for (int i : {8, 12})
        inv.emplace(4, i);
    for (int i : {8, 11, 13, 14})
        inv.emplace(6, i);
    for (int i : {8, 11, 12})
        inv.emplace(7, i);

    for (int i : {12, 13})
        inv.emplace(8, i);
    for (int i : {13})
        inv.emplace(9, i);
    for (int i : {12, 13})
        inv.emplace(11, i);
    
    for (int i = 0; i < (1 << 16); ++i) {
        int p = i;
        vector<int> v;
        v.emplace_back(p / (16 * 16 * 16));
        p %= 16 * 16 * 16;
        v.emplace_back(p / (16 * 16));
        p %= 16 * 16;
        v.emplace_back(p / 16);
        v.emplace_back(p % 16);
        bool good = true;
        for (int j : v)
            for (int k : v)
                if (inv.count({j, k}))
                    good = false;
        if (good)
            g[i] = true;
        else
            g[i] = false;
    }
}

class Solution {
public:
    int trafficCommand(vector<string>& directions) {
        if (!inited)
            init();
        
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0][0][0] = 0;
        vector<int> r(4), lim(4);
        for (int i = 0; i < 4; ++i)
            lim[i] = directions[i].size();
        for (r[0] = 0; r[0] <= lim[0]; ++r[0])
            for (r[1] = 0; r[1] <= lim[1]; ++r[1])
                for (r[2] = 0; r[2] <= lim[2]; ++r[2])
                    for (r[3] = 0; r[3] <= lim[3]; ++r[3]) {
                        int now = dp[r[0]][r[1]][r[2]][r[3]];
                        
                        if (now == INF)
                            continue;
                        
                        for (int s = 1; s < 16; ++s) {
                            vector<int> nxt(r);
                            int car = 0;
                            bool valid = true;
                            for (int p = 0; p < 4; ++p) {
                                car *= 16;
                                if (s & (1 << p)) {
                                    if (r[p] == lim[p]) {
                                        valid = false;
                                        break;
                                    }
                                    nxt[p]++;
                                    car += p * 4 + dc[directions[p][r[p]]];
                                }
                            }
                            
                            if (!valid || !g[car])
                                continue;
                            
                            auto &nn = dp[nxt[0]][nxt[1]][nxt[2]][nxt[3]];
                            nn = min(nn, now + 1);
                        }
                    }
        
        return dp[lim[0]][lim[1]][lim[2]][lim[3]];
    }
};
```

:::

<Utterances />
