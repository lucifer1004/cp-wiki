# Leetcode 第303场周赛题解

## Problem A - [第一个出现两次的字母](https://leetcode.cn/problems/first-letter-to-appear-twice/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(\min(|S|,|\Sigma|))$。
- 空间复杂度 $\mathcal{O}(\min(|S|,|\Sigma|))$。

::: details 参考代码（Python 3）

```python
class Solution:
    def repeatedCharacter(self, s: str) -> str:
        cnt = collections.Counter()
        for ch in s:
            cnt[ch] += 1
            if cnt[ch] == 2:
                return ch
        return ''
```

:::

## Problem B - [相等行列对](https://leetcode.cn/problems/equal-row-and-column-pairs/)

### 方法一：暴力

- 时间复杂度 $\mathcal{O}(N^2)$。
- 空间复杂度 $\mathcal{O}(N^2)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def equalPairs(self, grid: List[List[int]]) -> int:
        n = len(grid)
        rows = collections.Counter()
        cols = collections.Counter()
        for i in range(n):
            row = tuple(grid[i])
            col = tuple([grid[j][i] for j in range(n)])
            rows[row] += 1
            cols[col] += 1
        ans = 0
        for row in rows:
            ans += rows[row] * cols[row]
        return ans
```

:::

## Problem C - [设计食物评分系统](https://leetcode.cn/problems/design-a-food-rating-system/)

### 方法一：哈希表+平衡树

- 时间复杂度：修改操作 $\mathcal{O}(\log N)$，查询操作 $\mathcal{O}(1)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
class FoodRatings {
    unordered_map<string, set<pair<int, string>>> r;
    unordered_map<string, int> f;
    unordered_map<string, string> c;
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; ++i) {
            f[foods[i]] = ratings[i];
            c[foods[i]] = cuisines[i];
            r[cuisines[i]].emplace(-ratings[i], foods[i]);
        }
    }
    
    void changeRating(string food, int newRating) {
        r[c[food]].erase(make_pair(-f[food], food));
        f[food] = newRating;
        r[c[food]].emplace(-newRating, food);
    }
    
    string highestRated(string cuisine) {
        return r[cuisine].begin()->second;
    }
};
```

:::

## Problem D - [优质数对的数目](https://leetcode.cn/problems/number-of-excellent-pairs/)

### 方法一：按二进制表示中 1 的个数分组统计 + 前缀和

- 时间复杂度 $\mathcal{O}(N)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
const int K = 30;

class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        int n = nums.size();
        vector<unordered_set<int>> s(K + 1);
        vector<int> fcnt(K + 1);
        for (int num : nums)
            s[__builtin_popcount(num)].insert(num);
        for (int i = K - 1; i >= 0; --i)
            fcnt[i] = (int)s[i].size() + fcnt[i + 1];
        
        long long ans = 0;
        for (int i = 0; i <= K; ++i) {
            int req = min(max(0, k - i), K);
            ans += 1LL * (int)s[i].size() * fcnt[req];
        }
        
        return ans;
    }
};
```

<Utterances />
