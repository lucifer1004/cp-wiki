#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define INF 10000000000000000LL

using namespace std;
typedef long long ll;

bool is_palindrome(string &s) {
  int n = s.size();
  for (int i = 0; i < n / 2; ++i)
    if (s[i] != s[n - i - 1])
      return false;
  return true;
}

int n;
unordered_map<string, ll> memo[2];
unordered_set<string> vis[2];
vector<string> S[2];
vector<ll> C;
ll dfs(string s, int p) {
  if (memo[p].count(s))
    return memo[p][s];
  if (is_palindrome(s))
    return 0;
  if (vis[p].count(s))
    return INF;
  vis[p].insert(s);
  ll ans = INF;
  int ls = s.size();
  for (int i = 0; i < n; ++i) {
    string t = S[!p][i];
    int lt = t.size();
    int l = min(ls, lt);
    string ps = s.substr(0, l);
    string pt = t.substr(0, l);
    if (ps != pt)
      continue;
    ll cost =
        ls > lt ? dfs(s.substr(l, ls - l), p) : dfs(t.substr(l, lt - l), !p);
    if (cost < ans)
      ans = min(ans, cost + C[i]);
  }
  vis[p].erase(s);
  memo[p][s] = ans;
  return ans;
}

int main() {
  cin >> n;
  S[0] = vector<string>(n);
  S[1] = vector<string>(n);
  C = vector<ll>(n);
  ll ans = INF;
  for (int i = 0; i < n; ++i) {
    cin >> S[0][i] >> C[i];
    S[1][i] = string(S[0][i].rbegin(), S[0][i].rend());
  }
  for (int i = 0; i < n; ++i)
    ans = min(ans, dfs(S[0][i], 0) + C[i]);
  cout << (ans == INF ? -1 : ans);
}
