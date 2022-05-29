# Leetcode 第239场周赛题解

## Problem A - [到目标元素的最小距离](https://leetcode.cn/problems/minimum-distance-to-the-target-element/)

模拟。

- 时间复杂度$\mathcal{O}(N)$。
- 参考代码的空间复杂度为$\mathcal{O}(N)$，实际只需要保存当前最优结果，所以最优的空间复杂度是$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def getMinDistance(self, nums: List[int], target: int, start: int) -> int:
        return min([abs(i - start) for i in range(len(nums)) if nums[i] == target])
```

:::

## Problem B - [将字符串拆分为递减的连续值](https://leetcode.cn/problems/splitting-a-string-into-descending-consecutive-values/)

回溯+剪枝。

- 时间复杂度$\mathcal{O}(|S|\cdot2^{|S|})$，但实际上会远远小于这一上界。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def dfs(self, s: str, start: int, last: int):
        if self.ans:
            return
        
        n = len(s)
        if start == n:
            self.ans = True
            return
        
        now = 0
        hi = n if start != 0 else n - 1
        for i in range(start, hi):
            now = now * 10 + ord(s[i]) - ord('0')
            if start == 0 or now == last - 1:
                self.dfs(s, i + 1, now)
            if start != 0 and now >= last:
                return
    
    def splitString(self, s: str) -> bool:
        if len(s) == 1:
            return False
        
        self.ans = False
        self.dfs(s, 0, 0)
        return self.ans
```

:::

## Problem C - [邻位交换的最小次数](https://leetcode.cn/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/)

### 方法一：模拟

1. 利用`next_permutation`求出目标排列。
2. 贪心进行交换。

- 时间复杂度$\mathcal{O}(|S|^2+|S|K)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int getMinSwaps(string num, int k) {
        string target(num);
        for (int i = 0; i < k; ++i)
            next_permutation(target.begin(), target.end());
        
        int ans = 0, n = num.size();
        for (int i = 0; i < n; ++i) {
            if (num[i] != target[i]) {
                int j = i + 1;
                while (num[j] != target[i])
                    j++;
                for (; j > i; --j)
                    swap(num[j], num[j - 1]), ans++;
            }
        }
        
        return ans;
    }
};
```

:::

### 方法二：平衡树

在求第$K$个之后的排列和最后的交换次数的过程中，均可以使用平衡树，从而将时间复杂度优化到$\mathcal{O}(|S|\log|S|)$，但过程会比较繁琐。

## Problem D - [包含每个查询的最小区间](https://leetcode.cn/problems/minimum-interval-to-include-each-query/)

和第51场双周赛的[最后一题](../BC51/)如出一辙，将区间和查询分别排序，然后离线处理。

- 时间复杂度$\mathcal{O}(N\log N+Q\log Q+Q\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = intervals.size(), q = queries.size();
        vector<int> ans(q);
        
        vector<int> order(q);
        for (int i = 0; i < q; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return queries[i] < queries[j]; 
        });
        
        sort(intervals.begin(), intervals.end());
        set<pair<int, int>> s;
        int ptr = -1;
        
        for (int i : order) {
            int qi = queries[i];
            while (ptr + 1 < n && intervals[ptr + 1][0] <= qi) {
                ptr++;
                s.emplace(intervals[ptr][1] - intervals[ptr][0] + 1, intervals[ptr][1]);
            }
                
            while (!s.empty() && s.begin()->second < qi)
                s.erase(s.begin());
            
            if (s.empty())
                ans[i] = -1;
            else
                ans[i] = s.begin()->first;
        }
        
        return ans;
    }
};
```

:::


<Utterances />
