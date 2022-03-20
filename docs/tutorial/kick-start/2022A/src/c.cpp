#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
const int K = 5;
const int MSK1 = (1 << K) - 1;
const int MSK = (1 << (K + 1)) - 1;

template <typename T>
void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-') sig = -1;
  for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

bool bad1[1 << K]{};
bool bad[1 << (K + 1)]{};

class Solution {
 public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);

    int n;
    string s;
    cin >> n >> s;

    if (n <= 4) {
      cout << "POSSIBLE" << endl;
      return;
    }

    vector<bool> dp(1 << (K + 1));
    dp[0] = true;
    for (int i = 0; i < n; ++i) {
      vector<bool> ndp(1 << (K + 1));
      if (s[i] == '0' || s[i] == '?') {
        for (int j = 0; j <= MSK; ++j) {
          if (!dp[j]) continue;
          int nxt1 = (j << 1) & MSK1;
          if (i >= 4 && bad1[nxt1]) continue;
          int nxt = (j << 1) & MSK;
          if (i >= 5 && bad[nxt]) continue;
          ndp[nxt] = true;
        }
      }
      if (s[i] == '1' || s[i] == '?') {
        for (int j = 0; j <= MSK; ++j) {
          if (!dp[j]) continue;
          int nxt1 = ((j << 1) & MSK1) + 1;
          if (i >= 4 && bad1[nxt1]) continue;
          int nxt = ((j << 1) & MSK) + 1;
          if (i >= 5 && bad[nxt]) continue;
          ndp[nxt] = true;
        }
      }
      dp = move(ndp);
    }

    for (int i = 0; i < MSK; ++i) {
      if (dp[i]) {
        cout << "POSSIBLE" << endl;
        return;
      }
    }

    cout << "IMPOSSIBLE" << endl;
  }
};

bool is_palindrom(string s) {
  string t(s.rbegin(), s.rend());
  return s == t;
}

int main() {
  for (int i = 0; i < (1 << K); i++) {
    string s = bitset<K>(i).to_string();
    if (is_palindrom(s)) bad1[i] = true;
  }

  for (int i = 0; i < (1 << (K + 1)); i++) {
    string s = bitset<K + 1>(i).to_string();
    if (is_palindrom(s)) bad[i] = true;
  }

  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
