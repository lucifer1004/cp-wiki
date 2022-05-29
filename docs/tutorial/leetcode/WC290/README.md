# Leetcode 第290场周赛题解

## Problem A - [多个数组求交集](https://leetcode.cn/problems/intersection-of-multiple-arrays/)

### 方法一：模拟

按要求模拟即可。

::: details 参考代码（Python 3）

```python
class Solution:
    def intersection(self, nums: List[List[int]]) -> List[int]:
        return sorted(list(functools.reduce(lambda a, x: a & x, map(set, nums))))
```

:::

## Problem B - [统计圆内格点数目](https://leetcode.cn/problems/count-lattice-points-inside-a-circle/)

### 方法一：暴力

- 时间复杂度 $\mathcal{O}(NRC)$，$R$ 和 $C$ 为行列方向的搜索范围。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countLatticePoints(self, circles: List[List[int]]) -> int:
        xmin = min(x - r for x, y, r in circles)
        xmax = max(x + r for x, y, r in circles)
        ymin = min(y - r for x, y, r in circles)
        ymax = max(y + r for x, y, r in circles)
        ans = 0
        for x in range(xmin, xmax + 1):
            for y in range(ymin, ymax + 1):
                found = False
                for xi, yi, r in circles:
                    if (x - xi) ** 2 + (y - yi) ** 2 <= r ** 2:
                        found = True
                        break
                if found:
                    ans += 1
        return ans
```

:::


## Problem C - [统计包含每个点的矩形数目](https://leetcode.cn/problems/count-number-of-rectangles-containing-each-point/)

### 方法一：沿 y 方向枚举

- 时间复杂度 $\mathcal{O}(N\log N+M\log M+MY_{\max}\log N)$。
- 空间复杂度 $\mathcal{O}(N+M+Y_{\max})$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        int n = rectangles.size(), m = points.size();
        int ymax = 0;
        for (int i = 0; i < n; ++i)
            ymax = max(ymax, rectangles[i][1]);
        for (int i = 0; i < m; ++i)
            ymax = max(ymax, points[i][1]);
        vector<vector<int>> y(ymax + 1);
        for (int i = 0; i < n; ++i) {
            y[rectangles[i][1]].push_back(rectangles[i][0]);
        }
        for (int i = 0; i <= ymax; ++i)
            sort(y[i].begin(), y[i].end());
        vector<int> ans(m);
        for (int i = 0; i < m; ++i) {
            for (int j = points[i][1]; j <= ymax; ++j) {
                ans[i] += y[j].end() - upper_bound(y[j].begin(), y[j].end(), points[i][0] - 1);
            }
        }
        return ans;
    }
};
```

:::

### 方法二：双指针+平衡二叉搜索树

将矩形和点均按照 $x$ 坐标降序排序，然后用平衡二叉搜索树维护当前所有的 $y$ 值。

- 时间复杂度 $\mathcal{O}(N\log N+M\log M+(M+N)\log \min(N, Y_{\max}))$。
- 空间复杂度 $\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        int n = rectangles.size(), m = points.size();
        sort(rectangles.rbegin(), rectangles.rend());
        vector<int> order(m);
        for (int i = 0; i < m; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return points[i][0] > points[j][0]; 
        });
        vector<int> ans(m);
        ordered_set os;
        int ptr = 0;
        for (int i = 0; i < m; ++i) {
            int id = order[i];
            while (ptr < n && rectangles[ptr][0] >= points[id][0]) {
                os.insert(rectangles[ptr][1]);
                ptr++;
            }
            ans[id] = (int)os.size() - os.order_of_key(points[id][1]);
        }
        return ans;
    }
};
```

:::

## Problem D - [花期内花的数目](https://leetcode.cn/problems/number-of-flowers-in-full-bloom/)

### 方法一：双指针 + 小根堆

所有花按照花期开始时间排序，所有人按照访问时间排序。用小根堆维护当前开着的花的花期的结束时间。

- 时间复杂度 $\mathcal{O}((N+M)\log N + M\log M)$。
- 空间复杂度 $\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& persons) {
        int n = flowers.size(), m = persons.size();
        vector<int> ans(m);
        vector<int> order(m);
        for (int i = 0; i < m; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j) {
            return persons[i] < persons[j];
        });

        sort(flowers.begin(), flowers.end());
        int ptr = 0;
        priority_queue<int, vector<int>, greater<>> pq;
        for (int i = 0; i < m; ++i) {
            int idx = order[i];
            while (ptr < n && flowers[ptr][0] <= persons[idx]) {
                pq.push(flowers[ptr][1]);
                ptr++;
            }
            while (!pq.empty() && pq.top() < persons[idx])
                pq.pop();
            ans[idx] = pq.size();
        }
        
        return ans;
    }
};
```

:::

<Utterances />
