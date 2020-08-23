#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;
typedef pair<int, int> pii;
int main() {
  int n;
  cin >> n;
  vector<int> a(3 * n);
  for (int i = 0; i < 3 * n; ++i)
    cin >> a[i];
  vector<vector<int>> f(n + 1, vector<int>(n + 1, -INF));
  vector<int> local_opt(n + 1, -INF);
  f[a[0]][a[1]] = f[a[1]][a[0]] = 0;
  local_opt[a[0]] = 0, local_opt[a[1]] = 0;
  vector<pair<pii, int>> updates;
  int triplets = 0, opt = 0;
  for (int i = 2; i < 3 * (n - 1); i += 3) {
    vector<int> b(3);
    for (int j = 0; j < 3; ++j)
      b[j] = a[i + j];
    if (b[0] == b[1] && b[0] == b[2]) {
      triplets++;
      continue;
    }
    updates.clear();
    for (int p = 0; p <= 2; ++p) {
      int q = (p + 1) % 3, s = (p + 2) % 3;
      updates.push_back({{b[p], b[q]}, opt});
      updates.push_back({{b[p], b[q]}, f[b[s]][b[s]] + 1});
      for (int x = 1; x <= n; ++x) {
        updates.push_back({{b[p], x}, local_opt[x]});
        if (b[q] == b[s])
          updates.push_back({{b[p], x}, f[x][b[q]] + 1});
      }
    }
    for (const auto &u : updates) {
      int x = u.first.first, y = u.first.second, val = u.second;
      if (f[x][y] < val) {
        f[x][y] = f[y][x] = val;
        opt = max(opt, val);
        local_opt[x] = max(local_opt[x], val);
        local_opt[y] = max(local_opt[y], val);
      }
    }
  }
  opt = triplets + max(opt, f[a.back()][a.back()] + 1);
  printf("%d", opt);
}
