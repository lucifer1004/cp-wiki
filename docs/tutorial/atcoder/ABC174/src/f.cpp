#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

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

template <class T> class FenwickTree {
  int limit;
  vector<T> arr;

  T lowbit(T x) { return x & (-x); }

public:
  FenwickTree(int limit) {
    this->limit = limit;
    arr = vector<T>(limit + 1);
  }

  void update(int idx, T delta) {
    for (; idx <= limit; idx += lowbit(idx))
      arr[idx] += delta;
  }

  T query(int idx) {
    T ans = 0;
    for (; idx > 0; idx -= lowbit(idx))
      ans += arr[idx];
    return ans;
  }
};

class Solution {
public:
  void solve() {
    int n, q;
    read(n), read(q);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
      read(a[i]);
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; ++i) {
      int l, r;
      read(l), read(r);
      queries.emplace_back(l, r);
    }
    vector<int> order(q);
    for (int i = 0; i < q; ++i)
      order[i] = i;
    sort(order.begin(), order.end(),
         [&](int i, int j) { return queries[i].second < queries[j].second; });
    vector<int> ans(q);
    vector<int> pos(n + 1);
    int last = 0;
    FenwickTree<int> ft(n);
    for (int i = 0; i < q; ++i) {
      int k = order[i];
      int l = queries[k].first, r = queries[k].second;
      for (int j = last + 1; j <= r; ++j) {
        if (pos[a[j]] != 0)
          ft.update(pos[a[j]], -1);
        ft.update(j, 1);
        pos[a[j]] = j;
      }
      ans[k] = ft.query(r) - ft.query(l - 1);
      last = r;
    }
    for (int i : ans)
      printf("%d\n", i);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
