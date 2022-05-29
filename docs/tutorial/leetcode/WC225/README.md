# Leetcode 第225场周赛题解

## Problem A - [替换隐藏数字得到的最晚时间](https://leetcode.cn/problems/latest-time-by-replacing-hidden-digits/)

贪心替换即可。注意第一个数字和第二个数字有相互的依赖关系。

- 时间复杂度$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string maximumTime(string time) {
        if (time[0] == '?') {
            if (time[1] == '?' || time[1] < '4')
                time[0] = '2';
            else
                time[0] = '1';
        }
        if (time[1] == '?') {
            if (time[0] == '2')
                time[1] = '3';
            else
                time[1] = '9';
        }
        if (time[3] == '?')
            time[3] = '5';
        if (time[4] == '?')
            time[4] = '9';
        return time;
    }
};
```

:::

## Problem B - [满足三条件之一需改变的最少字符数](https://leetcode.cn/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/)

计数后分别考虑三种条件即可：

- 要实现条件三，我们只需要找出在两个字符串中总计出现次数最多的那个字符，然后将剩余字符都替换为它。
- 条件一和二实际上是一样的，我们只需要考虑条件一，然后交换两个字符串的计数数组再计算一次就等于考虑了条件二。
    - 对于条件一，我们考虑令$A$中所有字符都小于$c$，$B$中所有字符都不小于$c$，枚举$c$找出最优解即可。
    - 这里可以利用前缀和进一步优化，但因为$|\sum|$本身很小，所以不用前缀和也没关系。

- 时间复杂度$\mathcal{O}(N+M+|\sum|^2)$。其中$|\sum|$为字母表的大小，本题中$|\sum|=26$。
- 空间复杂度$\mathcal{O}(|\sum|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minCharacters(string a, string b) {
        vector<int> ca(26), cb(26);
        int n = a.size(), m = b.size();
        for (char c : a)
            ca[c - 'a']++;
        for (char c : b)
            cb[c - 'a']++;
        int ans = n + m;
        for (int i = 0; i < 26; ++i)
            ans = min(ans, n + m - ca[i] - cb[i]);
        
        auto make_smaller = [&](vector<int> &a, vector<int> &b) {
            for (int i = 1; i < 26; ++i) {
                int tot = 0;
                for (int j = i; j < 26; ++j)
                    tot += a[j];
                for (int j = 0; j < i; ++j)
                    tot += b[j];
                ans = min(ans, tot);
            }
        };        
        
        make_smaller(ca, cb);
        make_smaller(cb, ca);
        
        return ans;
    }
};
```

:::

## Problem C - [找出第 K 大的异或坐标值](https://leetcode.cn/problems/find-kth-largest-xor-coordinate-value/)

首先，如何求出每个坐标的异或值？我们可以用类似二维前缀和的办法来求。因为$\oplus$本身就是自己的逆运算，所以不需要像二维前缀和那样有$+$有$-$，直接全用$\oplus$即可。

一共$NM=10^6$个数，我们要找出第$K$大，这里有几种常用的办法：

1. 快速选择（快速排序思想），平均时间复杂度$\mathcal{O}(NM)$，但可能存在极端情况，为了避免极端情况，可以对得到的数组预先进行一次洗牌。
2. 排序，平均时间复杂度$\mathcal{O}(NM\log(NM))$。
3. 小根堆，维护$K$个最大的元素，平均时间复杂度$\mathcal{O}(NM\log K)$。

这里我使用的是第三种方法。实际测试下来，使用第二种方法也可以通过。

- 时间复杂度$\mathcal{O}(NM\log K)$，其中$N$是矩阵的行数，$M$是矩阵的列数。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> v(n + 1, vector<int>(m + 1));
        priority_queue<int, vector<int>, greater<>> q;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                v[i][j] = v[i - 1][j] ^ v[i][j - 1] ^ v[i - 1][j - 1] ^ matrix[i - 1][j - 1];
                q.emplace(v[i][j]);
                if (q.size() > k)
                    q.pop();
            }
        return q.top();
    }
};
```

:::

## Problem D - [放置盒子](https://leetcode.cn/problems/building-boxes/)

本题需要一些观察。题目中的几个范例其实已经给出了提示：最理想的情况下，每一层都是从$1$开始的等差数列。特别地，在当前层为$n=\frac{k(k+1)}{2}$的情况下，上一层恰好可以放下$\frac{k(k-1)}{2}$个箱子。

那么，在某一层的箱子数不能表示为一个等差数列的和的情况下，它的上面一层可以放多少个箱子呢？经过简单的尝试，我们可以发现，当$n=\frac{k(k+1)}{2}+1$时，无法比之前多放箱子；而随着$n$继续增加，$n$每增加$1$就可以多放$1$个箱子。这在数学上也是严密的，因为相邻的两个等差数列和$\frac{k(k-1)}{2}$和$\frac{k(k+1)}{2}$之间的差为$k$，而它们能放箱子的个数的差为$k-1$。

这样，我们就可以用二分搜索来确定最下层的箱子个数。在最下层箱子数一定的情况下，我们根据上面的推导，利用与当前层箱子数相邻的两个等差数列和，确定当前层的上方可以放的箱子个数，然后逐层上推即可。

- 预处理时间复杂度$\mathcal{O}(\sqrt{MAXN})$，单次运行时间复杂度$\mathcal{O}(\sqrt{N}\log N\log{MAXN})$。考虑到使用了记忆化，在连续多次运行的情况下，运行时间可以进一步缩短。
- 空间复杂度$\mathcal{O}(\sqrt{MAXN})$。

::: details 参考代码（C++）

```cpp
bool init = false;
int MAXN = 2e9;
vector<int> total;
unordered_map<int, long long> memo;

class Solution {
public:
    int minimumBoxes(int n) {
        if (!init) {
            init = true;
            total = {0};
            for (int i = 0; 1LL * i * (i + 1) / 2 < MAXN; ++i)
                total.emplace_back(1LL * i * (i + 1) / 2);
        }
        
        auto solve = [&](int num) {
            if (memo.count(num))
                return memo[num];
            int num0 = num;
            long long ans = num;
            while (num > 1) {
                auto it = lower_bound(total.begin(), total.end(), num);
                int r = *it, l = *prev(it), vl = *prev(prev(it));
                ans += num = vl + max(0, num - l - 1);
            }
            return memo[num0] = ans;
        };
        
        
        int lo = 1, hi = n;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (solve(mid) >= n)
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        return lo;
    }
};
```

:::

<Utterances />
