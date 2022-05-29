# Leetcode 第64场双周赛题解

## Problem A - [数组中第 K 个独一无二的字符串](https://leetcode.cn/problems/kth-distinct-string-in-an-array/)

### 方法一：模拟

统计出所有字符串的出现频次即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def kthDistinct(self, arr: List[str], k: int) -> str:
        cnt = collections.Counter(arr)
        uniq = [s for s in arr if cnt[s] == 1]
        return uniq[k - 1] if len(uniq) >= k else ""
```

:::


## Problem B - [两个最好的不重叠活动](https://leetcode.cn/problems/two-best-non-overlapping-events/)

### 方法一：排序+优先队列

将所有活动按开始时间排序后，我们可以这样考虑选择两个活动：
- 选择此刻已经结束的活动中价值最大的。
- 选择当前活动。

我们可以用一个优先队列（以结束时间为权重建立小根堆）维护当前尚未结束的活动，并记录当前已经结束的活动的最大价值。

- 时间复杂度为$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());
        int ans = 0, hi = 0, n = events.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (int i = 0; i < n; ++i) {
            int s = events[i][0], e = events[i][1], v = events[i][2];
            while (!pq.empty() && pq.top().first < s) {
                hi = max(hi, pq.top().second);
                pq.pop();
            }
            ans = max(ans, hi + v);
            pq.emplace(e, v);
        }
        return ans;
    }
};
```

:::

## Problem C - [蜡烛之间的盘子](https://leetcode.cn/problems/plates-between-candles/)

### 方法一：前缀和

我们可以利用前缀和的方法求出以下三个值：
- `plates[i]`代表$[1,i]$中盘子的总数
- `rcandle[i]`代表$[1,i]$中最靠右的蜡烛的位置
- `lcandle[i]`代表$[i+1,n]$中最靠左的蜡烛的位置

对于每一询问，我们利用`lcandle`和`rcandle`找到询问对应的区间中最左边的蜡烛和最右边的蜡烛，然后利用`plates`即可计算出盘子的数目。

- 时间复杂度$\mathcal{O}(N+Q)$。
- 空间复杂度$\mathcal{O}(N+Q)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> plates(n + 1), lcandle(n + 1, n + 1), rcandle(n + 1);
        for (int i = 1; i <= n; ++i) {
            plates[i] = plates[i - 1];
            rcandle[i] = rcandle[i - 1];
            if (s[i - 1] == '*')
                plates[i]++;
            else
                rcandle[i] = i;
        }
        for (int i = n - 1; i >= 0; --i) {
            lcandle[i] = lcandle[i + 1];
            if (s[i] == '|')
                lcandle[i] = i + 1;
        }
        
        int q = queries.size();
        vector<int> ans(q);
        for (int i = 0; i < q; ++i) {
            int l = queries[i][0] + 1, r = queries[i][1] + 1;
            int lc = lcandle[l - 1], rc = rcandle[r];
            if (lc >= rc)
                continue;
            ans[i] = plates[rc] - plates[lc];
        }
        
        return ans;
    }
};
```

:::

## Problem D - [棋盘上有效移动组合的数目](https://leetcode.cn/problems/number-of-valid-move-combinations-on-chessboard/)

### 方法一：模拟

按题意枚举所有可能的移动组合并检查是否有效即可。

- 时间复杂度$\mathcal{O}(64^N\cdot N^2)$。但由于限制了最多有一个皇后，实际最大的复杂度是$\mathcal{O}(64\cdot 32^{N-1}\cdot N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
const int d[8][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

class Solution {
    vector<vector<int>> positions, possible;
    int n, ans = 0;
    vector<int> direction, step, xinit, yinit;
    
    bool valid(int x, int y) {
        return x >= 1 && x <= 8 && y >= 1 && y <= 8;
    }
    
    void check() {
        vector<int> x(xinit), y(yinit), s(step);
        bool go = true;
        while (go) {
            go = false;
            for (int i = 0; i < n; ++i) {
                if (s[i] > 0) {
                    s[i]--;
                    x[i] += d[direction[i]][0];
                    y[i] += d[direction[i]][1];
                }
                if (s[i])
                    go = true;
            }
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    if (x[i] == x[j] && y[i] == y[j])
                        return;
        }
        ans++;
    }
    
    void dfs(int i) {        
        if (i == n) {
            check();
        } else {
            direction.push_back(0);
            step.push_back(0);
            dfs(i + 1);
            direction.pop_back();
            step.pop_back();
            
            for (int j = 1; j < 8; ++j) {
                for (int k : possible[i]) {
                    int x = positions[i][0] + d[k][0] * j, y = positions[i][1] + d[k][1] * j;
                    if (valid(x, y)) {
                        direction.push_back(k);
                        step.push_back(j);
                        dfs(i + 1);
                        direction.pop_back();
                        step.pop_back();
                    }
                }
            }
        }
    }
public:
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        n = pieces.size();
        possible = vector<vector<int>>(n);
        this->positions = positions;
        xinit = vector<int>(n), yinit = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            xinit[i] = positions[i][0], yinit[i] = positions[i][1];
            if (pieces[i] != "rook") {
                possible[i].emplace_back(1);
                possible[i].emplace_back(3);
                possible[i].emplace_back(5);
                possible[i].emplace_back(7);
            }
            if (pieces[i] != "bishop") {
                possible[i].emplace_back(0);
                possible[i].emplace_back(2);
                possible[i].emplace_back(4);
                possible[i].emplace_back(6);
            }
        }
        
        dfs(0);
        
        return ans;
    }
};
```

:::

<Utterances />
