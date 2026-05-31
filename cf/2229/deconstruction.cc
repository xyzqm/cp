#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 998244353;
void ad(int &a, int b) { if ((a += b) >= M) a -= M; }
void sb(int &a, int b) { if ((a -= b) < 0) a += M; }

void ac() {
    int n; cin >> n;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> p(n + 1);
    [&](this auto dfs, int x) -> void {
        for (int y : g[x]) if (y != p[x]) {
            p[y] = x;
            dfs(y);
        }
    }(n);
    vector<int> dp(n + 1), deg(n + 1);
    dp[n] = 1;
    for (int i = n, sm = dp[n]; i --> 1; ) if (!deg[i]) {
        for (int j = i; j < n; j = p[j]) {
            ++deg[j];
            if (deg[p[j]] == 1) sb(sm, dp[p[j]]); // no longer leaf
            if (++deg[p[j]] > 1) break;
        }
        ad(sm, dp[i] = sm);
    }
    int mx = 0;
    for (int i = 1; i <= n; i++) if (deg[i] == 1) mx = i;
    cout << dp[mx] << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
