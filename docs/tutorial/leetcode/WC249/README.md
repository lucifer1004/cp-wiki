# Leetcode 第249场周赛题解

## Problem A - [数组串联](https://leetcode-cn.com/problems/concatenation-of-array/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def getConcatenation(self, nums: List[int]) -> List[int]:
        return nums + nums
```

:::

## Problem B - [长度为 3 的不同回文子序列](https://leetcode-cn.com/problems/unique-length-3-palindromic-subsequences/)

### 方法一：枚举

我们可以首先记录下每个字母的所有出现位置，然后我们枚举可能的回文子序列ABA中的A和B。

确定A和B之后，我们需要在A的左端点和右端点之间查找B，这可以借助`upper_bound`函数或自行二分实现。

- 时间复杂度$\mathcal{O}(|S|+|\sum|^2\log|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        vector<vector<int>> pos(26);
        for (int i = 0; i < n; ++i) {
            int ch = s[i] - 'a';
            pos[ch].emplace_back(i);
        }
        int ans = 0;
        for (int i = 0; i < 26; ++i) {
            if (pos[i].size() >= 2) {
                int l = pos[i][0], r = pos[i].back();
                for (int j = 0; j < 26; ++j) {
                    auto it = upper_bound(pos[j].begin(), pos[j].end(), l);
                    if (it != pos[j].end() && *it < r)
                        ans++;
                }
            }
        }
        return ans;
    }
};
```

:::

## Problem C - [用三种不同颜色为网格涂色](https://leetcode-cn.com/problems/painting-a-grid-with-three-different-colors/)

### 方法一：动态规划

$M$很小，提示我们按列进行枚举。首先，对于一列来说，合法的方案数为$3\cdot2^{M-1}$；然后我们再枚举考虑这些方案之间是否可以相邻，从而确定转移矩阵。最后的动态规划是比较显然的。

本题中$N$不算大，逐列求解就可以保证通过；如果$N$达到$10^9$量级，我们可以使用矩阵快速幂求解。

- 时间复杂度$\mathcal{O}(N\cdot2^{2M})$。
- 空间复杂度$\mathcal{O}(2^M)$。

::: details 参考代码（Rust）

```rust
const MOD: usize = 1_000_000_007;

impl Solution {
    pub fn color_the_grid(m: i32, n: i32) -> i32 {
        let m = m as usize;
        let n = n as usize;
        
        let mut upper = 1;
        for i in 0..m {
            upper *= 3;
        }
        
        let mut codes = vec![];
        for i in 0..upper {
            let mut code = vec![0; m];
            let mut num = i;
            for j in 0..m {
                if num == 0 {
                    break;
                }
                code[j] = num % 3;
                num /= 3;
            }
            let mut valid = true;
            for j in 0..m - 1 {
                if code[j] == code[j + 1] {
                    valid = false;
                    break;
                }
            }
            if valid {
                codes.push(code);
            }
        }
        
        let k = codes.len();
        let mut trans = vec![vec![]; k];
        for i in 0..k {
            for j in i + 1..k {
                let mut valid = true;
                for t in 0..m {
                    if codes[i][t] == codes[j][t] {
                        valid = false;
                        break;
                    }
                }
                if valid {
                    trans[i].push(j);
                    trans[j].push(i);
                }
            }
        }
        
        let mut dp = vec![1; k];
        for i in 1..n {
            let mut ndp = vec![0; k];
            for j in 0..k {
                for &t in trans[j].iter() {
                    ndp[t] = (ndp[t] + dp[j]) % MOD;
                }
            }
            dp = ndp;
        }
        
        let mut ans = 0;
        for i in 0..k {
            ans = (ans + dp[i]) % MOD;
        }
        
        ans as i32
    }
}
```

:::

## Problem D - [合并多棵二叉搜索树](https://leetcode-cn.com/problems/merge-bsts-to-create-single-bst/)

### 方法一：模拟

本题的解题关键是认识到这实际上是一道模拟题，并不需要我们考虑合并方案。

为什么呢？这里首先给出结论：

> 如果本题有解，则：
> - 有且仅有一个根节点，无法替换任何一个其他二叉搜索树叶子节点。这个根节点也就是结果二叉树的根节点。
> - 其余的根节点，有且仅有一个其他二叉搜索树的叶子节点与其具有相同取值。

下面进行说明：

1. 如果没有这样的根节点，则我们最后结果二叉树的根节点必然与某个原来的叶子节点取值相同，这样显然不是二叉搜索树。而如果有两个或更多这样的根节点，我们最后会得到一个森林，而无法得到一棵树。
2. 对于其余的根节点，如果没有取值相同的叶子节点，则其将无法合并到结果二叉树中；而如果有两个或更多与其取值相同的叶子节点，因为所有根节点的取值都不同，所以最后的二叉树中将至少包含两个具有相同取值的节点，显然不是二叉搜索树。

所以我们找出结果二叉树的根节点，以及其余根节点所唯一对应的叶子节点，就可以唯一确定地建出一棵二叉树。但这棵二叉树未必满足条件，我们还需要检查：

1. 它确实是一棵二叉搜索树。
2. 它包含了正确的节点数目，也即原来的所有二叉树的总节点数减去$N-1$（因为要进行$N-1$次合并）。比如在`[[1, null, 3], [3, 1], [4]]`这个例子，我们最后检查以`4`为根节点的这棵树，它确实是一棵二叉搜索树，但没有包含全部的节点。

- 时间复杂度$\mathcal{O}(N)$。其中$N$为所有二叉搜索树的节点总数。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
const int N = 50005;
int cnt = 0;

bool valid(TreeNode* root, int lower, int upper) {
    if (!root)
        return true;
    cnt++;
    if (root->val < lower || root->val > upper)
        return false;
    return valid(root->left, lower, root->val - 1) && valid(root->right, root->val + 1, upper);
}

class Solution {
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        int n = trees.size();
        vector<TreeNode*> parent(N, nullptr);
        int tot = 0;
        for (TreeNode *tree : trees) {
            tot++;
            
            if (tree->left) {
                tot++;
                if (parent[tree->left->val])
                    return nullptr;
                parent[tree->left->val] = tree;
            }
            
            if (tree->right) {
                tot++;
                if (parent[tree->right->val])
                    return nullptr;
                parent[tree->right->val] = tree;
            }
        }
        
        TreeNode *root = nullptr;
        for (TreeNode *tree : trees) {
            if (!parent[tree->val]) {
                if (root)
                    return nullptr;
                root = tree;
            } else {
                TreeNode *p = parent[tree->val];
                if (p->val > tree->val)
                    p->left = tree;
                else
                    p->right = tree;
            }
        }

        cnt = 0;
        if (valid(root, 1, N) && cnt == tot + 1 - n)
            return root;
        
        return nullptr;
    }
};
```

:::

<Utterances />
