#include <cstdio>
#include <iostream>
#include <vector>

#define lson (idx << 1)
#define rson (idx << 1 | 1)
#define INF 10000000000LL
#define MAXN 200010

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

// `lo` is the minimum of the segment.
// `lh` is the current value of the left endpoint.
// `rh` is the current value of the right endpoint.
// `lazy` is the lazy tag for addition.
// `flag` is the lazy tag for assignment.
struct Node {
  int l, r;
  ll lo, lh, rh, lazy = 0;
  bool flag = false;
} s[MAXN << 2];
int h, w;

void calc(int idx) {
  s[idx].lo = min(s[lson].lo, s[rson].lo);
  s[idx].lh = s[lson].lh;
  s[idx].rh = s[rson].rh;
}

void build(int idx, int l, int r) {
  s[idx].l = l, s[idx].r = r;
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  build(lson, l, mid);
  build(rson, mid + 1, r);
}

void pushdown(int idx) {
  if (s[idx].flag) {
    ll L = s[idx].lh, R = s[idx].rh;
    int l = s[idx].l, r = s[idx].r;
    for (int i = lson; i <= rson; ++i) {
      s[i].lh = min(L + s[i].l - l, R + r - s[i].l);
      s[i].rh = min(L + s[i].r - l, R + r - s[i].r);
      s[i].lo = min(s[i].lh, s[i].rh);
      s[i].flag = true;
      s[i].lazy = 0;
    }
  } else if (s[idx].lazy) {
    for (int i = lson; i <= rson; ++i) {
      s[i].lh += s[idx].lazy;
      s[i].rh += s[idx].lazy;
      s[i].lo += s[idx].lazy;
      s[i].lazy += s[idx].lazy;
    }
  }
  s[idx].flag = false;
  s[idx].lazy = 0;
}

void update(int idx, int l, int r, ll L, ll R) {
  if (s[idx].l >= l && s[idx].r <= r) {
    s[idx].lh = min(L + s[idx].l - l + 1, R + r - s[idx].l + 1);
    s[idx].rh = min(L + s[idx].r - l + 1, R + r - s[idx].r + 1);
    s[idx].lo = min(s[idx].lh, s[idx].rh);
    s[idx].flag = true;
    s[idx].lazy = 0;
    return;
  }
  pushdown(idx);
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (l <= mid)
    update(lson, l, r, L, R);
  if (mid + 1 <= r)
    update(rson, l, r, L, R);
  calc(idx);
}

void add(int idx, int l, int r) {
  if (s[idx].l >= l && s[idx].r <= r) {
    s[idx].lh++;
    s[idx].rh++;
    s[idx].lo++;
    s[idx].lazy++;
    return;
  }
  pushdown(idx);
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (l <= mid)
    add(lson, l, r);
  if (mid + 1 <= r)
    add(rson, l, r);
  calc(idx);
}

ll query(int idx, int l, int r) {
  if (r < 1 || l > w)
    return INF;
  if (s[idx].l >= l && s[idx].r <= r)
    return s[idx].lo;
  pushdown(idx);
  ll ans = INF;
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (l <= mid)
    ans = min(ans, query(lson, l, r));
  if (mid + 1 <= r)
    ans = min(ans, query(rson, l, r));
  return ans;
}

class Solution {
public:
  void solve() {
    read(h), read(w);
    vector<int> l(h), r(h);
    for (int i = 0; i < h; ++i)
      read(l[i]), read(r[i]);
    vector<ll> ans(h, INF);
    build(1, 1, w);
    for (int i = 0; i < h; ++i) {
      if (l[i] > 1)
        add(1, 1, l[i] - 1);
      if (r[i] < w)
        add(1, r[i] + 1, w);
      ll L = query(1, l[i] - 1, l[i] - 1);
      ll R = query(1, r[i] + 1, r[i] + 1);
      update(1, l[i], r[i], L, R);
      ans[i] = min(ans[i], query(1, 1, w));
      if (ans[i] == INF)
        break;
    }
    for (ll i : ans)
      cout << (i == INF ? -1 : i) << endl;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
