# Leetcode 第205场周赛题解

## Problem A - [替换所有的问号](https://leetcode-cn.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/)

第一遍扫描把问号位置记下来，同时先暂时设成`a`。第二遍扫描检查合法性并修正。

时间复杂度$O(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string modifyString(string s) {
        int n = s.size();
        vector<int> v;
        for (int i = 0; i < n; ++i)
            if (s[i] == '?') {
                v.emplace_back(i);
                s[i] = 'a';
            }
        auto check = [&](int i) {
            if (i > 0 && s[i] == s[i - 1])
                return false;
            if (i < n - 1 && s[i] == s[i + 1])
                return false;
            return true;
        };
        for (int i : v) {
            if (!check(i)) {
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    s[i] = ch;
                    if (check(i))
                        break;
                }
            }
        }
        return s;
    }
};
```

:::

## Problem B - [数的平方等于两数乘积的方法数](https://leetcode-cn.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/)

用两个`map`记录平方，然后枚举乘积。

时间复杂度$O(N^2)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        map<ll, int> sq1, sq2;
        int n1 = nums1.size(), n2 = nums2.size();
        for (int num : nums1) 
            sq1[(ll)num * num]++;
        for (int num : nums2)
            sq2[(ll)num * num]++;
        ll ans = 0;
        for (int i = 0; i < n1; ++i)
            for (int j = i + 1; j < n1; ++j)
                ans += sq2[(ll)nums1[i] * nums1[j]];
        for (int i = 0; i < n2; ++i)
            for (int j = i + 1; j < n2; ++j)
                ans += sq1[(ll)nums2[i] * nums2[j]];
        return ans;
    }
};
```

:::

## Problem C - [避免重复字母的最小删除成本](https://leetcode-cn.com/problems/minimum-deletion-cost-to-avoid-repeating-letters/)

非常清晰的动态规划。用$dp[i][j]$表示处理到第$i$位，结尾为$j$的最小成本。显然有两种转移，一是保留当前字母，但要求上一位与其不同；二是删除当前字母，结尾字母不变，代价增加。

因为$dp[i+1]$只与$dp[i]$有关，所以可以用滚动数组优化。

时间复杂度$O(CN)$，其中$C$为字母表的大小，本题中为$26$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n = s.size();
        vector<int> dp(26);
        for (int i = 1; i <= n; ++i) {
            vector<int> ndp(26, INF);
            int c = s[i - 1] - 'a';
            for (int j = 0; j < 26; ++j) {
                ndp[j] = min(ndp[j], dp[j] + cost[i - 1]);
                if (j != c)
                    ndp[c] = min(ndp[c], dp[j]);
            }
            dp = move(ndp);
        }
        return *min_element(dp.begin(), dp.end());
    }
};
```

:::

## Problem D - [保证图可完全遍历](https://leetcode-cn.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/)

给两个人分别准备一个并查集。首先使用公共边，如果只用公共边无法连通，再分别使用各自独有的边。

时间复杂度$O((V+E)\alpha(V))$。

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
    a--, b--;
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

  int components() {
    vector<bool> is_root(n);
    for (int i = 0; i < n; ++i)
      is_root[find(i)] = true;
    int ans = 0;
    for (int i = 0; i < n; ++i)
      ans += is_root[i];
    return ans;
  }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        UnionFind ufa(n), ufb(n);
        for (auto v : edges) {
            if (v[0] == 3) {
                ufa.connect(v[1], v[2]);
                ufb.connect(v[1], v[2]);
            }
        }
        int c = ufa.components();
        for (auto v : edges) {
            if (v[0] == 1) 
                ufa.connect(v[1], v[2]);
        }
        if (ufa.components() != 1)
            return -1;
        for (auto v : edges) {
            if (v[0] == 2)
                ufb.connect(v[1], v[2]);
        }
        if (ufb.components() != 1)
            return -1;
        return m - (n - c) - (c - 1) * 2;
    }
};
```

:::

<Utterances />
