#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
  int n;
  cin >> n;
  vector<pair<ll, ll>> towns;
  ll sa = 0, sb = 0;
  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    towns.emplace_back(a, b);
    sa += a;
  }
  sort(towns.begin(), towns.end(), [](pair<ll, ll> &p, pair<ll, ll> &q){
    return p.first * 2 + p.second > q.first * 2 + q.second;
  });
  for (int i = 0; i < n; ++i) {
    if (sa < sb) {
      cout << i;
      return 0;
    }
    sa -= towns[i].first, sb += towns[i].first + towns[i].second;
  }
  cout << n;
}
