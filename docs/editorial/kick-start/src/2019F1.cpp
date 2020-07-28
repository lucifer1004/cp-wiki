#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

void solve(int case_num) {
  int n, k;
  cin >> n >> k;
  vector<ll> a;
  unordered_set<ll> nums_set;
  for (int i = 0; i < n; ++i) {
    int ai;
    cin >> ai;
    a.emplace_back(ai);
    nums_set.insert(ai);
  }
  vector<ll> nums(nums_set.begin(), nums_set.end());
  int t = nums.size();

  vector<vector<vector<ll>>> f(
      n + 1, vector<vector<ll>>(k + 1, vector<ll>(t, INT_MAX)));
  vector<vector<ll>> minf(n + 1, vector<ll>(k + 1, INT_MAX));

  for (int i = 0; i < t; ++i) {
    if (nums[i] != a[0]) {
      f[1][0][i] = 1;
    } else {
      f[1][0][i] = 0;
      minf[1][0] = 0;
    }
  }

  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j <= min(k, i - 1); ++j) {
      for (int m = 0; m < t; ++m) {
        f[i][j][m] = f[i - 1][j][m];
        if (j > 0)
          f[i][j][m] = min(f[i][j][m], minf[i - 1][j - 1]);
        if (a[i - 1] != nums[m])
          f[i][j][m]++;
        if (f[i][j][m] < minf[i][j])
          minf[i][j] = f[i][j][m];
      }
    }
  }

  ll ans = INT_MAX;
  for (int j = 0; j <= k; ++j)
    for (int m = 0; m < t; ++m)
      ans = min(ans, f[n][j][m]);

  cout << "Case #" << case_num << ": " << ans << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}
