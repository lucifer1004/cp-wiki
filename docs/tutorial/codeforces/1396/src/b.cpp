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
    vector<int> a(n);
    int sum = 0, hi = 0;
    for (int i = 0; i < n; ++i) {
      read(a[i]);
      sum += a[i];
      hi = max(hi, a[i]);
    }
    if (hi > sum - hi) {
      printf("T\n");
      return;
    }
    printf(sum % 2 == 0 ? "HL\n" : "T\n");
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