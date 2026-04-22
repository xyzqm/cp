#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

using ld = long double;

void ac() {
    int n; cin >> n;
    string s; cin >> s;
    s.insert(s.begin(), '0');
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<array<ld, 2>> dp(n + 1, {1/.0, 1/.0}); // 1 => edge directed away from i, 0 => else
    [&](this auto &&dfs, int x, int p) -> void {
        ld base = 0;
        vector<ld> opts;
        for (int y : g[x]) if (y != p) {
            dfs(y, x);
            base += dp[y][0];
            opts.push_back(dp[y][1] - dp[y][0]);
        }
        ranges::sort(opts);
        opts.insert(opts.begin(), base);
        partial_sum(opts.begin(), opts.end(), opts.begin());
        for (int in_deg = 0; in_deg < opts.size(); in_deg++) for (int t : {0, 1}) {
            ld id = in_deg + 1 - t;
            dp[x][t] = min(dp[x][t], opts[in_deg] + array{(ld)g[x].size()/id, (ld)0.0}[s[x] == '1']);
        }
    }(1, 0);
    DBG(dp);
    cout << fixed << setprecision(6) << dp[1][1] << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
