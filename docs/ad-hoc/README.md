---
sidebarDepth: 3
---

# Ad Hoc问题

Ad Hoc指一道题目没有现成的算法可用，需要一个专门的解决方法。

## 练习题

### [LC330 - 按要求补齐数组](https://leetcode.cn/problems/patching-array/)

### [LC1190 - 反转每对括号间的子串](https://leetcode.cn/problems/reverse-substrings-between-each-pair-of-parentheses/)

::: details 提示一

找出每对相互匹配的括号。

:::

::: details 提示二

从左向右遍历，每次遇到括号，就跳转到与其匹配的括号处，然后改变方向。

:::

::: details 参考代码（C++）

```cpp

class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();
        vector<int> pair(n, -1);
        stack<int> st;
        int p = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(')
                p++, st.push(i);
            if (s[i] == ')') {
                int j = st.top();
                pair[i] = j;
                pair[j] = i;
                st.pop();
            }
        }
        int c = n - 2 * p;
        string ans;
        int pos = 0;
        bool right = true;
        while (ans.size() < c) {
            if (s[pos] == '(' || s[pos] == ')') {
                pos = pair[pos];
                right = !right;
            } else {
                ans.push_back(s[pos]);
            }
            if (right)
                pos++;
            else
                pos--;
        }
        return ans;
    }
};

```

:::

### [BS679 - Delete from the ends and Reinsert to Target](https://binarysearch.com/problems/Delete-from-the-ends-and-Reinsert-to-Target)

::: details 提示一

考虑逆向过程：每次将中间的一个字符取出放在开头或结尾。

:::

::: details 提示二

原问题等价于求出$S$中是$T$的子序列的最长子串的长度。

:::

::: details 参考代码（C++）

```cpp
#include "solution.hpp"
using namespace std;

class Solution {
    public:
    int solve(string s, string t) {
        int n = s.size();
        vector<vector<int>> nxt(n + 1, vector<int>(26, -1));
        vector<int> c(26, -1);
        for (int i = n - 1; i >= 0; --i) {
            nxt[i + 1] = c;
            c[t[i] - 'a'] = i + 1;
        }
        nxt[0] = c;
        int hi = 0;
        for (int i = 0; i < n; ++i) {
            int p = 0, now = 0;
            while (i + p < n && nxt[now][s[i + p] - 'a'] != -1) {
                now = nxt[now][s[i + p] - 'a'];
                p++;
            }
            hi = max(hi, p);
        }
        return n - hi;
    }
};
```

:::

### [Kattis - Juggling Patterns](https://open.kattis.com/problems/jugglingpatterns)

::: details 提示

参考维基百科的[这一节](https://en.wikipedia.org/wiki/Siteswap#Validity)。

:::

::: details 参考代码（Python 3）

<<<@/docs/ad-hoc/src/Kattis-jugglingpatterns.py

:::

<Utterances />
