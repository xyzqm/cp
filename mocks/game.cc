#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int ac() {
    int n, k; cin >> n >> k;
    auto g = vector(n + 1, vector<array<int, 2>>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back({i, v});
        g[v].push_back({i, u});
    }
    for (auto &adj : g) sort(adj.begin(), adj.end(), greater());
    auto blocked = [&](int u, int bob, int opt) { return g[u][opt][1] == bob; };
    auto nx = [&](int u, int bob) {
        if (!blocked(u, bob, 0)) return g[u][0][1];
        else if (g[u].size() < 2) return u;
        else return g[u][blocked(u, bob, 0)][1];
    };
    vector<int> pos = {k, nx(k, 1)};
    if (pos[0] == pos[1]) return 0;
    while (pos.size() < 3 || pos.back() != pos[pos.size() - 3]) {
        int nu = nx(pos.back(), -1);
        pos.push_back(nu);
    }
    DBG(pos);
    // DBG(ans);
    // first, find leaves in component of k
    vector<int> leaves;
    auto dfs = [&](auto &&f, int x, int p) -> void {
        if (g[x].size() == 1) leaves.push_back(x);
        for (int cnt = 0; auto [i, y] : g[x]) if (cnt++ < 2 - (p > 0) && y != p) f(f, y, x);
    };
    dfs(dfs, k, 0);
    DBG(leaves);
    return 0;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) cout << ac() << "\n";
}
