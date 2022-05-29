# Leetcode 第243场周赛题解

## Problem A - [检查某单词是否等于两单词之和](https://leetcode.cn/problems/check-if-word-equals-summation-of-two-words/)

### 方法一：模拟

按要求转为整数后计算即可。

- 时间复杂度$\mathcal{O}(|S_1|+|S_2|+|S_3|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
def to_int(s):
    return int(''.join(map(lambda x: str(ord(x) - ord('a')), s)))

class Solution:
    def isSumEqual(self, firstWord: str, secondWord: str, targetWord: str) -> bool:
        return to_int(firstWord) + to_int(secondWord) == to_int(targetWord)
```

:::

## Problem B - [插入后的最大值](https://leetcode.cn/problems/maximum-value-after-insertion/)

### 方法一：贪心

如果原数是正数，那么找到第一个比待插入数字小的位置，将其插入；如果找不到这样的位置，插入到尾部；
如果原数是负数，那么找到第一个比待插入数字大的位置，将其插入；如果找不到这样的位置，插入到尾部。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxValue(self, n: str, x: int) -> str:
        if n[0] == '-':
            for i in range(1, len(n)):
                if int(n[i]) > x:
                    return n[:i] + str(x) + n[i:]
            return n + str(x)
        else:
            for i in range(len(n)):
                if int(n[i]) < x:
                    return n[:i] + str(x) + n[i:]
            return n + str(x)
            
```

:::

## Problem C - [使用服务器处理任务](https://leetcode.cn/problems/process-tasks-using-servers/)

### 方法一：优先队列模拟

使用两个优先队列，第一个队列中存储当前还不可用的服务器，按照可用时间+序号的方式排序；第二个队列中存储当前可用的服务器，按照权重+序号的方式排序。

维护全局的当前时间。如果某一个任务开始时，所有服务器都不可用，则取出所有可用时间与当前最早可用时间一致的服务器，将这些服务器设为可用，同时修改当前时间为最早可用时间。

- 时间复杂度$\mathcal{O}(Q\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    vector<int> assignTasks(vector<int> &servers, vector<int> &tasks) {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq, pq2;
        int n = servers.size();
        for (int i = 0; i < n; ++i)
            pq2.emplace(servers[i], i);

        int q = tasks.size();
        int now = 0;
        vector<int> ans(q);
        for (int i = 0; i < q; ++i) {
            now = max(now, i);
            while (!pq.empty() && pq.top().first <= now) {
                pq2.emplace(servers[pq.top().second], pq.top().second);
                pq.pop();
            }
            if (pq2.empty()) {
                int t = pq.top().first;
                while (!pq.empty() && pq.top().first == t) {
                    pq2.emplace(servers[pq.top().second], pq.top().second);
                    pq.pop();
                }
                now = t;
            }
            auto[w, idx] = pq2.top();
            pq2.pop();
            pq.emplace(now + tasks[i], idx);
            ans[i] = idx;
        }

        return ans;
    }
};
```

:::

## Problem D - [准时抵达会议现场的最小跳过休息次数](https://leetcode.cn/problems/minimum-skips-to-arrive-at-meeting-on-time/)

### 方法一：动态规划

令$f[i]$表示跳过$i$次时的最短时间，则对于每一段路程，我们可以选择跳过（$i\rightarrow i+1$）或不跳过$(i\rightarrow i)$，分别进行转移。

注意这里我们将时间表示为$(t,rem)$的形式，其中$0\le rem<speed$。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        int n = dist.size();
        int sum = 0;
        for (int di : dist)
            sum += di;
        if (1LL * speed * hoursBefore < sum)
            return -1;
        
        auto inf = make_pair(INT_MAX, INT_MAX);
        vector<pair<int, int>> f(n + 1, inf);
        f[0] = make_pair(0, 0);
        for (int di : dist) {
            vector<pair<int, int>> nf(n + 1, inf);
            for (int i = 0; i <= n; ++i) {
                if (f[i] < inf) {
                    auto [t, d] = f[i];
                    nf[i] = min(nf[i], make_pair(t + (d + di - 1) / speed + 1, 0));
                    if (i + 1 <= n)
                        nf[i + 1] = min(nf[i + 1], make_pair(t + (d + di) / speed, (d + di) % speed));
                }
            }
            f = move(nf);
        }
        auto target = make_pair(hoursBefore, 0);
        for (int i = 0; i <= n; ++i)
            if (f[i] <= target)
                return i;
        
        return -1;
    }
};
```

:::

<Utterances />
