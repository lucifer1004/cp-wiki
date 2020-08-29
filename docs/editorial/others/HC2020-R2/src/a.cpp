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

ll n, k;

void input(vector<ll> &v) {
  ll a, b, c, d;
  for (int i = 0; i < k; ++i)
    read(v[i]);
  read(a), read(b), read(c), read(d);
  for (int i = k; i < n; ++i)
    v[i] = (a * v[i - 2] + b * v[i - 1] + c) % d;
}

class Solution {
public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    read(n), read(k);
    vector<ll> s(n), x(n), y(n);
    input(s), input(x), input(y);
    ll overflow = 0, extra = 0, vacancy = 0, require = 0;
    for (int i = 0; i < n; ++i) {
      ll hi = x[i] + y[i];
      if (s[i] > hi)
        overflow += s[i] - hi;
      else
        vacancy += min(hi - s[i], y[i]);
      if (s[i] > x[i])
        extra += min(s[i] - x[i], y[i]);
      else
        require += x[i] - s[i];
    }
    if (overflow >= require) {
      if (overflow > require + vacancy)
        printf("-1\n");
      else
        printf("%lld\n", overflow);
    } else {
      if (require > overflow + extra)
        printf("-1\n");
      else
        printf("%lld\n", require);
    }
  }
};

int main() {
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}