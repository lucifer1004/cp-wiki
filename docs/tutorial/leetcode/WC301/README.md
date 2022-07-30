# Leetcode 第301场周赛题解

## Problem A - [装满杯子需要的最短总时长](https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/)

### 方法一：数学

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def fillCups(self, amount: List[int]) -> int:
        hi = max(amount)
        tot = sum(amount)
        return (tot - 1) // 2 + 1 if hi * 2 <= tot else hi
        
```

:::

## Problem B - [无限集中的最小数字](https://leetcode.cn/problems/smallest-number-in-infinite-set/)

### 方法一：平衡树

- 时间复杂度：初始化 $\mathcal{O}(C\log C)$，`popSmallest()` $\mathcal{O}(\log C)$，`addBack()` $\mathcal{O}(\log C)$。
- 空间复杂度 $\mathcal{O}(C)$。

::: details 参考代码（C++）

```cpp
class SmallestInfiniteSet {
    set<int> s;
public:
    SmallestInfiniteSet() {
        for (int i = 1; i <= 1001; ++i)
            s.insert(i);
    }
    
    int popSmallest() {
        int ret = *s.begin();
        s.erase(s.begin());
        return ret;
    }
    
    void addBack(int num) {
        s.insert(num);
    }
};

```

:::

## Problem C - [移动片段得到字符串](https://leetcode.cn/problems/move-pieces-to-obtain-a-string/)

### 方法一：依次比较

- 时间复杂度 $\mathcal{O}(|S|+|T|)$ 。
- 空间复杂度 $\mathcal{O}(|S|+|T|)$ 。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canChange(string start, string target) {
        int n = start.size();
        vector<pair<char, int>> ps, pt;
        for (int i = 0; i < n; ++i) {
            if (start[i] != '_')
                ps.emplace_back(start[i], i);
            if (target[i] != '_')
                pt.emplace_back(target[i], i);
        }
        
        if (ps.size() != pt.size())
            return false;
        
        int m = ps.size();
        for (int i = 0; i < m; ++i) {
            if (ps[i].first != pt[i].first)
                return false;
            
            if (ps[i].first == 'L' && ps[i].second < pt[i].second)
                return false;
            
            if (ps[i].first == 'R' && ps[i].second > pt[i].second)
                return false;
        }
        
        return true;
    }
};
```

:::

## Problem D - [统计理想数组的数目](https://leetcode.cn/problems/count-the-number-of-ideal-arrays/)

### 方法一：动态规划

> 本题有多种更优的解法，见官方题解区。

- 时间复杂度 $\mathcal{O}(N+K(\log K)^2)$ 。
- 空间复杂度 $\mathcal{O}(N+K)$ 。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;
const int N = 10005;

ll fexp(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = (ans * x) % MOD;
        x = (x * x) % MOD;
        y >>= 1;
    }
    return ans;
}

ll mod_inv(ll x) { return fexp(x, MOD - 2); }

bool inited = false;

ll fac[N], ifac[N];

void init() {
    if (!inited) {
        inited = true;
        fac[0] = ifac[0] = 1;
        for (int i = 1; i < N; ++i) fac[i] = (fac[i - 1] * i) % MOD;
        ifac[N - 1] = mod_inv(fac[N - 1]);
        for (int i = N - 2; i >= 0; --i) ifac[i] = (ifac[i + 1] * (i + 1)) % MOD;
    }
}

ll comb(int n, int k) { return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD; }

class Solution {
public:
    int idealArrays(int n, int maxValue) {
        init();
        ll ans = 0;
        unordered_map<int, ll> now;
        for (int i = 1; i <= maxValue; ++i) now[i] = 1;

        for (int round = 1; !now.empty() && round <= n; ++round) {
            for (auto [_, v]: now)
                ans = (ans + comb(n - 1, round - 1) * v % MOD) % MOD;
            unordered_map<int, ll> nxt;
            for (auto [k, v]: now)
                for (int i = 2; i * k <= maxValue; ++i)
                    nxt[i * k] = (nxt[i * k] + v) % MOD;
            now = move(nxt);
        }

        return ans;
    }
};
```

<Utterances />
