#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

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
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    int n;
    read(n);
    vector<int> e(n + 1), r(n + 1);
    priority_queue<pair<int, int>> pq;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
      read(e[i]), read(r[i]);
      pq.push({e[i] + r[i], i});
      sum += e[i];
    }
    ll csum = sum;
    while (!pq.empty()) {
      int val = pq.top().first, i = pq.top().second;
      if (val <= csum)
        break;
      else {
        pq.pop();
        csum -= e[i];
      }
    }
    if (!pq.empty()) {
      printf("%d INDEFINITELY\n", n - (int)pq.size());
      return;
    }
    ll max_val = csum = sum, min_del = 0, cdel = 0, cval = sum;
    for (int i = 1; i <= n; ++i) {
      if (e[i] + r[i] <= csum) {
        cval += e[i];
        pq.push({e[i] + r[i], i});
        if (cval > max_val) {
          max_val = cval;
          min_del = cdel;
        }
      } else {
        csum -= e[i];
        cval -= e[i];
        cdel++;
        while (!pq.empty() && pq.top().first > csum) {
          int val = pq.top().first, j = pq.top().second;
          pq.pop();
          csum -= e[j];
          cval -= 2 * e[j];
          cdel++;
        }
      }
    }
    printf("%lld %lld\n", min_del, max_val);
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