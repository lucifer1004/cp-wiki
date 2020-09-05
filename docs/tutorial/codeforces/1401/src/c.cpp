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
    int n;
    read(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i]);
    int lo = *min_element(a.begin(), a.end());
    vector<int> v;
    for (int i = 0; i < n; ++i)
      if (a[i] % lo == 0)
        v.emplace_back(i);
    vector<int> pos(v);
    sort(v.begin(), v.end(), [&](int i, int j) { return a[i] < a[j]; });
    vector<int> b(a);
    for (int i = 0; i < v.size(); ++i)
      b[pos[i]] = a[v[i]];
    int hi = 0;
    for (int i : b) {
      if (i < hi) {
        printf("NO\n");
        return;
      }
      hi = i;
    }
    printf("YES\n");
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