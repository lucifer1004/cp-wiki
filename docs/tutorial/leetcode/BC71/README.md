# Leetcode 第71场双周赛题解

## Problem A - [拆分数位后四位数字的最小和](https://leetcode-cn.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/)

### 方法一：贪心

最小的两个数字排在十位，较大的两个数字排在个位。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumSum(self, num: int) -> int:
        d = sorted(list(map(int, str(num))))
        return (d[0] + d[1]) * 10 + d[2] + d[3]
```

:::

## Problem B - [根据给定数字划分数组](https://leetcode-cn.com/problems/partition-array-according-to-given-pivot/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def pivotArray(self, nums: List[int], pivot: int) -> List[int]:
        small = [num for num in nums if num < pivot]
        large = [num for num in nums if num > pivot]
        return small + [pivot] * (len(nums) - len(small) - len(large)) + large
```

:::

## Problem C - [设置时间的最少代价](https://leetcode-cn.com/problems/minimum-cost-to-set-cooking-time/)

### 方法一：暴力

因为输入 `0` 是没有意义的，所以暴力枚举所有范围内的正整数即可。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {
        int ans = INT_MAX;
        for (int i = 1; i <= 9999; ++i) {
            int result = i / 100 * 60 + i % 100;
            if (result != targetSeconds)
                continue;
            
            string s = to_string(i);
            int cost = 0;
            char curr = startAt + '0';
            for (char ch : s) {
                if (curr == ch)
                    cost += pushCost;
                else {
                    curr = ch;
                    cost += moveCost + pushCost;
                }
            }
            ans = min(ans, cost);
        }
        return ans;
    }
};
```

:::

## Problem D - [删除元素后和的最小差值](https://leetcode-cn.com/problems/minimum-difference-in-sums-after-removal-of-elements/)

### 方法一：堆

转变思路，考虑从前面和后面各选取 $N$ 个数。显然，前面需要选最小的，后面需要选最大的。为了避免动态调整带来的思维难度，我们预处理得到左右的结果，最后枚举分界点得到答案。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    ll minimumDifference(vector<int>& nums) {
        int n = nums.size() / 3;
        ll ans = LLONG_MAX;
        
        vector<ll> L(3 * n), R(3 * n);
        ll lsum = 0;
        
        priority_queue<int> pq;
        for (int i = 0; i < 2 * n; ++i) {
            pq.push(nums[i]);
            lsum += nums[i];
            
            if (pq.size() > n) {
                lsum -= pq.top();
                pq.pop();
            }
            
            L[i] = lsum;
        }
        
        ll rsum = 0;
        priority_queue<int, vector<int>, greater<>> pq2;
        for (int i = n * 3 - 1; i >= n; --i) {
            pq2.push(nums[i]);
            rsum += nums[i];
            
            if (pq2.size() > n) {
                rsum -= pq2.top();
                pq2.pop();
            }
            
            R[i] = rsum; 
        }

        for (int i = n - 1; i < 2 * n; ++i)
            ans = min(ans, L[i] - R[i + 1]);
        
        return ans;
    }
};
```

:::

<Utterances />
