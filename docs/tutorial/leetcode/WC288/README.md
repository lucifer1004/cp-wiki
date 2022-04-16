# Leetcode 第288场周赛题解

## Problem A - [按奇偶性交换后的最大数字](https://leetcode-cn.com/problems/largest-number-after-digit-swaps-by-parity/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(\log^2N)$。
- 空间复杂度 $\mathcal{O}(\log N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def largestInteger(self, num: int) -> int:
        s = list(map(int, str(num)))
        n = len(s)
        for i in range(n):
            for j in range(i +1, n):
                if (s[i] - s[j]) % 2 == 0 and s[i] < s[j]:
                    s[i], s[j] = s[j], s[i]
        return int(''.join(map(str, s)))
```

:::

## Problem B - [向表达式添加括号后的最小结果](https://leetcode-cn.com/problems/minimize-result-by-adding-parentheses-to-expression/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(|S|^3)$。
- 空间复杂度 $\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimizeResult(self, expression: str) -> str:
        l, r = expression.split('+')
        best = eval(expression)
        best_expr = '(' + expression + ')'
        
        ln = len(l)
        rn = len(r)
        
        for i in range(ln):
            for j in range(rn):
                expr = l[:i] + '(' + l[i:] + '+' + r[:j+1] + ')' + r[j+1:]
                expr1 = l[:i] + ('*' if i > 0 else '') + '(' + l[i:] + '+' + r[:j+1] + ')' + ('*' if j + 1 < rn else '') + r[j+1:]
                val = eval(expr1)
                if val < best:
                    best = val
                    best_expr = expr
        
        return best_expr
```

:::


## Problem C - [K 次增加后的最大乘积](https://leetcode-cn.com/problems/maximum-product-after-k-increments/)

### 方法一：贪心

每次贪心将当前最小值增加一。

- 时间复杂度 $\mathcal{O}(K\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
  public:
    int maximumProduct(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<>> pq;
        for (int num : nums) pq.push(num);

        while (k--) {
            int u = pq.top();
            pq.pop();
            pq.push(u + 1);
        }

        ll ans = 1;
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            ans = ans * u % 1000000007;
        }

        return ans;
    }
};
```

:::

## Problem D - [花园的最大总美丽值](https://leetcode-cn.com/problems/maximum-total-beauty-of-the-gardens/)

### 方法一：枚举填满的数目，然后最大化剩余部分的最小值

- 时间复杂度 $\mathcal{O}(N\log^2N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
  public:
    long long maximumBeauty(vector<int>& flowers,
                            long long newFlowers,
                            int target,
                            int full,
                            int partial) {
        int n = flowers.size();
        sort(flowers.begin(), flowers.end());

        if (flowers[0] >= target) return 1LL * full * n;

        vector<ll> rneed(n + 1);
        int rp = n - 1;
        for (int i = n - 1; i >= 0; --i) {
            rneed[i] = max(0, target - flowers[i]);
            if (i + 1 < n) rneed[i] += rneed[i + 1];
            if (rneed[i] <= newFlowers) rp = i;
        }

        ll best = 0;
        if (rneed[0] <= newFlowers) best = 1LL * n * full;
        
        vector<ll> pre(n + 1);
        for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + flowers[i - 1];

        for (int lp = 0; lp < n; ++lp) {
            if (rneed[lp + 1] > newFlowers) continue;
            ll rem = newFlowers - rneed[lp + 1];

            ll lo = flowers[0], hi = target - 1;
            while (lo <= hi) {
                ll mid = (lo + hi) >> 1;
                int n = lower_bound(flowers.begin(), flowers.begin() + lp + 1,
                                    mid) -
                        flowers.begin();
                ll lneed = mid * n - pre[n];
                if (lneed > rem)
                    hi = mid - 1;
                else
                    lo = mid + 1;
            }

            best = max(best, hi * partial + 1LL * (n - lp - 1) * full);
        }

        return best;
    }
};
```

:::

<Utterances />
