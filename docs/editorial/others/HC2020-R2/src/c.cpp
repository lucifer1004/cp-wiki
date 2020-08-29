#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

#define INF 1e18
#define MOD 1000000007

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

ll n, m, e, k;

void input(vector<ll> &v, ll len, ll mod) {
  ll a, b, c;
  for (int i = 0; i < k; ++i)
    read(v[i]);
  read(a), read(b), read(c);
  for (int i = k; i < len; ++i)
    v[i] = (a * v[i - 2] + b * v[i - 1] + c) % mod;
}

class Solution {
public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    read(n), read(m), read(e), read(k);
    vector<ll> X(n), Y(n), I(e), W(e);
    input(X, n, m);
    input(Y, n, m);
    input(I, e, n * m + n);
    input(W, e, 1e9);
    ll ans = 1, MST = n * m - 1;
    ll MDT = INF;
    vector<set<pair<ll, int>, greater<>>> lheap(n), rheap(n), heaps(n + 1);
    vector<ll> value(n, -INF);
    set<pair<ll, int>, greater<>> gheap;
    vector<ll> edges(n * m + n, 1);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        heaps[i].insert({1, i * m + j});
    for (int i = n * m; i < n * m + n; ++i)
      heaps[n].insert({1, i});
    for (int i = 0; i < n; ++i) {
      if (X[i] == Y[i])
        continue;
      int xi = i * m + X[i], yi = i * m + Y[i];
      if (xi > yi)
        swap(xi, yi);
      for (int j = xi; j < yi; ++j)
        lheap[i].insert({1, j});
      for (int j = i * m; j < xi; ++j)
        rheap[i].insert({1, j});
      for (int j = yi; j < i * m + m; ++j)
        rheap[i].insert({1, j});
      if (!lheap[i].empty() && !rheap[i].empty()) {
        gheap.insert({1, i});
        value[i] = 1;
      }
    }

    for (int i = 0; i < e; ++i) {
      int idx = min(I[i] / m, n);
      if (I[i] != heaps[idx].begin()->second)
        MST += heaps[idx].begin()->first - edges[I[i]];
      heaps[idx].erase({edges[I[i]], I[i]});
      heaps[idx].insert({W[i], I[i]});
      MST += W[i] - heaps[idx].begin()->first;
      if (idx != n) {
        if (lheap[idx].count({edges[I[i]], I[i]})) {
          lheap[idx].erase({edges[I[i]], I[i]});
          lheap[idx].insert({W[i], I[i]});
        }
        if (rheap[idx].count({edges[I[i]], I[i]})) {
          rheap[idx].erase({edges[I[i]], I[i]});
          rheap[idx].insert({W[i], I[i]});
        }
        if (!lheap[idx].empty() && !rheap[idx].empty()) {
          gheap.erase({value[idx], idx});
          value[idx] = lheap[idx].begin()->first + rheap[idx].begin()->first -
                       heaps[idx].begin()->first;
          gheap.insert({value[idx], idx});
        }
      }
      if (!gheap.empty())
        MDT = MST + heaps[n].begin()->first - gheap.begin()->first;
      edges[I[i]] = W[i];
      ans = min(MST, MDT) % MOD * ans % MOD;
    }
    printf("%lld\n", ans);
  }
};

int main() {
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}