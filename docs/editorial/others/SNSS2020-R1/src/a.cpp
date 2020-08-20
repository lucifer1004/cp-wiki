#include <climits>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#define MAXN 20000005

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

int dict[MAXN];

class Solution {
public:
  void solve() {
    int n;
    read(n);
    vector<vector<int>> a(n, vector<int>(4));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < 4; ++j) {
        int aij;
        read(aij);
        a[i][j] = aij << 1;
      }
    ll ans = 0;
    for (int k = 0; k <= 1; ++k) {
      int lo = INT_MAX, hi = 0;
      set<int> ts;
      for (int i = 0; i < n; ++i) {
        lo = min(lo, a[i][k]);
        hi = max(hi, a[i][k + 2]);
        int c = (a[i][k] + a[i][k + 2]) >> 1;
        ts.insert(a[i][k]);
        ts.insert(c);
        ts.insert(a[i][k + 2]);
      }
      vector<int> v(ts.begin(), ts.end());
      int m = v.size();
      for (int i = 0; i < m; ++i)
        dict[v[i]] = i;
      vector<int> start(m), mid(m), end(m);
      for (int i = 0; i < n; ++i) {
        int c = (a[i][k] + a[i][k + 2]) >> 1;
        start[dict[a[i][k]]]++;
        mid[dict[c]]++;
        end[dict[a[i][k + 2]]]++;
      }
      ll tot = 0;
      for (int i = 0; i < n; ++i)
        tot += a[i][k] - lo;
      ll best = tot;
      int c1 = n, c2 = 0, c3 = 0, c4 = 0;
      for (int i = 0; i < m; ++i) {
        if (i > 0)
          tot += (ll)(c2 + c4 - (c1 + c3)) * (v[i] - v[i - 1]);
        c1 -= start[i];
        c2 += start[i];
        c2 -= mid[i];
        c3 += mid[i];
        c3 -= end[i];
        c4 += end[i];
        if (v[i] % 2 == 0)
          best = min(best, tot);
      }
      ans += best;
    }
    printf("%lld", ans / 2);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
