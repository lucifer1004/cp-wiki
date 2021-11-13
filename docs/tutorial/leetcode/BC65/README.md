# Leetcode 第65场双周赛题解

## Problem A - [检查两个字符串是否几乎相等](https://leetcode-cn.com/problems/check-whether-two-strings-are-almost-equivalent/)

### 方法一：模拟

按要求计数并判断即可。

- 时间复杂度$\mathcal{O}(|S_1|+|S_2|)$。
- 空间复杂度$\mathcal{O}(|\sum|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def checkAlmostEquivalent(self, word1: str, word2: str) -> bool:
        cnt1 = collections.Counter(word1)
        cnt2 = collections.Counter(word2)
        return all(abs(cnt1[key] - cnt2[key]) <= 3 for key in set(cnt1.keys()) | set(cnt2.keys()))
```

:::


## Problem B - [模拟行走机器人 II](https://leetcode-cn.com/problems/walking-robot-simulation-ii/)

### 方法一：优化模拟

容易发现，机器人只会走最外圈的格子。所以我们把所有最外圈格子的坐标和方向都记录下来，之后只要记录一个下标即可。

需要注意的是$(0,0)$这个格子，在一开始没有移动过的时候，它的朝向是`East`。但之后如果停在$(0,0)$，朝向一定是`South`。因此需要特判一下当前是否移动过。

- 初始化时间复杂度为$\mathcal{O}(W+H)$，其余操作时间复杂度为$\mathcal{O}(1)$。
- 空间复杂度$\mathcal{O}(W+H)$。

::: details 参考代码（C++）

```cpp
const string dirs[4] = {"East", "North", "West", "South"};

class Robot {
    bool _moved;
    int _pos, _n;
    vector<int> _x, _y, _d;
public:
    Robot(int width, int height) {
        _moved = false;
        _n = (width + height - 2) * 2;
        _pos = 0;
        _x = vector<int>(_n);
        _y = vector<int>(_n);
        _d = vector<int>(_n);
        
        int x = 0, y = 0, i = 0;
        _d[0] = 3;
        for (int j = 1; j < width; ++j) {
            x++, i++;
            _x[i] = x, _y[i] = y, _d[i] = 0;
        }
        for (int j = 1; j < height; ++j) {
            y++, i++;
            _x[i] = x, _y[i] = y, _d[i] = 1;
        }
        for (int j = 1; j < width; ++j) {
            i++, x--;
            _x[i] = x, _y[i] = y, _d[i] = 2;
        }
        for (int j = 1; j < height - 1; ++j) {
            i++, y--;
            _x[i] = x, _y[i] = y, _d[i] = 3;
        }
    }
    
    void move(int num) {
        _moved = true;
        _pos = (_pos + num) % _n;
    }
    
    vector<int> getPos() {
        return {_x[_pos], _y[_pos]};
    }
    
    string getDir() {
        if (!_moved)
            return dirs[0];
        
        return dirs[_d[_pos]];
    }
};
```

:::

## Problem C - [每一个查询的最大美丽值](https://leetcode-cn.com/problems/most-beautiful-item-for-each-query/)

### 方法一：离线

标准的离线查询题。将所有物品和查询都按照价格升序排列，然后依次处理查询。

- 时间复杂度$\mathcal{O}(N\log N+Q\log Q)$。
- 空间复杂度$\mathcal{O}(Q)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        int n = items.size(), q = queries.size();
        vector<int> ans(q);
        vector<int> order(q);
        for (int i = 0; i < q; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return queries[i] < queries[j]; 
        });
        sort(items.begin(), items.end());
        int hi = 0, ptr = -1;
        for (int i : order) {
            while (ptr + 1 < n && items[ptr + 1][0] <= queries[i]) 
                hi = max(hi, items[++ptr][1]);
            ans[i] = hi;
        }
        return ans;
    }
};
```

:::

## Problem D - [你可以安排的最多任务数目](https://leetcode-cn.com/problems/maximum-number-of-tasks-you-can-assign/)

### 方法一：二分答案+贪心

本题显然具有决策单调性：如果能安排$K$个任务，一定能安排$K-1$个任务；如果不能安排$K$个任务，一定不能安排$K+1$个任务，因此可以二分答案。

现在考虑安排$K$个任务。显然，我们应该选择最容易的$K$个任务，同时选择最强的$K$个人。

我们从难到易来考虑这$K$个任务。

一种贪心策略是：

- 如果有人能完成当前任务，我们就安排其中能力值最小的那个人去做这一任务。
- 如果没有人能完成当前任务，但当前有药，并且有人能在服药后完成这一任务，我们就安排其中能力值最小的那个人去做这一任务。
- 否则说明无法完成$K$个任务。

另一种贪心策略是：

- 如果当前有药，我们就安排服药后能够完成任务的人中能力值最小的那个人去做这一任务。但要注意这个人可能不吃药也能完成任务，此时就不必吃药了。
- 如果当前没有药，我们就安排能完成任务的人中能力值最小的那个人去做这一任务。
- 否则说明无法完成$K$个任务。

这两种贪心策略都是正确的。我们可以这样考虑：在有药丸的情况下，可能会存在A服药能完成任务，B不服药也能完成任务这样的情形。此时我们应该选择谁呢？实际上，因为后面的任务只会更简单，所以A+药或B都一定能完成后面的任务，因此此时使用A+药或使用B其实对后面的任务没有影响。

- 时间复杂度$\mathcal{O}(N\log^2N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int n = tasks.size(), m = workers.size();
        
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        
        auto check = [&](int k) {
            if (m < k)
                return false;
            
            multiset<int> ms(workers.rbegin(), workers.rbegin() + k);
            int rem = pills;
            for (int i = k - 1; i >= 0; --i) {
                // 贪心策略1
                auto it = ms.lower_bound(tasks[i]);
                if (it == ms.end()) {
                    if (rem == 0)
                        return false;
                    it = ms.lower_bound(tasks[i] - strength);
                    if (it == ms.end())
                        return false;
                    rem--;
                    ms.erase(it);
                } else {
                    ms.erase(it);
                }
                
                // 贪心策略2
                // if (rem) {
                //     auto it = ms.lower_bound(tasks[i] - strength);
                //     if (it == ms.end())
                //         return false;
                //     if (*it < tasks[i])
                //         rem--;
                //     ms.erase(it);
                // } else {
                //     auto it = ms.lower_bound(tasks[i]);
                //     if (it == ms.end())
                //         return false;
                //     ms.erase(it);
                // }
            }
            
            return true;
        };
        
        int lo = 1, hi = n;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
                        
            if (check(mid))
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        
        return hi;
    }
};
```

:::

### 方法二：单调队列

在二分的大框架下，我们也可以从弱到强来考虑选出的$K$个工人。

显然，每个工人都必须做一个任务，否则总共做不到$K$个。对于第$i$个工人，我们将所有难度值不超过$workers[i] + strength$的任务维护在一个双端队列中。由于我们已经对任务进行排序，这个队列天然就是一个单调队列。

- 首先考虑这个工人不吃药的情况。此时我们看队列最前面，也即当前最容易的任务是否能够被完成。如果可以，则让该工人做这个最容易的任务。因为任务是必须要做的，而后面的人能力都比当前这个人要强，所以安排当前这个人来做任务是不亏的。
- 如果他不吃药就做不了任务，那就必须吃药。吃药之后，我们应该让他做当前最难的任务，也即队尾的任务。
- 如果吃了药也做不了任何任务，则说明无法完成$K$个任务。

这样，时间复杂度就优化掉了一个log。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

> 参考了[@灵剑2012](https://leetcode-cn.com/problems/maximum-number-of-tasks-you-can-assign/solution/ji-yu-er-fen-dan-diao-dui-lie-de-onlogns-zy8q/)的题解。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int n = tasks.size(), m = workers.size();
        
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        
        auto check = [&](int k) {
            if (m < k)
                return false;
 
            int ptr = -1, rem = pills;
            deque<int> dq;
            for (int i = m - k; i < m; ++i) {
                while (ptr + 1 < k && tasks[ptr + 1] <= workers[i] + strength)
                    dq.push_back(tasks[++ptr]);
                if (dq.empty())
                    return false;
                if (dq.front() <= workers[i])
                    dq.pop_front();
                else if (rem > 0) {
                    rem--;
                    dq.pop_back();
                } else 
                    return false;
            }

            return true;
        };
        
        int lo = 1, hi = n;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
                        
            if (check(mid))
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        
        return hi;
    }
};
```

:::

<Utterances />
