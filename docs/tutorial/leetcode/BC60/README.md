# Leetcode 第60场双周赛题解

## Problem A - [找到数组的中间位置](https://leetcode-cn.com/problems/find-the-middle-index-in-array/)

### 方法一：模拟

逐位计算，判断是否满足要求。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        right = sum(nums)
        left = 0
        for i in range(len(nums)):
            right -= nums[i]
            if left == right:
                return i
            left += nums[i]
        return -1
```

:::


## Problem B - [找到所有的农场组](https://leetcode-cn.com/problems/find-all-groups-of-farmland/)

### 方法一：贪心

我们发现，在题目给定的限制条件下，农场组左上角的格子一定满足向上为边界或`0`，且向左也为边界或`0`。这样我们就可以很容易地找出所有左上角的格子。对于每个左上角的格子，我们向右就能确定该农场组的宽度，向下就能确定高度，从而就能得到右下角格子的坐标。

- 时间复杂度为$\mathcal{O}(RC)$。
- 空间复杂度$\mathcal{O}(RC)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        int n = land.size(), m = land[0].size();
        auto good = [&](int i, int j) {
            if (land[i][j] == 0)  
                return false;
            if (i > 0 && land[i - 1][j] == 1)
                return false;
            if (j > 0 && land[i][j - 1] == 1)
                return false;
            return true;
        };
        vector<vector<int>> ans;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (good(i, j)) {
                    int r = j;
                    while (r + 1 < m && land[i][r + 1] == 1)
                        r++;
                    int d = i;
                    while (d + 1 < n && land[d + 1][j] == 1)
                        d++;
                    ans.push_back({i, j, d, r});
                }
            }
        return ans;
    }
};
```

:::


## Problem C - [树上的操作](https://leetcode-cn.com/problems/operations-on-tree/)

### 方法一：模拟

预处理出每个节点的孩子节点，然后按要求模拟即可。

`lock`和`unlock`比较简单，`upgrade`需要三步：

1. 逐层上跳，检查祖先中是否有锁。
2. DFS检查子树中是否有锁。
3. DFS清除子树中的锁。

- 预处理时间复杂度$\mathcal{O}(N)$，`lock`和`unlock`时间复杂度$\mathcal{O}(1)$，`upgrade`时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class LockingTree {
    int n;
    vector<int> parent, locked;
    vector<vector<int>> adj;
    
    bool has_lock(int u) {
        if (locked[u])
            return true;
        
        for (int v : adj[u])
            if (has_lock(v))
                return true;
        
        return false;
    }
    
    void batch_unlock(int u) {
        locked[u] = 0;
        for (int v : adj[u])
            batch_unlock(v);
    }
    
public:
    LockingTree(vector<int>& parent) {
        this->parent = parent;
        n = parent.size();
        locked = vector<int>(n);
        adj = vector<vector<int>>(n);
        for (int i = 1; i < n; ++i)
            adj[parent[i]].emplace_back(i);
    }
    
    bool lock(int num, int user) {
        if (!locked[num]) {
            locked[num] = user;
            return true;
        }
        return false;
    }
    
    bool unlock(int num, int user) {
        if (locked[num] == user) {
            locked[num] = 0;
            return true;
        }
        return false;
    }
    
    bool upgrade(int num, int user) {
        int p = num;
        while (p != -1) {
            if (locked[p])
                return false;
            p = parent[p];
        }
        
        if (!has_lock(num))
            return false;
        
        batch_unlock(num);
        locked[num] = user;
        return true;
    }
};
```

:::

## Problem D - [好子集的数目](https://leetcode-cn.com/problems/the-number-of-good-subsets/)

### 方法一：动态规划预处理+枚举

首先要理清题意。我们要找的是什么样的子集？

1. 子集的乘积大于$1$，也即必须有非$1$的元素。
2. 子集中任意一个质因子最多出现一次。

注意到数组元素在$[1,30]$范围内，我们不妨列出这一范围内所有不含有重复质因子的数，这样的数一共有$18$个：


$$
\begin{aligned}
[2, 3, 5, 7, 11, 13, 17, 19, 23, 29] & \quad 质数\\
[6, 10, 14, 22, 26, 15, 21] & \quad 两个不同质数的乘积\\
[30] & \quad 三个不同质数的乘积\\
\end{aligned}
$$

剩下的数都是不能选取的（暂时不考虑$1$）。

同时，这$18$个数之间也存在一定的互斥关系，这里我们可以用一次状态压缩动态规划进行预处理，得到所有好的组合方式。我们会发现，这样的方式一共只有$3327$种。

预处理完毕后，对于给定的数组`nums`，每一个好的组合方式对应的好子集的个数（不考虑$1$）就是这一组合方式中包含的每一个数字的出现次数之积（乘法原理）。

累加之后，我们就得到了不含$1$的好子集的数目。对于每一个这样的子集，我们都可以向其中添加至多$cnt[1]$个$1$而保持其仍为好子集，因此最后的总方案数还需要乘上$2^{cnt[1]}$（每个$1$都有选或不选两种可能）。

- 预处理时间复杂度$\mathcal{O}(M\cdot2^M+N)$，每次运行时间复杂度$\mathcal{O}(M\cdot K+N)$，其中$M=18$，$K=3327$。
- 空间复杂度$\mathcal{O}(2^M+MAXN)$。

::: details 参考代码（C++）

```cpp
const int MOD = 1e9 + 7;
const int p[18] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 6, 10, 14, 22, 26, 15, 21, 30};
bool inited = false;
int two[100001];
bool g[18][18]{}, good[1 << 18]{};
vector<int> good_subset;

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

void init() {
    inited = true;
    
    for (int i = 0; i < 18; ++i)
        for (int j = i + 1; j < 18; ++j) {
            if (gcd(p[i], p[j]) == 1)
                g[i][j] = true;
        }
    
    good[0] = true;
    for (int i = 1; i < (1 << 18); ++i) {
        for (int j = 0; j < 18; ++j) {
            if (i & (1 << j)) {
                bool valid = good[i ^ (1 << j)];
                if (valid) {
                    for (int k = j + 1; k < 18; ++k) {
                        if ((i & (1 << k)) && !g[j][k]) {
                            valid = false;
                            break;
                        }
                    }
                }
                good[i] = valid;
                break;
            }
        }
        
        if (good[i])
            good_subset.emplace_back(i);
    }
    
    two[0] = 1;
    for (int i = 1; i <= 100000; ++i)
        two[i] = two[i - 1] * 2 % MOD;
}

class Solution {
public:
    int numberOfGoodSubsets(vector<int>& nums) {
        if (!inited)
            init();
        
        int n = nums.size();
        vector<int> cnt(31);
        for (int num : nums)
            cnt[num]++;
        
        int ans = 0;
        for (int i : good_subset) {
            int curr = 1;
            for (int j = 0; j < 18 && curr; ++j)
                if (i & (1 << j))
                    curr = 1LL * curr * cnt[p[j]] % MOD;
            ans = (ans + curr) % MOD;
        }
        
        return 1LL * ans * two[cnt[1]] % MOD;
    }
};
```

:::

<Utterances />
