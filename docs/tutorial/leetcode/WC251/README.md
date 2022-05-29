# Leetcode 第251场周赛题解

## Problem A - [字符串转化后的各位数字之和](https://leetcode.cn/problems/sum-of-digits-of-string-after-convert/)

### 方法一：模拟

按题意模拟即可。

- 时间复杂度$\mathcal{O}(k|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def getLucky(self, s: str, k: int) -> int:
        snum = ''.join(map(lambda x: str(ord(x) - ord('a') + 1), s))
        for _ in range(k):
            snum = str(sum(map(int, snum)))
        return int(snum)
```

:::

## Problem B - [子字符串突变后可能得到的最大整数](https://leetcode.cn/problems/largest-number-after-mutating-substring/)

### 方法一：贪心

我们贪心地从第一个突变后能够增大的位置开始，到第一个突变后减小的位置结束即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string maximumNumber(string num, vector<int>& change) {
        int n = num.size(), i = 0;
        while (i < n && change[num[i] - '0'] <= num[i] - '0')
            i++;
        while (i < n && change[num[i] - '0'] >= num[i] - '0')
            num[i] = change[num[i] - '0'] + '0', i++;
        return num;
    }
};
```

:::

## Problem C - [最大兼容性评分和](https://leetcode.cn/problems/maximum-compatibility-score-sum/)

这道题本身是一个二分图带权最大匹配问题，但是数据规模较小，因此我们可以有别的解题方法。

### 方法一：穷举

穷举进行老师和学生之间的匹配。

- 时间复杂度$\mathcal{O}(M\cdot M!)=\mathcal{O}(M!)$。
- 空间复杂度$\mathcal{O}(M^2)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxCompatibilitySum(self, students: List[List[int]], mentors: List[List[int]]) -> int:
        m, n = len(students), len(students[0])
        points = [[0] * m for _ in range(m)]
        for i in range(m):
            for j in range(m):
                for k in range(n):
                    points[i][j] += 1 if students[i][k] == mentors[j][k] else 0
        ans = 0
        for order in itertools.permutations(range(m)):
            curr = 0
            for i in range(m):
                curr += points[i][order[i]]
            ans = max(ans, curr)
        return ans
```

:::

### 方法二：状态压缩动态规划

用状态压缩来优化穷举过程。

- 时间复杂度$\mathcal{O}(M\cdot2^M)$。
- 空间复杂度$\mathcal{O}(M^2+2^M)=\mathcal{O}(2^M)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int m = students.size(), n = students[0].size();
        vector<vector<int>> points(m, vector<int>(m));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                for (int k = 0; k < n; ++k)
                    points[i][j] += students[i][k] == mentors[j][k];
        
        vector<int> dp(1 << m);
        for (int i = 0; i + 1 < (1 << m); ++i) {
            int idx = __builtin_popcount(i);
            for (int j = 0; j < m; ++j) {
                if (!(i & (1 << j))) {
                    int nxt = i ^ (1 << j);
                    dp[nxt] = max(dp[nxt], dp[i] + points[idx][j]);
                }
            }
        }
        
        return dp.back();
    }
};
```

:::

### 方法三：转化为费用流

二分图带权最大匹配可以转化为费用流问题，从而在多项式时间内求解。这已经超出了一般算法面试的要求，这里不展开介绍。

## Problem D - [删除系统中的重复文件夹](https://leetcode.cn/problems/delete-duplicate-folders-in-system/)

### 方法一：树哈希

首先，我们可以仿照建立字典树的方式，建立出文件系统对应的树结构。接下来，我们利用树哈希的方式来判断是否存在重复子树。

树哈希的方法多种多样，但原则是要保证相同结构的哈希值相同，不同结构的哈希值尽可能不同（尽可能不碰撞）。

我这里采用的方式是：

$$
h=H(name_1+h_1+"/"+name_2+h_2+"/"+\dots)
$$

其中$H(S)$为哈希函数（求得的结果为一个整数），$S$是一个字符串。

可能有人会想用字符串来表示每一个子树，但这样做的问题是，如果原结构是一条长链，则用于存储这些字符串将需要平方级别的空间，相应的，进行处理时也需要平方级别的时间。

另一个注意点是，这里存储孩子时要用有序结构（比如`map`），而不能用无序结构（比如`unordered_map`），因为题目并没有说明给出的路径是按照字典序排列的，所以可能存在像下面这样的例子：

`[["a"], ["a", "b"], ["a", "c"], ["d"], ["d", "c"], ["d", "b"]]`

如果采用无序结构，则很可能判定`"a"`和`"d"`不是重复文件夹，但实际上它们是重复的（都包含了`"b"`和`"c"`）。

::: details 参考代码（C++）

```cpp
using ull = unsigned long long;
const int P = 129;

struct Node {
    string name;
    map<string, Node*> children;
    ull hash = 0;
    bool deleted = false;

    Node(string name): name(name) {}
};

unordered_map<ull, vector<Node*>> mp;
vector<vector<string>> ans;

void dfs(Node *p) {
    string sub;
    for (auto [name, node] : p->children) {
        dfs(node);
        sub += name + to_string(node->hash) + "/";
    }
    for (char ch : sub)
        p->hash = p->hash * P + ch;
    if (!p->children.empty())
        mp[p->hash].emplace_back(p);
}

void dfs2(Node *p, vector<string> &curr) {
    if (!p->deleted) {
        if (p->name != "/") {
            curr.push_back(p->name);
            ans.push_back(curr);
        }
        for (auto [_name, node] : p->children)
            dfs2(node, curr);
        if (p->name != "/")
            curr.pop_back();
    }
}

class Solution {
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        Node *root = new Node("/");
        for (auto &path : paths) {
            Node *p = root;
            for (string &dir : path) {
                if (!p->children.count(dir))
                    p->children[dir] = new Node(dir);
                p = p->children[dir];
            }
        }
        
        mp.clear();
        dfs(root);
        for (auto [hash, nodes] : mp) {
            if (nodes.size() >= 2) {
                for (Node *node : nodes)
                    node->deleted = true;
            }
        }
        
        ans.clear();
        vector<string> curr;
        dfs2(root, curr);
        return ans;
    }
};
```

:::

<Utterances />
