# Leetcode 第242场周赛题解

## Problem A - [哪种连续子字符串更长](https://leetcode.cn/problems/longer-contiguous-segments-of-ones-than-zeros/)

### 方法一：暴力

记录当前的`0`串长度和最长的`0`串长度，以及当前的`1`串长度和最长的`1`串长度，遍历并维护即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool checkZeroOnes(string s) {
        int om = 0, zm = 0;
        int o = 0, z = 0;
        for (char c : s) {
            if (c == '0') {
                z++;
                o = 0;
            } else {
                o++;
                z = 0;
            }
            om = max(om, o);
            zm = max(zm, z);
        }
        return om > zm;
    }
};
```

:::

## Problem B - [准时到达的列车最小时速](https://leetcode.cn/problems/minimum-speed-to-arrive-on-time/)

### 方法一：二分

非常明显的二分答案。需要注意的是，最后一趟车需要单独判断，因为这里不需要等到整点。

- 时间复杂度$\mathcal{O}(N\log D)$。
- 空间复杂度$\mathcal{O}(1)$。

> 为了防止浮点数有关的精度问题，下面的代码中预先将`hour`乘以100变为整数。但这一操作是否是必要的，我暂时不能肯定。

::: details 参考代码（C++）

```cpp
using ll = long long;

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 );
}

class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = dist.size();
        int lo = 1, hi = 1e7;
        string s = string_format("%.2f", hour);
        int m = s.size();
        s = s.substr(0, m - 3) + s.substr(m - 2, 2);
        ll limit = stoll(s);
        
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            ll tot = 0;
            for (int i = 0; i < n - 1; ++i) {
                tot += (dist[i] - 1) / mid + 1;
            }
            tot *= 100;
            tot += (dist[n - 1] * 100 - 1) / mid + 1;
            if (tot <= limit)
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        if (lo > 1e7)
            return -1;
        return lo;
    }
};
```

:::

## Problem C - [跳跃游戏 VII](https://leetcode.cn/problems/jump-game-vii/)

### 方法一：离散化+树状数组+双指针

我们可以首先找出所有为`0`的位置；如果某一位置可到达，则将$[i+minJump,i+maxJump]$范围内为`0`的位置都设为可到达。

这里，我们可以用树状数组来实现区间操作，并用双指针维护对应的区间。

- 时间复杂度$\mathcal{O}(|S|+M\log M)$，其中$M$为字符串中`0`的个数。
- 空间复杂度$\mathcal{O}(M)$。

::: details 参考代码（C++）

```cpp
inline int lowbit(int x) {
    return x & (-x);
}

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {        
        int n = s.size();
        if (s[n - 1] == '1')
            return false;
        
        vector<int> zero;
        for (int i = 0; i < n; ++i)
            if (s[i] == '0')
                zero.emplace_back(i);
        int m = zero.size();
        
        vector<int> a(m + 1);
        auto query = [&](int pos) {
            int ans = 0;
            for (; pos; pos -= lowbit(pos))
                ans += a[pos];
            return ans;
        };
        auto update = [&](int pos, int val) {
            for (; pos <= m; pos += lowbit(pos))
                a[pos] += val;
        };

        update(1, 1);
        update(2, -1);
        int l = 0, r = 0;
        for (int i = 1; i < m; ++i) {
            if (query(i) > 0) {
                while (l < m && zero[l] < zero[i - 1] + minJump)
                    l++;
                while (r < m && zero[r] <= zero[i - 1] + maxJump)
                    r++;
                update(l + 1, 1), update(r + 1, -1);
            }
        }
        
        return query(m) > 0;
    }
};
```

:::

### 方法二：平衡二叉搜索树

另一种思路是用有序集合（如C++的`set`）维护所有为`0`的位置。注意，这里我们需要把已经能够到达的位置从集合中删除，这样就能够保证遍历的时间复杂度为$\mathcal{O}(M\log M)$。

- 时间复杂度$\mathcal{O}(|S|+M\log M)$，其中$M$为字符串中`0`的个数。
- 空间复杂度$\mathcal{O}(|S|+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {        
        int n = s.size();
        if (s[n - 1] == '1')
            return false;
        
        vector<int> zero;
        for (int i = 0; i < n; ++i)
            if (s[i] == '0')
                zero.emplace_back(i);
        int m = zero.size();
        vector<bool> can(n);
        can[0] = true;
        set<int> st(zero.begin(), zero.end());
        for (int i = 0; i + 1 < m; ++i) {
            if (can[zero[i]]) {
                vector<int> destinations;
                for (auto it = st.lower_bound(zero[i] + minJump); it != st.upper_bound(zero[i] + maxJump); ++it) {
                    destinations.emplace_back(*it);
                }
                for (int destination : destinations) {
                    can[destination] = true;
                    st.erase(destination);
                }
            }
        }
        
        return can[n - 1];
    }
};
```

:::

### 方法三：双端队列

逆向思考，想要到达一个位置，就必须能够到达$[i-maxJump,i-minJump]$范围内的某个位置。显然，我们可以用一个双端队列来维护这样的位置，从而实现线性的时间复杂度。

- 时间复杂度$\mathcal{O}(|S|+M)$，其中$M$为字符串中`0`的个数。
- 空间复杂度$\mathcal{O}(|S|+M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {        
        int n = s.size();
        if (s[n - 1] == '1')
            return false;
        
        vector<int> zero;
        for (int i = 0; i < n; ++i)
            if (s[i] == '0')
                zero.emplace_back(i);
        int m = zero.size();
        vector<bool> can(n);
        can[0] = true;
        deque<int> dq;
        int ptr = 0;
        for (int i = 1; i < m; ++i) {
            while (ptr < i && zero[ptr] + minJump <= zero[i]) {
                if (can[zero[ptr]])
                    dq.emplace_back(zero[ptr]);
                ptr++;
            }
            while (!dq.empty() && dq.front() + maxJump < zero[i])
                dq.pop_front();
            can[zero[i]] = !dq.empty();
        }
        
        return can[n - 1];
    }
};
```

:::



## Problem D - [石子游戏 VIII](https://leetcode.cn/problems/stone-game-viii/)

### 方法一：动态规划

观察可知，无论如何操作，数组的前缀和是恒定的。这里，我们定义$dp[i]$为当次操作取至原数组第$i$个数时的最大分值，可得到转移方程：

$$
dp[i]=\sum_{j=1}^istones[i]-\max_{j=i+1}^ndp[j]
$$

其中$\sum_{j=1}^istones[i]$是本次操作的得分，$\max_{j=i+1}^ndp[j]$则是对手后续操作的最大净得分。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<ll> s(n + 1);
        for (int i = 1; i <= n; ++i)
            s[i] = s[i - 1] + stones[i - 1];
        vector<ll> dp(n + 1);
        ll ans = dp[n] = s[n];
        for (int i = n - 1; i > 1; --i) {
            dp[i] = s[i] - ans;
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

:::

<Utterances />
