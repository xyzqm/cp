#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int K = 20;

int32_t main() {
    int n, q; cin >> n >> q;
    vector<vector<array<int, 2>>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector<int> a(n + 1), dp(n + 1), rt(n + 1), dep(n + 1), val(n + 1), ww(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<array<array<int, 2>, K>> jmp(n + 1);
    jmp[1][0] = {1, 0};

    auto dfs = [&](auto &&f, int x, int p) -> int {
        dep[x] = dep[p] + 1;
        dp[x] = a[x];
        for (auto [y, w] : g[x]) if (y != p) dp[x] += (val[y] = max(f(f, y, x) - 2 * w, (int)0));
        for (auto [y, w] : g[x]) if (y != p) jmp[y][0] = {x, dp[x] - val[y] - w};
        return dp[x];
    };
    dfs(dfs, 1, 0);
    auto rrt = [&](auto &&f, int x, int p, int p_) -> void {
        int cur = dp[x] + (rt[x] = max(p_, (int)0));
        for (auto [y, w] : g[x]) if (y != p) {
            ww[y] = w;
            f(f, y, x, cur - val[y] - 2 * w);
        }
    };
    rrt(rrt, 1, 0, 0);
    for (int k = 0; k + 1 < K; k++) for (int i = 1; i <= n; i++) {
        auto [nx, dif] = jmp[i][k];
        jmp[i][k + 1] = {jmp[nx][k][0], dif + jmp[nx][k][1]};
    }
    while (q--) {
        int u, v; cin >> u >> v;
        if (dep[u] < dep[v]) swap(u, v);
        int u_ = dp[u], v_ = dp[v];
        for (int k = K; k --> 0; ) if ((dep[u] - dep[v]) >> k & 1) {
            u_ += jmp[u][k][1];
            u = jmp[u][k][0];
        }
        if (u == v) cout << u_ + rt[u] << endl;
        else {
            for (int k = K; k --> 0; ) if (jmp[u][k][0] != jmp[v][k][0]) {
                u_ += jmp[u][k][1];
                u = jmp[u][k][0];
                v_ += jmp[v][k][1];
                v = jmp[v][k][0];
            }
            int fa = jmp[u][0][0];
            assert(fa == jmp[v][0][0]);
            cout << dp[fa] - val[u] - val[v] + u_ + v_ - ww[u] - ww[v] + rt[fa] << endl;
        }
    }
}
