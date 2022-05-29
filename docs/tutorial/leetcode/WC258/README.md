# Leetcode 第258场周赛题解

## Problem A - [反转单词前缀](https://leetcode.cn/problems/reverse-prefix-of-word/)

### 方法一：模拟

直接模拟即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def reversePrefix(self, word: str, ch: str) -> str:
        i = word.find(ch)
        return word if i == -1 else word[:i + 1][::-1] + word[i + 1:]
```

:::

## Problem B - [可互换矩形的组数](https://leetcode.cn/problems/number-of-pairs-of-interchangeable-rectangles/)

### 方法一：哈希表

统计每一个类型的数目即可。这里为了方便，使用了Python中的`Fraction`。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
from fractions import Fraction
from collections import Counter

class Solution:
    def interchangeableRectangles(self, rectangles: List[List[int]]) -> int:
        cnt = Counter()
        for w, h in rectangles:
            cnt[Fraction(w, h)] += 1
        ans = 0
        for value in cnt.values():
            ans += value * (value - 1) // 2
        return ans
```

:::

## Problem C - [两个回文子序列长度的最大乘积](https://leetcode.cn/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/)

### 方法一：状态压缩动态规划

注意到$N\le12$，考虑状压。

首先枚举出所有的回文子序列，然后对每个回文子序列枚举子集即可。

- 时间复杂度$\mathcal{O}(N\cdot2^N+3^N)$。
- 空间复杂度$\mathcal{O}(2^N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxProduct(string s) {
        int n = s.size();
        vector<bool> palin(1 << n, true);
        for (int i = 1; i < (1 << n); ++i) {
            int l = 0, r = n - 1;
            while (l < r) {
                while (l < n && !(i & (1 << l)))
                    l++;
                while (r > 0 && !(i & (1 << r)))
                    r--;
                if (l < r && s[l] != s[r]) {
                    palin[i] = false;
                    break;
                }
                l++, r--;
            }
        }
        
        int ans = 0, msk = (1 << n) - 1;
        for (int i = 1; i < (1 << n); ++i) {
            if (!palin[i])
                continue;
            int len1 = __builtin_popcount(i);
            int rem = msk ^ i;
            for (int j = rem; j; j = (j - 1) & rem) {
                if (palin[j])
                    ans = max(ans, len1 * __builtin_popcount(j));
            }
        }
        
        return ans;
    }
};
```

:::

## Problem D - [每棵子树内缺失的最小基因值](https://leetcode.cn/problems/smallest-missing-genetic-value-in-each-subtree/)

### 方法一：DFS+小大合并

朴素的想法是在DFS过程中，将每个子树拥有的数的集合合并，得到当前节点拥有的数。但考虑一条长链的情形，我们将面临时间和空间双爆的危险。

优化的方法其实很简单，就是小大合并（Small to large）。也即在合并数组、集合等时，总是将元素数较少的那个数组/集合中的元素合并到元素数较多的那个数组/集合中，这样就可以保证合并的总复杂度为$\mathcal{O}(N\log N)$。

另一个优化的点是，在搜索MEX时，只需要从所有子树的MEX的最大值开始搜索即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
    int n;
    vector<int> nums, mex;
    vector<vector<int>> adj;
    vector<unordered_set<int>> mp;
    
    void dfs(int u, int p) {
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                mex[u] = max(mex[u], mex[v]);
                if (mp[v].size() > mp[u].size())
                    swap(mp[u], mp[v]); // 需要注意的是，这样操作后，对于子树中的点，`mp[v]`就不一定和`v`对应了。但因为它们之后不会再被用到，所以也没有影响。
                for (int i : mp[v])
                    mp[u].emplace(i);
            }
        }
        mp[u].emplace(nums[u]);
        while (mp[u].count(mex[u]))
            mex[u]++;
    }
public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        n = parents.size();
        this->nums = nums;
        mex = vector<int>(n, 1);
        adj = vector<vector<int>>(n);
        for (int i = 1; i < n; ++i)
            adj[parents[i]].emplace_back(i);
        mp = vector<unordered_set<int>>(n);
        dfs(0, -1);
        return mex;
    }
};
```

:::

> [这里](/basic/small-to-large/)有一些小大合并的练习题。

<Utterances />
