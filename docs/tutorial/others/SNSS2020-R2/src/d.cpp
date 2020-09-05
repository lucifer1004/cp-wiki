#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
struct Author {
  ll l, r, w, idx;
  bool operator<(const Author &other) const {
    return l < other.l || (l == other.l && r > other.r);
  }
};
int main() {
  int n;
  cin >> n;
  vector<Author> a;
  for (int i = 0; i < n; ++i) {
    ll l, r, w;
    cin >> l >> r >> w;
    a.push_back(Author{l, r, w, i + 1});
  }
  sort(a.begin(), a.end());
  ll L, R;
  cin >> L >> R;
  ll lo = 0, hi = 1e18;
  while (lo <= hi) {
    ll mid = lo + (hi - lo) / 2;
    ll l = -1, r = -1;
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      if (a[i].w > mid)
        continue;
      if (r < a[i].l)
        l = a[i].l;
      r = max(r, a[i].r);
      if (r >= R)
        break;
    }
    if (l != -1 && l <= L && r >= R)
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  if (lo >= 1e18) {
    cout << -1;
    return 0;
  }
  vector<int> ans;
  for (int i = 0; i < n; ++i)
    if (a[i].w <= lo && a[i].l < R)
      ans.emplace_back(a[i].idx);
  cout << ans.size() << endl;
  for (int i : ans)
    cout << i << " ";
}
