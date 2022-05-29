# Leetcode 第235场周赛题解

## Problem A - [截断句子](https://leetcode.cn/problems/truncate-sentence/)

Python大法好。

::: details 参考代码（Python 3）

```python
class Solution:
    def truncateSentence(self, s: str, k: int) -> str:
        return ' '.join(s.split()[:k])
```

:::

## Problem B - [查找用户活跃分钟数](https://leetcode.cn/problems/finding-the-users-active-minutes/)

哈希表套哈希集合去重。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N + K)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {
        unordered_map<int, unordered_set<int>> cnt;
        for (auto &v : logs) {
            cnt[v[0]].insert(v[1]);
        }
        vector<int> ans(k);
        for (auto &p : cnt)
            ans[p.second.size() - 1]++;
        return ans;
    }
};
```

:::

## Problem C - [绝对差值和](https://leetcode.cn/problems/minimum-absolute-sum-difference/)

对$nums1$排序后，我们可以在$\mathcal{O}(\log N)$的时间内找出$nums1$中与$nums2$中某一元素最为接近的两个元素，从而能够确定修改某一个位置可以得到的最小差值。因此，只要枚举修改哪一个位置即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> s(nums1);
        sort(s.begin(), s.end());
        ll tot = 0;
        for (int i = 0; i < n; ++i)
            tot += abs(nums1[i] - nums2[i]);
        ll ans = tot;
        for (int i = 0; i < n; ++i) {
            auto it = lower_bound(s.begin(), s.end(), nums2[i]);
            int delta = INT_MAX;
            if (it != s.end())
                delta = abs(nums2[i] - *it);
            if (it != s.begin())
                delta = min(delta, abs(nums2[i] - *prev(it)));
            ans = min(ans, tot - abs(nums1[i] - nums2[i]) + delta);
        }
        return ans % MOD;
    }
};
```

:::

## Problem D - [序列中不同最大公约数的数目](https://leetcode.cn/problems/number-of-different-subsequences-gcds/)

不妨来思考下面一个问题：

如果序列中能够被$k$整除的数有$m$个，同时能被$k$的某一倍数$tk(t\neq1)$整除的数也有$m$个，那么，有没有可能找到一个子序列，其最大公约数为$k$？

答案是否定的。因为从已知条件可以得出，任意能够被$k$整除的数，一定能够被$tk$整除，因此如果$k$是一个子序列的公约数，那么$tk$也一定是这个子序列的公约数。

从而，我们可以首先统计出对于每一个数$k$，序列中有多少个数能被$k$整除，记为$cnt[k]$，这一步我们需要枚举每个数的因数，总时间消耗为$\mathcal{O}(N\sqrt{K})$，其中$K$为序列中的最大元素。接下来，对于每一个满足$cnt[k]>0$的数$k$，我们需要看是否存在一个倍数$tk$，使得$cnt[tk]=cnt[k]$。如果不存在这样的倍数，则$k$就是一个可行的答案。这一步的时间复杂度可以利用调和级数的性质计算出来，为$\mathcal{O}(K\log K)$。

- 时间复杂度$\mathcal{O}(N\sqrt{K}+K\log K)$，其中$K$为序列中的最大元素。
- 空间复杂度$\mathcal{O}(1)$。

但很遗憾的是，由于Leetcode特殊的计算总时间而非每个用例时间的判题方式，C++直接实现上述算法会超时。

::: details 参考代码（C++，TLE）

```cpp
const int MAXN = 200005;
int cnt[MAXN];

class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int hi = *max_element(nums.begin(), nums.end());
        for (int i = 1; i <= hi; ++i)
            cnt[i] = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j * j <= nums[i]; ++j) {
                if (nums[i] % j == 0) {
                    cnt[j]++;
                    if (j * j != nums[i])
                        cnt[nums[i] / j]++;
                }
            }
        }
        int ans = 0;
        for (int i = hi; i >= 1; --i) {
            if (cnt[i]) {
                bool ok = true;
                for (int j = i * 2; j <= hi; j += i) {
                    if (cnt[j] == cnt[i]) {
                        ok = false;
                        break;
                    }
                }
                ans += ok;
            }
        }
        return ans;
    }
};
```

:::

用Rust则可以顺利通过。

::: details 参考代码（Rust，AC）

```rust
impl Solution {
    pub fn count_different_subsequence_gc_ds(nums: Vec<i32>) -> i32 {
        let mut hi = 0;
        for num in nums.clone() {
            hi = hi.max(num);
        }
        let mut cnt = vec![0usize; hi as usize + 1];
        for num in nums {
            let mut j = 1;
            while j * j <= num {
                if num % j == 0 {
                    cnt[j as usize] += 1;
                    if j * j != num {
                        cnt[(num / j) as usize] += 1;
                    }
                }
                j += 1;
            }
        }
        let mut ans = 0;
        for i in 1..=hi as usize {
            if cnt[i] == 0 {
                continue;
            }
            let mut ok = true;
            for j in (i * 2..=hi as usize).step_by(i) {
                if cnt[j] == cnt[i] {
                    ok = false;
                    break;
                }
            }
            if ok {
                ans += 1;
            }
        }
        ans
    }
}
```

:::

针对Leetcode的这一特殊判题方式，我们可以采取的优化方式是：进行全局的预计算，预先求出从$1$到$MAXK$范围内每一个数的全部因数。这一步我们可以不用$\mathcal{O}(\sqrt{N})$的方式枚举因数，而是用枚举倍数的方式来求解，这样预处理的时间复杂度为$\mathcal{O}(MAXK\log MAXK)$。

后面的求解与之前的方法是一致的。

::: details 参考代码（C++，预计算，AC）

```cpp
const int MAXN = 200005;
int cnt[MAXN];
vector<int> factors[MAXN];
bool init = false;

class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        if (!init) {
            init = true;
            for (int i = 1; i < MAXN; ++i) {
                for (int j = i; j < MAXN; j += i) {
                    factors[j].emplace_back(i);
                }
            }
        }
        
        int hi = *max_element(nums.begin(), nums.end());
        for (int i = 1; i <= hi; ++i)
            cnt[i] = 0;
        for (int num : nums)
            for (int factor : factors[num])
                cnt[factor]++;
        int ans = 0;
        for (int i = hi; i >= 1; --i) {
            if (cnt[i]) {
                bool ok = true;
                for (int j = i * 2; j <= hi; j += i) {
                    if (cnt[j] == cnt[i]) {
                        ok = false;
                        break;
                    }
                }
                ans += ok;
            }
        }
        return ans;
    }
};
```

:::

<Utterances />
