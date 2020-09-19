#include <iostream>
#include <vector>
#define MAXN 200005
#define lson (idx << 1)
#define rson (idx << 1 | 1)

using namespace std;
typedef long long ll;

struct Node {
  int l, r, hi, lazy = 0;
};

struct SegTree {
  Node s[MAXN << 2];
  void calc(int idx) { s[idx].hi = max(s[lson].hi, s[rson].hi); }

  void pushdown(int idx) {
    if (s[idx].lazy) {
      for (int i = lson; i <= rson; ++i) {
        if (s[i].hi > s[idx].lazy) {
          s[i].hi = s[idx].lazy;
          s[i].lazy = s[idx].lazy;
        }
      }
    }
    s[idx].lazy = 0;
  }

  void build(int idx, int l, int r, vector<int> &a) {
    s[idx].l = l, s[idx].r = r;
    if (l == r) {
      s[idx].hi = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(lson, l, mid, a);
    build(rson, mid + 1, r, a);
    calc(idx);
  }

  void update(int idx, int l, int r, int x) {
    if (s[idx].hi <= x)
      return;
    if (s[idx].l >= l && s[idx].r <= r) {
      s[idx].hi = x;
      s[idx].lazy = x;
      return;
    }
    pushdown(idx);
    int mid = (s[idx].l + s[idx].r) >> 1;
    if (l <= mid)
      update(lson, l, r, x);
    if (mid + 1 <= r)
      update(rson, l, r, x);
    calc(idx);
  }

  int query(int idx, int l, int r) {
    if (s[idx].l >= l && s[idx].r <= r)
      return s[idx].hi;
    pushdown(idx);
    int ans = 0;
    int mid = (s[idx].l + s[idx].r) >> 1;
    if (l <= mid)
      ans = max(ans, query(lson, l, r));
    if (mid + 1 <= r)
      ans = max(ans, query(rson, l, r));
    return ans;
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> col(n + 1, n), row(n + 1, n);
  col[n] = 1, row[n] = 1;
  SegTree C, R;
  C.build(1, 1, n, col);
  R.build(1, 1, n, row);
  ll ans = (ll)(n - 2) * (n - 2);
  for (int i = 0; i < q; ++i) {
    int t, x;
    cin >> t >> x;
    if (t == 1) {
      int hi = C.query(1, x, x);
      ans -= hi - 2;
      R.update(1, 1, hi, x);
      C.update(1, x, x, 1);
    } else {
      int hi = R.query(1, x, x);
      ans -= hi - 2;
      C.update(1, 1, hi, x);
      R.update(1, x, x, 1);
    }
  }
  cout << ans;
}