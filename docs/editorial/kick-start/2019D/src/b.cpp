#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    cout << "Case #" << case_num << ": ";
    int n, g, m;
    cin >> n >> g >> m;
    map<int, int> C, A;
    vector<pair<int, int>> ct(n, make_pair(-1, -1)), at(n, make_pair(-1, -1));
    vector<pair<int, char>> p;
    for (int i = 0; i < g; ++i) {
      int hi;
      char c;
      cin >> hi >> c;
      hi--;
      p.emplace_back(hi, c);
      if (c == 'C')
        C[hi] = 0;
      else
        A[hi] = 0;
    }

    // Handle clockwise
    int pos = -1;
    for (auto pc : C) {
      int pe = (pc.first + m) % n;
      ct[pe] = {pc.first, m};
      if (pos == -1)
        pos = pe;
    }
    if (pos != -1) {
      int lp = ct[pos].first, lt = ct[pos].second;
      for (int i = 1; i < n; ++i) {
        lt--, pos--;
        if (pos < 0)
          pos = n - 1;
        if (lt > ct[pos].second)
          ct[pos] = make_pair(lp, lt);
        else
          lp = ct[pos].first, lt = ct[pos].second;
      }
    }

    // Handle anticlockwise
    pos = -1;
    for (auto pc : A) {
      int pe = (pc.first - m) % n;
      if (pe < 0)
        pe += n;
      at[pe] = {pc.first, m};
      if (pos == -1)
        pos = pe;
    }
    if (pos != -1) {
      int lp = at[pos].first, lt = at[pos].second;
      for (int i = 1; i < n; ++i) {
        lt--, pos++;
        if (pos >= n)
          pos = 0;
        if (lt > at[pos].second)
          at[pos] = make_pair(lp, lt);
        else
          lp = at[pos].first, lt = at[pos].second;
      }
    }

    // Compare the latest clockwise guest and anticlockwise guest.
    for (int i = 0; i < n; ++i) {
      if (at[i].second > ct[i].second)
        A[at[i].first]++;
      else if (at[i].second < ct[i].second)
        C[ct[i].first]++;
      else {
        A[at[i].first]++;
        C[ct[i].first]++;
      }
    }
    for (int i = 0; i < g; ++i) {
      if (p[i].second == 'C')
        cout << C[p[i].first] << " ";
      else
        cout << A[p[i].first] << " ";
    }
    cout << endl;
  }
}