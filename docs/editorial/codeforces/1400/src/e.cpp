#include <iostream>
#define N 5005

int n, a[N];

int dfs(int l, int r, int b) {
  if (l == r)
    return a[l] > b;
  int lo = 1e9;
  for (int i = l; i <= r; ++i)
    lo = std::min(lo, a[i]);
  int cl = -1, cr = -1;
  int tot = lo - b, cnt = 0;
  for (int i = l; i <= r; ++i) {
    if (a[i] == b) {
      if (cr != -1)
        tot += dfs(cl, cr, lo);
      cl = -1, cr = -1;
    } else {
      cnt++;
      if (cl == -1)
        cl = i;
      cr = i;
    }
  }
  if (cr != -1)
    tot += dfs(cl, cr, lo);
  return std::min(tot, cnt);
}

int main() {
  std::cin >> n;
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];
  std::cout << dfs(0, n - 1, 0);
}