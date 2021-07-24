# Leetcode 第57场双周赛题解

## Problem A - [检查是否所有字符出现次数相同](https://leetcode-cn.com/problems/check-if-all-characters-have-equal-number-of-occurrences/)

### 方法一：计数

直接计数即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|\sum|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def areOccurrencesEqual(self, s: str) -> bool:
        return len(set(collections.Counter(s).values())) == 1
```

:::


## Problem B - [最小未被占据椅子的编号](https://leetcode-cn.com/problems/the-number-of-the-smallest-unoccupied-chair/)

### 方法一：排序+优先队列

用一个小根堆维护当前未被占据的椅子。将所有的离开和加入事件以`(time, event_type, idx)`的形式记录并排序（注意因为离开的同时椅子就可以被占用，所以这里离开记为`-1`，加入记为`1`，从而排序时会将同一时刻的离开事件优先处理）。按顺序处理事件即可。

- 时间复杂度为$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size();
        priority_queue<int, vector<int>, greater<>> available;
        for (int i = 0; i < n; ++i)
            available.emplace(i);
        vector<tuple<int, int, int>> events;
        for (int i = 0; i < n; ++i) {
            events.emplace_back(times[i][1], -1, i);
            events.emplace_back(times[i][0], 1, i);
        }
        sort(events.begin(), events.end());
        vector<int> seats(n);
        
        for (auto [_time, event_type, idx] : events) {
            if (event_type == 1) {
                seats[idx] = available.top();
                if (idx == targetFriend)
                    return seats[idx];
                available.pop();
            } else {
                available.emplace(seats[idx]);
            }
        }
        
        return -1; // Should not return from here
    }
};
```

:::


## Problem C - [描述绘画结果](https://leetcode-cn.com/problems/describe-the-painting/)

### 方法一：离散化+差分数组

首先，我们对这些区间的端点进行离散化，将它们映射为连续的`1..idx`。之后，我们将每个区间的涂色视为对一个差分数组进行的操作。这样，我们最后就可以由这个差分数组得到整个数轴上每一段区间的颜色值之和。

因为每一个区间的颜色都是独一无二的，所以我们不需要考虑区间合并。直接输出所有非零区间即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        vector<int> endpoints;
        for (auto &segment : segments) {
            endpoints.emplace_back(segment[0]);
            endpoints.emplace_back(segment[1]);
        }
        sort(endpoints.begin(), endpoints.end());
        endpoints.resize(unique(endpoints.begin(), endpoints.end()) - endpoints.begin());
        map<int, int> mp;
        int idx = 1;
        for (int endpoint : endpoints)
            mp[endpoint] = idx++;
        
        vector<long long> diff(idx);
        for (auto &segment : segments) {
            int l = segment[0], r = segment[1], c = segment[2];
            diff[mp[l]] += c, diff[mp[r]] -= c;
        }
        
        vector<vector<long long>> ans;
        long long now = 0;
        for (int i = 1; i < idx; ++i) {
            now += diff[i];
            if (now != 0)
                ans.push_back({endpoints[i - 1], endpoints[i], now});
        }
        
        return ans;
    }
};
```

:::

## Problem D - [队列中可以看到的人数](https://leetcode-cn.com/problems/number-of-visible-people-in-a-queue/)

### 方法一：单调栈

容易发现，一个人向右可以看到的人，他们的身高必然是单调递增的；并且，他所能看到的最后一个人，必定是他右侧第一个比他高的人（对于最后一个人，我们可以假想队伍的最后还有一个身高无限高的隐形人）。

这就提示我们首先用单调栈计算出**每个人右侧第一个高于他的人**。

下一步我们应该如何求解呢？

首先考虑最简单的情形，一个人的右侧紧挨着的那个人就比他高，那么显然他只能看到这一个人。

那么，如果右侧紧挨着的那个人（B）比他（A）矮呢？他可以看到B，并且可以越过B继续向右看。但要注意，他无法看到右侧矮于B的人（他们被B挡住了），因此，如果他还能看到其他人，那么他所能看到的下一个人必定是第一个比B高的人C。假设C比A高，那么到此为止；否则，A还可以越过C继续向右看到第一个比C高的人D，依此类推。

我们直接按照这一思路，迭代找到比A高的那个人就可以得到答案。

有同学可能会担心这样会变为$\mathcal{O}(N^2)$的复杂度，但其实并非如此，因为每个人最多只会有一次作为中间节点被访问到。例如：

`[2,8,7,3,4,6,9]`

这个例子中，处理`7`时，会经历`7->3->4->6->9`的路径，但处理`8`时，对应的这一段路径就被压缩为`7->9`，中间的都被跳过了。

所以最后的复杂度仍然是线性的。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> ans(n), R(n, n);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && heights[st.top()] < heights[i]) {
                R[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        for (int i = n - 2; i >= 0; --i) {
            int r = i + 1;
            while (r < n && heights[r] < heights[i]) {
                ans[i]++;
                r = R[r];
            }
            if (r != n)
                ans[i]++;
        }
        return ans;
    }
};
```

:::

<Utterances />