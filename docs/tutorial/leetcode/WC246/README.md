# Leetcode 第246场周赛题解

## Problem A - [字符串中的最大奇数](https://leetcode.cn/problems/largest-odd-number-in-string/)

### 方法一：贪心

找到最后一个奇数数字即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string largestOddNumber(string num) {
        int n = num.size();
        int i = n - 1;
        while (i >= 0 && (num[i] - '0') % 2 == 0)
            i--;
        if (i == -1)
            return "";
        return num.substr(0, i + 1);
    }
};
```

:::

## Problem B - [你完成的完整对局数](https://leetcode.cn/problems/the-number-of-full-rounds-you-have-played/)

### 方法一：数学

首先将时间字符串转换成小时数和分钟数，然后计算即可。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
pair<int, int> get_hour_and_minute(string &time) {
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    return {hour, minute};
}

class Solution {
public:
    int numberOfRounds(string startTime, string finishTime) {
        auto [start_hour, start_minute] = get_hour_and_minute(startTime);
        auto [finish_hour, finish_minute] = get_hour_and_minute(finishTime);
        if (startTime > finishTime)
            finish_hour += 24;
        int ans = (finish_hour + 1 - start_hour) * 4 - (start_minute + 14) / 15 - (59 - finish_minute) / 15 - 1;
        return max(ans, 0);
    }
};  
```

:::

## Problem C - [统计子岛屿](https://leetcode.cn/problems/count-sub-islands/)

### 方法一：宽度优先搜索

使用宽度优先搜索（也可以使用深度优先搜索）遍历`grid2`中的每一个岛屿。如果一个岛屿中存在某个位置，其在`grid1`中的对应位置为水面，则这一岛屿不被计入答案。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
const int d[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int n = grid1.size(), m = grid1[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m));
        
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (vis[i][j] || !grid2[i][j])
                    continue;
                vis[i][j] = true;
                deque<pair<int, int>> q;
                q.emplace_back(i, j);
                bool good = true;
                
                while (!q.empty()) {
                    auto [ci, cj] = q.front();
                    q.pop_front();
                    if (!grid1[ci][cj])
                        good = false;
                    for (int k = 0; k < 4; ++k) {
                        int ni = ci + d[k][0], nj = cj + d[k][1];
                        if (ni < 0 || ni >= n || nj < 0 || nj >= m || vis[ni][nj] || !grid2[ni][nj])
                            continue;
                        vis[ni][nj] = true;
                        q.emplace_back(ni, nj);
                    }
                }
                
                if (good)
                    ans++;
            }
        
        return ans;
    }
};
```

:::

## Problem D - [查询差绝对值的最小值](https://leetcode.cn/problems/minimum-absolute-difference-queries/)

### 方法一：前缀和

考虑到本题中数组中的元素值不超过$100$，我们可以计算出每一元素出现次数的前缀和，然后对于每次查询，我们可以利用求出的前缀和快速判断出所查询的区间内出现了哪些数字，之后再遍历这些数字就可以求出答案。

- 时间复杂度$\mathcal{O}((N+Q)K)$，其中$K=100$。
- 空间复杂度$\mathcal{O}(NK)$。

::: details 参考代码（C++）

```cpp
const int K = 100;

class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int q = queries.size(), n = nums.size();
        vector<int> ans(q);
        
        vector<vector<int>> pre(K + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= K; ++j)
                pre[j][i] = pre[j][i - 1];
            pre[nums[i - 1]][i]++;
        }
        
        vector<int> v;
        v.reserve(K);
        
        for (int i = 0; i < q; ++i) {
            v.clear();
            int l = queries[i][0], r = queries[i][1];
            for (int j = 1; j <= K; ++j) {
                if (pre[j][r + 1] - pre[j][l] > 0)
                    v.emplace_back(j);
            }
            if (v.size() == 1)
                ans[i] = -1;
            else {
                ans[i] = K;
                for (int j = 0; j + 1 < v.size(); ++j)
                    ans[i] = min(ans[i], v[j + 1] - v[j]);
            }
        }
        
        return ans;
    }
};
```

:::

<Utterances />
