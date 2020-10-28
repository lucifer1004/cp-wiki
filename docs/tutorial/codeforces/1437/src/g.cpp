#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;
struct Node {
  int idx = -1, fail = 0, children[26]{};
};

int main() {
  int n, q;
  cin >> n >> q;

  vector<string> names(n + 1);
  unordered_map<string, int> dict;
  unordered_map<int, int> id_dict;
  vector<set<pair<int, int>, greater<>>> heaps;
  vector<int> suspicion(n + 1);
  suspicion[0] = -1;
  vector<Node> nodes = {Node{}};
  int idx = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> names[i];
    if (dict.count(names[i])) {
      heaps[dict[names[i]]].emplace(0, i);
      id_dict[i] = dict[names[i]];
      continue;
    }
    dict[names[i]] = idx;
    id_dict[i] = idx;
    heaps.push_back({{0, i}});
    int p = 0;
    for (char c : names[i]) {
      if (!nodes[p].children[c - 'a']) {
        nodes[p].children[c - 'a'] = nodes.size();
        nodes.emplace_back(Node{});
      }
      p = nodes[p].children[c - 'a'];
    }
    nodes[p].idx = idx++;
  }

  queue<int> que, visited;
  vector<bool> vis(nodes.size());
  for (int u : nodes[0].children)
    if (u)
      que.push(u);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int i = 0; i < 26; ++i) {
      auto &v = nodes[u].children[i];
      if (v) {
        nodes[v].fail = nodes[nodes[u].fail].children[i];
        que.push(v);
      } else
        v = nodes[nodes[u].fail].children[i];
    }
  }

  string output;

  auto query = [&](string &s) {
    int ans = -1;
    int p = 0;
    int idx = 0;
    while (idx < s.size()) {
      char c = s[idx];
      if (nodes[p].children[c - 'a']) {
        p = nodes[p].children[c - 'a'];
        if (!vis[p]) {
          vis[p] = true;
          que.push(p);
        }
        idx++;
      } else {
        p = nodes[p].fail;
        if (!p)
          idx++;
      }
    }
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      visited.push(u);
      if (nodes[u].idx != -1)
        ans = max(ans, heaps[nodes[u].idx].begin()->first);
      if (nodes[u].fail && !vis[nodes[u].fail]) {
        vis[nodes[u].fail] = true;
        que.push(nodes[u].fail);
      }
    }
    while (!visited.empty()) {
      vis[visited.front()] = false;
      visited.pop();
    }
    output += to_string(ans) + "\n";
  };

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int i, x;
      cin >> i >> x;
      heaps[id_dict[i]].erase({suspicion[i], i});
      suspicion[i] = x;
      heaps[id_dict[i]].emplace(suspicion[i], i);
    } else {
      string s;
      cin >> s;
      query(s);
    }
  }

  cout << output;
}