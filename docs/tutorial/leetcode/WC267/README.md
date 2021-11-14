# Leetcode 第267场周赛题解

## Problem A - [买票需要的时间](https://leetcode-cn.com/problems/time-needed-to-buy-tickets/)

### 方法一：模拟

按题意进行模拟。

- 时间复杂度$\mathcal{O}(NT)$。其中$T=tickets[k]$为第$k$个人需要购票的数量。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        queue<int> q;
        int n = tickets.size();
        for (int i = 0; i < n; ++i)
            q.emplace(i);
        int t = 0;
        while (tickets[k]) {
            int u = q.front();
            q.pop();
            tickets[u]--;
            t++;
            if (tickets[u])
                q.emplace(u);
        }
        return t;
    }
};
```

:::

### 方法二：一次遍历

实际上，我们只需要一次遍历就可以解决本题。对于第$k$个及之前的人来说，在第$k$个人刚好买完时，他们的购票数量为$\min(tickets[i],tickets[k])$；而之后的人，购票数量为$\min(tickets[i],tickets[k]-1)$。求和即可得到答案。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        return sum(min(t, tickets[k]) if i <= k else min(t, tickets[k] - 1) for i, t in enumerate(tickets))
```

:::

## Problem B - [反转偶数长度组的节点](https://leetcode-cn.com/problems/reverse-nodes-in-even-length-groups/)

### 方法一：模拟

我们可以将链表转换成数组后按要求进行反转，最后再更新链表中的数值即可。

- 时间复杂度$\mathcal{O}(N)$。
- 空间复杂度$\mathcal{O}(N)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        vector<int> v;
        ListNode *p = head;
        while (p != nullptr) {
            v.emplace_back(p->val);
            p = p->next;
        }
        
        int n = v.size();
        int i = 0, g = 1;
        while (i < n) {
            if (g > n - i)
                g = n - i;
            if (g % 2 == 0)
                reverse(v.begin() + i, v.begin() + i + g);
            i += g;
            g++;
        }
        
        p = head;
        for (int vi : v) {
            p->val = vi;
            p = p->next;
        }
        
        return head;
    }
};
```

:::

## Problem C - [解码斜向换位密码](https://leetcode-cn.com/problems/decode-the-slanted-ciphertext/)

### 方法一：模拟

理清题意后可知，我们由加密后字符串的长度和行数就可以求得矩阵的列数，然后沿着对角线方向依次取出字符即可。

因为题目说明了答案唯一且结尾不为空格，我们将上面操作得到的字符串末尾的空格全部去除即可得到答案。

- 时间复杂度$\mathcal{O}(|S|)$。
- 空间复杂度$\mathcal{O}(|S|)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        int n = encodedText.size();
        int cols = n / rows;
        string ans;
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                if (i + j >= cols)
                    break;
                int idx = j * cols + i + j;
                ans.push_back(encodedText[idx]);
            }
        }
        while (!ans.empty() && ans.back() == ' ')
            ans.pop_back();
        return ans;
    }
};
```

:::

## Problem D - [处理含限制条件的好友请求](https://leetcode-cn.com/problems/process-restricted-friend-requests/)

### 方法一：并查集

容易想到用并查集来维护好友关系。问题是如何处理限制条件。

假设当前好友请求为$(u,v)$，对于$(p,q)$这样一条限制条件来说，连接$(u,v)$而导致$(p,q)$相连，有两种情况：

1. $(u,p)$已经相连，$(v,q)$已经相连
2. $(u,q)$已经相连，$(v,p)$已经相连

如果这两种情况都得到排除，则这一条限制条件就不会被违反。

- 时间复杂度$\mathcal{O}(QR\alpha(N))$。其中$Q$为查询数，$R$为限制数，$N$为用户数，$\alpha(x)$为Ackerman函数的反函数，在本题的数据范围内可近似认为常数。
- 空间复杂度$\mathcal{O}(Q+N)$。

::: details 参考代码（C++）

```cpp
class UnionFind {
  int n;
  vector<int> parent, size;

public:
  UnionFind(int n) {
    this->n = n;
    parent = vector<int>(n);
    size = vector<int>(n, 1);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int idx) {
    if (parent[idx] == idx)
      return idx;
    return parent[idx] = find(parent[idx]);
  }

  void connect(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb) {
      if (size[fa] > size[fb]) {
        parent[fb] = fa;
        size[fa] += size[fb];
      } else {
        parent[fa] = fb;
        size[fb] += size[fa];
      }
    }
  }
};

class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        vector<bool> ans;
        
        UnionFind uf(n);
        
        for (auto &req : requests) {
            int u = req[0], v = req[1];
            if (uf.find(u) == uf.find(v))
                ans.push_back(true);
            else {
                bool valid = true;
                for (auto &res : restrictions) {
                    int p = res[0], q = res[1];
                    if ((uf.find(u) == uf.find(p) && uf.find(v) == uf.find(q))
                        || (uf.find(u) == uf.find(q) && uf.find(v) == uf.find(p))) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    uf.connect(u, v);
                    ans.push_back(true);
                } else
                    ans.push_back(false);
            }
        }
        
        return ans;
    }
};
```

:::

<Utterances />
