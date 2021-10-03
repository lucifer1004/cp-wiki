# Leetcode 第261场周赛题解

## Problem A - [转换字符串的最少操作次数](https://leetcode-cn.com/problems/minimum-moves-to-convert-string/)

### 方法一：贪心

从左到右遍历，每遇到一个`X`，就将从它开始的三个字母进行替换（并不需要真的进行替换）。

> 有可能出现最后长度不足三个的情况，我们需要将前面的字母也包括进来一起进行操作。但这并不影响解法的正确性。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumMoves(string s) {
        int ans = 0;
        for (int i = 0; i < s.size(); ++i) 
            if (s[i] == 'X') {
                ans++;
                i += 2;
            }
        return ans;
    }
};
```

:::

## Problem B - [找出缺失的观测数据](https://leetcode-cn.com/problems/find-missing-observations/)

### 方法一：贪心

首先计算出$n$个数字的总和，判断是否有解。

接下来贪心生成答案：如果能放$1$，就放$1$，否则基于剩下位置全都放$6$的考虑，来计算当前位置的数字。

- 时间复杂度$\mathcal{O}(M+N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int msum = 0;
        for (int roll : rolls)
            msum += roll;
        int nsum = mean * (n + m) - msum;
        if (nsum < n || nsum > n * 6)
            return {};
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            int rmax = (n - 1 - i) * 6;
            if (nsum - 1 > rmax)
                ans[i] = nsum - rmax;
            else
                ans[i] = 1;
            nsum -= ans[i];
        }
        return ans;
    }
};
```

:::

## Problem C - [石子游戏 IX](https://leetcode-cn.com/problems/stone-game-ix/)

### 方法一：贪心

我们可以观察到以下几点：

1. 只需要考虑每个数对$3$的模，而不需要考虑数字本身。
2. Alice第一步必须选$1$或$2$。
3. 之后的操作顺序是确定的，即如果当前和值为$1$，就取$1$；否则取$2$。如果没有对应的数字，就取$0$。

> 关于何时取$0$的进一步解释：实际上，何时取$0$不会影响最终的结果。我们可以把分出胜负时的操作序列写下来，此时，我们会发现，将其中的$0$任意移动到非首位的位置上，所得到的都还是一个合法的操作序列。所以在模拟的时候，尽量取$0$或者尽量不取$0$都能得到正确结果。

在以上几点观察的基础上，我们分别模拟一下Alice第一步取$1$和取$2$的情形即可得到答案。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
    bool check(int first, vector<int> mod) {
        // Alice takes `first` first
        if (mod[first] > 0) {
            mod[first]--;
            int state = first;
            while (true) {
                if (mod[state] > 0)
                    mod[state]--, state = 3 - state;
                else if (mod[0] > 0)
                    mod[0]--;
                else
                    return true;
                
                if (mod[0] + mod[1] + mod[2] == 0)
                    return false;
                
                if (mod[state] > 0)
                    mod[state]--, state = 3 - state;
                else if (mod[0] > 0)
                    mod[0]--;
                else
                    return false;
                
                if (mod[0] + mod[1] + mod[2] == 0)
                    return false;
            }
        }
        
        return false;
    }
public:
    bool stoneGameIX(vector<int>& stones) {
        int n = stones.size();
        if (n == 1)
            return false;
        
        vector<int> mod(3);
        for (int stone : stones)
            mod[stone % 3]++;
        
        return check(1, mod) || check(2, mod);
    }
};
```

:::

## Problem D - [含特定字母的最小子序列](https://leetcode-cn.com/contest/weekly-contest-261/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/)

### 方法一：贪心

我们可以逐位来考虑。我们希望每一位都尽可能小，但同时需要满足以下条件：

1. 这一位的位置应当大于上一位的位置；
2. 这一位后面需要有足够多的字母，以使得总长度能够达到$K$；
3. 这一位后面需要有足够多的`letter`，以使得`letter`的个数能够达到`repetition`。

针对1，我们使用$26$个队列来存储$26$个字母的位置；针对3，我们预处理出每个位置后面`letter`的个数。

接下来，我们就进行逐位枚举。对于每一位，我们都枚举`a`到`z`，如果枚举到一个字母能够满足条件，就选用这个字母，同时进行相应的更新操作：

1. 更新上一位的位置；
2. 更新队列；
3. 如果这个字母恰好是`letter`，更新`repetition`。

因为题目保证了至少有`repetition`个`letter`，所以一定有解，不需要考虑无解的情况。

- 时间复杂度$\mathcal{O}(|S|+K|\sum|)$。
- 空间复杂度$\mathcal{O}(|S|+K)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        int n = s.size();
        vector<int> rem(n);
        for (int i = n - 2; i >= 0; --i)
            rem[i] = rem[i + 1] + (s[i + 1] == letter);
        
        vector<queue<int>> pos(26);
        for (int i = 0; i < n; ++i)
            pos[s[i] - 'a'].push(i);
        
        int last = -1;
        string ans;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < 26; ++j) {
                while (!pos[j].empty() && pos[j].front() < last)
                    pos[j].pop();
                int need = (j == letter - 'a') ? repetition - 1 : repetition;
                if (!pos[j].empty() && rem[pos[j].front()] >= need && k - 1 - i >= need && n - 1 - pos[j].front() >= k - 1 - i) {
                    ans.push_back('a' + j);
                    if (j == letter - 'a')
                        repetition--;
                    last = pos[j].front();
                    pos[j].pop();
                    break;
                }
            }
        }
        return ans;
    }
};
```

:::

<Utterances />
