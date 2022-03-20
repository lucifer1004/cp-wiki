#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void read(T &x) {
  x = 0;
  char c = getchar();
  T sig = 1;
  for (; !isdigit(c); c = getchar())
    if (c == '-') sig = -1;
  for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
  x *= sig;
}

class Solution {
 public:
  void solve(int case_num) {
    printf("Case #%d: ", case_num);

    string N;
    cin >> N;
    int sum = 0;
    for (char ch : N) sum += ch - '0';
    int need = (9 - sum % 9) % 9;
    if (need == 0) {
      cout << N[0] << '0' << N.substr(1) << endl;
      return;
    }
    int n = N.size();
    for (int i = 0; i < n; ++i) {
      if (N[i] > (need + '0')) {
        cout << N.substr(0, i) << (char)(need + '0') << N.substr(i, n - i)
             << endl;
        return;
      }
    }
    cout << N << (char)(need + '0') << endl;
  }
};

int main() {
  int t;
  read(t);
  for (int i = 1; i <= t; ++i) {
    Solution solution = Solution();
    solution.solve(i);
  }
}
