# Leetcode 第257场周赛题解

## Problem A - [统计特殊四元组](https://leetcode-cn.com/problems/count-special-quadruplets/)

### 方法一：穷举

$N\leq50$，因此$\mathcal{O}(N^4)$的穷举即可通过本题。

- 时间复杂度$\mathcal{O}(N^4)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = j + 1; k < n; ++k)
                    for (int t = k + 1; t < n; ++t)
                        if (nums[i] + nums[j] + nums[k] == nums[t])
                            ans++;
        return ans;
    }
};
```

:::

### 方法二：哈希表

时间复杂度更优的方法是使用哈希表，从而利用到$MAXN\leq100$这一条件。

我们可以将单元素、双元素和三元素的和分别用三个哈希表进行计数。

遍历时，三元素和哈希表中与当前数字对应的键值就是以当前数字作为$d$可以增加的答案数。

之后，我们按照三、二、一的顺序对哈希表进行更新。

- 时间复杂度$\mathcal{O}(N\cdot MAXN)$。
- 空间复杂度$\mathcal{O}(MAXN)$。

::: details 参考代码（Python 3）

```python
from collections import Counter

class Solution:
    def countQuadruplets(self, nums: List[int]) -> int:
        single = Counter()
        double = Counter()
        triple = Counter()
        ans = 0
        for num in nums:
            ans += triple[num]
            for d in double:
                triple[d + num] += double[d]
            for s in single:
                double[s + num] += single[s]
            single[num] += 1
        return ans
```

:::

## Problem B - [游戏中弱角色的数量](https://leetcode-cn.com/problems/the-number-of-weak-characters-in-the-game/)

### 方法一：排序

对于这种有两个维度的问题，一个常见的方法就是对其中一个维度进行排序。

这里我们将第一维逆序排列（同时第二维也是逆序），这样在遍历时就能保证一个角色前面的角色在第一维上都不小于他，从而只要前面角色的第二维的最大值比他大，就能保证找到一个第一维不小于他，且第二维大于他的角色。但题目要求的是两个维度都严格大于，所以这里还需要一些特殊处理，也即对第二维最大值的更新不是在遍历每个元素时立刻进行，而是在遍历到一个第一维比上一元素第一维小的元素时，才用之前的元素去更新第二维的最大值。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        int n = properties.size();
        sort(properties.rbegin(), properties.rend());
        int ans = 0, bhi = 0, last = 0;
        for (int i = 0; i < n; i++) {
            int a = properties[i][0], b = properties[i][1];
            if (i > 0 && a < properties[i - 1][0]) {
                bhi = max(bhi, properties[last][1]);
                last = i;
            }
            if (b < bhi)
                ans++;
        }

        return ans;
    }
};
```

:::

## Problem C - [访问完所有房间的第一天](https://leetcode-cn.com/problems/first-day-where-you-have-been-in-all-the-rooms/)

### 方法一：脑筋急转弯+动态规划

本题的关键是理解题意。

令$dp[i]$表示第一次走到第$i$个房间的天数。我们考虑当前第一次走到了房间$i-1$，一共用去$dp[i-1]$天，接下来我们花一天时间去往$nextVisit[i-1]$。下面就到了关键点：

假设$nextVisit[i-1]\neq i-1$，则我们来到$nextVisit[i-1]$时的状态，应当是恰好$nextVisit[i-1]$和$i-1$被访问了奇数次，其余房间都被访问了偶数次（包括$0$次）。因此这一状态与我们第一次来到$nextVisit[i-1]$时的差别只在于$i-1$的访问状态，那么我们就可以得出：从$nextVisit[i-1]$到$i-1$的用时为$dp[i-1]-dp[nextVisit[i-1]]$天。接下来，我们再花一天到达$i$。

> $nextVisit[i]\leq i$是上面的分析成立的前提。

因此可以得到$dp[i]=2dp[i-1]-dp[nextVisit[i-1]]+2$。

对于$nextVisit[i-1]=i-1$的情形，易知上式同样成立。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;

class Solution {
public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        int n = nextVisit.size();
        vector<int> dp(n);
        for (int i = 1; i < n; ++i) {
            dp[i] = (2 * dp[i - 1] - dp[nextVisit[i - 1]] + 2) % MOD;
            if (dp[i] < 0)
                dp[i] += MOD;
        }
        return dp[n - 1];
    }
};
```

:::

## Problem D - [数组的最大公因数排序](https://leetcode-cn.com/problems/gcd-sort-of-an-array/)

### 方法一：并查集

我们可以基于元素之间是否有公因数来构建一个并查集，容易发现，同一连通块中的元素的顺序总是可以任意调换的。

因此，我们按照连通块分别排序，最后检查得到的数组是否是不下降的即可。

- 时间复杂度$\mathcal{O}(N\sqrt{N})$。
- 空间复杂度$\mathcal{O}(N)$。

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
    
    unordered_map<int, vector<int>> components() {
        unordered_map<int, vector<int>> res;
        for (int i = 0; i < n; ++i)
            res[find(i)].emplace_back(i);
        return res;
    }
};

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size(), hi = *max_element(nums.begin(), nums.end());
        UnionFind uf(n);
        vector<vector<int>> ele(hi + 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j * j <= nums[i]; ++j) {
                if (nums[i] % j == 0) {
                    ele[j].emplace_back(i);
                    if (nums[i] / j != j)
                        ele[nums[i] / j].emplace_back(i);
                }
            }
        }
        for (int i = 2; i <= hi; ++i)
            for (int j = 0; j + 1 < ele[i].size(); ++j)
                uf.connect(ele[i][j], ele[i][j + 1]);
        
        auto c = uf.components();
        vector<int> nn(nums);
        for (auto [k, v] : c) {
            vector<int> vv(v);
            
            sort(vv.begin(), vv.end(), [&](int i, int j){
                return nums[i] < nums[j];
            });
            
            for (int i = 0; i < v.size(); ++i)
                nn[v[i]] = nums[vv[i]];
        }
        
        for (int i = 0; i + 1 < n; ++i)
            if (nn[i] > nn[i + 1])
                return false;
        
        return true;
    }
};
```

:::

<Utterances />
