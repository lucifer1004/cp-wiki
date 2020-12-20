# Leetcode 第220场周赛题解

## Problem A - [重新格式化电话号码](https://leetcode-cn.com/problems/reformat-phone-number/)

按要求模拟即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string reformatNumber(string number) {
        string ans;
        for (char c : number)
            if ('0' <= c && c <= '9')
                ans.push_back(c);
        int len = ans.size();
        string s;
        int rem = len % 3;
        if (rem < 2)
            rem += 3;
        for (int i = 0; i < len - rem; ++i) {
            s.push_back(ans[i]);
            if (i % 3 == 2)
                s.push_back('-');
        }
        if (rem < 4)
            for (int i = len - rem; i < len; ++i)
                s.push_back(ans[i]);
        else {
            s.push_back(ans[len - 4]);
            s.push_back(ans[len - 3]);
            s.push_back('-');
            s.push_back(ans[len - 2]);
            s.push_back(ans[len - 1]);
        }
        return s;
    }
};
```

:::

## Problem B - [删除子数组的最大得分](https://leetcode-cn.com/problems/maximum-erasure-value/)

双指针。用哈希表存储当前窗口内每种数字的个数。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）
```cpp
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        unordered_map<int, int> cnt;
        int l = 0;
        int sum = 0;
        for (int r = 0; r < n; ++r) {
            sum += nums[r];
            cnt[nums[r]]++;
            while (cnt.size() < r - l + 1) {
                sum -= nums[l];
                cnt[nums[l]]--;
                if (cnt[nums[l]] == 0)
                    cnt.erase(nums[l]);
                l++;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
```
:::

## Problem C - [跳跃游戏 VI](https://leetcode-cn.com/problems/jump-game-vi/)

单调队列优化动态规划。在单调队列中降序存储当前位置之前最多$k$个位置的结果。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）
```cpp
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq;
        vector<int> dp(n);
        dp[0] = nums[0];
        dq.push_back(0);
        for (int i = 1; i < n; ++i) {
            while (!dq.empty() && dq.front() < i - k) 
                dq.pop_front();
            dp[i] = dp[dq.front()] + nums[i];
            while (!dq.empty() && dp[dq.back()] <= dp[i])
                dq.pop_back();
            dq.push_back(i);
        }
        return dp[n - 1];
    }
};
```
:::

## Problem D - [检查边长度限制的路径是否存在](https://leetcode-cn.com/problems/checking-existence-of-edge-length-limited-paths/)

离线处理。

所有边按照长度升序排列，同时所有询问也按照长度升序排列。这样我们就可以按照当前询问的限制逐步向图中添加边，从而点的连通性可以通过并查集来维护。

- 时间复杂度$\mathcal{O}(E\log E+Q\log Q+(Q+E)\alpha(N))$，其中$\alpha(N)$为Ackerman函数的反函数。
- 空间复杂度$\mathcal{O}(N+Q)$。

::: details 参考代码（C++）

```cpp
class UnionFind {
  int n;
  vector<int> parent, size;

public:
  UnionFind(int n) {
    this->n = n;
    parent = vector<int>(n);
    size = vector<int>(n, 1);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int idx) {
    if (parent[idx] == idx)
      return idx;
    return parent[idx] = find(parent[idx]);
  }

  void connect(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb) {
      if (size[fa] > size[fb]) {
        parent[fb] = fa;
        size[fa] += size[fb];
      } else {
        parent[fa] = fb;
        size[fb] += size[fa];
      }
    }
  }
};

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        sort(edgeList.begin(), edgeList.end(), [](vector<int> &p, vector<int> &q){
            return p[2] < q[2];
        });
        int q = queries.size();
        vector<bool> ans(q);
        vector<int> order(q);
        for (int i = 0; i < q; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return queries[i][2] < queries[j][2]; 
        });
        UnionFind uf(n);
        int idx = 0;
        for (int i : order) {
            int limit = queries[i][2];
            while (idx < edgeList.size() && edgeList[idx][2] < limit) {
                int u = edgeList[idx][0], v = edgeList[idx][1];
                uf.connect(u, v);
                idx++;
            }
            int u0 = queries[i][0], v0 = queries[i][1];
            if (uf.find(u0) == uf.find(v0))
                ans[i] = true;
        }
        return ans;
    }
};
```

:::

<Utterances />
