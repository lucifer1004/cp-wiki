#include <cstdio>
#include <iostream>
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
  bool ok = true;
  int n, m;
  vector<int> p, h, cnt, happy;
  vector<vector<int>> adj;
  void check(int u, int pre) {
    int lo = 0;
    cnt[u] = p[u];
    for (int v : adj[u]) {
      if (v != pre) {
        check(v, u);
        cnt[u] += cnt[v];
        lo += happy[v];
      }
    }
    if ((h[u] + cnt[u]) % 2 != 0)
      ok = false;
    happy[u] = (h[u] + cnt[u]) / 2;
    if (happy[u] < lo || happy[u] > cnt[u])
      ok = false;
  }

public:
  void solve() {
    read(n), read(m);
    adj = vector<vector<int>>(n + 1);
    p = vector<int>(n + 1);
    h = vector<int>(n + 1);
    cnt = vector<int>(n + 1);
    happy = vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
      read(p[i]);
    for (int i = 1; i <= n; ++i)
      read(h[i]);
    for (int i = 1; i < n; ++i) {
      int u, v;
      read(u), read(v);
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
    }
    check(1, 0);
    printf(ok ? "YES\n" : "NO\n");
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  while (t--) {
    Solution solution = Solution();
    solution.solve();
  }
}
