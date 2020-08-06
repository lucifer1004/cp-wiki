#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

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

class Solution {
  int n;
  vector<ll> a;
  vector<int> b, in, left, right;

public:
  void solve() {
    read(n);
    a = vector<ll>(n + 1);
    b = vector<int>(n + 1);
    in = vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
      read(a[i]);
    for (int i = 1; i <= n; ++i) {
      read(b[i]);
      if (b[i] != -1)
        in[b[i]]++;
    }
    queue<int> q;
    ll result = 0;
    for (int i = 1; i <= n; ++i) {
      if (in[i] == 0)
        q.push(i);
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (a[u] < 0)
        right.emplace_back(u);
      else {
        left.emplace_back(u);
        if (b[u] != -1)
          a[b[u]] += a[u];
      }
      result += a[u];
      if (b[u] != -1) {
        in[b[u]]--;
        if (in[b[u]] == 0)
          q.push(b[u]);
      }
    }
    printf("%lld\n", result);
    reverse(right.begin(), right.end());
    for (int i : left)
      printf("%d ", i);
    for (int i : right)
      printf("%d ", i);
    printf("\n");
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
