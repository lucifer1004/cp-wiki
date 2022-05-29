# Leetcode 第28场双周赛题解

## Problem A - [商品折扣后的最终价格](https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/)

### 方法一：暴力

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        vector<int> ans(prices);
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (prices[j] <= prices[i]) {
                    ans[i] -= prices[j];
                    break;
                }
        return ans;
    }
};
```

:::

### 方法二：单调栈

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        
        stack<int> st;
        vector<int> next_smaller(n, -1);
        
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && prices[st.top()] >= prices[i]) {
                next_smaller[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
            
        vector<int> ans(prices);
        for (int i = 0; i < n; ++i)
            if (next_smaller[i] != -1)
                ans[i] -= prices[next_smaller[i]];
        return ans;
    }
};
```

:::

## Problem B - [子矩形查询](https://leetcode.cn/problems/subrectangle-queries/)

### 方法一：模拟

- 时间复杂度：update为$\mathcal{O}(RC)$，get为$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(RC)$。

::: details 参考代码（C++）

```cpp
class SubrectangleQueries {
    vector<vector<int>> rectangle;
public:
    SubrectangleQueries(vector<vector<int>>& rectangle): rectangle(rectangle) {}

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        for (int i = row1; i <= row2; ++i)
            for (int j = col1; j <= col2; ++j)
                rectangle[i][j] = newValue;
    }
    
    int getValue(int row, int col) {
        return rectangle[row][col];
    }
};
```

:::

### 方法二：记录操作历史而非改变数组的值

另一种思路是：不实际对数组进行操作，而只是记录操作的历史。对于一次查询，我们倒序检查所有的操作，当找到第一个将查询位置包含在内的操作时，即返回对应的结果。

- 时间复杂度：update为$\mathcal{O}(1)$，get为$\mathcal{O}(Q)$。
- 空间复杂度$\mathcal{O}(RC+Q)$。

::: details 参考代码（C++）

```cpp
class SubrectangleQueries {
    vector<vector<int>> rectangle;
    vector<tuple<int, int, int, int, int>> history;
public:
    SubrectangleQueries(vector<vector<int>>& rectangle): rectangle(rectangle) {}
    
    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        history.emplace_back(row1, col1, row2, col2, newValue);
    }
    
    int getValue(int row, int col) {
        int n = history.size();
        for (int i = n - 1; i >= 0; --i) {
            auto [row1, col1, row2, col2, newValue] = history[i];
            if (row1 <= row && row <= row2 && col1 <= col && col <= col2)
                return newValue;
        }
        return rectangle[row][col];
    }
};
```

:::

## Problem C - [找两个和为目标值且不重叠的子数组](https://leetcode.cn/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/)

利用前缀和+哈希表可以求出以某一位置为结尾的，和为目标值的子数组的最短长度。对原数组正序和倒序分别求解一次，就可以枚举找到最终的答案。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
def solve(arr: List[int], target: int):
    n = len(arr)

    d = {0: 0}
    s = 0
    
    ans = [n + 1] * n
    
    for i in range(n):
        s += arr[i]
        if (s - target) in d:
            ans[i] = i + 1 - d[s - target]
        d[s] = i + 1
    
    for i in range(1, n):
        ans[i] = min(ans[i], ans[i - 1])
        
    return ans
    

class Solution:
    def minSumOfLengths(self, arr: List[int], target: int) -> int:
        n = len(arr)
        l = solve(arr, target)
        r = solve(arr[::-1], target)[::-1]
        ans = n + 1
        for i in range(n - 1):
            if l[i] < n and r[i + 1] < n:
                ans = min(ans, l[i] + r[i + 1])
        return -1 if ans == n + 1 else ans

```

:::

## Problem D - [安排邮筒](https://leetcode.cn/problems/allocate-mailboxes/)

注意到：

1. 邮筒应该放在某个房屋处，因为这样的总成本不会高于放在路中间的成本。
2. 任意两个邮筒的服务范围是不重叠的。

我们可以首先求出在$[i\dots j]$范围内放置一个邮筒时的总成本$dist[i][j]$，然后利用动态规划求解最后的答案。

- 时间复杂度$\mathcal{O}(N^3)$。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
int dp[105][105];
public:
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        sort(houses.begin(), houses.end());
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        vector<vector<int>> dist(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; ++j)
                for (int l = i, r = j; l < r; l++, r--)
                    dist[i][j] += houses[r - 1] - houses[l - 1];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= min(i, k); ++j) {
                for (int p = 0; p <= i - 1; ++p)
                    dp[i][j] = min(dp[i][j], dp[p][j - 1] + dist[p + 1][i]);
            }
        return dp[n][k];
    }
};
```

:::

<Utterances />
