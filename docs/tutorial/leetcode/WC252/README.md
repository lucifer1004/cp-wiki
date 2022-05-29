# Leetcode 第252场周赛题解

## Problem A - [三除数](https://leetcode.cn/problems/three-divisors/)

### 方法一：穷举

按照通常的做法穷举因子即可。可以加入提前终止的优化。

- 时间复杂度$\mathcal{O}(\sqrt{N})$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool isThree(int n) {
        int ans = 0;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                ans++;
                if (i != n / i)
                    ans++;
                if (ans > 3)
                    return false;
            }
        }
        return ans == 3;
    }
};
```

:::

## Problem B - [你可以工作的最大周数](https://leetcode.cn/problems/maximum-number-of-weeks-for-which-you-can-work/)

### 方法一：贪心

容易发现：如果阶段任务最多的那个项目可以完成，那么其他项目必定可以全部完成。否则的话，我们需要以其他项目作为分隔来隔开任务最多的那个项目，在其他项目有$rem$个任务的情况下，这样最多可以安排$2rem + 1$个任务。

二者取较小的那个即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def numberOfWeeks(self, milestones: List[int]) -> int:
        hi = max(milestones)
        s = sum(milestones)
        rem = s - hi
        return min(s, rem * 2 + 1)
```

:::

### 思考

如果做了一个项目之后，需要再做$k$个其他项目才能再做这个项目，应该如何做？如果每个项目的$k_i$不同呢？

## Problem C - [收集足够苹果的最小花园周长](https://leetcode.cn/problems/minimum-garden-perimeter-to-collect-enough-apples/)

### 方法一：二分+数学

经过推导，可以得出，正方形的右上角为$(n,n)$时：

- 最外面一圈，从任意一个顶点开始，到下一个顶点之前的苹果数为$2n,2n-1,\dots,n,n+1,\dots,2n-1$，总数为$2\cdot\frac{(n+2n-1)n}{2}+n=3n^2$，因此这一圈的苹果数为$12n^2$
- 从第一圈到第$n$圈包含的苹果总数为$12\sum i^2=2n(n+1)(2n+1)$，而对应的周长为$8n$。

因此二分答案即可。

- 时间复杂度$\mathcal{O}(\log C)$，其中$C=10^5$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumPerimeter(self, neededApples: int) -> int:
        lo = 1
        hi = int(1e5)
        while lo <= hi:
            mid = (lo + hi) >> 1
            total = 2 * mid * (mid + 1) * (2 * mid + 1)
            if total >= neededApples:
                hi = mid - 1
            else:
                lo = mid + 1
        return 8 * lo
```

:::

### 思考

如果只要求包含原点，并且不限定为正方形，应该如何做？

## Problem D - [统计特殊子序列的数目](https://leetcode.cn/problems/count-number-of-special-subsequences/)

### 方法一：动态规划

因为只要下标集合不同就是不同的子序列，所以我们不存在重复的子序列。因此，我们只要记录当前的$0$串数目、$01$串数目和$012$串数目即可。

因为我们可以从$0$串得到$0$串和$01$串，从$01$串得到$01$串和$012$串，从$012$串得到$012$串，所以转移是很清晰的：

- 如果当前位是$0$，则可以增加$zero+1$个$0$串；
- 如果当前位是$1$，则可以增加$zero+one$个$01$串；
- 如果当前位是$2$，则可以增加$one+two$个$012$串。

最后注意取模。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int countSpecialSubsequences(vector<int>& nums) {
        ll zero = 0, one = 0, two = 0;
        for (int num : nums) {
            if (num == 0) {
                zero += 1 + zero;
                zero %= MOD;
            } else if (num == 1) {
                one += zero + one;
                one %= MOD;
            } else {
                two += one + two;
                two %= MOD;
            }
        }
        return two;
    }
};
```

:::

### 思考

如果下标集合不同，但包含的数值完全相同的两个子序列认为是重复的，应该如何做？

<Utterances />
