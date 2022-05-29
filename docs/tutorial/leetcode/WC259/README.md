# Leetcode 第259场周赛题解

## Problem A - [执行操作后的变量值](https://leetcode.cn/problems/final-value-of-variable-after-performing-operations/)

### 方法一：模拟

直接模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def finalValueAfterOperations(self, operations: List[str]) -> int:
        x = 0
        for op in operations:
            if op == 'X++' or op == '++X':
                x += 1
            else:
                x -= 1
        return x
```

:::

## Problem B - [数组美丽值求和](https://leetcode.cn/problems/sum-of-beauty-in-the-array/)

### 方法一：前缀和

预处理得到前缀最大值和后缀最小值数组，即可快速判断中间元素的美丽值。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n), suf(n);
        pre[0] = nums[0];
        for (int i = 1; i < n; ++i)
            pre[i] = max(pre[i - 1], nums[i]);
        suf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i)
            suf[i] = min(suf[i + 1], nums[i]);
        int ans = 0;
        for (int i = 1; i < n - 1; ++i) {
            if (pre[i - 1] < nums[i] && nums[i] < suf[i + 1])
                ans += 2;
            else if (nums[i - 1] < nums[i] && nums[i] < nums[i + 1])
                ans++;
        }
        return ans;
    }
};
```

:::

## Problem C - [检测正方形](https://leetcode.cn/problems/detect-squares/)

### 方法一：哈希表

用一个哈希表存储所有的顶点，然后在`count`查询时，枚举对角线即可。注意这里首先判断确定对角线后剩余两顶点是否在哈希表中，以避免在哈希表内引入值为$0$的元素。

- `add`时间复杂度$\mathcal{O}(1)$，`count`时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class DetectSquares:

    def __init__(self):
        self.cnt = collections.Counter()


    def add(self, point: List[int]) -> None:
        self.cnt[(point[0], point[1])] += 1


    def count(self, point: List[int]) -> int:
        x, y = point
        ans = 0
        for xi, yi in self.cnt:
            if abs(xi - x) == abs(yi - y) and xi != x:
                if (xi, y) in self.cnt and (x, yi) in self.cnt:
                    ans += self.cnt[(xi, yi)] * self.cnt[(xi, y)] * self.cnt[(x, yi)]
        return ans

```

:::

## Problem D - [重复 K 次的最长子序列](https://leetcode.cn/problems/longest-subsequence-repeated-k-times/)

### 方法一：回溯

注意到结果中的每个字母最少出现$K$次，而由于$|S|<8K$，说明符合条件的字母至多有$7$个，那么我们通过回溯枚举符合条件的字母的排列方式即可。

在排列方式给定的情况下，判断是否出现了$K$次，这就是一道很经典的题目了。下面的参考解法中采取的是遍历整个字符串的$\mathcal{O}(|S|)$的方法，也可以预处理出$nxt$数组后再计算，可能可以减小一些常数。

- 时间复杂度$\mathcal{O}(|S|\cdot\lfloor\frac{|S|}{k}\rfloor!)$，。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
    int k;
    unordered_map<char, int> cnt;
    string s, t, ans;
    
    void dfs() {
        unordered_map<char, int> cnt2(cnt);
        for (auto [ch, freq] : cnt2) {
            t.push_back(ch);
            if (t.size() > ans.size() || (t.size() == ans.size() && t > ans)) {
                int times = 0, pos = 0;
                for (char c : s)
                    if (c == t[pos]) {
                        pos++;
                        if (pos == t.size())
                            times++, pos = 0;
                    }

                if (times >= k)
                    ans = t;
            }
            cnt[ch] -= k;
            if (cnt[ch] < k)
                cnt.erase(ch);
            dfs();
            t.pop_back();
            cnt[ch] = freq;
        }
    }
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        this->k = k;
        int n = s.size();
        for (char c : s)
            cnt[c]++;
        string to_del;
        for (auto [ch, freq] : cnt)
            if (freq < k)
                to_del.push_back(ch);
        for (char ch : to_del)
            cnt.erase(ch);
        
        for (char c : s)
            if (cnt.count(c))
                this->s.push_back(c);
        
        dfs();
        
        return ans;
    }
};
```

:::

<Utterances />
