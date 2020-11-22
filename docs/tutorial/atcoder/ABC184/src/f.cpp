#include <iostream>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;
int main() {
  int n, t;
  cin >> n >> t;
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  set<int> L, R;
  L.insert(0), R.insert(0);
  int l = n / 2, r = n - l;
  for (int i = 0; i < (1 << l); ++i) {
    int s = 0;
    for (int j = 0; j < l; ++j) {
      if (i & (1 << j))
        s += a[j];
      if (s > t)
        break;
    }
    if (s <= t)
      L.insert(s);
  }
  for (int i = 0; i < (1 << r); ++i) {
    int s = 0;
    for (int j = 0; j < r; ++j) {
      if (i & (1 << j))
        s += a[l + j];
      if (s > t)
        break;
    }
    if (s <= t)
      R.insert(s);
  }
  int ans = 0;
  for (int li : L) {
    auto it = R.lower_bound(t + 1 - li);
    if (it != R.begin())
      --it;
    if (li + *it <= t)
      ans = max(ans, li + *it);
    if (ans == t)
      break;
  }
  cout << ans << endl;
}