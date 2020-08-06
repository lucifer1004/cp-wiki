#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long ll;
const ll radix = 1001;

void solve(int case_num) {
  int n, s;
  cin >> n >> s;
  vector<ll> a;
  unordered_map<ll, int> cnt;
  for (int i = 0; i < n; ++i) {
    int skill_count;
    cin >> skill_count;
    vector<int> skills(skill_count);
    for (int j = 0; j < skill_count; ++j)
      scanf("%d", &skills[j]);
    sort(skills.begin(), skills.end());
    ll hash = 0;
    for (const int &skill : skills)
      hash = hash * radix + skill;
    a.emplace_back(hash);
    for (int j = 0; j < (1 << skill_count); ++j) {
      ll hash = 0;
      for (int k = 0; k < skill_count; ++k)
        if (j & (1 << k))
          hash = hash * radix + skills[k];
      cnt[hash]++;
    }
  }
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += n - cnt[a[i]];
  }
  cout << "Case #" << case_num << ": " << ans << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
  return 0;
}
