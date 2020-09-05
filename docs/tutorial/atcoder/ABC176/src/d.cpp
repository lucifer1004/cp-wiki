#include <deque>
#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int h, w, sx, sy, ex, ey;

int main() {
  cin >> h >> w >> sx >> sy >> ex >> ey;
  sx--, sy--, ex--, ey--;
  vector<string> a(h);
  for (int i = 0; i < h; ++i)
    cin >> a[i];
  vector<vector<int>> dist(h, vector<int>(w, INF));
  vector<vector<bool>> vis(h, vector<bool>(w, false));
  deque<pair<int, int>> q;
  q.push_back({sx, sy});
  dist[sx][sy] = 0;
  while (!q.empty()) {
    auto f = q.front();
    q.pop_front();
    int ci = f.first, cj = f.second;
    if (ci == ex && cj == ey) {
      cout << dist[ci][cj];
      return 0;
    }
    if (vis[ci][cj])
      continue;
    vis[ci][cj] = true;
    for (int k = 0; k < 4; ++k) {
      int ni = ci + dy[k], nj = cj + dx[k];
      if (ni < 0 || ni >= h || nj < 0 || nj >= w ||
          dist[ni][nj] <= dist[ci][cj] || a[ni][nj] == '#')
        continue;
      dist[ni][nj] = dist[ci][cj];
      q.push_front({ni, nj});
    }
    for (int ni = ci - 2; ni <= ci + 2; ++ni)
      for (int nj = cj - 2; nj <= cj + 2; ++nj) {
        if (ni < 0 || ni >= h || nj < 0 || nj >= w || a[ni][nj] == '#' ||
            dist[ni][nj] <= dist[ci][cj] + 1)
          continue;
        dist[ni][nj] = dist[ci][cj] + 1;
        q.push_back({ni, nj});
      }
  }
  cout << -1;
}
