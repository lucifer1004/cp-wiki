#include <cmath>
#include <complex>
#include <iostream>
#define MAXN (1 << 22)

using namespace std;
typedef complex<double> cd;
const cd I{0, 1};
cd a[MAXN], b[MAXN];
void change(cd *f, int n) {
  int i, j, k;
  for (int i = 1, j = n / 2; i < n - 1; i++) {
    if (i < j)
      swap(f[i], f[j]);
    k = n / 2;
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
  for (int i = 0; i < n + m + 1; ++i)
    cout << (int)round(a[i].real()) << " ";
}
