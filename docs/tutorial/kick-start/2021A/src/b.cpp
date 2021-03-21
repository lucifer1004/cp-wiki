#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

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
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int r, c;
    read(r), read(c);
    vector<vector<int>> m(r, vector<int>(c));
    for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j)
        read(m[i][j]);
    vector<vector<int>> W(r, vector<int>(c));
    vector<vector<int>> E(r, vector<int>(c));
    vector<vector<int>> N(r, vector<int>(c));
    vector<vector<int>> S(r, vector<int>(c));
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (m[i][j]) {
          W[i][j] = 1;
          if (j >= 1)
            W[i][j] += W[i][j - 1];
        }
      }
      for (int j = c - 1; j >= 0; --j) {
        if (m[i][j]) {
          E[i][j] = 1;
          if (j + 1 < c)
            E[i][j] += E[i][j + 1];
        }
      }
    }
    for (int j = 0; j < c; ++j) {
      for (int i = 0; i < r; ++i) {
        if (m[i][j]) {
          N[i][j] = 1;
          if (i >= 1)
            N[i][j] += N[i - 1][j];
        }
      }
      for (int i = r - 1; i >= 0; --i) {
        if (m[i][j]) {
          S[i][j] = 1;
          if (i + 1 < r)
            S[i][j] += S[i + 1][j];
        }
      }
    }

    ll ans = 0;
    for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j) {
        ans += max(0, min(W[i][j], N[i][j] / 2) - 1);
        ans += max(0, min(W[i][j] / 2, N[i][j]) - 1);
        ans += max(0, min(W[i][j], S[i][j] / 2) - 1);
        ans += max(0, min(W[i][j] / 2, S[i][j]) - 1);
        ans += max(0, min(E[i][j], N[i][j] / 2) - 1);
        ans += max(0, min(E[i][j] / 2, N[i][j]) - 1);
        ans += max(0, min(E[i][j], S[i][j] / 2) - 1);
        ans += max(0, min(E[i][j] / 2, S[i][j]) - 1);
      }

    printf("%lld\n", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
