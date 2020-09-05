#include <algorithm>
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
    int n, k;
    read(n), read(k);
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i)
      read(x[i]);
    for (int i = 0; i < n; ++i)
      read(y[i]);
    sort(x.begin(), x.end());
    vector<int> L(n + 1), R(n + 1);
    int r = 0;
    for (int l = 0; l < n; ++l) {
      while (r + 1 < n && x[r + 1] <= x[l] + k)
        r++;
      R[l] = L[l] = r - l + 1;
    }
    for (int i = n - 1; i >= 0; --i)
      R[i] = max(R[i], R[i + 1]);
    int ans = 0;
    for (int i = 0; i < n; ++i)
      ans = max(ans, L[i] + R[i + L[i]]);
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