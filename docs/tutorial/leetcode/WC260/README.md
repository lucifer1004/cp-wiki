# Leetcode 第260场周赛题解

## Problem A - [增量元素之间的最大差值](https://leetcode.cn/problems/maximum-difference-between-increasing-elements/)

### 方法一：前缀和

同时维护答案和前缀最小值即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int ans = -1, lo = INT_MAX;
        for (int num : nums) {
            if (num > lo)
                ans = max(ans, num - lo);
            lo = min(lo, num);
        }
        return ans;
    }
};
```

:::

## Problem B - [网格游戏](https://leetcode.cn/problems/grid-game/)

### 方法一：前缀和

注意到网格只有两行，所以第一个机器人需要选择的实际上就是从哪一列向下。在它确定了向下的那一列之后，第二个机器人要么只能拿到第二行开始部分的分数，要么只能拿到第一行结尾部分的分数。

因此我们枚举第一个机器人向下的列即可，过程中需要维护第二行的前缀和和第一行的后缀和。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int n = grid[0].size();
        long long left = 0, right = 0;
        for (int i = 1; i < n; ++i)
            right += grid[0][i];
        long long ans = right;
        for (int i = 1; i < n; ++i) {
            left += grid[1][i - 1], right -= grid[0][i];
            ans = min(ans, max(left, right));
        }
        return ans;
    }
};
```

:::

## Problem C - [判断单词是否能放入填字游戏内](https://leetcode.cn/problems/check-if-word-can-be-placed-in-crossword/)

### 方法一：动态规划预处理+枚举+旋转

我们先考虑只允许从左向右放置的情况。设单词的长度为$K$。

单词不能跨行，所以逐行进行考虑。对于每一行，我们枚举所有可能的起点。那么这里什么样的格子是可能的起点呢？它需要满足两个条件：

- 左侧为边界或障碍
- 从它开始连续$K$个格子非障碍，再下一个格子为边界或障碍

我们可以通过简单的动态规划找出每一行中满足条件的格子，然后以它们为起点进行枚举。容易发现，在上述条件的约束下，这些起点构成的区间是不会重叠的，因此我们处理一行的时间可以控制在$\mathcal{O}(M)$。从而遍历所有行的时间为$\mathcal{O}(NM)$。

对于另外三种情形，我们可以对数组进行旋转，从而化归到从左到右的情形再进行处理。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
bool check(vector<vector<char>> &board, string word) {
    int n = board.size(), m = board[0].size(), k = word.size();
    
    for (int i = 0; i < n; ++i) {
        vector<int> acc(m);
        for (int j = m - 1; j >= 0; --j) {
            if (board[i][j] == '#')
                acc[j] = 0;
            else
                acc[j] = (j == m - 1) ? 1 : acc[j + 1] + 1;
        }

        for (int j = 0; j < m; ++j) {
            if (acc[j] == k && (j == 0 || board[i][j - 1] == '#')) {
                bool good = true;
                for (int p = 0; p < k; ++p) {
                    if (board[i][j + p] != word[p] && board[i][j + p] != ' ') {
                        good = false;
                        break;
                    }
                }
                if (good)
                    return true;
            }
        }
    }
    
    return false;
}

class Solution {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size(), k = word.size();
        
        if (check(board, word))
            return true;
        
        vector<vector<char>> b1(board);
        for (int i = 0; i < n; ++i)
            reverse(b1[i].begin(), b1[i].end());
        
        if (check(b1, word))
            return true;
        
        vector<vector<char>> b2(m);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                b2[i].emplace_back(board[j][i]);
        
        if (check(b2, word))
            return true;
        
        vector<vector<char>> b3(b2);
        for (int i = 0; i < m; ++i)
            reverse(b3[i].begin(), b3[i].end());
        
        return check(b3, word);
    }
};
```

:::

## Problem D - [解出数学表达式的学生分数](https://leetcode.cn/problems/the-score-of-students-solving-math-expression/)

### 方法一：表达式求值+动态规划

首先理一理总体的思路，我们需要做的事情有：

1. 求出表达式的正确值
2. 求出表达式所有可能的值
3. 计算学生的得分

对于第一步，本题只包含个位数和加法、乘法，并且不含括号，我们可以简单地进行实现；但对于比赛来说，为了追求速度，我们可以借助一些已有的工具，比如说 [224. 基本计算器](https://leetcode.cn/problems/basic-calculator/)，或者干脆使用Python等语言中自带的`eval()`函数。

对于第二步，我们使用区间动态规划求解。对于每个区间，我们保存该区间可能得到的结果。对于一个较大的区间，我们枚举它最后一次运算的位置，然后将两侧子区间的结果进行合并。注意这里要结合题目给出的信息，$answers[i]\le1000$，又由于只有加法和乘法，所以我们不需要保存大于$1000$的中间结果。

最后我们就可以按照规则来计算所有学生的得分了。

::: details 参考代码（C++）

```cpp
using ll = long long;

unordered_map<char, int> order = {{'#', -1}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'$', 0}, {'(', 0}};

// Leetcode 224: Basic Calculator
class Calculator {
    string trim(string s) {
        string t;
        for (char c : s)
            if (c != ' ')
                t.push_back(c);
        return t;
    }
    
    ll calc(ll a, ll b, char c) {
        switch(c) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
            default:
                return a;
        }
    }
public:
    int calculate(string s) {
        s = trim(s);
        stack<ll> val;
        stack<char> op;
        op.push('#');
        bool is_num = false, is_negative = false;
        ll num = 0;
        s += '$';
        auto work = [&](){
            ll b = val.top();
            val.pop();
            ll a = val.top();
            val.pop();
            val.push(calc(a, b, op.top()));
            op.pop();
        };
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            ll delta = c - '0';
            if (delta >= 0 && delta <= 9) {
                num = num * 10 + delta;
                is_num = true;                
            }
            else {
                if (is_num) {
                    val.push(is_negative ? -num : num);
                    is_num = false;
                    is_negative = false;
                } else {
                    if (c == '-' && (i == 0 || s[i - 1] != ')')) {
                        is_negative = true;
                        continue;
                    }
                }

                // Special case: "-(...)" => "-1*(...)"
                if (is_negative) {
                    val.push(-1);
                    while (order[op.top()] >= order['*'])
                        work();
                    op.push('*');
                    is_negative = false;
                }

                num = 0;
                if (c == ')')
                    while (op.top() != '(')
                        work();
                else if (c != '(')
                    while (order[op.top()] >= order[c])
                        work();
                if (c == ')')
                    op.pop();
                else
                    op.push(c);
            }
        }
        return val.top();
    }
};

class Solution {
public:
    int scoreOfStudents(string s, vector<int>& answers) {
        vector<int> nums;
        vector<char> ops;
        for (char ch : s) {
            if (ch == '+' || ch == '*')
                ops.emplace_back(ch);
            else
                nums.emplace_back(ch - '0');
        }
        
        int n = nums.size();
        
        // Calculate correct answer.
        Calculator calculator;
        ll correct = calculator.calculate(s);
        
        // Calculate possible answers.
        vector<vector<unordered_set<int>>> dp(n, vector<unordered_set<int>>(n));
        for (int i = 0; i < n; ++i)
            dp[i][i].emplace(nums[i]);
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {
                    for (int x : dp[i][k])
                        for (int y : dp[k + 1][j]) {
                            if (ops[k] == '+' && x + y <= 1000)
                                dp[i][j].emplace(x + y);
                            else if (ops[k] == '*' && x * y <= 1000)
                                dp[i][j].emplace(x * y);
                        }
                }
            }
        }
        
        int ans = 0;
        for (int answer : answers) {
            if (answer == correct)
                ans += 5;
            else if (dp[0][n - 1].count(answer))
                ans += 2;
        }
        
        return ans;
    }
};
```

:::

<Utterances />
