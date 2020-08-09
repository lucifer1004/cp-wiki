# Leetcode 第32场双周赛题解

## Problem A - [第k个缺失的正整数](https://leetcode-cn.com/problems/kth-missing-positive-number/)

暴力枚举。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        vector<bool> c(2001);
        for (int i : arr)
            c[i] = true;
        int v = 0, i = 0;
        while (v < k) {
            i++;
            if (!c[i])
                v++;
        }
        return i;
    }
};
```

:::

## Problem B - [K次操作转变字符串](https://leetcode-cn.com/problems/can-convert-string-in-k-moves/)

对于需要操作1次的位置，需要在第1，27……次进行操作。
对于需要操作2次的位置，需要在第2，28……次进行操作。
以此类推，要求所需的总次数，只需要计算每一种情况下所需的次数然后求最大值即可。

需要注意的是，题目没有说s和t长度相等，需要先判断一下。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        if (s.size() != t.size())
            return false;
        vector<int> cnt(26);
        for (int i = 0; i < s.size(); ++i) {
            int delta = (t[i] - s[i] + 26) % 26;
            cnt[delta]++;
        }
        int hi = 0;
        for (int i = 1; i < 26; ++i)
            hi = max(hi, (cnt[i] - 1) * 26 + i);
        return hi <= k;
    }
};
```

:::

## Problem C - [平衡括号字符串的最少插入次数](https://leetcode-cn.com/problems/minimum-insertions-to-balance-a-parentheses-string/)

稍作改动的经典题——把`)`换成了`))`。首先把所有连续奇数个的`)`都补齐到偶数个，然后再把所有连续`)`折半，之后就是经典原题了。

计算当前的嵌套深度，如果深度小于0，则添加`(`将其补至0。字符串全部扫描完后，如果深度不为0，还需要相应地添加`))`。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int minInsertions(string s) {
        vector<pair<char, int>> v;
        char l = '$';
        int cnt = 0;
        s += "#";
        for (char c : s) {
            if (c == l)
                cnt++;
            else {
                if (cnt > 0)
                    v.emplace_back(l, cnt);
                cnt = 1;
                l = c;
            }
        }
        int ans = 0, bal = 0;
        for (auto p : v) {
            char c = p.first;
            int t = p.second;
            if (c == ')' && t % 2 == 1) {
                ans++;
                t++;
            }
            if (c == '(')
                bal += t;
            else
                bal -= t / 2;
            if (bal < 0) {
                ans -= bal;
                bal = 0;
            }
        }
        ans += bal * 2;
        return ans;
    }
};
```

:::

## Problem D - [找出最长的超赞子字符串](https://leetcode-cn.com/problems/find-longest-awesome-substring/)

要求子串能够重排成回文串，所有字符的个数中至多有一个奇数。因为只包含0~9，所以可以用一个10位二进制数表示当前每个字符的奇偶状态。在这种表示方法下，超赞字符串对应的状态只能为：

- 0000000000
- 0000000001
- ……
- 1000000000

这11种状态中的一种。

用一个数组记录每种状态最早出现的位置，然后在遍历过程中，针对每个位置处的状态，看看前缀中是否存在与其异或后结果为好状态的状态。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int longestAwesome(string s) {
        vector<int> first(1 << 10, -1);
        vector<int> good = {0};
        for (int i = 0; i < 10; ++i)
            good.emplace_back(1 << i);
        first[0] = 0;
        int n = s.size(), state = 0;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int c = s[i - 1] - '0';
            state ^= (1 << c);
            if (first[state] == -1)
                first[state] = i;
            for (int g : good) {
                int need = g ^ state;
                if (first[need] != -1)
                    ans = max(ans, i - first[need]);
            }
        }
        return ans;
    }
};
```

:::
