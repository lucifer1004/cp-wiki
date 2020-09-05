#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

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
    int n;
    read(n);
    set<pair<int, int>> s;
    for (int i = 0; i < n; ++i) {
      string t;
      cin >> t;
      int b = 0;
      for (char c : t)
        b += c == 'B';
      s.insert({b, t.size() - b});
    };
    vector<pair<int, int>> vs(s.begin(), s.end());
    int m = vs.size();
    int tb = 0, tn = 0;
    for (auto p : vs)
      tb = max(tb, p.first), tn = max(tn, p.second);
    auto calc = [&](int B, int N) {
      int dist = 0;
      for (auto &[b, n] : vs) {
        if ((ll)(b - B) * (n - N) >= 0)
          dist = max(dist, max(abs(b - B), abs(n - N)));
        else
          dist = max(dist, abs(b - B) + abs(n - N));
      }
      return dist;
    };
    auto query = [&](int b, int lo) {
      int hi = tn;
      while (lo <= hi) {
        int ml = lo + (hi - lo) / 3, mr = hi - (hi - lo) / 3;
        int ql = calc(b, ml), qr = calc(b, mr);
        if (ql >= qr)
          lo = ml + 1;
        if (ql <= qr)
          hi = mr - 1;
      }
      int extreme = (lo + hi) / 2;
      int dist = calc(b, extreme);
      return make_pair(extreme, dist);
    };
    int lo = 1, hi = tb;
    while (lo <= hi) {
      int ml = lo + (hi - lo) / 3, mr = hi - (hi - lo) / 3;
      int ql = query(ml, 0).second, qr = query(mr, 0).second;
      if (ql >= qr)
        lo = ml + 1;
      if (ql <= qr)
        hi = mr - 1;
    }
    int ansb = (lo + hi) / 2;
    auto [ansn, dist] = query(ansb, 0);
    auto [ansn2, dist2] = query(0, 1);
    if (dist2 < dist) {
      dist = dist2;
      ansn = ansn2;
      ansb = 0;
    }
    printf("%d\n", dist);
    string ans = string(ansb, 'B') + string(ansn, 'N');
    printf("%s\n", ans.c_str());
  }
};

int main() {
  Solution solution = Solution();
  solution.solve();
}
