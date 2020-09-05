#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;
typedef long long ll;

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
  int n, m;
  vector<vector<int>> adj;
  vector<int> cnt;
  vector<ll> weight;
  void dfs(int u, int p) {
    cnt[u] = 1;
    for (int v : adj[u])
      if (v != p) {
        dfs(v, u);
        cnt[u] += cnt[v];
      }
    weight[u] = (ll)cnt[u] * (n - cnt[u]);
  }

public:
  void solve() {
    read(n);
    adj = vector<vector<int>>(n + 1);
    cnt = vector<int>(n + 1);
    weight = vector<ll>(n + 1);
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      read(u), read(v);
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
    }
    read(m);
    vector<int> p(m);
    for (int i = 0; i < m; ++i)
      read(p[i]);
    sort(p.rbegin(), p.rend());
    dfs(1, 0);
    int idx = 0;
    if (m > n - 1) {
      for (int i = 1; m - i >= n - 1; ++i)
        p[i] = (ll)p[i - 1] * p[i] % MOD;
      idx = m - n + 1;
    }
    int ans = 0;
    sort(weight.rbegin(), weight.rend());
    for (int i = 0; i < n - 1; ++i)
      ans = ((ll)ans + weight[i] * (i < m ? p[i + idx] : 1)) % MOD;
    printf("%d\n", ans);
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