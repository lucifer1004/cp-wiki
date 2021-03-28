# Leetcode 第234场周赛题解

## Problem A - [字符串中不同整数的数目](https://leetcode-cn.com/problems/number-of-different-integers-in-a-string/)

### 方法一：模拟

手动模拟，取出每一段整数部分。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        nums = set()
        l = 0
        while l < len(word):
            if word[l].isnumeric():
                r = l
                while r + 1 < len(word) and word[r + 1].isnumeric():
                    r += 1
                nums.add(int(word[l:r + 1]))
                l = r + 1
            else:
                l += 1
        return len(nums)
```

:::

### 方法二：正则表达式

使用`re.split()`切分字母部分。

::: details 参考代码（Python 3）

```python
class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        return len(set(map(int, filter(lambda x: len(x) > 0, re.split(r'[a-z]+', word)))))
```

:::

或者利用`re.findall()`提取数字部分。

::: details 参考代码（Python 3）

```python
class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        return len(set(map(int, re.findall(r'\d+', word))))
```

:::

## Problem B - [还原排列的最少操作步数](https://leetcode-cn.com/problems/minimum-number-of-operations-to-reinitialize-a-permutation/)

### 方法一：模拟

模拟进行操作；在每次操作后检查是否还原到初始状态。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def reinitializePermutation(self, n: int) -> int:
        perm = [i for i in range(n)]
        orig = list(perm)
        ops = 0
        while True:
            ops += 1
            perm = [perm[i // 2] if i % 2 == 0 else perm[n // 2 + (i - 1) // 2] for i in range(n)]
            if perm == orig:
                break
        return ops
```

:::

### 方法二：模拟1的位置

事实上，我们只需要模拟$1$的位置变动即可。当$1$回到原位时，所有元素都处在原位。

设$1$的当前位置为$pos$，将变换规则反向，我们可以知道：

- 如果$pos<\dfrac{N}{2}$，则$pos\rightarrow 2pos$
- 否则，$pos\rightarrow 2(pos-\dfrac{N}{2})+1$


这一方法的

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def reinitializePermutation(self, n: int) -> int:
        pos = 1
        ops = 0
        while True:
            ops += 1
            if pos < n // 2:
                pos <<= 1
            else:
                pos = 1 + ((pos - n // 2) << 1)
            if pos == 1:
                break
        return ops
```

:::

### 思考

可以进一步用数学方法求解吗？

## Problem C - [替换字符串中的括号内容](https://leetcode-cn.com/problems/evaluate-the-bracket-pairs-of-a-string/)

### 方法一：模拟

手动模拟替换操作。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def evaluate(self, s: str, knowledge: List[List[str]]) -> str:
        d = dict()
        for key, val in knowledge:
            d[key] = val
        ans = []
        l = 0
        while l < len(s):
            if s[l] == '(':
                r = l + 1
                while s[r] != ')':
                    r += 1
                key = s[l+1:r]
                if key in d:
                    ans.append(d[key])
                else:
                    ans.append('?')
                l = r + 1
            else:
                ans.append(s[l])
                l += 1
        return ''.join(ans)
```

:::

### 方法二：正则表达式

使用正则表达式结合lambda函数进行替换。

::: details 参考代码（Python 3）

```python
class Solution:
    def evaluate(self, s: str, knowledge: List[List[str]]) -> str:
        d = collections.defaultdict(lambda: '?')
        for key, val in knowledge:
            d[key] = val
        return re.sub(r'\(([a-z]+)\)', lambda x: d[x.group(1)], s)
```

:::

## Problem D - [好因子的最大数目](https://leetcode-cn.com/problems/maximize-number-of-nice-divisors/)

由乘法原理容易看出，质因数的分解确定后，好因子的数目等于每个不同的质因数的个数的乘积。

因此，本题与[LC343 - 整数拆分](https://leetcode-cn.com/problems/integer-break/)几乎等价（$N\leq3$的情况有所区别，因为本题中可以不进行拆分）。

由于数据范围扩大了，我们需要用快速幂来计算最后的结果。这里利用了Python中`pow()`函数的可选参数`mod`。

- 时间复杂度$\mathcal{O}(\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
MOD = 1000000007

class Solution:
    def maxNiceDivisors(self, n: int) -> int:
        if n <= 3:
            return n
        if n % 3 == 1:
            return 4 * pow(3, (n - 4) // 3, MOD) % MOD
        elif n % 3 == 2:
            return 2 * pow(3, n // 3, MOD) % MOD
        else:
            return pow(3, n // 3, MOD)
```

:::

<Utterances />
