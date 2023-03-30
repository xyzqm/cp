#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 1, K = 1e3 + 1;
// mx[l][r] -> max from l to r
// dp[i][j] -> used first i cows, j cows not in group
// basically, cows [i - j + 1, i] are not in a group
// transition:
// if we finish the group with cow i + 1,
// dp[i + 1][0] = dp[i][j] + (j + 1) * mx[i - j + 1][i + 1]
int n, k, a[N], p[N], dp[N][K], mx[N];
int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        p[i] = p[i - 1] + a[i];
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= i + 1; j++) {
            mx[j] = max(mx[j], a[i + 1]);
        }
        for (int j = 0; j <= min(i, k - 1); j++) {
            if (j < k - 1) dp[i + 1][j + 1] = dp[i][j];
            int new_state = dp[i][j] + (j + 1) * mx[i - j + 1];
            dp[i + 1][0] = max(dp[i + 1][0], new_state);
        }
    }
    cout << dp[n][0];
}