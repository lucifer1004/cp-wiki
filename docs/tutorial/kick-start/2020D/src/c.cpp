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
  int n, a, b;
  vector<vector<int>> adj;
  vector<int> pa, pb, ac, bc;
  void dfs(int u, vector<int> &path) {
    int l = path.size();
    if (l >= a)
      pa[u] = path[l - a];
    if (l >= b)
      pb[u] = path[l - b];
    path.emplace_back(u);
    ac[u] = 1, bc[u] = 1;
    for (int v : adj[u])
      dfs(v, path);
    path.pop_back();
    if (pa[u] > 0)
      ac[pa[u]] += ac[u];
    if (pb[u] > 0)
      bc[pb[u]] += bc[u];
  }

public:
  void solve(int case_num) {
    read(n), read(a), read(b);
    adj = vector<vector<int>>(n + 1);
    for (int i = 2; i <= n; ++i) {
      int v;
      read(v);
      adj[v].emplace_back(i);
    }
    pa = vector<int>(n + 1);
    pb = vector<int>(n + 1);
    ac = vector<int>(n + 1);
    bc = vector<int>(n + 1);
    vector<int> path;
    dfs(1, path);
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans += (double)(ac[i] + bc[i]) * n;
      ans -= (double)ac[i] * bc[i];
    }
    printf("Case #%d: %.12f\n", case_num, ans / n / n);
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
