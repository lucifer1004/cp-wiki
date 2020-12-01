#include <iostream>
#include <set>
#include <unordered_map>

typedef long long ll;

using namespace std;
int n, s;

void work(unordered_map<int, ll> &cost, set<pair<ll, int>> &pq, ll &extra) {
  string cmd;
  int x, y;
  unordered_map<int, ll> nc;
  set<pair<ll, int>> nq;
  ll ne;
  while (n--) {
    cin >> cmd;
    if (cmd == "if") {
      cin >> x;
      nc.clear();
      nq.clear();
      ne = 0;
      if (cost.count(x)) {
        nc[x] = cost[x];
        nq.emplace(cost[x], x);
        pq.erase({cost[x], x});
        cost.erase(x);
      }
      work(nc, nq, ne);
      if (nc.size() > cost.size()) {
        extra += ne;
        ne = -ne;
        swap(cost, nc);
        swap(pq, nq);
      }
      for (auto [c, v] : nq)
        if (!cost.count(v) || cost[v] > c + ne) {
          pq.erase({cost[v], v});
          cost[v] = c + ne;
          pq.emplace(cost[v], v);
        }
    } else if (cmd == "set") {
      cin >> x >> y;
      if (cost.empty())
        continue;
      if (x != s) {
        auto [c, v] = *pq.begin();
        if (!cost.count(x) || cost[x] > c - y) {
          pq.erase({cost[x], x});
          cost[x] = c - y;
          pq.emplace(cost[x], x);
        }
      }
      extra += y;
    } else
      return;
  }
};

int main() {
  cin >> n >> s;
  string cmd;
  unordered_map<int, ll> cost;
  set<pair<ll, int>> pq;
  ll extra = 0;
  cost[0] = 0;
  pq.emplace(0, 0);
  work(cost, pq, extra);
  printf("%lld", pq.begin()->first + extra);
}