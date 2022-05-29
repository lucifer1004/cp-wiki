# Leetcode 第56场双周赛题解

## Problem A - [统计平方和三元组的数目](https://leetcode.cn/problems/count-square-sum-triples/)

### 方法一：暴力+预处理

本题数据范围较小，因此我们可以暴力枚举两个数（$a,b$或者$a,c$都可以）。为了运行速度更快，可以预处理打表。

- 预处理时间复杂度$\mathcal{O}(N^2)$，之后每次调用时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
const int N = 255;

bool inited = false;
int ans[N];

void init() {
    inited = true;
    int cnt = 0;
    for (int c = 2; c < N; ++c) {
        for (int a = 1; a * a * 2 <= c * c; ++a) {
            int b = int(sqrt(c * c - a * a));
            if (a * a + b * b == c * c)
                cnt += 2;
        }
        ans[c] = cnt;
    }
}

class Solution {
public:
    int countTriples(int n) {
        if (!inited)
            init();
        
        return ans[n];
    }
};
```

:::


## Problem B - [迷宫中离入口最近的出口](https://leetcode.cn/problems/nearest-exit-from-entrance-in-maze/)

### 方法一：宽度优先搜索

标准宽搜，注意判断入口在边界位置的情况。

- 时间复杂度为$\mathcal{O}(RC)$。
- 空间复杂度$\mathcal{O}(RC)$。


::: details 参考代码（C++）

```cpp
const int d[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int n = maze.size(), m = maze[0].size();
        int si = entrance[0], sj = entrance[1];
        vector<vector<int>> dis(n, vector<int>(m, INF));
        queue<pair<int, int>> q;
        q.emplace(si, sj);
        dis[si][sj] = 0;
        
        while (!q.empty()) {
            auto [ci, cj] = q.front();
            q.pop();
            if (dis[ci][cj] != 0 && (ci == 0 || ci == n - 1 || cj == 0 || cj == m - 1))
                return dis[ci][cj];
            for (int k = 0; k < 4; ++k) {
                int ni = ci + d[k][0], nj = cj + d[k][1];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m || maze[ni][nj] == '+' || dis[ni][nj] != INF)
                    continue;
                dis[ni][nj] = dis[ci][cj] + 1;
                q.emplace(ni, nj);
            }
        }
        
        return -1;
    }
};
```

:::


## Problem C - [求和游戏](https://leetcode.cn/problems/sum-game/)

### 方法一：分类讨论

首先统计出前半段的当前总和$lsum$和问号数$lcnt$，以及后半段的当前总和$rsum$和问号数$rcnt$。

我们分情况讨论：

- 如果问号的总数是奇数，则将由Alice进行最后一次操作。那么无论最后一次操作之前的情况如何，Alice至少有$9$种获胜的选择（因为能使得前后两段总和相等的选择至多有$1$种），因此Alice必胜。
- 如果问号的总数是偶数，则：
    - 如果问号多的那一边总和也较大，则Alice总可以选择在问号多的那边放$9$，在问号少的那边放$0$；那么无论Bob如何操作，两段的大小关系都不会改变。因此这种情况下Alice也必胜。
    - 如果问号多的那一边总和较小：
        - 我们不妨考虑一种镜像策略，即当Alice在某一段写下一个数字时，Bob就在另一段写下相同的数字。这样重复若干次后，必然只有一段包含问号（并且问号数目应当为偶数）。假设此时问号有$2k$个，而两段之差为$d$。对Bob来说，当且仅当$d=9k$时他有必胜策略，即当Alice写下$n$时，Bob就写下$9-n$，这样最后就能使得两段相等。而如果$d<9k$，Alice每次都写$9$即可确保获胜；如果$d>9k$，Alice每次都写$0$即可确保获胜。小结：在采用镜像策略时，Bob当且仅当$d=9k$时必胜，其中$d$为两段当前和的差的绝对值，$k$为两段问号数的差的绝对值的一半，
        - 我们还需要说明$d<9k$和$d>9k$时Alice有必胜策略。不难想到，对于$d<9k$，Alice可以首先在问号较少的那一半中写下一个$0$，之后Alice反过来采用镜像策略，这样到最后会在问号较多的那一半中剩下$2k+1$个问号。之后Alice每次都写$9$，则到Bob最后一次操作之前，包含最后一个问号的这一半的总和已经超过了另一半，所以Bob必败，Alice必胜。同理，$d>9k$时，Alice可以在问号较少的那一半中先写下一个$9$，然后采用镜像策略，最后在剩下的那一半中每次都写$0$，同样可以保证必胜。

这样，我们就完成了所有情况的讨论。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int lsum = 0, rsum = 0, lcnt = 0, rcnt = 0;
        for (int i = 0; i < n / 2; ++i) {
            if (num[i] == '?')
                lcnt++;
            else
                lsum += num[i] - '0';
        }
        for (int i = n / 2; i < n; ++i) {
            if (num[i] == '?')
                rcnt++;
            else
                rsum += num[i] - '0';
        }
        
        if ((lcnt + rcnt) % 2 == 1)
            return true;
        
        if ((lcnt > rcnt && lsum >= rsum) || (lcnt < rcnt && lsum <= rsum))
            return true;
        
        int dcnt = abs(lcnt - rcnt), dsum = abs(lsum - rsum);
        return dsum != 9 * dcnt / 2;
    }
};
```

:::

## Problem D - [规定时间内到达终点的最小花费](https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/)

### 方法一：Dijkstra算法

我们以$(node, time)$为节点建立一张新图，然后以$(0,0)$为源点运行一遍Dijkstra算法求出单源最短路径，最后的答案就是：

$$
\min_t dis(n-1,t)
$$

- 时间复杂度$\mathcal{O}((N+M)T\log NT)$。
- 空间复杂度$\mathcal{O}(NT)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<unordered_map<int, int>> adj(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (w > maxTime)
                continue;
            if (!adj[u].count(v) || adj[u][v] > w)
                adj[u][v] = w;
            if (!adj[v].count(u) || adj[v][u] > w)
                adj[v][u] = w;
        }
        
        int T = maxTime + 1;
        vector<int> dis(n * T + 1, INF);
        dis[0] = passingFees[0];
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(dis[0], 0);
        while (!pq.empty()) {
            auto [d, idx] = pq.top();
            pq.pop();
            if (d > dis[idx])
                continue;
            int u = idx / T, t = idx % T;
            for (auto [v, w] : adj[u]) {
                if (t + w < T) {
                    int nxt = v * T + t + w;
                    if (d + passingFees[v] < dis[nxt]) {
                        dis[nxt] = d + passingFees[v];
                        pq.emplace(dis[nxt], nxt);
                    }
                }
            }
        }
        int ans = INF;
        for (int t = 0; t < T; ++t)
            ans = min(ans, dis[(n - 1) * T + t]);
        
        return ans == INF ? -1 : ans;
    }
};
```

:::

### 方法二：动态规划

令$dp[node][time]$表示在$time$时刻到达$node$的最小花费，显然有两种转移方式：

- 在$node$原地不动，$(node,time)\rightarrow(node,time+1)$，不需要额外花费
- 走边$(v,cost)$去与$node$相邻的$v$，$(node,time)\rightarrow(v,time+cost)$，需要花费$v$的通行费

最后的答案就是$dp[n-1][maxTime]$。

- 时间复杂度$\mathcal{O}((N+M)T)$。
- 空间复杂度$\mathcal{O}(NT)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<unordered_map<int, int>> adj(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (w > maxTime)
                continue;
            if (!adj[u].count(v) || adj[u][v] > w)
                adj[u][v] = w;
            if (!adj[v].count(u) || adj[v][u] > w)
                adj[v][u] = w;
        }
        
        vector<vector<int>> dp(n, vector<int>(maxTime + 1, INF));
        dp[0][0] = passingFees[0];
        for (int t = 0; t < maxTime; ++t)
            for (int i = 0; i < n; ++i) {
                if (dp[i][t] == INF)
                    continue;
                dp[i][t + 1] = min(dp[i][t + 1], dp[i][t]);
                for (auto [v, w] : adj[i]) {
                    if (t + w <= maxTime)
                        dp[v][t + w] = min(dp[v][t + w], dp[i][t] + passingFees[v]);
                }
            }
        
        return dp[n - 1][maxTime] == INF ? -1 : dp[n - 1][maxTime];
    }
};
```

:::

<Utterances />
