#include <cstring>
#include <iostream>
#define MAXN 1005
#define MOD 998244353

using namespace std;
typedef long long ll;

int a[MAXN], b[MAXN], dp[MAXN][MAXN];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= m; ++i)
    cin >> b[i];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      dp[i][j] =
          ((ll)dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + MOD) % MOD;
      if (a[i] == b[j])
        dp[i][j] = ((ll)dp[i][j] + dp[i - 1][j - 1] + 1) % MOD;
    }
  cout << dp[n][m];
}