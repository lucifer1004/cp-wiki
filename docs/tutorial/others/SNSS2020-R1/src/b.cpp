#include <iostream>

using namespace std;

int main() {
  int a, b, c, d, e;
  cin >> a >> b >> c >> d >> e;
  int ans = a + b + c;
  int be = min(b, e);
  e -= be;
  int cd = min(c, d);
  d -= cd;
  c -= cd;
  if (c > 0)
    e -= min(c * 2, e);
  int dd = (d + 1) / 2;
  int extra = dd * 5 - d * 2;
  ans += dd;
  e = max(e - extra, 0);
  ans += (e + 4) / 5;
  cout << ans;
}
