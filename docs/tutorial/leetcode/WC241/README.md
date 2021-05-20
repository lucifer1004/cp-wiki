# Leetcode 第241场周赛题解

## Problem A - [找出所有子集的异或总和再求和](https://leetcode-cn.com/problems/sum-of-all-subset-xor-totals/)

### 方法一：暴力

本题数据范围很小，可以暴力枚举子集求解。

- 时间复杂度$\mathcal{O}(N\cdot2^N)$。
- 空间复杂度$\mathcal{O}(2^N)$。

::: details 参考代码（C++）

```c++
class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        for (int i = 0; i < (1 << n); ++i) {
            int s = 0;
            for (int j = 0; j < n; ++j)
                if (i & (1 << j))
                    s ^= nums[j];
            ans += s;
        }
        return ans;
    }
};
```

:::

### 方法二：组合+优化

利用位运算的性质，按照二进制位逐位进行考虑。

如果某一位为$1$的数有$k$个，则这一位为`1`的组合一共有$\sum_{i=1}^N {k\choose {2*i-1}}\cdot2^{N-k}$个。

这里，利用组合数的性质可知，$k\geq1$时，$\sum_{i=1}^N {k\choose {2*i-1}}=2^{k-1}$，因此只要数组中存在某一位为$1$的数，这一位为$1$的子集的个数就为$2^{N-1}$个。

累加即可得到答案。

- 时间复杂度$\mathcal{O}(K\log N)$，其中$K$为最高的二进制位数。
- 空间复杂度为$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
K = 5

class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        ans = 0
        n = len(nums)
        for i in range(K):
            s = False
            for num in nums:
                if num & (1 << i) > 0:
                    s = True
                    break
            if s:
                ans += 1 << (i + n - 1)
        return ans
```

:::

进一步地，我们可以利用位运算快速求出对于任意一位，数组中是否有该位为1的元素，从而将时间复杂度优化到$\mathcal{O}(N+K)$。

::: details 参考代码（Python 3）

```python
K = 5

class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        n = len(nums)
        or_sum = reduce(operator.__or__, nums, 0)
        return sum([0] + [1 << (i + n - 1) for i in range(K) if or_sum & (1 << i) > 0])
```

:::

## Problem B - [构成交替字符串需要的最小交换次数](https://leetcode-cn.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/)

### 方法一：模拟

注意交换并不限于相邻元素。这里可能构成的交替字符串一共只有两种，在`0`、`1`个数满足要求的情况下，所需的最小交换次数即为目标字符串为`1`而原字符串为`1`的位置数。分别讨论即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minSwaps(self, s: str) -> int:
        n = len(s)
        o = 0
        for c in s:
            if c == '1':
                o += 1
        ans = -1
        if o == n // 2:
            u = 0
            for i in range(1, n, 2):
                if s[i] == '0':
                    u += 1
            ans = u
        if (o == n // 2 and n % 2 == 0) or (o == n // 2 + 1 and n % 2 == 1):
            u = 0
            for i in range(0, n, 2):
                if s[i] == '0':
                    u += 1
            if ans == -1 or ans > u:
                ans = u
        return ans
```

:::

## Problem C - [找出和为指定值的下标对](https://leetcode-cn.com/problems/finding-pairs-with-a-certain-sum/)

### 方法一：哈希表+暴力

利用两个哈希表以计数的方式分别存储两个数组，对于`count`操作暴力枚举即可。

- 初始化时间复杂度$\mathcal{O}(N+M)$，`add`操作时间复杂度为$\mathcal{O}(1)$，`count`操作时间复杂度为$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N+M)$。

::: details 参考代码（C++）

```cpp
class FindSumPairs {
    vector<int> a, b;
    unordered_map<int, int> ca, cb;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        a = nums1, b = nums2;
        for (int i : nums1)
            ca[i]++;
        for (int i : nums2)
            cb[i]++;
    }
    
    void add(int index, int val) {
        cb[b[index]]--;
        if (cb[b[index]] == 0)
            cb.erase(b[index]);
        cb[b[index] + val]++;
        b[index] += val;
    }
    
    int count(int tot) {
        int ans = 0;
        for (auto [i, f] : ca)
            if (cb.count(tot - i))
                ans += f * cb[tot - i];
        return ans;
    }
};
```

:::

## Problem D - [恰有 K 根木棍可以看到的排列数目](https://leetcode-cn.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/)

### 方法一：第一类Stirling数

对于一个有$K$根木棍能被看到的排列，显然这$K$根木棍的长度是从左到右递增的。我们将每根能被看见的木棍之后，下一根能被看见的木棍之前的所有木棍与这一根木棍分为一组，一共可以得到$K$组。因此，每一个符合要求的排列，都对应于唯一的一个$N$个数分为$K$组的圆排列。

另一方面，对于每一个$N$个数分为$K$组的圆排列，我们将这$K$组按其最大元素升序排列，然后每组内旋转到最大元素居首的位置，这样就得到了唯一确定的一个符合要求的排列。

因此，本题的答案与$N$个数分为$K$组的圆排列一一对应，也即为（无符号）第一类Stirling数。

利用Stirling数的递推公式求解即可：

$$
s_u(n+1,m)=s_u(n,m-1)+n\cdot s_u(n,m)
$$

- 预处理时间复杂度$\mathcal{O}(MAXN^2)$，之后每次调用的时间复杂度为$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(MAXN^2)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;
const int N = 1005;

bool inited = false;
ll stir[N][N];
void init(){
    stir[0][0] = 1;

    for(int i=1; i<N; i++) {
        stir[i][0] = 0;
        stir[i][i] = 1;
        for(int j = 1; j < i; j++)
            stir[i][j] = (stir[i - 1][j - 1] + stir[i - 1][j] * (i - 1)) % MOD;
    }
}

class Solution {
public:
    int rearrangeSticks(int n, int k) {
        if (!inited) {
            init();
            inited = true;
        }
        
        return stir[n][k];
    }
};
```

:::

### 思考

如果题目改为，从左边能看到$k$个，从右边能看到$b$个，应该如何求解呢？

::: details 提示

修改后的题目即为HDU4372。

:::


<Utterances />
