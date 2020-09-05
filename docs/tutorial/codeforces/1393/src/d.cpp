#include <cstdio>
#include <iostream>
#include <vector>
#define MAXN 2005

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

int fa[MAXN][MAXN], fb[MAXN][MAXN], fc[MAXN][MAXN], fd[MAXN][MAXN];

class Solution {
public:
  void solve() {
    int n, m;
    read(n), read(m);
    vector<string> a(n);
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        if (i == 1 || j == 1 || a[i - 1][j - 1] != a[i - 2][j - 1] ||
            a[i - 1][j - 1] != a[i - 1][j - 2]) {
          fa[i][j] = 1;
          continue;
        }
        fa[i][j] = min(fa[i - 1][j], fa[i][j - 1]) + 1;
      }

    for (int i = 1; i <= n; ++i)
      for (int j = m; j >= 1; --j) {
        if (i == 1 || j == m || a[i - 1][j - 1] != a[i - 2][j - 1] ||
            a[i - 1][j - 1] != a[i - 1][j]) {
          fb[i][j] = 1;
          continue;
        }
        fb[i][j] = min(fb[i - 1][j], fb[i][j + 1]) + 1;
      }

    for (int i = n; i >= 1; --i)
      for (int j = 1; j <= m; ++j) {
        if (i == n || j == 1 || a[i - 1][j - 1] != a[i][j - 1] ||
            a[i - 1][j - 1] != a[i - 1][j - 2]) {
          fc[i][j] = 1;
          continue;
        }
        fc[i][j] = min(fc[i + 1][j], fc[i][j - 1]) + 1;
      }

    for (int i = n; i >= 1; --i)
      for (int j = m; j >= 1; --j) {
        if (i == n || j == m || a[i - 1][j - 1] != a[i][j - 1] ||
            a[i - 1][j - 1] != a[i - 1][j]) {
          fd[i][j] = 1;
          continue;
        }
        fd[i][j] = min(fd[i + 1][j], fd[i][j + 1]) + 1;
      }

    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        ans += min(min(fa[i][j], fb[i][j]), min(fc[i][j], fd[i][j]));
    printf("%lld", ans);
  }
};

int main() {
  Solution solution = Solution();
  solution.solve();
}