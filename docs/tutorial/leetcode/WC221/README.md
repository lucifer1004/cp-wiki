# Leetcode 第221场周赛题解

## Problem A - [判断字符串的两半是否相似](https://leetcode-cn.com/problems/determine-if-string-halves-are-alike/)

按要求模拟即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def halvesAreAlike(self, s: str) -> bool:
        vowels = set(list('aeiouAEIOU'))
        l = 0
        r = 0
        n = len(s)
        for c in s[:n // 2]:
            if c in vowels:
                l += 1
        for c in s[n // 2:]:
            if c in vowels:
                r += 1
        return l == r
```

:::

## Problem B - [吃苹果的最大数目](https://leetcode-cn.com/problems/maximum-number-of-eaten-apples/)

我们用一个`map`按照坏掉的日期从近到远的顺序存储当前的苹果，每次我们贪心地吃坏掉日期最近的一个苹果。

我们最多只需要考虑到第$\max(i+days[i])$天，因为之后所有苹果都会坏掉。

- 时间复杂度$\mathcal{O}(\max(i+days[i])\cdot\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        map<int, int> cnt;
        int ans = 0;
        int n = apples.size();
        auto add = [&](int i) {
            if (apples[i]) 
                cnt[i + days[i]] += apples[i];
        };
        auto eat = [&](int i) {
            while (!cnt.empty() && cnt.begin()->first <= i)
                cnt.erase(cnt.begin());
            if (!cnt.empty()) {
                ans++;
                int d = cnt.begin()->first;
                cnt[d]--;
                if (cnt[d] == 0)
                    cnt.erase(cnt.begin());
            }
        };
        for (int i = 0; i < n; ++i) {
            add(i);
            eat(i);
        }
        for (int i = n; !cnt.empty(); ++i)
            eat(i);
        return ans;
    }
};
```

:::

## Problem C - [球会落何处](https://leetcode-cn.com/problems/where-will-the-ball-fall/)

模拟每一列的球的下落过程即可。如果当前列的隔板是`\`方向的，则检查右边的隔板，如果右边也是`\`，则球右移一列，否则球会停住；反之，检查左边的隔板，如果左边也是`/`，则球左移一列，否则球会停住。

- 时间复杂度$\mathcal{O}(NM)$。
- 空间复杂度$\mathcal{O}(M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> ans(m);
        for (int i = 0; i < m; ++i) {
            int col = i;
            for (int j = 0; j < n; ++j) {
                if (grid[j][col] == 1 && col + 1 < m && grid[j][col + 1] == 1) {
                    col++;
                } else if (grid[j][col] == -1 && col > 0 && grid[j][col - 1] == -1) {
                    col--;
                } else {
                    ans[i] = -1;
                    break;
                }
            }
            if (ans[i] != -1)
                ans[i] = col;
        }
        return ans;
    }
};
```

:::

## Problem D - [与数组中元素的最大异或值](https://leetcode-cn.com/problems/maximum-xor-with-an-element-from-array/)

我们可以使用0-1字典树存储数组中的元素。因为每个查询还包含一个上界$m_i$，所以我们在字典树的每个节点额外存储以当前节点为根节点的子树中的最小元素。其作用是：如果某一子树的最小元素都超过了$m_i$，则没有必要继续对这一子树进行搜索。

考虑一次查询。我们从最高位开始逐位处理：

- 如果$x_i$的当前位为$1$，我们应当优先走当前位为$0$的分支；否则，我们尝试走当前位为$1$的分支，如果分支不存在，或分支的最小元素也超过了$m_i$，则本查询无解。
- 如果$x_i$的当前位为$0$，我们应当优先走当前位为$1$的分支，但要求这一分支的最小元素不超过$m_i$；否则，我们尝试走当前位为$0$的分支。

如果我们顺利地走到了最低位，就得到了这一查询的最优解。

- 时间复杂度$\mathcal{O}((N+Q)\log MAXN)$。
- 空间复杂度$\mathcal{O}(N\log MAXN+Q)$。

::: details 参考代码（C++）

```cpp
struct TrieNode {
    int lo = INT_MAX;
    TrieNode* children[2]{};
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        TrieNode* root = new TrieNode();
        for (int num : nums) {
            TrieNode* p = root;
            for (int i = 30; i >= 0; --i) {
                int nxt = (num & (1 << i)) ? 1 : 0;
                if (!p->children[nxt]) p->children[nxt] = new TrieNode();
                p = p->children[nxt];
                p->lo = min(p->lo, num);
            }
        }
        vector<int> ret;
        for (auto q : queries) {
            int x = q[0], limit = q[1];
            int ans = 0;
            TrieNode* p = root;
            for (int i = 30; i >= 0; --i) {
                if (x & (1 << i)) {
                    if (p->children[0]) {
                        p = p->children[0];
                        ans ^= (1 << i);
                    } else if (!p->children[1] || (p->children[1]->lo > limit)) {
                        ret.emplace_back(-1);
                        break;
                    } else {
                        p = p->children[1];
                    }
                } else {
                    if (p->children[1] && (p->children[1]->lo <= limit)) {
                        p = p->children[1];
                        ans ^= (1 << i);
                    } else if (!p->children[0]) {
                        ret.emplace_back(-1);
                        break;
                    } else {
                        p = p->children[0];
                    }
                }
                if (i == 0) ret.emplace_back(ans);
            }
        }
        return ret;
    }
};
```

:::

<Utterances />
