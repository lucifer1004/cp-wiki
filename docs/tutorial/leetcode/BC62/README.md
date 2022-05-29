# Leetcode 第62场双周赛题解

## Problem A - [将一维数组转变成二维数组](https://leetcode.cn/problems/convert-1d-array-into-2d-array/)

### 方法一：模拟

按要求操作即可。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def construct2DArray(self, original: List[int], m: int, n: int) -> List[List[int]]:
        if len(original) != m * n:
            return []
        return [original[i * n:(i + 1) * n] for i in range(m)]
```

:::


## Problem B - [连接后等于目标字符串的字符串对](https://leetcode.cn/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/)

### 方法一：暴力

暴力枚举所有长度符合要求的串即可。

- 时间复杂度为$\mathcal{O}(N^2|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numOfPairs(vector<string>& nums, string target) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (i != j && nums[i].size() + nums[j].size() == target.size() && nums[i] + nums[j] == target)
                    ans++;
            }
        return ans;
    }
};
```

:::

### 方法二：前后缀

我们可以逐个判断每个字符串是否是`target`的前缀或后缀，并对后缀长度计数。

然后，我们枚举所有是前缀的字符串，根据哈希表的计数结果就可以知道有多少个与之匹配的后缀。注意这里需要排除掉它自身也是后缀并且长度刚好为`target`的一半的情形。

- 时间复杂度为$\mathcal{O}(N|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int numOfPairs(vector<string>& nums, string target) {
        int n = nums.size(), t = target.size();
        vector<bool> pre(n), suf(n);
        unordered_map<int, int> suf_map;
        for (int i = 0; i < n; ++i) {
            auto &num = nums[i];
            int m = num.size();
            if (m > target.size())
                continue;
            if (num == target.substr(0, m))
                pre[i] = true;
            if (num == target.substr(t - m, m))
                suf[i] = true, suf_map[m]++;
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (pre[i]) {
                ans += suf_map[t - nums[i].size()];
                if (suf[i] && nums[i].size() * 2 == t)
                    ans--;
            }
        }
        
        return ans;
    }
};
```

:::



## Problem C - [考试的最大困扰度](https://leetcode.cn/problems/maximize-the-confusion-of-an-exam/)

### 方法一：贪心

显然，想要连续相邻的`T`，就应该改变连续的`F`（未必相邻）；想要连续相邻的`F`，就应该改变连续的`T`（未必相邻）。所以我们找出`T`和`F`的位置，分别考虑尽可能获取`T`和尽可能获取`F`这两种情形即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        vector<int> T{-1}, F{-1};
        int n = answerKey.size();
        for (int i = 0; i < n; ++i) {
            if (answerKey[i] == 'T')
                T.push_back(i);
            else
                F.push_back(i);
        }
        T.push_back(n), F.push_back(n);
        
        if (k >= T.size() - 2 || k >= F.size() - 2)
            return n;
        
        int ans = 0;
        for (int i = 1; i + k < T.size(); ++i)
            ans = max(ans, T[i + k] - T[i - 1] - 1);
        for (int i = 1; i + k < F.size(); ++i)
            ans = max(ans, F[i + k] - F[i - 1] - 1);
        
        return ans;
    }
};
```

:::

## Problem D - [分割数组的最多方案数](https://leetcode.cn/problems/maximum-number-of-ways-to-partition-an-array/)

### 方法一：哈希表

不进行改变的结果是容易求得的。

下面考虑改变一次的结果。

对于第$i$个元素，将其改变为$k$后的数值变化是$k - nums[i]$。问题是，我们并不知道第$i$个元素在划分中是属于左边还是右边。

可以发现，第$i$个元素有$n - i$种在左边的情况，有$i-1$种在右边的情况。而第$i$个元素和第$i+1$个元素只在一种划分中分属两边。这提示我们使用前后缀的思想：从第一个元素开始，考虑$n-1$种当前元素在左边的情况，然后每经过一个位置，进行一次修改。对于当前元素在左边的情况，我们对$\sum L-\sum R$进行计数；反之，则对$\sum R-\sum L$计数。这样我们就可以由$delta[nums[i]-k]$得到将当前元素修改为$k$后可以得到的划分数。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        vector<ll> pre(n + 1);
        for (int i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] + nums[i - 1];
        
        // Do not change
        for (int i = 1; i < n; ++i) {
            if (pre[i] * 2 == pre[n])
                ans++;
        }
        
        // Change one
        unordered_map<ll, int> delta;
        for (int i = n; i >= 1; --i) {
            ll l = pre[i - 1];
            ll r = pre[n] - l;
            delta[l - r]++;
        }
                
        for (int i = 1; i <= n; ++i) {
            ll l = pre[i - 1];
            ll r = pre[n] - l;
            if (i > 1)
                delta[r - l]++;
            delta[l - r]--;
            ans = max(ans, delta[nums[i - 1] - k]);
        }
        
        return ans;
    }
};
```

:::

<Utterances />
