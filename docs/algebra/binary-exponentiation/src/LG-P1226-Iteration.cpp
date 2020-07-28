#include <iostream>

using namespace std;

int fexp(int b, int p, int k) {
  int ans = 1 % k;
  while (p) {
    if (p & 1)
      ans = (long long)ans * b % k;
    b = (long long)b * b % k;
    p >>= 1;
  }
  return ans % k;
}

int main() {
  int b, p, k;
  cin >> b >> p >> k;
  cout << b << "^" << p << " mod " << k << "=" << fexp(b, p, k);
}
