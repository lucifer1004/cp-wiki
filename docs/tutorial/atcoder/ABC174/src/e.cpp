#include <algorithm>
#include <cstdio>
#include <iostream>
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
    int n, k;
    read(n), read(k);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i]);
    ll l = 1, r = *max_element(a.begin(), a.end());
    while (l <= r) {
      ll mid = l + (r - l) / 2;
      ll req = 0;
      for (int i : a)
        req += (i - 1) / mid;
      if (req > k)
        l = mid + 1;
      else
        r = mid - 1;
    }
    printf("%lld", l);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
