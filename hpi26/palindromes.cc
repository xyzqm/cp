#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

using T = array<int, 2>;
void smin(T &a, T b) { a = min(a, b); }
T operator+(T a, T b) {
    return {a[0] + b[0], a[1] + b[1]};
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    string s; cin >> s;
    auto dp = vector(n + 1, vector(n + 1, array{0, 0}));
    for (int l = n; l --> 0; ) for (int r = l + 1; r <= n; r++) {
        dp[l][r] = {r - l, 0};
        if (r > l + 1) if (s[l] == s[r - 1]) {
            if (dp[l + 1][r - 1][0] == 0) { // if we can delete all characters
                smin(dp[l][r], array{0, int(r - l == 2)} + dp[l + 1][r - 1]);
            }
            for (int m = l + 1; m + 1 < r; m++) {
                auto &lef = dp[l + 1][m], &rig = dp[m + 1][r - 1];
                if (!lef[0] && !rig[0]) {
                    // auto nx = array{0, 1} + lef + rig;
                    // if (dp[l][r][0] < r - l) {
                    //     DBG(l);
                    //     DBG(r);
                    //     cout << s.substr(l, r - l) << endl;
                    //     assert(nx >= dp[l][r]);
                    // }
                    smin(dp[l][r], array{0, 1} + lef + rig);
                }
            }
        }
        for (int m = l + 1; m < r; m++) {
            smin(dp[l][r], dp[l][m] + dp[m][r]);
        }
    }
    // DBG(dp[1][n - 1]);
    cout << n - dp[0][n][0] << "\n" << dp[0][n][1] << "\n";
}
