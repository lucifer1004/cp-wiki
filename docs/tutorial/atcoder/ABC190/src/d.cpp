#include <iostream>
#include <unordered_set>

using namespace std;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  unordered_set<ll> factors;
  ll x = n * 2;
  for (int i = 1; 1LL * i * i <= x; ++i) {
    if (x % i == 0) {
      factors.insert(i);
      factors.insert(x / i);
    }
  }

  int ans = 0;
  for (ll factor : factors)
    if ((x / factor + 1 - factor) % 2 == 0)
      ans++;

  cout << ans;
}