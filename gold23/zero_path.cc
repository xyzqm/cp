#include <iostream>
using namespace std;
const int N = 1e3;
int n, m, a[N][N], mn[N][N], mx[N][N];
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                if (!i && !j) {
                    mn[i][j] = mx[i][j] = a[i][j];
                    continue;
                }
                mn[i][j] = INT_MAX;
                if (i) mn[i][j] = mn[i - 1][j];
                if (j) mn[i][j] = min(mn[i][j], mn[i][j - 1]);
                mn[i][j] += a[i][j];
                mx[i][j] = INT_MIN;
                if (i) mx[i][j] = mx[i - 1][j];
                if (j) mx[i][j] = max(mx[i][j], mx[i][j - 1]);
                mx[i][j] += a[i][j];
            }
        }
        if (mn[n - 1][m - 1] % 2 == 0 && mn[n - 1][m - 1] <= 0 && mx[n - 1][m - 1] >= 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}