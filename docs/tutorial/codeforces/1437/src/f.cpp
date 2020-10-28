#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MOD 998244353

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
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i]);
    sort(a.begin(), a.end());
    if (a[n - 2] * 2 > a[n - 1]) {
      printf("0");
      return;
    }

    vector<int> pre(n, -1);
    int l = n - 2;
    for (int r = n - 1; r >= 0; --r) {
      while (l >= 0 && a[l] * 2 > a[r])
        l--;
      if (l >= 0)
        pre[r] = l;
    }

    ll ans = 0;
    vector<ll> dp(n, 1), S(n + 1);
    for (int i = 1; i <= n; ++i)
      S[i] = i;
    for (int i = 1; i < n; ++i) {
      vector<ll> ndp(n, 0);
      for (int j = 0; j < n; ++j) {
        // Case 1: j to j
        int left = pre[j] == -1 ? 0 : pre[j] + 1;
        left -= i - 1;
        if (left > 0)
          ndp[j] = (ndp[j] + dp[j] * left % MOD);

        // Case 2: smaller to j
        if (pre[j] != -1)
          ndp[j] = (ndp[j] + S[pre[j] + 1]) % MOD;
      }
      for (int j = 1; j <= n; ++j)
        S[j] = (S[j - 1] + ndp[j - 1]) % MOD;
      dp = move(ndp);
    }
    printf("%lld", S[n]);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}