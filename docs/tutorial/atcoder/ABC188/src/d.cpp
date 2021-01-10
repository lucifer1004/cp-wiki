#include <vector>
#include <iostream>
#include <set>
#include <map>

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
    s.insert(a[i]), s.insert(b[i]);
    s.insert(a[i] - 1), s.insert(b[i] + 1);
  }
  int idx = 0;
  map<int, int> mp;
  for (int si : s)
    mp[si] = idx++;
  int M = s.size();
  vector<int> v(s.begin(), s.end());
  vector<ll> diff(M + 1);
  for (int i = 0; i < N; ++i)
    diff[mp[a[i]]] += c[i], diff[mp[b[i]+1]] -= c[i];
  vector<ll> acc(M + 1);
  ll ans = 0;
  for (int i = 1; i < M - 1; ++i) {
    acc[i] = acc[i - 1] + diff[i];
    int span = v[i + 1] - v[i];
    ans += min(C, acc[i]) * span;
  }
  cout << ans;
}
