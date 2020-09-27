#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
typedef long long ll;
const ll mask = (1 << 10) - 1;

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

ll encode(ll state, ll a, ll b) { return state | (a << 50) | (b << 40); }

class Solution {
  vector<vector<int>> adj;
  unordered_map<ll, int> memo;
  void connect(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  int dfs(ll state, ll a, ll b) {
    ll code = encode(state, a, b);
    if (memo.count(code))
      return memo[code];
    bool a_can_move = false, b_can_move = false;
    int lo = 100;
    for (int u : adj[a]) {
      if (state & (1ll << u))
        continue;
      a_can_move = true;
      int result = dfs(state | (1ll << u), b, u);
      lo = min(lo, result);
    }
    if (a_can_move) {
      memo[code] = 1 - lo;
      return memo[code];
    }
    for (int u : adj[b]) {
      if (state & (1ll << u))
        continue;
      b_can_move = true;
      break;
    }
    if (!b_can_move) {
      memo[code] = 0;
      return 0;
    }
    memo[code] = -dfs(state, b, a);
    return memo[code];
  }

public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int s, ra, pa, rb, pb, c;
    read(s), read(ra), read(pa), read(rb), read(pb), read(c);
    int n = s * s;
    adj = vector<vector<int>>(n + 1);
    auto encode = [&](int i, int j) { return (i - 1) * (i - 1) + j; };
    vector<bool> ban(n + 1);
    for (int i = 0; i < c; ++i) {
      int ri, pi;
      read(ri), read(pi);
      ban[encode(ri, pi)] = true;
    }
    for (int i = 1; i <= s; ++i)
      for (int j = 1; j <= i * 2 - 1; ++j) {
        int u = encode(i, j);
        if (j < i * 2 - 1) {
          int v1 = encode(i, j + 1);
          if (!ban[v1])
            connect(u, v1);
        }
        if (j % 2 == 1 && i < s) {
          int v2 = encode(i + 1, j + 1);
          if (!ban[v2])
            connect(u, v2);
        }
      }
    ll start = 0;
    for (int i = 1; i <= n; ++i)
      if (ban[i])
        start |= (1ll << i);
    ll a = encode(ra, pa), b = encode(rb, pb);
    start |= (1ll << a);
    start |= (1ll << b);
    printf("%d\n", dfs(start, a, b));
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