# Leetcode 第31场双周赛题解

## Problem A - [在区间范围内统计奇数数目](https://leetcode-cn.com/problems/count-odd-numbers-in-an-interval-range/)

根据区间长度和起点的奇偶性进行讨论即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countOdds(int low, int high) {
        int delta = high - low + 1;
        return delta / 2 + (delta % 2 == 0 ? 0 : low % 2);
    }
};
```

:::

## Problem B - [和为奇数的子数组数目](https://leetcode-cn.com/problems/number-of-sub-arrays-with-odd-sum/)

记录前缀和中的奇数和偶数的数目，然后分别讨论即可。注意子数组和子串都要求是连续的。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        int odd = 0, even = 1, sum = 0;
        for (int i : arr) {
            sum += i;
            if (sum % 2 == 0) {
                ans = (ans + odd) % MOD;
                even++;
            }
            else {
                ans = (ans + even) % MOD;
                odd++;
            }
        }
        return ans;
    }
};
```

:::

## Problem C - [字符串的好分割数目](https://leetcode-cn.com/problems/number-of-good-ways-to-split-a-string/)

枚举分割点，用两个`map`分别记录左边和右边的字符种数即可。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numSplits(string s) {
        int ans = 0;
        map<char, int> l, r;
        for (char c : s)
            r[c]++;
        for (char c : s) {
            r[c]--;
            if (r[c] == 0)
                r.erase(c);
            l[c]++;
            if (r.size() == l.size())
                ans++;
        }
        return ans;
    }
};
```

:::

## Problem D - [形成目标数组的子数组最少增加次数](https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/)

贪心地累加相邻元素大于$0$的差值即可，理由在于，如果当前元素小于前一元素，那么总可以在操作前一元素时顺带对其进行操作；而如果当前元素大于前一元素，则必须对其进行额外的操作。

严格的证明参见[官方题解](https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/solution/xing-cheng-mu-biao-shu-zu-de-zi-shu-zu-zui-shao-ze/)。

[CF1392C: Omkar and Waterslide](https://codeforces.com/contest/1392/problem/C)与本题类似。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int ans = 0, last = 0;
        for (int i : target) {
            if (i > last)
                ans += i - last;
            last = i;
        }
        return ans;
    }
};
```

:::

<Utterances />
