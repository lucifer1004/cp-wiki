#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

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

class UnionFind {
  int n;
  vector<int> parent, size;

public:
  UnionFind(int n) {
    this->n = n;
    parent = vector<int>(n);
    size = vector<int>(n, 1);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int idx) {
    if (parent[idx] == idx)
      return idx;
    return parent[idx] = find(parent[idx]);
  }

  void connect(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb) {
      if (size[fa] > size[fb]) {
        parent[fb] = fa;
        size[fa] += size[fb];
      } else {
        parent[fa] = fb;
        size[fb] += size[fa];
      }
    }
  }
};

class Solution {
public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n;
    read(n);
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<int>> b(n, vector<int>(n));
    vector<int> r(n);
    vector<int> c(n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        read(a[i][j]);

    vector<tuple<int, int, int>> edges;
    ll tot = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        read(b[i][j]);
        tot += b[i][j];
        edges.emplace_back(b[i][j], i, n + j);
      }
    sort(edges.rbegin(), edges.rend());
    UnionFind uf(n * 2);

    for (int i = 0; i < n; ++i)
      read(r[i]);
    for (int i = 0; i < n; ++i)
      read(c[i]);

    ll remove = 0;
    for (auto [weight, u, v] : edges) {
      if (uf.find(u) == uf.find(v))
        continue;
      remove += weight;
      uf.connect(u, v);
    }

    printf("%lld\n", tot - remove);
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