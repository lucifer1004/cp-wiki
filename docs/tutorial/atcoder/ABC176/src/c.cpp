#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
int main() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  int hi = 0;
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += max(0, hi - a[i]);
    hi = max(hi, a[i]);
  }
  cout << ans;
}
