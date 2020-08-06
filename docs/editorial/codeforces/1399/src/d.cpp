#include <cstdio>
#include <iostream>
#include <stack>
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
    string s;
    cin >> s;
    stack<int> a, b;
    vector<int> color(n);
    int idx = 1;
    for (int i = 0; i < n; ++i) {
      char c = s[i];
      if (c == '0') {
        if (a.empty()) {
          color[i] = idx++;
        } else {
          color[i] = a.top();
          a.pop();
        }
        b.push(color[i]);
      } else {
        if (b.empty()) {
          color[i] = idx++;
        } else {
          color[i] = b.top();
          b.pop();
        }
        a.push(color[i]);
      }
    }
    printf("%d\n", idx - 1);
    for (int i : color)
      printf("%d ", i);
    printf("\n");
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