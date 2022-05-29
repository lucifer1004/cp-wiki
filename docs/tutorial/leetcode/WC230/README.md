# Leetcode 第230场周赛题解

## Problem A - [统计匹配检索规则的物品数量](https://leetcode.cn/problems/count-items-matching-a-rule/)

按要求模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        int ans = 0;
        int n = items.size();
        unordered_map<string, int> mp = {{"type", 0}, {"color", 1}, {"name", 2}};
        int key = mp[ruleKey];
        for (int i = 0; i < n; ++i)
            if (items[i][key] == ruleValue)
                ans++;
        return ans;
    }
};
```

:::

## Problem B - [最接近目标价格的甜点成本](https://leetcode.cn/problems/closest-dessert-cost/)

本题数据范围很小，暴力枚举辅料组合就可以通过，但时间复杂度为指数级。

把问题转化为背包问题，可以将时间复杂度降低到多项式级别。

- 因为每种辅料最多可以用两次，所以直接把每种辅料变成两个。
- 基料必须且只能选一种，可以首先处理好。
 
之后就按照0-1背包问题的一般做法，依次枚举辅料即可。

- 时间复杂度$\mathcal{O}(N + M\cdot MAXC)$。其中$MAXC$为背包的最大容量。本题中$MAXC=20000$，因为答案不可能超过$20000$。
- 空间复杂度$\mathcal{O}(MAXC)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        vector<bool> can(20001);
        for (int base : baseCosts)
            can[base] = true;
        toppingCosts.insert(toppingCosts.end(), toppingCosts.begin(), toppingCosts.end());
        for (int topping : toppingCosts) {
            for (int i = 20000; i >= topping; --i)
                can[i] = can[i] || can[i - topping];
        }
        int min_gap = INT_MAX, ans = 0;
        for (int i = 1; i <= 20000; ++i)
            if (can[i] && abs(i - target) < min_gap) {
                ans = i;
                min_gap = abs(i - target);
            }
        return ans;
    }
};
```

:::

## Problem C - [通过最少操作次数使数组的和相等](https://leetcode.cn/problems/equal-sum-arrays-with-minimum-number-of-operations/)

我们可以发现：

- 如果$\min(N,M)*6<\max(N,M)$则无解，因为此时即使把数少的那边都变成$6$，同时数多的那边都变成$1$，也不能使两侧相等。
- 增大$nums1$中的一个数，就等于减小$nums2$中的一个数。
- 在有多个数可以选择的情况下，增大时应该优先增大较小的数（上升空间大）；同理，减小时应当优先减小较大的数（下降空间大）。

因此，我们统计出增长空间$inc$和减小空间$dec$。

- 如果$\sum_{nums1}>\sum_{nums2}$，我们应当进行减小操作（减小$nums1$中的数或增大$nums2$中的数），直到$\sum_{nums1}\leq\sum_{nums2}$。
- 反之，我们进行增大操作，直到$\sum_{nums1}\geq\sum_{nums2}$。

直接对$inc$或$dec$降序排序就可以通过；而利用计数排序，我们可以将时间复杂度进一步优化到线性时间。

- 时间复杂度$\mathcal{O}(N + M)$。
- 空间复杂度$\mathcal{O}(|\sum|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if (n > m * 6 || m > n * 6)
            return -1;
        int s1 = 0, s2 = 0;
        vector<int> inc(6), dec(6);
        for (int num : nums1) {
            s1 += num;
            if (num < 6)
                inc[6 - num]++;
            if (num > 1)
                dec[num - 1]++;
        }
        for (int num : nums2) {
            s2 += num;
            if (num < 6)
                dec[6 - num]++;
            if (num > 1)
                inc[num - 1]++;
        }
        if (s1 == s2)
            return 0;
        
        int cnt = 0;
        if (s1 > s2) {
            for (int i = 5; i >= 1; --i) {
                while (dec[i]) {
                    s1 -= i;
                    dec[i]--;
                    cnt++;
                    if (s1 <= s2)
                        return cnt;
                }
            }
        } else {
            for (int i = 5; i >= 1; --i) {
                while (inc[i]) {
                    s1 += i;
                    inc[i]--;
                    cnt++;
                    if (s1 >= s2)
                        return cnt;
                }
            }
        }
        
        return -1;
    }
};
```

:::

## Problem D - [车队 II](https://leetcode.cn/problems/car-fleet-ii/)

因为每次发生相遇之后，都可能发生速度的变化，所以我们需要按照时间顺序来处理所有的事件。

### 方法一：优先队列+并查集

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
struct DSU {
    vector<int> p, sz, speed, left, right;
    vector<double> pos, speed_change;
    
    DSU(vector<int> &speed, vector<double> &pos): speed(speed), pos(pos) {
        int n = speed.size();
        p = vector<int>(n);
        left = vector<int>(n);
        right = vector<int>(n);
        speed_change = vector<double>(n);
        for (int i = 0; i < n; ++i)
            p[i] = left[i] = right[i] = i;
        sz = vector<int>(n, 1);
    }
    
    int find(int i) {
        return p[i] == i ? i : p[i] = find(p[i]);
    }
    
    void merge(int i, int j) {
        int pi = find(i), pj = find(j);
        if (pi == pj)
            return;
        int spd = min(speed[pi], speed[pj]);
        int l = min(left[pi], left[pj]);
        int r = max(right[pi], right[pj]);
        double ps = max(pos[pi], pos[pj]);
        double spc = max(speed_change[pi], speed_change[pj]);
        if (sz[pi] >= sz[pj]) {
            speed[pi] = spd;
            left[pi] = l;
            right[pi] = r;
            pos[pi] = ps;
            speed_change[pi] = spc;
            sz[pi] += sz[pj];
            p[pj] = pi;
        } else {
            speed[pj] = spd;
            left[pj] = l;
            right[pj] = r;
            pos[pj] = ps;
            speed_change[pj] = spc;
            sz[pj] += sz[pi];
            p[pi] = pj;
        }
    }
    
    int get_speed(int idx) {
        return speed[find(idx)];
    }
    
    double get_pos(int idx) {
        return pos[find(idx)];
    }
    
    int get_left(int idx) {
        return left[find(idx)];
    }
    
    int get_right(int idx) {
        return right[find(idx)];
    }
    
    double get_speed_change(int idx) {
        return speed_change[find(idx)];
    }
    
    void set_pos(int idx, double ps) {
        pos[find(idx)] = ps;
    }
    
    void set_speed_change(int idx, double spc) {
        speed_change[find(idx)] = spc;
    }
    
    void move(int idx, double t) {
        if (t < get_speed_change(idx))
            return;
        double delta = t - get_speed_change(idx);
        pos[find(idx)] += get_speed(idx) * delta;
        speed_change[find(idx)] = t;
    }
};

class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> ans(n, -1.0);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
        vector<int> speed(n);
        vector<double> time(n, -1.0), speed_change(n), pos(n);
        for (int i = 0; i < n; ++i)
            pos[i] = cars[i][0], speed[i] = cars[i][1];
        for (int i = 0; i < n - 1; ++i) {
            if (cars[i][1] > cars[i + 1][1]) {
                double t = (pos[i + 1] - pos[i]) / (cars[i][1] - cars[i + 1][1]);
                pq.emplace(t, i);
                time[i] = t;
            }
        }
        DSU dsu(speed, pos);
        while (!pq.empty()) {
            auto [t, idx] = pq.top();
            pq.pop();
            if (abs(t - time[idx]) > 1e-6 || ans[idx] > 0)
                continue;
            ans[idx] = t;
            int L = dsu.get_left(idx) - 1, R = dsu.get_right(idx + 1) + 1;
            dsu.move(idx, t), dsu.move(idx + 1, t);
            dsu.merge(idx, idx + 1);
            if (L >= 0 && ans[L] < 0) {
                dsu.move(L, t), dsu.move(L + 1, t);
                int sp0 = dsu.get_speed(L), sp1 = dsu.get_speed(L + 1);
                if (sp0 > sp1) {
                    double nxt = t + (dsu.get_pos(L + 1) - dsu.get_pos(L)) / (sp0 - sp1);
                    pq.emplace(nxt, L);
                    time[L] = nxt;
                } else {
                    time[L] = -1.0;
                }
            }
            if (R < n && ans[R - 1] < 0) {
                dsu.move(R - 1, t), dsu.move(R, t);
                int sp0 = dsu.get_speed(R - 1), sp1 = dsu.get_speed(R);
                if (sp0 > sp1) {
                    double nxt = t + (dsu.get_pos(R) - dsu.get_pos(R - 1)) / (sp0 - sp1);
                    pq.emplace(nxt, R - 1);
                    time[R - 1] = nxt;
                } else {
                    time[R - 1] = -1.0;
                }
            }
        }
        return ans;
    }
};
```

:::

### 方法二：单调栈（待补）

<Utterances />
