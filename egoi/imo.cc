#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 2;
const int M = 101;

int n, m, k, sum[N], zeros[N];
vector<int> a[N];

int kp[M][M * M], dp[N][M];

int smin(int &a, int b) { return a = min(a, b); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    a[0].assign(m + 1, n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].resize(m);
        for (int &x : a[i]) cin >> x;
        a[i].push_back(i);
    }
    sort(a + 1, a + n + 1, [](auto a, auto b) {
        int s_a = accumulate(a.begin(), --a.end(), 0);
        int s_b = accumulate(b.begin(), --b.end(), 0);
        if (s_a != s_b) return s_a < s_b;
        else return a[m] > b[m];
    });

    int MX = k * m + 1; // max possible right index

    for (int i = 0; i <= m; i++) fill(kp[i], kp[i] + MX, MX);
    for (int i = 1; i <= n; i++) {
        sum[i] = accumulate(a[i].begin(), --a[i].end(), 0);
        zeros[i] = count(a[i].begin(), --a[i].end(), 0);
        for (int j = sum[i - 1]; j <= sum[i]; j++) kp[0][j] = sum[i];
        for (int j = 1; j <= m; j++) kp[j][sum[i - 1]] = k * m + 1;
        for (int j = 0; j < m; j++) {
            for (int k = sum[i - 1] + a[i][j]; k <= sum[i]; k++) {
                for (int h = m; h --> 0; ) {
                    smin(kp[h + 1][k - a[i][j]], kp[h][k] - a[i][j]);
                }
            }
        }
    }
    auto nx = [&](int i, int j, int r) { // find next subset sum w/ j blanks >= r
        if (r > sum[i]) return MX;
        if (r < sum[i]) return kp[j][r];
        else return zeros[i] >= j ? r : MX;
    };

    for (int i = 1; i <= n + 1; i++) fill(dp[i], dp[i] + M, MX);
    dp[1][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; j + k <= m; k++) {
                smin(dp[i + 1][j + k], nx(i, k, dp[i][j] + (a[i - 1][m] < a[i][m])) + k * ::k);
            }
        }
    }
    for (int i = m; i >= 0; i--) if (dp[n + 1][i] < MX) {
        cout << n * m - i << endl;
        return 0;
    }
}
