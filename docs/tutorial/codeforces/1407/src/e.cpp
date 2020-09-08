#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

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

class Solution {

public:
  void solve() {
    int n, m;
    read(n), read(m);
    vector<vector<pair<int, int>>> in(n + 1);
    for (int i = 0; i < m; ++i) {
      int u, v, t;
      read(u), read(v), read(t);
      if (u == v)
        continue;
      t++;
      in[v].emplace_back(u, t);
    }

    queue<pair<int, int>> q;
    q.emplace(n, 0);
    vector<int> close(n + 1);
    vector<int> dist(n + 1);
    vector<bool> vis(n + 1);
    vis[n] = true;
    while (!q.empty()) {
      auto [v, d] = q.front();
      dist[v] = d;
      q.pop();
      for (auto [u, t] : in[v]) {
        if (vis[u])
          continue;
        if ((t == 1 && close[u] == 2) || (t == 2 && close[u] == 1)) {
          vis[u] = true;
          q.emplace(u, d + 1);
        } else
          close[u] = t;
      }
    }
    if (!vis[1])
      printf("-1\n");
    else
      printf("%d\n", dist[1]);
    for (int i = 1; i <= n; ++i)
      printf("%d", min(1, 2 - close[i]));
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
