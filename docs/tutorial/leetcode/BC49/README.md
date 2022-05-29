# Leetcode 第49场双周赛题解

## Problem A - [判断国际象棋棋盘中一个格子的颜色](https://leetcode.cn/problems/determine-color-of-a-chessboard-square/)

### 方法一：模拟

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def squareIsWhite(self, coordinates: str) -> bool:
        col = ord(coordinates[0]) - ord('a')
        row = int(coordinates[1]) - 1
        return (col - row) % 2 == 1
```

:::

## Problem B - [句子相似性 III](https://leetcode.cn/problems/sentence-similarity-iii/)

### 方法一：贪心

先尽可能从左向右匹配，再尽可能从右向左匹配即可。

- 时间复杂度为$\mathcal{O}(|S_1|+|S_2|)$。
- 空间复杂度$\mathcal{O}(|S_1|+|S_2|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def areSentencesSimilar(self, sentence1: str, sentence2: str) -> bool:
        w1 = sentence1.split()
        w2 = sentence2.split()
        len1 = len(w1)
        len2 = len(w2)
        l = 0
        while l < min(len1, len2) and w1[l] == w2[l]:
            l += 1
        if l == min(len1, len2):
            return True
        r = 0
        while l + r < min(len1, len2) and w1[len1-1-r] == w2[len2-1-r]:
            r += 1
        return l + r == min(len1, len2)
```

:::

## Problem C - [统计一个数组中好对子的数目](https://leetcode.cn/problems/count-nice-pairs-in-an-array/)

简单的移项得到`nums[i]-rev(nums[i])=nums[j]-rev(nums[j])`，所以按照`nums[i]-rev(nums[i])`对原数组进行计数后，每一组内元素相互匹配即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
def rev(x):
    return int(str(x)[::-1])

class Solution:
    def countNicePairs(self, nums: List[int]) -> int:
        cnt = collections.Counter()
        for num in nums:
            cnt[num - rev(num)] += 1
        ans = 0
        for key in cnt:
            ans += cnt[key] * (cnt[key] - 1) // 2
        return ans % 1000000007
```

:::

## Problem D - [得到新鲜甜甜圈的最多组数](https://leetcode.cn/problems/maximum-number-of-groups-getting-fresh-donuts/)

### 方法一：动态规划

容易看出，每一组的人数可以替换为其模`batchSize`的余数。之后，原问题就变为将这些余数分成尽可能多的和能被`batchSize`整除的组的新问题。

解决这一问题的关键是状态的表示。可以考虑的方式有：

- 数组或元组
- `bitset`或长整数
- 混合进制

为了减少状态，各个余数取值的剩余数量不应超过其初始值。也即，合并得到的新值不需要加入到状态中。这是因为，如果合并后可以被`batchSize`整除，显然不会在状态中加入新值；而如果合并后得到的值仍不能被`batchSize`整除，这个数值实际上可以借助当前状态与初始状态的差值来确定出来，也不需要通过在状态中加入新值来进行表示。

::: details 参考代码（C++）

这里给出[@newhar](https://leetcode.cn/problems/maximum-number-of-groups-getting-fresh-donuts/solution/cong-zui-zhi-jie-de-fang-fa-kai-shi-yi-b-x729/)的代码。代码中采用了混合进制的方式表示状态。

```cpp
int freq0[9], freq[9], w[9], f[300000];
class Solution {
public:
    int maxHappyGroups(int b, vector<int>& groups) {
        for(int i = 0; i < b; ++i) freq0[i] = 0;
        for(int i : groups) freq0[i % b]++;
        int msum = 1;
        for(int i = 1; i < b; ++i) msum *= (freq0[i] + 1);
        w[1] = 1;
        for(int i = 2; i < b; ++i) w[i] = w[i-1] * (freq0[i-1] + 1);
        for(int fmask = 0; fmask < msum; ++fmask) f[fmask] = 0;
        for(int fmask = 1; fmask < msum; ++fmask) {
            int last = 0;
            for(int i = 1; i < b; ++i) {
                freq[i] = (fmask / w[i]) % (freq0[i] + 1);
                last = (last + (freq0[i] - freq[i]) * i) % b;
            }
            for(int c = 1; c < b; ++c) {
                if(freq[c]) f[fmask] = max(f[fmask], f[fmask - w[c]] + (last == 0));
            }
        }
        return f[msum-1] + freq0[0];
    }
};
```

:::

<Utterances />
