# Leetcode 第244场周赛题解

## Problem A - [判断矩阵经轮转后是否一致](https://leetcode.cn/problems/determine-whether-matrix-can-be-obtained-by-rotation/)

### 方法一：模拟

尝试旋转`mat`，看是否能与`target`匹配。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
    vector<vector<int>> rotate(vector<vector<int>> &a) {
        int n = a.size();
        vector<vector<int>> ans(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ans[j][n - 1 - i] = a[i][j];
        return ans;
    }
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        vector<vector<int>> r(mat);
        for (int i = 0; i < 4; ++i) {
            bool same = true;
            for (int p = 0; p < n; ++p)
                for (int q = 0; q < n; ++q)
                    if (r[p][q] != target[p][q])
                        same = false;
            if (same)
                return true;
            r = rotate(r);
        }
        return false;
    }
};
```

:::

如果用Python的话，还可以直接使用`np.rot90`。

::: details 参考代码（Python 3）

```python
import numpy as np

class Solution:
    def findRotation(self, mat: List[List[int]], target: List[List[int]]) -> bool:
        source = np.array(mat)
        target = np.array(target)
        for i in range(4):
            if (source == target).all():
                return True
            source = np.rot90(source)
        return False
```

:::

## Problem B - [使数组元素相等的减少操作次数](https://leetcode.cn/problems/reduction-operations-to-make-the-array-elements-equal/)

### 方法一：排序

尝试模拟一下，会发现操作过程实际上就是把当前最大的这批数字都变成次大的数字，如此反复直到所有数字都变为原本最小的那个数字。因此我们用一个`map`计数并排序，然后从最大的数字开始进行处理，累加操作次数即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        map<int, int> cnt;
        for (int num : nums)
            cnt[num]++;
        int ans = 0, acc = 0;
        for (auto it = cnt.rbegin(); it != cnt.rend(); ++it) {
            int f = it->second;
            ans += acc;
            acc += f;
        }
        return ans;
    }
};      
```

:::

## Problem C - [使二进制字符串字符交替的最少反转次数](https://leetcode.cn/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/)

### 方法一：滑动窗口

容易想到令$T=S+S$，然后使用滑动窗口的方式来模拟操作一。

我们的目标串是`01...01`或`10...10`，而操作二的所需次数，实际上就是原串与目标串相异的位置的数目。因此，我们令$T_1$为`'01'*n`，$T_2$为`'10'*n`，然后在滑动窗口的过程中维护原串与这两个目标串的相异位置数即可。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minFlips(self, s: str) -> int:
        n = len(s)
        t = s + s
        a = '01' * n
        b = '10' * n
        ans = n
        da = 0
        db = 0
        for i in range(n * 2):
            if t[i] != a[i]:
                da += 1
            if t[i] != b[i]:
                db += 1
            if i >= n:
                if t[i - n] != a[i - n]:
                    da -= 1
                if t[i - n] != b[i - n]:
                    db -= 1
            if i >= n - 1:
                ans = min(ans, da, db)
        return ans
```

:::

## Problem D - [装包裹的最小浪费空间](https://leetcode.cn/contest/weekly-contest-244/problems/minimum-space-wasted-from-packaging/)

### 方法一：双指针

容易想到对包裹和供应商的箱子分别排序，然后使用双指针求解。但需要考虑这一端情形：$N=M=10^5$，也即有大量供应商而每个供应商的箱子种数只有一种的时候，如果我们使用常规双指针，我们会遍历`packages`数组$M$次，导致超时。

因此，我们改为只遍历每个供应商的箱子（因为所有供应商的箱子种类的总数不超过$10^5$），对于每个箱子，我们利用二分来确定`packages`数组中的指针应该移动到的位置。

- 时间复杂度$\mathcal{O}((N+K)\log N+K\log K)$，其中$K$是所有供应商的箱子总数。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        ll ans = LLONG_MAX;
        sort(packages.begin(), packages.end());
        ll sum = 0;
        for (int package : packages)
            sum += package;
        for (auto &box : boxes) {
            sort(box.begin(), box.end());
            if (packages.back() > box.back())
                continue;
            ll used = 0;
            ll ptr = 0;
            for (int b : box) {
                auto it = upper_bound(packages.begin(), packages.end(), b);
                if (it != packages.begin()) {
                    it--;
                    int idx = it - packages.begin();
                    used += 1LL * b * (idx + 1 - ptr);
                    ptr = idx + 1;
                }
            }
            ans = min(ans, used - sum);
        }
        
        return ans == LLONG_MAX ? -1 : ans % MOD;
    }
};
```

:::

<Utterances />
