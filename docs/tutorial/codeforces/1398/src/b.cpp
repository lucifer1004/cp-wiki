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
  void solve() {
    string s;
    cin >> s;
    s += "0";
    vector<int> v;
    int d = '$', cnt = 0;
    for (char c : s) {
      if (c == d)
        cnt++;
      else {
        if (d == '1')
          v.emplace_back(cnt);
        d = c;
        cnt = 1;
      }
    }
    sort(v.rbegin(), v.rend());
    int ans = 0;
    for (int i = 0; i < v.size(); i += 2)
      ans += v[i];
    printf("%d\n", ans);
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