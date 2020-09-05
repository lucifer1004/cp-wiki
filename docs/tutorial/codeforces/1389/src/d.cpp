#include <cstdio>
#include <iostream>

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
public:
  void solve() {
    int n, k;
    read(n), read(k);
    int l1, r1, l2, r2;
    read(l1), read(r1), read(l2), read(r2);
    if (l1 > l2) {
      swap(l1, l2);
      swap(r1, r2);
    }
    ll ans;
    if (r1 < l2) {
      int start = l2 - r1, supply = r2 - l1;
      int need = (k - 1) / supply + 1;
      if (need > n) {
        ans = (ll)n * (start + supply) + 2 * (k - n * supply);
      } else {
        ans = (ll)need * start + k;
        if (need > 1)
          ans = min(ans, (ll)(need - 1) * (start + supply) +
                             (k - (need - 1) * supply) * 2);
      }
    } else {
      ll current = (ll)n * (min(r1, r2) - l2);
      if (current >= k) {
        ans = 0;
      } else {
        k -= current;
        int supply = l2 - l1 + abs(r2 - r1);
        if (supply == 0) {
          ans = 2 * k;
        } else {
          int need = (k - 1) / supply + 1;
          if (need <= n)
            ans = k;
          else
            ans = (ll)n * supply + 2 * (k - n * supply);
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