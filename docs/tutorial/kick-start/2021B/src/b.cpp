#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

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

class Solution {
 public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n;
    read(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) read(a[i]);

    if (n <= 3) {
      printf("%d\n", n);
      return;
    }

    vector<int> l(n), r(n);
    l[0] = 1;
    l[1] = 2;
    for (int i = 2; i < n; ++i) {
      if (a[i] - a[i - 1] == a[i - 1] - a[i - 2])
        l[i] = l[i - 1] + 1;
      else
        l[i] = 2;
    }

    r[n - 1] = 1;
    r[n - 2] = 2;
    for (int i = n - 3; i >= 0; --i) {
      if (a[i + 1] - a[i] == a[i + 2] - a[i + 1])
        r[i] = r[i + 1] + 1;
      else
        r[i] = 2;
    }

    int ans = max(l[n - 2] + 1, r[1] + 1);
    for (int i = 1; i < n - 1; ++i) {
      ans = max(ans, max(l[i - 1] + 1, r[i + 1] + 1));
      if (i >= 2 && a[i + 1] - a[i - 1] == 2 * (a[i - 1] - a[i - 2]))
        ans = max(ans, l[i - 1] + 2);
      if (i + 2 < n && a[i + 1] - a[i - 1] == 2 * (a[i + 2] - a[i + 1]))
        ans = max(ans, r[i + 1] + 2);
      if (i >= 2 && i + 2 < n &&
          a[i + 1] - a[i - 1] == 2 * (a[i - 1] - a[i - 2]) &&
          a[i - 1] - a[i - 2] == a[i + 2] - a[i + 1])
        ans = max(ans, l[i - 1] + r[i + 1] + 1);
    }

    printf("%d\n", ans);
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