#include <iostream>
#include <map>
#include <vector>

using namespace std;
int main() {
  int q, n;
  string s;
  cin >> q >> s >> n;
  vector<pair<int, int>> pos;
  pos.emplace_back(0, 0);
  int cx = 0, cy = 0;
  map<char, int> dx = {{'L', -1}, {'R', 1}, {'U', 0}, {'D', 0}},
                 dy = {{'L', 0}, {'R', 0}, {'U', -1}, {'D', 1}};
  for (char c : s) {
    cx += dx[c], cy += dy[c];
    pos.emplace_back(cx, cy);
  }
  int ans = 0;
  for (int i = 0; i + n < q; ++i) {
    if (abs(pos[i].first - pos[i + n].first) <= 1 &&
        abs(pos[i].second - pos[i + n].second) <= 1)
      ans++;
  }
  cout << ans;
}