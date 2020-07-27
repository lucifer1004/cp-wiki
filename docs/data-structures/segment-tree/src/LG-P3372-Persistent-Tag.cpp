#include <iostream>
#define lson(idx) (idx << 1)
#define rson(idx) (idx << 1 | 1)
#define MAXN 100005
typedef long long ll;
using namespace std;
struct Node {
  ll sum = 0, lazy = 0;
  int l, r;
} s[MAXN << 2];
int a[MAXN];

void calc(int idx) {
  s[idx].sum = 0;

  // 注意在pushup的时候带上孩子节点的懒标记值
  for (int i = lson(idx); i <= rson(idx); ++i)
    s[idx].sum += s[i].sum + s[i].lazy * (s[i].r - s[i].l + 1);
}

void build(int idx, int l, int r) {
  s[idx].l = l, s[idx].r = r;
  if (l == r) {
    s[idx].sum = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  if (l <= mid)
    build(lson(idx), l, mid);
  if (mid < r)
    build(rson(idx), mid + 1, r);
  calc(idx);
}

void update(int idx, int l, int r, int delta) {
  if (s[idx].l >= l && s[idx].r <= r) {
    s[idx].lazy += delta;
    return;
  }
  int mid = (s[idx].l + s[idx].r) >> 1;
  if (l <= mid)
    update(lson(idx), l, r, delta);
  if (mid < r)
    update(rson(idx), l, r, delta);
  calc(idx);
}

ll query(int idx, int l, int r, ll lz) {
  if (s[idx].l >= l && s[idx].r <= r)
    return s[idx].sum + (lz + s[idx].lazy) * (s[idx].r - s[idx].l + 1);
  ll ans = 0;
  int mid = (s[idx].l + s[idx].r) >> 1;

  // 懒标记值自上而下逐层累加
  if (l <= mid)
    ans += query(lson(idx), l, r, lz + s[idx].lazy);
  if (mid < r)
    ans += query(rson(idx), l, r, lz + s[idx].lazy);
  return ans;
}

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  build(1, 1, n);
  for (int i = 1; i <= m; ++i) {
    int op, l, r;
    cin >> op >> l >> r;
    if (op == 1) {
      int x;
      cin >> x;
      update(1, l, r, x);
    } else
      cout << query(1, l, r, 0) << endl;
  }
}
