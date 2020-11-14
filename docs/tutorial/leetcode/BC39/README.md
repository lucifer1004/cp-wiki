# Leetcode 第39场双周赛题解

## Problem A - [拆炸弹](https://leetcode-cn.com/problems/defuse-the-bomb/)

数据范围有限，可以直接暴力模拟。如果数据范围扩大，可以预先计算前缀和。

时间复杂度$O(NK)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def decrypt(self, code: List[int], k: int) -> List[int]:
        n = len(code)
        ans = [0] * n
        for i in range(n):
            if k > 0:
                for j in range(1, k + 1):
                    ans[i] += code[(i + j) % n]
            else:
                for j in range(1, -k + 1):
                    ans[i] += code[(i - j + n) % n]
        return ans
```

:::

## Problem B - [使字符串平衡的最少删除次数](https://leetcode-cn.com/problems/minimum-deletions-to-make-string-balanced/)

枚举`a`和`b`的分割点。

时间复杂度$O(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumDeletions(self, s: str) -> int:
        a = s.count('a')
        ans = a
        b = 0
        for c in s:
            if c == 'b':
                b += 1
            else:
                a -= 1
            ans = min(ans, a + b)
        return ans
```

:::

## Problem C - [到家的最少跳跃次数](https://leetcode-cn.com/problems/minimum-jumps-to-reach-home/)

BFS即可，注意除了要记录当前的位置，还需要记录上一步是从左边过来的，还是从右边过来的。

时间复杂度$O(MAX)$，$MAX$为可能的最远位置。~~比赛时因为最远位置没有考虑清楚，吃了3发WA😶。~~

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;
const int HI = 4005;

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        vector<bool> can(HI + b, true);
        for (int i : forbidden)
            can[i] = false;
        queue<pair<int, bool>> q;
        q.emplace(0, false);
        vector<int> f(HI + b, INF), g(HI + b, INF);
        f[0] = 0;
        while (!q.empty()) {
            auto [pos, from_right] = q.front();
            q.pop();
            int curr = from_right ? g[pos] : f[pos];
            if (pos == x)
                return curr;
            if (!from_right && pos >= b && can[pos - b]) {
                if (g[pos - b] > curr + 1) {
                    g[pos - b] = curr + 1;
                    q.emplace(pos - b, true);
                }
            }
            if (pos + a < HI + b && can[pos + a]) {
                if (f[pos + a] > curr + 1) {
                    f[pos + a] = curr + 1;
                    q.emplace(pos + a, false);
                }
            }
        }
        return -1;
    }
};
```

:::

## Problem D - [分配重复整数](https://leetcode-cn.com/problems/distribute-repeating-integers/)

看到$M\leq10$，立即应该想到状态压缩。

首先，我们要用$O(N)$时间统计每一个不同数字的频率，因为在后面的过程中，只有这个频率值才有意义。假设统计得到$F$个频率，我们可以用$O(F\log F)$时间对频率值进行降序排序，这样在后面的DP过程中，会优先使用较大的频率，这样能够更早找到符合条件的解（假设每一步都选当前最大的数字都不行，那么换成别的更小的数字，显然也不行）。

在开始状态压缩DP之前，我们可以用$O(M\cdot2^M)$的时间预处理得到每一种人的子集对应需要的数字总个数，这样就不需要每次重复计算了。

DP的思路很简单，最开始所有人都没有分配数字，自然是处于$0$状态。每次我们枚举当前已经到达的状态，然后枚举将当前数字分配给哪几个人。当然，我们不会给已经分配了数字的人重新分配。这个过程中，我们可以使用枚举子集的优化方法，这样可以把DP的总时间复杂度降低到$O(F\cdot3^M)$。如果在某一步，已经可以实现给所有人分配数字，则不必再继续，可以提前返回结果。

- 时间复杂度$O(M\cdot2^M+F\cdot3^M+F\log F+N)$。其中$N$为数字个数，$F$为不同的数字的个数，$M$为人数。
- 空间复杂度$O(F+2^M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> cnt;
        for (int num : nums)
            cnt[num]++;
        vector<int> f;
        for (auto [num, freq] : cnt)
            f.emplace_back(freq);
        sort(f.rbegin(), f.rend());
        int m = quantity.size();
        vector<bool> can(1 << m);
        can[0] = true;
        vector<int> sum(1 << m);
        for (int i = 0; i < (1 << m); ++i)
            for (int j = 0; j < m; ++j)
                if (i & (1 << j))
                    sum[i] += quantity[j];
        int mask = (1 << m) - 1;
        for (int i : f) {
            for (int state = mask; state >= 0; --state) {
                if (!can[state])
                    continue;
                int rem = mask ^ state;
                for (int comb = rem; comb; comb = (comb - 1) & rem)
                    if (sum[comb] <= i)
                        can[state ^ comb] = true;
            }
            if (can[mask])
                return true;
        }
        return false;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def canDistribute(self, nums: List[int], quantity: List[int]) -> bool:
        m = len(quantity)
        cnt = list(collections.Counter(nums).values())
        cnt.sort(reverse=True)
        s = [0] * (1 << m)
        for i in range(1 << m):
            for j in range(m):
                if i & (1 << j) > 0:
                    s[i] += quantity[j]
        can = [False] * (1 << m)
        can[0] = True
        mask = (1 << m) - 1
        for freq in cnt:
            for state in range(mask, -1, -1):
                if not can[state]:
                    continue
                rem = mask ^ state
                nxt = rem
                while nxt > 0:
                    if s[nxt] <= freq:
                        can[state ^ nxt] = True
                    nxt = (nxt - 1) & rem
            if can[mask]:
                return True
        return False
```

:::

<Utterances />
