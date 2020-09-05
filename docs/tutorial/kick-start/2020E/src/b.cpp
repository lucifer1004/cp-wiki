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
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n, a, b, c;
    read(n), read(a), read(b), read(c);
    if (a + b - c > n || a < c || b < c) {
      printf("IMPOSSIBLE\n");
      return;
    }
    if (a == c && b == c && c < min(n, 2)) {
      printf("IMPOSSIBLE\n");
      return;
    }
    bool rev = false;
    if (a > b)
      swap(a, b), rev = true;
    vector<int> ans;
    int ra = a - c, rb = b - c;
    for (int i = 0; i < ra; ++i)
      ans.emplace_back(n - 1);
    ans.emplace_back(n);
    for (int i = 0; i < n - ra - rb - c; ++i)
      ans.emplace_back(1);
    for (int i = 0; i < c - 1; ++i)
      ans.emplace_back(n);
    for (int i = 0; i < rb; ++i)
      ans.emplace_back(n - 1);
    if (rev)
      reverse(ans.begin(), ans.end());
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
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
