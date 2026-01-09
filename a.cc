#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 7;

void ad(int &a, const int b) { a = (a + b) % M; }
void mul(int &a, const int b) { a = a * b % M; }

int inv(int x) {
    int r = 1;
    for (int pw = M - 2; pw; pw >>= 1, x = x * x % M) if (pw & 1) mul(r, x);
    return r;
}

void ac() {
    int n, k; cin >> n >> k;
    vector fact(n + 1, 1);
    for (int i = 2; i <= n; i++) fact[i] = fact[i - 1] * i % M;
    vector<array<int, 2>> e(n - 1);
    for (auto &[u, v] : e) cin >> u >> v;

    vector<bool> in(n);
    while (k--) {
        int e; cin >> e;
        in[e] = true;
    }

    vector<vector<array<int, 2>>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        auto [u, v] = e[i];
        g[u].push_back({v, in[i + 1]});
        g[v].push_back({u, in[i + 1]});
    }
    DBG(g);
    vector<array<int, 3>> dp(n + 1);
    vector<int> deg(n + 1);

    auto dfs = [&](this auto dfs, int u, int p) -> void {
        int p01 = 1;
        for (auto [v, f] : g[u]) if (v != p) {
            ++deg[u];
            dfs(v, u);
            dp[v][2] = (dp[v][2] * deg[v] % M + dp[v][1] * (deg[v] - 1) % M) % M;
            if (f) ad(dp[v][1], dp[v][0]), dp[v][0] = 0;
            mul(p01, dp[v][0] + dp[v][1]);
        }
        if (!deg[u]) dp[u] = {1, 0, 0};
        else for (auto [v, _] : g[u]) if (v != p) {
            // 0/1/2 case
            for (int t : {0, 1, 2}) {
                ad(dp[u][t],
                    p01 * inv(dp[v][0] + dp[v][1]) % M
                    * dp[v][t] % M * fact[deg[u] - 1] % M
                );
            }
        }
        if (u == 1) { // need to ensure we don't overcount
            // count number of ways for string to start and end in 0
            int cur = 0, tot = 0;
            for (auto [v, _] : g[u]) if (v != p) {
                int nw = dp[v][0] * inv(dp[v][0] + dp[v][1]) % M;
                ad(tot, cur * nw % M);
                ad(cur, nw);
            }
            if (deg[u] == 1) tot = cur;
            mul(tot, p01);
            DBG(tot);
            if (deg[u] > 1) mul(tot, 2 * fact[deg[u] - 2]);
            mul(p01, fact[deg[u]]);
            DBG(p01);
            int rem = (p01 - tot + M) % M;
            if (deg[u] > 1) mul(rem, (M + 1) / 2);
            dp[u][1] = rem;
        }
        DBG(u);
        DBG(dp[u]);
    };
    dfs(1, 0);
    DBG(dp);
    cout << (dp[1][1] + dp[1][2]) % M << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int c, t; cin >> c >> t;
    while (t--) ac();
}
