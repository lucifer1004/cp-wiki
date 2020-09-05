#include <cmath>
#include <iostream>
#include <vector>

#define MAXN 5005
#define K 15

using namespace std;
typedef long long ll;
const ll LO = -1e16;
int n, k;

ll st[MAXN * 2][K];

ll query(int l, int r) {
  int len = r - l + 1;
  int j = log2(len);
  return min(st[l][j], st[r - (1 << j) + 1][j]);
}

ll solve(vector<int> &v) {
  int len = v.size();
  vector<ll> s = {0};
  for (int i = 0; i < 2 * len; ++i)
    s.emplace_back(s.back() + v[i % len]);
  int slen = s.size();
  for (int i = 0; i < slen; ++i)
    st[i][0] = s[i];
  for (int j = 1; j <= log2(slen); ++j)
    for (int i = 0; i < slen; ++i) {
      st[i][j] = st[i][j - 1];
      int right = i + (1 << (j - 1));
      if (right < slen)
        st[i][j] = min(st[i][j], st[right][j - 1]);
    }
  ll sum = s[len], hi_r = LO, hi_all = LO;
  int r = k % len;
  for (int i = 1; i < slen; ++i) {
    if (r)
      hi_r = max(hi_r, s[i] - query(max(0, i - r), i - 1));
    hi_all = max(hi_all, s[i] - query(max(0, i - len), i - 1));
  }
  if (k < len)
    return hi_r;
  return max(hi_all, max(sum * (k / len - 1) + hi_all, sum * (k / len) + hi_r));
}

int main() {
  cin >> n >> k;
  vector<int> p(n), c(n);
  for (int i = 0; i < n; ++i)
    cin >> p[i];
  for (int i = 0; i < n; ++i)
    cin >> c[i];
  ll ans = LO;
  vector<bool> vis(n);
  for (int i = 0; i < n; ++i) {
    if (vis[i])
      continue;
    vector<int> v;
    int idx = i;
    while (!vis[p[idx] - 1]) {
      idx = p[idx] - 1;
      vis[idx] = true;
      v.emplace_back(c[idx]);
    }
    ans = max(ans, solve(v));
  }
  cout << ans;
}
