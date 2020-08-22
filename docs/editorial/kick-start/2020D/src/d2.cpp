#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = 240000;
int D[maxn], S[maxn], L[maxn], R[maxn], H[maxn];
int RL[maxn], RR[maxn];
int SZ[maxn], F[maxn][20];
void DFS(int u) {
  SZ[u] = u & 1;
  if (u & 1)
    RL[u] = RR[u] = (u + 1) / 2;
  for (int i = 1; i < 20; i += 1)
    F[u][i] = F[F[u][i - 1]][i - 1];
  if (~L[u]) {
    F[L[u]][0] = u;
    DFS(L[u]);
    SZ[u] += SZ[L[u]];
    RL[u] = RL[L[u]];
  }
  if (~R[u]) {
    F[R[u]][0] = u;
    DFS(R[u]);
    SZ[u] += SZ[R[u]];
    RR[u] = RR[R[u]];
  }
}
void work() {
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i < N; i += 1)
    cin >> D[i];
  for (int i = 1; i < 2 * N; i += 1) {
    L[i] = R[i] = -1;
    if (i & 1)
      H[i] = 0;
    else
      H[i] = D[i / 2];
  }
  for (int i = 1, top = 0; i < 2 * N; i += 1) {
    int k = top;
    while (k and H[S[k]] < H[i])
      k -= 1;
    if (k)
      R[S[k]] = i;
    if (k < top)
      L[i] = S[k + 1];
    S[k += 1] = i;
    top = k;
  }
  int root = max_element(H + 1, H + 2 * N) - H;
  F[root][0] = 0;
  DFS(root);
  SZ[0] = INT_MAX;
  for (int i = 0, S, K, X; i < Q; i += 1) {
    cin >> S >> K;
    if (K == 1)
      cout << S << " ";
    else {
      X = S * 2 - 1;
      for (int j = 19; ~j; j -= 1)
        if (SZ[F[X][j]] < K)
          X = F[X][j];
      int L = RL[X], R = RR[X];
      if (L == 1)
        cout << K;
      else if (R == N)
        cout << N - K + 1;
      else if (D[L - 1] > D[R])
        cout << L + K - 1;
      else
        cout << R - K + 1;
      cout << " ";
    }
  }
  cout << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t += 1) {
    cout << "Case #" << t << ": ";
    work();
  }
  return 0;
}
