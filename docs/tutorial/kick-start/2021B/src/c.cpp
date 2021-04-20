#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;
using ll = long long;

template <typename T>
void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-') sig = -1;
  for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

int mod_pow(int a, int b, int mod) {
  int result = 1;

  while (b > 0) {
    if (b & 1) result = 1LL * result * a % mod;
    a = 1LL * a * a % mod;
    b >>= 1;
  }

  return result;
}

bool miller_rabin(int n) {
  if (n < 2) return false;

  // Check small primes.
  for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29})
    if (n % p == 0) return n == p;

  int r = __builtin_ctz(n - 1);
  int d = (n - 1) >> r;

  // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
  for (int a : {2, 7, 61}) {
    int x = mod_pow(a % n, d, n);
    if (x <= 1 || x == n - 1) continue;
    for (int i = 0; i < r - 1 && x != n - 1; i++) x = 1LL * x * x % n;
    if (x != n - 1) return false;
  }

  return true;
}

class Solution {
 public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    ll s;
    read(s);

    if (s < 15) {
      printf("6\n");
      return;
    }

    int n = sqrt(s);
    int b = n;
    while (!miller_rabin(b)) b--;
    int a = b - 1;
    while (!miller_rabin(a)) a--;
    int c = n + 1;
    while (!miller_rabin(c)) c++;

    if (1LL * b * c <= s)
      printf("%lld\n", 1LL * b * c);
    else
      printf("%lld\n", 1LL * a * b);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
