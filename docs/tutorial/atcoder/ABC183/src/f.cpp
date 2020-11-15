#include <iostream>
#include <unordered_map>
#include <vector>
#define MOD 1000000007

using namespace std;
typedef long long ll;
int main() {
  int n, q;
  cin >> n >> q;
  vector<int> c(n);
  for (int i = 0; i < n; ++i)
    cin >> c[i];
  vector<int> parent(n);
  vector<unordered_map<int, int>> mem(n);
  for (int i = 0; i < n; ++i) {
    parent[i] = i;
    mem[i][c[i]]++;
  }
  auto find = [&](auto self, int u) {
    if (parent[u] == u)
      return u;
    return parent[u] = self(self, parent[u]);
  };

  auto merge = [&](int u, int v) {
    int pu = find(find, u), pv = find(find, v);
    if (pu == pv)
      return;
    if (mem[pu].size() >= mem[pv].size()) {
      for (auto [t, f] : mem[pv])
        mem[pu][t] += f;
      parent[pv] = pu;
    } else {
      for (auto [t, f] : mem[pu])
        mem[pv][t] += f;
      parent[pu] = pv;
    }
  };

  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      merge(x - 1, y - 1);
    } else {
      int root = find(find, x - 1);
      if (mem[root].count(y))
        cout << mem[root][y] << endl;
      else
        cout << 0 << endl;
    }
  }
}