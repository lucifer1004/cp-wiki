#include <bitset>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

inline int odd(int x) { return bitset<12>(x).count() % 2; }

int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    cout << "Case #" << case_num << ": ";
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    set<int> odds;
    int tot = 0;
    for (int i = 0; i < n; ++i) {
      int ai;
      cin >> ai;
      a[i] = odd(ai);
      tot += a[i];
      if (a[i])
        odds.insert(i);
    }
    for (int i = 0; i < q; ++i) {
      int p, v;
      cin >> p >> v;
      int new_val = odd(v);
      tot += new_val - a[p];
      if (a[p])
        odds.erase(p);
      if (new_val)
        odds.insert(p);
      a[p] = new_val;
      int ans = tot % 2 == 0 ? n : max(*odds.rbegin(), n - *odds.begin() - 1);
      cout << ans << " ";
    }
    cout << endl;
  }
}
