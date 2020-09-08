#include <iostream>
#include <vector>

using namespace std;

class Solution {
  vector<int> ans;
  vector<vector<pair<int, int>>> adj;

  int query(int i, int j) {
    int k;
    cout << "? " << i << " " << j << endl;
    cin >> k;
    return k;
  }

public:
  void solve() {
    int n;
    cin >> n;
    if (n == 1) {
      cout << "! 1" << endl;
      return;
    }
    ans = vector<int>(n + 1);
    int a = query(1, 2), b = query(2, 1);
    int m;
    if (a > b) {
      m = 2;
      ans[1] = a;
    } else {
      m = 1;
      ans[2] = b;
    }
    for (int i = 3; i <= n; ++i) {
      int a = query(m, i), b = query(i, m);
      if (a > b) {
        ans[m] = a;
        m = i;
      } else {
        ans[i] = b;
      }
    }
    ans[m] = n;
    cout << "! ";
    for (int i = 1; i <= n; ++i)
      cout << ans[i] << " ";
    cout << endl;
  }
};

int main() {
  Solution solution = Solution();
  solution.solve();
}