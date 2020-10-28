#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f

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
    int n, k;
    read(n), read(k);
    vector<int> a(n + 2), b(k + 2);
    a[0] = -INF, a[n + 1] = INF;
    b[0] = 0, b[k + 1] = n + 1;
    for (int i = 1; i <= n; ++i)
      read(a[i]);
    for (int i = 1; i <= k; ++i) {
      read(b[i]);
      if (a[b[i]] - a[b[i - 1]] < b[i] - b[i - 1]) {
        printf("-1");
        return;
      }
    }
    int ans = 0;
    auto handle = [&](int l, int r, int lo, int hi) {
      if (l > r)
        return 0;
      if (l == r)
        return (a[l] >= lo && a[l] <= hi) ? 0 : 1;
      vector<int> LIS;
      for (int i = l; i <= r; ++i) {
        int clo = lo + i - l, chi = hi - r + i;
        if (a[i] < clo || a[i] > chi)
          continue;
        int pos = upper_bound(LIS.begin(), LIS.end(), a[i] - i) - LIS.begin();
        if (pos >= LIS.size())
          LIS.emplace_back(a[i] - i);
        else
          LIS[pos] = a[i] - i;
      }
      return r - l + 1 - (int)LIS.size();
    };
    for (int i = 1; i <= k + 1; ++i)
      ans += handle(b[i - 1] + 1, b[i] - 1, a[b[i - 1]] + 1, a[b[i]] - 1);
    printf("%d", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}