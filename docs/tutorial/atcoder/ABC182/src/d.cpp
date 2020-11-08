#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
  int n;
  cin >> n;
  int a;
  ll ans = 0, hi = 0, sum = 0, pos = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a;
    sum += a;
    hi = max(hi, sum);
    ans = max(ans, pos + hi);
    pos += sum;
  }
  cout << ans;
}
