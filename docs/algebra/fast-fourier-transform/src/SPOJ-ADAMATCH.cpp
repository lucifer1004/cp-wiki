#include <cmath>
#include <complex>
#include <cstring>
#include <iostream>
#include <vector>
#define MAXN (1 << 22)

using namespace std;
typedef complex<double> cd;
const cd I{0, 1};
cd a[MAXN], b[MAXN];
void change(cd *f, int n) {
  for (int i = 1, j = n / 2; i < n - 1; i++) {
    if (i < j)
      swap(f[i], f[j]);
    int k = n / 2;
    while (j >= k) {
      j = j - k;
      k = k / 2;
    }
    if (j < k)
      j += k;
  }
}
void fft(cd *f, int n, int rev) {
  change(f, n);
  for (int len = 2; len <= n; len <<= 1) {
    cd omega = exp(I * (2 * M_PI / len * rev));
    for (int j = 0; j < n; j += len) {
      cd now = 1;
      for (int k = j; k < j + len / 2; ++k) {
        cd g = f[k], h = now * f[k + len / 2];
        f[k] = g + h, f[k + len / 2] = g - h;
        now *= omega;
      }
    }
  }
  if (rev == -1)
    for (int i = 0; i < n; ++i)
      f[i] /= n;
}
int main() {
  string s, r;
  cin >> s >> r;
  int n = s.size(), m = r.size();
  int k = 1 << (32 - __builtin_clz(n + m + 1));
  vector<int> cnt(k);
  for (char c : "ACGT") {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 0; i < n; ++i)
      a[i] = s[i] == c;
    for (int i = 0; i < m; ++i)
      b[i] = r[m - i - 1] == c;
    fft(a, k, 1);
    fft(b, k, 1);
    for (int i = 0; i < k; ++i)
      a[i] *= b[i];
    fft(a, k, -1);
    for (int i = 0; i < k; ++i)
      cnt[i] += (int)round(a[i].real());
  }
  int ans = m;
  for (int i = m - 1; i < n; ++i)
    ans = min(ans, m - cnt[i]);
  cout << ans;
}
