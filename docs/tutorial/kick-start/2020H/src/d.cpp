#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int INF = 0x3f3f3f3f;

class Solution {
public:
  void solve(int case_num) {
    cout << "Case #" << case_num << ": ";
    int N, Q;
    cin >> N >> Q;
    vector<string> S(N + 1);
    for (int i = 1; i <= N; ++i)
      cin >> S[i];
    vector<vector<int>> d(26, vector<int>(26, INF));
    for (string s : S)
      for (char c1 : s)
        for (char c2 : s)
          if (c1 != c2)
            d[c1 - 'A'][c2 - 'A'] = 1;
    for (int k = 0; k < 26; ++k)
      for (int i = 0; i < 26; ++i) {
        if (i == k)
          continue;
        for (int j = 0; j < 26; ++j) {
          if (j == i || j == k)
            continue;
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }

    for (int i = 1; i <= Q; ++i) {
      int X, Y;
      cin >> X >> Y;
      int ans = INF;
      bool found = false;
      for (char c1 : S[X]) {
        for (char c2 : S[Y]) {
          if (c1 == c2) {
            cout << 2 << " ";
            found = true;
            break;
          }
          ans = min(ans, d[c1 - 'A'][c2 - 'A'] + 2);
        }
        if (found)
          break;
      }
      if (!found)
        cout << (ans == INF ? -1 : ans) << " ";
    }
    cout << endl;
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