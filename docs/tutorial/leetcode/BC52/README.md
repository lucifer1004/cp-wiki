# Leetcode 第52场双周赛题解

## Problem A - [将句子排序](https://leetcode.cn/problems/sorting-the-sentence/)

### 方法一：模拟

- 时间复杂度$\mathcal{O}(|S|+N\log N)$。
- 空间复杂度$\mathcal{O}(|S|+N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def sortSentence(self, s: str) -> str:
        words = list(map(lambda x: (int(x[-1]), x[:-1]), s.split()))
        words.sort()
        return ' '.join(map(lambda x: x[1], words))
```

:::

## Problem B - [增长的内存泄露](https://leetcode.cn/problems/incremental-memory-leak/)

### 方法一：模拟

- 时间复杂度为$\mathcal{O}(\sqrt{N+M})$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def memLeak(self, memory1: int, memory2: int) -> List[int]:
        i = 1
        while memory1 >= i or memory2 >= i:
            if memory1 >= memory2:
                memory1 -= i
            else:
                memory2 -= i
            i += 1
        return [i, memory1, memory2]
```

:::

## Problem C - [旋转盒子](https://leetcode.cn/problems/rotating-the-box/)

### 方法一：模拟

从右向左处理每一行（等价于从下向上处理每一列，需要注意旋转前后行和列的对应关系）。为了优化速度，在遇到石头的时候可以先不处理，而是计数。在遇到下一个障碍的时候，再一次性将之前累积的石头安排到上一个障碍的上方。

- 时间复杂度$\mathcal{O}(RC)$。
- 空间复杂度$\mathcal{O}(RC)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int n = box.size(), m = box[0].size();
        vector<vector<char>> ans(m, vector<char>(n, '.'));
        for (int i = 0; i < n; ++i) {
            int bottom = m, stones = 0;
            for (int j = m - 1; j >= 0; --j) {
                if (box[i][j] == '*') {
                    while (stones) {
                        bottom--, stones--;
                        ans[bottom][n - 1 - i] = '#';
                    }
                    bottom = j;
                    ans[bottom][n - 1 - i] = '*';
                } else if (box[i][j] == '#') {
                    stones++;
                }
            }
            while (stones) {
                bottom--, stones--;
                ans[bottom][n - 1 - i] = '#';
            }
        }
        
        return ans;
    }
};
```

:::

## Problem D - [向下取整数对和](https://leetcode.cn/problems/sum-of-floored-pairs/)

### 方法一：计数+前缀和+调和级数思想

我们在原数组的计数数组上进行处理。

对于$[1,\max{nums}]$中每一个在$nums$中出现了的数，我们从小到大枚举其各个倍数，利用预计算的前缀和快速计算出除以这个数并向下取整后的结果为$k$的数的个数，从而累积答案。

- 时间复杂度$\mathcal{O}(H\log H+N)$，其中$H=\max{nums}$。
- 空间复杂度$\mathcal{O}(H)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        int n = nums.size();
        int hi = *max_element(nums.begin(), nums.end());
        ll ans = 0;
        
        vector<int> cnt(hi + 1);
        vector<int> a(hi + 1);
        for (int num : nums)
            cnt[num]++;
        for (int i = 1; i <= hi; ++i)
            a[i] = a[i - 1] + cnt[i];
        
        
        for (int i = 1; i <= hi; ++i) {
            if (cnt[i]) {
                int j = i * 2 - 1;
                for (; j < hi; j += i) {
                    ans += 1LL * cnt[i] * (j / i) * (a[j] - a[j - i]);
                }
                ans += 1LL * cnt[i] * (hi / i) * (a[hi] - a[hi / i * i - 1]);
            }
        }
        
        
        return ans % MOD;
    }
};
```

:::

<Utterances />
