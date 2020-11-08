#include <iostream>
#include <vector>

using namespace std;

int main() {
  int h, w, n, m;
  cin >> h >> w >> n >> m;
  int a, b, c, d;
  vector<vector<int>> mat(h, vector<int>(w));
  for (int i = 0; i < n; ++i) {
    cin >> a >> b;
    mat[a - 1][b - 1] = 1;
  }
  for (int i = 0; i < m; ++i) {
    cin >> c >> d;
    mat[c - 1][d - 1] = -1;
  }
  for (int i = 0; i < h; ++i) {
    bool light = false;
    for (int j = 0; j < w; ++j) {
      if (mat[i][j] == 1) {
        light = true;
      } else if (mat[i][j] == -1) {
        light = false;
      } else if (light)
        mat[i][j] = 2;
    }
    light = false;
    for (int j = w - 1; j >= 0; --j) {
      if (mat[i][j] == 1) {
        light = true;
      } else if (mat[i][j] == -1) {
        light = false;
      } else if (light)
        mat[i][j] = 2;
    }
  }
  for (int j = 0; j < w; ++j) {
    bool light = false;
    for (int i = 0; i < h; ++i) {
      if (mat[i][j] == 1) {
        light = true;
      } else if (mat[i][j] == -1) {
        light = false;
      } else if (light)
        mat[i][j] = 2;
    }
    light = false;
    for (int i = h - 1; i >= 0; --i) {
      if (mat[i][j] == 1) {
        light = true;
      } else if (mat[i][j] == -1) {
        light = false;
      } else if (light)
        mat[i][j] = 2;
    }
  }
  int ans = 0;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      ans += mat[i][j] > 0;
  cout << ans;
}