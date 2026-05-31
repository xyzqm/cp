#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    auto g = vector(n + 1, vector<array<int, 2>>());
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        for (int _ : {0, 1}) {
            g[u].push_back({v, w});
            swap(u, v);
        }
    }
    vector<int> path(n + 1);
    vector<bool> vis(n + 1);
    vector<int> basis;
    auto add = [&](int x) {
        for (int v : basis) x = min(x, x ^ v);
        if (x) basis.push_back(x);
    };
    auto dfs = [&](auto &&f, int x) -> void {
        vis[x] = true;
        for (auto &[y, w] : g[x]) {
            if (vis[y]) add(path[x] ^ path[y] ^ w);
            else {
                path[y] = path[x] ^ w;
                f(f, y);
            }
        }
    };
    dfs(dfs, 1);
    int ans = 0;
    sort(basis.begin(), basis.end(), greater<int>());
    // ranges::sort(basis, greater());
    for (int v : basis) ans = max(ans, ans ^ v);
    cout << ans << "\n";
}
