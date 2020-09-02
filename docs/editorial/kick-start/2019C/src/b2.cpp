#include <algorithm>
#include <deque>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    int r, c, k;
    cin >> r >> c >> k;
    cout << "Case #" << case_num << ": ";
    vector<vector<int>> v(r + 1, vector<int>(c + 1));
    for (int i = 1; i <= r; ++i)
      for (int j = 1; j <= c; ++j)
        cin >> v[i][j];
    vector<vector<int>> f(r + 2, vector<int>(c + 1));
    for (int i = 1; i <= r; ++i) {
      deque<pair<int, int>> asc, desc;
      int l = 1;
      for (int j = 1; j <= c; ++j) {
        while (!asc.empty() && asc.back().first >= v[i][j])
          asc.pop_back();
        while (!asc.empty() && v[i][j] - asc.front().first > k) {
          l = max(l, asc.front().second + 1);
          asc.pop_front();
        }
        asc.emplace_back(v[i][j], j);
        while (!desc.empty() && desc.back().first <= v[i][j])
          desc.pop_back();
        while (!desc.empty() && desc.front().first - v[i][j] > k) {
          l = max(l, desc.front().second + 1);
          desc.pop_front();
        }
        desc.emplace_back(v[i][j], j);
        f[i][j] = j - l + 1;
      }
    }
    int ans = 0;
    for (int j = 1; j <= c; ++j) {
      stack<pair<int, int>> st;
      for (int i = 1; i <= r + 1; ++i) {
        int l = i;
        while (!st.empty() && f[i][j] < st.top().first) {
          ans = max(ans, st.top().first * (i - st.top().second));
          l = st.top().second;
          st.pop();
        }
        if (st.empty() || st.top().first < f[i][j])
          st.emplace(f[i][j], l);
      }
    }
    cout << ans << endl;
  }
}
