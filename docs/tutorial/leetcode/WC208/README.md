# Leetcode 第208场周赛题解

## Problem A - [文件夹操作日志搜集器](https://leetcode-cn.com/problems/crawler-log-folder/)

因为说了没有非法操作，所以不需要关心当前路径名，只要保存当前的深度就可以了。

时间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth = 0;
        for (auto s : logs) {
            if (s == "./")
                continue;
            if (s == "../")
                depth = max(0, depth - 1);
            else 
                depth++;
        }
        return depth;
    }
};
```

:::

## Problem B - [经营摩天轮的最大利润](https://leetcode-cn.com/problems/maximum-profit-of-operating-a-centennial-wheel/)

阅读理解题。读懂题目后，一直模拟到所有游客都登上摩天轮，记录每一轮转后的利润的最大值即可。

总时间复杂度$O(\sum customers[i])$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int hi = INT_MIN;
        int profit = 0, rem = 0, idx = -1;
        int turn = 0;
        for (int c : customers) {
            turn++;
            profit -= runningCost;
            rem += c;
            int b = min(4, rem);
            profit += b * boardingCost;
            rem -= b;
            if (hi < profit) {
                hi = profit;
                idx = turn;
            }
                
        }
        while (rem) {
            turn++;
            int b = min(4, rem);
            rem -= b;
            profit += b * boardingCost - runningCost;
            if (hi < profit) {
                hi = profit;
                idx = turn;
            }
        }
        return hi > 0 ? idx : -1;
    }
};
```

:::

## Problem C - [皇位继承顺序](https://leetcode-cn.com/problems/throne-inheritance/)

阅读理解题。因为`getInheritanceOrder`最多调用10次，所以不需要什么复杂数据结构，直接把树建出来，每次DFS即可。

各操作的时间复杂度

- `birth`：$O(1)$
- `death`：$O(1)$
- `getInheritanceOrder`：$O(N)$

::: details 参考代码（C++）

```cpp
class ThroneInheritance {
    unordered_map<string, vector<string>> children;
    unordered_set<string> dead;
    string king;
    vector<string> order;
    void dfs(string u) {
        if (!dead.count(u))
            order.emplace_back(u);
        for (string v : children[u])
            dfs(v);
    }
public:
    ThroneInheritance(string kingName) {
        king = kingName;
        children[kingName] = {};
    }

    void birth(string parentName, string childName) {
        children[parentName].emplace_back(childName);
    }

    void death(string name) {
        dead.insert(name);
    }

    vector<string> getInheritanceOrder() {
        order.clear();
        dfs(king);
        return order;
    }
};
```

:::

## Problem D - [最多可达成的换楼请求数目](https://leetcode-cn.com/problems/maximum-number-of-achievable-transfer-requests/)

考虑到数据范围，直接用二进制枚举所有方案即可。

总时间复杂度为$O((N+M)\cdot2^M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int m = requests.size();
        int ans = 0;
        for (int i = 1; i < (1 << m); ++i) {
            int c = __builtin_popcount(i);
            if (c <= ans)
                continue;
            vector<int> delta(n);
            for (int j = 0; j < m; ++j) {
                if (!(i & (1 << j)))
                    continue;
                delta[requests[j][0]]--;
                delta[requests[j][1]]++;
            }
            bool ok = true;
            for (int j : delta)
                if (j != 0) {
                    ok = false;
                    break;
                }
            if (ok)
                ans = max(ans, c);
        }
        return ans;
    }
};
```

:::

<Utterances />
