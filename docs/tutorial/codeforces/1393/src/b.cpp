#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename T> void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-')
      sig = -1;
  for (; isdigit(c); c = getchar())
    x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

class Solution {
public:
  void solve() {
    int n, q;
    read(n);
    vector<int> a(n);
    set<pair<int, int>, greater<>> s;
    vector<int> cnt(100005);
    for (int i = 0; i < n; ++i)
      read(a[i]), cnt[a[i]]++;
    for (int i = 1; i < 100005; ++i)
      if (cnt[i])
        s.insert({cnt[i], i});
    read(q);
    int tot = n;
    for (int i = 0; i < q; ++i) {
      char c;
      int x;
      cin >> c;
      read(x);
      s.erase({cnt[x], x});
      if (c == '+')
        cnt[x]++, tot++;
      else
        cnt[x]--, tot--;
      if (cnt[x])
        s.insert({cnt[x], x});
      bool can = false;
      if (tot >= 8) {
        auto it = s.begin();
        if (it->first >= 8)
          can = true;
        else if (it->first >= 6 && next(it) != s.end() && next(it)->first >= 2)
          can = true;
        else if (it->first >= 4 && next(it) != s.end() && next(it)->first >= 4)
          can = true;
        else if (it->first >= 4 && next(it) != s.end() &&
                 next(it)->first >= 2 && next(next(it)) != s.end() &&
                 next(next(it))->first >= 2)
          can = true;
      }
      printf(can ? "YES\n" : "NO\n");
    }
  }
};

int main() {
  Solution solution = Solution();
  solution.solve();
}