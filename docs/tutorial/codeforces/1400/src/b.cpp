#include <cstdio>
#include <iostream>

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
    int p, f, cs, cw, s, w;
    read(p), read(f), read(cs), read(cw), read(s), read(w);
    int ans = 0;
    if (s > w)
      swap(s, w), swap(cs, cw);
    for (int i = 0; i <= cs && i * s <= p; ++i) {
      int p1 = p - i * s;
      int pw = min(p1 / w, cw);
      int cw1 = cw - pw;
      int fs = min(f / s, cs - i);
      int f1 = f - fs * s;
      int fw = min(f1 / w, cw1);
      ans = max(ans, i + pw + fs + fw);
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