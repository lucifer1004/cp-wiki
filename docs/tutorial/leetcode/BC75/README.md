# Leetcode 第75场双周赛题解

## Problem A - [转换数字的最少位翻转次数](https://leetcode.cn/problems/minimum-bit-flips-to-convert-number/)

### 方法一：位运算

异或运算即可找出所有需要翻转的位。

- 时间复杂度 $\mathcal{O}(1)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minBitFlips(int start, int goal) {
        return __builtin_popcount(start ^ goal);
    }
};
```

:::

## Problem B - [数组的三角和](https://leetcode.cn/problems/find-triangular-sum-of-an-array/)

### 方法一：模拟

按题意模拟即可。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Rust）

```rust
impl Solution {
    pub fn triangular_sum(mut nums: Vec<i32>) -> i32 {
        while nums.len() > 1 {
            let n = nums.len();
            let mut new_nums = vec![];
            for i in 0..n - 1 {
                new_nums.push((nums[i] + nums[i + 1]) % 10);
            }
            nums = new_nums;
        }
        return nums[0];
    }
}
```

:::

### 方法二：组合数

我们可以发现，其实第 $i$ 个数被累加的次数就是 ${n-1}\choose i$。但是这里要对 10 取模而 10 不是质数。我们可以对 2 和 5 分别算一次，然后将结果用中国剩余定理进行合并。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

参考代码略。

## Problem C - [选择建筑的方案数](https://leetcode.cn/contest/biweekly-contest-75/problems/number-of-ways-to-select-buildings/)

### 方法一：动态规划

最后合法的串只有"010"和"101"，那么我们记录"0"、"1"、"01"、"10"、"010"和"101"的个数并按照顺序更新即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    ll numberOfWays(string s) {
        int n = s.size();
        ll ans = 0;
        ll z = 0, o = 0, zo = 0, oz = 0, zoz = 0, ozo = 0;
        for (char c : s) {
            int i = c - '0';
            if (i == 0) {
                zoz += zo;
                oz += o;
                z++;
            } else {
                ozo += oz;
                zo += z;
                o++;
            }
        }
        return zoz + ozo;
    }
};
```

:::

## Problem D - [构造字符串的总得分和](https://leetcode.cn/problems/sum-of-scores-of-built-strings/)

### 方法一：后缀数组

题目中每次在前面添加一个字母得到的这一系列字符串其实就是原串的所有后缀，又要求最长公共前缀，自然想到用后缀数组解题。

求得后缀数组和最长公共前缀数组后，从原串对应的位置向两侧扩展累加得分即可。记得加上原串自己的分数。

复杂度：

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
#include <atcoder/string>

using ll = long long;

class Solution {
  public:
    long long sumScores(string s) {
        int n = s.size();
        auto sa = atcoder::suffix_array(s);
        auto lcp = atcoder::lcp_array(s, sa);
        int i = 0;
        while (sa[i] != 0)
            i++;
        
        ll ans = n;
        int l = n;
        int j = i - 1;
        while (j >= 0) {
            l = min(l, lcp[j]);
            ans += l;
            j--;
        }
        
        j = i;
        l = n;
        while (j < n - 1) {
            l = min(l, lcp[j]);
            ans += l;
            j++;
        }
        
        return ans;
    }
};
```

:::

### 方法二 Z-算法

其实这题是 Z-算法的裸题。本身 Z-算法求的就是每一个后缀跟原串的最长前缀。求出结果后直接求和就行，比后缀数组更加简单。

复杂度：

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
#include <atcoder/string>

using ll = long long;

class Solution {
  public:
    long long sumScores(string s) {
        auto z = atcoder::z_algorithm(s);
        ll ans = 0;
        for (int zi : z)
            ans += zi;
        return ans;
    }
};
```

:::

<Utterances />
