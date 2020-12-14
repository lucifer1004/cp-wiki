#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

vector<int> z_function(string s) {
  int n = (int)s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    vector<int> z = z_function(s);
    int n = (int)s.size();
    vector<int> diff(n + 1);
    for (int i = 1; i < n; ++i) {
      int zi = min(z[i], i);
      diff[i]++, diff[i + zi]--;
    }
    vector<int> num(n);
    for (int i = 1; i < n; ++i)
      num[i] = num[i - 1] + diff[i];
    ll ans = 1;
    for (int ni : num)
      ans = ans * (ni + 1) % MOD;
    cout << ans << endl;
  }
}
