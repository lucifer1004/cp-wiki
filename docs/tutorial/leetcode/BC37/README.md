# Leetcode 第37场双周赛题解

## Problem A - [删除某些元素后的数组均值](https://leetcode.cn/problems/mean-of-array-after-removing-some-elements/)

按照要求，对数组排序，删除最小和最大的5%，然后计算均值即可。

时间复杂度$O(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    double trimMean(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        if (n == 0)
            return 0.0;
        double sum = 0;
        for (int i = n / 20; i < n - n / 20; ++i)
            sum += arr[i];
        return sum / (n - n / 10);
    }
};
```

:::

## Problem B - [网络信号最好的坐标](https://leetcode.cn/problems/coordinate-with-maximum-network-quality/)

信号塔一定建在由$(0,0)$和$(50,50)$所围成的矩形范围内。枚举信号塔位置，求出最大的总信号强度即可。

时间复杂度$O(ND^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
    int calc(vector<vector<int>> &towers, int r, int x, int y) {
        double res = 0.0;
        for (auto &tower : towers) {
            int dx = abs(x - tower[0]);
            int dy = abs(y - tower[1]);
            double d = sqrt(dx * dx + dy * dy);
            if (d > r)
                continue;
            res += floor((double)tower[2] / (1 + d));
        }
        return (int)res;
    }
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int hi = 0;
        int ax = 0, ay = 0;
        for (int x = 0; x <= 50; ++x)
            for (int y = 0; y <= 50; ++y) {
                int power = calc(towers, radius, x, y);
                if (power > hi)
                    hi = power, ax = x, ay = y;
            }
        return {ax, ay};
    }
};
```

:::

## Problem C - [大小为 K 的不重叠线段的数目](https://leetcode.cn/problems/number-of-sets-of-k-non-overlapping-line-segments/)

线段在端点处重合的情况比较让人讨厌，不妨增加$k-1$个点，然后改为选取端点不能重合的线段，易知这与原题是等价的。进一步地，因为线段端点不能重合，所以我们只需要在$n+k-1$个点中选取$2k$个，然后将相邻两个点依次连成线段即可。

::: details 参考代码（Python 3）

```python
from math import comb

class Solution:
    def numberOfSets(self, n: int, k: int) -> int:
        return comb(n + k - 1, 2 * k) % 1000000007
```

:::

## Problem D - [奇妙序列](https://leetcode.cn/problems/fancy-sequence/)

本题可以直接套用[Luogu P3373 【模板】线段树2](https://www.luogu.com.cn/problem/P3373)的实现。需要注意的点是，加法和乘法各自需要一个懒标记，在乘法运算或进行乘法懒标记的下推时，需要同时修改加法的懒标记。

除初始化外，各操作的时间复杂度均为$O(\log N)$。

::: details 参考代码（C++）

```cpp
#define MAXN 100005
#define MOD 1000000007
#define lson (idx << 1)
#define rson (idx << 1 | 1)
typedef long long ll;

struct Seg{
    int l, r, val = 0, lazymul = 1, lazyadd = 0;
};

class Fancy {
    int len = 0;
    Seg s[MAXN << 2];
    
    void build(int idx, int l, int r) {
        s[idx].l = l, s[idx].r = r;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
    }
    
    void pushdown(int idx) {
        for (int i = lson; i <= rson; ++i) {
            if (s[idx].lazymul != 1) {
                s[i].val = (ll)s[i].val * s[idx].lazymul % MOD;
                s[i].lazymul = (ll)s[i].lazymul * s[idx].lazymul % MOD;
                s[i].lazyadd = (ll)s[i].lazyadd * s[idx].lazymul % MOD;
            }
            if (s[idx].lazyadd) {
                s[i].val = ((ll)s[i].val + (ll)(s[i].r - s[i].l + 1) * s[idx].lazyadd) % MOD;
                s[i].lazyadd = ((ll)s[i].lazyadd + s[idx].lazyadd) % MOD;
            }
        }
        s[idx].lazymul = 1;
        s[idx].lazyadd = 0;
    }
    
    void calc(int idx) {
        s[idx].val = ((ll)s[lson].val + s[rson].val) % MOD;
    }
    
    void add(int idx, int l, int r, int d) {
        if (s[idx].l >= l && s[idx].r <= r) {
            s[idx].val = ((ll)s[idx].val + (ll)(s[idx].r - s[idx].l + 1) * d) % MOD;
            s[idx].lazyadd = ((ll)s[idx].lazyadd + d) % MOD;
            return;
        }
        pushdown(idx);
        int mid = (s[idx].l + s[idx].r) >> 1;
        if (l <= mid)
            add(lson, l, r, d);
        if (mid < r)
            add(rson, l, r, d);
        calc(idx);
    }
    
    void mul(int idx, int l, int r, int d) {
        if (s[idx].l >= l && s[idx].r <= r) {
            s[idx].val = (ll)s[idx].val * d % MOD;
            s[idx].lazyadd = (ll)s[idx].lazyadd * d % MOD;
            s[idx].lazymul = (ll)s[idx].lazymul * d % MOD;
            return;
        }
        pushdown(idx);
        int mid = (s[idx].l + s[idx].r) >> 1;
        if (l <= mid)
            mul(lson, l, r, d);
        if (mid < r)
            mul(rson, l, r, d);
        calc(idx);
    }
    
    int query(int idx, int l, int r) {
        if (s[idx].l >= l && s[idx].r <= r)
            return s[idx].val;
        pushdown(idx);
        int mid = (s[idx].l + s[idx].r) >> 1;
        int ans = 0;
        if (l <= mid)
            ans += query(lson, l, r);
        if (mid + 1 <= r)
            ans += query(rson, l, r);
        return ans;
    }
public:
    Fancy() {
        build(1, 1, 100000);
    }
    
    void append(int val) {
        len++;
        add(1, len, len, val);
    }
    
    void addAll(int inc) {
        if (len)
            add(1, 1, len, inc);
    }
    
    void multAll(int m) {
        if (len)
            mul(1, 1, len, m);
    }
    
    int getIndex(int idx) {
        if (idx + 1 > len)
            return -1;
        return query(1, idx + 1, idx + 1);
    }
};
```

:::

除此之外，本题还可以利用前缀数组实现更优的复杂度，具体实现可以参考[zerotrac的题解](https://leetcode.cn/problems/fancy-sequence/solution/qi-miao-xu-lie-by-zerotrac2/)。

<Utterances />
