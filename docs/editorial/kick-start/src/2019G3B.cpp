#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class Solution {

public:
  void solve(int case_num) {
    ll n, h;
    cin >> n >> h;
    ll states = (1 << n);
    vector<ll> a(n), b(n), f(states);

    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
    }

    for (int i = 0; i < n; ++i) {
      scanf("%lld", &b[i]);
    }

    // 检查B的快乐值是否被满足。
    for (int i = 0; i < states; ++i) {
      ll sum = 0;
      for (int j = 0; j < n; ++j)
        if (!(i & (1 << j)))
          sum += b[j];
      if (sum >= h)
        f[i]++;
    }

    // 派生B的状态。
    // 注意这里循环的顺序，要把位的循环放在外层，才能保证不重复不遗漏。
    for (int j = 0; j < n; ++j)
      for (int i = 0; i < states; ++i)
        if (i & (1 << j))
          f[i] += f[i ^ (1 << j)];

    // 检查A的快乐值是否被满足。
    ll ans = 0;
    for (int i = 0; i < states; ++i) {
      ll sum = 0;
      for (int j = 0; j < n; ++j)
        if (i & (1 << j))
          sum += a[j];
      if (sum >= h)
        ans += f[i];
    }

    cout << "Case #" << case_num << ": " << ans << endl;
  }
};

int main() {
  Solution solution;
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i)
    solution.solve(i);
}
