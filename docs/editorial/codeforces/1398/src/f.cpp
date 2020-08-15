#include <cstdio>
#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f

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
    string s;
    cin >> s;
    string t(s);
    for (int i = 0; i < n; ++i)
      if (s[i] == '?')
        s[i] = '0', t[i] = '1';
    vector<int> p(n + 2), q(n + 2);
    for (int i = n; i >= 1; --i)
      p[i] = s[i - 1] == '0' ? p[i + 1] + 1 : 0,
      q[i] = t[i - 1] == '1' ? q[i + 1] + 1 : 0;
    vector<int> np(n + 1), nq(n + 1);
    for (int i = n, pp = INF, qq = INF, npp = INF, nqq = INF; i >= 1; --i) {
      if (s[i - 1] == '0')
        pp = i;
      if (s[i - 1] == '1')
        npp = pp;
      np[i] = npp;

      if (t[i - 1] == '0')
        nqq = qq;
      if (t[i - 1] == '1')
        qq = i;
      nq[i] = nqq;
    }
    printf("%d ", n);
    for (int i = 2; i <= n; ++i) {
      int cnt = 0, idx = 1, last = 0;
      while (idx + i - 1 <= n) {
        int delta = max(p[idx], q[idx]);
        if (p[idx] <= i && np[last] == idx)
          np[last] = np[idx];
        if (q[idx] <= i && nq[last] == idx)
          nq[last] = nq[idx];
        last = idx;
        if (delta >= i)
          cnt += delta / i, idx += delta / i * i;
        else
          idx = min(np[idx], nq[idx]);
      }
      printf("%d ", cnt);
    }
  }
};

int main() {
  Solution solution = Solution();
  solution.solve();
}