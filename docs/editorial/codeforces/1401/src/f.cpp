#include <cstdio>
#include <iostream>
#define MAXN 300005
#define lson (idx << 1)
#define rson (idx << 1 | 1)

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

int a[MAXN], ss = 0, rr = 0;
ll s[MAXN << 2];

void calc(int idx) { s[idx] = s[lson] + s[rson]; }

void build(int idx, int l, int r) {
  if (l == r) {
    s[idx] = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(lson, l, mid);
  build(rson, mid + 1, r);
  calc(idx);
}

void move(int &idx, int level) { idx = ((idx - 1) ^ (1 << (level - 1))) + 1; }

void update(int idx, int pos, int val, int level, int cl, int cr) {
  if (level == 0) {
    s[idx] = val;
    return;
  }
  bool fr = (rr & (1 << level));
  bool fs = (ss & (1 << level));
  int mid = (cl + cr) >> 1;
  if (fr)
    pos = cl + cr - pos;
  if (fs)
    move(pos, level);
  if (pos <= mid)
    update(lson, pos, val, level - 1, cl, mid);
  else
    update(rson, pos, val, level - 1, mid + 1, cr);
  calc(idx);
}

ll query(int idx, int l, int r, int level, int cl, int cr) {
  if (cl >= l && cr <= r)
    return s[idx];
  ll ans = 0;
  bool fr = (rr & (1 << level));
  bool fs = (ss & (1 << level));
  int mid = (cl + cr) >> 1;
  if (fr)
    l = cl + cr - l, r = cl + cr - r, swap(l, r);
  if (r <= mid || l >= mid + 1) {
    if (fs)
      move(l, level), move(r, level);
    if (l <= mid)
      ans += query(lson, l, r, level - 1, cl, mid);
    else
      ans += query(rson, l, r, level - 1, mid + 1, cr);
  } else {
    int le = mid, rs = mid + 1;
    if (fs)
      move(l, level), move(le, level), move(rs, level), move(r, level);
    if (l > rs)
      swap(l, rs), swap(le, r);
    ans += query(lson, l, le, level - 1, cl, mid);
    ans += query(rson, rs, r, level - 1, mid + 1, cr);
  }
  return ans;
}

class Solution {
public:
  void solve() {
    int n, q;
    read(n), read(q);
    int R = 1 << n;
    for (int i = 1; i <= R; ++i)
      read(a[i]);
    build(1, 1, R);
    while (q--) {
      int t, x, k, l, r;
      read(t);
      switch (t) {
      case 1:
        read(x), read(k);
        update(1, x, k, n, 1, R);
        break;
      case 2:
        read(k);
        rr ^= (1 << k);
        break;
      case 3:
        read(k);
        ss ^= (1 << (k + 1));
        break;
      default:
        read(l), read(r);
        printf("%lld\n", query(1, l, r, n, 1, R));
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}