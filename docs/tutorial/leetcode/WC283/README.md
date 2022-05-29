# Leetcode 第283场周赛题解

## Problem A - [Excel 表中某个范围内的单元格](https://leetcode.cn/problems/cells-in-a-range-on-an-excel-sheet/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(NM)$。
- 空间复杂度 $\mathcal{O}(NM)$。


::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<string> cellsInRange(string s) {
        char a = s[0], b = s[3];
        int p = s[1] - '0', q = s[4] - '0';
        vector<string> ans;
        for (char c = a; c <= b; ++c) {
            for (int d = p; d <= q; ++d) {
                string t{c, (char)(d + '0')};
                ans.push_back(t);
            }
        }
        return ans;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def cellsInRange(self, s: str) -> List[str]:
        return [chr(i) + str(j) for i in range(ord(s[0]), ord(s[3]) + 1) for j in range(int(s[1]), int(s[4]) + 1)]
```

:::

::: details 参考代码（Rust）

```rust
impl Solution {
    pub fn cells_in_range(s: String) -> Vec<String> {
        let s = s.chars().collect::<Vec<_>>();

        (s[0]..=s[3]).into_iter().flat_map(|col| 
            (s[1]..=s[4]).into_iter().map( |row|
                format!("{}{}", col, row)
            ).collect::<Vec<_>>()).collect::<Vec<_>>()
    }
}
```

:::

## Problem B - [向数组中追加 K 个整数](https://leetcode.cn/contest/weekly-contest-283/problems/append-k-integers-with-minimal-sum/)

### 方法一：贪心

我们首先将数组排序并去重。

之后，我们依次考虑数组中的每个数。显然，对于第 $i$ 个数  $a_i$，不超过它的且不出现在原数组中的正整数一共有 $a_i-i-1$ 个。如果这个数不小于 $k$，则说明我们最大只需要取到 $k+i$，就可以得到 $k$ 个互不相同且不在原数组中出现的正整数。此时容易求得这些数的和。

> 我们在数组最后插入了 `2e9` 以避免对边界的单独讨论。

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        nums.resize(unique(nums.begin(), nums.end()) - nums.begin());
        nums.push_back(2e9);
        long long sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] - 1 - i >= k)
                return 1LL * (k + i) * (k + i + 1) / 2 - sum;
            sum += nums[i];
        }
        
        return -1;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def minimalKSum(self, nums: List[int], k: int) -> int:
        nums = sorted(set(nums)) + [int(2e9)]
        s = 0
        for i, num in enumerate(nums):
            if num - 1 - i >= k:
                return (k + i) * (k + i + 1) // 2 - s
            s += num
        
        return -1
```

:::

::: details 参考代码（Rust）

```rust
use std::collections::BTreeSet;

impl Solution {
    pub fn minimal_k_sum(nums: Vec<i32>, k: i32) -> i64 {
        let mut nums = nums.into_iter().collect::<BTreeSet<_>>().into_iter().collect::<Vec<_>>();
        nums.push(2_000_000_000);
        let mut sum = 0i64;
        for (i, &num) in nums.iter().enumerate() {
            if num - i as i32 - 1 >= k {
                let u = (k + i as i32) as i64;
                return u * (u + 1) / 2 - sum;
            }  
            sum += num as i64;
        }
        
        -1
    }
}
```

:::

## Problem C - [根据描述创建二叉树](https://leetcode.cn/problems/create-binary-tree-from-descriptions/)

### 方法一：模拟

按照描述逐条进行操作即可。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {    
        unordered_map<int, TreeNode*> v;
        unordered_map<int, int> deg;
        for (auto &d : descriptions) {
            int p = d[0], c = d[1], left = d[2];
            if (!v.count(p))
                v[p] = new TreeNode(p);
            if (!v.count(c))
                v[c] = new TreeNode(c);
            if (left)
                v[p]->left = v[c];
            else
                v[p]->right = v[c];
            deg[c]++;
        }
        
        for (auto [i, node] : v)
            if (deg[i] == 0)
                return node;
        
        return nullptr;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
class Solution:
    def createBinaryTree(self, descriptions: List[List[int]]) -> Optional[TreeNode]:
        v = dict()
        deg = collections.Counter()
        for p, c, left in descriptions:
            if p not in v:
                v[p] = TreeNode(p)
            if c not in v:
                v[c] = TreeNode(c)
            if left == 1:
                v[p].left = v[c]
            else:
                v[p].right = v[c]
            deg[c] += 1
        for i in v:
            if deg[i] == 0:
                return v[i]
        
        return None
```

:::

::: details 参考代码（Rust）

```rust
use std::rc::Rc;
use std::cell::RefCell;
use std::collections::{HashMap, HashSet};

impl Solution {
    pub fn create_binary_tree(descriptions: Vec<Vec<i32>>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut v: HashMap<i32, Option<Rc<RefCell<TreeNode>>>> = HashMap::new();
        let mut s: HashSet<i32> = HashSet::new();

        for desc in descriptions {
            let p = desc[0];
            let c = desc[1];
            let left = desc[2];

            v.entry(p).or_insert_with(|| Some(Rc::new(RefCell::new(TreeNode::new(p)))));
            v.entry(c).or_insert_with(|| Some(Rc::new(RefCell::new(TreeNode::new(c)))));
            s.insert(c);

            let cnode = v.get(&c).unwrap().clone();
            let mut pnode = v.get(&p).unwrap().clone().unwrap();
            if left == 1 {
                pnode.borrow_mut().left = cnode;
            } else {
                pnode.borrow_mut().right = cnode;
            }
        }

        for (i, node) in v {
            if !s.contains(&i) {
                return node;
            }
        }

        None
    }
}
```

:::

## Problem D - [替换数组中的非互质数](https://leetcode.cn/problems/replace-non-coprime-numbers-in-array/)

### 方法一：栈模拟

题目已经说了，任何操作顺序都可以得到相同的结果；因此我们可以用栈来进行模拟，也即认为所有替换都发生在栈顶。

- 时间复杂度 $\mathcal{O}(N\log C)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> ans;
        for (int num : nums) {
            ans.push_back(num);
            int n = ans.size();
            while (n >= 2 && gcd(ans[n - 2], ans[n - 1]) > 1) {
                int r = ans.back();
                ans.pop_back();
                ans.back() *= r / gcd(ans.back(), r);
                n--;
            }
        }
        return ans;
    }
};
```

:::

::: details 参考代码（Python 3）

```python
from math import gcd, lcm

class Solution:
    def replaceNonCoprimes(self, nums: List[int]) -> List[int]:
        ans = []
        for num in nums:
            ans.append(num)
            while len(ans) >= 2 and gcd(ans[-2], ans[-1]) > 1:
                r = ans.pop()
                ans[-1] = lcm(ans[-1], r)
            
        return ans
```

:::

::: details 参考代码（Rust）

```rust
fn gcd(i: i32, j: i32) -> i32 {
    if j == 0 { i } else { gcd(j, i % j) }
}

impl Solution {
    pub fn replace_non_coprimes(nums: Vec<i32>) -> Vec<i32> {
        let mut ans = vec![];
        for num in nums {
            ans.push(num);
            let mut n = ans.len();
            while n >= 2 && gcd(ans[n - 2], ans[n - 1]) > 1 {
                let r = ans.pop().unwrap();
                ans[n - 2] *= r / gcd(ans[n - 2], r);
                n -= 1;
            }
        }
        ans
    }
}
```

:::

<Utterances />
