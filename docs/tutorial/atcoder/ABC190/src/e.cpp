#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
const int INF = 0x3f3f3f3f;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  int k;
  cin >> k;
  vector<int> c(k);
  map<int, int> mp;
  for (int i = 0; i < k; ++i)
    cin >> c[i], c[i]--, mp[c[i]] = i;

  vector<vector<int>> d(k, vector<int>(k, INF));
  for (int i = 0; i < k; ++i) {
    queue<pair<int, int>> q;
    vector<bool> vis(n);
    q.emplace(c[i], 0);
    vis[c[i]] = true;
    while (!q.empty()) {
      auto [u, steps] = q.front();
      q.pop();
      if (mp.count(u))
        d[i][mp[u]] = steps;
      for (int v : adj[u]) {
        if (!vis[v]) {
          vis[v] = true;
          q.emplace(v, steps + 1);
        }
      }
    }
  }

  vector<vector<int>> dp(1 << k, vector<int>(k, INF));
  for (int i = 0; i < k; ++i)
    dp[1 << i][i] = 1;
  for (int state = 1; state < (1 << k); ++state)
    for (int last = 0; last < k; ++last) {
      if (state & (1 << last)) {
        for (int nxt = 0; nxt < k; ++nxt) {
          if (!(state & (1 << nxt))) {
            dp[state ^ (1 << nxt)][nxt] = min(dp[state ^ (1 << nxt)][nxt],
                                              dp[state][last] + d[last][nxt]);
          }
        }
      }
    }

  int ans = INF;
  for (int i = 0; i < k; ++i)
    ans = min(ans, dp[(1 << k) - 1][i]);

  if (ans == INF)
    cout << "-1";
  else
    cout << ans;
}