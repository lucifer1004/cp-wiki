#include <cstdio>
#include <iostream>
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
public:
  void solve() {
    int n;
    read(n);
    vector<int> a(n), cnt(n + 1);
    for (int i = 0; i < n; ++i)
      read(a[i]), cnt[a[i]]++;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
      int &t = cnt[i];
      if (t >= 4)
        ans += (ll)t * (t - 1) * (t - 2) * (t - 3) / 24;
    }
    for (int i = 3; i < n; ++i) {
      vector<int> l(n + 1), r(n + 1);
      ll cnt = 0;
      for (int j = 0; j < i; ++j)
        r[a[j]]++;
      for (int j = 0; j < i; ++j) {
        if (a[j] == a[i])
          ans += cnt;
        else {
          cnt -= l[a[j]] * r[a[j]];
          l[a[j]]++, r[a[j]]--;
          cnt += l[a[j]] * r[a[j]];
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