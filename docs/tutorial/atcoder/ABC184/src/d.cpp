#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define MAXN 101

using namespace std;
double memo[MAXN][MAXN][MAXN]{};

double dfs(vector<int> &coins) {
  if (coins[1] == 0)
    return 100.0 - coins[0];
  if (coins[0] == 100 || coins[1] == 100 || coins[2] == 100)
    return 0.0;
  if (memo[coins[0]][coins[1]][coins[2]] >= 0)
    return memo[coins[0]][coins[1]][coins[2]];
  int s = 0;
  for (int coin : coins)
    s += coin;
  double ans = 0;
  for (int i = 0; i < 3; ++i) {
    if (coins[i] > 0) {
      vector<int> nxt(coins);
      nxt[i]++;
      ans += (double)coins[i] / s * (1 + dfs(nxt));
    }
  }
  return memo[coins[0]][coins[1]][coins[2]] = ans;
}

int main() {
  vector<int> coins(3);
  for (int i = 0; i < 3; ++i)
    cin >> coins[i];
  sort(coins.rbegin(), coins.rend());
  memset(memo, -1.0, sizeof(memo));
  printf("%.12f", dfs(coins));
}