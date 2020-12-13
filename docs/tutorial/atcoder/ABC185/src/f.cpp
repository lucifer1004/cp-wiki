#include <atcoder/segtree>
#include <iostream>
#include <vector>

using namespace std;

int op(int a, int b) { return a ^ b; }

int e() { return 0; }

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> v(n);
  for (int i = 0; i < n; ++i)
    cin >> v[i];
  atcoder::segtree<int, op, e> seg(v);
  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      seg.set(x - 1, v[x - 1] ^ y);
      v[x - 1] ^= y;
    } else {
      cout << seg.prod(x - 1, y) << endl;
    }
  }
}