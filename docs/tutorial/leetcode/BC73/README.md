# Leetcode 第73场双周赛题解

## Problem A - [数组中紧跟 key 之后出现最频繁的数字](https://leetcode-cn.com/problems/most-frequent-number-following-key-in-an-array/)

### 方法一：暴力+计数

枚举所有符合条件的位置并统计频率。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def mostFrequent(self, nums: List[int], key: int) -> int:
        return collections.Counter([nums[i] for i in range(1, len(nums)) if nums[i - 1] == key]).most_common(1)[0][0]
```

:::

## Problem B - [将杂乱无章的数字排序](https://leetcode-cn.com/problems/sort-the-jumbled-numbers/)

### 方法一：模拟

按要求映射后排序即可。注意如果语言默认的排序不是稳定排序，需要把位置加入考虑。

- 时间复杂度$\mathcal{O}(N\log N\log C)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def sortJumbled(self, mapping: List[int], nums: List[int]) -> List[int]:
        return sorted(nums, key = lambda num: int(''.join(map(str, [mapping[int(x)] for x in str(num)]))))
```

:::

## Problem C - [有向无环图中一个节点的所有祖先](https://leetcode-cn.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/)

### 方法一：拓扑排序

拓扑排序之后依次处理即可。这里在转移时用了 `bitset` 来进行加速。

- 时间复杂度$\mathcal{O}(N^2+NM/W)$，其中 $M$ 为边数，$W$ 为字长。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<int> deg(n);
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            deg[e[1]]++;
            adj[e[0]].push_back(e[1]);
        }
        
        vector<bitset<1000>> ans(n);
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (deg[i] == 0)
                q.push(i);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                ans[v] |= ans[u];
                ans[v].set(u);
                deg[v]--;
                if (deg[v] == 0)
                    q.push(v);
            }
        }
        
        vector<vector<int>> result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (ans[i][j])
                    result[i].push_back(j);
        
        return result;
    }
};
```

:::

## Problem D - [得到回文串的最少操作次数](https://leetcode-cn.com/problems/minimum-number-of-moves-to-make-palindrome/)

### 方法一：贪心

从左到右依次处理。对于每个字母，从右向左找第一个与他匹配的字母：

- 如果找到，且不是它本身，则将找到的这个字母移动到右侧的对称位置；
- 如果找到，但是当前字母本身，这说明当前字母需要最后放在字符串的正中间。注意这里不能一步到位，而只能先将其向右移动一步，以避免进行多余操作。操作完成后，我们需要继续处理当前位置（所以在下面的实现中，有 `i--` 这一步）。

复杂度：

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
    
public:
    int minMovesToMakePalindrome(string s) {
        int n = s.size();
        int ans = 0;
        
        for (int i = 0; i < n / 2; i++) {
            int left = i;
            int right = n - left - 1;
            
            while (s[right] != s[left])
                right--;
            
            if (left == right) {
                swap(s[left], s[left + 1]);
                ans++;
                i--;
            } else {
                for (int j = right; j < n - left - 1; j++) {
                    swap(s[j], s[j + 1]);
                    ans++;
                }
            }
        }
        
        return ans;
    }
};
```

:::

### 方法二：直接构造结果 + 树状数组优化

我们可以直接得到最终的回文字符串，从而将题目变为“使用最少的相邻交换，将字符串 S 变为它的一个排列 T”。

此时，我们可以贪心地对于每一个位置，选取最靠前且还未被使用的相同字母。使用这一字母需要移动的次数等于它的初始位置前还未被使用的字母的总个数。

- 时间复杂度$\mathcal{O}(N\log N+|\Sigma|)$。
- 空间复杂度$\mathcal{O}(N+|\Sigma|)$。

::: details 参考代码（C++）

```cpp
template <class T> class FenwickTree {
    int limit;
    vector<T> arr;

    int lowbit(int x) { return x & (-x); }

public:
    FenwickTree(int limit) {
        this->limit = limit;
        arr = vector<T>(limit + 1);
    }

    void update(int idx, T delta) {
        for (; idx <= limit; idx += lowbit(idx))
            arr[idx] += delta;
    }

    T query(int idx) {
        T ans = 0;
        for (; idx > 0; idx -= lowbit(idx))
            ans += arr[idx];
        return ans;
    }
};

class Solution {
public:
    int minMovesToMakePalindrome(string s) {
        int n = s.size();
        vector<vector<int>> pos(26);
        for (int i = 0; i < n; ++i)
            pos[s[i] - 'a'].push_back(i);
        
        // Step 1: Construct the target string
        vector<bool> used(n);
        vector<int> ptr(26);
        int odd = -1;
        string t;
        for (int i = 0; i < n; ++i) {
            if (used[i])
                continue;
            
            int c = s[i] - 'a';
            int right = (int)pos[c].size() - 1 - ptr[c];
            if (right == ptr[c])
                odd = c;
            else {
                used[pos[c][right]] = true;
                t.push_back(s[i]);
                ptr[c]++;
            }
        }
        
        string rt(t.rbegin(), t.rend());
        if (odd != -1)
            t.push_back(odd + 'a');
        t += rt;
        
        // Step 2: Calculate the minimum swaps
        FenwickTree<int> ft(n);
        ptr.assign(26, 0);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int c = t[i] - 'a';
            int p = pos[c][ptr[c]];
            ans += p - ft.query(p);
            ptr[c]++;
            ft.update(p + 1, 1);
        }
        
        return ans;
    }
};
```

:::

<Utterances />
