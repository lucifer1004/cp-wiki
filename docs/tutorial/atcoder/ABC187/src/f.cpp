#include <iostream>
#include <vector>

using namespace std;
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<bool>> adj(n, vector<bool>(n));
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u][v] = adj[v][u] = true;
  }
  int mask = 1 << n;
  vector<bool> can(mask);
  for (int i = 1; i < mask; ++i) {
    vector<int> v;
    for (int j = 0; j < n; ++j)
      if (i & (1 << j))
        v.emplace_back(j);
    if (v.size() == 1)
      can[i] = true;
    else {
      bool valid = true;
      for (int j = 0; j < v.size(); ++j) {
        for (int k = j + 1; k < v.size(); ++k)
          if (!adj[v[j]][v[k]]) {
            valid = false;
            break;
          }
        if (!valid)
          break;
      }
      can[i] = valid;
    }
  }

  const int INF = 1e9;
  vector<int> dp(mask, INF);
  for (int i = 1; i < mask; ++i) {
    if (can[i])
      dp[i] = 1;
    else {
      for (int sub = (i - 1) & i; sub; sub = (sub - 1) & i)
        dp[i] = min(dp[i], dp[sub] + dp[i ^ sub]);
    }
  }

  cout << dp[mask - 1];
}
