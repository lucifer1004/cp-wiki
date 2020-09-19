#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll MOD = 998244353;

int main() {
  int n, k;
  cin >> n >> k;
  vector<pair<int, int>> v(k);
  for (int i = 0; i < k; ++i)
    cin >> v[i].first >> v[i].second;
  vector<ll> sum(n + 1);
  sum[1] = 1;
  for (int i = 2; i <= n; ++i) {
    ll curr = 0;
    for (int j = 0; j < k; ++j) {
      if (v[j].first >= i)
        continue;
      int l = max(1, i - v[j].second);
      int r = i - v[j].first;
      curr += sum[r] - sum[l - 1];
    }
    curr %= MOD;
    if (curr < 0)
      curr += MOD;
    sum[i] = (sum[i - 1] + curr) % MOD;
  }
  ll ans = sum[n] - sum[n - 1];
  if (ans < 0)
    ans += MOD;
  cout << ans;
}
