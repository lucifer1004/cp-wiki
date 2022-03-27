# Leetcode 第286场周赛题解

## Problem A - [找出两数组的不同](https://leetcode-cn.com/problems/find-the-difference-of-two-arrays/)

### 方法一：集合运算

将数组转为集合后进行集合运算即可。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findDifference(self, nums1: List[int], nums2: List[int]) -> List[List[int]]:
        s1 = set(nums1)
        s2 = set(nums2)
        return [list(s1 - s2), list(s2 - s1)]
```

:::

## Problem B - [美化数组的最少删除数](https://leetcode-cn.com/problems/minimum-deletions-to-make-array-beautiful/)

### 方法一：反向思考+贪心

反向思考：要求删去最少，等于要构造最多的不相等的数对。显然，只要有合适的数字，我们就应该贪心选取。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python）

```python
class Solution:
    def minDeletion(self, nums: List[int]) -> int:
        pairs = 0
        last = -1
        for num in nums:
            if last == -1:
                last = num
            elif last != num:
                pairs += 1
                last = -1
        return len(nums) - 2 * pairs
```

:::

## Problem C - [找到指定长度的回文数](https://leetcode-cn.com/problems/find-palindrome-with-fixed-length/)

### 方法一：数学

长度固定的回文数可以看成是由 10..00 到 99..99 这些数字依次生成的。这样就可以建立明确的对应关系，直接由位次得到半边的数值。

- 时间复杂度 $\mathcal{O}(NQ)$。
- 空间复杂度 $\mathcal{O}(NQ)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def kthPalindrome(self, queries: List[int], intLength: int) -> List[int]:
        l = (intLength + 1) // 2
        limit = 10 ** (l - 1) * 9
        start = 10 ** (l - 1)
        ans = []
        for q in queries:
            if q > limit:
                ans.append(-1)
            else:
                left = str(start + q - 1)
                right = left[::-1]
                if intLength % 2 == 0:
                    ans.append(int(left + right))
                else:
                    ans.append(int(left + right[1:]))
        return ans
```

:::

## Problem D - [从栈中取出 K 个硬币的最大面值和](https://leetcode-cn.com/problems/maximum-value-of-k-coins-from-piles/)

### 方法一：动态规划

标准的动态规划问题，没什么值得说的。

- 时间复杂度 $\mathcal{O}(\Sigma\cdot K)$，其中 $\Sigma$ 是所有栈的元素数目之和。
- 空间复杂度 $\mathcal{O}(K)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        vector<int> dp(k + 1);
        int s = 0;
        for (auto &p : piles) {
            for (int i = min(s, k - 1); i >= 0; --i) {
                int sum = 0;
                for (int j = 1; j <= p.size() && i + j <= k; ++j) {
                    sum += p[j - 1];
                    dp[i + j] = max(dp[i + j], dp[i] + sum);
                }
            }

            s += p.size();
        }
        
        return dp[k]; 
    }
};
```

:::

<Utterances />
