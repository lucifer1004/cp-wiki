#include <cmath>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>
#define INF 0x3f3f3f3f;
#define K 18

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
  void solve(int case_num) {
    int n, q;
    read(n), read(q);
    vector<int> a(n + 1);
    for (int i = 1; i <= n - 1; ++i)
      read(a[i]);
    a[0] = INF;
    a[n] = INF;
    printf("Case #%d: ", case_num);
    vector<int> lf(n + 1, -1), rf(n + 1, n + 1);
    vector<vector<int>> sparse(n + 1, vector<int>(K));
    for (int i = 0; i <= n; ++i)
      sparse[i][0] = i;
    for (int k = 1; k < K; ++k) {
      for (int i = 0; i <= n; ++i) {
        sparse[i][k] = sparse[i][k - 1];
        int right = i + (1 << (k - 1));
        if (right <= n && a[sparse[right][k - 1]] > a[sparse[i][k]])
          sparse[i][k] = sparse[right][k - 1];
      }
    }
    auto query_sparse = [&](int l, int r) {
      if (l == r)
        return l;
      int len = r - l + 1;
      int half = trunc(log2(len - 1));
      int ans = sparse[l][half];
      if (a[sparse[r - (1 << half) + 1][half]] > a[ans])
        ans = sparse[r - (1 << half) + 1][half];
      return ans;
    };
    stack<int> st;
    for (int i = 0; i <= n; ++i) {
      while (!st.empty() && a[st.top()] < a[i]) {
        rf[st.top()] = i;
        st.pop();
      }
      st.push(i);
    }
    st = stack<int>();
    for (int i = n; i >= 0; --i) {
      while (!st.empty() && a[st.top()] < a[i]) {
        lf[st.top()] = i;
        st.pop();
      }
      st.push(i);
    }
    while (q--) {
      int s, k;
      read(s), read(k);

      auto output = [&](int ans) { printf("%d ", ans); };

      if (rf[s - 1] - (s - 1) > k - 1) {
        int ans = s + k - 1;
        if (ans > n)
          ans = n - k + 1;
        output(ans);
        continue;
      }
      if (s - lf[s] > k - 1) {
        int ans = s - k + 1;
        if (ans < 1)
          ans = k;
        output(ans);
        continue;
      }
      int l = 1, r = min(k - 2, s);
      while (l <= r) {
        int mid = (l + r) >> 1;
        int ma = query_sparse(s - mid, s - 1);
        int right = rf[ma];
        int tot = right - (s - mid);
        if (tot > k - 1)
          r = mid - 1;
        else
          l = mid + 1;
      }
      int lmost = s - r;
      int rmost = s - r + k - 2;
      int ans;
      if (rmost > n)
        ans = n - k + 1;
      else {
        int hi = query_sparse(lmost, rmost);
        if (hi >= s)
          ans = rmost + 1;
        else
          ans = lmost;
      }
      output(ans);
    }
    printf("\n");
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
