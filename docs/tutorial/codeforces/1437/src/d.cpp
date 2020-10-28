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
    int height = 0;
    vector<int> level = {1};
    int col = 0, first, last = 0;
    read(first);
    for (int i = 0; i < n - 1; ++i) {
      int u;
      read(u);
      if (u < last) {
        col++;
        if (col == level[height]) {
          height++;
          col = 0;
        }
      }
      if (level.size() <= height + 1)
        level.emplace_back(0);
      level[height + 1]++;
      last = u;
    }
    printf("%d\n", (int)level.size() - 1);
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