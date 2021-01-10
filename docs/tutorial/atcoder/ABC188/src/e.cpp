#include <iostream>
#include <vector>
#define MAXN 200005

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<int> A(N + 1);
  for (int i = 1; i <= N; ++i)
    cin >> A[i];

  vector<vector<int>> adj(N + 1);
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].emplace_back(v);
  }

  vector<int> hi(N + 1, -1e9);
  int ans = -1e9;
  for (int i = N; i >= 1; --i) {
    for (int v : adj[i])
      hi[i] = max(hi[i], hi[v]);
    ans = max(ans, hi[i] - A[i]);
    hi[i] = max(hi[i], A[i]);
  }
  cout << ans;
}
