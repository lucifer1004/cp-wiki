#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

inline int go(int x, int y, int op_type) {
  switch (op_type) {
  case 0:
    return x | y;
  case 1:
    return x & y;
  default:
    return x ^ y;
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> op(n);
  vector<bitset<32>> t(n);
  for (int i = 0; i < n; ++i) {
    string s;
    int ti;
    cin >> s >> ti;
    t[i] = bitset<32>(ti);
    if (s == "AND")
      op[i] = 1;
    else if (s == "XOR")
      op[i] = 2;
  }
  int ans = 0;
  for (int i = 29; i >= 0; --i) {
    bool flag = m & (1 << i);
    int zero = 0, one = 1;
    for (int j = 0; j < n; ++j) {
      zero = go(zero, t[j][i], op[j]);
      one = go(one, t[j][i], op[j]);
    }
    one = one && flag;
    if (flag && (zero || !one))
      m = (1 << i) - 1;
    if (zero || one)
      ans += 1 << i;
  }
  cout << ans;
}
