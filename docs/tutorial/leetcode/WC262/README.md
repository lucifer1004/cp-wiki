# Leetcode 第262场周赛题解

## Problem A - [至少在两个数组中出现的值](https://leetcode-cn.com/problems/two-out-of-three/)

### 方法一：模拟

直接模拟即可。自带集合运算的语言（比如Python）会有一些优势。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def twoOutOfThree(self, nums1: List[int], nums2: List[int], nums3: List[int]) -> List[int]:
        s1 = set(nums1)
        s2 = set(nums2)
        s3 = set(nums3)
        return list((s1 & s2) | (s1 & s3) | (s2 & s3))
```

:::

## Problem B - [获取单值网格的最小操作数](https://leetcode-cn.com/problems/minimum-operations-to-make-a-uni-value-grid/)

### 方法一：贪心

首先，所有数如果不是关于$X$同余，则本题显然无解。

在所有数关于$X$同余的情况下，我们可以将所有数除以$X$。这时就变成了经典的数轴集合问题（$N$个人在数轴上，要集合到一个位置使得所有人移动距离之和最小），最优的集合位置就是中位数。我们找到这些数的中位数，再计算总距离（也即总操作数）即可。

寻找中位数可以排序；也可以使用快速选择算法（比如C++中的`nth_element`），以得到更优的时间复杂度。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int n = grid.size(), m = grid[0].size(), mod = grid[0][0] % x;
        vector<int> v;
        for (auto &row : grid)
            for (int cell : row) {
                if (cell % x != mod)
                    return -1;
                v.emplace_back(cell / x);
            }
        int mid = n * m / 2;
        nth_element(v.begin(), v.begin() + mid, v.end());
        int ans = 0;
        for (int vi : v)
            ans += abs(vi - v[mid]);
        return ans;
    }
};
```

:::

## Problem C - [股票价格波动](https://leetcode-cn.com/problems/stock-price-fluctuation/)

### 方法一：数据结构

一道比较基础的数据结构题。我们需要观察题目的条件，来选择合适的数据结构存储信息。

我们需要的信息有：

- 每个时间戳对应的价格
- 当前的最晚时间戳
- 当前的最低价格
- 当前的最高价格

记录时间戳对应的价格，自然想到用一个`map`或`unordered_map`，同时因为要求最晚时间，所以考虑使用有序数据结构`map`。

记录最低和最高价格，考虑使用有序数据结构`set`，但这里可能出现重复的价格，所以使用`multiset`。当然，也可以使用`map`来维护每个价格出现的次数。

- 各操作时间复杂度均为$\mathcal{O}(\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class StockPrice {
    multiset<int> prices;
    map<int, int> history;
    
public:
    StockPrice() {}
    
    void update(int timestamp, int price) {
        if (history.count(timestamp))
            prices.erase(prices.find(history[timestamp]));
        history[timestamp] = price;
        prices.insert(price);
    }
    
    int current() {
        return history.rbegin()->second;
    }
    
    int maximum() {
        return *prices.rbegin();
    }
    
    int minimum() {
        return *prices.begin();
    }
};
```

:::

## Problem D - [将数组分成两个数组并最小化数组和的差](https://leetcode-cn.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/)

### 方法一：Meet in the middle + 动态规划 + 双指针

要让两个数组和的差最小，就是要让其中一个数组的和尽可能接近$sum/2$。

直接枚举，在$N=15$时需要考虑${30\choose15} \approx1.5\times10^8$种情况（这里还没有考虑每种情况需要求和），显然会超时。

因此，我们考虑使用Meet in the middle的方法，也即：分别求出前$N$个数中取$i$（$0\le i\le N$）个能够形成的和，以及后$N$个数中取$i$（$0\le i\le N$）个能够形成的和，最后枚举前$N$个数中选取的个数，来求取最后的答案。在折半之后，最多需要考虑的情况只有${15\choose7} = 6435$种。

第一步是一个比较简单的动态规划，注意这里最好使用集合类型来存储中间结果，以免出现大量重复。

第二步中，假设从前$N$个数中选$i$个，则应当从后$N$个数中选$N-i$个。这时就变成了一个经典问题：从两个数组中各选择一个数，使得它们的和最接近某一个给定的数。我们对两个数组分别排序后使用双指针求解即可。

> 在具体实现中，我们使用了一个小trick，也即将原数组中所有数变为两倍。这样可以保证我们的目标值$sum/2$是一个整数。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        for (auto &num : nums)
            num *= 2;
        
        int n = nums.size() / 2;
        int sum = 0;
        for (int num : nums)
            sum += num;
        
        vector<unordered_set<int>> left(n + 1), right(n + 1);
        left[0].insert(0), right[0].insert(0);
        for (int i = 0; i < n; ++i) {
            for (int j = i; j >= 0; --j) {
                for (int val : left[j])
                    left[j + 1].insert(val + nums[i]);
            }
        }
        
        for (int i = n; i < n * 2; ++i) {
            for (int j = i - n; j >= 0; --j) {
                for (int val : right[j])
                    right[j + 1].insert(val + nums[i]);
            }
        }
        
        vector<vector<int>> ls(n + 1), rs(n + 1);
        for (int i = 0; i <= n; ++i) {
            ls[i] = vector<int>(left[i].begin(), left[i].end());
            rs[i] = vector<int>(right[i].begin(), right[i].end());
            sort(ls[i].begin(), ls[i].end());
            sort(rs[i].begin(), rs[i].end());
        }
        
        int target = sum / 2;
        int dist = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            int llen = ls[i].size(), rlen = rs[n - i].size();
            int pl = 0, pr = rlen - 1;
            while (pl < llen && pr >= 0) {
                int curr = ls[i][pl] + rs[n - i][pr];
                dist = min(dist, abs(curr - target));
                if (curr < target)
                    pl++;
                else
                    pr--;
            }
        }
        
        return dist;
    }
};
```

:::

<Utterances />
