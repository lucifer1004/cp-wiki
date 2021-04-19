#include <cstdio>
#include <iostream>
#include <vector>
#define LMAX 200000
#define LBLKSIZE 500
#define LBLKNUM 400

using namespace std;
typedef long long ll;

template <typename T>
void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-') sig = -1;
  for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

class Solution {
  vector<vector<pair<int, int>>> adj;
  vector<int> limit, from, to;
  vector<ll> toll;
  vector<vector<ll>> acc;
  vector<vector<int>> last;

  void dfs(int u, int p, vector<ll> &gcd_memo, vector<int> &last_memo) {
    for (auto [v, i] : adj[u]) {
      if (v == p) continue;
      int lidx = (limit[i] - 1) / LBLKSIZE;

      // Save current value.
      int last_tmp = last_memo[lidx];
      ll gcd_tmp = gcd_memo[lidx];

      // Modify.
      last_memo[lidx] = i;
      gcd_memo[lidx] = gcd(gcd_memo[lidx], toll[i]);
      last[v] = vector<int>(last_memo);
      acc[v] = vector<ll>(gcd_memo);
      from[i] = u;
      to[i] = v;

      // Do recursion.
      dfs(v, u, gcd_memo, last_memo);

      // Restore.
      last_memo[lidx] = last_tmp;
      gcd_memo[lidx] = gcd_tmp;
    }
  }

 public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n, q;
    read(n), read(q);
    adj = vector<vector<pair<int, int>>>(n + 1);
    limit = vector<int>(n - 1);
    toll = vector<ll>(n - 1);
    from = vector<int>(n - 1);
    to = vector<int>(n - 1);
    acc = vector<vector<ll>>(n, vector<ll>(LBLKNUM));
    last = vector<vector<int>>(n, vector<int>(LBLKNUM, -1));

    for (int i = 0; i < n - 1; ++i) {
      int x, y;
      read(x), read(y), read(limit[i]), read(toll[i]);
      x--, y--;
      adj[x].emplace_back(y, i);
      adj[y].emplace_back(x, i);
    }

    vector<int> last_memo(LBLKNUM, -1);
    vector<ll> gcd_memo(LBLKNUM);
    dfs(0, -1, gcd_memo, last_memo);

    while (q--) {
      ll ans = 0;
      int x, w;
      read(x), read(w);
      x--;
      int lidx = (w - 1) / LBLKSIZE;
      for (int i = 0; i < lidx; ++i) {
        ans = gcd(ans, acc[x][i]);
      }
      while (true) {
        int r = last[x][lidx];
        if (r == -1) break;
        if (w >= limit[r]) ans = gcd(ans, toll[r]);
        x = from[r];
      }

      printf("%lld ", ans);
    }

    printf("\n");
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
