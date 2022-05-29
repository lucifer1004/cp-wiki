# Leetcode 第281场周赛题解

## Problem A - [统计各位数字之和为偶数的整数个数](https://leetcode.cn/problems/count-integers-with-even-digit-sum/)

### 方法一：暴力

枚举整个区间，找出所有符合条件的数字。

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countEven(self, num: int) -> int:
        ans = 0
        for i in range(1, num + 1):
            if sum(map(int, str(i))) % 2 == 0:
                ans += 1
        return ans
```

:::

## Problem B - [合并零之间的节点](https://leetcode.cn/problems/merge-nodes-in-between-zeros/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        sentinel = ListNode()
        s = 0
        p = head
        q = sentinel
        while p != None:
            if p.val == 0:
                if s != 0:
                    q.next = ListNode(s)
                    s = 0
                    q = q.next
            else:
                s += p.val
            p = p.next
        return sentinel.next
```

:::

## Problem C - [构造限制重复的字符串](https://leetcode.cn/problems/construct-string-with-repeat-limit/)

### 方法一：贪心

在不违背限制条件的情况下，总是贪心地放入当前剩余的最大的字符；否则放入次大字符；若没有次大字符，则停止。

- 时间复杂度 $\mathcal{O}(N|\Sigma|)$。
- 空间复杂度 $\mathcal{O}(N+|\Sigma|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> c(26);
        for (char ch : s)
            c[ch - 'a']++;
        
        vector<int> ans;
        int acc = 0;
        int now = -1;
        int n = s.size();
        for (int k = 0; k < n; ++k) {
            for (int i = 25; i >= 0; --i) {
                if (c[i] == 0)
                    continue;
                if (i != now || (i == now && acc < repeatLimit)) {
                    ans.push_back(i);
                    if (now != i) {
                        now = i;
                        acc = 0;
                    }
                    acc++;
                    c[now]--;
                    break;
                }
            }
        }
        string t;
        for (int i : ans)
            t.push_back(i + 'a');
        return t;
    }
};
```

:::

## Problem D - [统计可以被 K 整除的下标对数目](https://leetcode.cn/problems/count-array-pairs-divisible-by-k/)

### 方法一：哈希表

将所有数按照与 $K$ 的最大公约数分组，之后以组为单位进行配对。为了避免重复，只考虑 $k_1\le k_2$ 的情况：

- $k_1<k_2$，计入 $v_1v_2$ 组
- $k_1=k_2$，计入 $\frac{v_1(v_1-1)}{2}$ 组

复杂度：

- 时间复杂度 $\mathcal{O}(N\log K+\tau^2(K))$，其中 $\tau(K)$ 为 $K$ 的正因子个数。
- 空间复杂度 $\mathcal{O}(\tau(K))$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long coutPairs(vector<int>& nums, int k) {
        long long ans = 0;
        int n = nums.size();
        unordered_map<int, int> gc;
        for (int num : nums)
            gc[__gcd(num, k)]++;
        for (auto [k1, v1] : gc)
            for (auto [k2, v2] : gc) {
                if (1LL * k1 * k2 % k == 0) {
                    if (k1 < k2)
                        ans += 1LL * v1 * v2;
                    else if (k1 == k2)
                        ans += 1LL * v1 * (v1 - 1) / 2;
                }
            }
        return ans;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def coutPairs(self, nums: List[int], k: int) -> int:
        c = collections.Counter(math.gcd(num, k) for num in nums)
        return sum(c[k1] * c[k2] if k1 < k2 else c[k1] * (c[k1] - 1) // 2 if k1 == k2 else 0 for k1 in c for k2 in c if k1 * k2  % k == 0)
```

:::

<Utterances />
