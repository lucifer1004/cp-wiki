#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef long long ll;
int main() {
  ll n, x, m;
  cin >> n >> x >> m;
  map<ll, int> mp;
  int idx = 0;
  vector<ll> path;
  do {
    mp[x] = idx++;
    path.emplace_back(x);
    x = x * x % m;
  } while (!mp.count(x));
  int start = mp[x];
  int len = idx - start;
  ll sum = 0;
  for (int i = start; i < idx; ++i)
    sum += path[i];
  ll ans = 0;
  if (n < start) {
    for (int i = 0; i < n; ++i)
      ans += path[i];
  } else {
    for (int i = 0; i < start; ++i)
      ans += path[i];
    ll loop = (n - start) / len;
    ans += loop * sum;
    ll rem = (n - start) % len;
    for (int i = 0; i < rem; ++i)
      ans += path[start + i];
  }
  cout << ans;
}