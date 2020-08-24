#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    sort(a.begin(), a.end());
    int lo = 1, hi = a.back() - a.front();
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      int cnt = 0, left = 0;
      for (int i = 1; i < n - 1; ++i) {
        if (a[n - 1] - a[i] < mid)
          break;
        if (a[i] - a[left] >= mid) {
          cnt++;
          left = i;
        }
      }
      if (cnt >= c - 2)
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    cout << hi << endl;
  }
}
