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

struct Edge {
  int to, w, c;
};

struct Node {
  ll reward;
  int w, n;
  bool operator<(const Node &other) const { return reward < other.reward; }
};

class Solution {
  vector<vector<Edge>> adj;
  vector<int> leaves;
  ll sum = 0;
  priority_queue<Node> pqa, pqb;
  void dfs(int u, int p, ll c) {
    bool leaf = true;
    for (auto &[v, w, t] : adj[u]) {
      if (v == p)
        continue;
      leaf = false;
      dfs(v, u, c + w);
      Node node{(ll)(w - w / 2) * leaves[v], w, leaves[v]};
      if (t == 1)
        pqa.push(node);
      else
        pqb.push(node);
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
    adj = vector<vector<Edge>>(n + 1);
    leaves = vector<int>(n + 1);
    for (int i = 1; i < n; ++i) {
      int u, v, w, c;
      read(u), read(v), read(w), read(c);
      adj[u].push_back(Edge{v, w, c});
      adj[v].push_back(Edge{u, w, c});
    }
    dfs(1, 0, 0);
    ll ans = 0;
    while (sum > s) {
      if (pqa.empty()) {
        ans += 2;
        Node top = pqb.top();
        pqb.pop();
        sum -= top.reward;
        int w = top.w / 2;
        pqb.push(Node{(ll)(w - w / 2) * top.n, w, top.n});
      } else if (pqb.empty()) {
        ans++;
        Node top = pqa.top();
        pqa.pop();
        sum -= top.reward;
        int w = top.w / 2;
        pqa.push(Node{(ll)(w - w / 2) * top.n, w, top.n});
      } else {
        Node ta = pqa.top();
        pqa.pop();
        if (sum - ta.reward <= s) {
          ans++;
          break;
        }
        ll am = ta.reward, am1 = 0;
        int w = ta.w / 2;
        am += (ll)(w - w / 2) * ta.n;
        if (!pqa.empty())
          am1 = ta.reward + pqa.top().reward;
        ll bm = pqb.top().reward;
        if (max(am, am1) <= bm) {
          ans += 2;
          Node top = pqb.top();
          pqb.pop();
          sum -= top.reward;
          int wb = top.w / 2;
          pqb.push(Node{(ll)(wb - wb / 2) * top.n, wb, top.n});
          pqa.push(ta);
        } else {
          ans++;
          sum -= ta.reward;
          pqa.push({(ll)(w - w / 2) * ta.n, w, ta.n});
        }
      }
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