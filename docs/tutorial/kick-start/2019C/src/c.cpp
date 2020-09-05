#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    cout << "Case #" << case_num << ": ";
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> dogs(n);
    for (int i = 0; i < n; ++i)
      cin >> dogs[i].first;
    for (int i = 0; i < n; ++i)
      cin >> dogs[i].second;
    sort(dogs.begin(), dogs.end());
    map<int, vector<int>> c;
    for (auto dog : dogs)
      c[dog.second].emplace_back(dog.first);
    vector<vector<int>> vc;
    for (auto p : c)
      vc.push_back(p.second);
    vector<vector<int>> dp(k + 1, vector<int>(2, 1e9));
    dp[0][0] = 0;
    for (int i = 0; i < vc.size(); ++i) {
      vector<vector<int>> ndp(dp);
      for (int j = 0; j < vc[i].size(); ++j) {
        for (int s = k; s >= j + 1; --s) {
          ndp[s][0] = min(ndp[s][0], dp[s - j - 1][0] + 2 * vc[i][j]);
          ndp[s][1] = min(ndp[s][1], min(dp[s - j - 1][1] + 2 * vc[i][j],
                                         dp[s - j - 1][0] + vc[i][j]));
        }
      }
      dp = move(ndp);
    }
    cout << dp[k][1] << endl;
  }
}
