# Leetcode 第54场双周赛题解

## Problem A - [检查是否区域内所有整数都被覆盖](https://leetcode.cn/problems/check-if-all-the-integers-in-a-range-are-covered/)

### 方法一：暴力

本题数据范围较小，因此我们可以暴力枚举范围内的每一个数，然后判断是否有一个区间将其包含。

- 时间复杂度$\mathcal{O}(NM)$，其中$M=R-L+1$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def isCovered(self, ranges: List[List[int]], left: int, right: int) -> bool:
        for i in range(left, right + 1):
            found = False
            for l, r in ranges:
                if l <= i <= r:
                    found = True
                    break
            if not found:
                return False
        return True
```

:::

### 思考：

对于更大的数据范围，应当如何做？

## Problem B - [找到需要补充粉笔的学生编号](https://leetcode.cn/problems/find-the-student-that-will-replace-the-chalk/)

### 方法一：贪心

每一个轮次一共会消耗$\sum chalk_i$支粉笔。因此，我们首先将$k$对这一总和取余。

接下来，我们依次为学生分配粉笔，直到找到第一个需要补充粉笔的学生。

- 时间复杂度为$\mathcal{O}(N)$。

- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def chalkReplacer(self, chalk: List[int], k: int) -> int:
        s = sum(chalk)
        k %= s
        for i, num in enumerate(chalk):
            if k < num:
                return i
            k -= num
        return -1
```

:::

### 思考：

如果每个学生有一个需要粉笔的上限（取到这个上限之后这个学生就不参与后续的轮次），应当如何做？

## Problem C - [最大的幻方](https://leetcode.cn/problems/largest-magic-square/)

### 方法一：前缀和+暴力

计算出每行和每列的前缀和后，从大到小，暴力枚举所有的正方形区域，判断其是否是幻方。

- 时间复杂度$\mathcal{O}(N^2M^2)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> rowsum(n, vector<int>(m + 1));
        vector<vector<int>> colsum(m, vector<int>(n + 1));
        for (int i = 0; i < n; ++i)
            for (int j = 1; j <= m; ++j)
                rowsum[i][j] = rowsum[i][j - 1] + grid[i][j - 1];
        for (int j = 0; j < m; ++j)
            for (int i = 1; i <= n; ++i)
                colsum[j][i] = colsum[j][i - 1] + grid[i - 1][j];
        
        int k = min(m, n);
        for (int s = k; s >= 2; --s) {
            for (int i = 0; i + s <= n; ++i)
                for (int j = 0; j + s <= m; ++j) {
                    int sum = rowsum[i][j + s] - rowsum[i][j];
                    bool good = true;
                    for (int p = 1; p < s; ++p)
                        if (rowsum[i + p][j + s] - rowsum[i + p][j] != sum) {
                            good = false;
                            break;
                        }
                    if (!good)
                        continue;
                    int dsum1 = 0, dsum2 = 0;
                    for (int p = 0; p < s; ++p) {
                        if (colsum[j + p][i + s] - colsum[j + p][i] != sum) {
                            good = false;
                            break;
                        }
                        dsum1 += grid[i + p][j + p];
                        dsum2 += grid[i + p][j + s - 1 - p];
                    }
                    if (dsum1 != sum || dsum2 != sum)
                        good = false;
                    if (good)
                        return s;
                }
        }
        
        return 1;
    }
};
```

:::

## Problem D - [反转表达式值的最少操作次数](https://leetcode.cn/problems/minimum-cost-to-change-the-final-value-of-expression/) 

### 方法一：栈+动态规划

一道经典的表达式处理问题，我们使用操作符栈+操作数栈的经典双栈方式来进行模拟。

注意这里的“操作数”实际上是一个二元的状态$(p, q)$，其中$p$代表将当前“操作数”对应的范围变为$0$所需的最小操作次数，$q$代表将当前的“操作数”对应的范围变为$1$所需的最小操作次数。

显然，单个的$0$对应于状态$(0,1)$，而单个的$1$对应于状态$(1,0)$。

本题中，除括号外所有运算符优先级相同，需要从左到右进行运算，因此我们每得到一个新的“操作数”（这里既包括由单个的$0$或$1$带来的“操作数”，也包括`)`导致的出栈情形——对于上一层来说，这一层带来了一个新的“操作数”），就应当在上一个操作符不为`(`时将当前的“操作数”与上一个“操作数”进行一次“运算”，合并为一个新的“操作数”。

下面我们需要考虑如何实现“运算”。

假设待合并的两个状态为$(p_1,q_1)$和$(p_2,q_2)$。

如果当前操作符为`&`，则：

- 我们如果要得到$0$，只需要有一边为$0$，代价为$\min(p_1,p_2)$。

- 我们如果要得到$1$，需要左右两边同时为$1$，代价为$q_1+q_2$；或者将操作符变为`|`，同时只需要左右有一边为$1$，代价为$\min(q_1,q_2)+1$。

如果当前操作符为`|`，则：

- 我们如果要得到$0$，需要左右两边同时为$0$，代价为$p_1+p_2$；或者将操作符变为`&`，同时只需要左右有一边为$0$，代价为$\min(p_1,p_2)+1$。
- 我们如果要得到$1$，只需要有一边为$1$，代价为$\min(q_1,q_2)$。

这样我们就实现了操作数之间的运算。

所有操作执行完毕后，我们的操作数栈将只包含一个元素。这个元素必定包含一个零值（对应于表达式原本的值）和一个非零值。而这个非零值就是我们要寻找的答案。

总的复杂度为：

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minOperationsToFlip(self, expression: str) -> int:
        states = []
        ops = []
                
        for c in expression:
            if c in '01)':
                if c == '0':
                    states.append((0, 1))
                elif c == '1':
                    states.append((1, 0))
                else:
                    assert(ops[-1] == '(')
                    ops.pop()
                    
                if len(ops) > 0 and ops[-1] != '(':
                    op = ops.pop()
                    p2, q2 = states.pop()
                    p1, q1 = states.pop()
                    if op == '&':
                        states.append((min(p1, p2), min(q1 + q2, 1 + min(q1, q2))))
                    else:
                        states.append((min(p1 + p2, 1 + min(p1, p2)), min(q1, q2)))
            else:
                ops.append(c)
        
        return max(states[-1])
```

:::

<Utterances />
