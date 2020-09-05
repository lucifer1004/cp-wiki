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

ll dp[3005][3005][4];

class Solution {
public:
  void solve() {
    int R, C, K;
    read(R), read(C), read(K);
    vector<vector<int>> a(R + 1, vector<int>(C + 1));
    memset(dp, 0, sizeof(0));
    for (int i = 0; i < K; ++i) {
      int r, c, v;
      read(r), read(c), read(v);
      a[r][c] = v;
    }
    for (int i = 1; i <= R; ++i)
      for (int j = 1; j <= C; ++j) {
        for (int k = 0; k <= 3; ++k)
          dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][k]);
        for (int k = 0; k <= 3; ++k)
          dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k]);
        if (a[i][j])
          for (int k = 3; k > 0; --k)
            dp[i][j][k] = max(dp[i][j][k], dp[i][j][k - 1] + a[i][j]);
      }
    ll ans = 0;
    for (int i = 0; i <= 3; ++i)
      ans = max(ans, dp[R][C][i]);
    printf("%lld", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
