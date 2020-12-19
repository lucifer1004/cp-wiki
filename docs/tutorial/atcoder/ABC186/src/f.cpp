#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>

using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
typedef tree<int, null_type, less_equal<>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;

int main() {
  int h, w, m;
  cin >> h >> w >> m;
  vector<int> x(m), y(m);
  vector<int> hlimit(h + 1, w), wlimit(w + 1, h);
  for (int i = 0; i < m; ++i) {
    cin >> x[i] >> y[i];
    hlimit[x[i]] = min(hlimit[x[i]], y[i] - 1);
    wlimit[y[i]] = min(wlimit[y[i]], x[i] - 1);
  }
  ll ans = 0;
  for (int i = 1; i <= hlimit[1]; ++i)
    ans += wlimit[i];
  vector<pair<int, int>> v;
  for (int i = 2; i <= wlimit[1]; ++i)
    v.emplace_back(hlimit[i], i);
  sort(v.begin(), v.end());
  indexed_set s;
  int r = 0;
  for (auto [hl, i] : v) {
    while (r < hl && r < hlimit[1])
      s.insert(wlimit[++r]);
    int dup = s.size() - s.order_of_key(i - 1);
    ans += hlimit[i] - dup;
  }
  cout << ans << endl;
}