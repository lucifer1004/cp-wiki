#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;

template <typename T> void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-')
      sig = -1;
  for (; isdigit(c); c = getchar())
    x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

const int d[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

class Solution {
public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int r, c;
    read(r), read(c);
    vector<vector<int>> g(r, vector<int>(c));
    priority_queue<tuple<int, int, int>> pq;
    for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j) {
        read(g[i][j]);
        pq.emplace(g[i][j], i, j);
      }
    vector<vector<int>> g0(g);
    while (!pq.empty()) {
      auto [h, i, j] = pq.top();
      pq.pop();
      if (h < g[i][j])
        continue;
      for (int k = 0; k < 4; ++k) {
        int ni = i + d[k][0], nj = j + d[k][1];
        if (ni < 0 || ni >= r || nj < 0 || nj >= c)
          continue;
        if (h - 1 > g[ni][nj]) {
          pq.emplace(h - 1, ni, nj);
          g[ni][nj] = h - 1;
        }
      }
    }

    ll ans = 0;
    for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j)
        ans += g[i][j] - g0[i][j];

    printf("%lld\n", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}