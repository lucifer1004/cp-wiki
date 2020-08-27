#include <iostream>

using namespace std;

class Solution {
public:
  void solve() {
    string s;
    int x;
    cin >> s >> x;
    int n = s.size();
    string w(n, '1');
    for (int i = 0; i < n; ++i)
      if (s[i] == '0') {
        if (i >= x)
          w[i - x] = '0';
        if (i + x < n)
          w[i + x] = '0';
      }
    for (int i = 0; i < n; ++i)
      if (s[i] == '1') {
        bool ok = false;
        if (i >= x && w[i - x] == '1')
          ok = true;
        if (i + x < n && w[i + x] == '1')
          ok = true;
        if (!ok) {
          cout << -1 << endl;
          return;
        }
      }
    cout << w << endl;
  }
};

int main() {
  int t;
  cin >> t;
  while (t--) {
    Solution solution = Solution();
    solution.solve();
  }
}