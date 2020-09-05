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
  void solve(int case_num) {
    int n;
    read(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i]);
    vector<vector<int>> dp(n, vector<int>(4, n));
    for (int k = 0; k < 4; ++k)
      dp[0][k] = 0;
    for (int i = 1; i < n; ++i) {
      for (int last = 0; last < 4; ++last)
        for (int now = 0; now < 4; ++now) {
          if (now == last) {
            if (a[i] == a[i - 1])
              dp[i][now] = min(dp[i][now], dp[i - 1][last]);
            else
              dp[i][now] = min(dp[i][now], dp[i - 1][last] + 1);
          } else if (now > last) {
            if (a[i] > a[i - 1])
              dp[i][now] = min(dp[i][now], dp[i - 1][last]);
            else
              dp[i][now] = min(dp[i][now], dp[i - 1][last] + 1);
          } else {
            if (a[i] < a[i - 1])
              dp[i][now] = min(dp[i][now], dp[i - 1][last]);
            else
              dp[i][now] = min(dp[i][now], dp[i - 1][last] + 1);
          }
        }
    }
    int ans = n;
    for (int k = 0; k < 4; ++k)
      ans = min(ans, dp[n - 1][k]);
    printf("Case #%d: %d\n", case_num, ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
