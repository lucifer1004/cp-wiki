#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
typedef long long ll;

vector<int> primes{2, 3, 5, 7};

class Solution {
  void process(int p, vector<ll> &cnt) {
    unordered_map<int, int> factor;
    int i = 0;
    int p0 = p;
    while (p > 1) {
      while (p % primes[i] == 0) {
        factor[primes[i]]++;
        p /= primes[i];
      }
      i++;
      if (primes[i] * primes[i] > p) {
        if (p > 1)
          factor[p]++;
        break;
      }
    }
    vector<int> nums{1};
    for (const auto &f : factor) {
      int n = nums.size();
      for (int j = 0; j < n; ++j) {
        int m = nums[j];
        for (int k = 1; k <= f.second; ++k) {
          m *= f.first;
          nums.emplace_back(m);
        }
      }
    }
    for (int num : nums) {
      cnt[num] += 1;
    }
  }

public:
  void solve(int case_num) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<ll> cnt(n + 1);
    for (int i = 0; i < m; ++i) {
      int p;
      scanf("%d", &p);
      process(p, cnt);
    }

    ll ans = 0;
    for (int i = 0; i < q; ++i) {
      int r;
      scanf("%d", &r);
      ans += n / r - cnt[r];
    }
    cout << "Case #" << case_num << ": " << ans << endl;
  }
};

int main() {
  Solution solution;
  int t;
  cin >> t;

  for (int i = 4; i < 501; ++i) {
    int n = 2 * i + 1;
    int j = 0;
    bool prime = true;
    while (primes[j] * primes[j] <= n) {
      if (n % primes[j] == 0) {
        prime = false;
        break;
      }
      j++;
    }
    if (prime)
      primes.emplace_back(n);
  }

  for (int i = 1; i <= t; ++i)
    solution.solve(i);
}
