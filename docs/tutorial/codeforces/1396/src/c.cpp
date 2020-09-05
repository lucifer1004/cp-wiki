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
  struct Node {
    ll time = 0;
    int idx = 0, left = 0;
    bool operator<(const Node &other) const { return time > other.time; }
  };

public:
  void solve() {
    ll n, r1, r2, r3, d;
    read(n), read(r1), read(r2), read(r3), read(d);
    vector<ll> a(n + 1), kill_all(n + 1), leave_one(n + 1);
    for (int i = 1; i <= n; ++i) {
      read(a[i]);
      kill_all[i] = r1 * a[i] + r3;
      leave_one[i] = min(r2, r1 * (a[i] + 1)) + r1;
    }
    vector<ll> L(n + 2), R(n + 2);
    R[n] = min(kill_all[n], leave_one[n] + d * 2);
    for (int i = n - 1; i >= 1; --i)
      R[i] = R[i + 1] + d * 2 + min(kill_all[i], leave_one[i]);
    ll cost = R[1];
    L[0] = R[n + 1] = -d;
    for (int i = 1; i <= n; ++i) {
      L[i] = L[i - 1] + d + min(kill_all[i], leave_one[i] + d * 2);
      if (i >= 2)
        L[i] = min(L[i], L[i - 2] + d * 4 +
                             min(kill_all[i - 1], leave_one[i - 1]) +
                             min(kill_all[i], leave_one[i]));
      cost = min(cost, L[i] + R[i + 1] + d);
    }
    cout << cost;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
