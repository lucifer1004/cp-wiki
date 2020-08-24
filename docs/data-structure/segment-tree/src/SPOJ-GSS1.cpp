#include <iostream>
#define lson (idx << 1)
#define rson (idx << 1 | 1)
#define INF 0x3f3f3f3f
#define MAXN 50005

using namespace std;
struct Node {
  int l = 0, r = 0, lhi = 0, rhi = 0, hi = 0, sum = 0;
} s[MAXN << 2];
int a[MAXN];

Node merge(Node l, Node r) {
  Node ret;
  ret.l = l.l;
  ret.r = r.r;
  ret.sum = l.sum + r.sum;
  ret.lhi = max(l.lhi, l.sum + r.lhi);
  ret.rhi = max(r.rhi, l.rhi + r.sum);
  ret.hi = max(max(max(ret.lhi, ret.rhi), max(l.hi, r.hi)), l.rhi + r.lhi);
  return ret;
}

void calc(int idx) { s[idx] = merge(s[lson], s[rson]); }

void build(int idx, int l, int r) {
  if (l == r) {
    s[idx].l = l, s[idx].r = r;
    s[idx].hi = s[idx].lhi = s[idx].rhi = s[idx].sum = a[r];
    return;
  }

  int mid = (l + r) >> 1;
  build(lson, l, mid);
  build(rson, mid + 1, r);
  calc(idx);
}

Node query(int idx, int l, int r) {
  if (s[idx].l >= l && s[idx].r <= r)
    return s[idx];
  Node ans;
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (l <= mid)
    ans = query(lson, l, r);
  if (mid + 1 <= r) {
    Node right = query(rson, l, r);
    if (!ans.l)
      return right;
    ans = merge(ans, right);
  }
  return ans;
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  build(1, 1, n);
  int m;
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    int l, r;
    cin >> l >> r;
    cout << query(1, l, r).hi << endl;
  }
}
