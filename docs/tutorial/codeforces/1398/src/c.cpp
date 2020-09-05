#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef long long ll;

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
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      a[i] = s[i] - '0' - 1;
    map<int, int> cnt;
    cnt[0] = 1;
    int sum = 0;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
      sum += a[i];
      ans += cnt[sum];
      cnt[sum]++;
    }
    printf("%lld\n", ans);
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