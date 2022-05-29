# Leetcode 第285场周赛题解

## Problem A - [由单个字符重复的最长子字符串](https://leetcode.cn/problems/longest-substring-of-one-repeating-character/)

### 方法一：去重后计数

将连续的重复元素压缩后暴力检查每个位置是否符合要求。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countHillValley(self, nums: List[int]) -> int:
        s = []
        for num in nums:
            if len(s) == 0 or num != s[-1]:
                s.append(num)
        n = len(s)
        print(s)
        ans = 0
        for i in range(1, n - 1):
            l = i - 1
            r = i + 1
            if (s[l] < s[i] and s[r] < s[i]) or (s[l] > s[i] and s[r] > s[i]):
                ans += 1
        return ans
```

:::

## Problem B - [统计道路上的碰撞次数](https://leetcode.cn/problems/count-collisions-on-a-road/)

### 方法一：脑筋急转弯

去掉最左边的连续的 `L` 和最右边的连续的 `R`，剩下的非 `S` 元素的个数就是碰撞次数。

- 时间复杂度 $\mathcal{O}(|S|)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countCollisions(string directions) {
        string s = directions;
        int st = 0;
        for (char ch : directions)
            if (ch == 'S')
                st++;
        int n = s.size();
        int l = 0;
        while (l < n && s[l] == 'L')
            l++;
        int r = n - 1;
        while (r >= 0 && s[r] == 'R')
            r--;
        return max(0, r - l + 1 - st);
    }
};
```

:::

## Problem C - [射箭比赛中的最大得分](https://leetcode.cn/problems/maximum-points-in-an-archery-competition/)

### 方法一：贪心+枚举

枚举 Bob 最后得分的位置即可。

- 时间复杂度 $\mathcal{O}(N\cdot2^N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        int n = aliceArrows.size();
        int best = 0;
        int best_state = 0;
        for (int i = 1; i < (1 << n); ++i) {
            int sum = 0, score = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j))
                    sum += aliceArrows[j] + 1, score += j;
            }
            if (sum <= numArrows && score > best)
                best = score, best_state = i;
        }
        int tot = numArrows;
        vector<int> bobArrows(n);
        for (int j = 0; j < n; ++j)
            if (best_state & (1 << j))
                bobArrows[j] = aliceArrows[j] + 1, tot -= aliceArrows[j] + 1;
        bobArrows[n - 1] += tot;
        return bobArrows;
    }
};
```

:::

## Problem D - [由单个字符重复的最长子字符串](https://leetcode.cn/problems/longest-substring-of-one-repeating-character/)

### 方法一：维护每个字母的连续段

用区间 `set` 维护每个字母的连续段，并用 `multiset` 维护每个字母的最长段的长度。

- 时间复杂度 $\mathcal{O}(N\log N + Q(\log N+|\Sigma|))$。
- 空间复杂度 $\mathcal{O}(N+Q)$。

::: details 参考代码（C++）

```cpp
struct SegPool {
    set<pair<int, int>> segs;
    multiset<int> length;
    
    void insert_seg(int l, int r) {
        segs.emplace(l, r);
        length.emplace(r - l + 1);
    }
    
    int max_len() {
        if (segs.empty())
            return 0;
        return *length.rbegin();
    }
    
    void remove_at(int id) {
        auto it = segs.lower_bound(make_pair(id, INT_MAX));
        it--;
        auto [l, r] = *it;
        segs.erase(it);
        length.erase(length.find(r - l + 1));
        if (l < id)
            segs.emplace(l, id - 1);
        length.emplace(id - l);
        if (id < r)
            segs.emplace(id + 1, r);
        length.emplace(r - id);
    }
    
    void insert_at(int id) {
        auto it = segs.lower_bound(make_pair(id, INT_MAX));
        int l = id, r = id;
        
        vector<pair<int, int>> to_remove;
        if (it != segs.end() && it->first == id + 1) {
            auto [rl, rr] = *it;
            to_remove.emplace_back(rl, rr);
            length.erase(length.find(rr - rl + 1));
            r = rr;
        }
        
        if (it != segs.begin() && prev(it)->second == id - 1) {
            auto [ll, lr] = *prev(it);
            to_remove.emplace_back(ll, lr);
            length.erase(length.find(lr - ll + 1));
            l = ll;
        }
        
        for (auto p : to_remove)
            segs.erase(p);
        segs.emplace(l, r);
        length.emplace(r - l + 1);
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        vector<SegPool> pools(26);
        
        int n = s.size();
        for (char c = 'a'; c <= 'z'; ++c) {
            vector<int> pos;
            for (int i = 0; i < n; ++i)
                if (s[i] == c)
                    pos.push_back(i);
            int l = -2, r = -2;
            for (int p : pos) {
                if (p > r + 1) {
                    if (l != -2)
                        pools[c - 'a'].insert_seg(l, r);
                    l = r = p;
                } else
                    r++;
            }
            if (l != -2)
                pools[c - 'a'].insert_seg(l, r);
        }
        
        int q = queryCharacters.size();
        int last = 0;
        for (int j = 0; j < 26; ++j)
            last = max(last, pools[j].max_len());
        
        vector<int> ans(q);
        for (int i = 0; i < q; ++i) {
            int ci = queryCharacters[i] - 'a';
            int id = queryIndices[i];
            if (s[id] - 'a' == ci) {
                ans[i] = last;
                continue;
            }
            pools[s[id] - 'a'].remove_at(id);
            pools[ci].insert_at(id);
            s[id] = queryCharacters[i];
            for (int j = 0; j < 26; ++j)
                last = ans[i] = max(ans[i], pools[j].max_len());
        }
        
        return ans;
    }
};
```

:::

<Utterances />
