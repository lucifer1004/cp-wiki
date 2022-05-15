# Leetcode 第78场双周赛题解

## Problem A - [找到一个数字的 K 美丽值](https://leetcode.cn/problems/find-the-k-beauty-of-a-number/)

### 方法一：计数

- 时间复杂度 $\mathcal{O}(K\log N)$。
- 空间复杂度 $\mathcal{O}(\log N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def divisorSubstrings(self, num: int, k: int) -> int:
        s = str(num)
        n = len(s)
        ans = 0
        for i in range(n - k + 1):
            sub = int(s[i:i+k])
            if sub > 0 and num % sub == 0:
                ans += 1
        return ans
```

:::

## Problem B - [分割数组的方案数](https://leetcode.cn/problems/number-of-ways-to-split-array/)

### 方法一：枚举

枚举每个位置。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def waysToSplitArray(self, nums: List[int]) -> int:
        s = sum(nums)
        ans = 0
        l = 0
        for i in range(len(nums) - 1):
            l += nums[i]
            if l >= s - l:
                ans += 1
        return ans
```

:::

## Problem C - [毯子覆盖的最多白色砖块数](https://leetcode.cn/problems/maximum-white-tiles-covered-by-a-carpet/)

### 方法一：滑动窗口

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N\log N)$。

::: details 参考代码（Python 3）

```python
from collections import deque

class Solution:
    def maximumWhiteTiles(self, tiles: List[List[int]], carpetLen: int) -> int:
        tiles.sort()
        dq = deque()
        ans = 0
        s = 0
        for l, r in tiles:
            dq.append((l, r))
            s += r - l + 1
            while len(dq) > 0:
                if r - dq[0][1] + 1 > carpetLen:
                    s -= dq[0][1] - dq[0][0] + 1
                    dq.popleft()
                elif r - dq[0][0] + 1 > carpetLen:
                    l0, r0 = dq.popleft()
                    l1 = r0 - (carpetLen - (r - r0 + 1))
                    s -= l1 - l0
                    dq.appendleft((l1, r0))
                else:
                    break
            ans = max(ans, s)
        return ans
```

:::

## Problem D - [最大波动的子字符串](https://leetcode.cn/problems/substring-with-largest-variance/)

### 方法一：枚举最大和最少字母

- 时间复杂度 $\mathcal{O}(|\Sigma|^2\cdot|S|)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int largestVariance(string s) {
        int ans = 0;
        for (char a = 'a'; a <= 'z'; ++a)
            for (char b = 'a'; b <= 'z'; ++b) {
                if (b == a) continue;
                int diff = 0, diff_with_b = INT_MIN;
                for (char c : s) {
                    if (c == a) {
                        diff++, diff_with_b++;
                    } else if (c == b) {
                        diff_with_b = --diff;
                        diff = max(diff, 0);
                    }
                    ans = max(ans, diff_with_b);
                }
            }
        return ans;
    }
};
```

:::

<Utterances />
