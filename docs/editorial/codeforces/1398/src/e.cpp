#include <cstdio>
#include <iostream>
#include <set>

using namespace std;
typedef long long ll;

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
  void solve() {
    int n;
    read(n);
    set<int> fire, lightning, topk, rest, rf;
    int l = 0, tl = 0;
    ll ans = 0;
    auto move_from_rest_to_topk = [&](int k) {
      rest.erase(k);
      topk.insert(k);
      if (fire.count(k))
        rf.erase(k);
      else
        tl++;
      ans += k;
    };
    auto move_from_topk_to_rest = [&](int k) {
      topk.erase(k);
      rest.insert(k);
      if (fire.count(k))
        rf.insert(k);
      else
        tl--;
      ans -= k;
    };
    for (int i = 0; i < n; ++i) {
      int tp, p;
      read(tp), read(p);
      if (tp == 0) {
        if (p > 0) {
          fire.insert(p);
          if (l > 0 && p > *topk.begin()) {
            int rep = *topk.begin();
            move_from_topk_to_rest(rep);
            topk.insert(p);
            ans += 2 * p;
          } else {
            rest.insert(p);
            rf.insert(p);
            ans += p;
          }
        } else {
          p = -p;
          fire.erase(p);
          if (rest.count(p)) {
            ans -= p;
            rest.erase(p);
            rf.erase(p);
          } else {
            topk.erase(p);
            int rep = *rest.rbegin();
            move_from_rest_to_topk(rep);
            ans -= 2 * p;
          }
        }
      } else {
        if (p > 0) {
          lightning.insert(p);
          l++;
          rest.insert(p);
          ans += p;
          int rep = *rest.rbegin();
          move_from_rest_to_topk(rep);
        } else {
          p = -p;
          lightning.erase(p);
          l--;
          if (rest.count(p)) {
            rest.erase(p);
            ans -= p;
            int rep = *topk.begin();
            move_from_topk_to_rest(rep);
          } else {
            topk.erase(p);
            ans -= p * 2;
            tl--;
          }
        }
      }
      ll cans = ans;
      if (tl == l && tl > 0) {
        int rep = *topk.begin();
        cans -= rep;
        int other = 0;
        if (!rf.empty())
          other = *rf.rbegin();
        cans += other;
      }
      printf("%lld\n", cans);
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}