# Leetcode 第42场双周赛题解

## Problem A - [无法吃午餐的学生数量](https://leetcode.cn/problems/number-of-students-unable-to-eat-lunch/)

预先统计喜欢每种三明治的学生人数，并用栈模拟三明治堆。需要注意的是，不需要对学生的队列进行模拟，因为每次一定会找到一个喜欢当前栈顶三明治的学生，所以直接扣减人数即可。如果当前栈顶的三明治对应的学生人数已经为$0$，则可以提前终止。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        stack<int> st;
        for (int i = (int)sandwiches.size() - 1; i >= 0; --i)
            st.push(sandwiches[i]);
        vector<int> t(2);
        for (int student : students)
            t[student]++;
        while (!st.empty() && t[st.top()]) {
            t[st.top()]--;
            st.pop();
        }
        return st.size();
    }
};
```

:::

## Problem B - [平均等待时间](https://leetcode.cn/problems/average-waiting-time/)

因为顾客到达时间是有序的，所以直接模拟即可。记录厨师完成上一道菜的时间，与当前顾客的到达时间比较，就可以得到厨师开始给当前顾客做菜的时间，从而计算出厨师做完这道菜的时间和顾客的等待时间。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(1)$

::: details 参考代码（Python 3）

```python
class Solution:
    def averageWaitingTime(self, customers: List[List[int]]) -> float:
        n = len(customers)
        cook = 0
        wait = 0
        for arrival, duration in customers:
            if arrival >= cook:
                wait += duration
            else:
                wait += cook + duration - arrival
            cook = max(cook, arrival) + duration
        return wait / n
```

:::

## Problem C - [修改后的最大二进制字符串](https://leetcode.cn/problems/maximum-binary-string-after-change/)

借助`10->01`这一操作，我们可以将所有的`1`移到字符串末尾；借助`00->10`这一操作，我们可以将所有的`000...000`串变为`111...110`。在这一观察的基础上，容易想到，要得到最大的二进制字符串，我们应该首先把所有不在开头的`1`移到末尾，使得字符串变为`11...1100...0011...11`的形式，然后再用第二种操作把中间部分变为`11...10`。在这一操作顺序下，我们最终得到的字符串中最多包含一个`0`（考虑初始全为`1`的特殊情况），并且这个`0`的位置是尽可能靠后的，因此，得到的字符串就是我们要求的答案。

- 时间复杂度$\mathcal{O}(|S|)$
- 空间复杂度$\mathcal{O}(|S|)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string maximumBinaryString(string binary) {
        int n = binary.size();
        int front = 0;
        while (binary[front] == '1' && front < n)
            front++;
        if (front == n)
            return binary;
        int rest = 0;
        for (int i = front; i < n; ++i)
            if (binary[i] == '1')
                rest++;
        string ans(n - rest - 1, '1');
        if (front != n)
            ans.push_back('0');
        ans += string(rest, '1');
        return ans;
    }
};
```

:::

## Problem D - [得到连续 K 个 1 的最少相邻交换次数](https://leetcode.cn/problems/minimum-adjacent-swaps-for-k-consecutive-ones/)

如果之前做过数轴上$K$个人碰面的题目，做这道题会相对容易一些。

我们知道，对于$K$个人碰面的问题，我们应当将集合的位置选在中位数处，这样可以使得所有人移动的总路程最短。但本题中有一点不同，也即，$K$个人并不是集合到同一个位置，而是集合在$t,t+1,t+2,\dots,t+K-1$处。这种情况下，应当如何修改我们的算法呢？

事实上，我们只需要将每个人的原始坐标改为$X_i-i$，就可以将这一问题转化为原来的问题。对应到本题中，我们首先找出所有的`1`，然后得到它们的等效坐标$X_i-i$（其中$i$表示这是第$i$个`1`），接下来，我们用滑动窗口的方法，求出每一段长度为$K$的窗口内的“人”在中位数处集合的总移动距离，取其最小值即为答案。

### 对等效坐标的简单说明

为什么我们使用了等效坐标之后就可以将问题转化为集合到同一点的问题呢？考虑$K$个人的情形。假设第一个人移动到的目标位置是$t$，那么第二个人移动到的目标位置就应该是$t+1$。现在我们假设第二个人的目标位置也是$t$，这样就等于是左移了一个单位，为了保证移动的距离相等，我们需要把第二个人的初始位置也左移一个单位，这样就变成了$X_1-1$。依此类推，我们就可以得到所有人的等效坐标。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        vector<ll> one;
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] == 1)
                one.emplace_back(i - (int)one.size());
        vector<ll> pre{0};
        for (int i : one)
            pre.emplace_back(pre.back() + i);
        ll ans = 1e10;
        for (int l = 1; l + k - 1 <= one.size(); ++l) {
            int r = l + k - 1;
            int mid = (l + r) >> 1;
            ll left = one[mid - 1] * (mid - l) - pre[mid - 1] + pre[l - 1];
            ll right = pre[r] - pre[mid] - one[mid - 1] * (r - mid);
            ans = min(ans, left + right);
        }
        return ans;
    }
};
```

:::

<Utterances />
