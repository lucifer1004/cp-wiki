# Leetcode 第248场周赛题解

## Problem A - [基于排列构建数组](https://leetcode-cn.com/problems/build-array-from-permutation/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def buildArray(self, nums: List[int]) -> List[int]:
        return [nums[x] for x in nums]
```

:::

## Problem B - [消灭怪物的最大数量](https://leetcode-cn.com/problems/eliminate-maximum-number-of-monsters/)

### 方法一：贪心

消灭一个怪物的最晚时间为$\left\lfloor\dfrac{dist_i-1}{speed_i}\right\rfloor$。按照这一最晚时间从小到大排序，依次消灭直到遇到第一个无法消灭的怪物为止即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def eliminateMaximum(self, dist: List[int], speed: List[int]) -> int:
        t = [(d - 1) // s for d, s in zip(dist, speed)]
        t.sort()
        for i in range(len(t)):
            if t[i] < i:
                return i
        return len(t)
```

:::

## Problem C - [统计好数字的数目](https://leetcode-cn.com/problems/count-good-numbers/)

### 方法一：数学

题目允许字符串开头有多余的`"0"`，所以答案即为

$$
5^{\left\lfloor\frac{n+1}{2}\right\rfloor}\cdot4^{\left\lfloor\frac{n}{2}\right\rfloor}
$$

注意取模。

- 时间复杂度$\mathcal{O}(\log N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countGoodNumbers(self, n: int) -> int:
        return pow(5, (n + 1) // 2, 1000000007) * pow(4, n // 2, 1000000007) % 1000000007
```

:::

## Problem D - [最长公共子路径](https://leetcode-cn.com/problems/longest-common-subpath/)

### 方法一：Rabin-Karp算法+二分答案

如果有一个长度为$i$的公共子路径，则必然可以有长度为$i-1$的公共子路径。利用这一单调性，我们可以二分答案。

如何检查是否有长度为$i$的公共子路径呢？

我们可以利用Rabin-Karp算法（字符串哈希）。我们可以求出每一条路径长度为$i$的子路径的哈希值，如果某一个哈希值在所有路径中都出现了，则认为存在长度为$i$的子路径。当然，由于可能存在哈希碰撞，这里的判定其实是必要不充分的。

与本题类似的[718. 最长重复子数组](https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/)中，哈希碰撞的可能性较小，但本题中有一个较强的数据，对于很多模数和乘数组合都可能发生哈希碰撞。

这里，我们的应对策略是选择更大的模数，并使用128位的整型以支持对应的乘法运算。

- 时间复杂度$\mathcal{O}(K\log\min len_i)$。其中$K$为所有数组的长度之和。
- 空间复杂度$\mathcal{O}(K)$。

::: details 参考代码（Rust）

```rust
use std::collections::{HashSet, HashMap};

const MOD: u128 = 180143985094819841;
const K: u128 = 100019;

fn check(mid: usize, paths: &Vec<Vec<i32>>) -> bool {
    let m = paths.len();
    let mut f = 1;
    for i in 0..mid {
        f = f * K % MOD;
    }
    let mut cnt: HashMap<u128, usize> = HashMap::new();

    for j in 0..m {
        let mut now = 0u128;
        let mut s: HashSet<u128> = HashSet::new();

        for i in 0..paths[j].len() {
            now = now * K + paths[j][i] as u128;
            now %= MOD;
            
            if i >= mid {
                now = (now + MOD - paths[j][i - mid] as u128 * f % MOD) % MOD;
            }
            
            if i >= mid - 1 {
                s.insert(now);
            }
        }

        for &si in s.iter() {
            *cnt.entry(si).or_insert(0) += 1;
        }
    }

    for (_, &freq) in cnt.iter() {
        if freq == m {
            return true;
        }
    }

    false
}

impl Solution {
    pub fn longest_common_subpath(n: i32, paths: Vec<Vec<i32>>) -> i32 {
        let m = paths.len();
        let mut hi = paths.iter().map(|x| x.len()).min().unwrap();
        let mut lo = 1;

        while lo <= hi {
            let mid = (lo + hi) >> 1;
            
            if check(mid, &paths) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        hi as i32
    }
}
```

:::

### 方法二：后缀数组+二分答案

哈希方法并不能保证正确性，有没有严格正确的方法呢？

答案是肯定的。我们可以使用[后缀数组](https://oi-wiki.org/string/sa/)，一种在字符串处理中可以发挥强大作用的专门数据结构。

这里对后缀数组本身不进行展开介绍，可以查阅有关资料进行学习。

首先，我们将$m$条路径连成一条总路径，并用分隔符进行分隔。注意这里的分隔符需要是不在路径中出现的数字，且所有的分隔符各不相同。

我们考虑某一条公共子路径。它在总路径中至少应当出现$m$次。我们考虑从这一公共子路径每一次出现的位置开始的后缀，这些后缀必然对应于总路径的后缀数组中的至少$m$个连续的位置（这是因为后缀数组是按照字典序排列的，这些后缀有着公共的前缀，在字典序排列中必然是连续的）。

假设这条公共子路径的长度为$len$，则在LCP数组中，这一公共子路径就对应了至少$m-1$个连续且值不小于$len$的位置。

> 说明：$LCP[i]$表示$SA[i]$和$SA[i+1]$的最长公共前缀。因此，如果$LCP[i]$到$LCP[j-1]$都不小于$len$，就说明第$i$个后缀到第$j$个后缀之间的$j-i+1$个后缀的最长公共前缀不小于$len$。

因此，完成预处理后，我们就可以利用SA数组和LCP数组，基于二分答案的策略来解题。

- 时间复杂度$\mathcal{O}(K\log\min len_i)$。其中$K$为所有数组的长度之和。这里二分答案的复杂度占主导。这里使用的求后缀数组和LCP数组的时间复杂度为线性复杂度。
- 空间复杂度$\mathcal{O}(K)$。

::: details 参考代码（Rust）

```rust
fn sa_is(s: &[usize], upper: usize) -> Vec<usize> {
    let n = s.len();
    match n {
        0 => return vec![],
        1 => return vec![0],
        2 => return if s[0] < s[1] { vec![0, 1] } else { vec![1, 0] },
        _ => (),
    }
    let mut sa = vec![0; n];
    let mut ls = vec![false; n];
    for i in (0..n - 1).rev() {
        ls[i] = if s[i] == s[i + 1] {
            ls[i + 1]
        } else {
            s[i] < s[i + 1]
        };
    }
    let mut sum_l = vec![0; upper + 1];
    let mut sum_s = vec![0; upper + 1];
    for i in 0..n {
        if !ls[i] {
            sum_s[s[i]] += 1;
        } else {
            sum_l[s[i] + 1] += 1;
        }
    }
    for i in 0..=upper {
        sum_s[i] += sum_l[i];
        if i < upper {
            sum_l[i + 1] += sum_s[i];
        }
    }

    // sa's origin is 1.
    let induce = |sa: &mut [usize], lms: &[usize]| {
        for elem in sa.iter_mut() {
            *elem = 0;
        }
        let mut buf = sum_s.clone();
        for &d in lms {
            if d == n {
                continue;
            }
            let old = buf[s[d]];
            buf[s[d]] += 1;
            sa[old] = d + 1;
        }
        buf.copy_from_slice(&sum_l);
        let old = buf[s[n - 1]];
        buf[s[n - 1]] += 1;
        sa[old] = n;
        for i in 0..n {
            let v = sa[i];
            if v >= 2 && !ls[v - 2] {
                let old = buf[s[v - 2]];
                buf[s[v - 2]] += 1;
                sa[old] = v - 1;
            }
        }
        buf.copy_from_slice(&sum_l);
        for i in (0..n).rev() {
            let v = sa[i];
            if v >= 2 && ls[v - 2] {
                buf[s[v - 2] + 1] -= 1;
                sa[buf[s[v - 2] + 1]] = v - 1;
            }
        }
    };
    // origin: 1
    let mut lms_map = vec![0; n + 1];
    let mut m = 0;
    for i in 1..n {
        if !ls[i - 1] && ls[i] {
            lms_map[i] = m + 1;
            m += 1;
        }
    }
    let mut lms = Vec::with_capacity(m);
    for i in 1..n {
        if !ls[i - 1] && ls[i] {
            lms.push(i);
        }
    }
    assert_eq!(lms.len(), m);
    induce(&mut sa, &lms);

    if m > 0 {
        let mut sorted_lms = Vec::with_capacity(m);
        for &v in &sa {
            if lms_map[v - 1] != 0 {
                sorted_lms.push(v - 1);
            }
        }
        let mut rec_s = vec![0; m];
        let mut rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]] - 1] = 0;
        for i in 1..m {
            let mut l = sorted_lms[i - 1];
            let mut r = sorted_lms[i];
            let end_l = if lms_map[l] < m { lms[lms_map[l]] } else { n };
            let end_r = if lms_map[r] < m { lms[lms_map[r]] } else { n };
            let same = if end_l - l != end_r - r {
                false
            } else {
                while l < end_l {
                    if s[l] != s[r] {
                        break;
                    }
                    l += 1;
                    r += 1;
                }
                l != n && s[l] == s[r]
            };
            if !same {
                rec_upper += 1;
            }
            rec_s[lms_map[sorted_lms[i]] - 1] = rec_upper;
        }

        let rec_sa = sa_is(&rec_s, rec_upper);
        for i in 0..m {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(&mut sa, &mut sorted_lms);
    }
    for elem in sa.iter_mut() {
        *elem -= 1;
    }
    sa
}

fn sa_is_i32(s: &[i32], upper: i32) -> Vec<usize> {
    let s: Vec<usize> = s.iter().map(|&x| x as usize).collect();
    sa_is(&s, upper as usize)
}

fn suffix_array(s: &[i32], upper: i32) -> Vec<usize> {
    assert!(upper >= 0);
    for &elem in s {
        assert!(0 <= elem && elem <= upper);
    }
    sa_is_i32(s, upper)
}

fn lcp_array<T: Ord>(s: &[T], sa: &[usize]) -> Vec<usize> {
    let n = s.len();
    assert!(n >= 1);
    let mut rnk = vec![0; n];
    for i in 0..n {
        rnk[sa[i]] = i;
    }
    let mut lcp = vec![0; n - 1];
    let mut h = 0;
    for i in 0..n - 1 {
        if h > 0 {
            h -= 1;
        }
        if rnk[i] == 0 {
            continue;
        }
        let j = sa[rnk[i] - 1];
        while j + h < n && i + h < n {
            if s[j + h] != s[i + h] {
                break;
            }
            h += 1;
        }
        lcp[rnk[i] - 1] = h;
    }
    lcp
}

// 以上模板代码修改自[ac-library-rs](https://github.com/rust-lang-ja/ac-library-rs/blob/master/src/string.rs)

impl Solution {
    pub fn longest_common_subpath(n: i32, paths: Vec<Vec<i32>>) -> i32 {
        let m = paths.len();
        let mut hi = paths.iter().map(|x| x.len()).min().unwrap();
        let mut lo = 1;

        let mut global_path = vec![];
        let mut belong = vec![];
        let mut sep = n;
        
        // 将 m 条路径连成一条总路径，并用分隔符分隔
        for path in paths.iter() {
            for &city in path.iter() {
                global_path.push(city);
                belong.push(sep - n);
            }
            global_path.push(sep);
            belong.push(sep - n);
            
            // 使用的分隔符是 m 个不属于 [0,n) 且各不相同的数字，这样可以避免两个后缀的最长公共前缀跨越不同的路径
            sep += 1;
        }

        // sa[i] 表示排名为 i 的是哪一个后缀
        let sa = suffix_array(&global_path, sep - 1);

        // lcp[i] 表示排第 i 名和第 i+1 名的后缀的最长公共前缀的长度
        let lcp = lcp_array(&global_path, &sa);

        // 二分答案
        while lo <= hi {
            let mid = (lo + hi) >> 1;
            let mut i = 0;
            let mut found = false;

            while i < lcp.len() {
                if lcp[i] >= mid {
                    let mut vis = vec![false; m];
                    let mut vis_count = 0;
                    let mut j = i;
                    
                    // 找出不小于 mid 的最长的一段 lcp[i..j]，统计这些元素的归属，判断是否覆盖了所有路径。
                    while j < lcp.len() && lcp[j] >= mid {
                        if !vis[belong[sa[j]] as usize] {
                            vis[belong[sa[j]] as usize] = true;
                            vis_count += 1;
                        }
                        j += 1;
                    }
                    
                    // 因为 lcp[i] 表示 sa[i] 和 sa[i+1] 的最长公共前缀，所以还需要计入最后的一个位置。
                    if !vis[belong[sa[j]] as usize] {
                        vis_count += 1;
                    }

                    // 当前范围包含了 m 条路径，说明找到了长度为 mid 的公共子路径。
                    if vis_count == m {
                        found = true;
                        break;
                    }

                    i = j;
                } else {
                    i += 1;
                }
            }

            if found {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        hi as i32
    }
}

```

:::

### 方法三：后缀树

略。


<Utterances />
