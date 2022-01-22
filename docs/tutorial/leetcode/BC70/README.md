# Leetcode 第70场双周赛题解

## Problem A - [打折购买糖果的最小开销](https://leetcode-cn.com/problems/minimum-cost-of-buying-candies-with-discount/)

### 方法一：排序+贪心

从大到小排序，每三个买前两个即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumCost(self, cost: List[int]) -> int:
        return sum(x for i, x in enumerate(sorted(cost, reverse=True)) if i % 3 != 2)
```

:::

## Problem B - [统计隐藏数组数目](https://leetcode-cn.com/problems/count-the-hidden-sequences/)

### 方法一：假设起始值为0

先假设起始值为0，计算出过程中的最大值和最小值。通过平移使得最小值与允许的最小值重叠，根据此时最大值与允许的最大值的差值即可求得答案。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:
        lo = 0
        hi = 0
        now = 0
        for diff in differences:
            now += diff
            lo = min(lo, now)
            hi = max(hi, now)
        hi += lower - lo
        return max(0, upper - hi + 1)
```

:::

## Problem C - [价格范围内最高排名的 K 样物品](https://leetcode-cn.com/problems/k-highest-ranked-items-within-a-price-range/)

### 方法一：BFS+排序

BFS找出所有符合条件的物品，再按照题目要求排序取前 $K$ 个即可。

- 时间复杂度$\mathcal{O}(NM\log(NM))$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
const int d[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

class Solution {
public:
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        int n = grid.size(), m = grid[0].size();
        int lo = pricing[0], hi = pricing[1];
        int r = start[0], c = start[1];
        vector<tuple<int, int, int, int>> ans;
        queue<tuple<int, int, int>> q;
        vector<vector<bool>> vis(n, vector<bool>(m));
        q.emplace(0, r, c);
        vis[r][c] = true;
        while (!q.empty()) {
            auto [steps, i, j] = q.front();
            if (grid[i][j] >= lo && grid[i][j] <= hi)
                ans.emplace_back(steps, grid[i][j], i, j);
            q.pop();
            for (int t = 0; t < 4; ++t) {
                int ni = i + d[t][0], nj = j + d[t][1];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m || vis[ni][nj] || grid[ni][nj] == 0)
                    continue;
                q.emplace(steps + 1, ni, nj);
                vis[ni][nj] = true;
            }
        }
        sort(ans.begin(), ans.end());
        vector<vector<int>> ret;
        for (int i = 0; i < min(k, (int)ans.size()); ++i)
            ret.push_back(vector<int>{get<2>(ans[i]), get<3>(ans[i])});
        return ret;
    }
};
```

:::

## Problem D - [分隔长廊的方案数](https://leetcode-cn.com/problems/number-of-ways-to-divide-a-long-corridor/)

### 方法一：动态规划

从左到右依次考虑。有影响的是当前最后一个还没有隔断的长廊。我们需要知道这一个长廊中已经有几个座位。这里一共有三种情况：

- 没有座位
- 一个座位
- 两个座位

在遇到一个新的座位时：

- 如果原来没有座位，现在变为一个座位
- 如果原来有一个座位，我们可以选择在当前座位后隔断，则变为没有座位；也可以选择不在当前座位后隔断，则变为两个座位
- 如果原来已经有两个座位，这种情况不合法

在遇到一个非座位时：

- 如果原来没有座位或有一个座位，我们只能保持原样
- 如果原来有两个座位，我们可以选择隔断或不隔断

将所有情况讨论清楚之后，代码的实现是非常简单的。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;

class Solution {
public:
    int numberOfWays(string corridor) {
        int seats = 0;
        for (char ch : corridor)
            seats += ch == 'S';
        if (seats % 2 != 0)
            return 0;
        
        int zero = 1, one = 0, two = 0;
        for (char ch : corridor) {
            if (ch == 'S') {
                int tmp = zero;
                zero = two = one;
                one = zero;
            } else {
                zero = (zero + two) % MOD;
            }
        }
        
        return two;
    }
};
```

:::

<Utterances />
