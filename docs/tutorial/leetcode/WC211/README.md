# Leetcode 第211场周赛题解

## Problem A - [两个相同字符之间的最长子字符串](https://leetcode.cn/problems/largest-substring-between-two-equal-characters/)

我们可以记录每一个字母最早出现和最后出现的位置，然后枚举字母即可。

- 时间复杂度$O(|S|)$
- 空间复杂度$O(C)$，其中$C$为字母表的大小，本题中$C=26$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        vector<int> L(26, -1), R(26, -1);
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if (L[c] == -1)
                L[c] = i;
            R[c] = max(R[c], i);
        }
        int ans = -1;
        for (int i = 0; i < 26; ++i)
            if (R[i] != -1 && R[i] > L[i])
                ans = max(ans, R[i] - L[i] - 1);
        return ans;
    }
};
```

:::

## Problem B - [执行操作后字典序最小的字符串](https://leetcode.cn/problems/lexicographically-smallest-string-after-applying-operations/)

在本题的数据范围内，可以枚举所有可能的操作结果，从中选择最小的那一个。关键是：如何枚举？

首先考虑轮转操作。对于一个长度为$N$的字符串，每次轮转$b$个位置，等价于轮转$g=GCD(N,b)$个位置。所以，我们只需要以$g$为步长进行轮转的枚举即可。

接下来考虑增加操作。如果$g$是偶数，那么不管怎么轮转，我们只能对下标为奇数的位置进行增加操作；否则，我们也可以对下标为偶数的位置进行增加操作。根据这两种情况，枚举奇数和偶数位置的增加操作的次数即可。因为每一位是$[0,9]$之间的数，而$1\leq a\leq9$，所以我们只需要枚举操作$[0,9]$次的情形。

- 时间复杂度$O(D^2|S|^2)$，本题中$D=10$。
- 空间复杂度$O(|S|)$

::: details 参考代码（C++）

```cpp
class Solution {
    int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x % y);
    }
public:
    string findLexSmallestString(string s, int a, int b) {
        int n = s.size();
        string ans = s;
        string t = s + s;
        int g = gcd(n, b);
        for (int i = 0; i < n; i += g) {
            string p = t.substr(i, n);
            for (int j = 0; j <= 9; ++j) {
                int th = g % 2 == 0 ? 0 : 9;
                for (int k = 0; k <= th; ++k) {
                    string q(p);
                    for (int t = 1; t < n; t += 2)
                        q[t] = '0' + (q[t] - '0' + a * j) % 10;
                    for (int t = 0; t < n; t += 2)
                        q[t] = '0' + (q[t] - '0' + a * k) % 10;
                    ans = min(ans, q);
                }
            }
        }
        return ans;
    }
};
```

:::

## Problem C - [无矛盾的最佳球队](https://leetcode.cn/problems/best-team-with-no-conflicts/)

本题的数据范围显然不可能支持我们进行所有子集的枚举。我们希望找到一种顺序，使得我们在进行选择时，总是不会发生冲突。

我们可以将所有队员按照年龄升序进行排序，年龄相同时，则按照分数升序进行排序。排序之后，我们可以进行动态规划。令$dp[i]$表示最后一个队员是第$i$个队员时的最大分数（这里的$i$是重新排序后的编号）。我们只需要在$[0,i-1]$的范围内枚举上一个队员即可。这里，如果上一个队员的分数不超过当前队员的分数，就可以进行转移。

为什么这样的枚举一定是合法的呢？因为我们的最大分数总是在最后一个队员处取得（对于相同年龄的，我们是按照分数升序排序的，所以分数较高的一定在更后面），同时第$i$个队员的年龄不小于之前任意队员的年龄，所以只要第$i$个队员的分数大于等于之前的分组中最后一个队员的分数，就一定可以将第$i$个队员加入到组里，从而得到一个以第$i$个队员为最后一名队员的新的组。

- 时间复杂度$O(N^2)$
- 空间复杂度$O(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<int> order(n);
        for (int i = 0; i < n; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return ages[i] < ages[j] || (ages[i] == ages[j] && scores[i] < scores[j]);
        });
        vector<int> dp(n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int idx = order[i];
            dp[i] = scores[idx];
            for (int j = 0; j < i; ++j) {
                int last = order[j];
                if (scores[last] <= scores[idx])
                    dp[i] = max(dp[i], dp[j] + scores[idx]);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

:::

## Problem D - [带阈值的图连通性](https://leetcode.cn/problems/graph-connectivity-with-threshold/)

因为$N$最大可以到$10000$，我们显然不能枚举所有的边来构造这个图。不妨先把阈值条件放在一边，假设$P$是$A$和$B$的一个公因数，那么显然$P$也是$P$和$A$的公因数，同时也是$P$和$B$的公因数。因此，我们就可以不连接$(A,B)$，而是连接$(P,A)$和$(P,B)$。也就是说，我们可以枚举因子，然后将其所有的倍数与这一因子之间连边。

对于连通性，我们则可以借助并查集这一数据结构来实现近似$O(1)$时间复杂度的连边和查询操作。

如何把阈值考虑进来呢？很简单，只需要从$threshold+1$开始枚举因子即可。因为连边操作是近似$O(1)$时间复杂度的，所以在$threshold=0$的情况下，枚举因子并连边的时间复杂度为$\sum_{i=1}^N\frac{N}{i}=O(N\log N)$。

因为每次查询都是近似$O(1)$时间复杂度的，因此完成$Q$次查询的时间复杂度为$O(Q)$。

- 时间复杂度$O(N\log N+Q)$
- 空间复杂度$O(N)$

::: details 参考代码（C++）

```cpp
class UnionFind {
  int n;
  vector<int> parent, size;

public:
  UnionFind(int n) {
    this->n = n;
    parent = vector<int>(n);
    size = vector<int>(n, 1);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int idx) {
    if (parent[idx] == idx)
      return idx;
    return parent[idx] = find(parent[idx]);
  }

  void connect(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb) {
      if (size[fa] > size[fb]) {
        parent[fb] = fa;
        size[fa] += size[fb];
      } else {
        parent[fa] = fb;
        size[fb] += size[fa];
      }
    }
  }
};

class Solution {
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        UnionFind uf(n + 1);
        for (int i = threshold + 1; i <= n; ++i)
            for (int j = 2 * i; j <= n; j += i)
                uf.connect(i, j);
        vector<bool> ans;
        for (auto &q : queries) {
            int u = q[0], v = q[1];
            int fu = uf.find(u), fv = uf.find(v);
            ans.emplace_back(fu == fv);
        }
        return ans;
    }
};
```

:::

<Utterances />
