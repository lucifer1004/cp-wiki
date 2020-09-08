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
    int z = 0;
    for (int i = 0; i < n; ++i)
      read(a[i]), z += (a[i] == 0);
    int k = z, d = 0;
    if (z < n - z) {
      d = 1;
      k = n - z;
      if (k % 2 == 1)
        k--;
    }
    printf("%d\n", k);
    vector<int> ans(k, d);
    for (int i : ans)
      printf("%d ", i);
    printf("\n");
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
