---
sidebarDepth: 3
---

# 不变量

有时，一个问题中，具体操作的步骤可能是$\mathcal{O}(2^n)$或$\mathcal{O}(n!)$级别的，我们无法一一枚举；但是，通过观察，我们会发现存在某个量，在任意操作前后都不发生变化，这样的量我们就可以称其为不变量（invariant）。如果我们能进一步找到这一不变量与我们所关心的问题之间的关系，就能一举将问题简化：不再需要考虑具体的操作步骤，而只需要计算出这一不变量即可。

## 练习题

### [BS - Foo Bar Qaz Qux](https://binarysearch.com/problems/Foo-Bar-Qaz-Qux)

::: details 提示
如果我们给每种颜色一个赋值，并且令$R\text{ xor }G=B$，那么所有颜色的异或和就成了一个不变量。
:::

::: details 参考代码（Python 3）

```python
class Solution:
    def solve(self, quxes):
        n = len(quxes)
        if len(set(quxes)) == 1:
            return n
        if n <= 1:
            return n
        x = 0
        d = {"R": 1, "G": 2, "B": 3}
        for qux in quxes:
            x ^= d[qux]
        return 2 if x == 0 else 1
```

:::

<Utterances />
