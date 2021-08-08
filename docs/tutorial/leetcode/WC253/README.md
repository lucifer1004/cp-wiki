# Leetcode 第253场周赛题解

## Problem A - [检查字符串是否为数组前缀](https://leetcode-cn.com/problems/check-if-string-is-a-prefix-of-array/)

### 方法一：模拟

逐位检查即可。注意终止条件的判断。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool isPrefixString(string s, vector<string>& words) {
        int n = s.size();
        int ptr = 0;
        for (string &word : words) {
            int m = word.size();
            int i = 0;
            while (i < m && ptr < n && word[i] == s[ptr])
                i++, ptr++;
            if (i == m && ptr == n)
                return true;
            if (i != m)
                return false;
        }
        return false;
    }
};
```

:::

## Problem B - [移除石子使总数最小](https://leetcode-cn.com/problems/remove-stones-to-minimize-the-total/)

### 方法一：贪心+优先队列

每次应该从当前最大的那堆中移除，所以用一个大根堆来维护每堆中剩余的石子数即可。

- 时间复杂度$\mathcal{O}(K\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> pq;
        for (int pile : piles)
            pq.emplace(pile);
        while (k > 0) {
            k--;
            int t = pq.top();
            pq.pop();
            pq.emplace(t - t / 2);
        }
        int ans = 0;
        while (!pq.empty())
            ans += pq.top(), pq.pop();
        return ans;
    }
};
```

:::

## Problem C - [使字符串平衡的最小交换次数](https://leetcode-cn.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/)

### 方法一：贪心

因为左括号和右括号的数目保证相等，所以我们从左向右扫描并记录当前的嵌套深度，每当当前的深度为$0$而当前字符为`]`时，我们从最右边找一个`[`来与其进行交换（从最右边找是因为左括号越靠前越能保证不会出现非法位置）。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();
        int bal = 0, ans = 0;
        int ptr = n - 1;
        for (char c : s) {
            if (c == '[')
                bal++;
            else {
                if (bal > 0) {
                    bal--;
                } else {
                    ans++;
                    while (s[ptr] != '[')
                        ptr--;
                    s[ptr] = ']';
                    bal++;
                }
            }
        }
        return ans;
    }
};
```

:::

事实上，我们并不需要进行这样的交换，而只需要假设进行了这样的交换即可。这样可以将代码进一步简化。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minSwaps(string s) {
        int bal = 0, ans = 0;
        for (char c : s) {
            if (c == '[')
                bal++;
            else if (bal > 0)
                bal--;
            else
                ans++, bal++;
        }
        return ans;
    }
};
```

:::

这样做会导致最终的$bal$不为$0$，但并不影响结果的正确性，因为我们总是用最靠后的`[`来进行交换，所以最后得到的字符串末尾是一串连续的`]`，且所有用于交换的的`[`都来自于这个串中，而由于左右括号数量相等，只要这个串前面的正确性得到了保证，假设这个串的长度为$m$，那么这个串前面的嵌套深度就必定为$m$，从而结果保证是一个合法的字符串。

## Problem D - [找出到每个位置为止最长的有效障碍赛跑路线](https://leetcode-cn.com/problems/find-the-longest-valid-obstacle-course-at-each-position/)

### 方法一：动态规划（最长不下降子序列）

最长不下降子序列模板题。因为允许相等，所以这里二分时用`upper_bound`；如果要求严格递增，则应该用`lower_bound`。（对LIS不太熟悉的同学可以思考下这两者之间的差别，会对你理解这一方法的原理有所帮助。）

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<int> ans(n);
        vector<int> LIS;
        int i = 0;
        for (int obstacle : obstacles) {
            auto it = upper_bound(LIS.begin(), LIS.end(), obstacle);
            if (it == LIS.end()) {
                LIS.emplace_back(obstacle);
                ans[i] = LIS.size();
            } else {
                ans[i] = it - LIS.begin() + 1;
                *it = obstacle;
            }
            i++;
        }
        return ans;
    }
};
```

:::

<Utterances />
