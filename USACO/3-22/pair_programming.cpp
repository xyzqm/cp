#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e3 + 1;
const int M = 1e9 + 7;
char a[N], b[N];
bool zero[N][N];
ll dp[N][N];
bool digit(char c) { return c >= '1' && c <= '9'; }
ll ad(ll& a, ll b) { return a = (a + b) % M; }
ll sb(ll& a, ll b) { return a = (((a - b) % M) + M) % M; }
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        zero[0][0] = true;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (!i && !j) continue;
                zero[i][j] =
                    a[i] == '0' || b[j] == '0' ||
                    i && zero[i - 1][j] && a[i] != '+' ||
                    j && zero[i][j - 1] && b[j] != '+';
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            dp[0][i] = !zero[0][i];
            dp[i][0] = !zero[i][0];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = 0;
                if (a[i] != '0') ad(dp[i][j], dp[i - 1][j]);
                if (a[i] == '+') ad(dp[i][j], zero[i - 1][j]);
                if (b[j] != '0') ad(dp[i][j], dp[i][j - 1]);
                if (b[j] == '+') ad(dp[i][j], zero[i][j - 1]);
                if (a[i] == '+' && b[j] == '+' || a[i] == '1' && b[j] == '+' || a[i] == '+' && b[j] == '1') {
                    sb(dp[i][j], dp[i - 1][j - 1] + zero[i - 1][j - 1]);
                } else if (digit(a[i]) && digit(b[j])) {
                    sb(dp[i][j], dp[i - 1][j - 1]);
                }
            }
        }
        cout << ad(dp[n][n], zero[n][n]) << endl;
    }
    return 0;
}