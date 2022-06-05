# Leetcode 第296场周赛题解

## Problem A - [极大极小游戏](https://leetcode.cn/problems/min-max-game/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minMaxGame(self, nums: List[int]) -> int:
        while len(nums) > 1:
            nxt = []
            for i in range(0, len(nums), 2):
                if i % 4 == 0:
                    nxt.append(min(nums[i:i+2]))
                else:
                    nxt.append(max(nums[i:i+2]))
            nums = nxt
        return nums[0]
```

:::

## Problem B - [划分数组使最大差为 K](https://leetcode.cn/problems/partition-array-such-that-maximum-difference-is-k/)

### 方法一：排序 + 贪心

排序后从小到大分组即可。

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def partitionArray(self, nums: List[int], k: int) -> int:
        nums.sort()
        ans = 1
        l = nums[0]
        for num in nums[1:]:
            if num - l > k:
                ans += 1
                l = num
        return ans
```

:::

## Problem C - [替换数组中的元素](https://leetcode.cn/problems/replace-elements-in-an-array/)

### 方法一：记录双向映射

在本题的限制条件下，记录并维护从原始数值到当前数值，以及从当前数值到原始数值的双向映射即可。

- 时间复杂度 $\mathcal{O}(N+Q)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（Python 3）

```python
class Solution:
    def arrayChange(self, nums: List[int], operations: List[List[int]]) -> List[int]:
        mapping = {num: num for num in nums}
        original = {num: num for num in nums}
        for u, v in operations:
            raw = original[u]
            mapping[raw] = v
            original[v] = raw
            del original[u]
        return [mapping[num] for num in nums]
```

:::

### 思考

如果去掉题目中的限制条件，也即：

- 数组中可能包含相同的数字。
- 每次操作 $(u,v)$ 中， $u$ 可能不存在，$v$ 可能存在。

要如何解决呢？

::: details 提示

两组数一旦合并（变成相同的数值）之后无论如何操作都不会分开。因此可以使用并查集来维护每个数值分组。

:::

## Problem D - [设计一个文本编辑器](https://leetcode.cn/problems/design-a-text-editor/)

### 方法一：链表模拟

::: details 参考代码（C++，使用 `list`）

```cpp
const int LEN = 10;

class TextEditor {
    list<char> lst;
    list<char>::iterator c;

    string fetch() {
        auto it = c;
        string s;
        for (int k = LEN; k > 0 && *prev(it) != ' '; k--, it = prev(it)) s.push_back(*prev(it));
        reverse(s.begin(), s.end());
        return s;
    }

public:
    TextEditor() {
        lst = list<char> {' '};
        c = lst.end();
    }

    void addText(string text) {
        for (char ch : text) c = next(lst.insert(c, ch));
    }

    int deleteText(int k) {
        int i = 0;
        for (; k > 0 && *prev(c) != ' '; k--, i++, c = lst.erase(prev(c))) {}
        return i;
    }

    string cursorLeft(int k) {
        for (; k > 0 && *prev(c) != ' '; k--, c = prev(c)) {}
        return fetch();
    }

    string cursorRight(int k) {
        for (; k > 0 && c != lst.end(); k--, c = next(c)) {}
        return fetch();
    }
};
```

::: details 参考代码（C++，使用自定义链表）

```cpp
const int LEN = 10;

struct Node {
    char ch;
    Node *pre, *nxt;
    Node(char c) : ch(c), pre(nullptr), nxt(nullptr) {}
};

class TextEditor {
    Node *c;

    string fetch() {
        Node *p = c;
        string s;
        for (int k = LEN; k > 0 && p->ch != ' '; k--, p = p->pre) s.push_back(p->ch);
        reverse(s.begin(), s.end());
        return s;
    }

public:
    TextEditor() { c = new Node(' '); }

    void addText(string text) {
        for (char ch : text) {
            Node *n = new Node(ch);
            n->pre = c;
            n->nxt = c->nxt;
            if (c->nxt != nullptr) c->nxt->pre = n;
            c->nxt = n;
            c = n;
        }
    }

    int deleteText(int k) {
        int i = 0;
        for (; k > 0 && c->ch != ' '; k--, i++, c = c->pre) {
            c->pre->nxt = c->nxt;
            if (c->nxt != nullptr) c->nxt->pre = c->pre;
        }
        return i;
    }

    string cursorLeft(int k) {
        for (; k > 0 && c->ch != ' '; k--, c = c->pre) {}
        return fetch();
    }

    string cursorRight(int k) {
        for (; k > 0 && c->nxt != nullptr; k--, c = c->nxt) {}
        return fetch();
    }
};

```

:::

### 方法二：栈模拟

::: details 参考代码（C++）

```cpp
const int LEN = 10;

class TextEditor {
    stack<char> L, R;
    
    string fetch() {
        string s;
        for (int i = 0; i < LEN && !L.empty(); ++i) s.push_back(L.top()), L.pop();
        reverse(s.begin(), s.end());
        for (char ch : s) L.push(ch);
        return s;
    }
public:
    TextEditor() {}
    
    void addText(string text) {
        for (char ch : text) L.push(ch);
    }
    
    int deleteText(int k) {
        int i = 0;
        for (; i < k && !L.empty(); ++i) L.pop();
        return i;
    }
    
    string cursorLeft(int k) {
        for (int i = 0; i < k && !L.empty(); ++i) R.push(L.top()), L.pop();
        return fetch();
    }
    
    string cursorRight(int k) {
        for (int i = 0; i < k && !R.empty(); ++i) L.push(R.top()), R.pop();
        return fetch();
    }
};
```

:::

<Utterances />
