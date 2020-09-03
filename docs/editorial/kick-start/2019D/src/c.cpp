#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    cout << "Case #" << case_num << ": ";
    int k, n;
    cin >> k >> n;
    k++;
    vector<pair<int, int>> pos(n);
    for (int i = 0; i < n; ++i)
      cin >> pos[i].first;
    for (int i = 0; i < n; ++i)
      cin >> pos[i].second;
    sort(pos.begin(), pos.end());
    ll ans = 1e18;
    int L = k / 2, R = k - k / 2 - 1;
    ll lsum = 0, rsum = 0;
    set<pair<ll, int>> lheap, rheap, r2;
    vector<ll> c(n);
    for (int i = 0; i < L; ++i) {
      ll cost = pos[i].second + pos[L].first - pos[i].first;
      c[i] = cost;
      lheap.emplace(cost, i);
      lsum += cost;
    }
    for (int i = L + 1; i < n; ++i) {
      ll cost = pos[i].second + pos[i].first - pos[L].first;
      c[i] = cost;
      rheap.emplace(cost, i);
      rsum += cost;
      if (rheap.size() > R) {
        r2.insert(*rheap.rbegin());
        rsum -= rheap.rbegin()->first;
        rheap.erase(*rheap.rbegin());
      }
    }
    ll extra = 0;
    for (int mid = L; mid + R < n; ++mid) {
      ans = min(ans, lsum + extra * (L - R) + rsum + pos[mid].second);
      if (mid + 1 < n) {
        lheap.emplace(pos[mid].second - extra, mid);
        lsum += pos[mid].second - extra;
        lsum -= lheap.rbegin()->first;
        lheap.erase(*lheap.rbegin());
        if (rheap.count(make_pair(c[mid + 1], mid + 1))) {
          rheap.erase(make_pair(c[mid + 1], mid + 1));
          rsum -= c[mid + 1];
          rheap.insert(*r2.begin());
          rsum += r2.begin()->first;
          r2.erase(*r2.begin());
        } else {
          r2.erase(make_pair(c[mid + 1], mid + 1));
        }
        extra += pos[mid + 1].first - pos[mid].first;
      }
    }
    cout << ans << endl;
  }
}
