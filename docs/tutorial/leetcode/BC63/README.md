# Leetcode 第63场双周赛题解

## Problem A - [使每位学生都有座位的最少移动次数](https://leetcode-cn.com/problems/minimum-number-of-moves-to-seat-everyone/)

### 方法一：排序+贪心

座位和学生分别排序后，依次对应即可。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N\log N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def minMovesToSeat(self, seats: List[int], students: List[int]) -> int:
        return sum(abs(seat - student) for seat, student in zip(sorted(seats), sorted(students)))
```

:::


## Problem B - [如果相邻两个颜色均相同则删除当前颜色](https://leetcode-cn.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/)

### 方法一：模拟

两个人的操作互不影响，所以计算出Alice和Bob各自最多操作的次数即可。

- 时间复杂度为$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def winnerOfGame(self, colors: str) -> bool:
        a = 0
        b = 0
        now = '$'
        cnt = 0
        for ch in colors + '#':
            if ch == now:
                cnt += 1
            else:
                if cnt > 0:
                    if now == 'A':
                        a += max(0, cnt - 2)
                    else:
                        b += max(0, cnt - 2)
                now = ch
                cnt = 1
        return a > b
```

:::

## Problem C - [网络空闲的时刻](https://leetcode-cn.com/problems/the-time-when-the-network-becomes-idle/)

### 方法一：BFS

利用BFS计算出每个点到源点的距离，就可以计算出这个点最后一次发送报文的时间，从而求出它最后一次收到回复报文的时间。在所有点都收到最后的回复之后，网络就空闲了。

- 时间复杂度$\mathcal{O}(V+E)$。
- 空间复杂度$\mathcal{O}(V+E)$。

::: details 参考代码（C++）

```cpp
const int INF = 0x3f3f3f3f;

class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        int n = patience.size();
        vector<vector<int>> adj(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> dist(n, INF);
        dist[0] = 0;
        queue<int> q;
        q.emplace(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.emplace(v);
                }
            }
        }
        int ans = 0;
        for (int i = 1; i < n; ++i) {
            int stop = dist[i] * 2;
            int last_send = (stop - 1) / patience[i] * patience[i];
            ans = max(ans, last_send + stop);
        }
        return ans + 1;
    }
};
```

:::

## Problem D - [两个有序数组的第 K 小乘积](https://leetcode-cn.com/problems/kth-smallest-product-of-two-sorted-arrays/)

### 方法一：二分答案+双指针

显然不可能枚举所有的乘积。我们可以转换思路，将求第$K$小乘积变为：给定一个乘积，求出有多少不大于它的乘积。这样我们就可以采用二分答案的方法求解本题。

因为数组中包含零和负数，所以我们这里分别考虑正数、零和负数。

下面我们需要解决的是：给定一个乘积，求出不大于它的乘积的个数。

显然，我们应该分负数、零和正数三种情况分别考虑：

- 如果是一个负数，那么不大于它的乘积必然是由一正一负得来，这部分可以双指针求解。
- 如果是零，那么不大于它的乘积包括所有的负数和零；
- 如果是正数，那么不大于它的乘积包括所有的负数和零；以及两正和两负的情况，这部分可以双指针求解。

- 时间复杂度$\mathcal{O}(N\log C)$。其中$C$是乘积上下界之差。
- 空间复杂度$\mathcal{O}(N\log C)$。

::: details 参考代码（C++）

```cpp
using ll = long long;

class Solution {
public:
    ll kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, ll k) {
        ll lo = -1e10, hi = 1e10;
        int l1 = nums1.size(), l2 = nums2.size();
        
        vector<int> pos1, pos2, neg1, neg2;
        int zero1 = 0, zero2 = 0;
        for (int num : nums1) {
            if (num < 0) {
                neg1.emplace_back(-num);
            } else if (num == 0) {
                zero1++;
            } else {
                pos1.emplace_back(num);
            }
        }
        reverse(neg1.begin(), neg1.end());
        
        for (int num : nums2) {
            if (num < 0) {
                neg2.emplace_back(-num);
            } else if (num == 0) {
                zero2++;
            } else {
                pos2.emplace_back(num);
            }
        }
        reverse(neg2.begin(), neg2.end());
        
        int p1 = pos1.size(), n1 = neg1.size(), p2 = pos2.size(), n2 = neg2.size();
        
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            ll cnt = 0;
            if (mid > 0) {
                cnt += 1LL * zero1 * l2 + 1LL * l1 * zero2 - 1LL * zero1 * zero2; // == 0
                cnt += 1LL * p1 * n2 + 1LL * n1 * p2; // < 0
                int ptr2 = p2 - 1;
                for (int ptr1 = 0; ptr1 < p1 && ptr2 >= 0; ++ptr1) {
                    while (ptr2 >= 0 && 1LL * pos1[ptr1] * pos2[ptr2] > mid)
                        ptr2--;
                    cnt += ptr2 + 1;
                }
                
                ptr2 = n2 - 1;
                for (int ptr1 = 0; ptr1 < n1 && ptr2 >= 0; ++ptr1) {
                    while (ptr2 >= 0 && 1LL * neg1[ptr1] * neg2[ptr2] > mid)
                        ptr2--;
                    cnt += ptr2 + 1;
                }
            } else if (mid < 0) {
                ll amid = -mid;
                int ptr2 = 0;
                for (int ptr1 = p1 - 1; ptr1 >= 0 && ptr2 < n2; --ptr1) {
                    while (ptr2 < n2 && 1LL * pos1[ptr1] * neg2[ptr2] < amid)
                        ptr2++;
                    cnt += n2 - ptr2;
                }
                
                ptr2 = 0;
                for (int ptr1 = n1 - 1; ptr1 >= 0 && ptr2 < p2; --ptr1) {
                    while (ptr2 < p2 && 1LL * neg1[ptr1] * pos2[ptr2] < amid)
                        ptr2++;
                    cnt += p2 - ptr2;
                }
            } else {
                cnt += 1LL * zero1 * l2 + 1LL * l1 * zero2 - 1LL * zero1 * zero2; // == 0
                cnt += 1LL * p1 * n2 + 1LL * n1 * p2; // < 0
            }
            
            if (cnt >= k) {
                hi = mid - 1 ;
            } else {
                lo = mid + 1;
            }            
        }
        return lo;
    }
};
```

:::

<Utterances />
