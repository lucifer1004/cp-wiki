#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

class Graph {
  vector<ll> val, parent;
  vector<vector<ll>> adj, f;

  void dfs(int u, int fa) {
    int d = adj[u].size();
    for (int i = 0; i < d; i++) {
      int v = adj[u][i];
      if (v != fa)
        dfs(v, parent[v] = u);
    }
  }

  void to_tree() {
    parent = vector<ll>(val.size());
    parent[0] = -1;
    dfs(0, -1);
    for (int i = 0; i < val.size(); ++i)
      adj[i].clear();
    for (int i = 1; i < val.size(); ++i) {
      adj[parent[i]].emplace_back(i);
    }
  }

  void traverse(int u) {
    if (adj[u].empty()) {
      f[u][0] = 0;
      f[u][1] = val[u];
      f[u][2] = INT_MIN;
    } else {
      f[u][0] = 0;
      for (const int j : adj[u]) {
        traverse(j);
        f[u][0] += max(f[j][0], f[j][2]);
      }
      bool open = false;
      ll sec = 0;
      for (const int j : adj[u]) {
        ll m = max(f[j][0], f[j][2]);
        sec += max(m, f[j][1]);
        if (f[j][1] >= m)
          open = true;
      }
      if (!open) {
        ll delta = INT_MAX;
        for (const int j : adj[u]) {
          delta = min(delta, max(f[j][0], f[j][2]) - f[j][1]);
        }
        sec -= delta;
      }
      f[u][2] = sec + val[u];

      f[u][1] = val[u];
      for (const int j : adj[u]) {
        f[u][1] += max(f[j][0], max(f[j][1], f[j][2]) - val[j]) + val[j];
      }
    }
  }

public:
  Graph(vector<ll> &a) {
    val = vector<ll>(a);
    adj = vector<vector<ll>>(a.size(), vector<ll>{});
  }

  void add_edge(int a, int b) {
    adj[a].emplace_back(b);
    adj[b].emplace_back(a);
  }

  ll best() {
    to_tree();
    f = vector<vector<ll>>(val.size(), vector<ll>(3));
    traverse(0);
    return max(f[0][0], max(f[0][1], f[0][2]));
  }
};

void solve(int case_num) {
  int v;
  cin >> v;
  vector<ll> val;
  for (int i = 0; i < v; ++i) {
    int vi;
    cin >> vi;
    val.emplace_back(vi);
  }
  Graph g = Graph(val);
  for (int i = 0; i < v - 1; ++i) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a - 1, b - 1);
  }

  cout << "Case #" << case_num << ": " << g.best() << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
 
   solve(i);
  }
  return 0;
}