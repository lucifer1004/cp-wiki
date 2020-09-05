#include <cmath>
#include <complex>
#include <cstdio>
#include <iostream>
#include <vector>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

using namespace std;
typedef complex<double> cd;
const cd I{0, 1};

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

class Solution {
public:
  void solve() {
    int n, x, y;
    read(n), read(x), read(y);
    vector<int> a(n + 1);
    for (int i = 0; i <= n; ++i)
      read(a[i]);
    int q;
    read(q);
    vector<bool> vis(x + y + 1);
    int k = 1 << (32 - __builtin_clz(x * 8 + 2));
    vector<cd> A(k), B(k);
    for (int i = 0; i <= n; ++i)
      A[a[i] + x] = cd{1, 0}, B[x - a[i]] = cd{1, 0};
    fft(A, k, 1);
    fft(B, k, 1);
    for (int i = 0; i < k; ++i)
      A[i] *= B[i];
    fft(A, k, -1);
    for (int i = 2 * x + 1; i < 4 * x; ++i)
      if ((int)round(A[i].real()) > 0)
        vis[i - 2 * x + y] = true;
    int hi = x + y;
    for (int i = 0; i < q; ++i) {
      int l;
      read(l);
      l >>= 1;
      int ans = -1;
      for (int j = 1; j * j <= l; ++j) {
        if (l % j == 0) {
          if (j <= hi && vis[j])
            ans = j;
          if (l / j <= hi && vis[l / j]) {
            ans = l / j;
            break;
          }
        }
      }
      printf("%d ", ans == -1 ? ans : ans * 2);
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}