# 2022春中国银联专场竞赛题解

## Problem A - [回文链表](https://leetcode-cn.com/contest/cnunionpay-2022spring/problems/D7rekZ/)

### 方法一：贪心

先将链表转为数组再进行处理。

从两端开始，如果能够匹配，就一直贪心地进行匹配。

- 如果最终匹配成功，也即原本就是回文，此时在删去中间位置的数（长度为偶数时可以删去中间两个中的任意一个），仍是回文串。
- 如果无法匹配成功：
    - 尝试删去当前左侧的字符，也即左侧向后推进一位，继续匹配；
    - 尝试删去当前右侧的字符，也即右侧往前推进一位，继续匹配。

复杂度：

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        nums = []
        while head != None:
            nums.append(head.val)
            head = head.next

        n = len(nums)
        l = 0
        r = n - 1
        while l <= r and nums[l] == nums[r]:
            l += 1
            r -= 1
        if l > r:
            return True
        
        return nums[l+1:r+1] == nums[l+1:r+1][::-1] or nums[l:r] == nums[l:r][::-1]
```

:::

## Problem B - [优惠活动系统](https://leetcode-cn.com/contest/cnunionpay-2022spring/problems/kDPV0f/)

### 方法一：模拟

按要求模拟即可。

具体各操作的复杂度不再一一列出。

::: details 参考代码（C++）

```cpp
struct Activity {
    int priceLimit, discount, number, userLimit;
    unordered_map<int, int> cnt;
};

class DiscountSystem {
    unordered_map<int, Activity> activities;
public:
    DiscountSystem() {
    }
    
    void addActivity(int actId, int priceLimit, int discount, int number, int userLimit) {
        activities[actId] = Activity{priceLimit, discount, number, userLimit};
    }
    
    void removeActivity(int actId) {
        activities.erase(actId);
    }
    
    int consume(int userId, int cost) {
        int best_id = INT_MAX;
        int best_discount = 0;
        for (auto [i, a] : activities) {
            if (a.number > 0 && a.cnt[userId] < a.userLimit && cost >= a.priceLimit) {
                if (a.discount > best_discount) {
                    best_discount = a.discount;
                    best_id = i;
                }
            }
        }
        
        if (best_id != INT_MAX) {
            auto &a = activities[best_id];
            a.number--;
            a.cnt[userId]++;
        }
        
        return cost - best_discount;
    }
};
```

:::

## Problem C - [理财产品](https://leetcode-cn.com/contest/cnunionpay-2022spring/problems/I4mOGz/)

### 方法一：二分答案

我们可以首先二分答案求出买到不少于 `limit` 个产品时最低价值的理财产品的价值。

此时有两种情况：

1. 二分得到的答案是零，表明此时所有产品的个数加起来不到 `limit` 个，直接返回总价值即可（注意取模）。
2. 二分得到的答案是正数。此时所有价值不小于答案的产品的个数加起来大于等于 `limit` 个，我们先求出它们的总和，再减去多算的价值刚好等于答案的产品即可。

- 时间复杂度$\mathcal{O}(N\log C)$，其中 $C=10^7$ 为价值的最大值。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxInvestment(self, product: List[int], limit: int) -> int:
        lo = 1
        hi = int(1e7)
        while lo <= hi:
            mid = (lo + hi) >> 1
            cnt = 0
            for p in product:
                cnt += max(0, p - mid + 1)
            if cnt < limit:
                hi = mid - 1
            else:
                lo = mid + 1
        
        if hi == 0:
            return sum(p * (p + 1) // 2 for p in product) % 1000000007
        
        cnt = 0
        ans = 0
        for p in product:
            if p >= hi:
                ans += (p + hi) * (p - hi + 1) // 2
                cnt += p - hi + 1
        ans -= (cnt - limit) * hi
        
        return ans % 1000000007
        
```

:::

## Problem D - [合作开发](https://leetcode-cn.com/contest/cnunionpay-2022spring/problems/lCh58I/)

### 方法一：枚举子集+计数

我们尝试找出所有不能合作的员工对。

1. 技能完全一致的员工不能合作。我们将员工按照技能分组统计，并减去同一组内员工形成的对。
2. 一个人的技能被另一个人的技能真包含时，两人不能合作。对于这种情况，我们可以枚举每一个技能组的子集，并去除当前技能组与其各个子集形成的对。

最后就可以得到答案。

- 时间复杂度$\mathcal{O}(2^C\cdot N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
from itertools import chain, combinations

def powerset(lst):
    return chain.from_iterable(combinations(lst,n) for n in range(len(lst)))

class Solution:
    def coopDevelop(self, skills: List[List[int]]) -> int:
        cnt = collections.Counter()
        n = len(skills)
        for skill in skills:
            cnt[tuple(skill)] += 1
        ans = n * (n - 1) // 2
        for m in cnt.values():
            ans -= m * (m - 1) // 2
        for skill in cnt:
            for sub in powerset(skill):
                if sub in cnt:
                    ans -= cnt[skill] * cnt[sub]
        return ans % 1000000007
```

:::

<Utterances />
