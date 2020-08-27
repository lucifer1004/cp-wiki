#include <bitset>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#define MAXN 300005
#define MAXK 41
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

ll fac[MAXN], rev[MAXN];

ll fexp(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1)
      ans = ans * x % MOD;
    x = x * x % MOD;
    y >>= 1;
  }
  return ans;
}

ll C(int n, int k) {
  if (n < 0 || n < k || k < 0)
    return 0;
  return fac[n] * rev[k] % MOD * rev[n - k] % MOD;
}

ll pre[MAXK][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  read(n), read(m);
  fac[0] = 1, rev[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % MOD;
    rev[i] = fexp(fac[i], MOD - 2);
  }
  vector<pair<int, int>> p(n), c(m);
  vector<int> start(n + 1), end(n + 1);
  for (int i = 0; i < n; ++i) {
    read(p[i].first), read(p[i].second);
    start[p[i].first]++;
    end[p[i].second]++;
  }
  int cnt = 0;
  vector<int> can(n + 1);
  for (int i = 1; i <= n; ++i) {
    cnt += start[i];
    can[i] = cnt;
    cnt -= end[i];
  }
  for (int i = 0; i < m; ++i) {
    read(c[i].first), read(c[i].second);
    c[i].first--, c[i].second--;
  }
  for (int k = 0; k <= 2 * m; ++k) {
    pre[k][0] = 0;
    for (int i = 1; i <= n; ++i)
      pre[k][i] = (pre[k][i - 1] + C(can[i] - k, i - k)) % MOD;
  }
  ll ans = 0;
  for (int i = 0; i < (1 << m); ++i) {
    bitset<32> bs(i);
    int t = bs.count();
    int sig = (t & 1) ? -1 : 1;
    int l = 1, r = n;
    set<int> chosen;
    for (int j = 0; j < m; ++j)
      if (bs.test(j)) {
        chosen.insert(c[j].first);
        chosen.insert(c[j].second);
      }
    for (auto x : chosen) {
      l = max(l, p[x].first);
      r = min(r, p[x].second);
    }
    int k = chosen.size();
    l = max(l, k);
    if (l > r)
      continue;
    ll tot = (pre[k][r] - pre[k][l - 1] + MOD) % MOD;
    ans = (ans + sig * tot + MOD) % MOD;
  }
  printf("%lld", ans);
}