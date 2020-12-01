#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
  void solve() {
    int n, k;
    cin >> n >> k;
    auto nxt = [&](char c) {
      int d = c - 'a';
      return 'a' + (d + 1) % k;
    };
    auto pre = [&](char c) {
      int d = c - 'a';
      return 'a' + (d - 1 + k) % k;
    };
    string s;
    cin >> s;
    if (n == 1) {
      int c = s[0] - 'a' + 1;
      if (c == k || c == 1)
        printf("a\n");
      else
        printf("%c\n", 'a' + c - 2);
      return;
    }
    char a = s[0], b = s[1];
    char am = pre(a), bm = pre(b), ap = nxt(a), bp = nxt(b);
    vector<string> f{{a, b},   {a, bm}, {a, bp},  {am, b},  {am, bm},
                     {am, bp}, {ap, b}, {ap, bm}, {ap, bp}, {b, a},
                     {bm, a},  {bp, a}, {b, am},  {b, ap}};
    if (n == 2) {
      printf("%s\n", (*min_element(f.begin(), f.end())).c_str());
      return;
    }
    char c = s[2];
    for (string &fi : f)
      fi.push_back(c);
    vector<string> g{{a, c, b}, {am, c, b}, {ap, c, b}};
    string ans;
    for (int i = 2; i < n; ++i) {
      set<string> nf, ng;
      char flo = 'z', glo = 'z';
      if (!f.empty())
        flo = (*min_element(f.begin(), f.end()))[0];
      if (!g.empty())
        glo = (*min_element(g.begin(), g.end()))[0];
      for (string fi : f) {
        char a = fi[0], b = fi[1], c = fi[2];
        if (a > flo)
          continue;
        char cm = pre(c), cp = nxt(c);
        char d = (i + 1 < n) ? s[i + 1] : 'z';
        vector<string> fgen{
            {a, b, c, d}, {a, b, cm, d}, {a, b, cp, d}, {a, c, b, d}};
        for (string fj : fgen) {
          if (!nf.empty() && (*nf.begin())[0] > fj[0])
            nf.clear();
          if (nf.empty() || (*nf.begin())[0] == fj[0])
            nf.insert(fj);
        }
        string gj{a, b, d, c};
        if (!ng.empty() && (*ng.begin())[0] > gj[0])
          ng.clear();
        if (ng.empty() || (*nf.begin())[0] == gj[0])
          ng.insert(gj);
      }
      for (string gi : g) {
        char a = gi[0], c = gi[1], b = gi[2];
        if (a > glo && c > glo)
          continue;
        char cm = pre(c), cp = nxt(c);
        char d = (i + 1 < n) ? s[i + 1] : 'z';
        vector<string> fgen{
            {a, c, b, d}, {a, cm, b, d}, {a, cp, b, d}, {c, a, b, d}};
        for (string fj : fgen) {
          if (!nf.empty() && (*nf.begin())[0] > fj[0])
            nf.clear();
          if (nf.empty() || (*nf.begin())[0] == fj[0])
            nf.insert(fj);
        }
      }
      char tf = (*nf.begin())[0], tg = (*ng.begin())[0];
      if (tf < tg)
        ng.clear();
      if (tf > tg)
        nf.clear();
      f.clear();
      g.clear();
      ans.push_back(min(tf, tg));
      for (string fi : nf)
        f.emplace_back(fi.substr(1, 3));
      for (string gi : ng)
        g.emplace_back(gi.substr(1, 3));
    }
    for (string gi : g)
      f.emplace_back(gi);
    ans += (*min_element(f.begin(), f.end())).substr(0, 2);
    printf("%s\n", ans.c_str());
  }
};

int main() {
  int t;
  cin >> t;
  while (t--) {
    Solution solution = Solution();
    solution.solve();
  }
}