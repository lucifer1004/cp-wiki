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
    int n;
    read(n);
    vector<int> cnt(n + 1);
    for (int i = 0; i < n; ++i) {
      int a;
      read(a);
      cnt[a]++;
    }
    int ans = 0;
    for (int s = 2; s <= n * 2; ++s) {
      int tot = 0;
      for (int i = max(1, s - n); i * 2 <= s; ++i) {
        int j = s - i;
        if (j != i)
          tot += min(cnt[i], cnt[j]);
        else
          tot += cnt[i] / 2;
      }
      ans = max(ans, tot);
    }
    printf("%d\n", ans);
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
