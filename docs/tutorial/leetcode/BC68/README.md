# Leetcode 第68场双周赛题解

## Problem A - [句子中的最多单词数](https://leetcode-cn.com/problems/maximum-number-of-words-found-in-sentences/)

### 方法一：暴力

在题目给定的条件下，统计单词数实际上就是统计空格数。

- 时间复杂度$\mathcal{O}(\sum|W|)$。其中$|W|$表示单词的长度。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def mostWordsFound(self, sentences: List[str]) -> int:
        return max(map(lambda x: x.count(' ') + 1, sentences))
```

:::


## Problem B - [从给定原材料中找到所有可以做出的菜](https://leetcode-cn.com/problems/find-all-possible-recipes-from-given-supplies/)

### 方法一：暴力

首先排除那些绝对不可能做出来的菜，也即配方中包含了既不在食谱也不在现有食材中的菜。

接下来，我们从初始状态（只有食材）开始，反复遍历所有的配方，并检查是否能做出对应的菜。这里为了加速，使用了`bitset`。

如果某一轮遍历中都没有做出新的菜，说明已经不可能做出新的菜了，终止。

- 时间复杂度$\mathcal{O}(N^3/W)$。其中$W$为字长。
- 空间复杂度$\mathcal{O}(N^3/W)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int n = recipes.size();
        
        unordered_map<string, int> mp;
        int idx = 0;
        for (auto &s : recipes)
            mp[s] = idx++;
        for (auto &s : supplies)
            mp[s] = idx++;
        
        bitset<200> bs;
        for (auto &s : supplies)
            bs.set(mp[s]);
        
        vector<bitset<200>> vi(n);
        vector<bool> can(n, true);
        for (int i = 0; i < n; ++i) {
            for (auto &s : ingredients[i]) {
                if (!mp.count(s)) {
                    can[i] = false;
                    break;
                }
                vi[i].set(mp[s]);
            }
        }
        
        bool changed = true;
        for (int i = 0; i < n; ++i) {
            changed = false;
            for (int j = 0; j < n; ++j) {
                if (!can[j] || bs[j])
                    continue;
                if ((bs | vi[j]) == bs)
                    bs.set(j), changed = true;
            }
            if (!changed)
                break;
        }
        
        vector<string> ans;
        for (int i = 0; i < n; ++i)
            if (bs[i])
                ans.push_back(recipes[i]);
        
        return ans;
    }
};
```

:::

## Problem C - [判断一个括号字符串是否有效](https://leetcode-cn.com/problems/check-if-a-parentheses-string-can-be-valid/)

### 方法一：记录可能的最大和最小平衡值

令平衡值表示某一位置处，累积的`(`数量与`)`数量的差值，则我们知道，一个有效括号字符串必须满足：

- 所有位置处的平衡值非负
- 结尾处的平衡值为零

那么，我们的解题思路就是：依次遍历每个位置，根据每个位置处的字符和上锁情况来更新当前所有可能的平衡值。

本题$N$最大$10^5$，记录所有的平衡值可能会超时。但可以注意到，任意时刻，所有可能的平衡值必然构成一个公差为$2$的等差数列，所以我们只需要记录最大和最小平衡值即可。

如果当前字符为`(`，则最大平衡值必然增加一；而最小平衡值的变化则要看是否上锁：如果上锁，则最小值也需要增加一，否则最小值可以减少一（注意如果当前最小值已经为$0$，则新的最小值只能为$1$）。

如果当前字符为`)`，则最小平衡值必须减少一；而最大平衡值的变化则要看是否上锁；如果上锁，最大值也要减少一，否则可以增加一。如果出现最小值大于最大值的情况，则说明无解。

最后，如果最小值为$0$，说明有解，否则无解。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canBeValid(string s, string locked) {
        int n = s.size();
        if (n % 2 == 1)
            return false;
        
        int lo = 0, hi = 0;
        
        for (int i = 0; i < n; ++i) {            
            if (s[i] == '(') { 
                hi++;
                if (locked[i] == '1')
                    lo++;
                else
                    lo = lo == 0 ? 1 : lo - 1;
            } else {
                lo = lo == 0 ? 1 : lo - 1;
                if (locked[i] == '1')
                    hi--;
                else
                    hi++;
                if (lo > hi)
                    return false;
            }
        }
        
        return lo == 0;
    }
};
```

:::

## Problem D - [一个区间内所有数乘积的缩写](https://leetcode-cn.com/problems/abbreviating-the-product-of-a-range/)

### 方法一：数学

首先，对于区间长度比较小的情况，可以直接计算出精确结果（如果语言支持高精度运算的话）。

在区间长度长到无法直接计算的时候，我们分三部分考虑：

- 末尾$0$的数量：经典题，统计区间内的数有多少个$2$的因子和$5$的因子即可；
- 末尾五位：去除$2$和$5$后，对所有数进行模数为$100000$的带模乘法，并记得在最后乘上没有用掉的$2$或$5$；
- 开头五位：对所有数取以$10$为底的对数并求和，保留小数部分再还原即可得到。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
from functools import reduce
from numpy import float128, log10

MOD = 100000

class Solution:
    def abbreviateProduct(self, left: int, right: int) -> str:
        if right - left + 1 <= 50:
            ans = reduce(lambda x, y: x * y, range(left, right + 1), 1)
            s = str(ans)
            t = s.rstrip('0')
            z = len(s) - len(t)
            if len(t) <= 10:
                return t + 'e' + str(z)
            else:
                return t[:5] + '...' + t[-5:] + 'e' + str(z)
        else:
            l = float(
                sum(map(lambda x: log10(float128(x)), range(left, right + 1))))
            L = str(10 ** (l - trunc(l)) * 10000)[:5]

            R = 1
            two = 0
            five = 0
            for i in range(left, right + 1):
                num = i
                while num % 2 == 0:
                    two += 1
                    num >>= 1
                while num % 5 == 0:
                    five += 1
                    num //= 5
                R = R * num % MOD

            z = min(two, five)
            R = R * pow(2, two - z, MOD) % MOD
            R = R * pow(5, five - z, MOD) % MOD
            return L + '...' + str(R).rjust(5, '0') + 'e' + str(z)
```

:::

<Utterances />
