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
    int n;
    read(n);
    vector<ll> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i]);
    if (n == 1) {
      printf("1 1\n%lld\n1 1\n1\n1 1\n-1\n", -a[0]);
      return;
    }
    printf("1 %d\n", n - 1);
    for (int i = 0; i < n - 1; ++i) {
      ll r = (a[i] % n + n) % n;
      a[i] += r * (n - 1);
      printf("%lld ", r * (n - 1));
    }
    printf("\n2 %d\n", n);
    for (int i = 1; i < n; ++i) {
      ll r = (a[i] % n + n) % n;
      a[i] += r * (n - 1);
      printf("%lld ", r * (n - 1));
    }
    printf("\n1 %d\n", n);
    for (ll num : a)
      printf("%lld ", -num);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}