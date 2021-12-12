# Leetcode 第271场周赛题解

## Problem A - [环和杆](https://leetcode-cn.com/problems/rings-and-rods/)

### 方法一：模拟

按题意模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def countPoints(self, rings: str) -> int:
        cnt = [set() for _ in range(10)]
        for i in range(0, len(rings), 2):
            id = int(rings[i + 1])
            cnt[id].add(rings[i])
        return len([i for i in range(10) if len(cnt[i]) == 3])
```

:::

## Problem B - [子数组范围和](https://leetcode-cn.com/problems/sum-of-subarray-ranges/)

### 方法一：暴力

固定左端点，遍历所有子数组，然后统计最大值和最小值。

- 时间复杂度$\mathcal{O}(N^2)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def subArrayRanges(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        for i in range(n):
            lo = int(1e9)
            hi = -int(1e9)
            for j in range(i, n):
                lo = min(lo, nums[j])
                hi = max(hi, nums[j])
                ans += hi - lo
                
        return ans
```

:::

### 方法二：单调栈

我们也可以用单调栈求出每个元素在多少个子数组中作为最大值，并在多少个子数组中作为最小值。

需要注意，因为可能存在重复元素，为了不重复不遗漏，左右两侧判断时应当一个取等号，另一个不取等号。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode *p = head;
        vector<ListNode *> nodes;
        while (p != nullptr) {
            nodes.push_back(p);
            p = p->next;
        }
        
        int n = nodes.size();
        if (n == 1)
            return nullptr;
        
        int mid = n / 2;
        ListNode *pre = nodes[mid - 1];
        ListNode *nxt = (mid + 1 < n) ? nodes[mid + 1] : nullptr;
        pre->next = nxt;
        
        return nodes[0];
    }
};
```

:::

## Problem C - [给植物浇水 II](https://leetcode-cn.com/problems/watering-plants-ii/)

### 方法一：模拟

> 本题中文翻译与英文不一致：
>
> 中文题面：
> 如果没有足够的水完全浇灌**下一株**植物，他 / 她会立即重新灌满浇水罐。
>
> 英文题面：
> If one does not have enough water to completely water the **current** plant, he/she refills the watering can instantaneously.
>
> 另外，还存在在两人相遇的时候，比较水量和灌满水罐这两个动作的先后顺序的歧义。

在明确题意之后，一步步模拟即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int n = plants.size();
        int a = capacityA, b = capacityB;
        int l = 0, r = n - 1;
        int ans = 0;
        
        while (l <= r) {
            int lastA = a;
            if (l < r || a >= b) {
                if (a >= plants[l]) {
                    a -= plants[l];
                } else {
                    a = capacityA - plants[l];
                    ans++;
                }
            }
                
            if (l < r || lastA < b) {
                if (b >= plants[r]) {
                    b -= plants[r];
                } else {
                    b = capacityB - plants[r];
                    ans++;
                }
            } 
            
            l++, r--;
        }
        
        return ans;
    }
};
```

:::

## Problem D - [摘水果](https://leetcode-cn.com/problems/maximum-fruits-harvested-after-at-most-k-steps/)

### 方法一：双指针

显然在最优的方案中，最多掉头一次。那么就有两种情况：

- 先往左，如果还有步数，再往右
- 先往右，如果还有步数，再往左

第二种情况就相当于将所有坐标取为镜像之后再按照第一种情况处理，所以我们这里只需要考虑第一种情况。

我们首先二分找到$startPos$左侧（含本身）最靠近的一个位置，设为$p$。因为我们规定了是先往左再往右，所以我们的行程所覆盖的区间的左端点不会超过$p$。

接下来，我们从$0$开始枚举左端点的位置。

在确定了最左边的位置之后，我们需要确定最后的落脚点在哪里。显然，在最左边的位置右移时，最后的落脚点必然右移，所以可以使用双指针的方法，一个指针代表左端点，另一个指针代表最后的落脚点。

比较最后的落脚点和$p$的大小，就可以确定覆盖区间的右端点。这时我们需要求左端点到右端点之间的水果总和，显然，这可以通过前缀和解决。但更进一步，可以发现，如果在双指针移动过程中动态维护当前指针区间内的元素和，就不需要建立前缀和数组，从而将额外空间复杂度优化到$\mathcal{O}(1)$。

处理完向左再向右的情况后，按照前面说的，将所有坐标（包括$fruits$中的坐标和$startPos$都取为相反数，也即关于原点的镜像）再计算一次，就可以得到最后的结果。

- 时间复杂度$\mathcal{O}(N)$
- 空间复杂度$\mathcal{O}(1)$

::: details 参考代码（C++）

```cpp
const int INF = 1e9;

class Solution {
    int solve(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        int p = upper_bound(fruits.begin(), fruits.end(), vector<int>{startPos, INF}) - fruits.begin() - 1;
        int ans = 0, r = 0, sum = 0;
        for (int i = 0; i <= p; ++i)
            sum += fruits[i][1];

        for (int l = 0; l <= p; ++l) {
            if (l >= 1)
                sum -= fruits[l - 1][1];
            if (startPos - fruits[l][0] > k)
                continue;
            r = max(r, l);
            while (r + 1 < n && startPos - fruits[l][0] + fruits[r + 1][0] - fruits[l][0] <= k) {
                r++;
                if (r > p)
                    sum += fruits[r][1];
            }
            ans = max(ans, sum);
        }
        
        return ans;
    }
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int ans = solve(fruits, startPos, k);
        
        for (auto &fruit : fruits)
            fruit[0] = -fruit[0];
        reverse(fruits.begin(), fruits.end());
        ans = max(ans, solve(fruits, -startPos, k));
        
        return ans;
    }
};
```

:::

<Utterances />
