# Leetcode 第43场双周赛题解

## Problem A - [计算力扣银行的钱](https://leetcode-cn.com/problems/calculate-money-in-leetcode-bank/)

### 方法一：模拟

我们可以模拟计算每一天的钱数然后求和。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution:
    def totalMoney(self, n: int) -> int:
        num = [1] * n
        ans = 1
        for i in range(1, n):
            if i % 7 == 0:
                num[i] = num[i - 7] + 1
            else:
                num[i] = num[i - 1] + 1
            ans += num[i]
        return ans
```

:::

### 方法二：数学

注意到一周内每天的钱数是一个等差数列，同时完整的周的每周的总钱数也是一个等差数列。我们可以利用数学公式对等差数列进行求和。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Kotlin）

```kotlin
class Solution {
    fun totalMoney(n: Int): Int {
        val fullWeeks = n / 7;
        val startOfLastWeek = fullWeeks + 1;
        val daysOfLastWeek = n % 7;
        return (49 + 7 * fullWeeks) * fullWeeks / 2 + (startOfLastWeek * 2 + daysOfLastWeek - 1) * daysOfLastWeek / 2;
    }
}
```

:::

## Problem B - [删除子字符串的最大得分](https://leetcode-cn.com/problems/maximum-score-from-removing-substrings/)

我们假设$x\geq y$总是成立（如果不成立，我们就把所有`a`变成`b`，所有`b`变成`a`，然后交换$x$和$y$）。

接下来，对于每一段连续的`a`/`b`串，我们贪心地凑出`ab`，然后把最后剩下的`a`和`b`组成`ba`。

因为$x\geq y$，所以`ab`显然优于`ba`。同时每一个`a`/`b`串所能够组成的`ab`和`ba`对的总数永远是$\min(n_a,n_b)$，所以我们的贪心策略可以保证得到最优解。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(1)$

::: details 参考代码（JavaScript）

```js
var maximumGain = function(s, x, y) {
    const a = s.split('').map(c => {
        if (x > y || (c != 'a' && c != 'b'))
            return c;
        return c == 'a' ? 'b' : 'a';
    });
    if (x < y) {
        const tmp = x;
        x = y;
        y = tmp;
    }
    let ans = 0, na = 0, nb = 0;
    for (let c of a) {
        if (c != 'a' && c != 'b') {
            ans += Math.min(na, nb) * y;
            na = 0;
            nb = 0;
        } else if (c == 'a') {
            na++;
        } else {
            if (na > 0) {
                na--;
                ans += x;
            } else {
                nb++;
            }
        }
    }
    ans += Math.min(na, nb) * y;
    return ans;
};
```

:::

## Problem C - [构建字典序最大的可行序列](https://leetcode-cn.com/problems/construct-the-lexicographically-largest-valid-sequence/)

我们每次贪心地选取当前可选的最大的数字，然后回溯求解。这样我们找到的第一个可行解就是题目要求的字典序最大的解。

::: details 参考代码（C++）

```cpp
class Solution {
    bool ok;
    
    void rec(vector<int> &ans, set<int, greater<>> &s, int i) {
        if (i == ans.size()) {
            ok = true;
            return;
        }
        if (ok)
            return;
        if (ans[i])
            rec(ans, s, i + 1);
        vector<int> v(s.begin(), s.end());
        for (int vi : v) {
            if (vi != 1 && (i + vi >= ans.size() || ans[i + vi]))
                continue;
            ans[i] = vi;
            if (vi != 1)
                ans[i + vi] = vi;
            s.erase(vi);
            int idx = i + 1;
            while (idx < ans.size() && ans[idx])
                idx++;
            rec(ans, s, idx);
            if (ok)
                return;
            ans[i] = 0;
            if (vi != 1)
                ans[i + vi] = 0;
            s.insert(vi);
        }
    }
public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> ans(n * 2 - 1);
        set<int, greater<>> s;
        for (int i = 1; i <= n; ++i)
            s.insert(i);
        ok = false;
        rec(ans, s, 0);
        return ans;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def solve(self, pos):
        if pos == len(self.ans):
            self.found = True
        if self.found:
            return
        for i in range(self.n, 0, -1):
            if self.used[i] or (i > 1 and (pos + i >= len(self.ans) or self.ans[pos + i] != 0)):
                continue
            self.used[i] = True
            self.ans[pos] = i
            if i > 1:
                self.ans[pos + i] = i
            idx = pos + 1
            while idx < len(self.ans) and self.ans[idx] != 0:
                idx += 1
            self.solve(idx)
            if self.found:
                return
            self.used[i] = False
            self.ans[pos] = 0
            if i > 1:
                self.ans[pos + i] = 0
    
    def constructDistancedSequence(self, n: int) -> List[int]:
        self.found = False
        self.n = n
        self.ans = [0] * (2 * n - 1)
        self.used = [False] * (n + 1)
        self.solve(0)
        return self.ans
```

:::

## Problem D - [重构一棵树的方案数](https://leetcode-cn.com/problems/number-of-ways-to-reconstruct-a-tree/)

###  方法一：并查集+拓扑排序

- 利用并查集判断连通性，如果不连通，显然无解
- 遍历三元组，如果三元组构成的三个二元对只出现了两次，则可以确定出这三个数中哪一个应该作为根。
- 遍历二元组，如果该二元组出现了，但是两个数的关系未确定，则可能出现多解。
- 拓扑排序，判断是否有解。如果有解，再根据上一步结果判断是否多解。

::: details 参考代码（C++）

```cpp
struct UnionFind {
  int n;
  vector<int> parent, size;

  UnionFind(int n) {
    this->n = n;
    parent = vector<int>(n);
    size = vector<int>(n, 1);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int idx) {
    if (parent[idx] == idx)
      return idx;
    return parent[idx] = find(parent[idx]);
  }

  void connect(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb) {
      if (size[fa] > size[fb]) {
        parent[fb] = fa;
        size[fa] += size[fb];
      } else {
        parent[fa] = fb;
        size[fb] += size[fa];
      }
    }
  }
};

bool d[501][501], adj[501][501];
int in[501];

void init(int idx) {
    for (int i = 0; i < idx; ++i)
        for (int j = 0; j < idx; ++j)
            d[i][j] = adj[i][j] = false;
    for (int i = 0; i < idx; ++i)
        in[i] = 0;
}

class Solution {
public:
    int checkWays(vector<vector<int>>& pairs) {
        set<int> s;
        for (auto &v : pairs) {
            s.insert(v[0]);
            s.insert(v[1]);
        }
        unordered_map<int, int> mp;
        int idx = 0;
        for (int si : s)
            mp[si] = idx++;

        UnionFind uf(idx);
        init(idx);
        
        for (auto &v : pairs) {
            int p = mp[v[0]], q = mp[v[1]];
            uf.connect(p, q);
            d[p][q] = d[q][p] = true;
        }
        if (uf.size[uf.find(0)] != idx)
            return 0;
        
        for (auto &v : pairs) {
            int i = mp[v[0]], j = mp[v[1]];
            for (int k = 0; k < idx; ++k) {
                if (k == i || k == j)
                    continue;
                int tot = 1 + d[i][k] + d[j][k];
                if (tot != 2)
                    continue;
                if (d[i][k]) {
                    if (!adj[i][j]) {
                        adj[i][j] = true;
                        in[j]++;                        
                    }
                    if (!adj[i][k]) {
                        adj[i][k] = true;
                        in[k]++;                        
                    }
                } else {
                    if (!adj[j][i]) {
                        adj[j][i] = true;
                        in[i]++;                        
                    }
                    if (!adj[j][k]) {
                        adj[j][k] = true;
                        in[k]++;                        
                    }
                }
            }
        }
            
        bool large = false;
        for (int i = 0; i < idx && !large; ++i)
            for (int j = i + 1; j < idx && !large; ++j)
                if (d[i][j] && !adj[i][j] && !adj[j][i])
                    large = true;
        
        queue<int> q;
        for (int i = 0; i < idx; ++i)
            if (!in[i])
                q.emplace(i);
        
        vector<int> order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.emplace_back(u);
            for (int v = 0; v < idx; ++v) {
                if (adj[u][v]) {
                    if (!--in[v])
                        q.emplace(v);
                }
            }
        }
        
        if (order.size() != idx)
            return 0;
        
        return large ? 2 : 1;
    }
};
```

:::

<Utterances />
