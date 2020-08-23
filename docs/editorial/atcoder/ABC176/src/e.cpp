#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
int main() {
  int h, w, m;
  cin >> h >> w >> m;
  vector<int> hc(h + 1), wc(w + 1);
  vector<pair<int, int>> p(m);
  for (int i = 0; i < m; ++i)
    cin >> p[i].first >> p[i].second, hc[p[i].first]++, wc[p[i].second]++;
  set<pair<int, int>> s(p.begin(), p.end());
  int hm = *max_element(hc.begin(), hc.end());
  int wm = *max_element(wc.begin(), wc.end());
  vector<int> vh, vw;
  for (int i = 1; i <= h; ++i)
    if (hc[i] == hm)
      vh.emplace_back(i);
  for (int i = 1; i <= w; ++i)
    if (wc[i] == wm)
      vw.emplace_back(i);
  int sh = vh.size(), sw = vw.size();
  if (sh * sw > m) {
    cout << hm + wm;
    return 0;
  }
  for (int i : vh)
    for (int j : vw)
      if (!s.count({i, j})) {
        cout << hm + wm;
        return 0;
      }
  cout << hm + wm - 1;
}
