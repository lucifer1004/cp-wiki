#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

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

class Solution {
public:
  void solve() {
    int n;
    read(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
      read(a[i]);
    vector<int> primes = {2, 3, 5, 7, 11, 13};
    for (int i = 17; i < 1000; i += 2) {
      bool ok = true;
      for (int j = 0; primes[j] * primes[j] <= i; ++j) {
        if (i % primes[j] == 0) {
          ok = false;
          break;
        }
      }
      if (ok)
        primes.emplace_back(i);
    }
    map<int, int> cnt;
    for (int i : a) {
      int t = i;
      for (int j = 0; primes[j] * primes[j] <= t; ++j) {
        if (t % primes[j] == 0)
          cnt[primes[j]]++;
        while (t % primes[j] == 0)
          t /= primes[j];
      }
      if (t != 1)
        cnt[t]++;
    }
    int hi = 0;
    for (auto p : cnt)
      hi = max(hi, p.second);
    if (hi <= 1) {
      printf("pairwise coprime");
      return;
    }
    printf(hi < n ? "setwise coprime" : "not coprime");
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
