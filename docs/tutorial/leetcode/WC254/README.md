# Leetcode 第254场周赛题解

## Problem A - [作为子字符串出现在单词中的字符串数目](https://leetcode.cn/problems/number-of-strings-that-appear-as-substrings-in-word/)

### 方法一：暴力

逐个检查即可。

::: details 参考代码（Python 3）

```python
class Solution:
    def numOfStrings(self, patterns: List[str], word: str) -> int:
        return sum(1 if pattern in word else 0 for pattern in patterns)
```

:::

### 方法二：AC自动机（略）

## Problem B - [构造元素不等于两相邻元素平均值的数组](https://leetcode.cn/problems/array-with-elements-not-equal-to-average-of-neighbors/)

### 方法一：排序+贪心

Leetcode也开始出构造题了？

本题最简单的解法就是排序之后，先放所有奇数位置，再放所有偶数位置，这样就可以保证所有元素的相邻元素要么都比它大，要么都比它小，从而一定符合要求。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> ans(n);
        int ptr = 0;
        for (int i = 0; i < n; i += 2)
            ans[i] = nums[ptr++];
        for (int i = 1; i < n; i += 2)
            ans[i] = nums[ptr++];
        return ans;
    }
};
```

:::

## Problem C - [数组元素的最小非零乘积](https://leetcode.cn/problems/minimum-non-zero-product-of-the-array-elements/)

### 方法一：贪心

观察样例会发现，我们可以将所有小于$2^P-1$的元素按照$[x, 2^P-1-x]$的方式两两配对，然后将每一对经过若干次操作后都变为$[1, 2^P-2]$，这样最后的乘积就是$(2^P-2)^{2^{P-1}-1}*(2^P-1)$。

这里给出一个不太严格的说明：

- 因为每次操作不改变所有元素的总和，而我们知道总和一定时，要想乘积最小，应该让元素尽可能向两侧分布。
- 最大的$2^P-1$无论与哪一个其他元素进行交换，乘积都不会减小，因此我们将其放在一边。
- 对于剩下的元素，如果不按照上面的方式进行配对，那么一定会有一对元素，某一个二进制位上都为$1$；同时有另一对元素，某一个二进制位上都为$0$，这时我们将第一对中的一个元素的$1$换给第二对中的一个元素，我们就可以使得这四个元素在总和不变的情况下乘积减小。因此最优的配对中，一定是每一对元素的异或值都为$0$。
- 在固定异或值为$0$的情况下，可以得到的单对元素的最小非零乘积就是$1\times2^P-2=2^P-2$。
- 最后的操作结果就如上面所说。

复杂度为：

- 时间复杂度$\mathcal{O}(P)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
mod = 1000000007

class Solution:
    def minNonZeroProduct(self, p: int) -> int:
        if p == 1:
            return 1
        
        hi = (1 << p) - 1
        return pow(hi - 1, (hi - 1) >> 1, mod) * hi % mod
```

:::

## Problem D - [你能穿过矩阵的最后一天](https://leetcode.cn/problems/last-day-where-you-can-still-cross/)

### 方法一：二分答案+多源BFS

容易想到二分答案的思路。每次可以构造出当前的图，然后以所有第一行的点作为源点，跑一次多源BFS来判断是否能到达最后一行。

- 时间复杂度$\mathcal{O}(RC\log RC)$。
- 空间复杂度$\mathcal{O}(RC)$。

::: details 参考代码（C++）

```cpp
const int d[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int lo = 0, hi = row * col;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            vector<vector<bool>> mat(row, vector<bool>(col, true)), vis(row, vector<bool>(col));
            for (int i = 0; i < mid; ++i)
                mat[cells[i][0] - 1][cells[i][1] - 1] = false;
            queue<pair<int, int>> q;
            for (int i = 0; i < col; ++i)
                if (mat[0][i])
                    q.emplace(0, i), vis[0][i] = true;
            bool can = false;
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                if (r == row - 1) {
                    can = true;
                    break;
                }
                for (int k = 0; k < 4; ++k) {
                    int nr = r + d[k][0], nc = c + d[k][1];
                    if (nr >= 0 && nr < row && nc >= 0 && nc < col && mat[nr][nc] && !vis[nr][nc]) {
                        vis[nr][nc] = true;
                        q.emplace(nr, nc);
                    }
                }
            }
            if (can)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return hi;
    }
};
```

:::

### 方法二：倒序处理+并查集

更好的做法是并查集。正序处理需要从并查集中删边，这是难于实现的；但如果我们倒序处理，就只需要连边了。

这里为了方便处理，我们增加了一个源点$S$与所有第一行的点相连，一个汇点$T$与所有最后一行的点相连。当我们处理到某一位置时，只要判断$S$和$T$是否在同一个连通块中，就可以知道是否能从第一行走到最后一行。

注意本题中每次新增（倒序处理时）的是点，所以我们需要用一个额外的数组记录每个点当前是否已经存在，在连边时，只将当前点与其周围已经存在的点相连，否则将导致错误。（举个例子，假设$(2,1)$和$(2,3)$已经存在，而$(2,2)$还不存在，如果在连边时不进行存在性判断，就会导致$(2,1)$和$(2,3)$通过并不存在的$(2,2)$连接了起来。）

- 时间复杂度$\mathcal{O}(RC\alpha(RC))$。
- 空间复杂度$\mathcal{O}(RC)$。

::: details 参考代码（C++）

```cpp
const int d[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

class UnionFind {
  int n;
  vector<int> parent, size;

public:
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

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        UnionFind uf(row * col + 2);
        int S = row * col, T = row * col + 1;
        vector<vector<bool>> exist(row, vector<bool>(col));
        for (int i = row * col - 1; i >= 0; --i) {
            int r = cells[i][0] - 1, c = cells[i][1] - 1;
            if (r == 0)
                uf.connect(S, c);
            if (r == row - 1)
                uf.connect(T, r * col + c);
            exist[r][c] = true;
            for (int k = 0; k < 4; ++k) {
                int nr = r + d[k][0], nc = c + d[k][1];
                if (nr >= 0 && nr < row && nc >= 0 && nc < col && exist[nr][nc])
                    uf.connect(r * col + c, nr * col + nc);
            }
            if (uf.find(S) == uf.find(T))
                return i;
        }
        
        return -1; // Should not return from here.
    }
};
```

:::

<Utterances />
