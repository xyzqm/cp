#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 9;
void ad(int &a, const int b) {
    a = (a + b) % M;
    // if ((a += b) >= M) a -= M;
}

const int A = 1000;
const int B = 1000;
int split[A][B];
int dp[31][31];
int ways[32][31][B][2];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, c; cin >> n >> m >> c;
    split[0][0] = 1;
    for (int i = 0; i + 1 < A; i++) {
        for (int j = 0; j + 1 < B; j++) {
            ad(split[i + 1][j], split[i][j]);
            ad(split[i][j + 1], split[i][j]);
        }
    }
    auto choose = [&](int n, int k) { return n < k ? 0 : split[n - k][k]; };
    ways[1][0][0][0] = 1;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) for (int cur = 0; cur < B; cur++) {
        for (int old = 0; old <= j && cur + old < B; old++) { // add to previous columns
            ad(ways[i][j][cur + old][1], ways[i][j][cur][0] * choose(j, old) % M);
        }
        for (int nu = 0; j + nu <= m && cur + nu < B; nu++) { // add to new columns
            ad(ways[i + 1][j + nu][cur + nu][0], ways[i][j][cur][1] * split[j][nu] % M);
        }
        ad(ways[i + 1][j][cur][0], M - ways[i][j][cur][0]);
    }

    // for (int i = 1; i <= min(n, m); i++) for (int j = 1; j <= min(n, m); j++) for (int cur = 0; cur < B; cur++) {
    //     // DBG(i);
    //     // DBG(j);
    //     // DBG(cur);
    //     // DBG(ways[i + 1][j][cur][0]);
    //     // DBG(ways[j + 1][i][cur][0]);
    //     assert(ways[i + 1][j][cur][0] == ways[j + 1][i][cur][0]);
    // }

    dp[n][m] = 1; // # of remaining rows
    while (c--) {
        int pieces; cin >> pieces;
        assert(pieces > 0);
        for (int cur_r = 0; cur_r <= n; cur_r++) for (int cur_c = 0; cur_c <= m; cur_c++) {
            for (int dr = 1; dr <= cur_r; dr++) for (int dc = 1; dc <= cur_c; dc++) {
                ad(dp[cur_r - dr][cur_c - dc], dp[cur_r][cur_c] * ways[dr + 1][dc][pieces][0] % M * choose(cur_r, dr) % M * choose(cur_c, dc) % M);
            }
            dp[cur_r][cur_c] = 0;
        }
        DBG(dp);
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) ad(ans, dp[i][j]);
    cout << ans << "\n";
}
