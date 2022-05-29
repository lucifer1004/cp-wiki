# Leetcode 第44场双周赛题解

## Problem A - [找到最高海拔](https://leetcode.cn/problems/find-the-highest-altitude/)

逐个计算并记录最大值即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int h = 0, ans = 0;
        for (int g : gain) {
            h += g;
            ans = max(h, ans);
        }
        return ans;
    }
};
```

:::

## Problem B - [需要教语言的最少人数](https://leetcode.cn/problems/minimum-number-of-people-to-teach/)

注意到好友关系不存在传递性，且好友关系不重复，所以本题并不涉及并查集这类数据结构，我们只用逐个处理好友关系即可。

因为只能教一种语言，所以我们要枚举教的语言。如果一对好友关系中双方本来就用共同会的语言，那么自然就不用教，否则需要把当前这种语言教给不会的人。因为一个人可能出现在多对好友关系中，所以要用一个集合来去重。

注意到枚举语言过程中，判断双方是否有本来就共同会的语言这一步是重复的，因此我们可以预先计算每一对好友关系是否已经满足。

- 时间复杂度$\mathcal{O}(NE)$，其中$N$为人数，同时也是语言数，$E$为好友关系的数目。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumTeachings(self, n: int, languages: List[List[int]], friendships: List[List[int]]) -> int:
        m = len(languages)
        ans = m
        s = [set(l) for l in languages]
        can = [len(s[u - 1].intersection(s[v - 1])) > 0 for u, v in friendships]
        for i in range(1, n + 1):
            need = set()
            for j, friendship in enumerate(friendships):
                u, v = friendship
                if can[j]:
                    continue
                if i not in s[u - 1]:
                    need.add(u)
                if i not in s[v - 1]:
                    need.add(v)
            ans = min(ans, len(need))
        return ans
```

:::

## Problem C - [解码异或后的排列](https://leetcode.cn/problems/decode-xored-permutation/)

题目条件中的**n为奇数**非常显眼。这是一个重要的提示信息，说明我们的解法需要利用到**n为奇数**这一条件。

我们目前拥有的信息是：

$$
a_1\oplus a_2,a_2\oplus a_3,\dots,a_{n-1}\oplus a_n
$$

我们可以利用它求出什么呢？

试着求一下前缀异或和，我们会得到：

$$
a_1\oplus a_2,a_1\oplus a_3,\dots,a_1\oplus a_n
$$

这时候，我们再把这些数异或起来：

$$
\underbrace{a_1\oplus\dots\oplus a_1}_{n-1个a_1}\oplus a_2\oplus a_3\oplus\dots\oplus a_n
$$

因为$n$是奇数，$n-1$就是偶数，那么前面的那串$a_1$就正好消掉了，我们就得到了：

$$
a_2\oplus a_3\oplus\dots\oplus a_n
$$

而我们正好又知道：

$$
a_1\oplus a_2\oplus a_3\oplus\dots\oplus a_n=1\oplus2\oplus\dots\oplus n
$$

这样我们就可以求出$a_1$，之后所有数就都可以被顺藤摸瓜地求出来了。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size() + 1;
        vector<int> pre(n);
        for (int i = 1; i < n; ++i)
            pre[i] = pre[i - 1] ^ encoded[i - 1];
        int tot_except_first = 0;
        for (int i = 1; i < n; ++i)
            tot_except_first ^= pre[i];
        vector<int> ans(n);
        ans[0] = tot_except_first;
        for (int i = 1; i <= n; ++i)
            ans[0] ^= i;
        for (int i = 1; i < n; ++i)
            ans[i] = pre[i] ^ ans[0];
        return ans;
    }
};
```

:::

## Problem D - [生成乘积数组的方案数](https://leetcode.cn/problems/count-ways-to-make-array-with-product/)

因为有选位置这个步骤，所以想到预先计算阶乘及其乘法逆元，从而可以在$\mathcal{O}(1)$时间计算出组合数。

### 方法一：宽度优先搜索

对于每一个询问：

- 首先，如果$N=1$或$K=1$，结果显然为$1$
- 对于一般的情形，我采取的是BFS的方法。每一个状态记录为$[last,used,rem,ways]$表示上一次用的数字是$last$，已经用了$used$个数，剩下的乘积是$rem$，当前的总方法数为$ways$。对于每一个状态，我们有两种转移方式：
    - 不继续拆分，直接将$rem$选一个位置放置。这里要注意$rem=1$的情形。
    - 继续进行拆分。这里为了避免重复，我们从$last+1$开始枚举因子，同时枚举的上限是$\sqrt{rem}$。对于一个可行的因子，我们进一步枚举其使用次数。这里要注意$used$不能超过$N$，同时剩下的乘积$rem$应当大于当前的因子，或者为$1$。

- 时间复杂度$\mathcal{O}(MAXN\log MOD+Q\cdot F(N,K))$，其中前半部分为预处理的耗时，$F(N,K)$是$N$和$K$的一个函数，代表处理一次询问的时间复杂度，准确的表达式暂时无法给出。

::: details 参考代码（C++）

```cpp
#define MAXN 10005

typedef long long ll;
const ll MOD = 1e9 + 7;

bool init = false;
ll fac[MAXN], inv[MAXN];

ll fexp(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) 
            ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}

ll C(ll n, ll k) {
    return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}

class Solution {
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        if (!init) {
            init = true;
            fac[0] = inv[0] = 1;
            for (int i = 1; i < MAXN; ++i) {
                fac[i] = fac[i - 1] * i % MOD;
                inv[i] = fexp(fac[i], MOD - 2);
            }
        }
        
        vector<int> ans;
        for (auto v : queries) {
            int n = v[0], k = v[1];
            if (k == 1 || n == 1) {
                ans.emplace_back(1);
                continue;
            }
            ll tot = 0;
            queue<tuple<int, int, int, ll>> q;
            q.emplace(1, 0, k, 1);
            while (!q.empty()) {
                auto [last, used, rem, ways] = q.front();
                q.pop();
                if (rem == 1) {
                    tot = (tot + ways) % MOD;
                    continue;
                } else
                    tot = (tot + ways * (n - used)) % MOD;
                for (int i = last + 1; i * i <= rem; ++i) {
                    if (rem % i != 0)
                        continue;
                    int nu = used, nrem = rem, cnt = 0;
                    while (nrem % i == 0) {
                        nrem /= i;
                        cnt++;
                        if (used + cnt > n)
                            break;
                        if (nrem > i || nrem == 1)
                            q.emplace(i, used + cnt, nrem, ways * C(n - used, cnt) % MOD);
                    }
                }
            }
            ans.emplace_back(tot);
        }
        
        return ans;
    }
};
```

:::

### 方法二：数学

实际上，我们可以将$k_i$的每一个素因子单独考虑。假设$k_i$的这一素因子为$m$重的，则我们需要考虑的是将$m$个相同的小球放入$n$个盒子中的方法总数。这可以通过隔板法计算${n+m-1}\choose m$。

最后的结果就是每一个素因子的结果的乘积。

- 时间复杂度$\mathcal{O}(MAXN\log MOD+Q\sqrt{MAXK})$，其中前半部分为预处理的耗时。

::: details 参考代码（C++）

```cpp
#define MAXN 10020

typedef long long ll;
const ll MOD = 1e9 + 7;

bool init = false;
ll fac[MAXN], inv[MAXN];

ll fexp(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) 
            ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}

ll C(ll n, ll k) {
    return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}

class Solution {
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        if (!init) {
            init = true;
            fac[0] = inv[0] = 1;
            for (int i = 1; i < MAXN; ++i) {
                fac[i] = fac[i - 1] * i % MOD;
                inv[i] = fexp(fac[i], MOD - 2);
            }
        }
        
        vector<int> ans;
        for (auto v : queries) {
            int n = v[0], k = v[1];
            if (k == 1 || n == 1) {
                ans.emplace_back(1);
                continue;
            }
            ll tot = 1;
            for (int i = 2; i * i <= k; ++i) {
                if (k % i != 0)
                    continue;
                int cnt = 0;
                while (k % i == 0) {
                    k /= i;
                    cnt++;
                }
                tot = tot * C(n + cnt - 1, cnt) % MOD;
            }
            if (k > 1)
                tot = tot * n % MOD;
            ans.emplace_back(tot);
        }
        
        return ans;
    }
};
```

:::

::: tip 小贴士

预处理部分，$inv[i]$有复杂度更优的求法。可以参考[OI-Wiki](https://oi-wiki.org/math/inverse/#n)。

:::

<Utterances />
