#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const int d[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int main() {
  int n;
  cin >> n;
  vector<ll> lo(4, 1e12), hi(4, -1e12);
  for (int i = 0; i < n; ++i) {
    ll x, y;
    cin >> x >> y;
    for (int k = 0; k < 4; ++k) {
      ll result = x * d[k][0] + y * d[k][1];
      lo[k] = min(lo[k], result);
      hi[k] = max(hi[k], result);
    }
  }
  ll ans = 0;
  for (int k = 0; k < 4; ++k)
    ans = max(ans, hi[k] - lo[k]);
  cout << ans;
}