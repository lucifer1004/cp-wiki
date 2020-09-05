#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MAXN 1000000
#define lson (idx << 1)
#define rson (idx << 1 | 1)

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

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

struct Node {
  int l, r, zero = 0, first = 0, second = 0;
  bool lazy = false;
} s[(MAXN + 10) << 2];

void calc(int idx) {
  s[idx].zero = s[lson].zero + s[rson].zero;
  s[idx].first = s[lson].first + s[rson].first;
  s[idx].second = s[lson].second + s[rson].second;
}

void update(int idx) {
  s[idx].second += s[idx].first;
  s[idx].first = s[idx].zero;
  s[idx].zero = 0;
  s[idx].lazy = true;
  return;
}

void pushdown(int idx) {
  if (s[idx].lazy)
    for (int i = lson; i <= rson; ++i)
      update(i);
  s[idx].lazy = false;
}

void build(int idx, int l, int r) {
  s[idx].l = l, s[idx].r = r;
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  build(lson, l, mid);
  build(rson, mid + 1, r);
}

void update(int idx, int l, int r) {
  if (s[idx].l >= l && s[idx].r <= r) {
    update(idx);
    return;
  }
  pushdown(idx);
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (l <= mid)
    update(lson, l, r);
  if (mid + 1 <= r)
    update(rson, l, r);
  calc(idx);
}

void inc(int idx, int pos) {
  if (s[idx].l == s[idx].r && s[idx].l == pos) {
    s[idx].zero++;
    return;
  }
  pushdown(idx);
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (pos <= mid)
    inc(lson, pos);
  else
    inc(rson, pos);
  calc(idx);
}

void dec(int idx, int pos) {
  if (s[idx].l == s[idx].r && s[idx].l == pos) {
    s[idx].zero = s[idx].first = s[idx].second = 0;
    return;
  }
  pushdown(idx);
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (pos <= mid)
    dec(lson, pos);
  else
    dec(rson, pos);
  calc(idx);
}

int query(int idx, int l, int r) {
  if (s[idx].l >= l && s[idx].r <= r)
    return s[idx].second;
  pushdown(idx);
  int mid = (s[idx].l + s[idx].r) >> 1;
  int ans = 0;
  if (l <= mid)
    ans += query(lson, l, r);
  if (mid + 1 <= r)
    ans += query(rson, l, r);
  return ans;
}

class Solution {
public:
  void solve() {
    int n, m;
    read(n), read(m);
    vector<pair<int, pii>> hseg, vseg;
    vector<vector<int>> start(MAXN + 1), end(MAXN + 1);
    for (int i = 0; i < n; ++i) {
      int y, l, r;
      read(y), read(l), read(r);
      hseg.push_back({y, {l, r}});
    }
    hseg.push_back({0, {0, MAXN}});
    hseg.push_back({MAXN, {0, MAXN}});
    for (auto p : hseg) {
      int y = p.first;
      int l = p.second.first, r = p.second.second;
      start[l].emplace_back(y);
      end[r].emplace_back(y);
    }
    for (int i = 0; i < m; ++i) {
      int x, l, r;
      read(x), read(l), read(r);
      vseg.push_back({x, {l, r}});
    }
    vseg.push_back({0, {0, MAXN}});
    vseg.push_back({MAXN, {0, MAXN}});
    sort(vseg.begin(), vseg.end());
    ll ans = 0;
    build(1, 1, MAXN + 1);
    for (int i = 0; i < vseg.size(); ++i) {
      auto &p = vseg[i];
      int x = p.first;
      for (int y : start[x])
        inc(1, y + 1);
      int l = p.second.first, r = p.second.second;
      update(1, l + 1, r + 1);
      int cross = query(1, l + 1, r + 1);
      ans += max(0, cross - 1);
      for (int y : end[x])
        dec(1, y + 1);
      if (i + 1 < vseg.size())
        for (int j = x + 1; j < vseg[i + 1].first; ++j) {
          for (int y : start[j])
            inc(1, y + 1);
          for (int y : end[j])
            dec(1, y + 1);
        }
    }
    printf("%lld", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}