#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

vector<ll> three;

class Solution {
  ll ans, n, h;
  vector<ll> ca, cb;

  void dfs(vector<ll> &a, vector<ll> &b, ll asum, ll bsum, int n) {
    if (n == 0) {
      if (asum >= h && bsum >= h)
        ans++;
      return;
    }

    for (int i = 1; i <= 3; ++i) {
      ll na = asum, nb = bsum;
      if (i & 1)
        na += a[n - 1];
      if (i & 2)
        nb += b[n - 1];
      if (ca[n - 1] + na < h || cb[n - 1] + nb < h)
        continue;
      if (na >= h && nb >= h) {
        ans += three[n - 1];
        continue;
      }
      dfs(a, b, na, nb, n - 1);
    }
  }

public:
  void solve(int case_num) {
    cin >> n >> h;
    vector<ll> a(n), b(n);

    ca = vector<ll>(n + 1);
    cb = vector<ll>(n + 1);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
      ca[i + 1] = ca[i] + a[i];
    }

    for (int i = 0; i < n; ++i) {
      scanf("%lld", &b[i]);
      cb[i + 1] = cb[i] + b[i];
    }

    if (ca[n] < h || cb[n] < h) {
      cout << "Case #" << case_num << ": " << 0 << endl;
      return;
    }

    ans = 0;

    dfs(a, b, 0, 0, n);

    cout << "Case #" << case_num << ": " << ans << endl;
  }
};

int main() {
  Solution solution;
  ll n = 1;
  for (int i = 0; i < 21; ++i) {
    three.emplace_back(n);
    n *= 3l;
  }
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i)
    solution.solve(i);
}
