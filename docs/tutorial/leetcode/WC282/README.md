# Leetcode 第282场周赛题解

## Problem A - [统计包含给定前缀的字符串](https://leetcode-cn.com/problems/counting-words-with-a-given-prefix/)

### 方法一：暴力

枚举所有字符串，判断是否符合要求。

- 时间复杂度 $\mathcal{O}(N|T|)$，其中 $|T|$ 为给定前缀的长度。
- 空间复杂度 $\mathcal{O}(N|T|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def prefixCount(self, words: List[str], pref: str) -> int:
        return len([1 for word in words if len(word) >= len(pref) and word[:len(pref)] == pref])
```

:::

## Problem B - [使两字符串互为字母异位词的最少步骤数](https://leetcode-cn.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/)

### 方法一：哈希表

因为只能增加字符，所以我们对于每一个字母，我们都需要将拥有这一字母较少的那个字符串的字母个数增加到与较多的那一个一致。

- 时间复杂度 $\mathcal{O}(|S|+|T|+|\Sigma|)$。
- 空间复杂度 $\mathcal{O}(|\Sigma|)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cs = collections.Counter(s)
        ct = collections.Counter(t)
        return sum(abs(cs[ch] - ct[ch]) for ch in set(cs.keys()) | set(ct.keys()))
```

:::

## Problem C - [完成旅途的最少时间](https://leetcode-cn.com/problems/minimum-time-to-complete-trips/)

### 方法一：二分答案

经典二分答案题：已知总时间 $T$，我们可以很容易地求出所有车一共运行了多少次。将这一次数表示为一个 $T$ 的函数 $f(T)$，显然 $f(T)$ 随 $T$ 的增大单调递增。这一单调性是二分答案的基础。

- 时间复杂度 $\mathcal{O}(N\log C)$。其中 $C = \min(time)\times totalTrips$ 为答案的上界。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        lo = 1
        hi = min(time) * totalTrips
        while lo <= hi:
            mid = (lo + hi) >> 1
            tot = sum(mid // t for t in time)
            if tot >= totalTrips:
                hi = mid - 1
            else:
                lo = mid + 1
        return lo
```

:::

## Problem D - [完成比赛的最少时间](https://leetcode-cn.com/problems/minimum-time-to-finish-the-race/)

### 方法一：动态规划

令 $dp[i]$ 表示跑完 $i$ 圈所需的最短时间。考虑上一次换胎的时间，假设为第 $j$ 圈后，则有转移：

$$
dp[i]=\min_{j=0}^{i-1}(dp[j]+changeTime+best[j-i])
$$

其中 $best[j-i]$ 表示用单一轮胎跑 $j-i$ 圈的最短时间。

我们可以用暴力枚举的方式预处理出 $best$ 数组。注意到 $r_i\ge2$，而 $changeTime\le10^5$，因此同一轮胎连续使用的圈数不会太长（否则总用时必然超过了换新胎再跑的用时）。我们这里取上限 $K=20$，因为 $2^{20}\simeq10^6$，所以这一取值已经足够。

得到 $best$ 数组后，我们再进行上面的动态规划即可。注意这里并不需要遍历所有的 $j$ 而只需要遍历与 $i$ 相差不超过 $K$ 的那些（因为不可能用同一轮胎跑超过 $K$ 圈）。

- 时间复杂度 $\mathcal{O}((N+M)K)$，其中 $N$ 为轮胎种数，$M$ 为要跑的圈数， $K=20$。
- 空间复杂度 $\mathcal{O}(M+K)$。

::: details 参考代码（Python 3）

> 注意下面的代码中，因为多考虑了一次换胎时间（跑第一圈之前的换胎），所以最后的答案要减掉一次换胎时间。

```python
K = 20

class Solution:
    def minimumFinishTime(self, tires: List[List[int]], changeTime: int, numLaps: int) -> int:
        inf = int(1e12)
        best = [inf] * (K + 1)
        for f, r in tires:
            lap, last, tot = 1, f, f
            while lap <= K and tot < inf:
                best[lap] = min(best[lap], tot)
                lap, last, tot = lap + 1, last * r, tot + last * r
            
        dp = [inf] * (numLaps + 1)
        dp[0] = 0
        for i in range(1, numLaps + 1):
            for j in range(max(0, i - K), i):
                dp[i] = min(dp[i], dp[j] + changeTime + best[i - j])
                
        return dp[numLaps] - changeTime
```

:::

<Utterances />
