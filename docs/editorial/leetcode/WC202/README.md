# Leetcode 第202场周赛题解

## Problem A - [存在连续三个奇数的数组](https://leetcode-cn.com/problems/three-consecutive-odds/)

直接遍历即可。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i + 2 < n; ++i)
            if ((arr[i] & 1) && (arr[i + 1] & 1) && (arr[i + 2] & 1))
                return true;
        return false;
    }
};
```

:::

## Problem B - [使数组中所有元素相等的最小操作数](https://leetcode-cn.com/problems/minimum-operations-to-make-array-equal/)

因为$\sum_{i=1}^n(2i-1)=n^2$，所以最后所有元素都应该等于$n$。分奇偶两种情况，可以计算得到

$$
f(n)=\left\{
  \begin{aligned}
    & n^2/4 & n\text{为偶数} \\
    & (n+1)(n-1)/4 & n\text{为奇数}
  \end{aligned}
\right.
$$

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(int n) {
        return n % 2 == 0 ? n * n / 4 : (n + 1) * (n - 1) / 4;
    }
};
```

:::

## Problem C - [两球之间的磁力](https://leetcode-cn.com/problems/magnetic-force-between-two-balls/)

如果存在一种放法，使得最小磁力不小于$x$，则必然存在一种放法，使得最小磁力不小于$x-1$，因此可以对结果二分。

判断可行性的方法很简单，每当当前位置满足磁力大于等于$mid$就放球，最后检查放入的数目是否大于等于需要放的球数$m$。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        int n = position.size();
        sort(position.begin(), position.end());
        m -= 2;
        int l = 1, r = position[n - 1] - position[0];
        while (l <= r) {
            int mid = (l + r) / 2;
            int left = 0, cnt = 0;
            for (int i = 1; i < n - 1; ++i) {
                if (position[n - 1] - position[i] < mid)
                    break;
                if (position[i] - position[left] >= mid)
                    left = i, cnt++;
            }
            if (cnt >= m)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return r;
    }
};
```

:::

## Problem D - [吃掉 N 个橘子的最少天数](https://leetcode-cn.com/problems/minimum-number-of-days-to-eat-n-oranges/)

直接BFS即可，注意要自顶向下，而不能自底向上，因为自底向上的过程中，会产生大量无用的$x+1$节点。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int minDays(int n) {
        unordered_set<int> s;
        queue<pair<int, int>> q;
        q.push({n, 0});
        s.insert(n);
        while (!q.empty()) {
            auto [x, d] = q.front();
            q.pop();
            if (x == 0)
                return d;
            if (x % 2 == 0 && !s.count(x / 2))
                q.push({x / 2, d + 1}), s.insert(x / 2);
            if (x % 3 == 0 && !s.count(x / 3))
                q.push({x / 3, d + 1}), s.insert(x / 3);
            if (!s.count(x - 1))
                q.push({x - 1, d + 1}), s.insert(x - 1);
        }
        return 0;
    }
};
```

:::

<Utterances />
