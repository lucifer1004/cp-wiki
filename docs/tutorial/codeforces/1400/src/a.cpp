#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s, ans;
    cin >> n >> s;
    for (int i = 0; i < n; ++i)
      ans.push_back(s[2 * i]);
    cout << ans << endl;
  }
}