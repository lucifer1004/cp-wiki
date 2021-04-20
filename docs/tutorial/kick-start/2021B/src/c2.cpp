#include <bitset>
#include <cstdio>
#include <iostream>
#define MAXN 1000000010
#define MAXP 51000000

using namespace std;
typedef long long ll;

bitset<MAXN> p;
int primes[MAXP], ptr = 0;

template <typename T>
void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-') sig = -1;
  for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

class Solution {
 public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    ll n;
    read(n);
    int lo = 0, hi = ptr - 2;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      ll prod = 1LL * primes[mid] * primes[mid + 1];
      if (prod <= n)
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    printf("%lld\n", 1LL * primes[lo - 1] * primes[lo]);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  p[1] = true;
  for (int i = 2; i < MAXN; ++i) {
    if (!p[i]) primes[ptr++] = i;
    for (int j = 0; j < ptr && 1LL * i * primes[j] < MAXN; ++j) {
      p[i * primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
