# Leetcode 第51场双周赛题解

## Problem A - [将所有数字用字符替换](https://leetcode.cn/problems/replace-all-digits-with-characters/)

模拟。题目已经保证了操作合法性，所以不需要额外处理。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string replaceDigits(string s) {
        for (int i = 0; i < s.size(); i += 2)
            if (i + 1 < s.size())
                s[i + 1] += s[i] - '0';
        
        return s;
    }
};
```

:::

## Problem B - [座位预约管理系统](https://leetcode.cn/problems/seat-reservation-manager/)

用一个`set`维护所有空位置即可。题目已经保证了操作合法性，所以不需要额外处理。

- 初始化时间复杂度为$\mathcal{O}(N\log N)$，`reserve`和`unreserve`操作时间复杂度为$\mathcal{O}(\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class SeatManager {
    set<int> s;
public:
    SeatManager(int n) {
        for (int i = 1; i <= n; ++i)
            s.insert(i);
    }
    
    int reserve() {
        int res = *s.begin();
        s.erase(s.begin());
        return res;
    }
    
    void unreserve(int seatNumber) {
        s.insert(seatNumber);
    }
};
```

:::

## Problem C - [减小和重新排列数组后的最大元素](https://leetcode.cn/problems/maximum-element-after-decreasing-and-rearranging/)

排序后递推即可。注意第一个位置要强制设置为$1$（~~目测不少人都和我一样在这里吃了一发WA~~）。

- 时间复杂度$\mathcal{O}(N\log N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        
        arr[0] = 1;
        
        for (int i = 1; i < n; ++i) {
            arr[i] = min(arr[i], arr[i - 1] + 1);
        }
        
        return arr[n - 1];
    }
};
```

:::

## Problem D - [最近的房间](https://leetcode.cn/problems/closest-room/)

离线处理即可。将所有房间和询问都按照面积降序排列，并用一个`set`维护当前符合条件的房间的编号。

- 时间复杂度$\mathcal{O}(N\log N+Q\log Q+Q\log N)$。
- 空间复杂度$\mathcal{O}(N+Q)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int q = queries.size();
        vector<int> ans(q);
        vector<int> order(q);
        for (int i = 0; i < q; ++i)
            order[i] = i;
        sort(order.begin(), order.end(), [&](int i, int j) {
            return queries[i][1] > queries[j][1]; 
        });
        
        int n = rooms.size();
        sort(rooms.begin(), rooms.end(), [](vector<int> &a, vector<int> &b){
            return a[1] > b[1] || (a[1] == b[1] && a[0] < b[0]);
        });
        
        int ptr = -1;
        set<int> s;
        
        for (int i : order) {
            while (ptr + 1 < n && rooms[ptr + 1][1] >= queries[i][1]) {
                s.insert(rooms[++ptr][0]);
            }
            
            if (s.empty())
                ans[i] = -1;
            else {
                int p = queries[i][0];
                auto it = s.lower_bound(p);
                if (it != s.begin() && (it == s.end() || p - *prev(it) <= *it - p)) {
                    ans[i] = *prev(it);
                } else {
                    ans[i] = *it;
                }
            }
        }
        
        return ans;
    }
};
```

:::

<Utterances />
