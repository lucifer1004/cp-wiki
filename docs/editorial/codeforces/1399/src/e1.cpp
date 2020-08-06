#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

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

struct Node {
  ll reward;
  int w, n;
  bool operator<(const Node &other) const { return reward < other.reward; }
};

class Solution {
  vector<vector<pair<int, int>>> adj;
  vector<int> leaves;
  ll sum = 0;
  priority_queue<Node> pq;
  void dfs(int u, int p, ll c) {
    bool leaf = true;
    for (auto &[v, w] : adj[u]) {
      if (v == p)
        continue;
      leaf = false;
      dfs(v, u, c + w);
      pq.push(Node{(ll)(w - w / 2) * leaves[v], w, leaves[v]});
      leaves[u] += leaves[v];
    }
    if (leaf) {
      sum += c;
      leaves[u] = 1;
    }
  }

public:
  void solve() {
    int n;
    ll s;
    read(n), read(s);
    adj = vector<vector<pair<int, int>>>(n + 1);
    leaves = vector<int>(n + 1);
    for (int i = 1; i < n; ++i) {
      int u, v, w;
      read(u), read(v), read(w);
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
    }
    dfs(1, 0, 0);
    ll ans = 0;
    while (sum > s) {
      ans++;
      Node top = pq.top();
      pq.pop();
      sum -= top.reward;
      int w = top.w / 2;
      pq.push(Node{(ll)(w - w / 2) * top.n, w, top.n});
    }
    printf("%lld\n", ans);
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