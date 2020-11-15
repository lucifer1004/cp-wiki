#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
ll five[20], pre[20];
int a[10] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4};
int b[10] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5};

class Solution {
  ll count(ll x) {
    string s = to_string(x);
    int n = s.size();
    ll ans = pre[n - 1];
    for (int i = 1; i <= n; ++i) {
      int c = s[i - 1] - '0';
      if (c % 2 != i % 2) {
        ans += five[n - i] * b[c];
        break;
      } else {
        ans += five[n - i] * a[c];
        if (i == n)
          ans++;
      }
    }
    return ans;
  }

public:
  void solve(int case_num) {
    cout << "Case #" << case_num << ": ";
    ll L, R;
    cin >> L >> R;
    cout << count(R) - count(L - 1) << endl;
  }
};

int main() {
  int t;
  cin >> t;
  five[0] = 1;
  for (int i = 1; i < 20; ++i)
    five[i] = five[i - 1] * 5;
  pre[0] = 0;
  for (int i = 1; i < 20; ++i)
    pre[i] = pre[i - 1] + five[i];
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
