#include <iostream>
#include <unordered_set>

using namespace std;
int main() {
  int n;
  cin >> n;
  unordered_set<string> clean, banged;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (s[0] == '!')
      banged.insert(s.substr(1));
    else
      clean.insert(s);
  }
  for (string s : clean)
    if (banged.count(s)) {
      cout << s;
      return 0;
    }
  cout << "satisfiable";
}
