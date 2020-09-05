#include <cstdio>
#include <iostream>
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
    int n, k;
    read(n), read(k);
    string s, t;
    cin >> s >> t;
    if (t[0] == t[1]) {
      int cnt = 0;
      for (char c : s)
        cnt += c == t[0];
      int hi = min(n, cnt + k);
      printf("%d", hi * (hi - 1) / 2);
    } else {
      char a = t[0], b = t[1];
      vector<vector<int>> g(n + 1, vector<int>(k + 1, -1));
      g[0][0] = 0;
      for (int i = 0; i < n; ++i) {
        vector<vector<int>> ng(g);
        for (int j = 0; j <= i; ++j)
          for (int p = 0; p <= k; ++p) {
            if (g[j][p] == -1)
              continue;

            // Set to b
            if (s[i] == b)
              ng[j][p] = max(ng[j][p], g[j][p] + j);
            else if (p < k)
              ng[j][p + 1] = max(ng[j][p + 1], g[j][p] + j);

            // Set to a
            if (s[i] == a)
              ng[j + 1][p] = max(ng[j + 1][p], g[j][p]);
            else if (p < k)
              ng[j + 1][p + 1] = max(ng[j + 1][p + 1], g[j][p]);
          }
        g = move(ng);
      }
      int ans = 0;
      for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= k; ++j)
          ans = max(ans, g[i][j]);
      printf("%d", ans);
    }
  }
};

int main() {
  Solution solution = Solution();
  solution.solve();
}