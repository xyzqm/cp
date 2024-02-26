// http://www.usaco.org/index.php?page=viewproblem2&cpid=553
#include <iostream>
#define INC(A, B) A = (A + B) % M
using namespace std;
using ll = long long;
const int N = 5e2 + 1;
const int M = 1e9 + 7;
char g[N][N];
ll dp1[N][N], dp2[N][N];
int main() {
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> g[i][j];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            for (int k = n - 1; k >= max(i, n - 1 - i - j); k--) {
                int h = 2 * (n - 1) - i - j - k;
                if (g[i][j] == g[k][h]) {
                    char cd = 0, cr = 0;
                    if (k < n - 1) cd = g[k + 1][h];
                    if (h < n - 1) cr = g[k][h + 1];
                    if (!i && !j) dp2[j][k] = 1;
                    if (i) {
                        if (g[i - 1][j] == cd) INC(dp2[j][k], dp1[j][k + 1]);
                        if (g[i - 1][j] == cr) INC(dp2[j][k], dp1[j][k]);
                    }
                    if (j) {
                        if (g[i][j - 1] == cd) INC(dp2[j][k], dp2[j - 1][k + 1]);
                        if (g[i][j - 1] == cr) INC(dp2[j][k], dp2[j - 1][k]);
                    }
                    if (i == k && j == h) INC(ans, dp2[j][k]);
                }
            }
        }
        for (int j = 0; j < n; j++) for (int k = 0; k < n; k++) {
            dp1[j][k] = dp2[j][k];
            dp2[j][k] = 0;
        }
    }
    cout << ans << endl;
}