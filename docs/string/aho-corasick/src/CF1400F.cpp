#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
const int INF = 0x3f3f3f3f;

struct Node {
  int fail = 0, children[9]{};
  bool match = false;
};

string s, t;
int x, dp[5005][5005];
set<string> xprime;
vector<int> suffix = {0};
vector<Node> nodes;

void generate_xprime() {
  if (suffix[0] == x) {
    xprime.insert(t);
    return;
  }
  for (int i = 1; i <= 9 && i + suffix[0] <= x; ++i) {
    t.push_back(i + '0');
    for (int &j : suffix)
      j += i;
    suffix.emplace_back(i);
    bool ok = true;
    for (int &j : suffix)
      if (j != x && x % j == 0) {
        ok = false;
        break;
      }
    if (ok)
      generate_xprime();
    suffix.pop_back();
    for (int &j : suffix)
      j -= i;
    t.pop_back();
  }
}

void build_aca() {
  nodes.emplace_back(Node{});
  for (const string &str : xprime) {
    int curr = 0;
    for (const char &c : str) {
      if (!nodes[curr].children[c - '1']) {
        nodes[curr].children[c - '1'] = nodes.size();
        nodes.emplace_back(Node{});
      }
      curr = nodes[curr].children[c - '1'];
    }
    nodes[curr].match = true;
  }
  queue<int> q;
  for (const int &u : nodes[0].children)
    if (u)
      q.push(u);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 9; ++i) {
      int &v = nodes[u].children[i];
      if (v) {
        nodes[v].fail = nodes[nodes[u].fail].children[i];
        q.push(v);
      } else
        v = nodes[nodes[u].fail].children[i];
    }
  }
}

int main() {
  cin >> s >> x;

  // Step 1: Enumerate all x-prime strings
  generate_xprime();

  // Step 2: Build Aho-Corasick automaton with x-prime strings
  build_aca();

  // Step 3: Dynamic programming
  memset(dp, 0x3f, sizeof(dp));
  int n = s.size(), m = nodes.size(), ans = INF;
  dp[0][0] = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (dp[i][j] == INF)
        continue;
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
      int nxt = nodes[j].children[s[i] - '1'];
      if (!nodes[nxt].match)
        dp[i + 1][nxt] = min(dp[i + 1][nxt], dp[i][j]);
    }
  for (int j = 0; j < m; ++j)
    ans = min(ans, dp[n][j]);
  cout << ans;
}
