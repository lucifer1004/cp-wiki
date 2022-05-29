# Leetcode 第216场周赛题解

## Problem A - [检查两个字符串数组是否相等](https://leetcode.cn/problems/check-if-two-string-arrays-are-equivalent/)

没啥可说的，Python大法好。

- 时间复杂度$O(\sum|word1|+\sum|word2|)$。
- 空间复杂度$O(\sum|word1|+\sum|word2|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def arrayStringsAreEqual(self, word1: List[str], word2: List[str]) -> bool:
        return ''.join(word1) == ''.join(word2)
```

:::

## Problem B - [具有给定数值的最小字符串](https://leetcode.cn/problems/smallest-string-with-a-given-numeric-value/)

贪心，如果当前能设为`'a'`就设为`'a'`，如果不能的话（会导致后面全放`'z'`和也不够），就假设后面已经都放了`'z'`，然后给当前位置放剩下的那个字母。

- 时间复杂度$O(N)$。
- 空间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string getSmallestString(int n, int k) {
        string s;
        while (n > 0) {
            if ((k - 1) <= 26 * (n - 1))
                s.push_back('a'), k--;
            else {
                char c = 'a' + k - 1 - 26 * (n - 1);
                s.push_back(c);
                k -= c - 'a' + 1;
            }
            n--;
        }
        return s;
    }
};      
```

:::

## Problem C - [生成平衡数组的方案数](https://leetcode.cn/problems/ways-to-make-a-fair-array/)

分别计算奇数和偶数位置的前缀和，然后枚举删除的元素即可。

- 时间复杂度$O(N)$。
- 空间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        vector<int> odd(n + 1), even(n + 1);
        for (int i = 0; i < n; ++i) {
            even[i + 1] = even[i], odd[i + 1] = odd[i];
            if (i % 2 == 0)
                even[i + 1] += nums[i];
            else
                odd[i + 1] += nums[i];
        }
        for (int i = 0; i < n; ++i) {
            int osum, esum;
            if (i % 2 == 0) {
                osum = odd[i + 1] + even[n] - even[i + 1];
                esum = even[i] + odd[n] - odd[i + 1];
            } else {
                osum = odd[i] + even[n] - even[i + 1];
                esum = even[i] + odd[n] - odd[i + 1];
            }
            if (osum == esum)
                ans++;
        }
        return ans;
    }
};
```

:::

## Problem D - [完成所有任务的最少初始能量](https://leetcode.cn/problems/minimum-initial-energy-to-finish-tasks/)

贪心。我们希望最后的剩余最小，所以就按照剩余能量（$minimum-actual$）从大到小排序，优先进行剩余能量大的任务，这样最后的剩余就会最小。

- 时间复杂度$O(N\log N)$。我们进行了排序。
- 空间复杂度$O(1)$。我们只使用了常数的额外空间。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        int n = tasks.size();
        sort(tasks.begin(), tasks.end(), [](vector<int> &p, vector<int> &q) {
            return p[1] - p[0] > q[1] - q[0] || (p[1] - p[0] == q[1] - q[0] && p[1] > q[1]); 
        });
        int ans = 0, curr = 0;
        for (auto &task : tasks) {
            if (curr < task[1]) {
                ans += task[1] - curr;
                curr = task[1];
            }
            curr -= task[0];
        }
        return ans;
    }
};
```

:::

<Utterances />
