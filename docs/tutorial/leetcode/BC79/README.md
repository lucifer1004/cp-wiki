# Leetcode 第79场周赛题解

## Problem A - [判断一个数的数字计数是否等于数位的值](https://leetcode.cn/problems/check-if-number-has-equal-digit-count-and-digit-value/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(|S|)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def digitCount(self, num: str) -> bool:
        c = collections.Counter(num)
        return all(int(ch) == c[str(i)] for i, ch in enumerate(num))
```

:::

## Problem B - [最多单词数的发件人](https://leetcode.cn/problems/sender-with-largest-word-count/)

### 方法一：排序 + 贪心

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def largestWordCount(self, messages: List[str], senders: List[str]) -> str:
        users = collections.Counter()
        for msg, sender in zip(messages, senders):
            users[sender] += msg.count(' ') + 1
        return max((users[key], key) for key in users)[1]
```

:::

## Problem C - [道路的最大总重要性](https://leetcode.cn/problems/maximum-total-importance-of-roads/)

### 方法一：贪心

按度数排序之后再赋点权。

- 时间复杂度 $\mathcal{O}(N\log N)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        deg = [0] * n
        for u, v in roads:
            deg[u] += 1
            deg[v] += 1
        deg.sort(reverse=True)
        return sum(deg[i] * (n - i) for i in range(n))
```

:::

## Problem D - [以组为单位订音乐会的门票](https://leetcode.cn/problems/booking-concert-tickets-in-groups/)

### 方法一：线段树

使用支持二分查找、前缀和以及单点更新的线段树来完成有关操作。

- 初始化时间复杂度为 $\mathcal{O}(N\log N)$，`gather` 操作时间复杂度为  $\mathcal{O}(\log N)$，`scatter` 操作均摊时间复杂度为$\mathcal{O}(\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
#define lson (idx << 1)
#define rson (idx << 1 | 1)
using ll = long long;

struct Node {
    int l, r, hi;
    ll sum;
} s[50005 << 2];

void calc(int idx) {
    s[idx].hi = max(s[lson].hi, s[rson].hi);
    s[idx].sum = s[lson].sum + s[rson].sum;
}

void build(int idx, int l, int r, int val) {
    s[idx].l = l, s[idx].r = r, s[idx].hi = val;
    s[idx].sum = 1LL * val * (r - l + 1);
    if (l == r) return;

    int m = (l + r) / 2;
    build(lson, l, m, val);
    build(rson, m + 1, r, val);
}

int lb(int idx, int v) {
    if (s[idx].hi < v) return -1;

    if (s[idx].l == s[idx].r) return s[idx].l;

    int m = (s[idx].l + s[idx].r) / 2;
    if (s[lson].hi >= v) return lb(lson, v);
    return lb(rson, v);
}

ll query(int idx, int p) {
    if (s[idx].r <= p) return s[idx].sum;

    int m = (s[idx].l + s[idx].r) / 2;
    ll ans = query(lson, p);
    if (p >= m + 1) ans += query(rson, p);

    return ans;
}

void update(int idx, int p, int v) {
    if (s[idx].l == s[idx].r && s[idx].l == p) {
        s[idx].hi = s[idx].sum = v;
        return;
    }

    int m = (s[idx].l + s[idx].r) / 2;
    if (p <= m) update(lson, p, v);
    else update(rson, p, v);

    calc(idx);
}

class BookMyShow {
    int n, m, ptr;
    vector<int> v;

public:
    BookMyShow(int n, int m)
        : n(n), m(m), ptr(1), v(vector<int>(n + 1)) {
        build(1, 1, n, m);
    }

    vector<int> gather(int k, int maxRow) {
        int row = lb(1, k);
        if (row == -1 || row > maxRow + 1) return {};

        int l = v[row];
        v[row] += k;
        update(1, row, m - v[row]);

        return {row - 1, l};
    }

    bool scatter(int k, int maxRow) {
        if (query(1, maxRow + 1) < k)
            return false;

        while (k) {
            while (v[ptr] == m)
                ptr++;
            int used = min(k, m - v[ptr]);
            v[ptr] += used;
            k -= used;
            update(1, ptr, m - v[ptr]);
        }

        return true;
    }
};
```

:::

<Utterances />
