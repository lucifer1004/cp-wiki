# Leetcode 第278场周赛题解

## Problem A - [将找到的值乘以 2](https://leetcode-cn.com/problems/keep-multiplying-found-values-by-two/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(N+\log M)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findFinalValue(self, nums: List[int], original: int) -> int:
        s = set(nums)
        while original in s:
            original *= 2
        return original
```

:::

## Problem B - [分组得分最高的所有下标](https://leetcode-cn.com/problems/all-divisions-with-the-highest-score-of-a-binary-array/)

### 方法一：前缀和

遍历过程中，维护前缀中 `0` 的个数和后缀中 `1` 的个数。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maxScoreIndices(self, nums: List[int]) -> List[int]:
        n = len(nums)
        r = nums.count(1)
        l = 0
        hi = r
        ans = [0]
        for i in range(n):
            if nums[i] == 1:
                r -= 1
            if nums[i] == 0:
                l += 1
            now = l + r
            if now > hi:
                hi = now
                ans = []
            if now == hi:
                ans.append(i + 1)
        return ans
```

:::

## Problem C - [查找给定哈希值的子串](https://leetcode-cn.com/problems/find-substring-with-given-hash-value/)

### 方法一：倒序滑动窗口

长度 $K$ 是固定的，这提示我们使用滑动窗口来计算子串的哈希值。这里我们有两种选择：

- 从左向右滑动
- 从右向左滑动

但我们发现，如果从左向右滑动，在更新哈希值时，我们需要进行同余除法。但本题中的模数$M$ 不一定是质数，逆元未必存在。

因此我们只能从右向左滑动。

> 一个小细节：记录中间结果的时候并不需要记录下完整的子串，只需要记录开始（或结束）位置即可。否则，如果有大量相同子串且都为答案，而使用的语言底层对字符串切片没有相应优化的话，就会导致超时。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def subStrHash(self, s: str, power: int, modulo: int, k: int, hashValue: int) -> str:
        n = len(s)
        pk = 1
        
        now = 0
        for i in range(n - k, n):
            c = ord(s[i]) - ord('a') + 1
            now = (now + c * pk) % modulo
            if i != n - 1:
                pk = pk * power % modulo
            
        ans = -1 if now != hashValue else n - k
        
        for i in range(n - k - 1, -1, -1):
            c = ord(s[i]) - ord('a') + 1
            d = ord(s[i + k]) - ord('a') + 1
            now += modulo - d * pk % modulo
            now = (now * power + c) % modulo
            if now == hashValue:
                ans = i
        
        return s[ans:ans + k]
```

:::

## Problem D - [字符串分组](https://leetcode-cn.com/problems/groups-of-strings/)

### 方法一：并查集+枚举

> 本题题面存在一定问题，结果并不唯一。需要加上限制保证每个分组内的连通性，才能使得答案唯一。下面的分析假设已经有这一限制。

本题中我们需要关注的是**字符集合**，且题目说了每个字符串中都不包含相同的字母。因此我们可以将每个字符串转为对应的一个二进制数。

下面考虑三种操作：

- 删除：相当于把某一位从 1 变为 0
- 添加：相当于把某一位从 0 变为 1
- 修改：相当于把一个 0 变为 1， 同时把一个 1 变为 0（不考虑保持不变的情况）

从而删除和添加可以合并为一种操作，也即修改一位的操作；而修改则对应于修改两位的操作。当然，还可以保持不变。

题目要求的分组关系实际上就是并查集。我们遍历所有字符串（对应的二进制数），然后枚举所有可能的操作，判断操作后的结果是否已经在之前的遍历中出现过。如果已经出现过，则在并查集中连边。

最后统计并查集中每个连通分量的信息即可得到答案。

- 时间复杂度$\mathcal{O}(N|\Sigma|^2\alpha(N))$
- 空间复杂度$\mathcal{O}(N)$

::: details 参考代码（C++）

```cpp
struct UnionFind {
  int n;
  vector<int> parent, size;

  UnionFind(int n) {
    this->n = n;
    parent = vector<int>(n);
    size = vector<int>(n, 1);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int idx) {
    if (parent[idx] == idx)
      return idx;
    return parent[idx] = find(parent[idx]);
  }

  void connect(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb) {
      if (size[fa] > size[fb]) {
        parent[fb] = fa;
        size[fa] += size[fb];
      } else {
        parent[fa] = fb;
        size[fb] += size[fa];
      }
    }
  }
};

class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        int n = words.size();
        vector<int> bits(n);
        for (int i = 0; i < n; ++i)
            for (char c : words[i])
                bits[i] ^= 1 << (c - 'a');
        
        UnionFind uf(n);
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            if (mp.count(bits[i]))
                uf.connect(mp[bits[i]], i);
            else {
                for (int j = 0; j < 26; ++j) {
                    int nb = bits[i] ^ (1 << j);
                    if (mp.count(nb))
                        uf.connect(mp[nb], i);
                }
                for (int j = 0; j < 26; ++j) {
                    int mskj = 1 << j;
                    if ((bits[i] & mskj) == 0)
                        continue;
                    for (int k = 0; k < 26; ++k) {
                        int mskk = 1 << k;
                        if (bits[i] & mskk)
                            continue;
                        int nb = bits[i] ^ mskj ^ mskk;
                        if (mp.count(nb))
                            uf.connect(mp[nb], i);
                    }
                }
            }
            
            if (!mp.count(bits[i]))
                mp[bits[i]] = i;
        }
        
        int groups = 0, largest = 0;
        for (int i = 0; i < n; ++i) {
            if (uf.find(i) == i) {
                groups++;
                largest = max(largest, uf.size[i]);
            }
        }
        
        return {groups, largest};
    }
};
```

:::

<Utterances />
