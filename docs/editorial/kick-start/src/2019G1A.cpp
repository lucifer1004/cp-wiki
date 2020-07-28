#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
typedef long long ll;

class Solution {

public:
  void solve(int case_num) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> cnt(n + 1), torn(n + 1);
    for (int i = 0; i < m; ++i) {
      int p;
      scanf("%d", &p);
      torn[p]++;
    }
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n / i; ++j)
        if (torn[i * j])
          cnt[i]++;

    ll ans = 0;
    for (int i = 0; i < q; ++i) {
      int r;
      scanf("%d", &r);
      ans += n / r - cnt[r];
    }
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
