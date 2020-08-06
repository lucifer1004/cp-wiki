#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

template <typename T> void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-')
      sig = -1;
  for (; isdigit(c); c = getchar())
    x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

class Solution {
public:
  void solve() {
    int n;
    read(n);
    vector<int> l(n), r(n);
    set<int> s;
    for (int i = 0; i < n; ++i)
      read(l[i]), read(r[i]), s.insert(l[i]), s.insert(r[i]);
    int m = s.size();
    map<int, int> d;
    int idx = 0;
    for (int i : s)
      d[i] = idx++;
    for (int i = 0; i < n; ++i)
      l[i] = d[l[i]], r[i] = d[r[i]];
    vector<vector<int>> dp(m, vector<int>(m));
    vector<vector<bool>> exist(m, vector<bool>(m));
    vector<vector<int>> lr(m);
    for (int i = 0; i < n; ++i)
      lr[l[i]].emplace_back(r[i]), exist[l[i]][r[i]] = true;
    for (int i = 0; i < m; ++i)
      sort(lr[i].begin(), lr[i].end());
    for (int k = 0; k < m; ++k)
      for (int i = 0; i + k < m; ++i) {
        int j = i + k;
        if (exist[i][j])
          dp[i][j] = 1;
        int extra = 0;
        if (i < j)
          extra = dp[i + 1][j];
        for (int rr : lr[i]) {
          if (rr >= j)
            break;
          extra = max(extra, dp[i][rr] + dp[rr + 1][j]);
        }
        dp[i][j] += extra;
      }
    printf("%d\n", dp[0][m - 1]);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  while (t--) {
    Solution solution = Solution();
    solution.solve();
  }
}