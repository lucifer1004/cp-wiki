# Leetcode 第245场周赛题解

## Problem A - [重新分配字符使所有字符串都相等](https://leetcode.cn/problems/redistribute-characters-to-make-all-strings-equal/)

### 方法一：计数

因为字符的移动是任意的，所以我们只需要统计每个字母的个数，判断其是否能被字符串的个数整除即可。

- 时间复杂度$\mathcal{O}(\sum|word|)$。
- 空间复杂度$\mathcal{O}(|\sum|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def makeEqual(self, words: List[str]) -> bool:
        n = len(words)
        cnt = Counter()
        for word in words:
            for c in word:
                cnt[c] += 1
        for val in cnt.values():
            if val % n != 0:
                return False
        return True
```

:::

## Problem B - [可移除字符的最大数目](https://leetcode.cn/problems/maximum-number-of-removable-characters/)

### 方法一：二分+双指针

如果删除若干个字母后，$p$已经不是$s^\prime$的子序列，则继续删除字母，$p$也不会是$s^\prime$的子序列。根据这一决策单调性，我们可以二分答案。

在二分过程中，我们首先根据当前删除的位置得到$s^\prime$，然后用双指针判断$p$是否是$s^\prime$的子序列。

- 时间复杂度$\mathcal{O}((|S|+|P|)\log N)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def maximumRemovals(self, s: str, p: str, removable: List[int]) -> int:
        ls = len(s)
        lp = len(p)
        n = len(removable)
        lo = 1
        hi = min(n, ls - lp)
        while lo <= hi:
            mid = (lo + hi) >> 1
            mark = [False] * ls
            for i in range(mid):
                mark[removable[i]] = True
            t = [s[i] for i in range(ls) if not mark[i]]
            ptr = 0
            for c in t:
                if c == p[ptr]:
                    ptr += 1
                    if ptr == lp:
                        break
            if ptr == lp:
                lo = mid + 1
            else:
                hi = mid - 1
        return hi      
```

:::

## Problem C - [合并若干三元组以形成目标三元组](https://leetcode.cn/problems/merge-triplets-to-form-target-triplet/)

### 方法一：贪心

首先，注意到题中的操作实际上就是每一位取最大值。我们需要合并若干个三元组来得到目标三元组，也就是说用于合并的这些三元组的每一位的最大值恰好应当等于目标三元组对应位置上的值。

设目标为$(tx,ty,tz)$。考虑一个三元组$(x,y,z)$，如果$x>tx$或$y>ty$或$z>tz$，则我们显然不应将这一三元组用于合并，否则将会有一个位置超过目标三元组。反之，如果$x\leqslant tx,y\leqslant ty,z\leqslant tz$，我们就应当将这一三元组用于合并，因为这样做至少不会有坏处。

最后，我们检查合并得到的结果是否与目标三元组相等即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        vector<int> state(3, 0);
        for (auto &v : triplets) {
            if (v[0] <= target[0] && v[1] <= target[1] && v[2] <= target[2]) {
                state[0] = max(state[0], v[0]);
                state[1] = max(state[1], v[1]);
                state[2] = max(state[2], v[2]);
            }
        }
        return state == target;
    }
};
```

:::

## Problem D - [最佳运动员的比拼回合](https://leetcode.cn/problems/the-earliest-and-latest-rounds-where-players-compete/)

### 方法一：状态压缩+穷举

本题中，我们实际上只需要关心一号种子和二号种子的当前位置。初始状态为$(l,r)$。

我们逐轮进行考虑。在一轮中，我们枚举所有一、二号种子位置的可能组合：

- 如果这一位置下，一、二号种子将在本轮比拼，我们记录下这一轮次；
- 否则，我们在这一条件下枚举所有比赛的胜负情况。因为比赛的数目等于$\lfloor\frac{n}{2}\rfloor$，所以即使$n=28$的第一轮中，我们也只需要枚举$2^{14}<2\times10^4$种情况。筛除不合法的情况（一、二号种子被淘汰），我们就可以得到本轮比拼后剩余选手的编号，从而可以确定一号种子和二号种子的新编号，带入下一轮。

重复进行下去，我们就能得到所有可能的一、二号种子的比拼轮次，从而得到答案。

下面考虑复杂度。第一轮时需要枚举的比赛胜负情况最多，为$2^{\lfloor\frac{N}{2}\rfloor}$次，但此时只有$(l,r)$一种状态。后续状态数增多，但需要枚举的比赛胜负情况指数衰减。这里，不十分严格地，我们认为算法总的时间复杂度由对第一轮的枚举决定。

- 时间复杂度$\mathcal{O}(N\cdot2^{\lfloor\frac{N}{2}\rfloor})$，这里认为在$N$很小的情况下`set`操作的时间复杂度近似为常数。
- 空间复杂度$\mathcal{O}(N^2)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        int t = n, round = 0;
        int lo = -1, hi = -1;
        set<pair<int, int>> states{{firstPlayer, secondPlayer}};
        while (!states.empty()) {
            round++;
            set<pair<int, int>> nxt_states;
            int nt = (t + 1) / 2;
            for (auto [l, r] : states) {
                if (l + r == t + 1) {
                    if (lo == -1)
                        lo = round;
                    hi = round;
                } else {
                    int len = t / 2;
                    for (int i = 0; i < (1 << len); ++i) {
                        set<int> rem;
                        for (int j = 0; j < len; ++j) {
                            if (i & (1 << j))
                                rem.insert(j + 1);
                            else
                                rem.insert(t - j);
                        }
                        if (t % 2 == 1)
                            rem.insert(nt);
                        if (!rem.count(l) || !rem.count(r) || rem.size() != nt)
                            continue;
                        vector<int> seq(rem.begin(), rem.end());
                        int nl = -1, nr = -1;
                        for (int i = 0; i < nt; ++i) {
                            if (seq[i] == l)
                                nl = i + 1;
                            if (seq[i] == r)
                                nr = i + 1;
                        }
                        nxt_states.emplace(nl, nr);
                    }
                }
            }
            t = nt;
            states = move(nxt_states);
        }
        
        return {lo, hi};
    }
};
```

:::

<Utterances />
