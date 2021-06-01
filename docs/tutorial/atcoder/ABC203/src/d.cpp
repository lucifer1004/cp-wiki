#include <cstdio>
#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

template<typename T>
void read(T &x) {
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
public:
    void solve() {
        int n, k;
        read(n), read(k);
        vector <vector<int>> a(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                read(a[i][j]);

        int pos = (k * k - 1) / 2 + 1;
        int lo = 0, hi = INF;
        vector <vector<int>> v(n, vector<int>(n)), s(n + 1, vector<int>(n + 1));
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    v[i][j] = (int) (a[i][j] <= mid);
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + v[i - 1][j - 1];
            if (s[n][n] < pos) {
                lo = mid + 1;
                continue;
            }
            bool found = false;
            for (int i = k; i <= n; ++i) {
                for (int j = k; j <= n; ++j)
                    if (s[i][j] - s[i - k][j] - s[i][j - k] + s[i - k][j - k] >= pos) {
                        found = true;
                        break;
                    }
                if (found)
                    break;
            }

            if (found)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        printf("%d\n", lo);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution solution = Solution();
    solution.solve();
}