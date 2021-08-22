# Leetcode 第255场周赛题解

## Problem A - [找出数组的最大公约数](https://leetcode-cn.com/problems/find-greatest-common-divisor-of-array/)

### 方法一：模拟

按要求计算即可。

::: details 参考代码（Python 3）

```python
class Solution:
    def findGCD(self, nums: List[int]) -> int:
        return math.gcd(min(nums), max(nums))
```

:::

## Problem B - [找出不同的二进制字符串](https://leetcode-cn.com/problems/find-unique-binary-string/)

### 方法一：构造

选取第一位与第一个数的第一位不同，第二位与第二个数的第二位不同，第$N$位与第$N$个数的第$N$位不同，这样构造出来的数一定和原来的$N$个数都不同。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findDifferentBinaryString(self, nums: List[str]) -> str:
        return ''.join(str(1 - int(nums[i][i])) for i in range(len(nums)))
```

:::

## Problem C - [最小化目标值与所选元素的差](https://leetcode-cn.com/problems/minimize-the-difference-between-target-and-chosen-elements/)

### 方法一：动态规划

非常标准的动态规划问题，逐行计算即可。

- 时间复杂度$\mathcal{O}(N^2ML)$，其中$L=70$。
- 空间复杂度$\mathcal{O}(NL)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int n = mat.size(), m = mat[0].size();
        int lim = n * 70;
        vector<bool> can(lim + 1);
        can[0] = true;
        for (int i = 0; i < n; ++i) {
            vector<bool> ncan(lim + 1);
            for (int j = i * 1; j <= i * 70; ++j)
                if (can[j])
                    for (int k = 0; k < m; ++k)
                        ncan[j + mat[i][k]] = true;
            can = move(ncan);
        }
        int ans = INT_MAX;
        for (int i = 0; i <= lim; ++i)
            if (can[i])
                ans = min(ans, abs(i - target));
        return ans;
    }
};
```

:::

## Problem D - [从子集的和还原数组](https://leetcode-cn.com/problems/find-array-given-subset-sums/)

### 方法一：深度优先搜索

不妨对`sums`数组排序，则排序后的最大元素显然是原数组所有正数的和。接下来，我们考虑次大元素，它有两种可能的来源：

1. 所有正数加上一个最大的负数（也就是绝对值最小的负数）
2. 除去最小正数之外的所有正数

我们发现，无论如何，最大元素与次大元素的差都代表了原数组中绝对值最小那个数的绝对值。那么，我们就可以分别考虑这个数为正数，以及这个数为负数的两种情况，进行深度优先搜索。

两种情况是类似的。这里以正数为例进行说明。显然，`sums`数组中的元素可以分为两部分：不包含这一正数的，以及包含这一正数的。那么，我们就可以从最小数开始贪心地进行配对。如果最后能够将所有数都匹配成功，就代表我们找到了一种可能的分配，可以递归地求解剩余的数。但要注意，这里有可能找不到正确的解（意味着我们这一步选正数是错误的），因此我们需要对递归求得的结果进行检验，也即判断其长度是否正确。

- 时间复杂度$\mathcal{O}(N\cdot2^N)$。
- 空间复杂度$\mathcal{O}(2^N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def recoverArray(self, n: int, sums: List[int]) -> List[int]:
        if n == 1:
            if 0 not in sums:
                return []
            return [sum(sums)]
        
        sums.sort()
        cnt = collections.Counter(sums)
        keys = sorted(cnt.keys())
        x = sums[-1] - sums[-2]

        # Check x
        cnt2 = cnt.copy()
        valid = True
        rem = []
        for key in keys:
            if cnt2[key] > 0:
                if x == 0:
                    if cnt2[key] % 2 != 0:
                        valid = False
                        break
                    else:
                        rem += [key] * (cnt2[key] // 2)
                else:
                    if cnt2[key + x] < cnt2[key]:
                        valid = False
                        break
                    else:
                        cnt2[key + x] -= cnt2[key]
                        rem += [key] * cnt2[key]
        if valid:
            nxt = self.recoverArray(n - 1, rem)
            if len(nxt) == n - 1:
                return nxt + [x]
        
        # Check -x
        if x > 0:
            cnt2 = cnt.copy()
            valid = True
            rem = []
            for key in keys[::-1]:
                if cnt2[key] > 0:
                    if cnt2[key - x] < cnt2[key]:
                        valid = False
                        break
                    else:
                        cnt2[key - x] -= cnt2[key]
                        rem += [key] * cnt2[key]
        if valid:
            nxt = self.recoverArray(n - 1, rem)
            if len(nxt) == n - 1:
                return nxt + [-x]

        return []
```

:::

<Utterances />
