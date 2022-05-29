# Leetcode 第265场周赛题解

## Problem A - [值相等的最小索引](https://leetcode.cn/problems/smallest-index-with-equal-value/)

### 方法一：遍历

遍历一遍，逐个检查即可。

::: details 参考代码（Python 3）

```python
class Solution:
    def smallestEqual(self, nums: List[int]) -> int:
        ans = [i for i, num in enumerate(nums) if i % 10 == num]
        return -1 if len(ans) == 0 else ans[0]
```

:::

## Problem B - [找出临界点之间的最小和最大距离](https://leetcode.cn/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/)

### 方法一：遍历

为方便起见，首先将链表转为数组。接下来遍历找出所有的临界点即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> v;
        while (head != nullptr) {
            v.emplace_back(head->val);
            head = head->next;
        }
        
        vector<int> crit;
        for (int i = 1; i + 1 < v.size(); ++i) {
            if (v[i] > max(v[i - 1], v[i + 1]) || v[i] < min(v[i - 1], v[i + 1]))
                crit.emplace_back(i);
        }
        
        if (crit.size() < 2)
            return {-1, -1};
        
        int lo = 1e9, hi = crit.back() - crit.front();
        for (int i = 0; i + 1 < crit.size(); ++i)
            lo = min(lo, crit[i + 1] - crit[i]);
        
        return {lo, hi};
    }
};
```

:::

## Problem C - [转化数字的最小运算数](https://leetcode.cn/problems/minimum-operations-to-convert-number/)

### 方法一：BFS

典型的无权最短路问题，我们用BFS求解。

- 时间复杂度$\mathcal{O}(NC)$，其中$C$表示有效数值的范围大小。
- 空间复杂度$\mathcal{O}(C)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        if (goal == start)
            return 0;

        queue<int> q;
        vector<int> dis(1001, INF);
        q.emplace(start);
        dis[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int num : nums) {
                for (int nxt : {u - num, u + num, u ^ num}) {
                    if (nxt == goal)
                        return dis[u] + 1;
                    if (nxt >= 0 && nxt <= 1000 && dis[nxt] == INF)
                        dis[nxt] = dis[u] + 1, q.emplace(nxt);
                }
            }
        }

        return -1;
    }
};
```

:::

::: details 参考代码（Rust）

```rust
use std::collections::VecDeque;

const INF: i32 = 1_000_000_000;

impl Solution {
    pub fn minimum_operations(nums: Vec<i32>, start: i32, goal: i32) -> i32 {
        if start == goal {
            return 0;
        }

        let mut dis = [INF; 1001];
        let mut q = VecDeque::new();
        q.push_back(start);
        dis[start as usize] = 0;
        
        while !q.is_empty() {
            let u = q.pop_front().unwrap();
            for &num in nums.iter() {
                for &nxt in [u + num, u - num, u ^ num].iter() {
                    if nxt == goal {
                        return dis[u as usize] + 1;
                    }
                    if nxt >= 0 && nxt <= 1000 && dis[nxt as usize] == INF {
                        dis[nxt as usize] = dis[u as usize] + 1;
                        q.push_back(nxt);
                    }
                }
            }
        }
        
        -1
    }
}
```

:::

## Problem D - [同源字符串检测](https://leetcode.cn/contest/problems/check-if-an-original-string-exists-given-two-encoded-strings/)

### 方法一：动态规划

我们用$dp[i][j]$表示将$s_1$的前$i$个字母和$s_2$的前$j$个字母匹配且不发生冲突时，可能的长度差值。

可以看到，存在以下的转移：

- $dp[i][j]\rightarrow dp[p][j]$，$\Delta\rightarrow\Delta+s_1[i][p]$，这要求$s_1[i][p]$是一个数字
- $dp[i][j]\rightarrow dp[i][q]$，$\Delta\rightarrow\Delta-s_2[j][q]$，这要求$s_2[j][q]$是一个数字
- $dp[i][j]\rightarrow dp[i+1][j]$，$\Delta\rightarrow\Delta+1$，这要求$s_1[i]$是一个字母，并且$\Delta<0$，从而保证这个字母可以被$s_2$的剩余长度匹配掉。
- $dp[i][j]\rightarrow dp[i][j+1]$，$\Delta\rightarrow\Delta-1$，这要求$s_2[j]$是一个字母，并且$\Delta>0$，从而保证这个字母可以被$s_1$的剩余长度匹配掉。
- $dp[i][j]\rightarrow dp[i+1][j+1]$，$\Delta\rightarrow\Delta$，这要求$s_1[i]=s_2[j]$且都为字母，并且$\Delta=0$。

最后，我们检查$dp[N][M]$是否包含$0$即可。

- 时间复杂度$\mathcal{O}(NMD\cdot 10^D)$。其中$D$表示连续数字串的最长长度，本题中$D=3$。$D$决定了长度差的取值范围为$(-10^D, 10^D)$，这是因为连续的数字串前面至少有一个字母（或为字符串串首），而由我们的转移规则可知，字母只有在串的长度小于等于另一个串时才会被用于匹配，因此连续$D$个数字至多使得当前字符串比另一字符串长$10^D-1$。
- 空间复杂度$\mathcal{O}(NM\cdot 10^D)$。

::: details 参考代码（C++）

```cpp
class Solution {
    bool is_digit(char ch) {
        return ch >= '0' && ch <= '9';
    }
public:
    bool possiblyEquals(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<unordered_set<int>>> dp(n + 1, vector<unordered_set<int>>(m + 1));
        dp[0][0].emplace(0);
                
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int delta : dp[i][j]) {
                    int num = 0;
                    for (int p = i; p < min(i + 3, n); ++p) {
                        if (is_digit(s1[p])) {
                            num = num * 10 + s1[p] - '0';
                            dp[p + 1][j].emplace(delta + num);
                        } else {
                            break;
                        }
                    }
                    
                    num = 0;
                    for (int q = j; q < min(j + 3, m); ++q) {
                        if (is_digit(s2[q])) {
                            num = num * 10 + s2[q] - '0';
                            dp[i][q + 1].emplace(delta - num);
                        } else {
                            break;
                        }
                    }
                    
                    if (i < n && delta < 0 && !is_digit(s1[i])) 
                        dp[i + 1][j].emplace(delta + 1);
                            
                    if (j < m && delta > 0 && !is_digit(s2[j])) 
                        dp[i][j + 1].emplace(delta - 1);
                            
                    if (i < n && j < m && delta == 0 && s1[i] == s2[j])
                        dp[i + 1][j + 1].emplace(0);
                }
            }
        }
        
        return dp[n][m].count(0);
    }
};
```

:::

<Utterances />
