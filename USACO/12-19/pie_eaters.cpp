// http://www.usaco.org/index.php?page=viewproblem2&cpid=972
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e2;
const int M = N * (N + 1) / 2;
int n, m, w[M], l[M], r[M], mx[N][N][N], dp[N][N];
void upd(int& a, int b) {
    a = max(a, b);
}
signed main() {
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> w[i] >> l[i] >> r[i];
        l[i]--, r[i]--;
        for (int j = l[i]; j <= r[i]; j++) upd(mx[j][l[i]][r[i]], w[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 0; j--) {
            for (int k = i; k < n; k++) {
                // printf("%d %d %d: %d\n", i, j, k, mx[i][j][k]);
                if (j) upd(mx[i][j - 1][k], mx[i][j][k]);
                if (k < n - 1) upd(mx[i][j][k + 1], mx[i][j][k]);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            for (int k = i; k < j; k++) upd(dp[i][j], dp[i][k] + dp[k + 1][j]);
            for (int k = i; k <= j; k++) {
                upd(dp[i][j], (k > i) * dp[i][k - 1] + mx[k][i][j] + (k < j) * dp[k + 1][j]);
            }
        }
    }
    cout << dp[0][n - 1] << endl;
}