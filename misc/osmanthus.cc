#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;

void ad(int &a, int b) { a = (a + b) % M; }

void ac() {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 2, _; i <= n; i++) cin >> _;
    auto dp = vector(m + 1, vector<int>(1 << k));
    dp[0][0] = 1;
    for (int i = 0; i < m; i++) for (int msk = 0; msk < (1 << k); msk++) {
        int cnt = n + __builtin_popcount(msk) + i;
        if (msk & 1) { // this node is already placed
            ad(dp[i + 1][msk >> 1], dp[i][msk]);
        }
        else {
            // insert this node normally
            ad(dp[i + 1][msk >> 1], dp[i][msk] * (2 * cnt - 1) % M);

            // add virtual parent
            for (int kk = 0; kk < k; kk++) if (!((msk >> (kk + 1)) & 1)) {
                ad(dp[i + 1][(msk >> 1) | (1 << kk)], dp[i][msk] * (cnt - 1) % M);
            }
        }
    }
    cout << dp[m][0] << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int c, t; cin >> c >> t;
    while (t--) ac();
}
