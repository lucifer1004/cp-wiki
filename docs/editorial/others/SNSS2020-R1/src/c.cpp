#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

bool adj[105][10005], vis[10005];
int n, m, link[10005], match = 0;

bool find(int u) {
  for (int v = 1; v <= m; ++v) {
    if (adj[u][v] && !vis[v]) {
      vis[v] = true;
      if (link[v] == 0 || find(link[v])) {
        link[v] = u;
        return true;
      }
    }
  }
  return false;
}

void hungary() {
  for (int i = 1; i <= n; ++i) {
    memset(vis, 0, sizeof(vis));
    if (find(i))
      match++;
  }
}

int main() {
  cin >> n;

  set<string> abbr;
  vector<vector<string>> comb(n);
  for (int i = 0; i < n; ++i) {
    string s, t;
    cin >> s >> t;
    int ls = s.size(), lt = t.size();
    for (int j = 1; j <= ls; ++j)
      for (int k = 1; k <= lt; ++k) {
        string st = s.substr(0, j) + t.substr(0, k);
        abbr.insert(st);
        comb[i].emplace_back(st);
      }
  }
  vector<string> v(abbr.begin(), abbr.end());
  m = v.size();
  map<string, int> dict;
  for (int i = 0; i < m; ++i)
    dict[v[i]] = i + 1;
  memset(adj, 0, sizeof(adj));
  memset(link, 0, sizeof(link));
  for (int i = 0; i < n; ++i)
    for (string st : comb[i])
      adj[i + 1][dict[st]] = true;

  hungary();
  if (match != n)
    cout << "No solution";
  else {
    vector<string> ans(n + 1);
    for (int i = 1; i <= m; ++i)
      if (link[i])
        ans[link[i]] = v[i - 1];
    for (int i = 1; i <= n; ++i)
      cout << ans[i] << endl;
  }
}
