#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;

void ad(int &a, int b) { a = (a + b) % M; }

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> inv(n + 2), frq(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n + 1; i++) inv[i] = M - M / i * inv[M % i] % M;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ++frq[x];
    }
    auto split = vector(n + 2, vector<int>(n + 2));
    auto dp = split;
    split[0][0] = 1;
    for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) {
        ad(split[i + 1][j], split[i][j]);
        ad(split[i][j + 1], split[i][j]);
    }
    dp[1][0] = 1;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= n; j++) {
        for (int k = 0, w = 1; j + i * k <= n; w = w * split[j + i * k][i] % M * inv[k + 1] % M, k++) if (int rem = j + i * k - frq[i]; rem >= 0) {
            ad(dp[i + 1][rem], dp[i][j] * w % M);
        }
    }
    cout << dp[n + 1][0] << endl;
}
