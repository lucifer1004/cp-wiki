#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MOD 1000000007

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

struct Line {
  int l, r, y;
};

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

struct Fraction {
  int a, b;
  Fraction(int a, int b) {
    if (b < 0) {
      a = -a;
      b = -b;
    }
    int g = gcd(abs(a), abs(b));
    this->a = a / g;
    this->b = b / g;
  };
  bool operator<(const Fraction &other) const {
    return (ll)a * other.b < (ll)b * other.a;
  }
  bool operator<=(const Fraction &other) const {
    return (ll)a * other.b <= (ll)b * other.a;
  }
  bool operator>(const Fraction &other) const {
    return (ll)a * other.b > (ll)b * other.a;
  }
  bool operator>=(const Fraction &other) const {
    return (ll)a * other.b >= (ll)b * other.a;
  }
  bool operator!=(const Fraction &other) const {
    return (ll)a * other.b != (ll)b * other.a;
  }
  bool operator==(const Fraction &other) const {
    return (ll)a * other.b == (ll)b * other.a;
  }
};

class Solution {
  vector<pair<Fraction, Fraction>> seg;

  Fraction theta(int x1, int x2, int dy) { return Fraction(x1 - x2, dy); }

  void calc(Line a, Line b) {
    if (a.y == b.y)
      return;
    if (a.y < b.y)
      swap(a, b);
    Fraction t1 = theta(a.l, b.r, a.y - b.y);
    Fraction t2 = theta(a.r, b.l, a.y - b.y);
    if (t1 > t2)
      swap(t1, t2);
    seg.emplace_back(t1, t2);
  }

public:
  void solve() {
    int n;
    read(n);
    vector<Line> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i].l), read(a[i].r), read(a[i].y);
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
        calc(a[i], a[j]);
    double ans = 1e18;
    sort(seg.begin(), seg.end());
    vector<pair<Fraction, Fraction>> t;
    const Fraction magic(1, MOD);
    Fraction l0 = magic, r0 = magic;
    for (auto &[l, r] : seg) {
      if (l >= r0) {
        if (r0 != magic)
          t.emplace_back(l0, r0);
        l0 = l;
        r0 = r;
      } else {
        if (l0 == magic) {
          l0 = l;
          r0 = r;
        } else
          r0 = max(r0, r);
      }
    }
    if (l0 != magic)
      t.emplace_back(l0, r0);
    vector<Fraction> vt;
    for (auto &[l, r] : t)
      vt.emplace_back(l), vt.emplace_back(r);
    if (vt.empty())
      vt.emplace_back(0, 1);
    for (Fraction d : vt) {
      double l = 1e18, r = -1e18;
      for (auto &e : a) {
        l = min(l, (double)-d.a / d.b * e.y + e.l);
        r = max(r, (double)-d.a / d.b * e.y + e.r);
      }
      ans = min(ans, r - l);
    }
    printf("%.9f", ans);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
