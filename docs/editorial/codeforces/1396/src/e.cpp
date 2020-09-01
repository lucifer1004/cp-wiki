#include <cstdio>
#include <iostream>
#include <set>
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

class Solution {
  vector<vector<int>> adj, to_match;
  vector<int> size, cross_match;

  void dfs(int u, int p) {
    size[u] = 1;
    for (int v : adj[u])
      if (v != p) {
        dfs(v, u);
        size[u] += size[v];
      }
  }

  void match_in_subtree(int u, int p) {
    int remain = 1;
    to_match[u].emplace_back(u);
    set<pair<int, int>, greater<>> s;
    s.emplace(1, u);
    for (int v : adj[u])
      if (v != p) {
        match_in_subtree(v, u);
        remain += to_match[v].size();
        s.emplace(to_match[v].size(), v);
      }
    int internal_match = remain - cross_match[u];
    while (internal_match) {
      int first = s.begin()->second;
      s.erase(*s.begin());
      int second = s.begin()->second;
      s.erase(*s.begin());
      printf("%d %d\n", to_match[first].back(), to_match[second].back());
      to_match[first].pop_back();
      to_match[second].pop_back();
      if (!to_match[first].empty())
        s.emplace(to_match[first].size(), first);
      if (!to_match[second].empty())
        s.emplace(to_match[second].size(), second);
      internal_match -= 2;
    }
    for (int v : adj[u])
      if (v != p) {
        // Insert the shorter vector after the longer vector.
        if (to_match[v].size() > to_match[u].size())
          swap(to_match[v], to_match[u]);
        to_match[u].insert(to_match[u].end(), to_match[v].begin(),
                           to_match[v].end());
      }
  }

public:
  void solve() {
    int n;
    ll k;
    read(n), read(k);
    adj = vector<vector<int>>(n + 1);
    size = vector<int>(n + 1);
    cross_match = vector<int>(n + 1);
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      read(u), read(v);
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
    }
    dfs(1, 0);
    ll lo = 0, hi = 0;
    for (int i = 2; i <= n; ++i) {
      lo += size[i] % 2;
      hi += cross_match[i] = min(size[i], n - size[i]);
    }
    if (k < lo || k > hi || (k - lo) % 2 != 0) {
      printf("NO");
      return;
    }
    printf("YES\n");
    int l = 0, r = n;
    while (l <= r) {
      int mid = (l + r) >> 1;
      ll score = 0;
      for (int i = 2; i <= n; ++i) {
        if (cross_match[i] >= mid)
          score += mid + (cross_match[i] - mid) % 2;
        else
          score += cross_match[i];
      }
      if (score >= k)
        r = mid - 1;
      else
        l = mid + 1;
    }
    int &limit = l;
    ll score = 0;
    for (int i = 2; i <= n; ++i) {
      if (cross_match[i] >= limit)
        cross_match[i] = limit + (cross_match[i] - limit) % 2;
      score += cross_match[i];
    }

    // Currently score >= k, we need to make score = k;
    for (int i = 2; i <= n; ++i)
      if (cross_match[i] == limit + 1 && score > k) {
        score -= 2;
        cross_match[i] -= 2;
      }

    to_match = vector<vector<int>>(n + 1);
    match_in_subtree(1, 0);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
