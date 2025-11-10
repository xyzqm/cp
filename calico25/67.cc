#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n, m; cin >> n >> m;
    vector<bitset<100>> deps(10);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == '.') continue;
            deps[c - '0'][j] = 1;
        }
    }
    int ans = 0;

    for (int i = 9; i > 0; i--) {
        ans += deps[i].count();
        deps[i - 1] |= deps[i];
    }
    cout << ans << endl;
}

const int K = 1e6 + 1;
int dp[K][2];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    dp[1][0] = dp[1][1] = 0; // player 1 always loses
    for (int i = 2; i < K; i++) {
        dp[i][1] = !dp[i - 1][1] || dp[i - 1][0];
        dp[i][0] = !dp[i - 1][1] || !dp[i - 1][0];
    }
    int t; cin >> t;
    while (t--) {
        int k; cin >> k;
        cout << (dp[k][0] ? "Big Ben" : "Oski") << endl;
    }
}
