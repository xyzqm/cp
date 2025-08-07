#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;

struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v((v % M + M) % M) {}
	operator int() { return v; }
};

mint ac() {
    int n, m; cin >> n >> m;
    auto g = vector(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (m >= n) return 0;
    vector<mint> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    auto dfs = [&](this auto dfs, int x, int mx) -> mint {
        for (int y : g[x]) g[y].erase(ranges::find(g[y], x));
        int non_leaves = ranges::count_if(g[x], [&](int y) { return g[y].size() > 0; });
        if (non_leaves > mx) return 0;
        mint res = 1;
        if (non_leaves == 2) res = res * fact[g[x].size() - 2] * 2;
        else if (non_leaves == 1) res = res * fact[g[x].size() - 1] * mx;
        else res = res * fact[g[x].size()];
        for (int y : g[x]) if (g[y].size()) {
            res = res * dfs(y, 1);
        }
        return res;
    };
    return dfs(g[1].size() > 1 ? 1 : g[1][0], 2) * 2;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
