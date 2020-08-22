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
    int x1, y1, z1, x2, y2, z2;
    read(x1), read(y1), read(z1), read(x2), read(y2), read(z2);
    int zy = min(z1, y2);
    int pos = 2 * zy;
    z1 -= zy;
    int uz = min(z1 + x1, z2);
    z2 -= uz;
    int neg = -2 * min(y1, z2);
    printf("%d\n", pos + neg);
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