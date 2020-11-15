#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;
typedef long long ll;
int main() {
  int h, w;
  cin >> h >> w;
  vector<string> a(h);
  for (int i = 0; i < h; ++i)
    cin >> a[i];
  vector<vector<ll>> dp(h, vector<ll>(w));
  dp[0][0] = 1;
  vector<ll> row(h), col(w), diag(h + w);
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j) {
      if (a[i][j] == '#') {
        row[i] = 0;
        col[j] = 0;
        diag[i - j + w] = 0;
        continue;
      }
      if (i > 0)
        dp[i][j] += col[j];
      if (j > 0)
        dp[i][j] += row[i];
      if (i > 0 && j > 0)
        dp[i][j] += diag[i - j + w];
      dp[i][j] %= MOD;
      col[j] = (col[j] + dp[i][j]) % MOD;
      row[i] = (row[i] + dp[i][j]) % MOD;
      diag[i - j + w] = (diag[i - j + w] + dp[i][j]) % MOD;
    }
  cout << dp[h - 1][w - 1];
}