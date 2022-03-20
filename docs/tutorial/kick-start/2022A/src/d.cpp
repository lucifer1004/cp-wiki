#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

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

ll gcd_[1200][120];
ll dp[120][120][2][2];

class Solution {
  ll calc(ll num) {
    if (num == 0) return 0;

    string S = to_string(num);
    int n = S.size();
    int max_sum = 9 * n;

    ll ans = 0;
    for (int sum = 1; sum <= max_sum; ++sum) {
      memset(dp, 0, sizeof(dp));
      dp[0][0][0][1] = 1;
      for (int i = 0; i < n; ++i) {
        int si = S[i] - '0';
        for (int p = sum; p >= 0; --p) {
          // Optimization 1: p can only be 0 or a factor of sum
          if (p != 0 && sum % p != 0) continue;
          for (int s = min(sum, i * 9); s >= 0; --s) {
            ll v00 = dp[p][s][0][0], v01 = dp[p][s][0][1], v10 = dp[p][s][1][0],
               v11 = dp[p][s][1][1];
            // Optimization 2: all are 0 so have no future effects
            if (v00 + v01 + v10 + v11 == 0) continue;
            dp[p][s][0][0] = dp[p][s][0][1] = dp[p][s][1][0] = dp[p][s][1][1] =
                0;

            // Enumerate choice of the current position
            for (int nxt = 0; nxt <= 9; ++nxt) {
              int np = gcd_[max(p, 1) * nxt][sum];
              int ns = s + nxt;

              // Case 1: z == 0 && same == 0
              if (nxt == 0)
                dp[p][s][0][0] += v00;
              else if (s + nxt <= sum)
                dp[np][ns][1][0] += v00;

              // Case 2: z == 0 && same == 1
              if (nxt == 0) {
                dp[p][s][0][0] += v01;
              } else {
                if (nxt < si && ns <= sum) {
                  dp[np][ns][1][0] += v01;
                } else if (nxt == si && ns <= sum) {
                  dp[np][ns][1][1] += v01;
                }
              }

              // Case 3: z == 1 && same == 0
              if (ns <= sum) dp[np][ns][1][0] += v10;

              // Case 4: z == 1 && same == 1
              if (nxt < si && ns <= sum) {
                dp[np][ns][1][0] += v11;
              } else if (nxt == si && ns <= sum) {
                dp[np][ns][1][1] += v11;
              }
            }
          }
        }
      }
      ans += dp[sum][sum][1][0] + dp[sum][sum][1][1];
    }

    return ans;
  }

 public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);
    ll A, B;
    read(A), read(B);
    cout << calc(B) - calc(A - 1) << endl;
  }
};

int main() {
  int t;
  read(t);

  // Optimization 3: Precalculate GCDs
  for (int i = 0; i < 1200; ++i)
    for (int j = 0; j < 120; ++j) gcd_[i][j] = gcd(i, j);

  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
