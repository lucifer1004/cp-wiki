#include <cmath>
#include <complex>
#include <iostream>
#define MAXN (1 << 22)

using namespace std;
typedef complex<double> cd;
const cd I{0, 1};
cd tmp[MAXN], a[MAXN], b[MAXN];
void fft(cd *f, int n, int rev) {
  if (n == 1)
    return;
  for (int i = 0; i < n; ++i)
    tmp[i] = f[i];
  for (int i = 0; i < n; ++i) {
    if (i & 1)
      f[n / 2 + i / 2] = tmp[i];
    else
      f[i / 2] = tmp[i];
  }
  cd *g = f, *h = f + n / 2;
  fft(g, n / 2, rev), fft(h, n / 2, rev);
  cd omega = exp(I * (2 * M_PI / n * rev)), now = 1;
  for (int k = 0; k < n / 2; ++k) {
    tmp[k] = g[k] + now * h[k];
    tmp[k + n / 2] = g[k] - now * h[k];
    now *= omega;
  }
  for (int i = 0; i < n; ++i)
    f[i] = tmp[i];
}
int main() {
  int n, m;
  cin >> n >> m;
  int k = 1 << (32 - __builtin_clz(n + m + 1));
  for (int i = 0; i <= n; ++i)
    cin >> a[i];
  for (int j = 0; j <= m; ++j)
    cin >> b[j];
  fft(a, k, 1);
  fft(b, k, 1);
  for (int i = 0; i < k; ++i)
    a[i] *= b[i];
  fft(a, k, -1);
  for (int i = 0; i < k; ++i)
    a[i] /= k;
  for (int i = 0; i < n + m + 1; ++i)
    cout << (int)round(a[i].real()) << " ";
}
