#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  int lo = *min_element(a.begin(), a.end());

  unordered_map<int, int> memo;
  for (int ai : a) {
    for (int j = 1; j * j <= ai && j < lo; ++j) {
      if (ai % j == 0) {
        memo[j] = __gcd(ai, memo[j]);
        if (ai / j < lo)
          memo[ai / j] = __gcd(ai, memo[ai / j]);
      }
    }
  }

  int ans = 1;
  for (auto [factor, terminal] : memo)
    if (factor == terminal)
      ans++;

  cout << ans;
}