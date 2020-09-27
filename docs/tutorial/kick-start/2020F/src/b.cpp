#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
using ll = int64_t;

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
public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n, k;
    read(n), read(k);
    vector<pair<ll, ll>> v;
    for (int i = 0; i < n; ++i) {
      ll s, e;
      read(s), read(e);
      v.emplace_back(s, e);
    }
    sort(v.begin(), v.end());
    ll ans = 0, r = 0;
    for (auto vi : v) {
      if (vi.second > r) {
        ll l = max(r, vi.first);
        ll len = vi.second - l;
        ll num = (len - 1) / k + 1;
        r = l + num * k;
        ans += num;
      }
    }
    printf("%d\n", ans);
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