# Leetcode 第214场周赛题解

## Problem A - [获取生成数组中的最大值](https://leetcode.cn/problems/get-maximum-in-generated-array/)

按要求模拟。注意如果采用赋初值的方法，在$n=0$时，不能给$a[1]$赋值。

- 时间复杂度$O(N)$。
- 空间复杂度$O(N)$。

::: details 参考代码（Python 3）

```python
@functools.lru_cache(None)
def f(n):
    return n if n <= 1 else f(n // 2) if n % 2 == 0 else f(n // 2) + f(n // 2 + 1)

class Solution:
    def getMaximumGenerated(self, n: int) -> int:
        a = [f(i) for i in range(n + 1)]
        return max(a)
```

:::

## Problem B - [字符频次唯一的最小删除次数](https://leetcode.cn/problems/minimum-deletions-to-make-character-frequencies-unique/)

统计所有频次，排序后从大到小贪心设置。

- 时间复杂度$O(N+K\log K)$，$K$为不同字符的个数。
- 空间复杂度$O(K)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minDeletions(self, s: str) -> int:
        cnt = collections.Counter(s)
        freq = sorted([cnt[key] for key in cnt])
        upper = [i for i in range(len(freq) + 1)]
        upper[-1] = int(1e9)
        ans = 0
        for i in range(len(freq) - 1, -1, -1):
            upper[i] = min(freq[i], max(0, upper[i + 1] - 1))
            ans += freq[i] - upper[i]
        return ans % int(1e9 + 7)        
```

:::

## Problem C - [销售价值减少的颜色球](https://leetcode.cn/problems/sell-diminishing-valued-colored-balls/)

排序后贪心卖当前个数最多的球。注意需要不断合并当前个数相同的组。

- 时间复杂度$O(N\log N)$。
- 空间复杂度$O(N)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;

class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        sort(inventory.begin(), inventory.end());
        vector<pair<int, int>> v = {{0, 0}};
        for (int i : inventory)
            v.emplace_back(i, 1);
        ll ans = 0;
        while (orders) {
            int m = v.size();
            if (v[m - 1].first == v[m - 2].first) {
                v[m - 2].second += v[m - 1].second;
                v.pop_back();
            } else {
                int l = v[m - 2].first + 1, r = v[m - 1].first;
                ll delta = r - l + 1;
                ll sell = min(delta * v[m - 1].second, (ll)orders);
                ll full = sell / v[m - 1].second;
                ans += ((ll)r + r - full + 1) * full * v[m - 1].second / 2 + ((ll)r - full) * (sell - full * v[m - 1].second);
                orders -= sell;
                if (orders) {
                    v[m - 2].second += v[m - 1].second;
                    v.pop_back();
                }
            }
        }
        return ans % int(1e9 + 7);
    }
};
```

:::

## Problem D - [通过指令创建有序数组](https://leetcode.cn/problems/create-sorted-array-through-instructions/)

树状数组模板题。

- 时间复杂度$O(N\log K)$，$K$为不同数字的个数。
- 空间复杂度$O(K)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;

template <class T> class FenwickTree {
  int limit;
  vector<T> arr;

  T lowbit(T x) { return x & (-x); }

public:
  FenwickTree(int limit) {
    this->limit = limit;
    arr = vector<T>(limit + 1);
  }

  void update(int idx, T delta) {
    for (; idx <= limit; idx += lowbit(idx))
      arr[idx] += delta;
  }

  T query(int idx) {
    T ans = 0;
    for (; idx > 0; idx -= lowbit(idx))
      ans += arr[idx];
    return ans;
  }
};

class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        ll ans = 0;
        set<int> s(instructions.begin(), instructions.end());
        unordered_map<int, int> dict;
        int idx = 0;
        for (int i : s)
            dict[i] = ++idx;
        FenwickTree<int> ft((int)s.size());
        int n = 0;
        for (int i : instructions) {
            int pos = dict[i];
            int l = ft.query(pos - 1);
            int r = n - ft.query(pos);
            ans += min(l, r);
            ft.update(pos, 1);
            n++;
        }
        return ans % int(1e9 + 7);
    }
};
```

:::

<Utterances />
