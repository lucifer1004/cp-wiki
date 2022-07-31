# Leetcode 第83场双周赛题解

## Problem A - [最好的扑克手牌](https://leetcode.cn/problems/best-poker-hand/)

### 方法一：分类讨论

- 时间复杂度 $\mathcal{O}(1)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def bestHand(self, ranks: List[int], suits: List[str]) -> str:
        cnt = collections.Counter(ranks)
        freq = list(cnt.values())
        
        if len(set(suits)) == 1:
            return 'Flush'
        elif max(freq) >= 3:
            return 'Three of a Kind'
        elif max(freq) == 2:
            return 'Pair'
        else:
            return 'High Card'
```

:::

## Problem B - [全 0 子数组的数目](https://leetcode.cn/problems/number-of-zero-filled-subarrays/)

### 方法一：分段累加

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def zeroFilledSubarray(self, nums: List[int]) -> int:
        ans = 0
        cnt = 0
        for num in nums:
            if num == 0:
                cnt += 1
            else:
                ans += cnt * (cnt + 1) // 2
                cnt = 0
        ans += cnt * (cnt + 1) // 2
        return ans
```

:::

## Problem C - [设计数字容器系统](https://leetcode.cn/problems/design-a-number-container-system/)

### 方法一：哈希表 + 平衡树

- 时间复杂度 $\mathcal{O}(\log N)$ 。
- 空间复杂度 $\mathcal{O}(N)$ 。

::: details 参考代码（C++）

```cpp
class NumberContainers {
    unordered_map<int, int> mp;
    unordered_map<int, set<int>> nums;
    
public:
    NumberContainers() {}
    
    void change(int index, int number) {
        if (mp.count(index))
            nums[mp[index]].erase(index);
        mp[index] = number;
        nums[number].insert(index);
    }
    
    int find(int number) {
        if (nums[number].empty())
            return -1;
        
        return *nums[number].begin();
    }
};
```

:::

### 方法二：懒删除堆

::: details 参考代码（Python 3）

```python
from heapq import heappush, heappop

class NumberContainers:
    def __init__(self):
        self.idx = dict()
        self.nums = defaultdict(list)

    def change(self, index: int, number: int) -> None:
        self.idx[index] = number
        heappush(self.nums[number], index)

    def find(self, number: int) -> int:
        while len(self.nums[number]) > 0 and self.idx[self.nums[number][0]] != number:
            heappop(self.nums[number])
        return -1 if len(self.nums[number]) == 0 else self.nums[number][0]
```

:::


## Problem D - [不可能得到的最短骰子序列](https://leetcode.cn/problems/shortest-impossible-sequence-of-rolls/)

### 方法一：脑筋急转弯

> 骰子序列的每一位都需要对应一段连续的包括 $1$ 到 $k$ 所有数字的区间，所以找出有多少个这样的区间就好了。

- 时间复杂度 $\mathcal{O}(N)$。
- 空间复杂度 $\mathcal{O}(K)$。

::: details 参考代码（C++）

```cpp
class Solution:
    def shortestSequence(self, rolls: List[int], k: int) -> int:
        s = set()
        full = 0
        for roll in rolls:
            s.add(roll)
            if len(s) == k:
                s = set()
                full += 1
        return full + 1
```

:::

<Utterances />
