#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll INF = 1e12;

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

struct Recipe {
  vector<int> in;
  int out;
};

class Solution {

public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n, m, s, r;
    read(n), read(m), read(s), read(r);
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF)),
        cost(s + 1, vector<ll>(n + 1, INF));
    vector<ll> lo(s + 1, INF);
    vector<Recipe> recipes;
    for (int i = 0; i < m; ++i) {
      int u, v;
      read(u), read(v);
      dist[u][v] = dist[v][u] = 1;
    }

    for (int k = 1; k <= n; ++k) {
      dist[k][k] = 0;
      for (int i = 1; i <= n; ++i) {
        if (i == k)
          continue;
        for (int j = 1; j <= n; ++j) {
          if (j == k || j == i)
            continue;
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    for (int i = 1; i <= n; ++i) {
      int c;
      read(c);
      for (int j = 0; j < c; ++j) {
        int si;
        read(si);
        lo[si] = 0;
        cost[si][i] = 0;
        for (int k = 1; k <= n; ++k)
          cost[si][k] = min(cost[si][k], dist[i][k]);
      }
    }

    for (int i = 0; i < r; ++i) {
      int k;
      read(k);
      vector<int> v(k);
      for (int j = 0; j < k; ++j)
        read(v[j]);
      sort(v.begin(), v.end());
      int result;
      read(result);
      recipes.push_back({v, result});
    }

    bool changed = true;
    auto valid = [&](Recipe &r) {
      for (int i : r.in)
        if (lo[i] == INF)
          return false;
      return true;
    };
    while (changed) {
      changed = false;
      for (auto &recipe : recipes) {
        if (!valid(recipe))
          continue;
        for (int i = 1; i <= n; ++i) {
          ll c = 0;
          for (int si : recipe.in)
            c += cost[si][i];
          if (c < cost[recipe.out][i]) {
            changed = true;
            lo[recipe.out] = min(lo[recipe.out], c);
            cost[recipe.out][i] = c;
            for (int j = 1; j <= n; ++j)
              cost[recipe.out][j] = min(cost[recipe.out][j], c + dist[i][j]);
          }
        }
      }
    }
    printf("%lld\n", lo[1] == INF ? -1 : lo[1]);
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