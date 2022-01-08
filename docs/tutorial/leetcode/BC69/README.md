# Leetcode 第69场双周赛题解

## Problem A - [将标题首字母大写](https://leetcode-cn.com/problems/capitalize-the-title/)

### 方法一：模拟

按要求操作即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def capitalizeTitle(self, title: str) -> str:
        return ' '.join([word[0].upper() + word[1:].lower() if len(word) > 2 else word.lower() for word in title.split()])
```

:::

## Problem B - [链表最大孪生和](https://leetcode-cn.com/problems/maximum-twin-sum-of-a-linked-list/)

### 方法一：暴力

变成数组后枚举即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def pairSum(self, head: Optional[ListNode]) -> int:
        nums = []
        p = head
        while p != None:
            nums.append(p.val)
            p = p.next
        n = len(nums)
        return max(nums[i] + nums[n - 1 - i] for i in range(n // 2))
```

:::

## Problem C - [连接两字母单词得到的最长回文串](https://leetcode-cn.com/problems/longest-palindrome-by-concatenating-two-letter-words/)

### 方法一：哈希表

两字母单词最多 $26\times26$ 种，我们直接用哈希表统计之后，分两位相同的单词和不同的单词分别处理。

- 对于两位不同的单词，它需要与它的对称单词构成一对才能放入回文串中；
- 对于两位相同的单词，它可以与它自身构成一对；同时，特别的，有且仅有一次，可以把一个两位相同的单词放在正中间。

处理过程中注意避免重复计数即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(|\sum|^2)$。其中 $\sum$ 表示字母表。

::: details 参考代码（Python 3）

```python
class Solution:
    def longestPalindrome(self, words: List[str]) -> int:
        same = collections.Counter()
        diff = collections.Counter()
        for word in words:
            if word[0] == word[1]:
                same[word] += 1
            else:
                diff[word] += 1
        ans = 0
        for word in diff:
            rev = word[::-1]
            if rev in diff:
                ans += min(diff[word], diff[rev]) * 2
        for word in same:
            ans += same[word] // 2 * 4
            same[word] %= 2
        for word in same:
            if same[word] == 1:
                ans += 2
                break
        return ans
```

:::

## Problem D - [用邮票贴满网格图](https://leetcode-cn.com/problems/stamping-the-grid/)

### 方法一：贪心+二维前缀和

我们考虑邮票的左上角。在一个格子$(i,j)$可以成为合法的左上角，也即$(i,j)\to(i+h-1,j+w-1)$的矩形范围内都没有坏格子的情况下，我们应当贪心地以它为左上角贴一枚邮票——因为我们并不怕重复，而是怕遗漏。这里，对于坏格子的统计，可以用二维前缀和进行。

这样的贴法可以保证不会有坏格子被覆盖到。接下来，我们需要检查是否每个好格子都被覆盖。朴素的想法是在上一步操作中，每贴一张邮票，就对邮票覆盖的所有格子进行标记。但在邮票比较大的情况下，这样做会超时。在比赛中，我是采用的二维树状数组来进行区间更新。但实际上，我们只需要再使用一次前缀和就可以解决第二部分的问题。

考虑一个格子$(i,j)$，它被覆盖，当且仅当$(i-h+1,j-w+1)\to(i,j)$这一矩形范围内存在邮票的左上角。所以，我们在上一步中把所有成为左上角的格子进行标记，对这个标记数组再计算一次前缀和，就可以快速求出每个格子是否被覆盖了。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
    vector<vector<int>> build_2d_prefix_sum(vector<vector<int>> &arr) {
        int n = arr.size(), m = arr[0].size();
        vector<vector<int>> sum(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + arr[i][j];
        return sum;
    }
    
    inline int query(vector<vector<int>> &sum, int u, int l, int d, int r) {
        return sum[d][r] - sum[d][l - 1] - sum[u - 1][r] + sum[u - 1][l - 1];
    }
    
public:
    bool possibleToStamp(vector<vector<int>>& grid, int h, int w) {
        int n = grid.size(), m = grid[0].size();
        auto sum = build_2d_prefix_sum(grid);
       
        vector<vector<int>> paint(n, vector<int>(m));
        for (int i = 0; i + h <= n; ++i)
            for (int j = 0; j + w <= m; ++j)
                if (grid[i][j] == 0 && query(sum, i + 1, j + 1, i + h, j + w) == 0)
                    paint[i][j] = 1;
        
        auto psum = build_2d_prefix_sum(paint);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] == 0 && query(psum, max(1, i - h + 2), max(1, j - w + 2), i + 1, j + 1) == 0)
                    return false;

        return true;
    }
};
```

:::

<Utterances />
