# Leetcode 第80场双周赛题解

## Problem A - [强密码检验器 II](https://leetcode.cn/problems/strong-password-checker-ii/)

### 方法一：模拟

- 时间复杂度 $\mathcal{O}(|S|)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
special_set = set("!@#$%^&*()-+")

class Solution:
    def strongPasswordCheckerII(self, password: str) -> bool:
        n = len(password)
        if n < 8:
            return False
        
        lower = False
        upper = False
        digit = False
        special = False
        for i, p in enumerate(password):
            if i > 0 and p == password[i - 1]:
                return False
            if 'a' <= p <= 'z':
                lower = True
            elif 'A' <= p <= 'Z':
                upper = True
            elif '0' <= p <= '9':
                digit = True
            elif p in special_set:
                special = True
        return lower and upper and digit and special
```

:::

## Problem B - [咒语和药水的成功对数](https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/)

### 方法一：排序 + 双指针

- 时间复杂度 $\mathcal{O}(N\log N + M\log M)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size(), m = potions.size();
        sort(potions.begin(), potions.end());
        
        vector<int> order(n);
        for (int i = 0; i < n; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j){
            return spells[i] < spells[j]; 
        });
        
        vector<int> ans(n);
        int ptr = m;
        for (int i : order) {
            while (ptr >= 1 && 1LL * spells[i] * potions[ptr - 1] >= success)
                ptr--;
            ans[i] = m - ptr;
        }
        
        return ans;
    }
};
```

:::

## Problem C - [替换字符后匹配](https://leetcode.cn/problems/match-substring-after-replacement/)

### 方法一：暴力

- 时间复杂度 $\mathcal{O}(NM+K)$ 。
- 空间复杂度 $\mathcal{O}(|\Sigma|^2 + N + M)$ 。

::: details 参考代码（Rust）

```rust
impl Solution {
    pub fn match_replacement(s: String, sub: String, mappings: Vec<Vec<char>>) -> bool {
        let mut adj = vec![vec![false; 256]; 256];
        for mapping in mappings {
            adj[mapping[0] as u8 as usize][mapping[1] as u8 as usize] = true;
        }

        let s = s.chars().collect::<Vec<_>>();
        let sub = sub.chars().collect::<Vec<_>>();
        let n = s.len();
        let m = sub.len();

        for i in 0..n - m + 1 {
            let mut can = true;
            for j in 0..m {
                if s[i + j] == sub[j] {
                    continue;
                }

                if !adj[sub[j] as u8 as usize][s[i + j] as u8 as usize] {
                    can = false;
                    break;
                }
            }
        
            if can {
                return true;
            }
        }
        
        false
    }
}
```

:::

## Problem D - [统计得分小于 K 的子数组数目](https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/)

### 方法一：前缀和 + 二分

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long ans = 0;
        int n = nums.size();
        vector<long long> pre(n + 1);
        for (int i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] + nums[i - 1];
        
        for (int i = 0; i < n; ++i) {
            int lo = i, hi = n - 1;
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                long long sum = 1LL * (mid - i + 1) * (pre[mid + 1] - pre[i]);
                if (sum >= k)
                    hi = mid - 1;
                else
                    lo = mid + 1;
            }
            ans += hi - i + 1;
        }
        
        return ans;
    }
};
```

:::

<Utterances />
