#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class Solution {
public:
  void solve(int case_num) {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), ones(64), zeros(64);
    for (int i = 0; i < n; ++i) {
      ll d;
      cin >> d;
      bitset<64> bs(d);
      for (int j = 0; j < 64; ++j) {
        if (bs[j])
          ones[j]++;
        else
          zeros[j]++;
      }
    }

    vector<ll> min_val(64);
    ll last = 0;
    for (int i = 0; i <= 50; ++i) {
      ll num = (1ll << i);
      last += (ll)min(ones[i], zeros[i]) * num;
      min_val[i] = last;
    }

    ll sum = 0;
    bitset<64> k(0);
    for (int i = 50; i >= 0; --i) {
      ll num = (1ll << i);
      ll one = num * zeros[i];
      ll zero = num * ones[i];
      if (sum + one + (i > 0 ? min_val[i - 1] : 0) <= m) {
        k.set(i);
        sum += one;
      } else if (sum + zero + (i > 0 ? min_val[i - 1] : 0) <= m) {
        sum += zero;
      } else {
        cout << "Case #" << case_num << ": " << -1 << endl;
        return;
      }
    }

    ll ans = k.to_ullong();
    cout << "Case #" << case_num << ": " << ans << endl;
  }
};

int main() {
  Solution solution;
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i)
    solution.solve(i);
}
