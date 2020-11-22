#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
const int INF = 0x3f3f3f3f;

int main() {
  int h, w;
  cin >> h >> w;
  vector<string> a(h);
  int si, sj, gi, gj;
  vector<vector<pair<int, int>>> tele(26);
  for (int i = 0; i < h; ++i) {
    cin >> a[i];
    for (int j = 0; j < w; ++j) {
      if (a[i][j] == 'S')
        si = i, sj = j;
      if (a[i][j] == 'G')
        gi = i, gj = j;
      if (a[i][j] >= 'a' && a[i][j] <= 'z')
        tele[a[i][j] - 'a'].emplace_back(i, j);
    }
  }
  vector<bool> used(26);
  vector<vector<int>> dist(h, vector<int>(w, INF));
  dist[si][sj] = 0;
  queue<pair<int, int>> q;
  q.emplace(si, sj);
  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();
    if (i == gi && j == gj) {
      cout << dist[i][j] << endl;
      return 0;
    }
    for (int k = 0; k < 4; ++k) {
      int ni = i + dy[k], nj = j + dx[k];
      if (ni < 0 || ni >= h || nj < 0 || nj >= w || dist[ni][nj] != INF ||
          a[ni][nj] == '#')
        continue;
      dist[ni][nj] = dist[i][j] + 1;
      q.emplace(ni, nj);
    }
    if (a[i][j] >= 'a' && a[i][j] <= 'z' && !used[a[i][j] - 'a']) {
      used[a[i][j] - 'a'] = true;
      for (auto [ni, nj] : tele[a[i][j] - 'a']) {
        if (dist[ni][nj] == INF) {
          dist[ni][nj] = dist[i][j] + 1;
          q.emplace(ni, nj);
        }
      }
    }
  }
  cout << -1 << endl;
}