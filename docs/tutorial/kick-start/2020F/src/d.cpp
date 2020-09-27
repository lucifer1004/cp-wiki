#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T> void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-')
      sig = -1;
  for (; isdigit(c); c = getchar())
    x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

class Solution {
public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n, m, k;
    read(n), read(m), read(k);
    vector<int> a(k);
    vector<int> cnt(n + 1);
    for (int i = 0; i < k; ++i)
      read(a[i]), cnt[a[i]]++;
    int hi = a.back();
    vector<int> target(hi + 1);
    target[0] = m - k;
    for (int i = 1; i <= hi; ++i)
      target[i] = target[i - 1] + cnt[i];
    map<vector<int>, double> p, e;
    vector<int> raw(hi + 1, m);
    p[raw] = 1, e[raw] = 0;
    for (int i = 1; i <= n; ++i) {
      map<vector<int>, double> np, ne;
      vector<pair<vector<int>, pair<double, double>>> updates;
      for (const auto &pr : p) {
        const vector<int> &state = pr.first;
        double pi = pr.second;
        double ei = e[state];
        int good = 0;
        vector<pair<int, int>> choices;
        for (int j = 0; j < hi; ++j) {
          if (state[j] == target[j])
            continue;
          int rem = state[j] - (j == 0 ? 0 : state[j - 1]);
          if (!rem)
            continue;
          good += rem;
          choices.emplace_back(j, rem);
        }
        for (auto choice : choices) {
          int j = choice.first, c = choice.second;
          vector<int> nxt(state);
          nxt[j]--;
          double pnxt = pi * c / good;
          np[nxt] += pnxt;
          updates.emplace_back(nxt, make_pair(pnxt, ei + (double)m / good));
        }
      }
      for (const auto &update : updates) {
        const vector<int> &nxt = update.first;
        double pnxt = update.second.first, enxt = update.second.second;
        ne[nxt] += pnxt / np[nxt] * enxt;
      }
      p = move(np);
      e = move(ne);
    }
    double ans = 0;
    for (auto pr : e)
      ans += pr.second * p[pr.first];
    printf("%.8f\n", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}