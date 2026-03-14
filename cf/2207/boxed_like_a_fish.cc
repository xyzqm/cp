#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, k, v; cin >> n >> k >> v;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout << array{"YES\n", "NO\n"}[([&](this auto dfs, int x, int p) -> int {
        if (g[x].size() == 1) return 0;
        vector<int> opts;
        for (int &y : g[x]) if (y != p) {
            opts.push_back(dfs(y, x) + 1);
            ranges::sort(opts);
            if (opts.size() > 2) opts.pop_back();
        }
        if (opts.size() > 1 && opts[0] + opts[1] <= k + 1) return 0;
        else return opts[0];
    }(v, 0) > 0)];
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
