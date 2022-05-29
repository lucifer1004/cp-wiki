# Leetcode 第55场双周赛题解

## Problem A - [删除一个元素使数组严格递增](https://leetcode.cn/problems/remove-one-element-to-make-the-array-strictly-increasing/)

### 方法一：暴力

本题数据范围较小，因此我们可以暴力枚举删除的元素，然后检查剩余的数组是否严格递增。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def canBeIncreasing(self, nums: List[int]) -> bool:
        n = len(nums)
        for i in range(n):
            sub = nums[:i] + nums[i + 1:]
            good = True
            for j in range(len(sub) - 1):
                if sub[j + 1] <= sub[j]:
                    good = False
                    break
            if good:
                return True
        return False
```

:::

### 方法二：双指针

最终剩下的数组必然由原数组的一个前缀和一个后缀组合而成，因此我们可以采用双指针的方法：

- 左指针找出最长的严格递增的前缀；
- 右指针找出最长的严格递增的后缀。

然后，我们判断这个前缀和这个后缀是否能按照题目要求进行组合。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2)
            return true;
        
        int p = 0;
        while (p + 1 < n && nums[p + 1] > nums[p])
            p++;
        if (p == n - 1)
            return true;
        
        int q = n - 1;
        while (q >= 1 && nums[q - 1] < nums[q])
            q--;
        
        if (p + 2 == q && nums[p] < nums[q])
            return true;
        
        if (p + 1 == q) {
            if (p == 0 || (p >= 1 && nums[p - 1] < nums[q]))
                return true;
            if (q == n - 1 || (q + 1 < n && nums[p] < nums[q + 1]))
                return true;
        }
        
        return false;
    }
};
```

:::


## Problem B - [删除一个字符串中所有出现的给定子字符串](https://leetcode.cn/problems/remove-all-occurrences-of-a-substring/)

### 方法一：模拟

本题数据范围较小，我们可以直接进行模拟，将原字符串中的字符逐个加入，每次加入一个字符，就判断当前结果串的尾部是否与给定字符串相同，若是，则将其删去。

- 时间复杂度为$\mathcal{O}(|S||T|)$。
- 空间复杂度$\mathcal{O}(|S|)$。


::: details 参考代码（C++）

```cpp
class Solution {
public:
    string removeOccurrences(string s, string part) {
        string ans;
        for (char c : s) {
            ans.push_back(c);
            if (ans.size() >= part.size() && ans.substr(ans.size() - part.size(), part.size()) == part)
                ans = ans.substr(0, ans.size() - part.size());
        }
        return ans;
    }
};
```

:::

### 方法二：KMP算法

我们可以使用KMP算法来实现线性复杂度。

首先预处理得到给定字符串对应的$\pi$数组（表示以当前位置为结尾，且与字符串的前缀相同的最长字符串的长度），然后逐个处理原始字符串中的字符。每当匹配成功时，回退相应的长度即可。

- 时间复杂度为$\mathcal{O}(|S|+|T|)$。
- 空间复杂度$\mathcal{O}(|S|+|T|)$。


::: details 参考代码（Python 3）

```python
class Solution:
    def removeOccurrences(self, s: str, part: str) -> str:
        m = len(part)
        pi = [0] * m
        for i in range(1, m):
            j = pi[i - 1]
            while j != 0 and part[i] != part[j]:
                j = pi[j - 1]
            pi[i] = j + 1 if part[i] == part[j] else 0
        
        ans = []
        dp = [0]
        for c in s:
            ans.append(c)
            j = dp[-1]
            while j != 0 and c != part[j]:
                j = pi[j - 1]
            dp.append(j + 1 if c == part[j] else 0)
            if dp[-1] == m:
                dp = dp[:-m]
                ans = ans[:-m]
        
        return ''.join(ans)
```

:::

## Problem C - [最大子序列交替和](https://leetcode.cn/problems/maximum-alternating-subsequence-sum/)

### 方法一：动态规划

我们维护两个值：当前长度为偶数的子序列的最大和、当前长度为奇数的子序列的最大和。

遍历所有元素，对于每个元素，我们都有选取/不选取这两种情况，从而可以更新两个最大值。

最后的结果就是长度为奇数的子序列的最大和（想想为什么不可能是长度为偶数的子序列的最大和？）。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        odd = int(-1e10)
        even = 0
        for num in nums:
            odd, even = max(odd, even + num), max(even, odd - num)
        return odd
```

:::

## Problem D - [设计电影租借系统](https://leetcode.cn/problems/design-movie-rental-system/)

### 方法一：数据结构+模拟

按照题目要求，选取合适的数据结构进行模拟即可。

- 使用一个键值为`set`的哈希表来存储当前拥有每部电影的店铺。
- 使用一个`set`来存储当前借出的所有电影。
- 使用一个`map`来存储每个店铺中每部电影的租借价格。

对于查询类操作，因为最多查询$5$个元素，所以可以先将这些元素移除，再重新加入。

最后各操作的时间复杂度为：

- `search`：$\mathcal{O}(\log N)$
- `rent`：$\mathcal{O}(\log N+\log M)$
- `drop`：$\mathcal{O}(\log N+\log M)$
- `report`：$\mathcal{O}(\log M)$

其中$N$为店铺的数目，$M$为电影的数目。

::: details 参考代码（C++）

```cpp
class MovieRentingSystem {
    int n;
    unordered_map<int, set<pair<int, int>>> has;
    set<tuple<int, int, int>> borrowed;
    map<pair<int, int>, int> query;
    
public:
    MovieRentingSystem(int n, vector<vector<int>>& entries): n(n) {
        for (auto &v : entries) {
            int shop = v[0], movie = v[1], price = v[2];
            query[{shop, movie}] = price;
            has[movie].emplace(price, shop);
        }
    }
    
    vector<int> search(int movie) {
        vector<int> ans;
        for (int i = 0; i < 5 && !has[movie].empty(); ++i) {
            ans.emplace_back(has[movie].begin()->second);
            has[movie].erase(has[movie].begin());
        }
        
        for (int shop : ans)
            has[movie].emplace(query[{shop, movie}], shop);
        
        return ans;
    }
    
    void rent(int shop, int movie) {
        int price = query[{shop, movie}];
        has[movie].erase({price, shop});
        borrowed.emplace(price, shop, movie);
    }
    
    void drop(int shop, int movie) {
        int price = query[{shop, movie}];
        has[movie].emplace(price, shop);
        borrowed.erase({price, shop, movie});
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> ans;
        
        for (int i = 0; i < 5 && !borrowed.empty(); ++i) {
            auto [price, shop, movie] = *borrowed.begin();
            ans.push_back({shop, movie});
            borrowed.erase(borrowed.begin());
        }
        
        for (auto &v : ans) {
            int shop = v[0], movie = v[1];
            int price = query[{shop, movie}];
            borrowed.emplace(price, shop, movie);
        }
        
        return ans;
    }
};

```

:::

<Utterances />
