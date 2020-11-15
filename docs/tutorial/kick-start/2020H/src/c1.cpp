#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class Solution {
public:
  void solve(int case_num) {
    cout << "Case #" << case_num << ": ";
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i)
      cin >> X[i] >> Y[i];
    sort(Y.begin(), Y.end());
    ll ylo = 0;
    for (int yi : Y)
      ylo += abs(yi - Y[N / 2]);
    sort(X.begin(), X.end());
    ll l = -2e9, r = 2e9;
    ll xlo = LLONG_MAX;
    auto dist = [&](ll start) {
      ll ret = 0;
      int idx = 0;
      for (int xi : X) {
        ret += abs(start + idx - xi);
        idx++;
      }
      xlo = min(xlo, ret);
      return ret;
    };
    while (l <= r) {
      ll mid = (l + r) / 2;
      ll delta = dist(mid + 1) - dist(mid);
      if (delta >= 0)
        r = mid - 1;
      else
        l = mid + 1;
    }
    cout << ylo + xlo << endl;
  }
};

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
