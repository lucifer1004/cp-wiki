# Leetcode 第237场周赛题解

## Problem A - [判断句子是否为全字母句](https://leetcode.cn/problems/check-if-the-sentence-is-pangram/)

去重后看个数是否为26即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def checkIfPangram(self, sentence: str) -> bool:
        return len(set(list(sentence))) == 26
```

:::

## Problem B - [雪糕的最大数量](https://leetcode.cn/problems/maximum-ice-cream-bars/)

排序后贪心即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxIceCream(self, costs: List[int], coins: int) -> int:
        costs.sort()
        ans = 0
        for cost in costs:
            if coins < cost:
                return ans
            coins -= cost
            ans += 1
        return ans
```

:::

## Problem C - [单线程 CPU](https://leetcode.cn/problems/single-threaded-cpu/)

读清题意后按要求模拟即可。把所有任务按开始时间排序，同时用优先队列维护当前待执行的任务。

- 如果下一个任务的开始时间的小于当前CPU时间，且队列非空，则逐个执行队列中的任务，直到当前时间超过下一个任务的开始时间或CPU空闲。
- 此时，或者当前CPU时间已经超过下一个任务的开始时间；或者下一个任务前的所有任务都已执行完毕。无论何种情况，我们都应该将下一个时间点开始的所有任务加入优先队列中。

复杂度：
- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        vector<int> ans;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        map<int, vector<int>> mp;
        int n = tasks.size();
        for (int i = 0; i < n; ++i)
            mp[tasks[i][0]].emplace_back(i);
        int now = 0;
        
        for (auto [t, v] : mp) {
            while (now < t && !pq.empty()) {
                auto [duration, idx] = pq.top();
                pq.pop();
                ans.emplace_back(idx);
                now += duration;
            }
            now = max(now, t);
            for (int i : v) 
                pq.emplace(tasks[i][1], i);
        }
        
        while (!pq.empty()) {
            ans.emplace_back(pq.top().second);
            pq.pop();
        }
        
        return ans;
    }
};
```

:::

## Problem D - [所有数对按位与结果的异或和](https://leetcode.cn/problems/find-xor-sum-of-all-pairs-bitwise-and/)

### 方法一：逐位处理

我们可以逐位计算结果，而不会影响最终的答案。因此，我们可以把两个数组都视为0-1数组（就每一位而言）。

显然，这一位在最终结果中为0还是为1，取决于有多少个1-1对。如果1-1对的数目为奇数，结果中为1，否则为0。

- 时间复杂度$\mathcal{O}((N+M)W)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int ans = 0;
        for (int i = 0; i < 31; ++i) {
            int msk = 1 << i, c1 = 0, c2 = 0;
            for (int num : arr1)
                if (num & msk)
                    c1++;
            for (int num : arr2)
                if (num & msk)
                    c2++;
            if (1LL * c1 * c2 % 2 == 1)
                ans ^= msk;
        }
        return ans;
    }
};
```

:::

### 方法二：利用分配律

我们可以利用xor和and之间的分配律：

(a xor b) and c = (a and c) xor (b and c)

来简化求解。

原式最终可以被化简为：

(a_1 xor a_2 xor … xor a_n) and (b_1 xor b_2 xor … xor b_m)

从而容易求得。

- 时间复杂度$\mathcal{O}(N+M)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int a1 = 0, a2 = 0;
        for (int num : arr1)
            a1 ^= num;
        for (int num : arr2)
            a2 ^= num;
        return a1 & a2;
    }
};
```

:::


<Utterances />
