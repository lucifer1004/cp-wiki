# Leetcode 第236场周赛题解

## Problem A - [数组元素积的符号](https://leetcode-cn.com/problems/sign-of-the-product-of-an-array/)

如果有零，显然结果为零；如果没有零，就看负数是奇数个还是偶数个。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int arraySign(vector<int>& nums) {
        bool neg = false;
        for (int num : nums) {
            if (num == 0)
                return 0;
            if (num < 0)
                neg = !neg;
        }
        return neg ? -1 : 1;
    }
};
```

:::

## Problem B - [找出游戏的获胜者](https://leetcode-cn.com/problems/find-the-winner-of-the-circular-game/)

经典约瑟夫问题。数学方法倒推求解。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int findTheWinner(int n, int k) {
        int p = 0;
        for (int i = 2; i <= n; ++i)
            p = (p + k) % i;
        return p + 1;
    }
};
```

:::

## Problem C - [最少侧跳次数](https://leetcode-cn.com/problems/minimum-sideway-jumps/)

比较简单的动态规划。只需要维护上一列三行的最小侧跳次数即可。

- 时间复杂度$\mathcal{O}(C^2N)$。
- 空间复杂度$\mathcal{O}(C)$。

::: details 参考代码（C++）

```cpp
const int inf = 1e9;

class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size() - 1;
        vector<int> dp(4, inf);
        dp[2] = 0;
        dp[1] = dp[3] = 1;
        for (int i = 1; i < n; ++i) {
            vector<int> ndp(4, inf);
            for (int k = 1; k <= 3; ++k) {
                if (dp[k] == -1 || obstacles[i] == k)
                    continue;
                ndp[k] = min(ndp[k], dp[k]);
                for (int j = 1; j <= 3; ++j) {
                    if (obstacles[i] != j)
                        ndp[j] = min(ndp[j], dp[k] + 1);
                }
            }
            dp = move(ndp);
        }
        return *min_element(dp.begin(), dp.end());
    }
};
```

:::

## Problem D - [求出 MK 平均值](https://leetcode-cn.com/problems/finding-mk-average/)

### 方法一：`set`

- `small`存放最小的不超过$K$个数，`small_candidates`存放剩余的未过期的数。
- `large`存放最大的不超过$K$个数，`large_candidates`存放剩余的未过期的数。

`addElement`时：
- 如果当前元素超过$M$个，先进行过期操作，将过期的元素从四个`set`中删去。
- 如果当前元素可以放入`small`中（比`small_candidates`最小的元素小），将其放入。
- 如果当前元素可以放入`large`中（比`large_candidates`最大的元素大），将其放入。
- 如果`small`或`large`元素个数超过了$K$个，进行维护。
- 整个过程中，需要同时维护`small_sum`和`large_sum`。

`calculateMKAverage`时：
- 如果当前元素不足$M$个，返回$-1$。
- 否则，先将`small`和`large`补充至$K$个元素，同时维护`small_sum`和`large_sum`。
- 计算平均值。

复杂度：
- `addElement`时间复杂度$\mathcal{O}(\log M)$。
- `calculateMKAverage`的均摊时间复杂度为$\mathcal{O}(\log M)$。
- 空间复杂度$\mathcal{O}(N)$。

解释：
- `calculateMKAverage`中的补充元素操作仅会发生在有元素过期时。因为每个元素最多过期一次，所以补充元素操作的次数上限即为过期元素的数目。

::: details 参考代码（C++）

```cpp
class MKAverage {
    int m, k, cnt;
    vector<int> mem;
    double sum, large_sum, small_sum;
    set<pair<int, int>> small, large, small_candidates, large_candidates;
public:
    MKAverage(int m, int k): m(m), k(k), cnt(0), sum(0), large_sum(0), small_sum(0) {}
    
    void addElement(int num) {
        if (cnt >= m) {
            pair<int, int> p = {mem[cnt - m], cnt - m};
            if (small.count(p))
                small.erase({mem[cnt - m], cnt - m}), small_sum -= p.first;
            small_candidates.erase({mem[cnt - m], cnt - m});
            if (large.count(p))
                large.erase({mem[cnt - m], cnt - m}), large_sum -= p.first;
            large_candidates.erase({mem[cnt - m], cnt - m});
            sum -= p.first;
        }
        sum += num;
        mem.emplace_back(num);
        if (small_candidates.empty() || num <= small_candidates.begin()->first) {
            small.emplace(num, cnt);
            small_sum += num;
        } else {
            small_candidates.emplace(num, cnt);
        }
        if (small.size() > k) {
            auto p = *small.rbegin();
            small.erase(p);
            small_sum -= p.first;
            small_candidates.insert(p);
        }
        
        if (large_candidates.empty() || num >= large_candidates.rbegin()->first) {
            large.emplace(num, cnt);
            large_sum += num;
        } else {
            large_candidates.emplace(num, cnt);
        }
        if (large.size() > k) {
            auto p = *large.begin();
            large.erase(p);
            large_sum -= p.first;
            large_candidates.insert(p);
        }
        cnt++;
    }
    
    int calculateMKAverage() {
        if (cnt < m)
            return -1;
        
        while (small.size() < k) {
            auto p = *small_candidates.begin();
            small_sum += p.first;
            small.insert(p);
            small_candidates.erase(p);
        }
        
        while (large.size() < k) {
            auto p = *large_candidates.rbegin();
            large_sum += p.first;
            large.insert(p);
            large_candidates.erase(p);
        }
        
        double ans = (sum - small_sum - large_sum) / (m - k * 2);
        
        return int(ans);
    }
};
```

:::

### 方法二：自行实现平衡二叉树

我们可以自己实现任意一种平衡二叉树（Splay、AVL、红黑树……），同时在节点中额外存储：
- 子树元素和
- 子树元素个数

从而可以在平衡二叉树基本操作的基础上扩展出$\mathcal{O}(\log N)$的求前$K$大/小元素和的操作。

具体实现略。

<Utterances />
