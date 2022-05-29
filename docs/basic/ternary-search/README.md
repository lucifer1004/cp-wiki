---
sidebarDepth: 3
---

# 三分查找

## 基本性质

二分查找要求数组或范围满足一定意义上的有序性，三分查找则是针对数组或范围满足单峰或单谷的特性，即可能是先递增后递减，或先递减后递增。

## 三分套三分

针对高维空间，可以在固定前$k$维的情况下对第$k+1$维进行三分查找，这样一层层进行下去，也就是所谓的三分套三分。

## 练习题

### [CF1394C - Boboniu and String](https://codeforces.com/problemset/problem/1394/C)

::: details 提示一

字符串的顺序并不影响所需要的操作次数，起作用的只有`B`和`N`的个数。

:::

::: details 提示二

如果两重三分都从$0$开始，有可能搜索到$(0,0)$这个点，这是不符合题目要求的。

:::

::: details 参考代码（C++）

<<<@/docs/tutorial/codeforces/1394/src/c.cpp

:::

### [LC1515 - 服务中心的最佳位置](https://leetcode.cn/problems/best-position-for-a-service-centre/)

::: details 提示

可以证明，平面上任意一点到所有给顶点的Euclidean距离之和是一个凸函数（证明过程详见[官方题解](https://leetcode.cn/problems/best-position-for-a-service-centre/solution/fu-wu-zhong-xin-de-zui-jia-wei-zhi-by-leetcode-sol/)），因此可以使用三分套三分的方法求解。

:::

::: details 参考代码（C++）

```cpp

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        double eps = 1e-7;
        auto dist = [&](double xc, double yc) {
            double ans = 0;
            for (const auto& pos: positions) {
                ans += sqrt((pos[0] - xc) * (pos[0] - xc) + (pos[1] - yc) * (pos[1] - yc));
            }
            return ans;
        };
        auto query = [&](double cx) {
            double l = 0, r = 100;
            while (r - l > eps) {
                double ml = l + (r - l) / 3, mr = r - (r - l) / 3;
                double dl = dist(cx, ml), dr = dist(cx, mr);
                if (dl > dr)
                    l = ml;
                else
                    r = mr;
            }
            return dist(cx, l);
        };
        double l = 0, r = 100, ans = 1e9;
        while (r - l > eps) {
            double ml = l + (r - l) / 3, mr = r - (r - l) / 3;
            double dl = query(ml), dr = query(mr);
            if (dl > dr)
                l = ml;
            else
                r = mr;
            ans = min(ans, min(dl, dr));
        }
        return ans;
    }
};
```

:::

<Utterances />
