#include <iostream>
#include <vector>
#define MAXN 200005

using namespace std;
typedef long long ll;
vector<int> adj[MAXN]{};
int parent[MAXN]{};
ll lazy[MAXN]{}, val[MAXN];
ll global_lazy = 0;

void build_tree(int u) {
  for (int v : adj[u]) {
    if (v != parent[u]) {
      parent[v] = u;
      build_tree(v);
    }
  }
}

void push_down(int u, ll lazy_acc) {
  lazy_acc += lazy[u];
  val[u] = global_lazy + lazy_acc;
  for (int v : adj[u]) {
    if (v != parent[u])
      push_down(v, lazy_acc);
  }
}

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> edges;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
    edges.emplace_back(u, v);
  }
  build_tree(1);

  int q;
  cin >> q;
  while (q--) {
    int t, e, x;
    cin >> t >> e >> x;
    int u = edges[e - 1].first, v = edges[e - 1].second;
    if (t == 2)
      swap(u, v);
    if (parent[v] == u) {
      global_lazy += x;
      x = -x;
      swap(u, v);
    }
    lazy[u] += x;
  }

  push_down(1, 0);
  for (int i = 1; i <= n; ++i)
    cout << val[i] << endl;
}
