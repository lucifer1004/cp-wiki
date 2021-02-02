#include <atcoder/fenwicktree>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  vector<ll> ans(n);
  atcoder::fenwick_tree<int> ft(n);
  for (int i = 0; i < n; ++i) {
    ans[0] += ft.sum(a[i] + 1, n);
    ft.add(a[i], 1);
  }
  cout << ans[0] << endl;
  for (int i = 1; i < n; ++i) {
    ans[i] = ans[i - 1] + n - 1 - 2 * a[i - 1];
    cout << ans[i] << endl;
  }
}