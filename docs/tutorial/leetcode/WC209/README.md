# Leetcode 第209场周赛题解

## Problem A - [特殊数组的特征值](https://leetcode.cn/problems/special-array-with-x-elements-greater-than-or-equal-x/)

### 方法一：暴力枚举特征值

枚举所有可能的特征值（最大为$N$），判断是否成立。

时间复杂度$O(N^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i <= n; ++i) {
            int cnt = 0;
            for (int num : nums)
                if (num >= i)
                    cnt++;
            if (cnt == i)
                return i;
        }
        return -1;
    }
};
```

:::

### 方法二：排序+枚举特征值

先排序，然后枚举特征值，这样可以快速找到符合每个特征值的元素个数。

时间复杂度$O(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i <= n; ++i) {
            int d = nums.end() - lower_bound(nums.begin(), nums.end(), i);
            if (d == i)
                return i;
        }
        return -1;
    }
};
```

:::

### 方法三：计数数组后缀和

我们可以首先进行计数（$\geq N$的元素视为$N$，因为特征值最大为$N$），然后计算计数数组的后缀和，就可以直接得到不小于某一个数的元素个数。

时间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> cnt(n + 1);
        for (int num : nums)
            cnt[min(num, n)]++;
        for (int i = n; i >= 0; --i) {
            if (i < n)
                cnt[i] += cnt[i + 1];
            if (cnt[i] == i)
                return i;
        }
        return -1;
    }
};
```

:::

## Problem B - [奇偶树](https://leetcode.cn/problems/even-odd-tree/)

经典层次遍历。BFS后得到每一层的序列，然后逐层检查即可。

总时间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        vector<vector<int>> v;
        queue<pair<TreeNode*, int>> q;
        q.emplace(root, 0);
        while (!q.empty()) {
            TreeNode *u = q.front().first;
            int lev = q.front().second;
            q.pop();
            if (!u)
                continue;
            if (lev >= v.size())
                v.push_back({});
            v[lev].emplace_back(u->val);
            q.emplace(u->left, lev + 1);
            q.emplace(u->right, lev + 1);
        }
        for (int i = 0; i < v.size(); ++i) {
            if (i % 2 == 0) {
                for (int j = 0; j < v[i].size(); ++j) {
                    if (v[i][j] % 2 == 0 || (j + 1 < v[i].size() && v[i][j] >= v[i][j + 1]))
                        return false;
                }
            } else {
                for (int j = 0; j < v[i].size(); ++j) {
                    if (v[i][j] % 2 == 1 || (j + 1 < v[i].size() && v[i][j] <= v[i][j + 1]))
                        return false;
                }
            }
        }
        return true;
    }
};
```

:::

## Problem C - [可见点的最大数目](https://leetcode.cn/problems/maximum-number-of-visible-points/)

首先排除与人的位置重合的点，只考虑剩下的点。

计算每个点到人的位置的极角，然后按极角排序。因为可以循环，所以把整个数组加上$360^\circ$再接到后面。

接下来双指针找出覆盖最多点的区间即可。

最后返回答案时，把与人的位置重合的点加上。

总时间复杂度$O(N\log N)$。

::: details 参考代码（C++）

```cpp
const double eps = 1e-8;

class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        int x = location[0], y = location[1];
        int same = 0;
        vector<double> v;
        for (auto p : points) {
            int px = p[0], py = p[1];
            if (px == x && py == y)
                same++;
            else
                v.emplace_back(atan2(py - y, px - x) * 180 / M_PI);
        }
        sort(v.begin(), v.end());
        int m = v.size();
        for (int i = 0; i < m; ++i)
            v.emplace_back(v[i] + 360);
        int r = 0, hi = 0;
        for (int l = 0; l < m; ++l) {
            while (r + 1 < v.size() && v[r + 1] - v[l] <= (double)angle + eps)
                r++;
            hi = max(hi, r - l + 1);
        }
        return hi + same;
    }
};
```

:::

## Problem D - [使整数变为 0 的最少操作次数](https://leetcode.cn/problems/minimum-one-bit-operations-to-make-integers-zero/)

要注意到的是，因为必须首先将高位的$1$翻转为$0$，所以本题其实只存在一种合法的操作顺序，我们只要按照这一顺序进行操作即可。

### 方法一：递归

手算几个数，可以发现$F(2^n)=2^{n+1}-1$，因此我们可以将其作为一个捷径。

我们需要考虑两种情况：

1. 把当前数变为$0$。我们首先要找到最高位的$1$，找到之后，我们需要的翻转次数，就是将之后的位置变为$10\dots0$，再将最高位翻转，然后将剩下的数变为$0$。因为剩下的数必然是$2$的幂次，就可以使用上面的捷径。
2. 把当前数变为$10\dots 0$。如果$1$对应的位置已经是$1$，我们只需要将后面的数变为$0$；否则，我们需要先把后面变为$10\dots0$，将最高位翻转，再将剩下的数变为$0$。

实现这两个函数，递归计算即可。

::: details 参考代码（C++）

```cpp
class Solution {
    int f(int n) {
        if (n <= 1)
            return n;
        int t = 32 - __builtin_clz(n) - 1;
        return (1 << t) + g(n ^ (1 << t), t - 1);
    }
    
    int g(int n, int t) {
        if (t == 0)
            return 1 - n;
        if (n & (1 << t))
            return f(n ^ (1 << t));
        return (1 << t) + g(n, t - 1);
    }
public:
    int minimumOneBitOperations(int n) {
        return f(n);
    }
};
```

:::

### 方法二：格雷码

如果进一步观察，可以发现，题目中给出的操作，实际上就是从Gray(n)变换为Gray(n-1)的操作。所以我们可以直接套用求逆格雷码的方法来进行求解。

时间复杂度$O(\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumOneBitOperations(int n) {
        int ans = 0;
        while (n) {
            ans ^= n;
            n >>= 1;
        }
        return ans;
    }
};
```

:::

<Utterances />
