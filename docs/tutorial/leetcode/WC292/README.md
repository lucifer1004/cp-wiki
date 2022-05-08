# Leetcode 第292场周赛题解

## Problem A - [字符串中最大的 3 位相同数字](https://leetcode.cn/problems/largest-3-same-digit-number-in-string/)

### 方法一：暴力

- 时间复杂度 $\mathcal{O}(|S|)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def largestGoodInteger(self, num: str) -> str:
        ans = ''
        n = len(num)
        for i in range(n - 2):
            if num[i] == num[i + 1] == num[i + 2]:
                ans = max(ans, num[i])
        return ans * 3
```

:::

## Problem B - [统计值等于子树平均值的节点数](https://leetcode.cn/problems/count-nodes-equal-to-average-of-subtree/)

### 方法一：DFS

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(H)$，其中 $H$ 表示树高。

::: details 参考代码（C++）

```cpp
class Solution {
    int ans;
    
    pair<int, int> dfs(TreeNode *root) {
        if (root == nullptr)
            return make_pair(0, 0);
        
        int sum = root->val;
        int cnt = 1;
        auto [ls, lc] = dfs(root->left);
        auto [rs, rc] = dfs(root->right);
        sum += ls + rs;
        cnt += lc + rc;
        if (sum / cnt == root->val)
            ans++;
        
        return make_pair(sum, cnt);
    }
public:
    int averageOfSubtree(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
```

:::

## Problem C - [统计打字方案数](https://leetcode.cn/problems/count-number-of-texts/)

### 方法一：动态规划

- 时间复杂度 $\mathcal{O}(|S|)$ 。
- 空间复杂度 $\mathcal{O}(|S|)$，可以进一步优化到 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countTexts(self, pressedKeys: str) -> int:
        d = [3] * 10
        d[7] = d[9] = 4
        MOD = 1000000007
        dp = [1]
        n = len(pressedKeys)
        for i in range(n):
            v = int(pressedKeys[i])
            curr = 0
            for j in range(d[v]):
                if i < j or pressedKeys[i - j] != pressedKeys[i]:
                    break
                curr += dp[i - j]
            curr %= MOD
            dp.append(curr)
        return dp[-1]
```

:::

## Problem D - [检查是否有合法括号字符串路径](https://leetcode.cn/problems/check-if-there-is-a-valid-parentheses-string-path/)

### 方法一：动态规划

- 时间复杂度 $\mathcal{O}(NM(N+M))$，可以利用 `bitset` 进一步优化。
- 空间复杂度 $\mathcal{O}(NM(N+M))$，可以利用 `bitset` 进一步优化。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        if (grid[0][0] == ')')
            return false;
        
        int n = grid.size(), m = grid[0].size();
        vector<vector<unordered_set<int>>> v(n, vector<unordered_set<int>>(m));
        v[0][0].insert(1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                int c = grid[i][j] == '(' ? 1 : -1;
                if (i > 0)
                    for (int k : v[i - 1][j])
                        if (k + c >= 0)
                            v[i][j].insert(k + c);
                if (j > 0)
                    for (int k : v[i][j - 1])
                        if (k + c >= 0)
                            v[i][j].insert(k + c);
            }
        
        return v[n - 1][m - 1].count(0);
    }
};
```

:::

<Utterances />
