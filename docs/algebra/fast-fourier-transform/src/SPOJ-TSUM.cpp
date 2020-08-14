#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#define MAXN 131072
#define OFFSET 20000

using namespace std;
typedef complex<double> cd;
const cd I{0, 1};

void change(vector<cd> &f, int n) {
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

void fft(vector<cd> &f, int n, int rev) {
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
  int n;
  cin >> n;
  vector<cd> a(MAXN), a2(MAXN);
  vector<int> a3(MAXN);
  for (int i = 0; i < n; ++i) {
    int m;
    cin >> m;
    a[m + OFFSET] = cd{1, 0};
    a2[(m + OFFSET) << 1] = cd{1, 0};
    a3[(m + OFFSET) * 3] = 1;
  }
  vector<cd> tot(a), b(a);
  fft(tot, MAXN, 1);
  fft(b, MAXN, 1);
  fft(a2, MAXN, 1);
  for (int i = 0; i < MAXN; ++i)
    tot[i] *= b[i] * b[i], a2[i] *= b[i];
  fft(tot, MAXN, -1);
  fft(a2, MAXN, -1);
  for (int i = 0; i < MAXN; ++i) {
    int cnt1 = round(tot[i].real()); // ABC, with permutation
    int cnt2 = round(a2[i].real());  // AAB, no permutation
    int cnt3 = a3[i];                // AAA
    int cnt = (cnt1 - cnt2 * 3 + cnt3 * 2) / 6;
    if (cnt > 0)
      cout << i - OFFSET * 3 << " : " << cnt << endl;
  }
}
