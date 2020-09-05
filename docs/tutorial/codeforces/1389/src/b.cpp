#include <cstdio>
#include <iostream>
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
    int n, k, z;
    read(n), read(k), read(z);
    vector<int> a(n), s(n + 1), l(n);
    for (int i = 0; i < n; ++i) {
      read(a[i]), s[i + 1] = s[i] + a[i];
      if (i >= 1)
        l[i] = max(l[i - 1], a[i] + a[i - 1]);
    }
    int ans = s[k + 1];
    for (int j = 1; j <= z && 2 * j <= k; ++j)
      ans = max(ans, l[k + 1 - j * 2] * j + s[k + 1 - j * 2]);
    printf("%d\n", ans);
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