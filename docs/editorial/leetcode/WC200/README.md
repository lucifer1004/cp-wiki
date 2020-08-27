# Leetcode 第200场周赛题解

## Problem A - [统计好三元组](https://leetcode-cn.com/problems/count-good-triplets/)

暴力枚举。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = j + 1; k < n; ++k)
                    if (abs(arr[i] - arr[j]) <= a && abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c)
                        ans++;
        return ans;
    }
};
```

:::

## Problem B - [找出数组游戏的赢家](https://leetcode-cn.com/problems/find-the-winner-of-an-array-game/)

直接模拟求解。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int n = arr.size();
        k = min(k, n - 1);
        int ans = arr[0], idx = 1, c = 0;
        while (c < k && idx < n) {
            if (ans > arr[idx])
                c++;
            else {
                ans = arr[idx];
                c = 1;
            }
            idx++;
        }
        return ans;
    }
};
```

:::

## Problem C - [排布二进制网格的最少交换次数](https://leetcode-cn.com/problems/minimum-swaps-to-arrange-a-binary-grid/)

首先计算出每行末尾连续的$0$的数量，然后从最上面一行开始，找到最靠近的一个能满足当前行对$0$的个数需求的行，用冒泡的方式把这一行换上来。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> cnt(n);
        for (int i = 0; i < n; ++i) {
            int j = 0;
            while (j < n && grid[i][n - j - 1] == 0)
                j++;
            cnt[i] = j;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            bool found = false;
            for (int j = i; j < n; ++j) {
                if (cnt[j] >= n - i - 1) {
                    ans += j - i;
                    found = true;
                    for (int k = j; k > i; --k)
                        swap(cnt[k], cnt[k - 1]);
                    break;
                }
            }
            if (!found)
                return -1;
        }
        return ans;
    }
};
```

:::

## Problem D - [最大得分](https://leetcode-cn.com/problems/get-the-maximum-score/)

分别记录当前在第一个数组和第二个数组中能够取得的最大值，每次移动两个数组中较小的那个指针；如果双指针指向的数字相等，则可以将两个最大值进行同步。

::: details 参考代码（C++）

```cpp
typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        ll s1 = 0, s2 = 0;
        int n1 = nums1.size(), n2 = nums2.size();
        int i1 = 0, i2 = 0;
        while (i1 < n1 || i2 < n2) {
            if (i1 == n1 || (i2 < n2 && nums2[i2] < nums1[i1]))
                s2 += nums2[i2++];
            else if (i2 == n2 || nums1[i1] < nums2[i2])
                s1 += nums1[i1++];
            else {
                s1 = max(s1, s2) + nums1[i1];
                s2 = s1;
                i1++, i2++;
            }
        }
        return max(s1, s2) % MOD;
    }
};
```

:::

<Utterances />
