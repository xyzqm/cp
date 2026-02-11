#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

// an O(Q*N^2) brute force

void ac() {
    int n, q; cin >> n >> q;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<bool> vis(n + 1);
    auto dfs = [&](this auto dfs, int u, int v, int p) -> bool {
        if (u == v) return vis[v] = true;
        for (int y : g[u]) if (y != p && dfs(y, v, u)) {
            return vis[u] = true;
        }
        return false;
    };
    while (q--) {
        int l, r; cin >> l >> r;
        vis.assign(n + 1, false);
        while (l <= r) dfs(l++, r, 0);
        DBG(vis);
        int res = ranges::count(vis, true) - 1;
        cout << res << endl;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
