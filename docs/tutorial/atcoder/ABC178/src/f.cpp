#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> a(n), b(n), cb(n + 1);
  vector<bool> taken(n);
  vector<vector<int>> ca(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    ca[a[i]].emplace_back(i);
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
    cb[b[i]]++;
  }
  priority_queue<pair<int, int>> pq;
  for (int i = 1; i <= n; ++i) {
    int lo = min((int)ca[i].size(), cb[i]);
    if (lo)
      pq.emplace(lo, i);
  }
  while (pq.size() >= 2) {
    auto [cx, x] = pq.top();
    pq.pop();
    auto [cy, y] = pq.top();
    pq.pop();
    if (cx == 1 && pq.size() == 1) {
      auto [cz, z] = pq.top();
      pq.pop();
      int px = ca[x].back();
      int py = ca[y].back();
      int pz = ca[z].back();
      taken[px] = taken[py] = taken[pz] = true;
      b[px] = y;
      b[py] = z;
      b[pz] = x;
      ca[x].pop_back();
      ca[y].pop_back();
      ca[z].pop_back();
      cb[x]--;
      cb[y]--;
      cb[z]--;
    } else {
      int px = ca[x].back();
      int py = ca[y].back();
      taken[px] = taken[py] = true;
      b[px] = y;
      b[py] = x;
      ca[x].pop_back();
      ca[y].pop_back();
      cb[x]--;
      cb[y]--;
      if (cx > 1)
        pq.emplace(cx - 1, x);
      if (cy > 1)
        pq.emplace(cy - 1, y);
    }
  }
  int idx = 0;
  if (!pq.empty()) {
    auto [cx, x] = pq.top();
    pq.pop();
    while (cb[x]) {
      while (idx < n && (taken[idx] || a[idx] == x))
        idx++;
      if (idx >= n)
        break;
      b[idx] = x;
      cb[x]--;
      taken[idx] = true;
    }
    if (cb[x]) {
      cout << "No" << flush;
      return 0;
    }
  }
  vector<int> rest;
  for (int i = 1; i <= n; ++i)
    if (cb[i]) {
      for (int j = 0; j < cb[i]; ++j)
        rest.emplace_back(i);
    }
  idx = 0;
  for (int i : rest) {
    while (taken[idx])
      idx++;
    b[idx] = i;
    taken[idx] = true;
  }
  cout << "Yes" << endl;
  for (int i : b)
    cout << i << " ";
  cout << flush;
}