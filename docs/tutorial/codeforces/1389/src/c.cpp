#include <algorithm>
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
    string s;
    cin >> s;
    int n = s.size();
    vector<int> cnt(10);
    for (char c : s)
      cnt[c - '0']++;
    int ans = n - *max_element(cnt.begin(), cnt.end());
    for (int i = 0; i < 10; ++i)
      for (int j = 0; j < 10; ++j) {
        vector<char> t{(char)(i + '0'), (char)(j + '0')};
        int tot = 0, idx = 0;
        for (char c : s) {
          if (c == t[idx]) {
            idx++;
            if (idx == 2)
              tot++, idx = 0;
          }
        }
        ans = min(ans, n - tot * 2);
      }
    printf("%d\n", ans);
  }
};

int main() {
  int t;
  read(t);
  while (t--) {
    Solution solution = Solution();
    solution.solve();
  }
}