# Leetcode 第40场双周赛题解

## Problem A - [最大重复子字符串](https://leetcode-cn.com/problems/maximum-repeating-substring/)

### 方法一：暴力枚举

时间复杂度$\mathcal{O}(|S||W|\frac{|S|}{|W|}=|S|^2)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        n = len(sequence)
        m = len(word)
        for i in range(n // m, 0, -1):
            if word * i in sequence:
                return i
        return 0
```

:::

### 方法二：KMP算法

利用KMP算法在`sequence`中匹配`word`。每次匹配到时，检查$|W|$位之前是否也能匹配，如果也能匹配，则续接上（动态规划思想）。

时间复杂度$\mathcal{O}(|S|+|W|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        n = len(sequence)
        m = len(word)
        s = word + '#' + sequence
        pi = [0] * (n + m + 1)
        match = [0] * (n + m + 1)
        for i in range(1, n + m + 1):
            j = pi[i - 1]
            while j > 0 and s[i] != s[j]:
                j = pi[j - 1]
            pi[i] = j + 1 if s[i] == s[j] else 0
            if pi[i] == m:
                match[i] = match[i - m] + 1 if i >= m else 1
        return max(match)
```

:::

## Problem B - [合并两个链表](https://leetcode-cn.com/problems/merge-in-between-linked-lists/)

比赛就不要考虑空间复杂度优化了，直接转数组之后再转回链表。这里的一个小窍门是利用Python的生成器实现链表快速转数组。

时间复杂度$\mathcal{O}(|L_1|+|L_2|)$。

::: details 参考代码（Python 3）

```python
def flatten(node):
    p = node
    while p:
        yield p.val
        p = p.next

class Solution:
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
        la = list(flatten(list1))
        lb = list(flatten(list2))
        ans = la[:a] + lb + la[b+1:]
        sen = ListNode(0)
        p = sen
        for i in ans:
            p.next = ListNode(i)
            p = p.next
        return sen.next
```

:::

## Problem C - [设计前中后队列](https://leetcode-cn.com/problems/design-front-middle-back-queue/)

利用两个双端队列（deque）来实现。这里定义平衡状态为$R-1\leq L\leq R$。为了保证在所有操作执行后都能够回到平衡状态，专门实现了一个`maintain()`方法用于维护这一平衡状态。

在满足平衡状态的情况下，不难设计出各种操作的实现方法。

所有操作的时间复杂度都为$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class FrontMiddleBackQueue {
    deque<int> left, right;
    void maintain() {
        if (left.size() > right.size()) {
            right.push_front(left.back());
            left.pop_back();
        } else if (left.size() + 1 < right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
    }
public:
    FrontMiddleBackQueue() {
    }
    
    void pushFront(int val) {
        left.push_front(val);
        maintain();
    }
    
    void pushMiddle(int val) {
        left.push_back(val);
        maintain();
    }
    
    void pushBack(int val) {
        right.push_back(val);
        maintain();        
    }
    
    int popFront() {
        if (left.empty()) {
            if (right.empty())
                return -1;
            int ans = right.front();
            right.pop_front();
            return ans;
        }
        int ans = left.front();
        left.pop_front();
        maintain();
        return ans;
    }
    
    int popMiddle() {
        if (left.empty() && right.empty())
            return -1;
        if (left.size() == right.size()) {
            int ans = left.back();
            left.pop_back();
            return ans;
        }
        int ans = right.front();
        right.pop_front();
        return ans;
    }
    
    int popBack() {
        if (right.empty())
            return -1;
        int ans = right.back();
        right.pop_back();
        maintain();
        return ans;
    }
};

```

:::

## Problem D - [得到山形数组的最少删除次数](https://leetcode-cn.com/problems/minimum-number-of-removals-to-make-mountain-array/)

从左到右计算一次LIS，再从右到左计算一次LIS，就可以得到以每一个位置为中心点的山形数组的最大长度，从而可以得到最少需要的删除次数。

时间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> L(n), R(n);
        vector<int> LIS;
        for (int i = 0; i < n; ++i) {
            auto it = lower_bound(LIS.begin(), LIS.end(), nums[i]);
            if (it == LIS.end()) {
                L[i] = LIS.size();
                LIS.emplace_back(nums[i]);
            } else {
                L[i] = it - LIS.begin();
                *it = nums[i];
            }
        }
        LIS.clear();
        for (int i = n - 1; i >= 0; --i) {
            auto it = lower_bound(LIS.begin(), LIS.end(), nums[i]);
            if (it == LIS.end()) {
                R[i] = LIS.size();
                LIS.emplace_back(nums[i]);
            } else {
                R[i] = it - LIS.begin();
                *it = nums[i];
            }
        }
        int ans = n;
        for (int i = 0; i < n; ++i) {
            if (L[i] > 0 && R[i] > 0)
                ans = min(ans, n - L[i] - R[i] - 1);
        }
        return ans;
    }
};
```

:::

<Utterances />
