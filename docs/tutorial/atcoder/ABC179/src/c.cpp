#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> primes = {2, 3, 5, 7, 11, 13};
  for (int i = 17; i <= n - 1; i += 2) {
    bool is_prime = true;
    for (int j = 0; primes[j] * primes[j] <= i; ++j) {
      if (i % primes[j] == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      primes.emplace_back(i);
  }
  int ans = 0;
  for (int i = 1; i < n; ++i) {
    int k = i;
    int fac = 1;
    for (int j = 0; primes[j] * primes[j] <= k; ++j) {
      if (k % primes[j] == 0) {
        int cnt = 0;
        while (k % primes[j] == 0)
          cnt++, k /= primes[j];
        fac *= (cnt + 1);
      }
    }
    if (k != 1)
      fac *= 2;
    ans += fac;
  }
  cout << ans;
}