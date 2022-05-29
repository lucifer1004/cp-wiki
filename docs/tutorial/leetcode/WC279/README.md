# Leetcode 第279场周赛题解

## Problem A - [对奇偶下标分别排序](https://leetcode.cn/problems/sort-even-and-odd-indices-independently/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def sortEvenOdd(self, nums: List[int]) -> List[int]:
        n = len(nums)
        even = sorted([nums[i] for i in range(0, n, 2)])
        odd = sorted([nums[i] for i in range(1, n, 2)], reverse=True)
        return [even[i // 2] if i % 2 == 0 else odd[i // 2] for i in range(n)]
```

:::

## Problem B - [重排数字的最小值](https://leetcode.cn/problems/smallest-value-of-the-rearranged-number/)

### 方法一：贪心

- 零永远是零。
- 对于负数，将所有数字从大到小排列可以得到最小值。
- 对于正数，我们本应该将所有数字从小到大排列，但因为限制不允许有先导零，所以还要在排序后，将从左到右的第一个非零值移到最前面。

- 时间复杂度 $\mathcal{O}(\log N\log\log N)$。
- 空间复杂度 $\mathcal{O}(\log N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def smallestNumber(self, num: int) -> int:
        if num == 0:
            return 0
        
        digits = list(str(abs(num)))
        
        if num < 0:
            digits.sort(reverse=True)
            return -int(''.join(digits))
        else:
            digits.sort()
            it = 0
            while digits[it] == '0':
                it += 1
            digits = digits[it:it+1] + digits[:it] + digits[it+1:]
            return int(''.join(digits))
```

:::

## Problem C - [设计位集](https://leetcode.cn/problems/design-bitset/)

### 方法一：记录翻转状态而非实际进行翻转

本题可能的瓶颈在于 `flip()` 操作。如果对内部数组进行整体的翻转，则这一步操作的时间复杂度会变为 $\mathcal{O}(N)$，而题目并没有像限制 `toString()` 的次数那样去限制 `flip()` 的次数。

一个可行的办法是记录翻转状态，而非实际进行翻转。我们采用一个布尔值 `flipped` 来记录当前是否处于翻转状态。此时，判断某一位是否被设置，应采用 `v[i] ^ flipped`，而不是直接使用 `v[i]`。

- 初始化和 `toString()` 时间复杂度 $\mathcal{O}(N)$，其余操作时间复杂度 $\mathcal{O}(1)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Bitset {
    int n;
    int sum;
    bool flipped;
    vector<bool> v;
    
public:
    Bitset(int size) {
        n = size;
        sum = 0;
        flipped = false;
        v = vector<bool>(n);
    }
    
    void fix(int idx) {
        if (!(v[idx] ^ flipped))
            v[idx] = !v[idx], sum++;
    }
    
    void unfix(int idx) {
        if (v[idx] ^ flipped)
            v[idx] = !v[idx], sum--;
    }
    
    void flip() {
        flipped = !flipped;
        sum = n - sum;
    }
    
    bool all() {
        return sum == n;
    }
    
    bool one() {
        return sum > 0;
    }
    
    int count() {
        return sum;
    }
    
    string toString() {
        string ans;
        for (int i = 0; i < n; ++i)
            if (v[i] ^ flipped)
                ans.push_back('1');
            else
                ans.push_back('0');
        return ans;
    }
};
```

:::

## Problem D - [移除所有载有违禁货物车厢所需的最少时间](https://leetcode.cn/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/)

### 方法一：动态规划

因为像在 `011110` 这样的例子中，最优方案需要移除为 `0` 的车厢，因此直接贪心地移除首尾的 `1`，之后用操作三移除中间的 `0` 是错误的。

因为题目可以从最左边或最右边进行移除，我们不妨也分左右两边分别考虑。

考虑左边的情况。令 $l[i]$ 表示通过若干操作使得左边前 $i$ 个车厢都不违禁的最少时间，则：

- 若当前车厢不违禁（为 `0`），有 $l[i] = l[i - 1]$，即不需要额外操作。
- 若当前车厢违禁（为 `1`），此时有两种可能：
    - 在 $l[i - 1]$ 的基础上进行移除。因为 $l[i - 1]$ 并不保证之前的车厢已经全部移除，我们只能通过操作三来移除当前车厢，所需要的总时间为 $l[i-1] + 2$。
    - 之前的车厢已经全部移除。在进一步移除当前车厢后，所需要的总时间为 $i$，因为一共移除了 $i$ 节车厢。
    从而，$l[i] = \min(l[i-1] + 2, i)$。
    
同理可以求得右边的 $r[i]$。

最后的结果就是 $\min_{i=0}^N (l[i]+r[N-i])$。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumTime(string s) {
        int n = s.size();
        int ans = 2 * n;
        
        vector<int> l(n + 1), r(n + 1);
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == '0')
                l[i] = l[i - 1];
            else
                l[i] = min(l[i - 1] + 2, i);
        }
        
        for (int i = 1; i <= n; ++i) {
            if (s[n - i] == '0')
                r[i] = r[i - 1];
            else
                r[i] = min(r[i - 1] + 2, i);
        }
        
        for (int i = 0; i <= n; ++i)
            ans = min(ans, l[i] + r[n - i]);
        
        return ans;
    }
};
```

:::

<Utterances />
