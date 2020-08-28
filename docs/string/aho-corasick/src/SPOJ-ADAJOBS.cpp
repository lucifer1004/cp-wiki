#include <iostream>
#include <queue>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

struct Node {
  int occur = INF, fail = 0, children[26]{};
};

int main() {
  int q;
  cin >> q;
  vector<string> dict;
  vector<pair<int, string>> query;
  while (q--) {
    int t;
    string s;
    cin >> t >> s;
    if (t == 0)
      dict.emplace_back(s);
    else
      query.emplace_back(dict.size(), s);
  }
  int m = dict.size();
  vector<Node> nodes(1);
  for (int i = 1; i <= m; ++i) {
    int current = 0;
    for (char c : dict[i - 1]) {
      if (!nodes[current].children[c - 'a']) {
        nodes[current].children[c - 'a'] = nodes.size();
        nodes.emplace_back(Node{});
      }
      current = nodes[current].children[c - 'a'];
    }
    nodes[current].occur = min(nodes[current].occur, i);
  }
  queue<int> que;
  for (const int &u : nodes[0].children)
    if (u)
      que.push(u);
  while (!que.empty()) {
    int u = que.front();

    // Push down the timestamp. This is critical.
    nodes[u].occur = min(nodes[u].occur, nodes[nodes[u].fail].occur);
    que.pop();
    for (int i = 0; i < 26; ++i) {
      int &v = nodes[u].children[i];
      if (v) {
        nodes[v].fail = nodes[nodes[u].fail].children[i];
        que.push(v);
      } else
        v = nodes[nodes[u].fail].children[i];
    }
  }
  string ans;
  for (auto &[ts, s] : query) {
    int current = 0;
    bool found = false;
    int idx = 0;
    while (idx < s.size()) {
      char c = s[idx];
      if (nodes[current].children[c - 'a']) {
        current = nodes[current].children[c - 'a'];
        if (nodes[current].occur <= ts) {
          ans += "YES\n";
          found = true;
          break;
        }
        idx++;
      } else {
        current = nodes[current].fail;
        if (!current)
          idx++;
      }
    }
    if (!found)
      ans += "NO\n";
  }
  cout << ans;
}
