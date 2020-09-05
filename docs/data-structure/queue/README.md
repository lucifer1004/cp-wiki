---
sidebarDepth: 3
---

# 队列

队列（Queue）是一种具有先进先出特性的线性数据结构。

## 双端队列

双端队列（Deque）是可以在两端进行插入和弹出操作的线性数据结构。

## 单调队列

单调队列（Monotonic Queue）在数据结构层面就是最普通的队列（或双端队列），但我们需要在新元素入队时维护队列的单调性，使队列中的元素始终保持升序或降序。在一类与区间有关的问题中，单调队列可以实现$O(N)$的复杂度，因为每个元素至多入队和出队一次。

## 练习题

### [LC862 - 和至少为K的最短子数组](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/)

::: details 提示一

计算前缀和。

:::

::: details 提示二

用单调队列维护单调递增的前缀和。注意，如果最左端的一个元素已经被使用过，那么后面不会再使用它（因为后面使用它得到的区间长度一定比当前得到的区间长度更长）。

:::

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        vector<ll> s(n + 1);
        for (int i = 1; i <= n; ++i)
            s[i] = s[i - 1] + A[i - 1];
        deque<int> dq;
        int ans = n + 1;
        for (int i = 0; i <= n; ++i) {
            while (!dq.empty() && s[dq.back()] >= s[i])
                dq.pop_back();
            while (!dq.empty() && s[dq.front()] + K <= s[i]) {
                ans = min(ans, i - dq.front());
                dq.pop_front();
            }
            dq.push_back(i);
        }
        return ans == n + 1 ? -1 : ans;
    }
};
```

:::

### [KS2019C2 - Circuit Board](https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050ff2/0000000000150aae)

::: details 提示一

求出第$i$行以$(i,j)$结尾的最长的合法长度。因为有$k$的限制，我们需要知道区间最大值和最小值，并且在指针移动过程中，我们需要对其进行更新。用`set`是一种可行的策略，还有更优的方法吗？

:::

::: details 提示二

使用两个单调双端队列，一个升序，一个降序。

:::

::: details 提示三

对于每一列求解最大矩形面积问题。

:::

::: details 参考代码（C++）

<<<@/docs/tutorial/kick-start/2019C/src/b2.cpp

:::

<Utterances />
