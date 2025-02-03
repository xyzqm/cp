#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int N = 751;
const int inf = 1e9;
int n, dp[N][N]; // dp[i][j] -> cost of uniting range i...j with root i
int g[2][N][N], gp[2][N][N]; // 0 for add, 1 for remove

void pref(int a[N][N], int p[N][N]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
           p[i][j] += p[i - 1][j];
           p[i][j] += p[i][j - 1];
           p[i][j] -= p[i - 1][j - 1];
           p[i][j] += a[i][j];
        }
    }
}

int sum(int p[N][N], int l, int r) {
    if (l > r) return 0;
    return p[r][r] - p[l - 1][r] - p[r][l - 1] + p[l - 1][l - 1];
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            int x; cin >> x;
            g[x < 0][j][i] = abs(x);
        }
    }
    for (int t : {0, 1}) pref(g[t], gp[t]);
    for (int i = 1; i <= n; i++) fill(dp[i], dp[i] + N, inf);
    for (int i = n; i > 0; i--) {
        dp[i][i] = 0;
        for (int j = i + 1; j <= n; j++) {
            dp[i][j] = min(dp[i][j], g[0][i][i + 1] + dp[i + 1][j]); // add single edge from i to i + 1
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = min(dp[i][j],
                    dp[i][k] + g[0][i][k + 1] + dp[k + 1][j] // add edge to k + 1
                    + sum(gp[1], i + 1, j) - sum(gp[1], i + 1, k) - sum(gp[1], k + 1, j) // have to remove cross-edges
                );
            }
        }
    }
    cout << dp[1][n] << endl;
}
