# Leetcode 第224场周赛题解

## Problem A - [可以形成最大正方形的矩形数目](https://leetcode.cn/problems/number-of-rectangles-that-can-form-the-largest-square/)

显然一个矩形能够构成的最大正方形的边长为$\min(l,w)$，找出最大边长然后计数即可。当然也可以一次遍历，同时记录当前最大值的频次，不过时间复杂度是一样的。

- 时间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countGoodRectangles(self, rectangles: List[List[int]]) -> int:
        maxlen = max(min(l, w) for l, w in rectangles)
        return sum(1 for l, w in rectangles if min(l, w) == maxlen)
```

:::

## Problem B - [同积元组](https://leetcode.cn/problems/tuple-with-same-product/)

先统计出所有的乘积出现的频次。如果一个乘积出现了$k$次，则能够构成$4k(k-1)$个同积元组。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def tupleSameProduct(self, nums: List[int]) -> int:
        n = len(nums)
        cnt = collections.Counter(nums[i] * nums[j] for i in range(n) for j in range(i + 1, n))
        return sum(4 * value * (value - 1) for value in cnt.values())
```

:::

## Problem C - [重新排列后的最大子矩阵](https://leetcode.cn/problems/largest-submatrix-with-rearrangements/)

首先逐列进行预处理，从最下方的行开始逆序进行动态规划，得到从每一个位置开始向下最长延伸的连续$1$的段的长度。

接下来逐行处理，将这一行对应的预处理结果逆序排列，然后遍历更新最大值。由于已经逆序排列，所以对第$i$行的处理遍历到第$j$个元素时对应的最大矩形高度就是$f[j][i]$（为提高性能，预处理的$f$数组是按照列优先进行存储的），从而对应的矩形面积为$(j+1)\cdot f[j][i]$（因为$j$是从$0$开始的）。

- 时间复杂度$\mathcal{O}(MN\log N)$，其中$M$是矩阵的行数，$N$是矩阵的列数。
- 空间复杂度$\mathcal{O}(MN)$。

::: details 参考代码（Python）

```python
class Solution:
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        m = len(matrix)
        n = len(matrix[0])
        f = [[0] * m for _ in range(n)]
        for col in range(n):
            for row in range(m - 1, -1, -1):
                if matrix[row][col] == 1:
                    f[col][row] = 1
                    if row + 1 < m:
                        f[col][row] += f[col][row + 1]
        ans = 0
        for row in range(m):
            g = [f[col][row] for col in range(n)]
            g.sort(reverse=True)
            for i in range(n):
                ans = max(ans, g[i] * (i + 1))
        return ans
            
```

:::

## Problem D - [猫和老鼠 II](https://leetcode.cn/problems/cat-and-mouse-ii/)

本题的难点在于状态图并非DAG（有向无环图），所以，解题关键在于破环。如何破环？我们有两种方法。

### 方法一：增加时间维，将状态图变为DAG

- 时间复杂度$\mathcal{O(n^3m^3)}$，因为总状态数为$n^2m^2T$，其中$T=2nm$。

::: details 参考代码（Python）

```python
class Solution:
    def canMouseWin(self, grid: List[str], catJump: int, mouseJump: int) -> bool:
        rows = len(grid)
        cols = len(grid[0])
        print('\n'.join(grid))
        
        def neighbors(pos, step):
            r, c = pos
            yield (r, c)
            for dr, dc in [(-1, 0), (0, -1), (1, 0), (0, 1)]:
                for k in range(1, step + 1):
                    nr = r + k * dr
                    nc = c + k * dc
                    if nr < 0 or nr >= rows or nc < 0 or nc >= cols or grid[nr][nc] == '#':
                        break
                    yield (nr, nc)
        
        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == 'C':
                    cat = (i, j)
                if grid[i][j] == 'M':
                    mouse = (i, j)
                if grid[i][j] == 'F':
                    food = (i, j)
        
        @functools.lru_cache(None)
        def solve(mouse, cat, turn):
            if mouse == cat or cat == food or turn > 2 * rows * cols:
                return False
            if mouse == food:
                return True
            if turn % 2 == 0:
                for mouse_nxt in neighbors(mouse, mouseJump):
                    if solve(mouse_nxt, cat, turn + 1):
                        return True
                return False
            else:
                for cat_nxt in neighbors(cat, catJump):
                    if not solve(mouse, cat_nxt, turn + 1):
                        return False
                return True
            
        return solve(mouse, cat, 0)
```

:::

### 方法二：使用变形拓扑排序，从确定结果的状态逆向求解

- 时间复杂度$\mathcal{O}(V+E)=\mathcal{O}(n^2m^2(m+n))$。

::: details 参考代码（C++）

```cpp
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1}; 

class Solution {
    int n;
    
    int encode(int c, int m, int m_move) {
        return 2 * (c * n + m) + m_move;
    }

    tuple<int, int, int> decode(int code) {
        return {code / (2 * n), code % (2 * n) / 2, code % 2};
    }
public:
    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        int rows = grid.size(), cols = grid[0].size();
        n = rows * cols;
        int cat, mouse, food;
        vector<vector<int>> madj(n), cadj(n);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '#')
                    continue;
                int u = i * cols + j;
                if (grid[i][j] == 'C')
                    cat = u;
                if (grid[i][j] == 'M')
                    mouse = u;
                if (grid[i][j] == 'F')
                    food = u;
                madj[u].emplace_back(u);
                cadj[u].emplace_back(u);
                for (int k = 0; k < 4; ++k) {
                    for (int d = 1; d <= max(catJump, mouseJump); ++d) {
                        int ni = i + dy[k] * d, nj = j + dx[k] * d;
                        if (ni < 0 || ni >= rows || nj < 0 || nj >= cols || grid[ni][nj] == '#')
                            break;
                        int v = ni * cols + nj;
                        if (d <= catJump)
                            cadj[u].emplace_back(v);
                        if (d <= mouseJump)
                            madj[u].emplace_back(v);
                    }
                }
            }
        
        int max_state = n * n * 2;
        vector<int> result(max_state), in_degree(max_state);
        vector<vector<int>> adj(max_state);
        queue<int> q;
        
        auto assign_state = [&](int c, int m, int m_move, int state) {
            int code = encode(c, m, m_move);
            result[code] = state;
            q.emplace(code);
        };
        
        for (int i = 0; i < n; ++i) {
            if (i != food) {
                assign_state(i, i, 1, -1);
                assign_state(food, i, 1, -1);
                assign_state(i, food, 0, -1);
            }
        }
        
        for (int i = 0; i < max_state; ++i) {
            auto [c, m, m_move] = decode(i);
            if (m_move) {
                for (int nm : madj[m]) {
                    int pre = encode(c, nm, 0);
                    adj[pre].emplace_back(i);
                    in_degree[i]++;
                }
            } else {
                for (int nc : cadj[c]) {
                    int pre = encode(nc, m, 1);
                    adj[pre].emplace_back(i);
                    in_degree[i]++;
                }
            }
        }
            
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            auto [c, m, m_move] = decode(curr);
            for (int pre : adj[curr]) {
                in_degree[pre]--;
                if (result[pre] != 0)
                    continue;
                if (result[curr] == -1) {
                    result[pre] = 1;
                    q.emplace(pre);
                } else if (in_degree[pre] == 0) {
                    result[pre] = -1;
                    q.emplace(pre);
                }
            }
        }
        
        return result[encode(cat, mouse, 1)] == 1;
    }
};
```

:::

<Utterances />
