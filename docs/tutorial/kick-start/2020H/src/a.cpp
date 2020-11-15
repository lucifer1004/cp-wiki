#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  void solve(int case_num) {
    cout << "Case #" << case_num << ": ";
    long long N, K, S;
    cin >> N >> K >> S;
    cout << K - 1 + min(N + 1, K - S + N - S + 1) << endl;
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