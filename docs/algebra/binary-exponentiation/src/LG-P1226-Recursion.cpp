#include <iostream>

using namespace std;
int fexp(int b, int p, int k) {
  if (p == 0)
    return 1 % k;
  int half = fexp(b, p / 2, k);
  int ans = (long long)half * half % k;
  if (p & 1)
    ans = (long long)ans * b % k;
  return ans;
}

int main() {
  int b, p, k;
  cin >> b >> p >> k;
  cout << b << "^" << p << " mod " << k << "=" << fexp(b, p, k);
}
