# Leetcode 第280场周赛题解

## Problem A - [得到 0 的操作数](https://leetcode-cn.com/problems/count-operations-to-obtain-zero/)

### 方法一：用辗转相除代替辗转相减

本题的操作实际上是辗转相减。我们可以用辗转相除代替辗转相减以优化时间复杂度。

- 时间复杂度 $\mathcal{O}(\log \max(N,M))$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countOperations(self, num1: int, num2: int) -> int:
        if num1 == 0 or num2 == 0:
            return 0
        elif num1 < num2:
            return self.countOperations(num2, num1)
        else:
            return self.countOperations(num2, num1 % num2) + num1 // num2
```

:::

## Problem B - [使数组变成交替数组的最少操作数](https://leetcode-cn.com/problems/minimum-operations-to-make-the-array-alternating/)

### 方法一：计数+贪心

理解题意：我们要让奇数位置都相同，偶数位置都相同，且这两个数字不能相同。

要想操作最少，我们应该尽可能利用已有的数字，因此我们对奇数和偶数位置分别计数。但这里直接采用最大频率的数字是不对的，因为二者的最大频率数字可能相同。因此我们枚举前二大频率进行搭配。

> 代码实现中为了简洁起见，对频率进行了排序；实际上寻找前二大频率可以在线性时间内完成。

- 时间复杂度 $\mathcal{O}(N\log N)$，如果将寻找前二大频率从排序改为线性寻找，则时间复杂度为 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
from collections import Counter

class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return 0
        
        ec = Counter(nums[::2])
        oc = Counter(nums[1::2])
        
        e = sorted([(ec[key], key) for key in ec], reverse=True)
        o = sorted([(oc[key], key) for key in oc], reverse=True)
        
        ans = n
        for i in range(min(2, len(e))):
            for j in range(min(2, len(o))):
                if e[i][1] != o[j][1]:
                    ans = min(ans, n - e[i][0] - o[j][0])
                else:
                    ans = min(ans, n - max(e[i][0], o[j][0]))
        
        return ans
```

:::

## Problem C - [拿出最少数目的魔法豆](https://leetcode-cn.com/problems/removing-minimum-number-of-magic-beans/)

### 方法一：排序

按照数目从小到大排序后，对于每个位置，我们可以选择将这个位置左边的袋子清空，并将右边的袋子中魔法豆的数目都减少到与当前位置相同。从这些位置中找出代价最小的一个即可。

- 时间复杂度 $\mathcal{O}(N \log N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumRemoval(self, beans: List[int]) -> int:
        beans.sort()
        s = sum(beans)
        n = len(beans)
        ans = s
        for i, b in enumerate(beans):
            ans = min(ans, s - b * (n - i))
        return ans
```

:::

## Problem D - [数组的最大与和](https://leetcode-cn.com/problems/maximum-and-sum-of-array/)

从题目的数据范围容易想到状态压缩。本题中需要对篮子和数字进行匹配，自然而然地，我们就有两种选择：枚举数字，或是枚举篮子。

### 方法一：状态压缩动态规划（三进制记录篮子状态，枚举数字）

如果选择枚举数字，我们需要用三进制记录篮子的状态。对于每个数字，我们尝试将其放入一个还未被装满的篮子。

- 时间复杂度$\mathcal{O}(NS\cdot3^S)$
- 空间复杂度$\mathcal{O}(3^S)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int s) {
        int n = nums.size();
        vector<int> t(s + 1);
        t[0] = 1;
        for (int i = 1; i <= s; ++i)
            t[i] = t[i - 1] * 3;
        
        vector<int> dp(t[s], -1);
        dp[0] = 0;
        
        for (int num : nums) {
            for (int i = t[s] - 1; i >= 0; --i) {
                if (dp[i] == -1)
                    continue;
                
                int x = i;
                for (int j = 0; j < s; ++j) {
                    if (x % 3 < 2)
                        dp[i + t[j]] = max(dp[i + t[j]], dp[i] + (num & (j + 1)));
                    x /= 3;
                }
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};
```

:::

### 方法二：状态压缩动态规划（二进制记录数字状态，枚举篮子）

如果选择枚举篮子，我们需要用二进制记录篮子的状态。对于每个篮子，我们尝试向其中放入一个或两个目前还未被使用的数字。

- 时间复杂度$\mathcal{O}(N^2S\cdot2^N)$
- 空间复杂度$\mathcal{O}(2^N)$

根据本题中的数据范围可知方法二的复杂度是大于方法一的。因此下面不带剪枝处理的 C++ 实现是无法在时限内通过测试的。

::: details 参考代码（C++，无剪枝，超时）

```cpp
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        int n = nums.size();
        int ans = 0;
        
        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for (int s = 1; s <= numSlots; ++s) {
            for (int i = (1 << n) - 1; i >= 0; --i) {
                if (dp[i] == -1)
                    continue;
                for (int j = 0; j < n; ++j) {
                    if (i & (1 << j))
                        continue;
                    int msk = i ^ (1 << j);
                    dp[msk] = max(dp[msk], dp[i] + (nums[j] & s));
                    for (int k = j + 1; k < n; ++k) {
                        if (i & (1 << k))
                            continue;
                        dp[msk ^ (1 << k)] = max(dp[msk ^ (1 << k)], dp[i] + (nums[j] & s) + (nums[k] & s));
                    }
                }
            }
        }
        
        return dp.back();
    }
};
```

:::

::: details 参考代码（Rust，无剪枝，通过）

```rust
impl Solution {
    pub fn maximum_and_sum(nums: Vec<i32>, num_slots: i32) -> i32 {
        let n = nums.len();
        let mut ans = 0;
        let mut dp = vec![-1; 1 << n];
        dp[0] = 0;
        for s in 1..=num_slots {
            for i in (0..(1<<n)).rev() {
                if dp[i] == -1 {
                    continue;
                }

                for j in 0..n {
                    if (i & (1 << j)) != 0 {
                        continue;
                    }
                    
                    let msk = i ^ (1 << j);
                    dp[msk] = dp[msk].max(dp[i] + (nums[j] & s));
                    
                    for k in j+1..n {
                        if (i & (1 << k)) != 0 {
                            continue;
                        }
                        dp[msk ^ (1 << k)] = dp[msk ^ (1 << k)].max(dp[i] + (nums[j] & s) + (nums[k] & s));
                    }
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
}
```

:::

需要的优化并不多，只要加上状态合法性判断（如果剩下的篮子不够装剩下的数，就不再继续）就足以通过：

::: details 参考代码（C++，剪枝，通过）

```cpp
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        int n = nums.size();
        int ans = 0;
        
        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for (int s = 1; s <= numSlots; ++s) {
            for (int i = (1 << n) - 1; i >= 0; --i) {
                if (dp[i] == -1 || (__builtin_popcount(i) + (numSlots - s + 1) * 2 < n))
                    continue;
                for (int j = 0; j < n; ++j) {
                    if (i & (1 << j))
                        continue;
                    int msk = i ^ (1 << j);
                    dp[msk] = max(dp[msk], dp[i] + (nums[j] & s));
                    for (int k = j + 1; k < n; ++k) {
                        if (i & (1 << k))
                            continue;
                        dp[msk ^ (1 << k)] = max(dp[msk ^ (1 << k)], dp[i] + (nums[j] & s) + (nums[k] & s));
                    }
                }
            }
        }
        
        return dp.back();
    }
};
```

:::

::: details 参考代码（Rust，剪枝，通过）

```rust
impl Solution {
    pub fn maximum_and_sum(nums: Vec<i32>, num_slots: i32) -> i32 {
        let n = nums.len();
        let mut ans = 0;
        let mut dp = vec![-1; 1 << n];
        dp[0] = 0;
        for s in 1..=num_slots {
            for i in (0..(1<<n)).rev() {
                if dp[i] == -1 || (i.count_ones() as i32 + (num_slots - s + 1) * 2 < n as i32) {
                    continue;
                }
                
                for j in 0..n {
                    if (i & (1 << j)) != 0 {
                        continue;
                    }
                    
                    let msk = i ^ (1 << j);
                    dp[msk] = dp[msk].max(dp[i] + (nums[j] & s));
                    
                    for k in j+1..n {
                        if (i & (1 << k)) != 0 {
                            continue;
                        }
                        dp[msk ^ (1 << k)] = dp[msk ^ (1 << k)].max(dp[i] + (nums[j] & s) + (nums[k] & s));
                    }
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
}
```

:::

### 方法三：最大费用最大流

解决本题的最优方法还是网络流：我们可以将数字和篮子都抽象成节点。从源点向每个数字连一条流量为 1 的无费用的边，从每个数字向每个篮子连一条流量为 1 的费用等于二者与的边，从每个篮子向汇点连一条流量为 2 的无费用的边，在上面跑最大费用最大流即可。

<Utterances />
