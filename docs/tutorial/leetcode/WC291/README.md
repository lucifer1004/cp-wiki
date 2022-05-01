# Leetcode 第291场周赛题解

## Problem A - [移除指定数字得到的最大结果](https://leetcode.cn/problems/remove-digit-from-number-to-maximize-result/)

### 方法一：暴力

尝试移除每一个目标数字，并选择结果中的最大值。

- 时间复杂度 $\mathcal{O}(N^2)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def removeDigit(self, number: str, digit: str) -> str:
        ans = 0
        for i, ch in enumerate(number):
            if ch == digit:
                ans = max(ans, int(number[:i] + number[i + 1:]))
        return str(ans)
```

:::

### 方法二：预处理出每个字符后面第一个不同的字符

先从右往左遍历，预处理得到每个字符后面第一个不同的字符。然后从左往右遍历，如果发现目标字符，并且它后面第一个不同的字符是比它要大的，那就将它删去。如果没有找到这样的情况，就删去最后一个目标字符。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def removeDigit(self, number: str, digit: str) -> str:
        n = len(number)
        right = [' '] * n
        p = ' '
        q = ' '
        for i in range(n - 1, -1, -1):
            if number[i] != p:
                right[i] = p
                p, q = number[i], p
            else:
                right[i] = q
        last = -1
        for i in range(n):
            if number[i] == digit:
                if right[i] > number[i]:
                    return number[:i] + number[i + 1:]
                last = i
        return number[:last] + number[last + 1:]
```

:::

### 方法三：方法二在本题限制条件下的简化

在本题限制条件下，我们实际上可以只比较下一个字母，并不需要考虑它是否与当前字母相同。因为如果相同，那么无论删前一个还是删后一个，结果是相同的。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def removeDigit(self, number: str, digit: str) -> str:
        n = len(number)
        for i in range(n):
            if number[i] == digit:
                if i == n - 1 or number[i + 1] > number[i]:
                    return number[:i] + number[i + 1:]
                last = i
        return number[:last] + number[last + 1:]
```

:::

## Problem B - [必须拿起的最小连续卡牌数](https://leetcode.cn/problems/minimum-consecutive-cards-to-pick-up/)

### 方法一：计算分组后的最小相邻差值

将所有下标按照数值分组后，计算每一个分组中相邻元素的最小差值。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumCardPickup(self, cards: List[int]) -> int:
        d = collections.defaultdict(list)
        for i, card in enumerate(cards):
            d[card].append(i)
        ans = int(1e9)
        for v in d.values():
            for i in range(len(v) - 1):
                ans = min(ans, v[i + 1] - v[i] + 1)
        return -1 if ans == int(1e9) else ans
```

:::


## Problem C - [含最多 K 个可整除元素的子数组](https://leetcode.cn/problems/k-divisible-elements-subarrays/)

因为 $N\le200$，所以枚举子数组完全可行。关键是如何去重。

### 方法一：按照数组去重（正确性有保证）

- 时间复杂度 $\mathcal{O}(N^3)$ 或 $\mathcal{O}(N^3\log N)$。
- 空间复杂度 $\mathcal{O}(N^3)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        set<vector<int>> s;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int f = 0;
            for (int j = i; j < n; ++j) {
                if (nums[j] % p == 0)
                    f++;
                if (f > k)
                    break;
                s.insert(vector<int>(nums.begin() + i, nums.begin() + j + 1));
            }
        }
        return (int)s.size();
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def countDistinct(self, nums: List[int], k: int, p: int) -> int:
        n = len(nums)
        s = set()
        for i in range(n):
            f = 0
            for j in range(i, n):
                if nums[j] % p == 0:
                    f += 1
                if f > k:
                    break
                s.add(tuple(nums[i : j + 1]))
        return len(s)
```

:::

### 方法二：哈希去重（不能保证正确）

- 时间复杂度 $\mathcal{O}(N^2)$ 或 $\mathcal{O}(N^2\log N)$。
- 空间复杂度 $\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll K1 = 7, K2 = 13, M1 = 1e9 + 7, M2 = 1e9 + 9;

class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        set<pair<ll, ll>> s;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int f = 0;
            ll v1 = 0, v2 = 0;
            for (int j = i; j < n; ++j) {
                if (nums[j] % p == 0)
                    f++;
                if (f > k)
                    break;
                v1 = (v1 * K1 + nums[j]) % M1;
                v2 = (v2 * K2 + nums[j]) % M2;
                s.emplace(v1, v2);
            }
        }
        return (int)s.size();
    }
};
```

:::

## Problem D - [字符串的总引力](https://leetcode.cn/problems/total-appeal-of-a-string/)

### 方法一：按字符分组处理

每个字符分别处理；计算贡献时，为了避免重复，按照以当前字符作为最后一个该字符的方式来统计。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    ll appealSum(string s) {
        vector<vector<int>> v(26);
        int n = s.size();
        for (int i = 0; i < 26; ++i) {
            v[i].push_back(-1);
        }
        for (int i = 0; i < n; ++i)
            v[s[i] - 'a'].push_back(i);
        ll ans = 0;
        for (int i = 0; i < 26; ++i) {
            v[i].push_back(n);
            for (int j = 1; j + 1 < v[i].size(); ++j) {
                int l = v[i][j] + 1, r = v[i][j + 1] - v[i][j];
                ans += 1LL * l * r;
            }
        }
        return ans;
    }
};
```

:::

<Utterances />
