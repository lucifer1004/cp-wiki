# Leetcode 第47场双周赛题解

- [视频题解-Bilibili](https://www.bilibili.com/video/BV12p4y1H72G/)
- [实况录像-Bilibili](https://www.bilibili.com/video/BV1CV411v7Tt/)

## Problem A - [找到最近的有相同 X 或 Y 坐标的点](https://leetcode.cn/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/)

模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int ans = -1;
        int best = 100000;
        for (int i = 0;i < points.size(); ++i) {
            int xi = points[i][0], yi = points[i][1];
            if (xi == x && abs(yi - y) < best) {
                best = abs(yi - y);
                ans = i;
            }
            if (yi == y && abs(xi - x) < best) {
                best = abs(xi - x);
                ans = i;
            }
        }
        return ans;
    }
};
```

:::

## Problem B - [判断一个数字是否可以表示成三的幂的和](https://leetcode.cn/problems/check-if-number-is-a-sum-of-powers-of-three/)

从最大的3的幂开始，如果大于等于剩余数字，就应当使用这一幂次（因为剩下的所有幂次加起来也比它小）。看最后是否能减到0。

- 时间复杂度$\mathcal{O}(\log_3N)$。
- 空间复杂度$\mathcal{O}(\log_3N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool checkPowersOfThree(int n) {
        vector<int> threes{1};
        while (threes.back() < n)
            threes.emplace_back(threes.back() * 3);
        for (int i = threes.size() - 1; i >= 0; --i) {
            if (n >= threes[i])
                n -= threes[i];
        }
        return n == 0;
    }
};
```

:::

## Problem C - [所有子字符串美丽值之和](https://leetcode.cn/problems/sum-of-beauty-of-all-substrings/)

枚举子串起点，用`multiset`维护不同字符的出现频次。

- 时间复杂度$\mathcal{O}(N^2\log |\sum|)$
- 空间复杂度$\mathcal{O}(N+|\sum|)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int beautySum(string s) {
        int ans = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            multiset<int> st;
            vector<int> cnt(26);
            for (int j = i; j < n; ++j) {
                int c = s[j] - 'a';
                if (st.find(cnt[c]) != st.end())
                    st.erase(st.find(cnt[c]));
                st.insert(++cnt[c]);
                ans += *st.rbegin() - *st.begin();
            }
        }
        return ans;
    }
};
```

:::

## Problem D - [统计点对的数目](https://leetcode.cn/problems/count-pairs-of-nodes/)

先假设$(a,b)$的公共边可以计算两次，这时可以对度数排序后双指针求解。

再考虑删去无效点对。一个点对应该被删去，当且仅当：

- $deg[a]+deg[b]>target$
- 同时$deg[a]+deg[b]-cnt[(a,b)]\leq target$

- 时间复杂度$\mathcal{O}(V\log V+VQ+EQ)$
- 空间复杂度$\mathcal{O}(E+V+Q)$

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        int q = queries.size();
        vector<int> deg(n + 1);
        unordered_map<int, int> cnt;
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1];
            if (u > v)
                swap(u, v);
            cnt[u * (n + 1) + v]++;
            deg[u]++;
            deg[v]++;
        }
        vector<int> s(deg);
        sort(s.begin(), s.end());
        vector<int> ans(q);
        for (int i = 0; i < q; ++i) {
            int target = queries[i];
            int r = n;
            for (int l = 1; l < n; ++l) {
                r = max(r, l + 1);
                while (r - 1 > l && s[l] + s[r - 1] > target)
                    r--;
                if (s[l] + s[r] > target)
                    ans[i] += n - r + 1;
            }
            for (auto [key, val] : cnt) {
                int u = key / (n + 1), v = key % (n + 1);
                if (deg[u] + deg[v] > target && deg[u] + deg[v] - val <= target)
                    ans[i]--;
            }
        }
        return ans;
    }
};
```

:::

<Utterances />
