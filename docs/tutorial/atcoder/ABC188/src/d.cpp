#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
  int N;
  ll C;
  cin >> N >> C;
  vector<int> a(N), b(N), c(N);
  set<int> s;
  for (int i = 0; i < N; ++i) {
    cin >> a[i] >> b[i] >> c[i];

    // We only need a[i] and b[i]+1 to represent the final segments.
    // For example, [1, 4] and [3, 8] will make
    // [1, 2], [3, 4], [5, 8] and [9, +inf].
    // We need 1, 3, 5, and 9 to represent these segments.
    s.insert(a[i]), s.insert(b[i] + 1);
  }

  // Discretize the endpoints.
  int idx = 0;
  map<int, int> mp;
  for (int si : s)
    mp[si] = idx++;
  int M = s.size();
  vector<int> v(s.begin(), s.end());

  // Use a difference array to handle the services.
  vector<ll> diff(M);
  for (int i = 0; i < N; ++i)
    diff[mp[a[i]]] += c[i], diff[mp[b[i] + 1]] -= c[i];

  // Accumulate the difference array to get the value of each segment.
  // At the same time, add to the total cost.
  vector<ll> acc(M);
  acc[0] = diff[0];
  ll ans = 0;
  for (int i = 0; i < M - 1; ++i) {
    if (i >= 1)
      acc[i] = acc[i - 1] + diff[i];
    int span = v[i + 1] - v[i];
    ans += min(C, acc[i]) * span;
  }
  cout << ans;
}
