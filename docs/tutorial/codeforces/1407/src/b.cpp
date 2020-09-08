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

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

class Solution {
public:
  void solve() {
    int n;
    read(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i]);
    vector<bool> vis(n);
    vector<int> ans(n);
    int g = 0;
    for (int i = 0; i < n; ++i) {
      int hi = -1, hidx = -1;
      for (int j = 0; j < n; ++j) {
        if (vis[j])
          continue;
        int gj = gcd(g, a[j]);
        if (gj > hi) {
          hi = gj;
          hidx = j;
        }
      }
      ans[i] = a[hidx];
      vis[hidx] = true;
      g = hi;
    }
    for (int i : ans)
      printf("%d ", i);
    printf("\n");
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
