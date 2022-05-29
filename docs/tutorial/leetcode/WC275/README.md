# Leetcode 第275场周赛题解

## Problem A - [检查是否每一行每一列都包含全部整数](https://leetcode.cn/problems/check-if-every-row-and-column-contains-all-numbers/)

### 方法一：模拟

按题意检查即可。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def checkValid(self, matrix: List[List[int]]) -> bool:
        n = len(matrix)
        return all(len(set(row)) == n for row in matrix) and all(len(set(col)) == n for col in zip(*matrix))
```

:::

## Problem B - [最少交换次数来组合所有的 1 II](https://leetcode.cn/problems/minimum-swaps-to-group-all-1s-together-ii/)

### 方法一：滑动窗口

统计滑动窗口中 $1$ 的数目即可。注意这里的滑动窗口可以从数组结尾连接到开头。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        int total_ones = 0;
        for (int num : nums)
            total_ones += num;
        
        int current_ones = 0;
        for (int i = 0; i < total_ones; ++i)
            current_ones += nums[i];
        int max_ones_in_a_seg = current_ones;
        for (int i = 1; i < n; ++i) {
            current_ones += nums[(i - 1 + total_ones) % n] - nums[i - 1];
            max_ones_in_a_seg = max(max_ones_in_a_seg, current_ones);
        }
        
        return total_ones - max_ones_in_a_seg;
    }
};
```

:::

## Problem C - [统计追加字母可以获得的单词数](https://leetcode.cn/problems/count-words-obtained-after-adding-a-letter/)

### 方法一：枚举删除的字母

因为所有单词都不包含重复字母，所以我们可以将它们全都转换成二进制数表示。

我们将`startWords`中的单词构建成一个集合，然后对于`targetWords`中的单词，我们枚举删除的字母，判断删除之后的结果是否在集合中。

- 时间复杂度$\mathcal{O}((N+M)|\sum|)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        unordered_set<int> has;
        for (auto &word : startWords) {
            int num = 0;
            for (char ch : word)
                num ^= 1 << (ch - 'a');
            has.insert(num);
        }
        
        int ans = 0;
        for (auto &word : targetWords) {
            int num = 0;
            for (char ch : word)
                num ^= 1 << (ch - 'a');
            for (char ch : word)
                if (has.count(num ^ (1 << (ch - 'a')))) {
                    ans++;
                    break;
                }
        }
        
        return ans;
    }
};
```

:::

## Problem D - [全部开花的最早一天](https://leetcode.cn/problems/earliest-possible-day-of-full-bloom/)

### 方法一：贪心

先种生长时间长的，再种生长时间短的。

> 为什么这一贪心是正确的？

对于任意两盆花，假设第一盆的种植和生长时间为 $(a, b)$，第二盆的种植和生长时间为 $(c,d)$，且有 $b>d$。

暂时不考虑交错种植的情况。

- 先种一，再种二：总时间为 $\max(a+b, a+c+d)$
- 先种二，再种一：总时间为 $\max(c+d,c+a+b)$。因为 $c+a+b>c+a+d>c+d$，所以结果就为 $c+a+b$。

二者对比，显然有 $c+a+b>c+a+d$ 且 $c+a+b>a+b$。所以应该先种一。

下面考虑交错种植。我们可以发现，无论是几盆花发生交错，交错种植并不能让种植结束时间提前。所以在存在交错种植的情况下，我们总是可以按照种植结束时间的顺序，以无交错的方式进行种植，此时所有花的种植结束时间均不会比原来延后。在这样的情况下，结合上面的讨论，就说明我们的贪心策略确实是最优的。

- 时间复杂度$\mathcal{O}(N\log N)$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int n = plantTime.size();
        vector<int> order(n);
        for (int i = 0; i < n; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return growTime[i] > growTime[j]; 
        });
        
        int ans = 0, day = 0;
        for (int i : order) {
            day += plantTime[i];
            ans = max(ans, day + growTime[i]);
        }
        return ans;
    }
};
```

:::

<Utterances />
