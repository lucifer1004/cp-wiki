# Leetcode 第218场周赛题解

## Problem A - [设计 Goal 解析器](https://leetcode-cn.com/problems/goal-parser-interpretation/)

因为不需要考虑输入不合法的情形，所以直接模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string interpret(string command) {
        string ans;
        for (int i = 0; i < command.size(); ++i) {
            char c = command[i];
            if (c == 'G')
                ans.push_back(c);
            else if (c == '(') {
                if (command[i + 1] == ')')
                    ans.push_back('o'), i++;
                else
                    ans += "al", i += 3;
            }
        }
        return ans;
    }
};
```

:::

## Problem B - [K 和数对的最大数目](https://leetcode-cn.com/problems/max-number-of-k-sum-pairs/)

计数之后进行处理即可，需要特别处理一下$num*2=k$的情况。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

需要注意的是，代码中对$k-num$是否存在的这一判断是不能忽略的，因为如果直接使用$mp[k-num]$，C++会自动将$k-num$这个键插入进去；而在遍历哈希表的时候增加键（或删除键）会导致遍历结果和预期不符。

::: details 参考代码（C++）
```cpp
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        int ans = 0;
        unordered_map<int, int> mp;
        for (int num : nums)
            mp[num]++;
        for (auto [num, freq] : mp) {
            if (num * 2 == k) {
                ans += freq / 2;
            } else if (mp.count(k - num)) {
                int delta = min(freq, mp[k - num]);
                mp[k - num] -= delta;
                mp[num] -= delta;
                ans += delta;
            }
        }
        return ans;
    }
};
```
:::

## Problem C - [连接连续二进制数字](https://leetcode-cn.com/problems/concatenation-of-consecutive-binary-numbers/)

考虑数据范围，可以直接进行模拟。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
mod = 1000000007

class Solution:
    def concatenatedBinary(self, n: int) -> int:
        ans = 0
        for i in range(1, n + 1):
            b = bin(i)[2:]
            n = len(b)
            ans = ans * pow(2, n) % mod
            ans = (ans + i) % mod
        return ans
```

:::

使用C++中的内置函数`__builtin_clz`来求$i$的二进制表示的长度是更迅速的。因为内置函数有指令集优化，所以时间复杂度会来到$\mathcal{O}(N)$。

::: details 参考代码（C++）
```cpp
const int MOD = 1e9 + 7;

class Solution {
public:
    int concatenatedBinary(int n) {
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            int len = 32 - __builtin_clz(i);
            ans = ((ans << len) + i) % MOD;
        }
        return ans;
    }
};
```
:::

## Problem D - [最小不兼容性](https://leetcode-cn.com/problems/minimum-incompatibility/)

看到$N$的范围，立即想到进行状态压缩。

我们从初始状态（所有数字都在一起）开始，尝试所有可能的将当前数字分成两堆的方案，然后递归求解左堆和右堆。为了避免重复计算，我们需要使用记忆化。

在枚举分组方案时，如果我们朴素地遍历$[1\dots state]$（$state$为当前堆中的数字），总时间复杂度将来到$\mathcal{O}(4^N)$，对于$N=16$，$4^{16}\simeq4\times10^9$，这是我们不能接受的。因此，我们需要使用子集枚举的优化（注释中**优化二**），从而将总时间复杂度降低到$\mathcal{O}(3^N)$。

此时，如果直接提交，会发现超时。实际上，本题中存在一种特殊情况，也即$N=K$，这时所有组的大小都为$1$，不兼容性总和一定为$0$。我们可以单独考虑这种情况（注释中**优化一**），直接返回$0$。这一优化的影响非常大。可以尝试对比一下，在固定$N$和$nums$的情况下，$K$越大，代码的运行时间是越长的，因为$K$越大意味着分组越小，从而有效的分组方案越多。因此$N=K$是耗时最久的一种情况。

有了这两个优化，实际上已经可以通过题目的时间限制。不过，我们还可以通过引入**优化三**和**优化四**，来进一步减少代码的运行时间。

- 时间复杂度$\mathcal{O}(3^N)$。
- 空间复杂度$\mathcal{O}(2^N)$。

::: details 题外话
比赛时，拷贝代码的时候不知道怎么把版本搞错了，本来是加上了优化一的，结果连着交了几发没加优化一的版本，怒吃三发TLE，最后靠着优化二和优化三勉强通过了。预计下周就要跌出国服前十了，心塞。
:::

::: details 参考代码（C++）

```cpp
// 优化四：指令集优化，让CPU使用POPCNT指令，从而加速__builtin_popcount
#pragma GCC target ("sse4.2")

const int INF = 0x3f3f3f3f;
int memo[65536], v[16];

class Solution {
    int n, k, sz;
    vector<int> nums;
    int solve(int state) {
        if (memo[state] != -1)
            return memo[state];
        
        // 边界条件：当前集合刚好包含n/k个元素，不需要继续划分
        if (__builtin_popcount(state) == sz) {
            int idx = 0;
            for (int i = 0; i < n; ++i)
                if (state & (1 << i))
                   v[idx++] = i;
            for (int i = 0; i + 1 < sz; ++i)
                if (nums[v[i]] == nums[v[i + 1]])
                    return memo[state] = INF;
            return memo[state] = nums[v[n / k - 1]] - nums[v[0]];
        }
        int ans = INF;
        
        // 优化二：子集枚举优化
        for (int sub = state & (state - 1); sub; sub = (sub - 1) & state) {
            if (__builtin_popcount(sub) % sz != 0)
                continue;
            int left = solve(sub);
            
            // 优化三：如果左边的最优值已经达到了当前总和的最优值，则不需要继续计算右边。
            if (left >= ans)
                continue;
            int right = solve(state ^ sub);
            ans = min(ans, left + right);
        }
        return memo[state] = ans;
    }

public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        n = nums.size();
        this->k = k;
        sz = n / k;
        
        // 优化一：每个子集的大小为1，不兼容性显然为0，总和也是0。
        // 这种情况的筛除非常重要，因为它需要最多的枚举次数。
        if (sz == 1)
            return 0;
        
        sort(nums.begin(), nums.end());
        vector<int> cnt(n + 1);
        for (int num : nums) {
            cnt[num]++;
            if (cnt[num] > k)
                return -1;
        }
        this->nums = nums;
        for (int i = 0; i < (1 << n); ++i)
            memo[i] = -1;
        return solve((1 << n) - 1);
    }
};
```

:::

<Utterances />
