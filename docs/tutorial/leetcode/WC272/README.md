# Leetcode 第272场周赛题解

## Problem A - [找出数组中的第一个回文字符串](https://leetcode.cn/problems/find-first-palindromic-string-in-the-array/)

### 方法一：模拟

按题意模拟即可。

- 时间复杂度$\mathcal{O}(\sum|W|)$。
- 空间复杂度$\mathcal{O}(\sum|W|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def firstPalindrome(self, words: List[str]) -> str:
        return ([word for word in words if word == word[::-1]] + [""])[0]
```

:::

## Problem B - [向字符串添加空格](https://leetcode.cn/problems/adding-spaces-to-a-string/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def addSpaces(self, s: str, spaces: List[int]) -> str:
        t = ' '.join(s[i:j] for i, j in zip(spaces[:-1], spaces[1:]))
        return s[:spaces[0]] + (' ' if t != '' else '') + t + ' ' + s[spaces[-1]:]
```

:::

## Problem C - [股票平滑下跌阶段的数目](https://leetcode.cn/problems/number-of-smooth-descent-periods-of-a-stock/)

### 方法一：动态规划

最简单的动态规划：由以前一天为结尾的平滑下跌阶段的数目，可以求得以这一天为结尾的平滑下跌阶段的数目。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        long long ans = 0;
        int acc = 1, last = 0;
        for (int price : prices) {
            if (price == last - 1)
                ans += ++acc;
            else
                ans += acc = 1;
            last = price;
        }
        
        return ans;
    }
};
```

:::

## Problem D - [使数组 K 递增的最少操作次数](https://leetcode.cn/problems/minimum-operations-to-make-the-array-k-increasing/)

### 方法一：最长不下降子序列

我们实际上需要让原数组的$[0,K,2K,\dots]$，$[1,K+1,2K+1,\dots]$，$\dots$，$[K-1,2K-1,3K-1,\dots]$这几个子序列分别变为递增。

对于某一个子序列，要求让它变为递增的最少次数，实际上就是要求它的最长不下降子序列，之后对不在这一最长不下降子序列中的元素进行修改操作即可。

- 时间复杂度$\mathcal{O}(N\log N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
    int increasing(vector<int> &a) {
        int n = a.size();
        vector<int> LIS;
        for (int ai : a) {
            auto it = upper_bound(LIS.begin(), LIS.end(), ai);
            if (it == LIS.end())
                LIS.push_back(ai);
            else
                *it = ai;
        }
        return n - LIS.size();
    }
    
public:
    int kIncreasing(vector<int>& arr, int k) {
        int ans = 0;
        for (int i = 0; i < k; ++i) {
            vector<int> v;
            for (int j = i; j < arr.size(); j += k)
                v.push_back(arr[j]);
            ans += increasing(v);
        }
        return ans;
    }
};
```

:::

<Utterances />
