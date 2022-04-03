# Leetcode 第287场周赛题解

## Problem A - [转化时间需要的最少操作数](https://leetcode-cn.com/problems/minimum-number-of-operations-to-convert-time/)

### 方法一：模拟

按要求模拟即可。

- 时间复杂度 $\mathcal{O}(1)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def convertTime(self, current: str, correct: str) -> int:
        sh, sm = map(int, current.split(':'))
        th, tm = map(int, correct.split(':')) 
        delta = (th * 60 + tm) - (sh * 60 + sm)
        ans = 0
        for unit in [60, 15, 5, 1]:
            ans += delta // unit
            delta %= unit
        return ans
```

:::

::: details 参考代码（C++）

```cpp
int seconds(string s) {
    return stoi(s.substr(0, 2)) * 60 + stoi(s.substr(3, 2));
}

class Solution {
public:
    int convertTime(string current, string correct) {
        int start = seconds(current);
        int end = seconds(correct);
        int delta = end - start;
        int ans = 0;
        if (delta >= 60)
            ans += delta / 60, delta %= 60;
        if (delta >= 15)
            ans += delta / 15, delta %= 15;
        if (delta >= 5)
            ans += delta / 5, delta %= 5;
        return ans + delta;
    }
};
```

:::

## Problem B - [找出输掉零场或一场比赛的玩家](https://leetcode-cn.com/problems/find-players-with-zero-or-one-losses/)

### 方法一：模拟

按要求模拟即可。记得最后对结果排序。

- 时间复杂度 $\mathcal{O}(N\log N)$。
- 空间复杂度 $\mathcal{O}(N)$。

::: details 参考代码（Python 3）

```python
class Solution:
    def findWinners(self, matches: List[List[int]]) -> List[List[int]]:
        all_players = set(itertools.chain(*matches))
        lose_count = collections.Counter([loser for winner, loser in matches])
        return [sorted([player for player in all_players if lose_count[player] == i]) for i in range(2)]
```

:::

::: details 参考代码（C++）

```cpp
class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int, int> cnt;
        for (auto &v : matches)
            cnt[v[0]] += 0, cnt[v[1]]++;
        vector<vector<int>> ans(2);
        for (auto [k, v] : cnt)
            if (v <= 1)
                ans[v].push_back(k);
        sort(ans[0].begin(), ans[0].end());
        sort(ans[1].begin(), ans[1].end());
        return ans;
    }
};
```

:::


## Problem C - [每个小孩最多能分到多少糖果](https://leetcode-cn.com/problems/maximum-candies-allocated-to-k-children/)

### 方法一：二分答案

我们发现，“规定每个小孩拿 x 个糖果，能否给 k 个小孩都发足糖果”这个问题具有决策单调性，因此可以二分答案解决本题。

- 时间复杂度 $\mathcal{O}(N\log C)$。
- 空间复杂度 $\mathcal{O}(1)$。

::: details 参考代码（C++）

```cpp
class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        long long lo = 1, hi = 1e12;
        while (lo <= hi) {
            long long mid = (lo + hi) >> 1;
            long long can = 0;
            for (int candy : candies)
                can += candy / mid;
            if (can >= k)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return hi;
    }
};
```

:::

## Problem D - [加密解密字符串](https://leetcode-cn.com/problems/encrypt-and-decrypt-strings/)

### 方法一：预先加密字典中的所有字符串

反向思维：解密具有多解性，但加密过程是确定的。对于解密操作，我们只需要预先将字典中的所有字符串加密，就可以直接求出与目标串对应的原串个数。

- 时间复杂度 $\mathcal{O}(\Sigma\cdot K)$，其中 $\Sigma$ 是所有栈的元素数目之和。
- 空间复杂度 $\mathcal{O}(K)$。

::: details 参考代码（Python 3)

```python
class Encrypter:

    def __init__(self, keys: List[str], values: List[str], dictionary: List[str]):
        self.d = {key: value for key, value in zip(keys, values)}
        self.cnt = collections.Counter(self.encrypt(word) for word in dictionary)


    def encrypt(self, word1: str) -> str:
        return ''.join(self.d[ch] for ch in word1) if all(ch in self.d for ch in word1) else ''


    def decrypt(self, word2: str) -> int:
        return self.cnt[word2]
```

:::

::: details 参考代码（C++）

```cpp
class Encrypter {
    vector<string> v;
    unordered_map<string, int> cnt;
    
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        v = vector<string>(26);
        
        for (int i = 0; i < keys.size(); ++i)
            v[keys[i] - 'a'] = values[i];
    
        for (auto &s : dictionary)
            cnt[encrypt(s)]++;
    }

    string encrypt(string word1) {
        string result;
        for (char ch : word1) {
            if (v[ch - 'a'].empty())
                return "";
            result += v[ch - 'a'];
        }
        return result;
    }
    
    int decrypt(string word2) {
        return cnt[word2];
    }
};
```

:::

### 方法二：字典树

我们也可以用字典树来处理解密操作。

::: details 参考代码（C++）

```cpp
struct Trie {
    bool flag{};
    Trie* children[26]{};
    
    Trie() {}
};

class Encrypter {
    Trie *root;
    vector<string> v;
    unordered_map<string, vector<int>> mp;
    
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        v = vector<string>(26);
        
        for (int i = 0; i < keys.size(); ++i)
            v[keys[i] - 'a'] = values[i], mp[values[i]].push_back(keys[i] - 'a');
    
        root = new Trie();
        for (auto s : dictionary) {
            Trie *p = root;
            for (char c : s) {
                if (p->children[c - 'a'] == nullptr)
                    p->children[c - 'a'] = new Trie();
                p = p->children[c - 'a'];
            }
            p->flag = true;
        }
    }

    string encrypt(string word1) {
        string result;
        for (char ch : word1)
            if (v[ch - 'a'].empty())
                result.push_back(ch);
            else
                result += v[ch - 'a'];
        return result;
    }
    
    int decrypt(string word2) {
        vector<Trie*> possible{root};
        
        for (int i = 0; i < word2.size(); i += 2) {
            vector<Trie*> nxt;
            for (int j : mp[word2.substr(i, 2)]) {
                for (Trie *p : possible) {
                    if (p->children[j] != nullptr)
                        nxt.push_back(p->children[j]);
                }
            }
            
            possible = move(nxt);
        }
        
        int ans = 0;
        
        for (Trie *p : possible)
            ans += p->flag;
        
        return ans;
    }
};
```

:::

<Utterances />
