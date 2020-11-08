#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
  int n;
  ll x;
  cin >> n >> x;
  vector<ll> a(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  unordered_map<ll, ll> v;
  v[x] = 1;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    unordered_map<ll, ll> nv;
    for (auto [c, f] : v) {
      if (i + 1 < n) {
        ll rem = c % a[i + 1];
        nv[c - rem] += f;
        if (rem > 0)
          nv[c + a[i + 1] - rem] += f;
      } else {
        if (c % a[i] == 0)
          nv[0] += f;
      }
    }
    v = move(nv);
  }
  cout << v[0];
}