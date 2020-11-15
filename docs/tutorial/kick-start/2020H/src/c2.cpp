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
    for (int i = 0; i < N; ++i)
      X[i] -= i;
    sort(X.begin(), X.end());
    ll xlo = 0;
    for (int xi : X)
      xlo += abs(xi - X[N / 2]);
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
