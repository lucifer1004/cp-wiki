# Leetcode 第29场双周赛题解

## Problem A - [去掉最低工资和最高工资后的工资平均值](https://leetcode-cn.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/)

分别求出总和，最大值和最小值即可。

::: spoiler 参考代码（Python3）

```python
class Solution:
    def average(self, salary: List[int]) -> float:
        return (sum(salary) - min(salary) - max(salary)) / (len(salary) - 2)
```

:::

## Problem B - [n 的第 k 个因子](https://leetcode-cn.com/problems/the-kth-factor-of-n/)

$O(\sqrt{n})$求出$n$的所有因子，排序后取第$k$个即可。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int kthFactor(int n, int k) {
        set<int> s;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                s.insert(i);
                s.insert(n / i);
            }
        }
        vector<int> v(s.begin(), s.end());
        if (k > v.size())
            return -1;
        return v[k - 1];
    }
};
```

:::

## Problem C - [删掉一个元素以后全为 1 的最长子数组](https://leetcode-cn.com/problems/longest-subarray-of-1s-after-deleting-one-element/)

求出每个元素左边连续1的长度和右边连续1的长度，然后枚举删除的位置即可。时间复杂度$O(n)$。

::: spoiler 参考代码（C++）

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n), right(n);
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] == 1)
                left[i] = left[i - 1] + 1;
        }
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i + 1] == 1)
                right[i] = right[i + 1] + 1;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans = max(ans, left[i] + right[i]);
        return ans;
    }
};
```

:::

## Problem D - [并行课程 II](https://leetcode-cn.com/problems/parallel-courses-ii/)

本题比赛时测试数据比较弱，导致很多错误贪心代码也都通过了评测，因此最后本场比赛unrated。

本题的各种贪心策略都能够找到反例，只有通过枚举所有状态才能保证最优解。因为本题的状态可以用二进制数来表示当前状态（哪些课上过，哪些课还没上过），所以就有了**状态压缩**这么个名字。

状态的转移是非常清晰的，对于当前状态（这一学期结束后所有课程的学习状态），我们需要枚举上一个学期结束时所有课程的学习状态。但由于上个学期结束时已学的课程必定是本学期结束时已学课程的子集，所以我们可以用位运算枚举子集的技巧来进行优化，使得总的时间复杂度由$O(4^n)$变为$O(3^n)$。

用位运算优化子集枚举的关键，就是下面代码中的`j = (j - 1) & i`这部分。为了理解这一步操作的含义，我们需要考虑一下一个二进制数减一之后发生了什么：最右边的一个$1$变为$0$，而其后的所有$0$都变为$1$。之后我们再将$j-1$与$i$求与，去除最右边不该有的$1$。所以，这一步操作整体上就相当于是，放弃最后一个取的元素，然后取上所有在它之后能取的元素。

最后再说明一下为什么总时间复杂是$O(3^n)$。道理很简单，原本有$11,10,01,00$四种可能，但通过位运算，我们能够在$O(1)$时间内找到当前集合的下一个子集，所以就把$01$这种情况给去掉了。自然总复杂度就降低到了$O(3^n)$。

```cpp
for (int i = 1; i < (1 << n); ++i) {
    for (int j = i; j; j = (j - 1) & i) {
        // ...
    }
}
```

当然，在最后的状压DP之前，还有对$pre$和$valid$的预处理，相关的细节看代码就可以。

::: spoiler 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;
int dp[40000];
bool valid[40000];

class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        vector<int> pre(n), in(n);
        vector<vector<int>> adj(n);
        for (auto v : dependencies) {
            adj[v[0] - 1].emplace_back(v[1] - 1);
            in[v[1] - 1]++;
        }
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (in[i] == 0)
                q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                pre[v] |= pre[u] | (1 << u);
                in[v]--;
                if (in[v] == 0)
                    q.push(v);
            }
        }
        
        memset(valid, true, sizeof(valid));
        for (int i = 1; i < (1 << n); ++i) {
            vector<int> t;
            for (int j = 0; j < n; ++j)
                if (i & (1 << j))
                    t.emplace_back(j);
            if (t.size() > k) {
                valid[i] = false;
                continue;
            }
            for (int j : t) {
                for (int p : t)
                    if (pre[j] & (1 << p)) {
                        valid[i] = false;
                        break;
                    }
                if (!valid[i])
                    break;
            }
        }
        
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = i; j; j = (j - 1) & i)
                if (valid[j] && dp[i - j] != INF)
                    dp[i] = min(dp[i], dp[i - j] + 1);
        }
        return dp[(1 << n) - 1];
    }
};
```

:::

<Utterances />
