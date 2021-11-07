# Leetcode 第266场周赛题解

## Problem A - [统计字符串中的元音子字符串](https://leetcode-cn.com/problems/count-vowel-substrings-of-a-string/)

### 方法一：暴力穷举

枚举所有子字符串，并判断是否符合条件。

- 时间复杂度$\mathcal{O}(|S|^3)$。
- 空间复杂度$\mathcal{O}(|S|^3)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countVowelSubstrings(self, word: str) -> int:
        n = len(word)
        ans = 0
        for i in range(n):
            for j in range(i + 4, n):
                sub = word[i:j + 1]
                good = True
                s = set(sub)
                if len(s) == 5:
                    for ch in s:
                        if ch not in 'aeiou':
                            good = False
                            break
                    if good:
                        ans += 1
        return ans
```

:::

### 方法二：双指针

预处理出每个字母后面第一个辅音字母的位置，然后使用双指针求解。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countVowelSubstrings(self, word: str) -> int:
        n = len(word)
        next_consonant = [n] * n
        for i in range(n - 2, -1, -1):
            if word[i + 1] not in 'aeiou':
                next_consonant[i] = i + 1
            else:
                next_consonant[i] = next_consonant[i + 1]
        
        ans = 0
        l = 0
        r = -1
        cnt = collections.Counter()
        while l < n:
            r = max(r, l - 1)
            
            if word[l] not in 'aeiou':
                l += 1
                cnt = collections.Counter()
                continue
        
            jump = False
        
            while len(cnt) < 5 and r + 1 < n:
                r += 1
                if word[r] in 'aeiou':
                    cnt[word[r]] += 1
                else:
                    l = r + 1
                    jump = True
                    cnt = collections.Counter()
                    break
                    
            if jump:
                continue
                    
            if len(cnt) == 5:
                ans += next_consonant[r] - r
            
            if l < n:
                cnt[word[l]] -= 1
                if cnt[word[l]] == 0:
                    del cnt[word[l]]

            l += 1
        return ans
```

:::

## Problem B - [所有子字符串中的元音](https://leetcode-cn.com/problems/vowels-of-all-substrings/)

### 方法一：遍历

我们考虑每一个元音字母被计数的次数。对于第$i$位（$i$从$0$开始）的字母，它向前扩展有$i+1$种可能，向后扩展有$n-i$种可能，所以一共被计数$(i+1)(n-i)$次。对所有为元音的$i$求和即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countVowels(self, word: str) -> int:        
        n = len(word)
        return sum((i + 1) * (n - i) for i, ch in enumerate(word) if ch in 'aeiou')
```

:::

## Problem C - [分配给商店的最多商品的最小值](https://leetcode-cn.com/problems/minimized-maximum-of-products-distributed-to-any-store/)

### 方法一：二分答案

我们考虑这样一个问题：

假设一个商店最多分配$k$件商品，至少需要多少个商店才能分配完所有的商品？

显然这一问题可以贪心求解。

另一方面，我们注意到上面的问题具有单调性，也即$k$越大，需要的商店就越少。

因此我们可以二分求得需要的商店数目不超过$N$的最大的$k$，即为本题答案。

- 时间复杂度$\mathcal{O}(N\log Q_{\max})$，其中$Q_{\max}$表示数目最多的商品的件数。
- 空间复杂度$\mathcal{O}(C)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        int m = quantities.size();
        int lo = 1, hi = *max_element(quantities.begin(), quantities.end());
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            long long need = 0;
            for (int q : quantities)
                need += (q - 1) / mid + 1;
            if (need > n)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return lo;
    }
};
```

:::

## Problem D - [最大化一张图中的路径价值](https://leetcode-cn.com/problems/maximum-path-quality-of-a-graph/)

### 方法一：回溯

本题看起来非常复杂，但注意到两个关键条件：

1. 节点的度数不超过$4$
2. 边权不小于$10$，同时允许的最长时间不超过$100$

在这两个条件的约束下，可以知道我们穷举所有可能的路径，所需要讨论的情况数也不会超过$4^{10}=2^{20}\simeq10^6$。因此，我们用回溯的方法即可解决本题。

- 时间复杂度$\mathcal{O}(D^{T/t})$。其中$D\le4$为最大度数，$t\ge10$为最小边权，$T\le100$为最长的允许时间。
- 空间复杂度$\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
class Solution {
    int max_time, best_value, current_value, current_time;
    vector<int> vis, values;
    vector<vector<pair<int, int>>> adj;
    
    void dfs(int u) {
        if (!vis[u])
            current_value += values[u];
        
        vis[u]++;
        if (u == 0)
            best_value = max(best_value, current_value);
        
        for (auto [v, time] : adj[u]) {
            if (current_time + time <= max_time) {
                current_time += time;
                dfs(v);
                current_time -= time;
            }
        }
        
        vis[u]--;
        if (!vis[u]) 
            current_value -= values[u];
    }
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int max_time) {
        this->max_time = max_time;
        this->values = values;        
        int n = values.size();
        adj = vector<vector<pair<int, int>>>(n);
        vis = vector<int>(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], t = e[2];
            adj[u].emplace_back(v, t);
            adj[v].emplace_back(u, t);
        }
        
        best_value = 0, current_time = 0, current_value = 0;
        dfs(0);
        return best_value;
    }
};
```

:::

<Utterances />
