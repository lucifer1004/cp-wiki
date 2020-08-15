#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
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

ll dp[202][202][202];

class Solution {
public:
  void solve() {
    int R, G, B;
    read(R), read(G), read(B);
    vector<int> r(R), g(G), b(B);
    for (int i = 0; i < R; ++i)
      read(r[i]);
    for (int i = 0; i < G; ++i)
      read(g[i]);
    for (int i = 0; i < B; ++i)
      read(b[i]);
    sort(r.rbegin(), r.rend());
    sort(g.rbegin(), g.rend());
    sort(b.rbegin(), b.rend());
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= R; ++i)
      for (int j = 0; j <= G; ++j)
        for (int k = 0; k <= B; ++k) {
          if (i < R && j < G)
            dp[i + 1][j + 1][k] =
                max(dp[i + 1][j + 1][k], dp[i][j][k] + r[i] * g[j]);
          if (i < R && k < B)
            dp[i + 1][j][k + 1] =
                max(dp[i + 1][j][k + 1], dp[i][j][k] + r[i] * b[k]);
          if (j < G && k < B)
            dp[i][j + 1][k + 1] =
                max(dp[i][j + 1][k + 1], dp[i][j][k] + g[j] * b[k]);
        }
    ll ans = 0;
    for (int i = 0; i <= R; ++i)
      for (int j = 0; j <= G; ++j)
        for (int k = 0; k <= B; ++k)
          ans = max(ans, dp[i][j][k]);
    printf("%lld", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}