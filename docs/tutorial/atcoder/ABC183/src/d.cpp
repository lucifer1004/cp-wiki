#include <iostream>
#include <vector>
#define MAXN 200005

using namespace std;
typedef long long ll;
int main() {
  int n, w;
  cin >> n >> w;
  vector<ll> delta(MAXN);
  for (int i = 0; i < n; ++i) {
    int s, t, p;
    cin >> s >> t >> p;
    delta[s] += p;
    delta[t] -= p;
  }
  ll curr = 0;
  for (int i = 0; i < MAXN; ++i) {
    curr += delta[i];
    if (curr > w) {
      cout << "No";
      return 0;
    }
  }
  cout << "Yes";
}