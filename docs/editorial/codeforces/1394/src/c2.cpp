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
    auto check = [&](int l, bool output) {
      int xl = 0, xr = 5e5, yl = 0, yr = 5e5, zl = -5e5, zr = 5e5;
      for (auto p : vs) {
        xl = max(xl, p.first - l);
        xr = min(xr, p.first + l);
        yl = max(yl, p.second - l);
        yr = min(yr, p.second + l);
        zl = max(zl, p.first - p.second - l);
        zr = min(zr, p.first - p.second + l);
      }
      if (xl > xr || yl > yr || zl > zr)
        return false;
      int zl1 = xl - yr, zr1 = xr - yl;
      if (output) {
        // To avoid (0, 0), we choose right endpoint for both x and y.
        int x = min(xr, zr + yr);
        int y = min(yr, x - zl);
        string s(x, 'B'), t(y, 'N');
        printf("%s", (s + t).c_str());
      }
      return max(zl, zl1) <= min(zr, zr1);
    };
    int lo = 0, hi = 1e6;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      if (check(mid, false))
        hi = mid - 1;
      else
        lo = mid + 1;
    }
    printf("%d\n", lo);
    check(lo, true);
  }
};

int main() {
  Solution solution = Solution();
  solution.solve();
}
