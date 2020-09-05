#include <cstdio>
#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f

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
    vector<int> a(n);
    vector<int> b(n);
    int la = INF, lb = INF;
    for (int i = 0; i < n; ++i)
      read(a[i]), la = min(la, a[i]);
    for (int i = 0; i < n; ++i)
      read(b[i]), lb = min(lb, b[i]);
    ll ans = 0;
    for (int i = 0; i < n; ++i)
      ans += max(a[i] - la, b[i] - lb);
    printf("%lld\n", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  while (t--) {
    Solution solution = Solution();
    solution.solve();
  }
}
