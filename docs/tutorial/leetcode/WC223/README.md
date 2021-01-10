# Leetcode 第223场周赛题解

## Problem A - [解码异或后的数组](https://leetcode-cn.com/problems/decode-xored-array/)

利用异或的性质逐个求解即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        int n = encoded.size() + 1;
        vector<int> ans(n);
        ans[0] = first;
        for (int i = 1; i < n; ++i)
            ans[i] = ans[i - 1] ^ encoded[i - 1];
        return ans;
    }
};
```

:::

## Problem B - [交换链表中的节点](https://leetcode-cn.com/problems/swapping-nodes-in-a-linked-list/)

直接找到两个节点，交换数值即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        int len = 0;
        ListNode *ptr = head;
        while (ptr) {
            len++;
            ptr = ptr->next;
        }
        auto get_node = [&](int idx) {
            ListNode *ptr = head;
            for (int i = 0; i < idx - 1; ++i)
                ptr = ptr->next;
            return ptr;
        };
        auto left = get_node(k);
        auto right = get_node(len + 1 - k);
        swap(left->val, right->val);
        return head;
    }
};
```

:::

## Problem C - [执行交换操作后的最小汉明距离](https://leetcode-cn.com/problems/minimize-hamming-distance-after-swap-operations/)

利用$allowedSwaps$构建并查集，然后在每一个连通分量内使用哈希表计数，然后贪心匹配即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
struct UnionFind {
  int n;
  vector<int> parent, size;
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
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        UnionFind uf(n);
        for (auto &v : allowedSwaps)
            uf.connect(v[0], v[1]);
        unordered_map<int, vector<int>> groups;
        for (int i = 0; i < n; ++i)
            groups[uf.find(i)].emplace_back(i);
        int same = 0;
        for (auto [root, group] : groups) {
            unordered_map<int, int> sc, tc;
            for (int i : group) {
                sc[source[i]]++;
                tc[target[i]]++;
            }
            for (auto [num, freq] : tc)
                same += min(freq, sc[num]);
        }
        return n - same;
    }
};
```

:::

## Problem D - [完成所有工作的最短时间](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/)

二分+状压DP。DP之前预计算所有子集的和，DP过程中注意使用子集枚举的优化。

- 时间复杂度$\mathcal{O}(3^N\log\sum job_i))$，其中$N$是任务的数量。
- 空间复杂度$\mathcal{O}(2^N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        int lo = *max_element(jobs.begin(), jobs.end());
        int hi = 0;
        for (int job : jobs)
            hi += job;
        vector<int> subsum(1 << n);
        for (int i = 0; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j)
                if (i & (1 << j))
                    subsum[i] += jobs[j];
        }
        auto can = [&](int limit) {
            vector<int> dp(1 << n, 1e9);
            dp[0] = 0;
            for (int i = 0; i < (1 << n); ++i) {
                int rem = ((1 << n) - 1) ^ i;
                for (int j = rem; j; j = (j - 1) & rem)
                    if (subsum[j] <= limit)
                        dp[i ^ j] = min(dp[i ^ j], dp[i] + 1);
            }
            return dp[(1 << n) - 1] <= k;
        };
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (can(mid))
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        return lo;
    }
};
```

:::

<Utterances />
