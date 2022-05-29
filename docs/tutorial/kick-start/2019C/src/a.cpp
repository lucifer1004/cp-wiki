#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// Validated by [LC57](https://leetcode.cn/problems/insert-interval/).
// Need to change "r + 1" to "r" due to difference in the definition of segment.
void insert(set<pair<int, int>> &s, pair<int, int> p) {
  s.insert(p);
  auto it = s.lower_bound(p);
  if (it != s.begin())
    --it;
  int l = it->first, r = it->second;
  ++it;
  while (l <= p.first) {
    if (it == s.end())
      break;
    if (it->first > r + 1) {
      l = it->first;
      r = it->second;
      ++it;
    } else {
      s.erase({l, r});
      r = max(r, it->second);
      ++it;
      s.erase(prev(it));
      s.insert({l, r});
    }
  }
}

int find(set<pair<int, int>> &s, int pos, int type) {
  if (type) {
    auto it = s.lower_bound({pos, pos});
    if (it != s.end() && it->first == pos)
      return it->second + 1;
    --it;
    return it->second + 1;
  } else {
    auto it = s.lower_bound({pos, pos});
    if (it != s.end() && it->first == pos)
      return pos - 1;
    --it;
    return it->first - 1;
  }
}

int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    int n, r, c, sr, sc;
    string s;
    cin >> n >> r >> c >> sr >> sc >> s;
    cout << "Case #" << case_num << ": ";
    vector<set<pair<int, int>>> row(r + 1), col(c + 1);
    insert(row[sr], {sc, sc});
    insert(col[sc], {sr, sr});
    for (char c : s) {
      switch (c) {
      case 'W':
        sc = find(row[sr], sc, 0);
        break;
      case 'E':
        sc = find(row[sr], sc, 1);
        break;
      case 'N':
        sr = find(col[sc], sr, 0);
        break;
      default:
        sr = find(col[sc], sr, 1);
        break;
      }
      insert(row[sr], {sc, sc});
      insert(col[sc], {sr, sr});
    }
    cout << sr << " " << sc << endl;
  }
}
