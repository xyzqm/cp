#include <iostream>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
const int N = 2e3 + 1;
const int M = 1e9 + 7;
char a[N], b[N];
P dp[N][N];
int S(P p) { return (p.first + p.second) % M; }
bool d(char c) { return c >= '1' && c <= '9'; }
int ad(int& a, int b) { return a = (a + b) % M; }
int sb(int& a, int b) { return a = (((a - b) % M) + M) % M; }
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        dp[0][0] = {1, 0};
        for (int i = 1; i <= n; i++) {
            if (b[i] == '0') dp[0][i] = {1, 0};
            else if (b[i] == '+') dp[0][i] = {0, 1};
            else dp[0][i] = dp[0][i - 1];
            if (a[i] == '0') dp[i][0] = {1, 0};
            else if (a[i] == '+') dp[i][0] = {0, 1};
            else dp[i][0] = dp[i - 1][0];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = {0, 0};
                if (a[i] == '0') dp[i][j].first = 1;
                else if (a[i] != '+') dp[i][j].first |= dp[i - 1][j].first;
                if (a[i] != '0') ad(dp[i][j].second, dp[i - 1][j].second + (dp[i - 1][j].first * (a[i] == '+')));
                if (b[j] == '0') dp[i][j].first = 1;
                else if (b[j] != '+') dp[i][j].first |= dp[i][j - 1].first;
                if (b[j] != '0') ad(dp[i][j].second, dp[i][j - 1].second + (dp[i][j - 1].first * (b[j] == '+')));
                if (a[i] == '+' && b[j] == '+' || a[i] == '1' && b[j] == '+' || b[j] == '1' && a[i] == '+') {
                    sb(dp[i][j].second, S(dp[i - 1][j - 1]));
                } else if (d(a[i]) && d(b[j])) {
                    sb(dp[i][j].second, dp[i - 1][j - 1].second);
                }
            }
        }
        cout << S(dp[n][n]) << endl;
    }
    return 0;
}