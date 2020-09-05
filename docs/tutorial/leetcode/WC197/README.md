# Leetcode 第197场周赛题解

## Problem A - [好数对的数目](https://leetcode-cn.com/problems/number-of-good-pairs/)

方法一：暴力枚举

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                ans += nums[i] == nums[j];
        return ans;
    }
};
```

:::

方法二：计数

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int ans = 0;
        vector<int> cnt(101);
        for (int i : nums)
            cnt[i]++;
        for (int i = 1; i <= 100; ++i)
            ans += cnt[i] * (cnt[i] - 1) / 2;
        return ans;
    }
};
```

:::

## Problem B - [仅含 1 的子串数](https://leetcode-cn.com/problems/number-of-substrings-with-only-1s/)

找出每一个全为1的最长连续段，假设有$m$个这样的段，每段长度为$l_i$，则最终的结果为$\sum\frac{l_i(l_i-1)}{2}$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int numSub(string s) {
        s += "0";
        ll curr = 0, ans = 0;
        for (char c : s) {
            if (c == '1')
                curr++;
            else {
                ans += curr * (curr + 1) / 2;
                ans %= MOD;
                curr = 0;
            }
        }
        return ans;
    }
};
```

:::

## Problem C - [概率最大的路径](https://leetcode-cn.com/problems/path-with-maximum-probability/)

因为概率不会超过$1$，所以概率相乘是不会增加的。所以，求概率最大的路径，等价于权值相加情况下求最短路径，直接用Dijkstra算法求解即可。

::: details 参考代码（C++）

```cpp
const double eps = 1e-8;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<double> prob(n);
        prob[start] = 1;
        vector<vector<pair<int, double>>> adj(n);
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            double p = succProb[i];
            adj[u].emplace_back(v, p);
            adj[v].emplace_back(u, p);
        }
        priority_queue<pair<double, int>> pq;
        vector<bool> vis(n);
        pq.push({1, start});
        while (!pq.empty()) {
            auto top = pq.top();
            double p = top.first;
            int u = top.second;
            pq.pop();
            if (vis[u])
                continue;
            vis[u] = true;
            if (p < eps)
                continue;
            for (auto edge : adj[u]) {
                int v = edge.first;
                double now = p * edge.second;
                if (prob[v] < now) {
                    prob[v] = now;
                    pq.push({prob[v], v});
                }
            }
        }
        
        return prob[end]; 
    }
};
```

:::

## Problem D - [服务中心的最佳位置](https://leetcode-cn.com/problems/best-position-for-a-service-centre/)

所求的最佳位置即为几何中位数（[Geometric Median](https://en.wikipedia.org/wiki/Geometric_median)）。目前这一问题的最新研究进展为[Cohen et al., 2016](http://www.cs.cmu.edu/~./glmiller/Publications/Papers/CLMPS16.pdf)。

本题需要使用优化方法进行求解，如梯度下降、模拟退火等。下面给出的是爬山法的示例，所谓“爬山法”，其实可以看成是梯度下降的一种特例，也即每次固定向上下左右四个方向进行搜索。

此外，本题也可以通过三分查找求解。

::: details 参考代码（C++）

```cpp
const double eps = 1e-8;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

double calc(double ax, double ay, double bx, double by) {
    double dx = bx - ax, dy = by - ay;
    return sqrt(dx * dx + dy * dy);
}

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = positions.size();
        double x = 0, y = 0;
        for (auto v : positions) {
            x += v[0];
            y += v[1];
        }
        x /= n, y /= n;
        auto dist = [&](double cx, double cy) {
            double ans = 0;
            for (auto v : positions) 
                ans += calc(cx, cy, v[0], v[1]);
            return ans;
        };
        double d = dist(x, y);
        double step = 100.0;
        int done = 0;
        while (step > eps) {
            done = 0;
            for (int i = 0; i < 4; ++i) {
                double nx = x + step * dx[i];
                double ny = y + step * dy[i];
                double t = dist(nx, ny);
                if (t < d) {
                    d = t;
                    x = nx;
                    y = ny;
                    done = 1;
                    break;
                }
            }
            if (!done)
                step /= 2;
        }
        
        return d;
    }
};
```

:::

相关资源：
- [Wikipedia: Geometric Median](https://en.wikipedia.org/wiki/Geometric_median)
- [Medium: The Geometric Median](https://medium.com/towards-artificial-intelligence/the-geometric-median-b5b3b2d1a695)
- [GeeksforGeeks: Geometric Median](https://www.geeksforgeeks.org/geometric-median/)

<Utterances />
