# Leetcode 第192场周赛题解

## Problem A - [重新排列数组](https://leetcode.cn/problems/shuffle-the-array/)

### 方法一：模拟

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(n * 2);
        for (int i = 0; i < n; ++i) {
            ans[i * 2] = nums[i];
            ans[i * 2 + 1] = nums[n + i];
        }
        return ans;
    }
};
```

:::

## Problem B - [数组中的 k 个最强值](https://leetcode.cn/problems/the-k-strongest-values-in-an-array/)

### 方法一：排序

首先利用`nth_element`求出中位数，然后按要求排序即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$，使用了常数量级的额外空间。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        nth_element(arr.begin(), arr.begin() + (n - 1) / 2, arr.end());
        int mid = arr[(n - 1) / 2];
        sort(arr.begin(), arr.end(), [&](int p, int q){
            return abs(p - mid) == abs(q - mid) ? p > q : abs(p - mid) > abs(q - mid);
        });
        arr.resize(k);
        return arr;
    }
};  
```

:::

## Problem C - [设计浏览器历史记录](https://leetcode.cn/problems/design-browser-history/)

### 方法一：模拟

维护当前的历史记录和指针即可。

::: details 参考代码（Python 3）

```python
class BrowserHistory:

    def __init__(self, homepage: str):
        self.history = [homepage]
        self.idx = 0

    def visit(self, url: str) -> None:
        self.history = self.history[:self.idx + 1]
        self.idx += 1
        self.history.append(url)

    def back(self, steps: int) -> str:
        self.idx = max(self.idx - steps, 0)
        return self.history[self.idx]

    def forward(self, steps: int) -> str:
        self.idx = min(len(self.history) - 1, self.idx + steps);
        return self.history[self.idx]
```

:::

## Problem D - [粉刷房子 III](https://leetcode.cn/problems/paint-house-iii/)

### 方法一：动态规划

使用`dp[blocks][color]`表示已经组成`blocks`个街区且最后一个街区颜色为`color`时的最小花费。一共有五种转移，具体可参考代码。其中，为了节约一重循环，针对第一和第二种转移，使用额外的数组`best[blocks]=(first,first_color,second)`记录当前组成`blocks`的最小花费、最小花费对应的颜色以及次小花费。

- 时间复杂度$\mathcal{O}(MNT)$。
- 空间复杂度$\mathcal{O}(NT)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        vector<vector<int>> dp(target + 1, vector<int>(n, INF));
        for (int i = 0; i < n; ++i)
            dp[0][i] = 0;
        vector<array<int, 3>> best(target + 1, {INF, INF, INF});
        best[0] = {0, -1, 0};
        for (int i = 0; i < m; ++i) {
            vector<vector<int>> ndp(target + 1, vector<int>(n, INF));
            vector<array<int, 3>> nbest(target + 1, {INF, INF, INF});

            for (int blocks = 0; blocks <= target; ++blocks) {
                for (int color = 0; color < n; ++color) {
                    if (houses[i] == 0) {
                        // Case 1&2: Use a different color.
                        if (blocks < target) {
                            // Case 1: Current house is not colored, and the color to use matches the best choice, so we need to use the second best.
                            if (color == best[blocks][1]) {
                                ndp[blocks + 1][color] = min(ndp[blocks + 1][color], best[blocks][2] + cost[i][color]);
                            } else {
                            // Case 2: Current house is not colored, and we use the best.
                                ndp[blocks + 1][color] = min(ndp[blocks + 1][color], best[blocks][0] + cost[i][color]);
                            }
                        }

                        // Case 3: Use the same color.
                        if (blocks > 0) {
                            ndp[blocks][color] = min(ndp[blocks][color], dp[blocks][color] + cost[i][color]);
                        }
                    } else if (houses[i] - 1 == color && blocks > 0) {
                        // Case 4: Current house is already colored, but does not form a new block.
                        ndp[blocks][color] = min(ndp[blocks][color], dp[blocks][color]);
                    } else if (blocks < target) {
                        // Case 5: Current house is already colored, and forms a new block.
                        ndp[blocks + 1][houses[i] - 1] = min(ndp[blocks + 1][houses[i] - 1], dp[blocks][color]);
                    }
                }
            }

            for (int blocks = 1; blocks <= target; ++blocks) {
                for (int color = 0; color < n; ++color) {
                    if (ndp[blocks][color] < nbest[blocks][0]) {
                        nbest[blocks][2] = nbest[blocks][0];
                        nbest[blocks][1] = color;
                        nbest[blocks][0] = ndp[blocks][color];
                    } else if (ndp[blocks][color] < nbest[blocks][2]) {
                        nbest[blocks][2] = ndp[blocks][color];
                    }
                }
            }

            dp = move(ndp);
            best = move(nbest);
        }

        int ans = INF;
        for (int color = 0; color < n; ++color)
            ans = min(ans, dp[target][color]);
        return ans == INF ? -1 : ans;
    }
};
```

:::

<Utterances />
