# Leetcode 第36场双周赛题解

## Problem A - [设计停车系统](https://leetcode-cn.com/problems/design-parking-system/)

用一个数组记录三种规格的剩余车位数量即可。

单次操作的时间复杂度为$O(1)$。

::: details 参考代码（C++）

```cpp
class ParkingSystem {
    vector<int> rem;
public:
    ParkingSystem(int big, int medium, int small) {
        rem = vector<int>{big, medium, small};
    }
    
    bool addCar(int carType) {
        return (rem[--carType]-- > 0);
    }
};
```

:::

## Problem B - [警告一小时内使用相同员工卡大于等于三次的人](https://leetcode-cn.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/)

按人名重新整理记录，每个人的记录排序后，依次判断第$i$和第$i+2$条记录的时间差是否在一小时之内。

时间复杂度$O(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
    int to_int(string s) {
        int hh = stoi(s.substr(0, 2));
        int mm = stoi(s.substr(3, 2));
        return hh * 60 + mm;
    }
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        set<string> invalid;
        unordered_map<string, vector<int>> mp;
        for (int i = 0; i < keyName.size(); ++i)
            mp[keyName[i]].emplace_back(to_int(keyTime[i]));
        for (auto p : mp) {
            auto &v = p.second;
            sort(v.begin(), v.end());
            for (int i = 0; i + 2 < v.size(); ++i) {
                if (v[i + 2] - v[i] <= 60) {
                    invalid.insert(p.first);
                    break;
                }
            }
        }
        return vector<string>(invalid.begin(), invalid.end());
    }
};
```

:::

## Problem C - [给定行和列的和求可行矩阵](https://leetcode-cn.com/problems/find-valid-matrix-given-row-and-column-sums/)

将第$i$行第$j$列设为$\min(row[i], col[j])$，同时更新$row[i]$和$col[j]$即可。

为什么这一贪心策略是正确的呢？

其实很简单。我们首先考虑第一行，显然有$row[0]\leq\sum_j col[j]$，因此在经过上述操作后，一定能使得$row[0]=0$。同时，因为每次我们取得是$\min(row[0], col[j])$，所以操作后，一定仍满足$\forall j,col[j]\geq0$。这样，我们就把原问题变成了$N-1$行，$M$列的新问题。依次类推，我们就一定能够得到一组可行解。

时间复杂度$O(NM)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int n = rowSum.size(), m = colSum.size();
        vector<vector<int>> ans(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans[i][j] = min(rowSum[i], colSum[j]);
                rowSum[i] -= ans[i][j];
                colSum[j] -= ans[i][j];
            }
        }
        return ans;
    }
};
```

:::

## Problem D - [找到处理最多请求的服务器](https://leetcode-cn.com/problems/find-servers-that-handled-most-number-of-requests/)

数据结构题。用一个`set`记录当前空闲的服务器，使用按照结束时间排序的小根堆（`priority_queue`）记录进行中的任务，然后依次处理任务。在开始一个任务之前，先将小根堆中结束时间不晚于当前时间的任务取出，然后归还它们所占用的服务器。接下来，如果当前有空闲服务器，利用`lower_bound`找出符合条件的第一个（也即$\geq i\%k$的第一个服务器，如果`lower_bound`找到了末端，则应该使用下一个，也即`set`中的第一个服务器），然后将任务加入小根堆中。

时间复杂度$O(N\log N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        int n = arrival.size();
        vector<int> cnt(k);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        set<int> vac;
        for (int i = 0; i < k; ++i)
            vac.insert(i);
        for (int i = 0; i < n; ++i) {
            while (!pq.empty() && pq.top().first <= arrival[i]) {
                int pos = pq.top().second;
                pq.pop();
                vac.insert(pos);
            }
            int pos = -1;
            auto it = vac.lower_bound(i % k);
            if (it == vac.end())
                it = vac.begin();
            if (it != vac.end()) {
                pos = *it;
                vac.erase(it);
            }
            if (pos != -1) {
                cnt[pos]++;
                pq.emplace(arrival[i] + load[i], pos);
            }
        }
    
        
        int hi = 0;
        vector<int> ans;
        for (int i = 0; i < k; ++i) {
            if (cnt[i] > hi) {
                ans.clear();
                hi = cnt[i];
            }
            if (cnt[i] == hi)
                ans.emplace_back(i);
        }
        
        return ans;
    }
};
```

:::

<Utterances />
