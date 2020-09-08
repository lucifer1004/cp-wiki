#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
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
  vector<set<int>> adj;

public:
  void solve() {
    int n;
    read(n);
    vector<int> h(n);
    for (int i = 0; i < n; ++i)
      read(h[i]);
    adj = vector<set<int>>(n);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
      while (!st.empty() && h[i] <= h[st.top()]) {
        adj[st.top()].insert(i);
        st.pop();
      }
      st.push(i);
    }
    while (!st.empty())
      st.pop();
    for (int i = 0; i < n; ++i) {
      while (!st.empty() && h[i] >= h[st.top()]) {
        adj[st.top()].insert(i);
        st.pop();
      }
      st.push(i);
    }
    while (!st.empty())
      st.pop();
    for (int i = n - 1; i >= 0; --i) {
      while (!st.empty() && h[i] <= h[st.top()]) {
        adj[i].insert(st.top());
        st.pop();
      }
      st.push(i);
    }
    while (!st.empty())
      st.pop();
    for (int i = n - 1; i >= 0; --i) {
      while (!st.empty() && h[i] >= h[st.top()]) {
        adj[i].insert(st.top());
        st.pop();
      }
      st.push(i);
    }
    queue<int> q;
    q.push(0);
    vector<int> dist(n, -1);
    dist[0] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == n - 1) {
        printf("%d", dist[u]);
        return;
      }
      for (int v : adj[u]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Solution solution = Solution();
  solution.solve();
}
