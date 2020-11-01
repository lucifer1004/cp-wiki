# Leetcode 第213场周赛题解

## Problem A - [能否连接形成数组](https://leetcode-cn.com/problems/check-array-formation-through-concatenation/)

因为题目说明了$arr$和$pieces$中所有数字都是互异的，所以这题实际是一个模拟题。我们首先用一个哈希表记录下$pieces$中每一个数组的第一个数字对应的$pieces$中的下标，接下来，我们对$arr$进行遍历。如果当前位置不在哈希表中，则说明没有合法的起点，直接返回`false`。如果当前位置在哈希表中，表明应该使用$pieces$中对应的那一个数组，检查其是否符合要求即可。

- 时间复杂度$O(N+M)$=$O(N)$。$N$为$arr$的长度。
- 空间复杂度$O(M)$。$M$为$pieces$的长度。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        int n = arr.size(), m = pieces.size();
        unordered_map<int, int> mp;
        for (int i = 0; i < m; ++i)
            mp[pieces[i][0]] = i;
        for (int i = 0; i < n; ++i) {
            if (!mp.count(arr[i]))
                return false;
            int j = mp[arr[i]];
            for (int k = 1; k < pieces[j].size(); ++k) {
                if (arr[i + k] != pieces[j][k])
                    return false;
            }
            i += pieces[j].size() - 1;
        }
        return true;
    }
};
```

:::

## Problem B - [统计字典序元音字符串的数目](https://leetcode-cn.com/problems/count-sorted-vowel-strings/)

### 方法一 动态规划

用$dp[i][j]$表示最后一个字母**不大于**第$j$个元音字母的长度为$i$的字符串数目。显然，我们有转移：

$$
dp[i][j]=dp[i-1][j] + dp[i][j-1]
$$

注意到这一转移式实际只需要用一维数组进行存储，我们可以对空间进行优化。

- 时间复杂度$O(CN)$，本题中$C=5$。
- 空间复杂度$O(C)$。

我们也可以用$dp2[i][j]$表示最后一个字母**恰好为**第$j$个元音字母的长度为$i$的字符串数目，但使用这样的表示方式，将使得转移变为：

$$
dp2[i][j]=\sum_{k=0}^jdp2[i-1][j]
$$

从而时间复杂度为$O(C^2N)$。

事实上，可以注意到，$dp[i][j]=\sum_{k=0}^jdp2[i][k]$，也即方法一中的$dp$数组实际上恰好是方法二中的$dp2$数组的前缀和。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countVowelStrings(int n) {
        vector<int> dp(5, 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= 4; ++j)
                dp[j] += dp[j - 1];
        return dp[4];
    }
};
```

:::

### 方法二 组合计数

在本题中，我们可以写出方程：

$$
a+e+i+o+u=N
$$

其中$a,e,i,o,u$均为非负整数。

不妨令

$$
a'=a+1,e'=e+1,\dots,u'=u+1
$$

则我们有：

$$
a'+e'+i'+o'+u'=N+5
$$

其中$a',e',i',o',u'$均为正整数。

此时我们可以使用隔板法求解，一共$N+4$个间隔，需要放入$4$个搁板，所以最后的答案为${N+4}\choose4$。

::: details 参考代码 （Python 3）

```python
class Solution:
    def countVowelStrings(self, n: int) -> int:
        return math.comb(n + 4, 4)
```

## Problem C - [可以到达的最远建筑](https://leetcode-cn.com/problems/furthest-building-you-can-reach/)

贪心。我们应当首先使用梯子，如果梯子已经用完，我们需要找出之前最小的一个高度差，改为使用砖块。这提示我们使用优先队列来存储每一个大于$0$的高度差。

如果当前砖块的需求量已经超过了供给量，我们应当提前返回答案。

- 时间复杂度$O(N\log N)$。
- 空间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        int need = 0;
        priority_queue<int, vector<int>, greater<>> pq;
        for (int i = 0; i + 1 < n; ++i) {
            int delta = heights[i + 1] - heights[i];
            if (delta <= 0)
                continue;
            pq.push(delta);
            if (pq.size() > ladders) {
                int small = pq.top();
                pq.pop();
                need += small;
                if (need > bricks)
                    return i;
            }
        }
        return n - 1;
    }
};
```

:::

## Problem D - [第 K 条最小指令](https://leetcode-cn.com/problems/kth-smallest-instructions/)

不管我们如何行走，最后的指令中总是包含$row$个`V`和$col$个`H`，所以，我们实际上就是要求，含有$row$个`V`和$col$个`H`的字符串中，字典序第$k$小的那一个。

不妨先设当前的字典序为$1$。每一步我们有两种选择：`H`或`V`（如果某一字母已经用完，则只有一种选择）。如果选择`H`，那么字典序不会增加；但如果选择`V`，则需要计入所有以`H`开头的字符串的数目，这是字典序增加的最小数目。以`H`开头的字符串的数目可以通过组合求解，假设当前剩余$h$个`H`和$v$个`V`，则以`H`开头的字符串的数目为${v+h-1}\choose{h-1}$。我们计算出这一数目后，将当前字典序加上这一数字，如果超过了$k$，则表明我们必须选择`H`；否则我们必须选择`V`。

- 时间复杂度$O(N+M)$。
- 空间复杂度$O(N+M)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def kthSmallestPath(self, destination: List[int], k: int) -> str:
        ans = []
        v, h = destination
        
        fac = [1]
        for i in range(v + h):
            fac.append(fac[-1] * (i + 1))
        def comb(n, k):
            return fac[n] // fac[n - k] // fac[k];
        
        L = 1
        for i in range(v + h):
            if v == 0:
                ans.append('H')
                continue
            if h == 0:
                ans.append('V')
                continue
            left = comb(v + h - 1, h - 1)
            if L + left > k:
                ans.append('H')
                h -= 1
            else:
                ans.append('V')
                L += left
                v -= 1
        return ''.join(ans)
```

:::

<Utterances />
