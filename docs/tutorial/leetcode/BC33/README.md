# Leetcode 第33场双周赛题解

## Problem A - [千位分隔数](https://leetcode-cn.com/problems/thousand-separator/)

模拟。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string thousandSeparator(int n) {
        string s = to_string(n);
        string ans;
        int k = s.size();
        for (int i = 0; i < k; ++i) {
            ans.push_back(s[i]);
            if ((k - i - 1) % 3 == 0 && i != k - 1)
                ans.push_back('.');
        }
        return ans;
    }
};
```

:::

## Problem B - [可以到达所有点的最少点数目](https://leetcode-cn.com/problems/minimum-number-of-vertices-to-reach-all-nodes/)

因为是有向无环图，所以直接统计所有入度为$0$的节点即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> in(n);
        for (auto v : edges)
            in[v[1]]++;
        vector<int> ans;
        for (int i = 0; i < n; ++i)
            if (!in[i])
                ans.emplace_back(i);
        return ans;
    }
};
```

:::

## Problem C - [得到目标数组的最少函数调用次数](https://leetcode-cn.com/problems/minimum-numbers-of-function-calls-to-make-target-array/)

倒推。所有当前为奇数的数，必然是通过加一操作得来，因此先把所有奇数减一变为偶数；此时剩下的都是偶数，将不为$0$的数都减半（这只需要一次操作），如果已经都是$0$，则退出循环。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        bool nonzero = true;
        while (nonzero) {
            nonzero = false;
            for (int &num : nums)
                if (num & 1)
                    num--, ans++;
            bool d = false;
            for (int &num : nums) {
                if (num > 0)
                    num >>= 1, d = true;
                if (num)
                    nonzero = true;
            }
            ans += d;
        }
        return ans;
    }
};
```

:::

## Problem D - [二维网格图中探测环](https://leetcode-cn.com/problems/detect-cycles-in-2d-grid/)

DFS实现无向图找环，遍历过程中记录深度，检查环的长度是否满足要求。实际上，因为本题的特殊性，不可能存在长度为$3$的环，所以只要能成环（有反向边），长度至少为$4$，因此即使不加对深度的判断，只根据是否已经访问过来进行判断，也是OK的。

::: details 参考代码（C++）

```cpp
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

class Solution {
    bool ans = false;
    vector<vector<char>> grid;
    vector<vector<int>> depth;
    int n, m;
    void dfs(int i, int j, int pi, int pj) {
        if (ans)
            return;
        for (int k = 0; k < 4; ++k) {
            int ci = i + dy[k], cj = j + dx[k];
            if (ci < 0 || ci >= n || cj < 0 || cj >= m || grid[ci][cj] != grid[i][j] || (ci == pi && cj == pj))
                continue;
            if (depth[ci][cj] == -1) {
                depth[ci][cj] = depth[i][j] + 1;
                dfs(ci, cj, i, j);
            } else if (depth[i][j] - depth[ci][cj] >= 3) {
                ans = true;
                return;
            }
        }
    }
public:
    bool containsCycle(vector<vector<char>>& grid) {
        this->grid = grid;
        n = grid.size(), m = grid[0].size();
        depth = vector<vector<int>>(n, vector<int>(m, -1));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (ans)
                    return ans;
                if (depth[i][j] == -1) {
                    depth[i][j] = 0;
                    dfs(i, j, -1, -1);
                }
            }
        return ans;
    }
};
```

:::

<Utterances />
