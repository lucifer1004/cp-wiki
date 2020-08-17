# Leetcode 第199场周赛题解

## Problem A - [重新排列字符串](https://leetcode-cn.com/problems/shuffle-string/)

直接模拟即可。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        string ans(s);
        for (int i = 0; i < indices.size(); ++i)
            ans[indices[i]] = s[i];
        return ans;
    }
};
```

:::

## Problem B - [灯泡开关 IV](https://leetcode-cn.com/problems/bulb-switcher-iv/)

因为所有灯泡起始状态一致，所以在对第$i$个灯泡开始操作之前，它的状态一定与第$i-1$个灯泡保持一致。因此，如果第$i-1$个灯泡的最终状态和第$i$个灯泡的最终状态一致，就不需要对第$i$个灯泡进行操作；否则需要进行一次操作。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int minFlips(string target) {
        int ans = 0;
        char last = '0';
        for (char c : target) {
            if (c != last)
                ans++;
            last = c;
        }
        return ans;
    }
};
```

:::

## Problem C - [好叶子节点对的数量](https://leetcode-cn.com/problems/number-of-good-leaf-nodes-pairs/)

因为$distance$较小，所以可以在DFS过程中，记录当前节点的子树中到当前节点距离不超过$distance$的叶子节点的数目。每次合并左右孩子的信息就可以更新答案。在合并过程中，实际上是得到了以当前节点为LCA的符合条件的叶子节点对的数目，所以能做到不重不漏。

::: spoiler 参考代码（C++）

```cpp
class Solution {
    int ans = 0;
    vector<int> dfs(TreeNode* u, int d) {
        vector<int> cnt(d + 1);
        if (!u)
            return cnt;
        vector<int> left = dfs(u->left, d);
        vector<int> right = dfs(u->right, d);
        for (int i = 0; i <= d; ++i)
            for (int j = 0; j <= d; ++j)
                if (i + j + 2 <= d)
                    ans += left[i] * right[j];
        for (int i = 0; i < d; ++i)
            cnt[i + 1] = left[i] + right[i];
        if (!u->left && !u->right)
            cnt[0] = 1;
        return cnt;
    }
public:
    int countPairs(TreeNode* root, int distance) {
        dfs(root, distance);
        return ans;
    }
};
```

:::

## Problem D - [压缩字符串 II](https://leetcode-cn.com/problems/string-compression-ii/)

容易想到使用动态规划，朴素的状态表示是$dp[len][del][last\_char][last\_len]$，但这样的时间复杂度是$O(CN^3)$，$C$为不同的字母数。

实际上，可以省掉字母这一维，方法是记录最后一个连续段的结束位置，这样就把最后一段的字母隐含在其中了。这一思想与[Leetcode 546: 移除盒子](https://leetcode-cn.com/problems/remove-boxes/)有异曲同工之妙。

改造之后的状态是$dp[last\_seg\_end][len]$，需要考虑两种转移，一是从$dp[i][j]$到$dp[k][j+1]+1$，也即另起一段；二是从$dp[i][j]$到$dp[k][j+cnt]+cost$，也即接在上一段之后，这一转移要求$s[i-1]==s[k-1]$，而$cnt$表示从$i$到$k$与$s[i-1]$相同的字符数，$cost$为额外的代价，需要根据$cnt$进行计算。总时间复杂度降低到$O(N^3)$。

::: spoiler 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        if (n == k)
            return 0;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = 1;
            for (int j = 1; j < n; ++j) {
                int cost = 0, cnt = 0;
                for (int k = i + 1; k <= n; ++k) {
                    dp[k][j + 1] = min(dp[k][j + 1], dp[i][j] + 1);
                    if (s[k - 1] == s[i - 1]) {
                        cnt++;
                        if (cnt == 1 || cnt == 9 || cnt == 99)
                            cost++;
                        if (j + cnt > n)
                            break;
                        dp[k][j + cnt] = min(dp[k][j + cnt], dp[i][j] + cost);
                    }
                }
            }
        }
        int ans = n;
        for (int i = 1; i <= n; ++i)
            ans = min(ans, dp[i][n - k]);
        return ans;
    }
};
```

:::

<Utterances />
